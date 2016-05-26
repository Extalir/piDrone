/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServidorTCP.h
 * Author: extalir
 *
 * Created on February 9, 2016, 10:02 AM
 */

#ifndef SERVIDORTCP_H
#define SERVIDORTCP_H

#include <string>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "../PLANVUELO/PlanVuelo.h"
#include "../Variables.h"

using namespace std;
class ServidorTCP 
{
public:
    ServidorTCP();
    ServidorTCP(const ServidorTCP& orig);
    void Configurar(char* ip, int puerto);
    void Configurar(int puerto);
    int Iniciar(Variables *temp);
    int Ejecutar();
    int Leer(int sockfd,char* buffer);
    int LeerLinea(int sockfd,string* buffer);
    int Enviar(int sockfd, char* buffer);
    int Enviar(string datos);
    bool CheckConex();
    void  ObtenerPlanVuelo(PlanVuelo plan);
    virtual ~ServidorTCP();
    
    Variables *var;
private:
    int puerto;
    string ip;
    char buffer[128];
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd, newsockfd, clilen;
    bool clConet;
    void ProsComandos(string buff);
};

#endif /* SERVIDORTCP_H */

