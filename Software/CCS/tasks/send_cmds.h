/*
 * send_cmds.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Zeus
 */

#ifndef SEND_CMDS_H_
#define SEND_CMDS_H_

#include "../global.h"

extern uint8_t cmd_number;
uint8_t byte_R;
uint8_t byte_L;

#define mux_delay 100
#define uart_delay 100

extern Void mux_cmds(UArg arg0, UArg arg1)
{
	UART_Handle uart0 = init_uart( 0 );
	UART_Handle uart1 = init_uart( 1 );
	UART_Handle uart2 = init_uart( 2 );
	UART_Handle uart3 = init_uart( 3 );
	UART_Handle uart4 = init_uart( 4 );


	// Right 1,2, 9
	// Left 7, 8, 12
	while(1)
	{

		byte_R = value_byte_R;
		byte_L = value_byte_L;

		UART_write(uart0, &value_byte_R, 1);

		//////////////////////////
		// Right Command
		//////////////////////////
		mux_1( 1 );
		mux_2( 2 );

		SysCtlDelay( SysCtlClockGet() / mux_delay );

		UART_writePolling(uart1, &value_byte_R, 1);
		UART_writePolling(uart2, &value_byte_R, 1);

		SysCtlDelay( SysCtlClockGet() / uart_delay );

		//////////////////////////
		// Left Command
		//////////////////////////
		mux_1( 8 );
		mux_2( 7 );

		SysCtlDelay( SysCtlClockGet() / mux_delay );

		UART_writePolling(uart1, &value_byte_L, 1);
		UART_writePolling(uart2, &value_byte_L, 1);

		SysCtlDelay( SysCtlClockGet() / uart_delay );

	}

}

#endif /* SEND_CMDS_H_ */
