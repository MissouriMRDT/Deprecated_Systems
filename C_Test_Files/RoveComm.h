// RoveComm.h
// Author: Gbenga Osibodu

#ifndef ROVECOMM_H
#define ROVECOMM_H

#include "roveBoard.h"

#include <stdint.h>

void RoveCommBegin(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data);
void RoveCommSendMsg(uint16_t dataID, size_t size, const void* const data);

#endif

