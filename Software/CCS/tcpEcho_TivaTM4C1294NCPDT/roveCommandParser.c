/*
 * roveCommandParser.c
 *
 *  Created on: Jan 24, 2015
 *      Author: owen
 */

#include "roveCommandParser.h"

Void roveCommandParser(UArg arg0, UArg arg1)
{
	MsgObj             fromBaseMsg;

	System_printf("roveCommandParser has started\n");
	System_flush();
	while(1)
	{
		System_printf("roveCommandParser is waiting for a message\n");
		System_flush();
		Mailbox_pend(fromBaseStationMailbox, &fromBaseMsg, BIOS_WAIT_FOREVER);
		System_printf("roveCommandParser has recieved a message\n");
		System_printf("Message contents: %s\n", fromBaseMsg.message_body);
		System_flush();
		//Wait to get data from base station

		//Dump data back to base station
	}

}


