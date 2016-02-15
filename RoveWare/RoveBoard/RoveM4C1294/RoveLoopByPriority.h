// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifndef ROVEMORELOOPS_H_
#define ROVEMORELOOPS_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif



// rtos hooks are scheduled by explicit runtime post/pend sleep/wake priority schedule
//#include <ti/sysbios/knl/Swi.h>
//#include <ti/sysbios/knl/Mailbox.h>
//#include <ti/sysbios/knl/Semaphore.h>

// == RoveLoopsCCS List ==============
//
/*
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



#ifdef __cplusplus
}
#endif

#endif // ROVELOOP_H_
