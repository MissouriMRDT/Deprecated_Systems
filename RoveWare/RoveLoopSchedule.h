// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifndef ROVELOOPSCHEDULE_H_
#define ROVELOOPSCHEDULE_H_
#pragma once

//=== RoveLoop_CCSBios_RtosSchedule ========
//
// rtos hooks are scheduled by implicit config priority/ interrupt_vector
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
//#include <ti/sysbios/knl/Clock.h>
//
// rtos hooks are scheduled by explicit runtime post/pend
//#include <ti/sysbios/knl/Swi.h>
//#include <ti/sysbios/knl/Mailbox.h>
//#include <ti/sysbios/knl/Semaphore.h>

// == Texas Inst Loop Forever at Rtos Priority Schedule ========
//
// Interface between RoveWare LoopForever and TexasIntrmnts RtosTask schedule
typedef ti_sysbios_knl_Task_FuncPtr roveLoopPtr;
//
// roveTiRtos Interface Constructor
void roveBoard_LOOP_open(roveLoopPtr loop_Ptr, UInt loop_Pri);

#endif // ROVELOOP_H_
