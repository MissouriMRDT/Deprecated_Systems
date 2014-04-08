/*
 * queue_elements.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef QUEUE_ELEMENTS_H_
#define QUEUE_ELEMENTS_H_

#include <ti/sysbios/knl/Queue.h>

typedef struct _Debug_message {
	Queue_Elem elem;
	char* message;
} Debug_message;

#endif /* QUEUE_ELEMENTS_H_ */
