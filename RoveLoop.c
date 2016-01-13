// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// C interface for a TexInst TIVA RTOS TASK Thread with private stack / signal
// Using Texas Instruments Code Composer Studio RTOS stack instatiates the roveDevice_Thread.c
// This is found in the tivaRtscJS.cfg[TI-RTOS] Javascript Gui/Script tab at the bottom of Projece Explorer Folders
// recieves base station messages using ip bsd style sockets and issues logic commands to hardware
//
// mrdt::rovWare
#ifdef __cplusplus
extern "C" {
#endif
//Cplus
#include "RoveLoop.h"

//RoveWare
#include "RoveWare/RoveComm.h"
#include "RoveWare/RoveControl.h"
//#include "roveWare/roveSense.h"
//#include "roveWare/roveScience.h"
//#include "roveWare/roveMonitor.h"



//////////////::BEGIN//////Forever Thread Tiva Rtos Scheduled Task//////////////
Void roveLoop(UArg arg0, UArg arg1)
{
















    //Private Thread Stack  (Tiva Rtos Task MemSpace) roveThread_Setup()

    //extern roveUart_Handle UART_2;
    //extern roveGpio_Handle PE_1;
    //roveUART_Handle FAKE_UART;
    //roveGPIO_Handle FAKE_GPIO;
/*
    uint16_t data_id;
    size_t size;
    char data[] = "Tiva Cplus RoveComm For the Win!";

    RoveCommBegin();

    while(1)
    {
        RoveCommGetMsg(&data_id, &size, data);
        //printf("%s", data);
        RoveCommSendMsg(data_id, size, data);
    }// end while
*/
}//end task

#ifdef __cplusplus
}
#endif
