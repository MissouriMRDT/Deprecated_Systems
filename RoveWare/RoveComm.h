// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifndef ROVECOMM_H_
#define ROVECOMM_H_

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//Standard C lib
#include <stdio.h>
#include <stdint.h>

//Rover Wrappers for hardware specific ip network access
#include "RoveBoard/RoveM4C1294/RoveEthernet.h"

// == Public API ========
//
//Todo Gbenga-> one line Api explanation
void roveComm_Begin(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);

//Todo Gbenga-> one line Api explanation
void roveComm_GetMsg(uint16_t* dataID, size_t* size, void* data);

//Todo Gbenga-> one line Api explanation
void roveComm_SendMsg(uint16_t dataID, size_t size, const void* const data);

#ifdef __cplusplus
}
#endif

#endif // ROVECOMM_H_
