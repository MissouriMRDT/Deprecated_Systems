// roveUarts.h MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad jrs6w7@mst.edu

#pragma once

#ifndef ROVEUARTS_H_
#define ROVEUARTS_H_

//globally scoped Texas Instruments (TI) header files

#include "../RoverMotherboardMain.h"

//MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

UART_Handle init_uart(UInt uart_index, UInt baud_rate);

#endif // ROVEUARTS_H_
