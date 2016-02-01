// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifndef ROVELOOP_H_
#define ROVELOOP_H_
#pragma once

// == RoveWareCCS ========
//
#include "RoveWare/RoveComm.h"
#include "RoveWare/RoveControl.h"
//#include "roveWare/roveSense.h"
//#include "roveWare/roveScience.h"

// == RoveLoopCCS ========
//
#include "RoveRtosLoops.h"

// == RoveLoopCCS_HiPri ========
//
// loops spin forever, but sleep and wake states are scheduled by the rtos
//
Void roveLOOP(UArg arg0, UArg arg1)
{
    //Private Thread Stack  (Tiva Rtos Task MemSpace) roveThread_Setup()
    printf("Init roveLoop\n\n");
    uint16_t comms_id = 0;
    size_t comms_size = 0;
    char comms_data[1024];
    //RoveCommBegin(192, 168, 1, 51);
    printf("RoveCommBegin\n\n");

    //DEBUGGING
    //#define ECHO_UDP_RECVD 222

    while(FOREVER)
    {
        //Todo-> Gbenga Shift out Header Bytes and Replace with Ending Null Bytes to ease debug prints (\N for serialprintln in RoveCommParseMsg memcpy - sizeof(header...
       //RoveCommGetMsg(&comms_id, &comms_size, comms_data);
       if(comms_id > 0)
       {
           printf("comms_id: %d\n", comms_id);
           printf("comms_size: %d\n", comms_size);
           printf("%s\n\n", comms_data);
           //RoveCommSendMsg(ECHO_UDP_RECVD, comms_size, comms_data);
       }//end if

    }// end while

}//end loop

#endif // ROVELOOP_H_
