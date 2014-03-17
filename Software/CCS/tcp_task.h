/*
 * tcp_task.h
 *
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "tcp.h"

extern Void tcp(UArg arg0, UArg arg1)
{
	//Uart inits
	UART_Handle uart0 = init_uart( 0 );
	UART_write(uart0, "UART0 init complete\n", 20);

	UART_Handle uart7 = init_uart( 7 );
	UART_write(uart0, "UART7 init complete\n", 20);

	UART_Handle uart1 = init_uart( 1 );
	UART_write(uart0, "UART1 init complete\n", 20);

	UART_Handle uart2 = init_uart( 2 );
	UART_write(uart0, "UART2 init complete\n", 20);

	char tcp_input;

	while(1)
	{
		//Read byte from TCP
		UART_read(uart7, &tcp_input, 1);

		//Send byte out debug port
		UART_write(uart0, &tcp_input, 1);

		//Send to first set of motor controllers
		mux_1(1);
		mux_2(2);

		//Send command
		UART_write(uart1, &tcp_input, 1);
		UART_write(uart2, &tcp_input, 1);

		//Send to second set of motor controllers
		mux_1(8);
		mux_2(7);

		//Send command
		UART_write(uart1, &tcp_input, 1);
		UART_write(uart2, &tcp_input, 1);
	}
}

#endif /* TCP_TASK_H_ */
