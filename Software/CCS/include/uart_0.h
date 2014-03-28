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
	UART_Handle uart1 = init_uart( 1 );
	UART_Handle uart2 = init_uart( 2 );
	UART_Handle uart3 = init_uart( 3 );
	UART_Handle uart4 = init_uart( 4 );
	UART_Handle uart5 = init_uart( 5 );
	UART_Handle uart7 = init_uart( 7 );

	mux_1(8);
	mux_2(7);
	mux_3(6);
	mux_4(5);
	mux_5(14);
	mux_7(17);

	while(1)
	{
		UART_write(uart1, "Hey", 3);
		UART_write(uart2, "Hey", 3);
		UART_write(uart3, "Hey", 3);
		UART_write(uart4, "Hey", 3);
		UART_write(uart5, "Hey", 3);
		UART_write(uart7, "Hey", 3);
		//UART_read(uart7, &input, 1);
	}
}

#endif /* UART_0_H_ */
