// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
// instatiates the roveDevice_Thread.c as TI RTOS backed TASK
//
// mrdt::roveWare
#ifndef ROVETHREAD_H_
#define ROVETHREAD_H_

//MRDT definitions
#include "roveWare/roveProtocol.h"
//#include "roveWare/roveCplusWires.h"

//C lib
#include <stdio.h>
//CCS TI operating system
#include <ti/sysbios/knl/Task.h>
//TODO wtf TaskSelf Warning?
//#include <ti/ndk/inc/os/osif.h>
//#include <ti/sysbios/knl/Mailbox.h>
//Handle to a TivaWare RTOS Private Stack -> See tivaRtscJS.cfg

//#include "roveComm.h"
//#include "roveControl.h"

#include <xdc/std.h>

#include <xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>

#include <xdc/cfg/global.h>

void roveThread_TivaTask(UArg arg0 , UArg arg1);

#endif // ROVETHREAD_H_
