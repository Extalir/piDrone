/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GPS.cpp
 * Author: extalir
 * 
 * Created on 16 de febrero de 2016, 9:07
 */

#include "../DRONE/Drone.h"

GPS::GPS() 
{
}
int GPS::Conectar(char *puerto, int baud)
{
    serial.Setup(puerto,baud);
}

GPS::GPS(const GPS& orig) 
{
}

GPS::~GPS() 
{
}

