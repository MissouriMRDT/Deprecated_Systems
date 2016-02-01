// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifndef ROVECOMM_H_
#define ROVECOMM_H_
#pragma once

//Standard C lib
#include <stdio.h>
#include <stdint.h>

//Rover Wrappers for hardware specific ip network access
#include "../RoveBoard/RoveEthernet.h"



// == Public API ========
//
//Todo Gbenga-> one line Api explanation
void RoveCommBegin(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);

//Todo Gbenga-> one line Api explanation
void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data);

//Todo Gbenga-> one line Api explanation
void RoveCommSendMsg(uint16_t dataID, size_t size, const void* const data);

#endif // ROVECOMM_H_
