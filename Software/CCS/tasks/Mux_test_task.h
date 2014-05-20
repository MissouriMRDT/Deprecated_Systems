/*
 * tcp_task.h
 *
 */

#ifndef MUX_TEST_TASK_H_
#define MUX_TEST_TASK_H_

#include "../include/struct_xfer.h"
#include "../include/timing.h"

extern Void mux_test(UArg arg0, UArg arg1)
{
	UART_Handle uart1 = init_uart( 1, 115200 );

	struct motor_struct _struct;

		// Enable close loop mode
	//_struct.closedLoopMode = 3;
	//_struct.openPWM = 5;

	mux_1(1);

	while(1)
	{

		//Go foreward
		//_struct.setSpeed = 2;

		//Send command
		send_struct(uart1, &_struct, motor_controller);


		//ms_delay( 1 );

		/*
		//Stop
		_struct.setSpeed = 0;
		//Send command

		//Send command
		send_struct(uart1, &_struct);

		SysCtlDelay( SysCtlClockGet()  );
		*/
	}
}

#endif /* TCP_TASK_H_ */
