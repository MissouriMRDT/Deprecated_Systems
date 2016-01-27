// RoveEthernet.h for Linux
// Author: Gbenga Osibodu

#ifndef ROVEETHERNET_LINUX
#define ROVEETHERNET_LINUX

#include <stdint.h>
#include <netinet/in.h>
#include <stdbool.h>

#define ROVE_IP_ADDR_NONE INADDR_NONE

typedef enum 
{
  ROVE_ETHERNET_ERROR_SUCCESS       =  0,
  ROVE_ETHERNET_ERROR_UNKNOWN       = -1,
  ROVE_ETHERNET_ERROR_SOCKET_IN_USE = -2,
  ROVE_ETHERNET_ERROR_HOST_DOWN     = -3,
  ROVE_ETHERNET_ERROR_WOULD_BLOCK   = -4
} roveEthernet_Error;

typedef in_addr_t roveIP;

void roveNetworkingStart(roveIP myIP);
roveEthernet_Error roveUdpSocketListen(uint16_t port);
roveEthernet_Error RoveCommSendUdpPacket(roveIP destIP, uint16_t destPort, const uint8_t* msg, size_t msgSize);
roveEthernet_Error RoveCommGetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize);
roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);

#endif
