// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Gbenga Osibodu
//
// Last Edit: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare

#ifndef ROVECOMM_H_
#define ROVECOMM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../RoveBoard/RoveBoardSockets.h"
#include <stdint.h>

void RoveCommBegin(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data);
void RoveCommSendMsg(uint16_t dataID, size_t size, const void* const data);
#ifdef __cplusplus
}
#endif
#endif // ROVECOMM_H_
