// roveComTester.c MST MRDT
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu
//
// this implements a single function BIOS thread
// that acts as the RoverMotherboard.cfg roveComTesterTask handle
//
// This task would need to be activated in RoverMotherbaordMain.cfg gui with high pri
//
// BIOS_start in would then init this as the rroveComTesterTask Thread
//
// this is a RoverMotherboard.cfg object::roveComTesterTask::
//
// priority 15, vital_flag = t, 2048 persistent private stack

#include "../roveWareHeaders/roveComTester.h"

Void roveComTester(UArg arg0, UArg arg1) {
    /*
    const uint8_t FOREVER = 1;

    base_station_msg_struct baseStationMsg;

    while (FOREVER){

        ms_delay(1000);

        Mailbox_post(fromBaseStationMailbox, &baseStationMsg, BIOS_WAIT_FOREVER);

    }
    */
}//end roveComTest

