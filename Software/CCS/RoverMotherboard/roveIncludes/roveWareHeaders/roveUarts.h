//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)
//
// roveUarts.h
//
// first created:
//
// 04_20_2014_Keenan_Johnson
//
// last edited:
//
//02_25_2015_Judah Schad_jrs6w7@mst.edu

//MRDesign Team:: 	roveWare::		roveCom uart :: constructs and instatiates uarts

#pragma once

#ifndef ROVEUARTS_H_
#define ROVEUARTS_H_

//globally scoped Texas Instruments (TI) header files

#include "../RoverMotherboardMain.h"

//MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

UART_Handle init_uart( UInt uart_index, UInt baud_rate );

#endif // ROVEUARTS_H_
