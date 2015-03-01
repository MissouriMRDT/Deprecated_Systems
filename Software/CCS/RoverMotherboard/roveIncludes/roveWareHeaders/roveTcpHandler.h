//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)

// roveTcpHandler.h
//
// first created:
//
// 01_22_2015_Owen_Chiaventone
//
// last edited:
//
//02_24_2015_Judah Schad_jrs6w7@mst.edu

#pragma once

#ifndef ROVETCPHANDLER_H_
#define ROVETCPHANDLER_H_

//includes globally scoped Texas Instruments (TI) header files

#include "../RoverMotherboardMain.h"

//MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

//When data is recieved it goes into the fromBaseStationMailbox as RoveNet recieve struct base_station_msg_struct

//When data is sent it goes into the toBaseStationMailbox mailbox RoveNet send switching on the enum device structs and sizeof()

Void roveTcpHandler(UArg arg0, UArg arg1);

#endif // ROVETCPHANDLER_H_
