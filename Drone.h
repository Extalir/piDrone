/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drone.h
 * Author: extalir
 *
 * Created on 12 de febrero de 2016, 13:47
 */

#ifndef DRONE_H
#define DRONE_H

#include <unistd.h>
#include <stdio.h>
#include <string>

#include "ServidorTCP.h"

#define PITCH 0
#define ROLL 1
#define YAW 2
#define ALT 3
#define NAV 4

#define X 0
#define Y 1
#define Z 2

using namespace std;
class Drone
{
public:
    Drone();
    // Inicializar Acelerometro, giroscopio, magnometro y barometro.
    int InitIMU();
    // Inicializar las ganancias de los PID.
    int InitPIDs();
    // Configurar e iniciar comunicacion con gps.
    int InitGPS(char *_port,int baud);
    // Calcular la velocidad vertical.
    void CalAltVel();
    // Calcular la velocidad de navegacion.
    void CalNavVel();
    // Calcular la salida de los PID.
    void CalPIDs();
    // Calcular la posicion de pitch, roll y yaw.
    void UpdateP_R_Y();
    
    void UpdateMotors();
    // Ejecutar todo.
    int Loop();
    
    void Loop100hz();
    void Loop30hz();
    void loop20hz();
    
    bool calculateOffset();
    void meansensors();
    void calibration();
    
    Drone(const Drone& orig);
    virtual ~Drone();
    
    Variables var;
    ServidorTCP servidor;
private:
    long int mean_ax, mean_ay, mean_az, mean_gx, mean_gy, mean_gz, state = 0;
    int ax_offset, ay_offset, az_offset, gx_offset, gy_offset, gz_offset;
};

#endif /* DRONE_H */