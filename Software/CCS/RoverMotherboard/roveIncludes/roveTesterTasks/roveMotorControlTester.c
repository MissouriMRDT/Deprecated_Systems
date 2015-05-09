// roveMotorControlTester.c MST MRDT
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu
//
// this implements a single function BIOS thread
// that acts as the RoverMotherboard.cfg roveMotorControlTester handle
//
// This task would need to be activated in RoverMotherbaordMain.cfg gui with high pri
//
// BIOS_start in would then init this as the roveMotorControlTester Thread
//
// this is a RoverMotherboard.cfg object::roveMotorControlTester::
//
// priority 15, vital_flag = t, 2048 persistent private stack

#include "../roveWareHeaders/roveMotorControlTester.h"

Void roveMotorControlTester(UArg arg0, UArg arg1) {

	const uint8_t FOREVER = 1;

	char messageBuffer[35] = "This is a test of motor control";

	int messageSize = 32;

	int speed = 0;

	int loopCount = 0;

	//extern UART_Handle uart0;
	//extern UART_Handle uart1;
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

	char configMessageBuffer[] = "^MMOD 1 0_^ALIM 1 250_";

	int configMessageSize = sizeof(configMessageBuffer);

	deviceWrite(ONBOARD_ROVECOMM, configMessageBuffer, configMessageSize);

	while (FOREVER) {

		if (speed > 900) {

			speed = 0;

		} //endif:	(speed > 900)

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

		deviceWrite(ONBOARD_ROVECOMM, messageBuffer, (messageSize - 1));

		ms_delay(100);

		loopCount = loopCount + 1;

		System_printf("Finished testing loop number %d \n", loopCount);
		System_flush();

	}		//endwhile (FOREVER)

}		//endfnctn Task roveMotorControlTester
