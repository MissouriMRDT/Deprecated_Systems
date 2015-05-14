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

	for (i = 0;
	        i < (sizeof(E_STOP_MOTORS) / sizeof(struct motor_control_struct));
	        i++)
	{
		Mailbox_post(fromBaseStationMailbox, &(E_STOP_MOTORS[i]),
		        BIOS_WAIT_FOREVER);
	}

	for (i = 0; i < (sizeof(E_STOP_ARM) / sizeof(struct motor_control_struct));
	        i++)
	{
		Mailbox_post(fromBaseStationMailbox, &(E_STOP_MOTORS[i]),
		        BIOS_WAIT_FOREVER);
	}

	return;
}

