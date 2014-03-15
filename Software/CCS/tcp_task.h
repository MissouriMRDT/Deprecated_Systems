/*
 * tcp_task.h
 *
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "tcp.h"

extern Void tcp(UArg arg0, UArg arg1)
{
	UART_Handle uart0 = init_uart( 0 );
	UART_write(uart0, "Hey", 3);

	while(1)
	{
		uint32_t buf;

		buf = SPI_Read(S0_RX_RSR);
		System_printf("%x", buf);
		System_flush();

		UART_write(uart0, buf, 1);


	}
}

#endif /* TCP_TASK_H_ */
