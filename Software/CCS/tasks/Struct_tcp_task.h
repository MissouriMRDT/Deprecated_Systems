/*
 * tcp_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include <string.h>
#include <stdbool.h>

#include "../include/struct_test.h"

#define mux_delay 100
#define uart_delay 100

struct motor_struct
{
	uint8_t speed;
};

extern Void struct_tcp(UArg arg0, UArg arg1)
{
	/*

	// Init UARTs
	//UART_Handle uart0 = init_uart( 0 );
	UART_Handle uart1 = init_uart( 1 );
	UART_Handle uart2 = init_uart( 2 );

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
		// Read one byte from TCP
		UART_read(uart7, &tcp_input, 1);
		//UART_write(uart0, &tcp_input, 1);

		if( tcp_input == 'L' )
		{
			System_printf("Left Command\n");
			System_flush();
			UART_read(uart7, &tcp_input, 1);
			//////////////////////////
			// Left Command
			//////////////////////////
			mux_1( 8 );
			mux_2( 7 );

			SysCtlDelay( SysCtlClockGet() / mux_delay );

			UART_writePolling(uart1, &tcp_input, 1);
			UART_writePolling(uart2, &tcp_input, 1);

			SysCtlDelay( SysCtlClockGet() / uart_delay );
		}
		if( tcp_input == 'R' )
		{
			System_printf("Right Command\n");
			System_flush();
			UART_read(uart7, &tcp_input, 1);
			//////////////////////////
			// Left Command
			//////////////////////////
			mux_1( 1 );
			mux_2( 2 );

			SysCtlDelay( SysCtlClockGet() / mux_delay );

			UART_writePolling(uart1, &tcp_input, 1);
			UART_writePolling(uart2, &tcp_input, 1);

			SysCtlDelay( SysCtlClockGet() / uart_delay );
		}
	}
*/
}


#endif /* TCP_TASK_H_ */
