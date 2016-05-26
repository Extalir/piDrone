/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: extalir
 *
 * Created on 19 de febrero de 2016, 7:44
 */

#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

#include "Drone.h"

using namespace std;

Drone drone;
int contThread=0;

string ToString(double value)
{
    ostringstream ss;
    string out;
    ss << value;
    out = ss.str();
    return out;
}

void *Servidor_T(void *obj)
{
    drone.servidor.Ejecutar();
    pthread_exit(NULL);
}

void *Control_T(void *id)
{
    drone.Loop();
    pthread_exit(NULL);
}

int IniDrone(Drone *drone)
{
    if(drone->InitIMU()!=0)
        return -1;
    if(drone->InitPIDs()!=0)
        return -2;
    //if(drone->InitGPS("/dev/ttyUSB0",B38400)!=0)
      //  return -3;
    return 0;
}

int main(int argc, char** argv) 
{
    pthread_t tServidor;
    pthread_t tDrone;
    int initSta=0;
    
    initSta=IniDrone(&drone);
    
    if(initSta>=0)
    {
        pthread_create(&tDrone,NULL,Control_T,(void *)1);
        pthread_create(&tServidor,NULL,Servidor_T,(void *)2);
    
        drone.servidor.Configurar(5555);
        drone.servidor.Iniciar(&drone.var);
        usleep(1000);
        pthread_join(tServidor,NULL);
        usleep(1000);
        pthread_join(tDrone,NULL);
    }
    else
    {
        switch(initSta)
        {
            case -1:
                printf("Error al iniciar IMU\r\n");
                break;
            case -2:
                printf("Error al configurar PIDs\r\n");
                break;
            case -3:
                printf("Error al correr el drone\r\n");
        }
    }
    printf("Terminando programa \r\n");
    //PlanVuelo plan(1,2,3,4,5);
    return 0;
}