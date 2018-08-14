/*
 * roveScience.c
 *
 *  Created on: May 28, 2015
 *      Author: mrdtdev
 */
#include "roveIncludes/roveWareHeaders/roveScience.h"


Void roveScience(UArg arg0, UArg arg1) {

    const uint8_t FOREVER = 1;

    char messageBuffer[MAX_TELEM_SIZE];

    int deviceJack;

    deviceJack = SCIENCE_BAY;

    while (FOREVER) {

        while(!recvSerialStructMessage(deviceJack, messageBuffer));

        Mailbox_post(toBaseStationMailbox, messageBuffer, BIOS_WAIT_FOREVER);

    } //endwhile

    //postcondition: execution will not reach this state unless a serious error occurs

    printf("Rove Science Task Error: Forced Exit\n");

    //exit Task

    Task_exit();

} //endfnctn:       roveTelemContoller() Task Thread
