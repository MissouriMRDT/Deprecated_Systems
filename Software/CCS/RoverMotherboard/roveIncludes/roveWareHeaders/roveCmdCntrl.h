//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)
//
// roveCmdCtrl.h
//
// first created:
//
// 01_22_2015_Owen_Chiaventone
//
// last edited:
//
//02_24_2015_Judah Schad_jrs6w7@mst.edu

//	this implements a single function BIOS thread that acts as the RoverMotherboard.cfg roveCmdCtrlTask handle
//
//	recieves roveTCPHandler commands in roveCom using Mailbox.from obj and
//
//	sends roveTelemCntrl Requests for device telemetry in roveCom using using Mailbox.to obj

#ifndef ROVECMDCNTRL_H_
#define ROVECMDCNTRL_H_

//globally scoped Texas Instruments (TI) headers

#include "../RoverMotherboardMain.h"

//MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

#include "roveHardwareAbstraction.h"

//When data is recieved it comes from fromBaseStationMailbox as RoveNet recieve struct base_station_msg_struct

//When data is sent it goes into the TODO

Void roveCmdCntrl(UArg arg0, UArg arg1);

#endif //ROVECMDCNTRL_H_
