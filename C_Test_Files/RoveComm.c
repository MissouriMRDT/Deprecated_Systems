// RoveComm.c
// Author: Gbenga Osibodu

#include "RoveComm.h"

struct RoveComm RoveComm;

void RoveCommBegin(){
  RoveComm.sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

  memset(&RoveComm.sa, 0, sizeof RoveComm.sa);
  RoveComm.sa.sin_family = AF_INET;
  RoveComm.sa.sin_addr.s_addr = htonl(INADDR_ANY);
  RoveComm.sa.sin_port = htons(11000);
  
  if (-1 == bind(RoveComm.sock, (struct sockaddr *)&RoveComm.sa, sizeof RoveComm.sa)) {
    perror("error bind failed");
    close(RoveComm.sock);
    exit(EXIT_FAILURE);
  }
}

void RoveCommGetUdpMsg(uint16_t* dataID, uint16_t* size, void* data){
  struct sockaddr_in incoming;
  ssize_t recsize, sendsize;
  socklen_t fromlen;
  fd_set socketSet;
  struct timeval timeout;
  
  *dataID = 0;
  *size = 0;
  
  fromlen = sizeof(RoveComm.sa);
  FD_ZERO(&socketSet);
  FD_SET(RoveComm.sock,&socketSet);
  timeout.tv_usec = 0;
  timeout.tv_sec = 0;
  select(RoveComm.sock +1, &socketSet,NULL,NULL,&timeout);
  if (FD_ISSET(RoveComm.sock, &socketSet)){
    memcpy(&incoming, &RoveComm.sa, fromlen);
    
    recsize = recvfrom(RoveComm.sock, (void*)RoveComm.buffer, sizeof RoveComm.buffer, 0, (struct sockaddr*)&incoming, &fromlen);

    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    
    
    RoveCommParseUdpMsg( dataID, size, data);
    
      sendsize = sendto(RoveComm.sock, RoveComm.buffer, recsize, 0, (struct sockaddr*)&incoming, sizeof(incoming));
      
  }
}


void RoveCommParseUdpMsg(uint16_t* dataID, uint16_t* size, void* data) {
  int protocol_version = RoveComm.buffer[0];
  switch (protocol_version) {
    case 1:
      *dataID = RoveComm.buffer[3];
      *dataID = (*dataID << 8) | RoveComm.buffer[4];
      *size = RoveComm.buffer[5];
      *size = (*size << 8) | RoveComm.buffer[6];
      int i;
      for (i=0; i < *size; i++) {
        ((uint8_t*)data)[i] = RoveComm.buffer[i + ROVECOMM_HEADER_LENGTH];
      }
  }
}

