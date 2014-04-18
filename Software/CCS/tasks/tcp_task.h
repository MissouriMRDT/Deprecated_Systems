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
#include <stdbool.h>

#include "../global.h"


extern Queue_Handle debug_Q;

Debug_message test;

#define mux_delay 100
#define uart_delay 100

extern Void tcp_connection(UArg arg0, UArg arg1)
{

	// Init UARTs
	//UART_Handle uart0 = init_uart( 0 );
	UART_Handle uart1 = init_uart( 1 );
	UART_Handle uart2 = init_uart( 2 );
	UART_Handle uart7 = init_uart( 7 );

	// Read buffer
	char tcp_input;

	char JSON_string_buf[50] = "";

	//UART_write(uart0, "Rover Booting\n", 14);

	size_t len;

	bool end_bracket;
	bool is_end_of_value;
	int value_index;
	int json_value_string_index;

	char Id[4];
	char Value[10];
	extern uint8_t value_byte_L;
	extern uint8_t value_byte_R;
	extern uint8_t cmd_number;
	int local_val_l;
	int local_val_r;

	while(1)
	{

		/*
		////////////////////////
		// JSON String Buffer
		////////////////////////
		end_bracket = false;

		// Read one byte from TCP
		UART_read(uart7, &tcp_input, 1);

		//Check if start of JSON string
		if (tcp_input == '{')
		{
			len=0;

			// Place { into buf
			len = strlen(JSON_string_buf);
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

			// Get Id
			Id[0] = JSON_string_buf[6];
			Id[1] = JSON_string_buf[7];
			Id[2] = JSON_string_buf[8];
			Id[3] = JSON_string_buf[9];

			//Convert from string to int
			cmd_number = atoi( Id );

			// Get Value starting at 19
			Value[0] = '\0';
			is_end_of_value = false;

			value_index = 0;
			json_value_string_index = 19;

			while(is_end_of_value == false)
			{
				//Check for ending } which denotes end of value
				if( JSON_string_buf[json_value_string_index] == '}' )
				{
					is_end_of_value = true;
					Value[value_index] = '\0';
				}
				// this char is a digit of a value
				else
				{
					Value[value_index] = JSON_string_buf[json_value_string_index];
					value_index++;
					json_value_string_index++;
				}
			}

			//Convert from string to int
			value_byte = atoi( Value );
			*/

		// Read one byte from TCP
			UART_read(uart7, &tcp_input, 1);
			//UART_write(uart0, &tcp_input, 1);

			if( tcp_input == 'L' )
			{
				UART_read(uart7, &tcp_input, 1);
				if( tcp_input != 'L' && tcp_input != 'R')
				{
					//////////////////////////
					// Left Command
					//////////////////////////
					mux_1( 8 );
					mux_2( 7 );

					SysCtlDelay( SysCtlClockGet() / mux_delay );

					UART_write(uart1, &tcp_input, 1);
					UART_write(uart2, &tcp_input, 1);

					SysCtlDelay( SysCtlClockGet() / uart_delay );
				}

			}
			if( tcp_input == 'R' )
			{
				UART_read(uart7, &tcp_input, 1);
				if( tcp_input != 'L' && tcp_input != 'R')
				{
					//////////////////////////
					// Left Command
					//////////////////////////
					mux_1( 9 );
					mux_2( 2 );

					SysCtlDelay( SysCtlClockGet() / mux_delay );

					UART_write(uart1, &tcp_input, 1);
					UART_write(uart2, &tcp_input, 1);

					SysCtlDelay( SysCtlClockGet() / uart_delay );
				}
			}
/*
			// Debug prints
			UART_write(uart0, "Cmd ID:", 7);
			UART_write(uart0, Id, 4);
			UART_write(uart0, " Value: ", 8);
			UART_write(uart0, Value, value_index);
			UART_write(uart0, "\n", 1);
			*/

			////////////////////
			// ISSUE DRIVE COMMANDS
			//////////////////////

			// Drive all for now

			//mux_1( 1 );

			// Left Wheels

			//UART_write(uart1, &value_byte, 1);

			/*
			#define mux_delay 100
			#define uart_delay 100

			//////////////////////////
			// Send cmd out all ports
			//////////////////////////
			//
			// Position 0
			mux_1( 1 );
			mux_2( 2 );
			mux_3( 3 );
			mux_4( 4 );

			SysCtlDelay( SysCtlClockGet() / mux_delay );

			UART_writePolling(uart1, &value_byte, 1);
			UART_writePolling(uart2, &value_byte, 1);
			UART_writePolling(uart3, &value_byte, 1);
			UART_writePolling(uart4, &value_byte, 1);

			SysCtlDelay( SysCtlClockGet() / uart_delay );

			// Position 1
			mux_1( 8 );
			mux_2( 7 );
			mux_3( 6 );
			mux_4( 5 );

			SysCtlDelay( SysCtlClockGet() / mux_delay );

			UART_write(uart1, &value_byte, 1);
			UART_write(uart2, &value_byte, 1);
			UART_write(uart3, &value_byte, 1);
			UART_write(uart4, &value_byte, 1);

			SysCtlDelay( SysCtlClockGet() / uart_delay );

			// Position 2
			mux_1( 9 );
			mux_2( 10 );
			mux_3( 11 );
			mux_4( 12 );

			SysCtlDelay( SysCtlClockGet() / mux_delay );

			UART_write(uart1, &value_byte, 1);
			UART_write(uart2, &value_byte, 1);
			UART_write(uart3, &value_byte, 1);
			UART_write(uart4, &value_byte, 1);

			SysCtlDelay( SysCtlClockGet() / uart_delay );



			////////////////////
			// Clean up
			////////////////////

			// Clear c string for the next JSON string
			JSON_string_buf[0] = '\0';
			*/
		}
	}


#endif /* TCP_TASK_H_ */
