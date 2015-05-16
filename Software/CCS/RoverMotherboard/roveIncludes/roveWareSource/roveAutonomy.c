/*
 * roveAutonomy.c
 *
 *  Created on: May 13, 2015
 *      Author: mrdtdev
 */

#include "../roveWareHeaders/roveAutonomy.h"

void emergencyStop()
{
	int i;

	for (i = 0; i < (sizeof(E_STOP_MOTORS) / sizeof(E_STOP_MOTORS[0])); i++)
	{
		Mailbox_post(fromBaseStationMailbox, &(E_STOP_MOTORS[i]),
		        BIOS_WAIT_FOREVER);
	}

	for (i = 0; i < (sizeof(E_STOP_ARM) / sizeof(E_STOP_ARM[0])); i++)
	{
		Mailbox_post(fromBaseStationMailbox, &(E_STOP_ARM[i]),
		        BIOS_WAIT_FOREVER);
	}

	return;
}

