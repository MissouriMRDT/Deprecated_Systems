// RoveComm.h
// Author: Gbenga Osibodu

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef ROVECOMM_H
#define ROVECOMM_H

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
};

extern struct RoveComm RoveComm;

void RoveCommBegin(int port);
void RoveCommGetUdpMsg(uint16_t* dataID, uint16_t* size, void* data);
void RoveCommParseUdpMsg(uint16_t* dataID, uint16_t* size, void* data, uint8_t* flags);
bool RoveCommSendPacket(in_addr_t destIP, int destPort, uint8_t* msg, int msgSize);
void RoveCommSendMsgTo(uint16_t dataID, uint16_t size, void* data, in_addr_t destIP, int destPort, uint8_t flags);
void RoveCommSendMsg(uint16_t dataID, uint16_t size, void* data);

#endif

