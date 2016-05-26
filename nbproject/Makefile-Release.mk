#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Librerias/BMP085/BMP085.o \
	${OBJECTDIR}/Librerias/HMC5883L/HMC5883L.o \
	${OBJECTDIR}/Librerias/I2C/I2Cdev.o \
	${OBJECTDIR}/Librerias/MPU6050/MPU6050.o \
	${OBJECTDIR}/src/Drone.o \
	${OBJECTDIR}/src/GPS.o \
	${OBJECTDIR}/src/OFFSET.o \
	${OBJECTDIR}/src/PID.o \
	${OBJECTDIR}/src/PlanVuelo.o \
	${OBJECTDIR}/src/Serial.o \
	${OBJECTDIR}/src/ServidorTCP.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raspidrone

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raspidrone: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raspidrone ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Librerias/BMP085/BMP085.o: Librerias/BMP085/BMP085.cpp 
	${MKDIR} -p ${OBJECTDIR}/Librerias/BMP085
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Librerias/BMP085/BMP085.o Librerias/BMP085/BMP085.cpp

${OBJECTDIR}/Librerias/HMC5883L/HMC5883L.o: Librerias/HMC5883L/HMC5883L.cpp 
	${MKDIR} -p ${OBJECTDIR}/Librerias/HMC5883L
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Librerias/HMC5883L/HMC5883L.o Librerias/HMC5883L/HMC5883L.cpp

${OBJECTDIR}/Librerias/I2C/I2Cdev.o: Librerias/I2C/I2Cdev.cpp 
	${MKDIR} -p ${OBJECTDIR}/Librerias/I2C
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Librerias/I2C/I2Cdev.o Librerias/I2C/I2Cdev.cpp

${OBJECTDIR}/Librerias/MPU6050/MPU6050.o: Librerias/MPU6050/MPU6050.cpp 
	${MKDIR} -p ${OBJECTDIR}/Librerias/MPU6050
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Librerias/MPU6050/MPU6050.o Librerias/MPU6050/MPU6050.cpp

${OBJECTDIR}/src/Drone.o: src/Drone.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Drone.o src/Drone.cpp

${OBJECTDIR}/src/GPS.o: src/GPS.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GPS.o src/GPS.cpp

${OBJECTDIR}/src/OFFSET.o: src/OFFSET.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OFFSET.o src/OFFSET.cpp

${OBJECTDIR}/src/PID.o: src/PID.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PID.o src/PID.cpp

${OBJECTDIR}/src/PlanVuelo.o: src/PlanVuelo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/PlanVuelo.o src/PlanVuelo.cpp

${OBJECTDIR}/src/Serial.o: src/Serial.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Serial.o src/Serial.cpp

${OBJECTDIR}/src/ServidorTCP.o: src/ServidorTCP.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ServidorTCP.o src/ServidorTCP.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raspidrone

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
