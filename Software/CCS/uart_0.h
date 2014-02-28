/*
 * uart_0.h
 *
 *  Keenan Johnson
 */

#ifndef UART_0_H_
#define UART_0_H_

extern Void uart_0_task(UArg arg0, UArg arg1)
{
	// Init Uart 0
	UART_Handle uart0 = init_uart( 0 );
	UART_write(uart0, "Hey", 3);
}

#endif /* UART_0_H_ */
