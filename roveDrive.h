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

#ifdef __cplusplus
extern "C" {
#endif

// == RoveBoard_CCS_1294 UNDER DEVELOPEMENT ========
//
// Pin Access and Rtos Post/Pend Interface
#include "RoveBoard/RoveBoard.h"

// == RoveWare2016 UNDER DEVELOPEMENT =========
//
#include "../RoveWare/RoveComm.h"
#include "../RoveWare/RoveCntrl.h"
#include "../RoveWare/RoveLoopSchedule.h"

/* Todo
void roveBoard_EK_TM4C1294XL_Open()
{
    // TI board driver routines
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();
    EK_TM4C1294XL_initWatchdog();
}//end fnctn*/

#ifdef __cplusplus
}
#endif

#endif // ROVEDRIVE_H_
