// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// C interface for a TexInst TIVA RTOS TASK Thread with private stack / signal
// Using Texas Instruments Code Composer Studio RTOS stack instatiates the roveDevice_Thread.c
// This is found in the tivaRtscJS.cfg[TI-RTOS] Javascript Gui/Script tab at the bottom of Projece Explorer Folders
// recieves base station messages using ip bsd style sockets and issues logic commands to hardware
//
// mrdt::rovWare
//Cplus
#include "RoveWristLoop.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////::BEGIN//////Forever Thread Tiva Rtos Scheduled Task//////////////
void roveLoop(UArg arg0, UArg arg1)
{
    //Private Thread Stack  (Tiva Rtos Task MemSpace) roveThread_Setup()

    //extern roveUart_Handle UART_2;
    //extern roveGpio_Handle PE_1;
    //roveUART_Handle FAKE_UART;
    //roveGPIO_Handle FAKE_GPIO;

    /*RoveComm UdpSock;

    int test_error =  UdpSock.beginUdp("192.168.1.2", 11000);
        printf("beginUdp test_error: %d", test_error);

    while(FOREVER)
    {
        test_error = UdpSock.readUdp();
            printf("readUdp test_error: %d", test_error);

    }// end while
*/
}//end task

#ifdef __cplusplus
}
#endif
