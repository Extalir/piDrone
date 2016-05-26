/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BMP085.cpp
 * Author: str-har-pc
 * 
 * Created on 11 de marzo de 2016, 02:58 PM
 */

#include "BMP085.h"

float filterSmooth(float currentData, float previousData, float smoothFactor)
{
  if (smoothFactor != 1.0) //only apply time compensated filter if smoothFactor is applied
  {
    return (previousData * (1.0 - smoothFactor) + (currentData * smoothFactor));
  }
  return currentData; //if smoothFactor == 1.0, do not calculate, just bypass!
}

BMP085::BMP085() {
    memset(buff,0,24);
}
void BMP085::initializeBaro()
{
    // oversampling setting
    // 0 = ultra low power
    // 1 = standard
    // 2 = high
    // 3 = ultra high resolution
    overSamplingSetting = OVER_SAMPLING_SETTING;
    pressure = 0;
    baroGroundAltitude = 0;
    pressureFactor = 1 / 5.255;

    //i2cBMP085.writeByte(BMP085_I2C_ADDRESS,0xD0);
    i2cBMP085.readByte(BMP085_I2C_ADDRESS,0xD0,buff);
    if(buff[0]==0x55)
        vehicleState|=0x008;
    i2cBMP085.readBytes(BMP085_I2C_ADDRESS,0xAA,22,buff);
    ac1 = ( buff[0] << 8 | buff[1] );
    ac2 = ( buff[2] << 8 | buff[3] );
    ac3 = ( buff[4] << 8 | buff[5] );
    ac4 = ( buff[6] << 8 | buff[7] );
    ac5 = ( buff[8] << 8 | buff[9] );
    ac6 = ( buff[10] << 8 | buff[11] );
    b1 = ( buff[12] << 8 | buff[13] );
    b2 = ( buff[14] << 8 | buff[15] );
    mb = ( buff[16] << 8 | buff[17] );
    mc = ( buff[18] << 8 | buff[19] );
    md = ( buff[20] << 8 | buff[21] );
    memset(buff,0,24);

    requestRawTemperature(); // setup up next measure() for temperature
    isReadPressure = false;
    pressureCount = 0;
    measureBaro();
    delay(5); // delay for temperature
    measureBaro();
    delay(50); // delay for pressure
    measureGroundBaro();
    // check if measured ground altitude is valid
    while (abs(baroRawAltitude - baroGroundAltitude) > 10) {
      delay(26);
      measureGroundBaro();
    }
    baroAltitude = baroGroundAltitude;
}

void BMP085::measureBaro()
{
    measureBaroSum();
    evaluateBaroAltitude();
}

void BMP085::measureBaroSum() {
  // switch between pressure and temperature measurements
  // each loop, since it is slow to measure pressure
  if (isReadPressure) {
    rawPressureSum += readRawPressure();
    rawPressureSumCount++;

    if (pressureCount == 4)
    {
      requestRawTemperature();
      pressureCount = 0;
      isReadPressure = false;
    }
    else {
      requestRawPressure();
    }
    pressureCount++;
  }
  else { // select must equal TEMPERATURE
    rawTemperature = (long)readRawTemperature();
    requestRawPressure();
    isReadPressure = true;
  }
}

void BMP085::evaluateBaroAltitude() {
  long x1, x2, x3, b3, b5, b6, p;
  unsigned long b4, b7;
  int32_t tmp;

  //calculate true temperature
  x1 = ((long)rawTemperature - ac6) * ac5 >> 15;
  x2 = ((long) mc << 11) / (x1 + md);
  b5 = x1 + x2;

  if (rawPressureSumCount == 0) { // it may occur at init time that no pressure has been read yet!
    return;
  }
  rawPressure = rawPressureSum / rawPressureSumCount;
  rawPressureSum = 0.0;
  rawPressureSumCount = 0;

  //calculate true pressure
  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11;
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;

  // Real Bosch formula - b3 = ((((int32_t)ac1 * 4 + x3) << overSamplingSetting) + 2) >> 2;
  // The version below is the same, but takes less program space
  tmp = ac1;
  tmp = (tmp * 4 + x3) << overSamplingSetting;
  b3 = (tmp + 2) >> 2;

  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
  b7 = ((uint32_t) rawPressure - b3) * (50000 >> overSamplingSetting);
  p = b7 < 0x80000000 ? (b7 << 1) / b4 : (b7 / b4) << 1;

  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  pressure = (p + ((x1 + x2 + 3791) >> 4));
  
  baroRawAltitude = 44330 * (1 - pow(pressure / 101325.0, pressureFactor)); // returns absolute baroAltitude in meters
  baroAltitude = filterSmooth(baroRawAltitude, baroAltitude, baroSmoothFactor);
}

const float BMP085::getRelativeBaroAltitude() {
  return baroAltitude - baroGroundAltitude;
}

float BMP085::getBaroGroundAltitude()
{
  return baroGroundAltitude;
}

float BMP085::getBaroAltitude()
{
  return baroAltitude;
}

void BMP085::measureGroundBaro() {
  // measure initial ground pressure (multiple samples)
  double altSum = 0.0;
  for (int i = 0; i < 25; i++) {
    measureBaro();
    altSum += baroRawAltitude;
    delay(50);
  }
  baroGroundAltitude = altSum / 25;
}

void BMP085::requestRawPressure() {
  i2cBMP085.writeByte_B(BMP085_I2C_ADDRESS, 0x34 + (overSamplingSetting << 6));
}

long BMP085::readRawPressure() {
    i2cBMP085.readBytes(BMP085_I2C_ADDRESS, 0xF6, 3, buff);
  return (((unsigned long)buff[0] << 16) | ((unsigned long)buff[1] << 8) | ((unsigned long)buff[2])) >> (8 - overSamplingSetting);
}

void BMP085::requestRawTemperature() {
  i2cBMP085.writeByte_B(BMP085_I2C_ADDRESS, 0x2E);
}

unsigned int BMP085::readRawTemperature() {
    i2cBMP085.readBytes(BMP085_I2C_ADDRESS, 0xF6, 2, buff);
    return ((buff[0]<<8)|buff[1]);
}

BMP085::BMP085(const BMP085& orig) {
}

BMP085::~BMP085() {
}