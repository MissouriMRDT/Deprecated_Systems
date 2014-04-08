/*
 * tcp_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "../include/queue_elements.h"

extern Queue_Handle debug_Q;

Debug_message test;

extern Void tcp_connection(UArg arg0, UArg arg1)
{

	// Init UARTs
	UART_Handle uart0 = init_uart( 0 );
	UART_Handle uart7 = init_uart( 7 );

	// Read buffer
	uint8_t tcp_input;

	UART_write(uart0, "Rover Booting", 13);

	while(1)
	{
		// Read one byte from TCP
		UART_read(uart7, &tcp_input, 1);
		UART_write(uart0, &tcp_input, 1);
	}
}

#endif /* TCP_TASK_H_ */
