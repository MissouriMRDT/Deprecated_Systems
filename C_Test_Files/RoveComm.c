// RoveComm.c
// Author: Gbenga Osibodu

#include "RoveComm.h"
#include <string.h>

#define ROVECOMM_VERSION 1
#define ROVECOMM_HEADER_LENGTH 8
#define ROVECOMM_PORT 11000

#define UDP_TX_PACKET_MAX_SIZE 1024
#define ROVECOMM_MAX_SUBSCRIBERS 5



uint8_t RoveCommBuffer[UDP_TX_PACKET_MAX_SIZE]; //roveWare
roveIP RoveCommSubscribers[ROVECOMM_MAX_SUBSCRIBERS]; 

static void RoveCommParseUdpMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags);
static void RoveCommControl(uint16_t* dataID, size_t* size, void* data, uint8_t* flags, roveIP IP);
static void RoveCommAddSubscriber(roveIP IP);

void RoveCommBegin(roveIP IP){
  roveNetworkingStart(IP);
  
  roveSocketListen(11000);
  
  int i;
  for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++) {
    RoveCommSubscribers[i] = INADDR_NONE;
  }
}

void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data) {
  uint8_t flags = 0;
  roveIP senderIP;
  
  *dataID = 0;
  *size = 0;
  
  if (RoveCommGetUdpMsg(senderIP, RoveCommBuffer) == true) {
    RoveCommParseUdpMsg(dataID, size, data, &flags);  
  }
}


static void RoveCommParseUdpMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags) {
  int protocol_version = RoveCommBuffer[0];
  switch (protocol_version) {
    case 1:
      *flags = RoveCommBuffer[3];
      *dataID = RoveCommBuffer[4];
      *dataID = (*dataID << 8) | RoveCommBuffer[5];
      *size = RoveCommBuffer[6];
      *size = (*size << 8) | RoveCommBuffer[7];
      
      memcpy(data, &(RoveCommBuffer[8]), *size);
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
  
  memcpy(&(RoveCommBuffer[8]), data, size);
  
  RoveCommSendPacket(destIP, destPort, buffer, packetSize);
}

void RoveCommSendMsg(uint16_t dataID, size_t size, const void* const data) {
  int i = 0; 
  
  while (i < ROVECOMM_MAX_SUBSCRIBERS) {
    if (RoveCommSubscribers[i] == INADDR_NONE) {
      RoveCommSendMsgTo(dataID, size, data, RoveCommSubscribers[i], ROVECOMM_PORT, 0);
    }
    i++;
  }
}

static void RoveCommAddSubscriber(roveIP IP) {
  int i = 0;
  
  while (i < ROVECOMM_MAX_SUBSCRIBERS && !(RoveCommSubscribers[i] == INADDR_NONE || RoveCommSubscribers[i] == IP)) {
    i++;
  } 
  
  if (i == ROVECOMM_MAX_SUBSCRIBERS)
    return;
    
  RoveCommSubscribers[i] = IP;
  return;
}

static void RoveCommControl(uint16_t* dataID, size_t* size, void* data, uint8_t* flags, roveIP IP) {
  if (*dataID < 0x00FF) {
    switch (*dataID) {
      case 0x0001:
        RoveCommAddSubscriber(IP);
        break;
      default:
        break;
    }
  }
}

