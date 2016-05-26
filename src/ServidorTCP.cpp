/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServidorTCP.cpp
 * Author: extalir
 * 
 * Created on February 9, 2016, 10:02 AM
 */

#include <stdlib.h>

#include "ServidorTCP.h"
#include "../DRONE/Drone.h"

std::vector<std::string> split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void ServidorTCP::ProsComandos(string buff)
{
    vector<string> valores;
    int op;
    string strSend="";
    int temp;
    valores=split(buff,',');
    const char* num=valores[0].c_str();
    op=static_cast<unsigned int>(*num);
    //op=atoi(valores[0].c_str());
    switch(op)
    {                           
        case COMM::initDrone:
            var->flight=true;
            break;
            
        case COMM::detDrone:
            var->flight=false;
            break;
            
            
        case COMM::calOffsetIMU:
            break;
            
        case COMM::angPitch_Roll_Yaw:
            strSend="";
            strSend+=var->ToString(COMM::angPitch_Roll_Yaw)+",";
            strSend+=var->ToString((int)var->angle[PITCH] * 100)+",";
            strSend+=var->ToString((int)var->angle[ROLL] * 100)+",";
            strSend+=var->ToString((int)var->angle[YAW] * 100)+"\n";
            Enviar(strSend);
            break;
            
            
        case COMM::velAngPitch_Roll_Yaw:
            strSend="";
            strSend+=var->ToString(COMM::velAngPitch_Roll_Yaw)+",";
            strSend+=var->ToString((int)var->gyroRate[PITCH] * 100)+",";
            strSend+=var->ToString((int)var->gyroRate[ROLL] * 100)+",";
            strSend+=var->ToString((int)var->gyroRate[YAW] * 100)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::velAltitud:
            break;
            
            
        case COMM::altActual:
            break;
            
        case COMM::altActualRel:
            break;
            
        case COMM::altActualSonar:
            break;
                            
        case COMM::rAkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rAltKp=atof(valores[1].c_str());
            temp=(var->rAltKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rAkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            cout<<"enviando: "<<strSend<<"\r\n";
            break;
            
        case COMM::rAki:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rAltKi=atof(valores[1].c_str());
            temp=(var->rAltKi+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rAki)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rAkd:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rAltKd=atof(valores[1].c_str());
            temp=(var->rAltKd+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rAkd)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::sAkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->sAltKp=atof(valores[1].c_str());
            temp=(var->sAltKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::sAkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::imaxA:
            if(valores.capacity()>1 && valores[1]!="$")
                var->imaxAlt=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::imaxA)+",";
            strSend+=var->ToString(var->imaxAlt)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::salMaxA:
            if(valores.capacity()>1 && valores[1]!="$")
                var->salMaxAlt=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::salMaxA)+",";
            strSend+=var->ToString(var->salMaxAlt)+"\n";
            Enviar(strSend);
            break;
            
            
        case COMM::rPkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rPitchKp=atof(valores[1].c_str());
            temp = (var->rPitchKp + 0.001) * 100;
            strSend.erase(0,strSend.size());
            strSend+=var->ToString(COMM::rPkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rPki:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rPitchKi=atof(valores[1].c_str());
            temp=(var->rPitchKi+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rPki)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rPkd:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rPitchKd=atof(valores[1].c_str());
            temp=(var->rPitchKd+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rPkd)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::sPkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rPitchKp=atof(valores[1].c_str());
            temp=(var->sPitchKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::sPkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::imaxP:
            if(valores.capacity()>1 && valores[1]!="$")
                var->imaxPitch=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::imaxP)+",";
            strSend+=var->ToString(var->imaxPitch)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::salMAxP:
            if(valores.capacity()>1 && valores[1]!="$")
                var->salMAxPitch=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::salMAxP)+",";
            strSend+=var->ToString(var->salMAxPitch)+"\n";
            Enviar(strSend);
            break;
            
            
        case COMM::rRkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rRollKp=atof(valores[1].c_str());
            temp=(var->rRollKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rRkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rRki:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rRollKi=atof(valores[1].c_str());
            temp=(var->rRollKi+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rRki)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rRkd:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rRollKd=atof(valores[1].c_str());
            temp=(var->rRollKd+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rRkd)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::sRkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->sRollKp=atof(valores[1].c_str());
            temp=(var->sRollKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::sRkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::imaxR:
            if(valores.capacity()>1 && valores[1]!="$")
                var->imaxRoll=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::imaxR)+",";
            strSend+=var->ToString(var->imaxRoll)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::salMaxR:
            if(valores.capacity()>1 && valores[1]!="$")
                var->salMaxRoll=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::salMaxR)+",";
            strSend+=var->ToString(var->salMaxRoll)+"\n";
            Enviar(strSend);
            break;   
            
            
        case COMM::rYkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rYawKp=atof(valores[1].c_str());
            temp=(var->rYawKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rYkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rYki:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rYawKi=atof(valores[1].c_str());
            temp=(var->rYawKi+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rYki)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rYkd:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rYawKd=atof(valores[1].c_str());
            temp=(var->rYawKd+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rYkd)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::sYkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->sYawKp=atof(valores[1].c_str());
            temp=(var->sYawKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::sYkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::imaxY:
            if(valores.capacity()>1 && valores[1]!="$")
                var->imaxYaw=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::imaxY)+",";
            strSend+=var->ToString(var->imaxYaw)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::salMaxY:
            if(valores.capacity()>1 && valores[1]!="$")
                var->salMaxYaw=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::salMaxY)+",";
            strSend+=var->ToString(var->salMaxYaw)+"\n";
            Enviar(strSend);
            break;
            
            
        case COMM::rVkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rVelKp=atof(valores[1].c_str());
            temp=(var->rVelKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rVkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rVki:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rVelKi=atof(valores[1].c_str());
            temp=(var->rVelKi+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rVki)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::rVkd:
            if(valores.capacity()>1 && valores[1]!="$")
                var->rVelKd=atof(valores[1].c_str());
            temp=(var->rVelKd+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::rVkd)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::sVkp:
            if(valores.capacity()>1 && valores[1]!="$")
                var->sVelKp=atof(valores[1].c_str());
            temp=(var->sVelKp+0.001)*100;
            strSend="";
            strSend+=var->ToString(COMM::sVkp)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::imaxV:
            if(valores.capacity()>1 && valores[1]!="$")
                var->imaxVel=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::imaxV)+",";
            strSend+=var->ToString(var->imaxVel)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::salMaxV:
            if(valores.capacity()>1 && valores[1]!="$")
                var->salMaxVel=atof(valores[1].c_str());
            strSend="";
            strSend+=var->ToString(COMM::salMaxV)+",";
            strSend+=var->ToString(var->salMaxVel)+"\n";
            Enviar(strSend);
            break;
            
            
        case COMM::setPointAlt:
            if(valores.capacity()>1 && valores[1]!="$")
                var->s_PID[ALT].setPoint=atof(valores[1].c_str());
            temp=var->s_PID[ALT].setPoint*100;
            strSend="";
            strSend+=var->ToString(COMM::setPointAlt)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::setPointPitch:
            if(valores.capacity()>1 && valores[1]!="$")
                var->s_PID[PITCH].setPoint=atof(valores[1].c_str());
            temp=var->s_PID[PITCH].setPoint*100;
            strSend="";
            strSend+=var->ToString(COMM::setPointPitch)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::setPointRoll:
            if(valores.capacity()>1 && valores[1]!="$")
                var->s_PID[ROLL].setPoint=atof(valores[1].c_str());
            temp=var->s_PID[ROLL].setPoint*100;
            strSend="";
            strSend+=var->ToString(COMM::setPointRoll)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
            
        case COMM::setPointYaw:
            if(valores.capacity()>1 && valores[1]!="$")
                var->s_PID[YAW].setPoint=atof(valores[1].c_str());
            temp=var->s_PID[YAW].setPoint*100;
            strSend="";
            strSend+=var->ToString(COMM::setPointYaw)+",";
            strSend+=var->ToString(temp)+"\n";
            Enviar(strSend);
            break;
        default:
            cout<<"Comando desconocido: "<<valores[0].c_str()<<"\r\n";
            break;
    }
}

ServidorTCP::ServidorTCP() 
{
    puerto=0;
    ip="";
    memset(buffer,'0',sizeof(buffer));
    sockfd=0,newsockfd=0,clilen=0;
    clConet=false;
}

void ServidorTCP::Configurar(char* ip, int puerto_t)
{
    bzero((char *) &serv_addr.sin_zero, sizeof(serv_addr.sin_zero));
    puerto=puerto_t;
    serv_addr.sin_family = inet_addr(ip);
    serv_addr.sin_port = htons( puerto );
}

void ServidorTCP::Configurar(int puerto)
{
    bzero((char *) &serv_addr.sin_zero, sizeof(serv_addr.sin_zero));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( puerto );
}

int ServidorTCP::Iniciar(Variables *temp)
{
    var=temp;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
    {
        perror(const_cast<char *>("ERROR opening socket"));
        return -1;
    }
    if(serv_addr.sin_port==0)
    {
        perror(const_cast<char *>("ERROR Puerto no configurado"));
        return -1;
    }
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
       perror( const_cast<char *>( "ERROR on binding" ) );
       return -1;
    }
    listen(sockfd,2);
}

int ServidorTCP::Ejecutar()
{
    int data=0;
    string _buff="";
     while ( 1 ) 
     {
        printf( "Esperando por cliente... \r\n" );
        clilen = sizeof(cli_addr);
        if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
        {
            perror( const_cast<char *>("ERROR on accept") );
            return -1;
        }
        printf( "Nuevo comunicacion para cliente \r\n" );
        clConet=true;
        while ( 1 ) 
        {
             data=LeerLinea(newsockfd, &_buff);
             if(data<=0)
             {
                 close( newsockfd );
                 break;
             }
             cout<<"leido: "<<_buff<<"\r\n";
             ProsComandos(_buff);
             _buff.clear();
        }
        close( newsockfd );
        clConet=false;
    }
}

int ServidorTCP::Leer(int sockfd,char* _buffer)
{
    int n=0;
    while ( (n = read(sockfd,_buffer,1024) ) < 0 )
    {
      perror(const_cast<char *>( "ERROR reading from socket"));
      return -1;
    }
    _buffer[n] = '\0';
  
  return n;
}

int ServidorTCP::LeerLinea(int sockfd,string* _buffer)
{
    int n=0;
    int cont=0;
    char b[128]={0};
    while ( b[0]!='$')
    {
        try
        {
            n = recv(sockfd,b,128,0);
            if(n<0)
            {
                perror(const_cast<char *>( "ERROR reading from socket"));
                return -1;
            }
            _buffer->append(b);
            if(_buffer->find('$')>0)
                break;
            /*
            if(b[0]!='$'&& b[0]!='"')
            {
                if(cont>1024)
                    cont=0;
                buffer[cont++]=*b;
            }
             * */
        }
        catch(int e){
            cout<<"Error al leer \r\n";
        }
    }
    //_buffer[cont] = '\0';
  return n;
}

int ServidorTCP::Enviar(int sockfd, char* _buffer)
{
    int n;
    try
    {
        if ( (n = send( sockfd, _buffer, strlen(_buffer),0 ) ) < 0 )
        {
            perror(const_cast<char *>( "ERROR writing to socket"));
            return -1;
        }
    }
    catch(int e){
        cout<<"Error al escribir \r\n";
    }
    //_buffer[n] = '\0';
}

int ServidorTCP::Enviar(string datos)
{
    char *temp=&datos[0];
    return Enviar(newsockfd,temp);
}

bool ServidorTCP::CheckConex()
{
    return clConet;
}

void ServidorTCP::ObtenerPlanVuelo(PlanVuelo plan)
{
}

ServidorTCP::ServidorTCP(const ServidorTCP& orig) 
{
}

ServidorTCP::~ServidorTCP()
{
    close(sockfd);
    close(newsockfd);
    close(clilen);
}

