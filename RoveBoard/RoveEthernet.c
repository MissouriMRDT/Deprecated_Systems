// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Gbenga Osibodu
//
// Last Edit: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare

#include "RoveEthernet.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
//#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int roveCommSocket;
struct sockaddr_in roveCommAddr;

void roveEthernet_NetworkingStart(roveIP myIP) {}

roveIP roveEthernet_SetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet)
{
  uint32_t temp = 0;

  temp = first_octet << 24 | second_octet << 16 | third_octet << 8 | fourth_octet;
  return (roveIP)temp;
}

roveEthernet_Error roveEthernet_UdpSocketListen(uint16_t port)
{
  roveCommSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&roveCommAddr, 0, sizeof roveCommAddr);
  roveCommAddr.sin_family = AF_INET;
  roveCommAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  roveCommAddr.sin_port = htons(port);

  if (-1 == bind(roveCommSocket, (struct sockaddr *)&roveCommAddr, sizeof roveCommAddr))
  {
    close(roveCommSocket);

    if (errno == EADDRINUSE)
    {
      return ROVE_ETHERNET_ERROR_SOCKET_IN_USE;
    }
    else
    {
      return ROVE_ETHERNET_ERROR_UNKNOWN;
    }
  }

  return ROVE_ETHERNET_ERROR_SUCCESS;
}

roveEthernet_Error roveEthernet_SendUdpPacket(roveIP destIP, uint16_t destPort, const uint8_t * msg, size_t msgSize)
{
  struct sockaddr_in destination;
  ssize_t sendSize;

  memset(&destination, 0, sizeof(destination));
  destination.sin_family = AF_INET;
  destination.sin_addr.s_addr = (destIP);
  destination.sin_port = htons(destPort);

  sendSize = sendto(roveCommSocket, msg, msgSize, 0,(struct sockaddr*)&destination, sizeof(destination));
  if (sendSize < 0)
  {
    if (errno == EHOSTDOWN)
    {
      return ROVE_ETHERNET_ERROR_HOST_DOWN;
    }
    else
    {
      return ROVE_ETHERNET_ERROR_UNKNOWN;
    }
  }

  return ROVE_ETHERNET_ERROR_SUCCESS;
}

roveEthernet_Error roveEthernet_GetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize)
{
  struct sockaddr_in incoming;
  ssize_t recsize;
  socklen_t fromlen = sizeof(roveCommAddr);

  recsize = recvfrom(roveCommSocket, buffer, bufferSize, MSG_DONTWAIT, (struct sockaddr*)&incoming, &fromlen);

  if (recsize < 0)
  {
    if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
    {
      return ROVE_ETHERNET_ERROR_WOULD_BLOCK;
    }
    else
    {
      return ROVE_ETHERNET_ERROR_UNKNOWN;
    }
  }

  *senderIP = incoming.sin_addr.s_addr;
  return ROVE_ETHERNET_ERROR_SUCCESS;
}



#ifdef __cplusplus
}
#endif
