/*
 * roveHardwareTester.c
 *
 *  Created on: Mar 3, 2015
 *      Author: owen
 *
 * Task that will test all of the hardware functionality
 * Should be disabled most of the time. Only run it when you want to
 * do hardware testing.
 */
#include "roveIncludes/roveWareHeaders/roveHardwareTester.h"


Void roveHardwareTester(UArg arg0, UArg arg1)
{
	char buffer[20] = "This is a test\0";
	int i, j;

	System_printf("Starting hardware diagnostic\n");
	System_flush();

	System_printf("Testing GPIO abstraction on U3_MUX_S0 (PH0)\n");
	while(1)
	{
		System_printf("Testing High\n");
		System_flush();
		for(j = U3_MUX_S0; j < U7_MUX_S1; j++)
			digitalWrite(j, HIGH);
		Task_sleep(2000);

		System_printf("Testing Low\n");
		System_flush();
		for(j = U3_MUX_S0; j < U7_MUX_S1; j++)
			digitalWrite(j, LOW);
		Task_sleep(2000);
	}

	for(i = 0; i < 18; i++)
	{
		System_printf("Testing Device #%d\n", i);
		System_flush();
		deviceWrite(i, buffer, 20);
		Task_sleep(2000);
	}

	System_printf("Finished testing all devices\n");
	System_flush();
	Task_exit();
}
