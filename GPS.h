/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GPS.h
 * Author: extalir
 *
 * Created on 16 de febrero de 2016, 9:07
 */

#ifndef GPS_H
#define GPS_H

#include <string>
#include <math.h>
#include <vector>
#include "Serial.h"

using namespace std;

class GPS 
{
public:
    GPS();
    GPS(const GPS& orig);
    
    int Conectar(char *_port,int baud);
    int Desconectar();
    
    int ProscDatos(string datos);
    void *Ejecutar(void*);
    
    double A_Radianes(double val);
    double A_Grados(double val);
    
    double DistanciaPaP(double lat1,double long1,double lat2, double long2);
    double DireccionPaP(double lat1,double long1,double lat2, double long2);
    
    double obtenerLatitud();
    double obtenerLongitud();
    double obtenerAltitud();
    double obtenerFecha();
    double obtenerVelocidad();
    double obtenerEstadoGps();
    double obtenerVelocidadLatitud();
    double obtenerVelocidadLongitud();
    
    void VelGPvS(double lat1,double long1,double lat2, double long2);

    struct DatosGPS ObtenerDatosGPS();
    struct Coordenada
    {
        double latitud;
        double longitud;

    };
    virtual ~GPS();
private:
    struct DatosGPS
    {
        double latitud, longitud, altitud, velocidad;
        string fecha;
        int numSatelites=0;
        static int estadoGps;
    };
    bool signoLat, signoLong;

    double prevLat=0, prevLong=0;
    double prevLatVel=0,prevLongVel=0;
    double velLatitud=0,velLongitud=0;

    vector<Coordenada> listaCoordenadas;
    static Coordenada punto;
    
    Serial serial;
};

#endif /* GPS_H */