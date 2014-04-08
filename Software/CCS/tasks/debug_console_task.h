/*
 * uart_0_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef DEBUG_CONSOLE_TASK_H_
#define DEBUG_CONSOLE_TASK_H_

extern Void debug_console(UArg arg0, UArg arg1)
{
	// Uart0 debug path
	UART_Handle uart1 = init_uart( 0 );

	UART_write(uart1, &tcp_input, 1);
}

#endif /* DEBUG_CONSOLE_TASK_H_ */
