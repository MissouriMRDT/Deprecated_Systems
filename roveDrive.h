// Missouri Science and Technology Mars Rover Design Team 2015
// Judah Schad jrs6w7@mst.edu
//
// RoveSetupCCS/CCSJs.cfg
//
// initializes Texas Instruments drivers
// configs hardware interface
// get global handles
// begins the scheduler
//
// mrdt::rovWareCCS
#ifndef ROVEDRIVE_H_
#define ROVEDRIVE_H_
#pragma once
//
#ifdef __cplusplus
extern "C" {
#endif


// == RoveBoard_CCS_1294 UNDER DEVELOPEMENT ========
//
// Pin Access and Rtos Post/Pend Interface
#include "RoveWare/RoveBoard.h"

Void roveLoop_DRIVE_RcServoByIp(UArg arg0, UArg arg1);

Void roveLoop_DRIVE_RcServosEstop(UArg arg0);

#ifdef __cplusplus
}
#endif
//
#endif // ROVEDRIVE_H_
