// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#ifndef ROVELOOP_H_
#define ROVELOOP_H_

//Rover Wrappers for Tiva C Connected
#include "roveWare/roveBoard/roveBOARD_TIVA1294.h"

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
