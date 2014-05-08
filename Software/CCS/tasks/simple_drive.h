/*
 * simple_drive.h
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 */

#ifndef SIMPLE_DRIVE_H_
#define SIMPLE_DRIVE_H_

#include <string.h>
#include <stdbool.h>
#include "../include/struct_xfer.h"

struct motor_struct
{
	unsigned char closedLoopMode; // 0 for open loop control, non-zero for closed-loop
	float setSpeed; // speed in km/hr for closed-loop control. This is intentionally redundant (for debug and production mode)
	unsigned char openPWM; // directly set the PWM value for open-loop control mode
};

extern Void tcp_connection(UArg arg0, UArg arg1)
{

	// Init UARTs
	int baud_rate = 115200;
	UART_Handle uart0 = init_uart( 0, baud_rate );
	UART_Handle uart1 = init_uart( 1, baud_rate );
	UART_Handle uart2 = init_uart( 2, baud_rate );
	UART_Handle uart3 = init_uart( 3, baud_rate );
	UART_Handle uart7 = init_uart( 7, baud_rate );

	// Debug
	UART_write(uart0, "Rover Booting\n", 14);

	// Read buffer
	char tcp_input;

	struct motor_struct _struct;

	_struct.closedLoopMode = 1;

	while(1)
	{
		// Read one byte from TCP
			UART_read(uart7, &tcp_input, 1);

			if( tcp_input == 'L' )
			{
				UART_read(uart7, &tcp_input, 1);

				_struct.x = tcp_input;
				//////////////////////////
				// Left Command
				//////////////////////////
				mux_1( 8 );
				mux_2( 7 );
				mux_3( 6 );

				send_struct(uart1, &_struct);
				send_struct(uart2, &_struct);
				send_struct(uart3, &_struct);
			}
			if( tcp_input == 'R' )
			{
				UART_read(uart7, &tcp_input, 1);

				_struct.x = tcp_input;
				//////////////////////////
				// Left Command
				//////////////////////////
				mux_1( 1 );
				mux_2( 2 );
				mux_3( 3 );

				send_struct(uart1, &_struct);
				send_struct(uart2, &_struct);
				send_struct(uart3, &_struct);
			}
		}
	}

#endif /* SIMPLE_DRIVE_H_ */
