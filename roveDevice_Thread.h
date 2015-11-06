// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveDevice_Thread.c
//
// jrs6w7@mst.edu
//
// instatiates the roveDevice_Thread.c as TI RTOS backed TASK
//
// mrdt::roveWare

#ifndef ROVEDEVICE_THREAD_H_
#define ROVEDEVICE_THREAD_H_

//C lib
#include <stdio.h>

//CCS TI operating system
#include <ti/sysbios/knl/Task.h>
//#include <ti/sysbios/knl/Mailbox.h>

//TODO wtf TaskSelf Warning?
//#include <ti/ndk/inc/os/osif.h>

//MRDT definitions
//#include "roveWare/roveWare_TCPSocket.h"
#include "roveWare/roveWare_UDPSocket.h"

#include "roveWare/roveWare_CntrlUtils.h"

//Handle to a TivaWare RTOS Private Stack -> See tivaRtscJS.cfg
void roveDeviceThread(UArg arg0, UArg arg1);

#endif // ROVEDEVICE_THREAD_H_
