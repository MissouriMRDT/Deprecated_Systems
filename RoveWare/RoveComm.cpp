// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Gbenga Osibodu
//
// Last Edit: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#ifdef __cplusplus
extern "C" {
#endif
#include "RoveComm.h"

//Standard C lib
#include <string.h>

//Todo Gbenga-> one line Api explanation
#define ROVECOMM_VERSION 1
#define ROVECOMM_HEADER_LENGTH 8
#define ROVECOMM_PORT 11000
#define UDP_TX_PACKET_MAX_SIZE 1500
uint8_t RoveCommBuffer[UDP_TX_PACKET_MAX_SIZE];

#define ROVECOMM_ACKNOWLEDGE_FLAG   1

#define ROVECOMM_PING               0x0001
#define ROVECOMM_PING_REPLY         0x0002
#define ROVECOMM_SUBSCRIBE          0x0003
#define ROVECOMM_UNSUBSCRIBE        0x0004
#define ROVECOMM_FORCE_UNSUBSCRIBE  0x0005
#define ROVECOMM_ACKNOWLEDGE_MSG    0x0006

//Todo Gbenga-> one line Api explanation
#define ROVECOMM_MAX_SUBSCRIBERS 5
#define ROVECOMM_ADD_SUBSCRIBER 0x0003
roveIP RoveCommSubscribers[ROVECOMM_MAX_SUBSCRIBERS];

void roveComm_SendMsgTo(uint16_t dataID, size_t size, const void* data, uint16_t seqNum, uint8_t flags, roveIP destIP, uint16_t destPort);
static void roveComm_ParseMsg(uint8_t* buffer, uint16_t* dataID, size_t* size, void* data, uint16_t* seqNum, uint8_t* flags);
static void roveComm_HandleSystemMsg(uint8_t* buffer, uint16_t* dataID, size_t* size, void* data, uint16_t* seqNum, uint8_t* flags, roveIP IP);
static bool roveComm_AddSubscriber(roveIP IP);

void roveComm_Begin(uint8_t IP_octet1, uint8_t IP_octet2, uint8_t IP_octet3, uint8_t IP_octet4)
{
  roveIP IP = roveEthernet_SetIP(IP_octet1, IP_octet2, IP_octet3, IP_octet4);

  roveEthernet_NetworkingStart(IP);

  roveEthernet_UdpSocketListen(ROVECOMM_PORT);

  int i;
  for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++)
  {
    RoveCommSubscribers[i] = ROVE_IP_ADDR_NONE;
  }
}

void roveComm_GetMsg(uint16_t* dataID, size_t* size, void* data)
{
  uint8_t flags = 0;
  uint16_t seqNum = 0;
  roveIP senderIP;

  *dataID = 0;
  *size = 0;

  if (roveEthernet_GetUdpMsg(&senderIP, RoveCommBuffer, sizeof(RoveCommBuffer)) == ROVE_ETHERNET_ERROR_SUCCESS)
  {
    roveComm_ParseMsg(RoveCommBuffer, dataID, size, data, &seqNum, &flags);
    roveComm_HandleSystemMsg(RoveCommBuffer, dataID, size, data, &seqNum, &flags, senderIP);
  }
}

static void roveComm_ParseMsg(uint8_t* buffer, uint16_t* dataID, size_t* size, void* data, uint16_t* seqNum, uint8_t* flags)
{
  int protocol_version = buffer[0];
  switch (protocol_version)
  {
    case 1:
      *seqNum = buffer[1];
      *seqNum = (*seqNum << 8) | buffer[2];
      *flags = buffer[3];
      *dataID = buffer[4];
      *dataID = (*dataID << 8) | buffer[5];
      *size = buffer[6];
      *size = (*size << 8) | buffer[7];

      memcpy(data, &(buffer[8]), *size);
  }
}

void roveComm_SendMsgTo(uint16_t dataID, size_t size, const void* data, uint16_t seqNum, uint8_t flags, roveIP destIP, uint16_t destPort)
{
  size_t packetSize = size + ROVECOMM_HEADER_LENGTH;
  uint8_t buffer[packetSize];

  buffer[0] = ROVECOMM_VERSION;
  buffer[1] = seqNum >> 8;
  buffer[2] = seqNum & 0x00FF;
  buffer[3] = flags;
  buffer[4] = dataID >> 8;
  buffer[5] = dataID & 0x00FF;
  buffer[6] = size >> 8;
  buffer[7] = size & 0x00FF;

  memcpy(&(buffer[8]), data, size);

  roveEthernet_SendUdpPacket(destIP, destPort, buffer, packetSize);
}

void roveComm_SendMsg(uint16_t dataID, size_t size, const void* data)
{
  int i = 0;

  for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++)
  {
    if (!(RoveCommSubscribers[i] == ROVE_IP_ADDR_NONE))
    {
      roveComm_SendMsgTo(dataID, size, data, 0x00FF, 0, RoveCommSubscribers[i], ROVECOMM_PORT);
    }
  }
}

static bool roveComm_AddSubscriber(roveIP IP)
{
  int i = 0;

  for (i=0; i<ROVECOMM_MAX_SUBSCRIBERS; i++)
  {
    if (RoveCommSubscribers[i] == IP)
    {
      return true;
    }
    if (RoveCommSubscribers[i] == ROVE_IP_ADDR_NONE)
    {
      RoveCommSubscribers[i] = IP;
      return true;
    }
  }

  return false;
}

static void roveComm_HandleSystemMsg(uint8_t* buffer, uint16_t* dataID, size_t* size, void* data, uint16_t* seqNum, uint8_t* flags, roveIP IP)
{
  if (*flags & ROVECOMM_ACKNOWLEDGE_FLAG != 0)
  {
    roveComm_SendMsgTo(ROVECOMM_ACKNOWLEDGE_MSG, sizeof(uint16_t), dataID, 0x00FF, 0, IP, ROVECOMM_PORT);
  }

  switch (*dataID)
  {
    case ROVECOMM_PING:
      roveComm_SendMsgTo(ROVECOMM_PING_REPLY, sizeof(uint16_t), seqNum, 0x00FF, 0, IP, ROVECOMM_PORT);
      break;
    case ROVECOMM_PING_REPLY:
      break;
    case ROVECOMM_SUBSCRIBE:
      roveComm_AddSubscriber(IP);
      break;
    case ROVECOMM_ACKNOWLEDGE_MSG:
      break;
    default:
      return;
  }
  *dataID = 0;
  *size = 0;
}

#ifdef __cplusplus
}
#endif
