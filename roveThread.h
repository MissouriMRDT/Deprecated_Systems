// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
// instatiates the roveDevice_Thread.c as TI RTOS backed TASK
//
// mrdt::roveWare
#ifndef ROVETHREAD_H_
#define ROVETHREAD_H_


//RoveWare Naming Convention : loosely adapted from crnrPMcore Scripting Convention
//roveSquadName _ <Do Action> <On Noun> (optional ATTRIBUTE)
//ie. roveComm_ParseUdpMSG
//ie. roveDynmxl_SetWheelModeCFG


// TODO Judah Factor Out Dev Shorthand
//extern roveUart_Handle UART_2;
//extern roveGpio_Handle PE_1;
//roveUART_Handle FAKE_UART;
//roveGPIO_Handle FAKE_GPIO;

//MRDT definitions
#include "roveWare/roveProtocol.h"
//#include "roveWare/roveCplusWires.h"
#include "roveWare/roveBoard/roveBOARD_TIVA1294.h"


#include "roveWare/roveComm.h"
#include "roveWare/roveControl.h"

//C lib
#include <stdio.h>
//CCS TI operating system
//#include <ti/sysbios/knl/Task.h>
//TODO wtf TaskSelf Warning?
//#include <ti/ndk/inc/os/osif.h>
//#include <ti/sysbios/knl/Mailbox.h>
//Handle to a TivaWare RTOS Private Stack -> See tivaRtscJS.cfg


#include <xdc/std.h>
//#include <xdc/runtime/Log.h>
//#include <xdc/runtime/Diags.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/cfg/global.h>


/* roveRtosMonitor
class roveRtosMonitor {

    private:
        rove_rtos_inst _runtime_instances;
        rove_errno _runtime_errnos;

        int32_t roveRtosMon_InitInstance(rove_rtos_inst* rtos_inst, uint8_t ints_type, int32_t monitor_flag);
        int32_t roveRtosMon_GetErrnos(rove_rtos_inst* rtos_inst);

    public:
        roveComm(int newId);
        ~roveComm();
        //roveComm::beginUdp(my_ip_addr, port);
        //roveComm::beginTcp(my_ip_addr, port);;
};// end class
*/



class roveComm {

    private:
        rovecomm_socket _udp_socket;
        rovecomm_protocol _udp_data;

        int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);
        int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);

    public:
        roveComm(int newId);
        ~roveComm();
        //roveComm::beginUdp(my_ip_addr, port);
        //roveComm::beginTcp(my_ip_addr, port);;
};// end class



class roveControl {

    private:
        rove_dyna_serial rove_dynamxl;

        //config constructor
        int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

        //WHEEL Mode
        int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
        int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
        int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

         //JOINT Mode
        int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
        int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
        int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);
    public:
        roveControl(int newId);
        ~roveControl();
        //https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Constructor
        //BeginAx(serial_pin, dyna_id, baud_rate);
        //BeginMx(serial_pin, dyna_id, baud_ra);
};// end class



class Clock {
    private:
         // data
         int id;
         double ticks;
         int microsecond;
         int millisecond;
         int second;

    public:
        // methods
        Clock(int newId);  // Constructor
        ~Clock();          // Destructor
        void tick();
        int getId();
};// end class


// Global clock objects
Clock cl0(0);  // idle loop clock
Clock cl1(1);  // periodic clock, period = 1 ms
Clock cl2(2);  // periodic clock, period = 1 sec
Clock cl3(3);  // task clock
Clock cl4(4);  // task clock

// Wrapper functions to call Clock::tick()
extern "C"
{
//Wtf??
void clockIdle(void);
void clockPeridoic(UArg arg);
void clockTask(UArg arg);
} // end extern "C"


// Production Thread
void roveThread(UArg arg0 , UArg arg1);


//Clock methods
Clock::Clock(int newId)
{
    id = newId;
    ticks = 0;

    microsecond = 0;
    millisecond = 0;
    second = 0;

}// end constructor

Clock::~Clock()
{
}// end destructor

void Clock::tick()
{
    ticks++;
    return;
}// end fnctn

int Clock::getId()
{
    return id;
}// end fnctn


// ======== clockIdle ========
// Wrapper function for
// IDL objects
// calling Clock::tick()
// ========  ======== ========
void clockIdle(void)
{
    cl0.tick();
    return;
} // end fnctn

#endif // ROVETHREAD_H_
