/*
 * tcp_task.h
 *
 *  Created on: Feb 27, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include "tcp.h"

extern Void tcp(UArg arg0, UArg arg1)
{
	while(1)
	{
		if (SPI_Read(S0_RX_RSR) != 0x0000)
		{
			System_printf("GOT DATA");
			System_flush();
		}
	}
}

#endif /* TCP_TASK_H_ */
