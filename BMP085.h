/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BMP085.h
 * Author: str-har-pc
 *
 * Created on 11 de marzo de 2016, 02:58 PM
 */

#ifndef BMP085_H
#define BMP085_H

#include <stdint.h>
#include <string.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "I2Cdev.h"

#define BMP085_I2C_ADDRESS 0x77

#define TEMPERATURE 0
#define PRESSURE 1
#define OVER_SAMPLING_SETTING 1 // use to be 3
using namespace std;

class BMP085 {
public:
    BMP085();
    BMP085(const BMP085& orig);
    
    void initializeBaro();
    const float getRelativeBaroAltitude();
    float getBaroGroundAltitude();
    float getBaroAltitude();
    void measureGroundBaro();
    void measureBaro();
    
    I2Cdev i2cBMP085;
    
    virtual ~BMP085();
private:
    
    unsigned long vehicleState = 0;

    float baroAltitude      = 0.0;
    float baroRawAltitude   = 0.0;
    float baroGroundAltitude = 0.0;
    float baroSmoothFactor   = 0.04;
    
    uint8_t overSamplingSetting = OVER_SAMPLING_SETTING;
    int16_t ac1 = 0, ac2 = 0, ac3 = 0;
    uint16_t ac4 = 0, ac5 = 0, ac6 = 0;
    int16_t b1 = 0, b2 = 0, mb = 0, mc = 0, md = 0;
    int32_t pressure = 0;
    int32_t rawPressure = 0, rawTemperature = 0;
    uint8_t pressureCount = 0;
    float pressureFactor = 1 / 5.255;
    bool isReadPressure = false;
    float rawPressureSum = 0;
    uint8_t rawPressureSumCount = 0;
    
    void requestRawPressure();
    long readRawPressure();
    void requestRawTemperature();
    unsigned int readRawTemperature();
    void measureBaroSum();
    void evaluateBaroAltitude();
    
    uint8_t buff[24];
};

#endif /* BMP085_H */