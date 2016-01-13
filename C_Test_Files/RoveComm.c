// RoveComm.c
// Author: Gbenga Osibodu

#include "RoveComm.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROVECOMM_VERSION 1
#define ROVECOMM_HEADER_LENGTH 8
#define ROVECOMM_PORT 11000

#define UDP_TX_PACKET_MAX_SIZE 1024
#define ROVECOMM_MAX_SUBSCRIBERS 5



struct RoveComm{
  int socket;
  struct sockaddr_in myAddr;
  uint8_t buffer[UDP_TX_PACKET_MAX_SIZE];
  in_addr_t subscribers[ROVECOMM_MAX_SUBSCRIBERS];
} RoveComm;

static void RoveCommParseUdpMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags);
static bool RoveCommSendPacket(in_addr_t destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize);
static void RoveCommGetUdpMsg(uint16_t* dataID, size_t* size, void* data);



void RoveCommBegin(){
  RoveComm.socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&RoveComm.myAddr, 0, sizeof RoveComm.myAddr);
  RoveComm.myAddr.sin_family = AF_INET;
  RoveComm.myAddr.sin_addr.s_addr = htonl(INADDR_ANY); //TODO Pass in some IP. will it work?
  RoveComm.myAddr.sin_port = htons(ROVECOMM_PORT);
  
  if (-1 == bind(RoveComm.socket, (struct sockaddr *)&RoveComm.myAddr, sizeof RoveComm.myAddr)) {
    perror("error bind failed");
    close(RoveComm.socket);
    exit(EXIT_FAILURE);
  }
  
  int i;
  for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++) {
    RoveComm.subscribers[i] = INADDR_NONE;
  }
}

void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data) {
  RoveCommGetUdpMsg(dataID, size, data);
}

static void RoveCommGetUdpMsg(uint16_t* dataID, size_t* size, void* data){
  struct sockaddr_in incoming;
  ssize_t recsize;
  socklen_t fromlen;
  fd_set socketSet;
  struct timeval timeout;
  
  uint8_t flags = 0;
  
  *dataID = 0;
  *size = 0;
  
  fromlen = sizeof(RoveComm.myAddr);
  FD_ZERO(&socketSet);
  FD_SET(RoveComm.socket,&socketSet);
  timeout.tv_usec = 0;
  timeout.tv_sec = 0;
  select(RoveComm.socket +1, &socketSet,NULL,NULL,&timeout);
  if (FD_ISSET(RoveComm.socket, &socketSet)){
    memset(&incoming, 0, fromlen);
    
    recsize = recvfrom(RoveComm.socket, (void*)RoveComm.buffer, sizeof RoveComm.buffer, 0, (struct sockaddr*)&incoming, &fromlen);

    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    
    RoveCommParseUdpMsg(dataID, size, data, &flags);
  }
}

static void RoveCommParseUdpMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags) {
  int protocol_version = RoveComm.buffer[0];
  switch (protocol_version) {
    case 1:
      *flags = RoveComm.buffer[3];
      *dataID = RoveComm.buffer[4];
      *dataID = (*dataID << 8) | RoveComm.buffer[5];
      *size = RoveComm.buffer[6];
      *size = (*size << 8) | RoveComm.buffer[7];
      
      memcpy(data, &(RoveComm.buffer[8]), *size);
  }
}

static bool RoveCommSendPacket(in_addr_t destIP, uint16_t destPort, const uint8_t * const msg, size_t msgSize) {
  struct sockaddr_in destination;
  
  memset(&destination, 0, sizeof(destination));
  destination.sin_family = AF_INET;
  destination.sin_addr.s_addr = (destIP);
  destination.sin_port = htons(destPort);
  
  sendto(RoveComm.socket, msg, msgSize, 0,(struct sockaddr*)&destination, sizeof(destination));
  return true;
}

void RoveCommSendMsgTo(uint16_t dataID, size_t size, const void* const data, in_addr_t destIP, uint16_t destPort, uint8_t flags) {
  size_t packetSize = size + ROVECOMM_HEADER_LENGTH;
  uint8_t buffer[packetSize];
  
  buffer[0] = ROVECOMM_VERSION;
  buffer[1] = 0x00;
  buffer[2] = 0xFF;
  buffer[3] = flags;
  buffer[4] = dataID >> 8;
  buffer[5] = dataID & 0x00FF;
  buffer[6] = size >> 8;
  buffer[7] = size & 0x00FF;
  
  memcpy(&(RoveComm.buffer[8]), data, size);
  
  RoveCommSendPacket(destIP, destPort, buffer, packetSize);
}

void RoveCommSendMsg(uint16_t dataID, size_t size, const void* const data) {
  int i = 0; 
  
  while (i < ROVECOMM_MAX_SUBSCRIBERS) {
    if (RoveComm.subscribers[i] == INADDR_NONE) {
      RoveCommSendMsgTo(dataID, size, data, RoveComm.subscribers[i], ROVECOMM_PORT, 0);
    }
    i++;
  }
}
