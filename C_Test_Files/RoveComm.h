// RoveComm.h
// Author: Gbenga Osibodu

#ifndef ROVECOMM_H
#define ROVECOMM_H

#include "RoveEthernet.h"

#include <stdint.h>

void RoveCommBegin(uint8_t IP_octet1, uint8_t IP_octet2, uint8_t IP_octet3, uint8_t IP_octet4);
void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data);
void RoveCommSendMsg(uint16_t dataID, size_t size, const void* data);

#endif

