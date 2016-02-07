// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare

#include "RoveLoops.h"

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


*/
