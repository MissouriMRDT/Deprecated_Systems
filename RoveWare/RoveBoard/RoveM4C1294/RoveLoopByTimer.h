// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#pragma once
#ifndef ROVESCHEDULE_H_
#define ROVESCHEDULE_H_

#ifdef __cplusplus
extern "C" {
#endif


// rtos hooks are scheduled by implicit config timed interrupts
//#include <ti/sysbios/knl/Clock.h>

// == RoveClock ========
//
// Rtos ISR, wires to call Clock rtos object scheduled by Microsecond Interrupt by TivaRtos
// wires to call Clock rtos object
// #include <ti/sysbios/knl/Clock.h>
// void clock_mS(UArg arg);

// #include <ti/sysbios/knl/Swi.h>
// Rtos Post Processing Manifest, scheduled by TivaRtos

// TODO roveWare Upgrades Version 1 Release

/* Cplus object wrappers
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
*/

#ifdef __cplusplus
}
#endif

#endif // ROVEPOSTPROCCESS_H_
