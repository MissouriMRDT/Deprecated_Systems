// RoveComm.c
// Author: Gbenga Osibodu

#include "RoveComm.h"
#include <string.h>

#define ROVECOMM_VERSION 1
#define ROVECOMM_HEADER_LENGTH 8
#define ROVECOMM_PORT 11000

#define UDP_TX_PACKET_MAX_SIZE 1024
#define ROVECOMM_MAX_SUBSCRIBERS 5



struct RoveComm{
  uint8_t buffer[UDP_TX_PACKET_MAX_SIZE]; //roveWare
  roveIP subscribers[ROVECOMM_MAX_SUBSCRIBERS]; 
} RoveComm;

static void RoveCommParseUdpMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags);



void RoveCommBegin(){
  roveIP temp;
  roveNetworkingStart(temp);
  
  roveSocketListen(11000);
  
  int i;
  for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++) {
    RoveComm.subscribers[i] = INADDR_NONE;
  }
}

void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data) {
  uint8_t flags = 0;
  
  *dataID = 0;
  *size = 0;
  
  if (RoveCommGetUdpMsg(RoveComm.buffer) == true) {
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



void RoveCommSendMsgTo(uint16_t dataID, size_t size, const void* const data, roveIP destIP, uint16_t destPort, uint8_t flags) {
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
