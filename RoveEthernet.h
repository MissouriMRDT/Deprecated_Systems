//Missouri University of Science and Technology: Mars Rover Design Team
#pragma once
#ifndef ROVEETHERNET_H_
#define ROVEETHERNET_H_

//C lib
#include <stdint.h>
#include <stddef.h>

#define ROVE_IP_ADDR_NONE 0

typedef unsigned int roveIP;

typedef enum
{
  ROVE_ETHERNET_ERROR_SUCCESS       =  0,
  ROVE_ETHERNET_ERROR_UNKNOWN       = -1,
  ROVE_ETHERNET_ERROR_SOCKET_IN_USE = -2,
  ROVE_ETHERNET_ERROR_HOST_DOWN     = -3,
  ROVE_ETHERNET_ERROR_WOULD_BLOCK   = -4
} roveEthernet_Error;

void roveEthernet_NetworkingStart(roveIP myIP);
roveEthernet_Error roveEthernet_UdpSocketListen(uint16_t port);
roveEthernet_Error roveEthernet_SendUdpPacket(roveIP destIP, uint16_t destPort, const uint8_t* msg, size_t msgSize);
roveEthernet_Error roveEthernet_GetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize);
roveIP roveEthernet_SetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);

#endif
