/*
 * uart_0_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef DEBUG_CONSOLE_TASK_H_
#define DEBUG_CONSOLE_TASK_H_

#include <ti/sysbios/knl/Queue.h>
#include <string.h>

#include "../include/uarts.h"
#include "../include/queue_elements.h"

extern Queue_Handle debug_Q;

extern Void debug_console(UArg arg0, UArg arg1)
{
	while(1);

	// Putting this on the back burner
	/*
	// Queue element
	Debug_message* message_struct;

	// Uart0 debug path
	UART_Handle uart0 = init_uart( 0 );

	while(1)
	{
		// Dequeue the data and prints it
		while ( !Queue_empty( debug_Q ) )
		{
			// Implicit cast from (Queue_Elem *) to (Rec *)
			message_struct = Queue_dequeue( debug_Q );

			UART_writePolling(uart0, message_struct->message, 1);
		}
	}
	*/
}

#endif /* DEBUG_CONSOLE_TASK_H_ */
