// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Gbenga Osibodu
//
// Last Edit: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare

#ifndef ROVEETHERNET_H_
#define ROVEETHERNET_H_
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <socketndk.h>

#define ROVE_IP_ADDR_NONE 0

typedef unsigned int roveIP;

typedef enum
{
    ROVE_ETHERNET_ERROR_SUCCESS = 0
    ,ROVE_ETHERNET_ERROR_UNKOWN = -1
    //,roveBoard_ERROR_KNOWN = -2
} roveEthernet_Error;


int roveCommSocket;
struct sockaddr_in roveCommAddr;
/*
void roveNetworkingStart(roveIP myIP);
void roveUdpSocketListen(uint16_t port);
bool RoveCommSendUdpPacket(roveIP destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize);
bool RoveCommGetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize);
roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
*/
#endif // ROVEETHERNET_H_
