// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifndef ROVELOOPS_H_
#define ROVELOOPS_H_
#pragma once

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

//roveTiRtos Interface Object
typedef ti_sysbios_knl_Task_FuncPtr roveLoopPtr;

// == RoveLoopsCCS List ==============
//
#define FOREVER 1



// == TODO::LOOP_TWO_DEVELOPER ==============
//
Void roveLOOP_two(UArg arg0, UArg arg1)
{
    //DEBUGGING
    int second_loop_awake_count = 0;
    while(FOREVER)
    {
       //printf("%d\n\n", second_loop_awake_count);
       second_loop_awake_count++;
    }// end while
}//end loop



// == TODO::LOOP_THREE_DEVELOPER ==============
//
Void roveLOOP_three(UArg arg0, UArg arg1)
{
    //DEBUGGING
    int third_loop_awake_count = 0;
    while(FOREVER)
    {
       //printf("%d\n\n", second_loop_awake_count);
        third_loop_awake_count++;
    }// end while
}//end loop.
//
//Etc....Max of 16 Loops awakened/slept on rtos priority ..




//roveTiRtos Interface Constructor
void roveBoard_LOOP_open(roveLoopPtr loop_Ptr, UInt loop_Pri)
{
    //construct
    Task_Params roveLoop_Params;
    Task_Params_init(&roveLoop_Params);

    //config
    roveLoop_Params.priority = loop_Pri;
    Task_create (loop_Ptr, &roveLoop_Params, NULL);
}//end fnctn

#endif // ROVELOOPS_H_
