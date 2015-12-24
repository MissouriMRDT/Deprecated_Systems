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

void RoveCommGetUdpMsg(){
  struct sockaddr_in incoming;
  ssize_t recsize, sendsize;
  socklen_t fromlen;
  fd_set socketSet;
  struct timeval timeout;
  
  fromlen = sizeof(RoveComm.sa);
    FD_ZERO(&socketSet);
    FD_SET(RoveComm.sock,&socketSet);
    timeout.tv_usec = 0;
    timeout.tv_sec = 3;
    select(RoveComm.sock +1, &socketSet,NULL,NULL,&timeout);
    if (FD_ISSET(RoveComm.sock, &socketSet)){
      memcpy(&incoming, &RoveComm.sa, fromlen);
      
      recsize = recvfrom(RoveComm.sock, (void*)RoveComm.buffer, sizeof RoveComm.buffer, 0, (struct sockaddr*)&incoming, &fromlen);

      if (recsize < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      
      int i = 0;
      for (i=0; i<recsize; i++){
        printf("%X ", (uint8_t)RoveComm.buffer[i]);
      }
      printf("\n");
      printf("recsize: %d\n", (int)recsize);
      sendsize = sendto(RoveComm.sock, RoveComm.buffer, recsize, 0, (struct sockaddr*)&incoming, sizeof(incoming));
      printf("Sent %d bytes\n", (int)sendsize);
    } else
      printf("%s", "No packet\n");
}

