/*
 * tcp_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "../include/queue_elements.h"

#include <string.h>

extern Queue_Handle debug_Q;

Debug_message test;

extern Void tcp_connection(UArg arg0, UArg arg1)
{

	// Init UARTs
	UART_Handle uart0 = init_uart( 0 );
	UART_Handle uart7 = init_uart( 7 );

	// Read buffer
	char tcp_input;

	char JSON_string_buf[40] = {};

	UART_write(uart0, "Rover Booting", 13);

	while(1)
	{
		// Read one byte from TCP
		UART_read(uart7, &tcp_input, 1);

		//Check if start of JSON string
		if (tcp_input == '{')
		{
			// Place { into buf
			strcat(JSON_string_buf, tcp_input);

			// Place rest of JSON string into buf
			while( UART_read(uart7, &tcp_input, 1) != '}' )
			{
				strcat(JSON_string_buf, tcp_input);
			}

			// Place } into Json buf
			strcat(JSON_string_buf, tcp_input);

			UART_write(uart0, JSON_string_buf, 24);

			// Clear c string for the next JSON string
			strcpy(JSON_string_buf, "");
		}
	}
}

#endif /* TCP_TASK_H_ */
