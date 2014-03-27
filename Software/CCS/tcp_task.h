/*
 * tcp_task.h
 *
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "tcp.h"

extern Void tcp(UArg arg0, UArg arg1)
{
	UART_Handle uart = init_uart(5 );

	uint8_t tcp_input;

	//Send to first set of motor controllers
	mux_7(18);

	/*
	while(1)
	{
		UART_write(uart, "h", 1);
	}
	*/

	while(1)
	{
		//Read byte from TCP
		//UART_read(uart7, &tcp_input, 1);

		//Go foreward
		tcp_input = 0xFF;
		//Send command
		UART_write(uart, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );

		//Stop
		tcp_input = 0x80;
		//Send command
		UART_write(uart, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );

		//Backwards
		tcp_input = 0x01;
		//Send command
		UART_write(uart, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );

		//Stop
		tcp_input = 0x80;
		//Send command
		UART_write(uart, &tcp_input, 1);
		SysCtlDelay( SysCtlClockGet()  );
	}
}

#endif /* TCP_TASK_H_ */
