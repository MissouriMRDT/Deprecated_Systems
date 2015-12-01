// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
// instatiates the roveDevice_Thread.c as TI RTOS backed TASK
//
// mrdt::roveWare
#ifndef ROVETHREAD_H_
#define ROVETHREAD_H_

//MRDT definitions
#include "roveWare/roveComm.h"
#include "roveWare/roveControl.h"
#include "roveWare/roveProtocol.h"

enum RoveThreadShorthand {
    FOREVER = 0x01
};//end enum

//C lib
#include <stdio.h>
//CCS TI operating system
#include <ti/sysbios/knl/Task.h>

//TODO wtf TaskSelf Warning?
//#include <ti/ndk/inc/os/osif.h>
//#include <ti/sysbios/knl/Mailbox.h>
//Handle to a TivaWare RTOS Private Stack -> See tivaRtscJS.cfg

void roveThread(UArg arg0 , UArg arg1);//end fnctn

#endif // ROVETHREAD_H_
