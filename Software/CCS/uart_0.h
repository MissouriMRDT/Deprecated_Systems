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

	while(1)
	{
		UART_write(uart1, "Hey", 3);
		//UART_read(uart7, &input, 1);
		    	//System_printf("%c", input);
		    	//System_flush()
	}
}

#endif /* UART_0_H_ */
