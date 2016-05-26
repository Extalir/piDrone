/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlanVuelo.cpp
 * Author: extalir
 * 
 * Created on February 9, 2016, 1:44 PM
 */

#include "PlanVuelo.h"

PlanVuelo::PlanVuelo() {
}
PlanVuelo::PlanVuelo(double latitud_t, double longitud_t, double altura_t, double velocidad_t, double espera_t)
{
    latitud=latitud_t;
    longitud=longitud_t;
    altura=altura_t;
    velocidad=velocidad_t;
    espera=espera_t;
}
double PlanVuelo::ObtenerAltura()
{
    return altura;
}
double PlanVuelo::ObtenerLatitud()
{
    return latitud;
}
double PlanVuelo::ObtenerLongitud()
{
    return longitud;
}
double PlanVuelo::ObtenerVelocidad()
{
    return velocidad;
}
PlanVuelo::PlanVuelo(const PlanVuelo& orig) {
}

PlanVuelo::~PlanVuelo() {
}

