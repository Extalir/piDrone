/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drone.cpp
 * Author: extalir
 * 
 * Created on 12 de febrero de 2016, 13:47
 */

#include "Drone.h"


Drone::Drone() {
}

int Drone::InitIMU()
{
    var.hmc.initialize();
    delay(10);

    var.mpu.initialize();
    delay(10);

    if(var.mpu.testConnection()==false)
        return -1;
    
    var.mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);
    var.mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
    var.mpu.setDLPFMode(MPU6050_DLPF_BW_5);

    var.mpu.setXGyroOffset(0);
    var.mpu.setYGyroOffset(0);
    var.mpu.setZGyroOffset(0);
    var.mpu.setXAccelOffset(823);
    var.mpu.setYAccelOffset(1320);
    var.mpu.setZAccelOffset(1249);

    InitPIDs();
    
    //printf("READ_FS_SEL: %u\r\n",READ_FS_SEL);
    //var.calculateOffset(&var.mpu);
    
    for(int i=0;i<400;i++)
    {
        UpdateP_R_Y();
        usleep(1000);
    }
    
    return 0;
}

int Drone::InitPIDs()
{
    // Reinicio de los PID del pitch, rol y yaw
    try
    {
        for (int i = 0; i < 4; i++)
        {
          var.objPID.resetPID(&var.r_PID[i]);
          var.objPID.resetPID(&var.s_PID[i]);
        }

        // Dar valores al pitch en ambos PID
        //objPID.initPID(&r_PID[PITCH], 2.35, 3.05, 0.016, 0, 100, 400);
        //objPID.initPID(&r_PID[PITCH], 0.9, 2.5, 0.015, 0, 50, 500);
        var.objPID.initPID(&var.r_PID[PITCH], var.rPitchKp, var.rPitchKi, var.rPitchKd, 0, var.imaxPitch, var.salMAxPitch);//i0.85
        var.objPID.initPID(&var.s_PID[PITCH], var.sPitchKp, 0, 0, 0, 0, 100);

        // Dar valores al roll en ambos PID
        //objPID.initPID(&r_PID[ROLL], 2.35, 3.05, 0.016, 0, 100, 400);
        //objPID.initPID(&r_PID[ROLL], 0.9, 2.5, 0.015, 0, 50, 500);
        var.objPID.initPID(&var.r_PID[ROLL], var.rRollKp, var.rRollKi, var.rRollKd, 0, var.imaxRoll, var.salMaxRoll);//i0.85
        var.objPID.initPID(&var.s_PID[ROLL], var.sRollKp, 0, 0, 0, 0, 100);

        // Dar valores al yaw en ambos PID
        //objPID.initPID(&r_PID[YAW], 1.25, 2.5, 0, 0, 20, 50);
        //objPID.initPID(&r_PID[YAW], 4, 1.4, 0.025, 0, 50, 100);
        var.objPID.initPID(&var.r_PID[YAW],var.rYawKp, var.rYawKi, var.rYawKd, 0, var.imaxYaw, var.salMaxYaw);
        var.objPID.initPID(&var.s_PID[YAW], var.sYawKp, 0, 0, 0, 0, 90);

        // Dar valores al alt. hold en ambos PID
        var.objPID.initPID(&var.r_PID[ALT], var.rAltKp, var.rAltKi, var.rAltKd, 0, var.imaxAlt, var.salMaxAlt);
        var.objPID.initPID(&var.s_PID[ALT], var.sAltKp, 0, 0, 0, 0, 1.5);

        // Dar valores al navegation en ambos PID
        var.objPID.initPID(&var.r_PID[NAV], var.rVelKp, var.rVelKi, var.rVelKd, 0, var.imaxVel, var.salMaxVel);
        var.objPID.initPID(&var.s_PID[NAV], var.sVelKp, 0, 0, 0, 100, 1.5);
    }
    catch(int e)
    {
        printf("Error No. %i al Iniciar PIDs \r\n",e);
    }
    return 0;
}

int Drone::InitGPS(char* _port, int baud)
{
    var.gps.Conectar(_port,baud);
}

void Drone::CalAltVel()
{
}

void Drone::CalNavVel()
{
}

void Drone::CalPIDs()
{
    if(millis()-var.timer100hz>=10)
    {
        var.objPID.CalculatePID(&var.s_PID[PITCH], var.s_PID[PITCH].setPoint, var.angle[PITCH]);
        var.objPID.CalculatePID(&var.r_PID[PITCH], var.s_PID[PITCH].outPut, var.gyroRate[PITCH]);

        var.objPID.CalculatePID(&var.s_PID[ROLL], var.s_PID[ROLL].setPoint, var.angle[ROLL]);
        var.objPID.CalculatePID(&var.r_PID[ROLL], var.s_PID[ROLL].outPut, var.gyroRate[ROLL]);

        var.objPID.CalculatePID(&var.s_PID[YAW], var.s_PID[YAW].setPoint, var.angle[YAW]);
        var.objPID.CalculatePID(&var.r_PID[YAW], var.s_PID[YAW].outPut, var.gyroRate[YAW]);
        var.timer100hz=millis();
    }
}

void Drone::UpdateP_R_Y()
{
    var.mpu.getMotion6(&var.ax, &var.ay, &var.az, &var.gx, &var.gy, &var.gz);
    
    if(var.ax==0 && var.ay==0 && var.az==0 && var.gx==0 && var.gy==0 && var.gz==0)
        var.mpu.getMotion6(&var.ax, &var.ay, &var.az, &var.gx, &var.gy, &var.gz);
    
    /*
    printf("ax: %i\r\n",var.ax);
    printf("ay: %i\r\n",var.ay);
    printf("az: %i\r\n",var.az);

    printf("gx: %i\r\n",var.gx);
    printf("gy: %i\r\n",var.gy);
    printf("gz: %i\r\n",var.gz);
*/
     
    // Remove offsets and scale gyro data
    double gyroRate_X = var.gx  * var.GYRO_FACTOR;
    double gyroRate_Y = var.gy  * var.GYRO_FACTOR;
    double gyroRate_Z = var.gz  * var.GYRO_FACTOR;

    var.gyroRate[ROLL] = gyroRate_X ;
    var.gyroRate[PITCH] = gyroRate_Y * -1;
    var.gyroRate[YAW] = gyroRate_Z * -1;

    double accel_angle_y = atan(-1 * var.ax / sqrt(pow(var.ay, 2) + pow(var.az, 2))) * var.RADIANS_TO_DEGREES;
    double accel_angle_x = atan(var.ay / sqrt(pow(var.ax, 2) + pow(var.az, 2))) * var.RADIANS_TO_DEGREES;
    double accel_angle_z = 0;

    double dt = (double)(micros() - var.timer) / 1000000; // Calculate delta time
    var.timer = micros();

    double gyro_angle_x = gyroRate_X * dt + var.prev_angle[ROLL];
    double gyro_angle_y = gyroRate_Y * dt + var.prev_angle[PITCH];
    //double gyro_angle_z = gyroRate_Z * dt + prev_angle[YAW];

    // Compute the drifting gyro angles
    var.unfiltered_gyro_angle[X] = gyroRate_X * dt + var.unfiltered_gyro_angle[X];
    var.unfiltered_gyro_angle[Y] = gyroRate_Y * dt + var.unfiltered_gyro_angle[Y];
    var.unfiltered_gyro_angle[Z] = gyroRate_Z * dt + var.unfiltered_gyro_angle[Z];

    // Apply the complementary filter to figure out the change in angle - choice of alpha is
    // estimated now.  Alpha depends on the sampling rate...
    const double alpha = 0.96;
    var.prev_angle[ROLL] = alpha * gyro_angle_x + (1.0 - alpha) * accel_angle_x;
    var.prev_angle[PITCH] = alpha * gyro_angle_y + (1.0 - alpha) * accel_angle_y;
    //prev_angle[YAW] = gyro_angle_z;  //Accelerometer doesn't give z-angle

    var.angle[ROLL] = var.prev_angle[ROLL];
    var.angle[PITCH] = var.prev_angle[PITCH] * -1;

   
    var.hmc.getHeading(&var.mx, &var.my, &var.mz);

    double rollAngle = var.angle[ROLL] * var.DEG_TO_RAD;
    double pitchAngle = var.angle[PITCH] * var.DEG_TO_RAD;

    double Bfy = var.mz * sin(rollAngle) - var.my * cos(rollAngle);
    double Bfx = var.mx * cos(pitchAngle) + var.my * sin(pitchAngle) * sin(rollAngle) + var.mz * sin(pitchAngle) * cos(rollAngle);
    var.angle[YAW] = atan2(-Bfy, Bfx) * var.RADIANS_TO_DEGREES;
    var.angle[YAW] = var.filterSmooth(var.angle[YAW], var.prev_angle[YAW], 0.2);
    var.prev_angle[YAW] = var.angle[YAW];
  
    /*
    printf("Angulo Pitch: %f \r\n",var.angle[PITCH]);
    printf("Angulo Roll: %f \r\n",var.angle[ROLL]);
    printf("Angulo Yaw: %f \r\n",var.angle[YAW]);
    */
    
    if(servidor.CheckConex()==true)
    { 
        string strSend;
        /*
        string send="Pitch:"+var.ToString(var.angle[PITCH])+",";
        send+="Roll:"+var.ToString(var.angle[ROLL])+",";
        send+="Yaw:"+var.ToString(var.angle[YAW])+"\r\n";
         * */
       // string strKp=var.ToString(var.rAltKd)+"\r\n";
        //servidor.Enviar(strKp);
        /*
        strSend="";
        strSend+=var.ToString(COMM::angPitch_Roll_Yaw)+",";
        strSend+=var.ToString((int)var.angle[PITCH] * 100)+",";
        strSend+=var.ToString((int)var.angle[ROLL] * 100)+",";
        strSend+=var.ToString((int)var.angle[YAW] * 100)+"\n";
        servidor.Enviar(strSend);
         * */
    }
}

void Drone::UpdateMotors()
{
    var.Motor[0] = var.throttle + var.r_PID[PITCH].outPut + var.r_PID[ROLL].outPut + var.r_PID[YAW].outPut;
    var.Motor[1] = var.throttle + var.r_PID[PITCH].outPut - var.r_PID[ROLL].outPut - var.r_PID[YAW].outPut;
    var.Motor[2] = var.throttle - var.r_PID[PITCH].outPut - var.r_PID[ROLL].outPut + var.r_PID[YAW].outPut;
    var.Motor[3] = var.throttle - var.r_PID[PITCH].outPut + var.r_PID[ROLL].outPut - var.r_PID[YAW].outPut;
    
    uint8_t buff_motor[8];
    buff_motor[0] = (var.Motor[0] & 0xff00) >> 8;
    buff_motor[1] = (var.Motor[0] & 0x00ff);
    buff_motor[2] = (var.Motor[1] & 0xff00) >> 8;
    buff_motor[3] = (var.Motor[1] & 0x00ff);
    buff_motor[4] = (var.Motor[2] & 0xff00) >> 8;
    buff_motor[5] = (var.Motor[2] & 0x00ff);
    buff_motor[6] = (var.Motor[3] & 0xff00) >> 8;
    buff_motor[7] = (var.Motor[3] & 0x00ff);
    
    //I2Cdev::writeBytes(0x10,sizeof(buff_motor),buff_motor);
}

int Drone::Loop()
{
    var.timer100hz=millis();
    var.timer20hz=millis();
    var.timer=micros();
    while(1)
    {
        Loop100hz();
        Loop30hz();
        loop20hz();
        CalNavVel();
        usleep(1000);
    }
}

void Drone::Loop100hz()
{
    if((millis()-var.timer100hz) >= 10)
    {
        UpdateP_R_Y();
        CalAltVel();
        CalPIDs();
        UpdateMotors();
        var.timer100hz=millis();
    }
}

void Drone::Loop30hz()
{
}

void Drone::loop20hz()
{
}

Drone::Drone(const Drone& orig) {
}

Drone::~Drone() {
}