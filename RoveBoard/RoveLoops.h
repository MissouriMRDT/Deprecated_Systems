// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifndef ROVELOOPS_H_
#define ROVELOOPS_H_
#pragma once

#define FOREVER 1

// == RoveLoopCCS ========
//
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

//roveTiRtos Interface Object
typedef ti_sysbios_knl_Task_FuncPtr roveLoopPtr;

//roveTiRtos Interface Constructor
void roveBoard_LOOP_open(roveLoopPtr loop_Ptr, UInt loop_Pri);

#endif // ROVELOOP_H_
