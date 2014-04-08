/*
 * tcp_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "../include/queue_elements.h"

extern Queue_Handle debug_Q;

Debug_message test;

extern Void tcp_connection(UArg arg0, UArg arg1)
{
	test.message = "hey";

	while(1)
	{
		Queue_enqueue(debug_Q, &(test.elem));
	}
}

#endif /* TCP_TASK_H_ */
