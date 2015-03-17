/*
 * roveStructTransfer.h
 *
 *  Created on: Mar 7, 2015
 *      Author: Connor Walsh
 */

#pragma once

#ifndef ROVESTRUCTTRANSFER_H_
#define ROVESTRUCTTRANSFER_H_

enum peripheral_devices{motor_controller, bms, robotic_arm, tcp_cmd, drill, gripper, science_payload, gps, lighting_board, camera, power_board, test};

// XOR checksum calculation for a struct
uint8_t CalcCheckSum(const void* my_struct, uint8_t size);

// Pre: buffer must be of size(my_struct) + 4 bytes (start bytes, size, and checksum)
void buildSerialStructMessage(void* my_struct, enum peripheral_devices device, char* buffer);

// Pre: is a buffer containing a message in easyTransfer form
bool ParseStructSerial(void* out_struct, enum peripheral_devices device, char* buffer);

#endif /* ROVESTRUCTTRANSFER_H_ */
