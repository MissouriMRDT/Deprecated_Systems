/*
 * tcp_task.h
 *
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "tcp.h"

extern Void tcp(UArg arg0, UArg arg1)
{
	//Uart inits
	UART_Handle uart0 = init_uart( 0 );
	UART_write(uart0, "UART0 init complete\n", 20);

	UART_Handle uart7 = init_uart( 7 );
	UART_write(uart0, "UART7 init complete\n", 20);

	UART_Handle uart1 = init_uart( 1 );
	UART_write(uart0, "UART1 init complete\n", 20);

	UART_Handle uart2 = init_uart( 2 );
	UART_write(uart0, "UART2 init complete\n", 20);

	char tcp_input;

	//Send to first set of motor controllers
	mux_1(1);

	while(1)
	{
		//Read byte from TCP
		//UART_read(uart7, &tcp_input, 1);

		//Go foreward
		tcp_input = 0xFF;
		//Send command
		UART_write(uart1, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );

		//Stop
		tcp_input = 0x80;
		//Send command
		UART_write(uart1, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );

		//Backwards
		tcp_input = 0x01;
		//Send command
		UART_write(uart1, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );

		//Stop
		tcp_input = 0x80;
		//Send command
		UART_write(uart1, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );
	}
}

#endif /* TCP_TASK_H_ */
