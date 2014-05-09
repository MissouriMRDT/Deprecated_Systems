/*
 * tcp_task.h
 *
 */

#ifndef UART_LOOPBACK_TASK_H_
#define UART_LOOPBACK_TASK_H_

#include "../include/struct_xfer.h"

extern Void uartTest(UArg arg0, UArg arg1)
{
	UART_Handle uart = init_uart( 1, 115200 );

	struct receive_test test_struct;

	while(1)
	{
		recv_struct( uart, &test_struct, recv_test );
		System_printf("Value: %i\n", test_struct.data);
		System_flush();
	}
}

#endif /* TCP_TASK_H_ */
