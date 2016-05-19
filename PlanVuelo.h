/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlanVuelo.h
 * Author: extalir
 *
 * Created on February 9, 2016, 1:44 PM
 */

#ifndef PLANVUELO_H
#define PLANVUELO_H

class PlanVuelo {
public:
    PlanVuelo();
    PlanVuelo(double latitud_t,double longitud_t, double altura_t, double velocidad_t, double espera_t);
    PlanVuelo(const PlanVuelo& orig);
    double ObtenerLatitud();
    double ObtenerLongitud();
    double ObtenerAltura();
    double ObtenerVelocidad();
    virtual ~PlanVuelo();
private:
    double latitud;
    double longitud ;
    double altura ;
    double velocidad ;
    double espera ;
    int cuenta;
};

#endif /* PLANVUELO_H */