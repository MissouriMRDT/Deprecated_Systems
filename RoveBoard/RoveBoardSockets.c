// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Gbenga Osibodu
//
// Last Edit: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare

#include "RoveBoardSockets.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
//#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void roveNetworkingStart(roveIP myIP) {}



roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) {
  roveIP temp;

  temp = first_octet << 24 | second_octet << 16 | third_octet << 8 | fourth_octet;
  return temp;
}



void roveUdpSocketListen(uint16_t port) {
  roveCommSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

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



bool RoveCommSendUdpPacket(roveIP destIP, uint16_t destPort, const uint8_t * const msg, size_t msgSize) {
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
