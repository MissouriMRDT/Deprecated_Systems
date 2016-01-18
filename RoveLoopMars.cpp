// Missouri Science and Technology Mars Rover Design Team 2015
// Judah Schad jrs6w7@mst.edu
//
// function hooks for the scheduler to prioritize the RoveLoop, RoveISR, and RoveClock and RovePostProcces Rtos Task routines

// == RoveBoard ========
//
// Rtos Pin Access MCU Interface Assets
#include "RoveBoard/RoveBoard.h"



// == RoveWare ========
//
// Rtos Pin Access MCU Interface Assets
#include "RoveWare/RoveComm.h"
#include "RoveWare/RoveControl.h"
//#include "roveWare/roveSense.h"
//#include "roveWare/roveScience.h"



// == RoveLoop ========
//
// CCS Rtos Forever Loops, scheduled by By Highest Priority by Texas_Instruments_BIOS
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
typedef ti_sysbios_knl_Task_FuncPtr roveLoopPtr;
void roveBoard_RtosLoop_init(roveLoopPtr loop, UInt priority);

Void firstPriorityLoop(UArg arg0, UArg arg1);
//Void secondPriorityLoop(UArg arg0, UArg arg1);
//
//Max of 16 Loops..



// == RoveMoreLoops ==============
//
// Texas Inst Rtos Module Constructor
void roveLoop_RtosTask_init(roveLoopPtr loop_name, UInt loop_priority) {

    Task_Params roveLoop_Params;
    Task_Params_init(&roveLoop_Params);

    roveLoop_Params.priority = loop_priority;
    Task_create (loop_name, &roveLoop_Params, NULL);

}//endfnctn



//////////////::BEGIN//////Forever Thread Tiva Rtos Scheduled Tasks//////////////
Void firstPriorityLoop(UArg arg0, UArg arg1)
{
    //Private Thread Stack  (Tiva Rtos Task MemSpace) roveThread_Setup()
    printf("Init roveLoop\n\n");

    //extern roveUart_Handle UART_2;
    //extern roveGpio_Handle PE_1;
    //roveUART_Handle FAKE_UART;
    //roveGPIO_Handle FAKE_GPIO;

    //Todo Ip unused here and linux desktop...how does Energia/Wiznet set dynamic??
    uint16_t comms_id;
    size_t comms_size;
    char comms_data[1024];

    RoveCommBegin(192, 168, 1, 51);
    printf("RoveCommBegin\n\n");

    //DEBUGGING
    #define ECHO_UDP_RECVD 222

    while(1)
    {
        //Todo-> Gbenga Shift out Header Bytes and Replace with Ending Null Bytes to ease debug prints (\N for serialprintln in RoveCommParseMsg memcpy - sizeof(header...
       RoveCommGetMsg(&comms_id, &comms_size, comms_data);

       if(comms_id > 0)
       {
           printf("%d\n",comms_data);
           printf("%s\n\n", comms_data);

           RoveCommSendMsg(ECHO_UDP_RECVD, comms_size, comms_data);
       }//end if
    }// end while
}//end task

//Void secondPriorityLoop(UArg arg0, UArg arg1)
//{
    //Extra Loops Here
//}




















/* == RovePostProccess ========
//
// CCS Rtos Forever Loops, scheduled by By Highest Priority by Texas_Instruments_BIOS

//Rtos ISR, scheduled by Microsecond Interrupt by Texas_Instruments_BIOSTexas_Instruments_BIOS
//#include <ti/sysbios/knl/Clock.h>

//Rtos Post Processing List, scheduled by Texas_Instruments_BIOS
//#include <ti/sysbios/knl/Swi.h>


// TODO roveWare Upgrades Version 1 Release
// ========  RovePostProccess ========
//
// Cplus object wrappers
class roveHardClock
{
    private:
         // data
         int id;
         double ticks;
         //int microseconds;
         int milliseconds;
         //int seconds;
         void tick_millisecond();

    public:
        // methods
         roveSoftClock(int newId);
        ~roveSoftClock();
        int getClockId();
        int getMilliSec();
};// end class

// wires to call Clock rtos object
void clock_mS(UArg arg);
*/

