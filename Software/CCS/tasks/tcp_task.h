/*
 * tcp_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "../include/queue_elements.h"
#include "../include/frozen.h"

#include <string.h>
#include <stdbool.h>

extern Queue_Handle debug_Q;

Debug_message test;

extern Void tcp_connection(UArg arg0, UArg arg1)
{

	// Init UARTs
	UART_Handle uart0 = init_uart( 0 );
	UART_Handle uart7 = init_uart( 7 );

	// Read buffer
	char tcp_input;

	char JSON_string_buf[50] = "";

	UART_write(uart0, "Rover Booting\n", 14);

	bool end_bracket = false;

	while(1)
	{
		////////////////////////
		// JSON String Buffer
		////////////////////////

		// Read one byte from TCP
		UART_read(uart7, &tcp_input, 1);

		//Check if start of JSON string
		if (tcp_input == '{')
		{
			// Place { into buf
			size_t len = strlen(JSON_string_buf);
			JSON_string_buf[len++] = tcp_input;
			JSON_string_buf[len] = '\0';

			// Place rest of JSON string into buf
			while( end_bracket == false )
			{
				// Read char
				UART_read(uart7, &tcp_input, 1);

				// Place char in buf
				len = strlen(JSON_string_buf);
				JSON_string_buf[len++] = tcp_input;
				JSON_string_buf[len] = '\0';

				// Check for end bracket
				if( tcp_input == '}')
				{
					end_bracket = true;
				}
			}

			///////////////
			// JSON Parse
			//
			// Handwritten for now
			//
			// TODO: fix this and make it less brittle
			///////////////

			// Get ID
			char Id[4];

			Id[0] = JSON_string_buf[6];
			Id[1] = JSON_string_buf[7];
			Id[2] = JSON_string_buf[8];
			Id[3] = JSON_string_buf[9];

			// Get Value

			UART_write(uart0, Id, 4);

			////////////////////
			// Clean up
			////////////////////

			// Clear c string for the next JSON string
			JSON_string_buf[0] = '\0';
		}
	}
}

#endif /* TCP_TASK_H_ */
