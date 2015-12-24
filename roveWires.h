// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#ifndef ROVEWIRES_H_
#define ROVEWIRES_H_

#ifdef __cplusplus
extern "C" {
#endif

//RoveWare
#include "roveWare/roveComm.h"
#include "roveWare/roveControl.h"
//#include "roveWare/roveSense.h"
//#include "roveWare/roveScience.h"
//#include "roveWare/roveMonitor.h"



// ========  roveComm  ========
//
// Cplus object wrappers
class RoveComm
{
    //public:
    private:
        //pure C public API roveComm.h
        rovecomm_socket _udp_socket;
        rovecomm_protocol _udp_data;

    public:
        //Cplus extension API for Tiva Threads
        RoveComm();
        ~RoveComm();

        int beginUdp(char* my_ip_addr, int port);
        int readUdp();
        //int writeUdp(char* message);

};// end class



// ========  roveControl  ========
//
// Cplus object wrappers
class RoveControl
{
    private:
        rove_dyna_serial _rove_dynamxl;

    public:
        RoveControl(int newId);
        ~RoveControl();

        int BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin);
        int testWheelMode(int min_speed, int max_speed, int speed_increment, int pause_microseconds);
        int testJointMode(int min_angle, int max_angle, int angle_increment, int speed, int pause_microseconds);

        //TODO https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Constructor
        //BeginMx(serial_pin, dyna_id, baud_ra);
};// end class



// ========  roveComm  ========
//
RoveComm::RoveComm()
{
}// end constructor

RoveComm::~RoveComm()
{
}// end destructor

int RoveComm::beginUdp(char* my_ip_addr, int port)
{
    return roveComm_InitUdpCFG(&_udp_socket, (uint8_t*)my_ip_addr, (int32_t)port);
}// end method



int RoveComm::readUdp()
{
    return roveComm_GetUdpMSG(&_udp_socket, &_udp_data);
}// end method



// ========  roveControl  ========
//
RoveControl::RoveControl(int newId)
{
    _rove_dynamxl.dynmxl_id = newId;
}// end constructor

RoveControl::~RoveControl()
{
}// end destructor

int RoveControl::BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin)
{
    //return roveDynmxAx_InitCFG(&_rove_dynamxl, (uint8_t)dyna_id, serial_pin, tri_state_pin);
    return -1;
}// end method



int RoveControl::testWheelMode(int min_speed, int max_speed, int speed_increment, int pause_microseconds)
{
    //TODO
    test_metrics test;
    return roveDynmxAx_TestWheelMode(&_rove_dynamxl, &test);
}// end method



int RoveControl::testJointMode(int min_angle, int max_angle, int angle_increment, int speed, int pause_microseconds)
{
    //TODO
    test_metrics test;
    return roveDynmxAx_TestJointMode(&_rove_dynamxl, &test);
}// end method



#ifdef __cplusplus
}
#endif

#endif //ROVEWIRES_H_



/* TODO roveWare Upgrades Version 1 Release
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

// wires to call Clock rtos object
void clock_mS(UArg arg);
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
