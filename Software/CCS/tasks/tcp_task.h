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

	// Init UART
	UART_Handle uart7 = init_uart( 7 );

	// Read buffer
	uint8_t tcp_input;



	while(1)
	{
		// Read one byte from TCP
		UART_read(uart7, &tcp_input, 1);

		if ( tcp_input == '{')
		{

		}
	}
}

#endif /* TCP_TASK_H_ */
