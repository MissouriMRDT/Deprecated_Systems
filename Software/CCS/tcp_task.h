/*
 * tcp_task.h
 *
 *  Created on: Feb 27, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "uarts.h"

extern Void tcp(UArg arg0, UArg arg1)
{
	// Init Uart 7
	UART_Handle uart7 = init_uart( 7 );

    char input;

    /* Loop forever echoing */
    while (TRUE) {
		UART_read(uart7, &input, 1);
    	System_printf("%c", input);
    	System_flush();
    }
}

#endif /* TCP_TASK_H_ */
