// roveTelemCnrtl.c MST MRDT
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu
//
// this implements a single function BIOS thread
// that acts as the RoverMotherboard.cfg roveTelemCnrtlTask handle
//
// recieves telemetry from Devices in roveCom protocol via uart
//
// sends telemetry to TCPHandler via roveCom protocol using TI.Mailbox.from objecm
//
// BIOS_start in main inits this as the roveTelemCntrlTask Thread
//
// this is a RoverMotherboard.cfg object::roveTelemCntrlTask::
//
// priority 3, vital_flag = t, 2048 persistent private stack

#include "roveIncludes/roveWareHeaders/roveTelemCntrl.h"

Void roveTelemCntrl(UArg arg0, UArg arg1) {

    const uint8_t FOREVER = 1;

    char messageBuffer[MAX_TELEM_SIZE];

    int deviceJack;

    deviceJack = GPS_ON_MOB;

    while (FOREVER) {

        while(!recvSerialStructMessage(deviceJack, messageBuffer));

        Mailbox_post(toBaseStationMailbox, messageBuffer, BIOS_WAIT_FOREVER);

    } //endwhile

    //postcondition: execution will not reach this state unless a serious error occurs

    printf("Rove Telem Cntrl Task Error: Forced Exit\n");

    //exit Task

    Task_exit();

} //endfnctn:       roveTelemContoller() Task Thread
