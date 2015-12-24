// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#ifndef ROVELOOP_H_
#define ROVELOOP_H_

//Rover Wrappers for Tiva C Connected
#include "roveBoard/roveBOARD_TIVA1294.h"

//RoveWare
#include "roveWare/roveComm.h"
#include "roveWare/roveControl.h"
//#include "roveWare/roveSense.h"
//#include "roveWare/roveScience.h"
//#include "roveWare/roveMonitor.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>

//#include <ti/sysbios/BIOS.h>
//#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
//#include <ti/sysbios/knl/Clock.h>
//#include <ti/sysbios/knl/Semaphore.h>

#include <xdc/cfg/global.h>

void roveLoop(UArg arg0, UArg arg1);

#endif // ROVELOOP



/* ========  roveComm  ========
//
// Cplus object wrappers
class roveComm
{
    public:
    //private:
        //pure C public API roveComm.h
        rovecomm_socket _udp_socket;
        rovecomm_protocol _udp_data;

        int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);
        int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);

    //public:
        //Cplus extension API for Tiva Threads
        roveComm(int newId);
        ~roveComm();
        //roveComm::beginUdp(my_ip_addr, port);
        //roveComm::beginTcp(my_ip_addr, port);;
};// end class

//Tell the compiler to wire the C++ Tiva interface to pure C implementations in roveComm.h
extern "C"
{
int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);
int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);
}// end extern



// ======== roveComm Future Developement:
//roveComm::beginTcp(local_ip_addr, port);
//roveComm::readTcp(remote_ip_addr, "char_message");
//roveComm::writeTcp(remote_ip_addr, "char_message");
//
//roveComm::beginHttp();
//roveComm::getHttp(remote_url, "json_message");
//roveComm::postHttp(remote_url, "json_message");
//
//roveComm::beginMqqt(broker);
//roveComm::publishMqqt("message");
//roveComm::subscribeMqqt("message");
// ========  =======  ========



// ========  roveControl  ========
//
// Cplus object wrappers
class roveControl
{
    public:
    //private:
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
    //public:
        roveControl(int newId);
        ~roveControl();
        //https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Constructor
        //BeginAx(serial_pin, dyna_id, baud_rate);
        //BeginMx(serial_pin, dyna_id, baud_ra);
};// end class

//Tell the compiler to wire the C++ Tiva interface to pure C implementations in roveControl.h
extern "C"
{
//config constructor
int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

//WHEEL Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

//JOINT Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);
}// end extern
//
// ========  =======  ========*/



/* roveWare Upgrades Version 1 Release
 *
// ========  roveMonitor ========
//
// Cplus object wrappers
class roveSoftClock
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

// Wrapper functions to call Clock::tick()
extern "C"
{
    void clock_mS(UArg arg);
    //void tick_millisecond();
    //int getClockId();
    //int getMilliSec();
} // end extern "C"

*/



/* roveWare Upgrades Version 2 Release

//TODO US Digital Encoders, Adafruit GPS, Sparkfun UltraSonic,  Sparkfun IR, SenseorHub Imu
class roveSense {

    private:

    public:
        roveSense();
        ~roveSense();
};// end class

//TODO CCD, Sparkfun Temp, Sparkfun Humidty
class roveScience {

    private:

    public:
        roveScience();
        ~roveScience();
};// end class

class roveRtosMonitor {

    private:
        rove_rtos_inst _runtime_instances;
        rove_errno _runtime_errnos;

        int32_t roveRtosMon_InitInstance(rove_rtos_inst* rtos_inst, uint8_t ints_type, int32_t monitor_flag);
        int32_t roveRtosMon_GetErrnos(rove_rtos_inst* rtos_inst);

    public:
        roveRtosMonitor();
        ~roveRtosMonitor();
};// end class
*/
