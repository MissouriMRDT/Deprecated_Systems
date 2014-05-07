/*
 * tcp_task.h
 *
 */

#ifndef MUX_TEST_TASK_H_
#define MUX_TEST_TASK_H_

#include "../include/struct_xfer.h"

struct test_motor_struct
{
	uint8_t x;
};

extern Void mux_test(UArg arg0, UArg arg1)
{
	UART_Handle uart1 = init_uart( 5 );

	struct test_motor_struct test;

	mux_5(13);

	while(1)
	{
		//Go foreward
		test.x = 0x9B;

		//Send command
		send_struct(uart1, &test);

		SysCtlDelay( SysCtlClockGet()  );

		//Stop
		test.x = 0x80;
		//Send command

		//Send command
		send_struct(uart1, &test);

		SysCtlDelay( SysCtlClockGet()  );
	}
}

#endif /* TCP_TASK_H_ */
