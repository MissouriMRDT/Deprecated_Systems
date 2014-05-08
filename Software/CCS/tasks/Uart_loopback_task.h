/*
 * tcp_task.h
 *
 */

#ifndef UART_LOOPBACK_TASK_H_
#define UART_LOOPBACK_TASK_H_

extern Void uartTest(UArg arg0, UArg arg1)
{
	UART_Handle uart = init_uart( 5, 115200 );

	mux_5(13);

	while(1)
	{
		//int = sizeof(*test);
	}
}

#endif /* TCP_TASK_H_ */
