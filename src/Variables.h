/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VariablesGlobales.h
 * Author: extal
 *
 * Created on 6 de febrero de 2016, 22:46
 */

#ifndef VARIABLESGLOBALES_H
#define VARIABLESGLOBALES_H

#include "GPS/GPS.h"
#include "HMC5883L/HMC5883L.h"
#include "PID/PID.h"
#include "PLANVUELO/PlanVuelo.h"
#include "MPU6050/MPU6050.h"

namespace COMM
{
    enum Comandos
    {
        initDrone = 0,
        detDrone = 1,

        calOffsetIMU = 2,

        angPitch_Roll_Yaw = 3,

        velAngPitch_Roll_Yaw = 4,
        velAltitud = 5,

        rPkp = 6,
        rPki = 7,
        rPkd = 8,
        imaxP = 9,
        salMAxP = 10,
        sPkp = 11,

        rRkp = 12,
        rRki = 13,
        rRkd = 14,
        imaxR = 15,
        salMaxR = 16,
        sRkp = 17,

        rYkp = 18,
        rYki = 19,
        rYkd = 20,
        imaxY = 21,
        salMaxY = 22,
        sYkp = 23,

        rAkp = 24,
        rAki = 25,
        rAkd = 26,
        imaxA = 27,
        salMaxA = 28,
        sAkp = 29,

        rVkp = 30,
        rVki = 31,
        rVkd = 32,
        imaxV = 33,
        salMaxV = 34,
        sVkp = 35,

        altActual = 36,
        altActualRel = 37,
        altActualSonar = 38,

        setPointPitch = 39,
        setPointRoll = 40,
        setPointYaw = 41,
        setPointAlt = 42,

        voltaje=43,

        latitud=44,
        longitud=45,
        estGps=46,
        numSatelites=47,
        velGps=48
    };
};
//----------------------EEPROM----------------------------
class Variables
{
public:
    MPU6050 mpu;
    HMC5883L hmc;

    //--------------------Variables Pitch, Roll y Yaw --------------------------

    float unfiltered_gyro_angle[3] = {0, 0, 0};
    float prev_angle[3] = {0, 0, 0};

    float GYRO_FACTOR = 1 / 32.8; //  32.8  gyro rate 1000º/s

    float ACCEL_FACTOR = 1 / 8192; //  8192 acc scale 4g

    int16_t mx, my, mz;

    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    double angle[3] = {0, 0, 0};
    double gyroRate[3] = {0, 0, 0};

    const float RADIANS_TO_DEGREES = 57.2958;
    const float DEG_TO_RAD = 0.01745329252;

    //--------------------Variables Motores ------------------------------------
    uint16_t Motor[4]; // valor PWM para cada uno de los 4 motores
    int throttle = 1060; // aceleracion vertical inicial
    int minThrottle = 1050;
    int maxThrottle = 1800;

    //---------------------Variables PID----------------------------------------
    PIDQuad objPID;
    PIDQuad::var_PID r_PID[5]; // Estructura que contiene los valores con los que trabajara el rate PID de cada eje
    PIDQuad::var_PID s_PID[5]; // Estructura que contiene los valores con los que trabajara el stability PID de cada eje

    double rPitchKp=0.75;
    double rPitchKi=4.1;
    double rPitchKd=0.085;
    int imaxPitch=20;
    int salMAxPitch=250;
    double sPitchKp=1.4;

    double rRollKp=0.75;
    double rRollKi=4.1;
    double rRollKd=0.085;
    int imaxRoll=20;
    int salMaxRoll=250;
    double sRollKp=1.4;

    double rYawKp=3.5;
    double rYawKi=2.5;
    double rYawKd=0.09;
    int imaxYaw=50;
    int salMaxYaw=150;
    double sYawKp=1.2;

    double rAltKp=1;
    double rAltKi=0.25;
    double rAltKd=0;
    int imaxAlt=250;
    int salMaxAlt=300;
    double sAltKp=1.5;

    double rVelKp=0;
    double rVelKi=0;
    double rVelKd=0;
    int imaxVel=0;
    int salMaxVel=0;
    double sVelKp=0;

    //----------------------Variables Barometro---------------------------------
    float realAltitude = 0; // Altitud a nivel del mar
    float currAltitude = 0; // Altitud relativa
    float prevCurrAltitud = 0;
    uint32_t timerBMP; // timer para leer el valor de la presion sin filtrar
    bool resetInitAlt = false; // bandera que indica si se solicito el cambio de la altitud que se tomara como tierra.

    //---------------------- Altitud Hold --------------------------------------
    int throttleAltHold = 0; 
    bool altHold = false; // bandera si se inicio el PID
    bool firstRun = false; // bandera que indica si es el primer ciclo del althold

    //---------------------- Variables Distancia Sonares -----------------------
    unsigned int distSonarUp = 0;
    unsigned int distSonarDown = 0;

    //-----------------------Variables Voltaje----------------------------------
    double valVoltaje = 0;
    double prevValVoltaje = 0;

    // ---------------------Otras Variables-------------------------------------
    bool flight = false; // bandera si se inicio el vuelo

    // ---------------------- Timers -------------------------------------------
    long timerStability; // Para calcular la salida de los PID pitch, roll y yaw cada 10 ms
    long timerAcc; // Para calcular la velocidad vertical
    long timer100hz;
    long timer20hz;
    long timer5hz;
    uint64_t timer;
    
    float estimatedZVelocity = 0.0;
    double velocidad_F = 0, velocidad_I = 0; // velocidad vertical y velocidad vertical previa

    //------------------------Variables GPS ------------------------------------
    GPS gps;
        
        
    float filterSmooth(float currentData, float previousData, float smoothFactor)
    {
      if (smoothFactor != 1.0) //only apply time compensated filter if smoothFactor is applied
      {
        return (previousData * (1.0 - smoothFactor) + (currentData * smoothFactor));
      }
      return currentData; //if smoothFactor == 1.0, do not calculate, just bypass!
    }


    string ToString(double value)
    {
        ostringstream ss;
        string out;
        ss << value;
        out = ss.str();
        return out;
    }
    
    string ToString(int value)
    {
        ostringstream ss;
        string out;
        ss << value;
        out = ss.str();
        return out;
    }
    
    bool is_number(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }
    
    union byteInt
    {
        uint8_t b[sizeof(int)];
        int i;
    };

    union byteFloat
    {
        uint8_t b[sizeof(float)];
        float f;
    };
};
#endif /* VARIABLESGLOBALES_H */

