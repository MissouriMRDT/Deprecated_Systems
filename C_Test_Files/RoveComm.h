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

#ifndef ROVECOMM_H
#define ROVECOMM_H

#define ROVECOMM_VERSION 1
#define ROVECOMM_HEADER_LENGTH 8

struct RoveComm{
  int receiverSocket;
  struct sockaddr_in myAddr;
  uint8_t buffer[1024];
};

extern struct RoveComm RoveComm;

void RoveCommBegin();
void RoveCommGetUdpMsg(uint16_t* dataID, uint16_t* size, void* data);
void RoveCommParseUdpMsg(uint16_t* dataID, uint16_t* size, void* data, uint8_t* flags);


#endif

