/*
 * roveCommandParser.c
 *
 *  Created on: Jan 24, 2015
 *      Author: owen
 */

#include "roveCommand.h"

Void roveCommand(UArg arg0, UArg arg1)
{
	base_station_cmd_struct            fromBaseMsg;

	System_printf("roveCommandParser has started\n");
	System_flush();
	while(1)
	{
		System_printf("roveCommandParser is waiting for a message\n");
		System_flush();
		Mailbox_pend(fromBaseStationMailbox, &fromBaseMsg, BIOS_WAIT_FOREVER);
		System_printf("\nCommand Parser Thread has received a command!:");
		System_printf("id - %d, value - %d\n", fromBaseMsg.id, fromBaseMsg.value);
		System_flush();
		//Wait to get data from base station

		//Dump data back to base station
	}

}


