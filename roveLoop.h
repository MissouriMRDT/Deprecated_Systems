// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#ifndef ROVELOOP_H_
#define ROVELOOP_H_

#ifdef __cplusplus
extern "C" {
#endif

//Rover Cplusplus Wires
#include "roveWires.h"

//Rtos Kernel Module Api
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Semaphore.h>

// wired to the build time allocation for the main Rtos Task Thread in roveBuildRtos.cfg
void roveLoop(UArg arg0, UArg arg1);

#ifdef __cplusplus
}
#endif

#endif // ROVELOOP
