// RoveComm.c
// Author: Gbenga Osibodu

#include "RoveComm.h"

struct RoveComm RoveComm;

void RoveCommBegin(){
  RoveComm.receiverSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&RoveComm.myAddr, 0, sizeof RoveComm.myAddr);
  RoveComm.myAddr.sin_family = AF_INET;
  RoveComm.myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  RoveComm.myAddr.sin_port = htons(11000);
  
  if (-1 == bind(RoveComm.receiverSocket, (struct sockaddr *)&RoveComm.myAddr, sizeof RoveComm.myAddr)) {
    perror("error bind failed");
    close(RoveComm.receiverSocket);
    exit(EXIT_FAILURE);
  }
}

void RoveCommGetUdpMsg(uint16_t* dataID, uint16_t* size, void* data){
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
  FD_SET(RoveComm.receiverSocket,&socketSet);
  timeout.tv_usec = 0;
  timeout.tv_sec = 0;
  select(RoveComm.receiverSocket +1, &socketSet,NULL,NULL,&timeout);
  if (FD_ISSET(RoveComm.receiverSocket, &socketSet)){
    memcpy(&incoming, &RoveComm.myAddr, fromlen);
    
    recsize = recvfrom(RoveComm.receiverSocket, (void*)RoveComm.buffer, sizeof RoveComm.buffer, 0, (struct sockaddr*)&incoming, &fromlen);

    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    
    RoveCommParseUdpMsg(dataID, size, data, &flags);
  }
}


void RoveCommParseUdpMsg(uint16_t* dataID, uint16_t* size, void* data, uint8_t* flags) {
  int protocol_version = RoveComm.buffer[0];
  switch (protocol_version) {
    case 1:
      *flags = RoveComm.buffer[3];
      *dataID = RoveComm.buffer[4];
      *dataID = (*dataID << 8) | RoveComm.buffer[5];
      *size = RoveComm.buffer[6];
      *size = (*size << 8) | RoveComm.buffer[7];
      int i;
      for (i=0; i < *size; i++) {
        ((uint8_t*)data)[i] = RoveComm.buffer[i + ROVECOMM_HEADER_LENGTH];
      }
  }
}

