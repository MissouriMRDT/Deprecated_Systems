/*
 * tcp_task.h
 *
 */

#ifndef MUX_TEST_TASK_H_
#define MUX_TEST_TASK_H_

#include "../include/struct_xfer.h"
#include "../include/timing.h"

extern Void mux_test(UArg arg0, UArg arg1)
{
	extern UART_Handle uart4;

	struct drill_Controls _struct;

	mux_4(4);

	while(1)
	{
		//Send command
		send_struct(uart4, &_struct, drill);

	}
}

#endif /* TCP_TASK_H_ */
