/*
 * roveMotorControlTester.h
 *
 *  Created on: Mar 25, 2015
 *      Author: mrdtdev
 */

#ifndef ROVEMOTORCONTROLTESTER_H_
#define ROVEMOTORCONTROLTESTER_H_

//globally scoped Texas Instruments (TI) headers

#include "../RoverMotherboardMain.h"

//MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

//MRDesign Team::roveHardwareAbstraction::		GPIO and RS485 jack access

#include "roveHardwareAbstraction.h"

Void roveMotorControlTester(UArg arg0, UArg arg1);

#endif /* ROVEMOTORCONTROLTESTER_H_ */
