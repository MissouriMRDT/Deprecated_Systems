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

void roveSocketListen(uint16_t port) {
  roveCommSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&roveCommAddr, 0, sizeof roveCommAddr);
  roveCommAddr.sin_family = AF_INET;
  roveCommAddr.sin_addr.s_addr = htonl(INADDR_ANY); //TODO Pass in some IP. will it work?
  roveCommAddr.sin_port = htons(port);
  
  if (-1 == bind(roveCommSocket, (struct sockaddr *)&roveCommAddr, sizeof roveCommAddr)) {
    perror("error bind failed");
    close(roveCommSocket);
    exit(EXIT_FAILURE);
  }
}

bool RoveCommSendPacket(in_addr_t destIP, uint16_t destPort, const uint8_t * const msg, size_t msgSize) {
  struct sockaddr_in destination;
  
  memset(&destination, 0, sizeof(destination));
  destination.sin_family = AF_INET;
  destination.sin_addr.s_addr = (destIP);
  destination.sin_port = htons(destPort);
  
  sendto(roveCommSocket, msg, msgSize, 0,(struct sockaddr*)&destination, sizeof(destination));
  return true;
}

bool RoveCommGetUdpMsg(void* buffer){
  struct sockaddr_in incoming;
  ssize_t recsize;
  socklen_t fromlen;
  fd_set socketSet;
  struct timeval timeout;
  
  
  fromlen = sizeof(roveCommAddr);
  FD_ZERO(&socketSet);
  FD_SET(roveCommSocket,&socketSet);
  timeout.tv_usec = 0;
  timeout.tv_sec = 0;
  select(roveCommSocket +1, &socketSet,NULL,NULL,&timeout);
  if (FD_ISSET(roveCommSocket, &socketSet)){
    memset(&incoming, 0, fromlen);
    
    recsize = recvfrom(roveCommSocket, buffer, sizeof buffer, 0, (struct sockaddr*)&incoming, &fromlen);

    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    
  } else {
    return false;
  }
  
  return true;
}
