/*
 * struct_xfer.h
 *
 *  Created on: May 6, 2014
 *      Author: Keenan Johnson
 */

//Jan 28 2015 included Keenans 2014 struct_xfer implementation

#ifndef STRUCT_XFER_H_
#define STRUCT_XFER_H_

#include <xdc/runtime/System.h>
#include "structs.h"
#include <stdint.h>
#include <stdbool.h>
#include <ti/drivers/UART.h>

enum peripheral_devices{motor_controller, bms, robotic_arm, tcp_cmd, drill, gripper, science_payload, gps, lighting_board, camera, power_board, test};

void send_struct(UART_Handle uart, void* my_struct, enum peripheral_devices device);

bool recv_struct( UART_Handle uart, void* my_struct, enum peripheral_devices device );

#endif /* STRUCT_XFER_H_ */
