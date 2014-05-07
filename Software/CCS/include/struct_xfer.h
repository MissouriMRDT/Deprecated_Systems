/*
 * struct_xfer.h
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 */

#ifndef STRUCT_XFER_H_
#define STRUCT_XFER_H_

#include <stdint.h>
#include <ti/drivers/UART.h>

void send_struct(UART_Handle uart, void* my_struct);

#endif /* STRUCT_XFER_H_ */
