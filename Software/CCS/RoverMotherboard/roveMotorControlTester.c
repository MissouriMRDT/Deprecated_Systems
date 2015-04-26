/*
 * roveMotorControlTester.c
 *
 *  Created on: Mar 25, 2015
 *      Author: Judah
 *
 * Task that will test MC functionality
 * Should be disabled most of the time. Only run it when you want to
 * do Motor Control testing.
 */
#include "roveIncludes/roveWareHeaders/roveMotorControlTester.h"


Void roveMotorControlTester(UArg arg0, UArg arg1){

	char messageBuffer[35] = "This is a test of motor control";

	int messageSize = 32;

	int speed = 0;

	int loopCount = 0;

	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;

	System_printf("messageBuffer holds %s \n", messageBuffer);
	System_flush();

	System_printf("messageSize holds %d \n", messageSize);
	System_flush();

	System_printf("speed holds %d \n", speed);
	System_flush();

	System_printf("Starting motor control diagnostic\n");
	System_flush();

	//config the MC for safe test protection modes

	//^MMOD 1 0_		Set to Open Loop Mode

	//^ALIM 1 250_		Set Max Amps to 25A

	//char configMessageBuffer[] = "^MMOD 1 0_^ALIM 1 250_";

	//int configMessageSize = sizeof(configMessageBuffer);

	//deviceWrite(ONBOARD_ROVECOMM, configMessageBuffer, configMessageSize);

	while(1){

		if(speed > 900){

			speed = 0;

		}//endif:	(speed > 900)

		speed = speed + 10;

		ms_delay(100);

		messageSize = generateMotorCommand(speed, messageBuffer);

		System_printf("messageBuffer holds %s \n", messageBuffer);
		System_flush();

		System_printf("messageSize holds %d \n", messageSize);
		System_flush();

		System_printf("speed holds %d \n", speed);
		System_flush();

		//	#define ONBOARD_ROVECOMM 19
		//	UART2		U2TX PA7

		deviceWrite(ONBOARD_ROVECOMM, messageBuffer, (messageSize-1));

		ms_delay(100);

		loopCount = loopCount + 1;


		System_printf("Finished testing loop number %d \n", loopCount);
		System_flush();

	}//endwhile:	(1)

}//endfnctn:		roveMotorControlTester(UArg arg0, UArg arg1)
