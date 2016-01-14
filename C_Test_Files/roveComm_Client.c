#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "RoveComm.h"

#define ROVECOMM_VERSION 1

int main(int argc, char* argv[])
{
  int sock;
  struct sockaddr_in sa;
  int bytes_sent, fromlen;
  uint8_t verNum = ROVECOMM_VERSION;
  uint16_t dataID, dataSize, seqNum = 0x0000;
  char destinationIP[15] = "192.168.1.51";
  char hexData[512];
  int destinationPort = 11000;
  
  if(argc < 3 || argc > 6) {
    printf("Usage: %s DataID Data [Dest_IP [Dest_Port [Sequence Number]]]\n", argv[0]);
    printf("Check the RoveComm readme for more info\n");
    exit(EXIT_FAILURE);
  }
  
  sscanf(argv[1], "%i", (int*)&dataID);
  sscanf(argv[2], "%lX", (long*)hexData);
  dataSize = (strlen(argv[2])+1) /2; //the number of bytes of data should be have of what was entered
  
  if(argc > 3) {
    sscanf(argv[3], "%s", destinationIP);
  }
  
  if(argc > 4) {
    sscanf(argv[4], "%d", &destinationPort);
  }

  if(argc > 5) {
    sscanf(argv[5], "%X", (int*)&seqNum);
  }
  
  RoveCommBegin();
  
  RoveCommSendMsgTo(dataID, dataSize, hexData, inet_addr(destinationIP), destinationPort, 0);
  
  return 0;
}
