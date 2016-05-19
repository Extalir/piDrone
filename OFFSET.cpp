/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Drone.h"

#define DEBUG


bool Drone::calculateOffset()
{
  var.mpu.setXGyroOffset(0);
  var.mpu.setYGyroOffset(0);
  var.mpu.setZGyroOffset(0);
  var.mpu.setXAccelOffset(0);
  var.mpu.setYAccelOffset(0);
  var.mpu.setZAccelOffset(0);

  var.mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  var.mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  
#ifdef DEBUG
  printf("escala acc: %d\r\n",var.mpu.getFullScaleAccelRange());
  printf("escala gyro: %d\r\n",var.mpu.getFullScaleGyroRange());
#endif
  
  delay(100);
  meansensors();
  calibration();

  var.mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);
  var.mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
  
  var.mpu.setXAccelOffset(ax_offset);
  var.mpu.setYAccelOffset(ay_offset);
  var.mpu.setZAccelOffset(az_offset);
}

void Drone::meansensors() {
  int buffersize = 100;
  long int i = 0, buff_ax = 0, buff_ay = 0, buff_az = 0;

  while (i < (buffersize + 101)) {
    // read raw accel/gyro measurements from device
    var.mpu.getMotion6(&var.ax, &var.ay, &var.az, &var.gx, &var.gy, &var.gz);

    if (i > 100 && i <= (buffersize + 100)) { //First 100 measures are discarded
      buff_ax = buff_ax + var.ax;
      buff_ay = buff_ay + var.ay;
      buff_az = buff_az + var.az;
    }
    if (i == (buffersize + 100)) {
      mean_ax = buff_ax / buffersize;
      mean_ay = buff_ay / buffersize;
      mean_az = buff_az / buffersize;
    }
    i++;
    delay(2); //Needed so we don't get repeated measures
  }
#ifdef DEBUG
  printf("mean_ax: %i \r\n",mean_ax);
  printf("mean_ay: %i\r\n",mean_ay);
  printf("mean_az: %i\r\n",mean_az);
#endif
}

void Drone::calibration(){
  uint8_t acel_deadzone = 8;
  //uint8_t giro_deadzone = 1;
  ax_offset=-mean_ax/8;
  ay_offset=-mean_ay/8;
  az_offset=(16384-mean_az)/8;
  while (1){
    int ready=0;
    var.mpu.setXAccelOffset(ax_offset);
    var.mpu.setYAccelOffset(ay_offset);
    var.mpu.setZAccelOffset(az_offset);
    
    meansensors();
 
    if (abs(mean_ax)<=acel_deadzone) ready++;
    else ax_offset=ax_offset-mean_ax/acel_deadzone;
 
    if (abs(mean_ay)<=acel_deadzone) ready++;
    else ay_offset=ay_offset-mean_ay/acel_deadzone;
 
    if (abs(16384-mean_az)<=acel_deadzone) ready++;
    else az_offset=az_offset+(16384-mean_az)/acel_deadzone;
    
    if (ready==3) break;
  }
}
