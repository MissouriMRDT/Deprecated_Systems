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

#ifndef ROVECOMM
#define ROVECOMM

struct RoveComm{
  int sock;
  struct sockaddr_in sa;
  char buffer[1024];
};

extern struct RoveComm RoveComm;

void RoveCommBegin();
void RoveCommGetUdpMsg();


#endif

