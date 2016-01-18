// RoveComm.c
// Author: Gbenga Osibodu

#include "RoveComm.h"
#include <string.h>

#define ROVECOMM_VERSION 1
#define ROVECOMM_HEADER_LENGTH 8
#define ROVECOMM_PORT 11000

#define UDP_TX_PACKET_MAX_SIZE 1500
#define ROVECOMM_MAX_SUBSCRIBERS 5

#define ROVECOMM_ADD_SUBSCRIBER 0x0003



uint8_t RoveCommBuffer[UDP_TX_PACKET_MAX_SIZE];
roveIP RoveCommSubscribers[ROVECOMM_MAX_SUBSCRIBERS]; 

void RoveCommSendMsgTo(uint16_t dataID, size_t size, const void* const data, roveIP destIP, uint16_t destPort, uint8_t flags);
static void RoveCommParseMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags);
static void RoveCommHandleSystemMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags, roveIP IP);
static bool RoveCommAddSubscriber(roveIP IP);

void RoveCommBegin(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) {
  roveIP IP = roveSetIP(first_octet, second_octet, third_octet, fourth_octet);
  
  roveNetworkingStart(IP);
  
  roveUdpSocketListen(ROVECOMM_PORT);
  
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
  
  if (RoveCommGetUdpMsg(&senderIP, RoveCommBuffer, sizeof(RoveCommBuffer)) == true) {
    RoveCommParseMsg(dataID, size, data, &flags);  
    RoveCommHandleSystemMsg(dataID, size, data, &flags, senderIP);
  }
}

static void RoveCommParseMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags) {
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
  
  memcpy(&(buffer[8]), data, size);

  RoveCommSendUdpPacket(destIP, destPort, buffer, packetSize);
}

void RoveCommSendMsg(uint16_t dataID, size_t size, const void* const data) {
  int i = 0; 
  
  for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++) {
    if (!(RoveCommSubscribers[i] == INADDR_NONE)) {
      RoveCommSendMsgTo(dataID, size, data, RoveCommSubscribers[i], ROVECOMM_PORT, 0);
    }
  }
}

static bool RoveCommAddSubscriber(roveIP IP) {
  int i = 0;

  for (i=0; i<ROVECOMM_MAX_SUBSCRIBERS; i++) {
    if (RoveCommSubscribers[i] == IP) {
      return true;
    }
    if (RoveCommSubscribers[i] == INADDR_NONE) {
      RoveCommSubscribers[i] = IP;
      return true;
    }
  }
  
  return false;
}

static void RoveCommHandleSystemMsg(uint16_t* dataID, size_t* size, void* data, uint8_t* flags, roveIP IP) {
  switch (*dataID) {
    case ROVECOMM_ADD_SUBSCRIBER:
      RoveCommAddSubscriber(IP);
      break;
    default:
      return;
  }
  *dataID = 0;
  *size = 0;
}

