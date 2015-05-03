/*
 * roveStructTransfer.h
 *
 *  Created on: Mar 7, 2015
 *      Author: Connor Walsh
 */

#pragma once

#ifndef ROVESTRUCTTRANSFER_H_
#define ROVESTRUCTTRANSFER_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoverMotherboardMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

// used in Hardware tester, probably need to change to lowercase version
uint8_t CalcCheckSum(const void* my_struct, uint8_t size);

// XOR checksum calculation for a struct
uint8_t calcCheckSum(const void* my_struct, uint8_t size);

// Pre: buffer must be of size(my_struct) + 4 bytes (start bytes, size, and checksum)
int buildSerialStructMessage(void* my_struct, char* buffer);

// Pre: is a buffer where the received struct will be placed. The function returns true if the
// received value is valid and false if not. This is currently a BLOCKING call and will
// only return when either a whole message is read or an incorrect message was received and dropped
// In the future this may be changed to work as a nonblocking function or a different function
// may be written - Connor
bool recvSerialStructMessage(int deviceJack, char* buffer);

#endif /* ROVESTRUCTTRANSFER_H_ */
