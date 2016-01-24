// roveBoard.c for Linux
// Author: Gbenga Osibodu

#include "roveBoard.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void roveNetworkingStart(roveIP myIP) {}

roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) {
  uint32_t temp = 0;
  
  temp = first_octet << 24 | second_octet << 16 | third_octet << 8 | fourth_octet;
  return (roveIP)temp;
}

void roveUdpSocketListen(uint16_t port) {
  roveCommSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&roveCommAddr, 0, sizeof roveCommAddr);
  roveCommAddr.sin_family = AF_INET;
  roveCommAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  roveCommAddr.sin_port = htons(port);
  
  if (-1 == bind(roveCommSocket, (struct sockaddr *)&roveCommAddr, sizeof roveCommAddr)) {
    perror("error bind failed");
    close(roveCommSocket);
    exit(EXIT_FAILURE);
  }
}

bool RoveCommSendUdpPacket(in_addr_t destIP, uint16_t destPort, const uint8_t * msg, size_t msgSize) {
  struct sockaddr_in destination;
  
  memset(&destination, 0, sizeof(destination));
  destination.sin_family = AF_INET;
  destination.sin_addr.s_addr = (destIP);
  destination.sin_port = htons(destPort);
  
  sendto(roveCommSocket, msg, msgSize, 0,(struct sockaddr*)&destination, sizeof(destination));
  return true;
}

bool RoveCommGetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize){
  struct sockaddr_in incoming;
  ssize_t recsize;
  socklen_t fromlen = sizeof(roveCommAddr);
  
  recsize = recvfrom(roveCommSocket, buffer, bufferSize, MSG_DONTWAIT, (struct sockaddr*)&incoming, &fromlen);

  if (recsize < 0) {
    if ((errno == EWOULDBLOCK) || (errno == EAGAIN)) {
      return false;
    }
  }
  
  *senderIP = incoming.sin_addr.s_addr;
  return true;
}
