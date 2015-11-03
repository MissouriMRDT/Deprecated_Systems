// Missouri Science and Technology Mars Rover Design Team 2015
//
// roveDevTemplateThread.c
//
// Using Texas Instruments Code Composer Studio RTOS stack
//
// first created:
//
// 09_01_2015       V1 - URC Horizon IP TCP Client / UART/ PWM Controller Template
//
// Judah Schad jrs6w7@mst.edu
//
// get global handles
// initializes Texas Instruments drivers
// configs hardware interface
// begins the scheduler
//
// Texas Instruments:
//
// SYS/BIOS Kernel
// RTOS operating system
// TIVA RTSC config
//
// instatiates the roveDevTemplate.c as the C interface for a TexInst TIVA TASK Thread
//
// This is found in the tivaRtscJS.cfg Javascript Gui
//
// mrdt::roveWare

#ifndef ROVEDEVICETEMPLATE_THREAD_H_
#define ROVEDEVICETEMPLATE_THREAD_H_

//TI TIVA Mailbox() BIOS software routine support
//#include <ti/sysbios/knl/Mailbox.h>

//TODO wtf TaskSelf Warning?
//#include <ti/ndk/inc/os/osif.h>

//C lib
#include <stdio.h>

//CCS TI operating system
#include <ti/sysbios/knl/Task.h>

//MRDT definitions
#include "roveWare/roveWare_TCPSocket.h"
#include "roveWare/roveWare_NewMemberUtils.h"
#include "roveWare/roveWare_dynamixelWrappers.h"

//Handle to a TivaWare RTOS Private Stack -> See tivaRtscJS.cfg
void roveDeviceTemplateThread(UArg arg0, UArg arg1);

#endif // ROVEDEVICETEMPLATE_THREAD_H_
