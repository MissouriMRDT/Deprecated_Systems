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

extern void roveComm_SendMsgTo(uint16_t dataID, size_t size, const void* const data, uint16_t seqNum, uint8_t flags, roveIP destIP, uint16_t destPort);

int main(int argc, char* argv[])
{
  uint8_t flags=0, verNum = 1;
  uint16_t dataID, dataSize, seqNum = 0x00FF;
  char destinationIP[15] = "192.168.1.51";
  char hexData[sizeof(long)];
  int destinationPort = 11000;
  int temp = 0;
  
  if(argc < 3 || argc > 6) 
  {
    printf("Usage: %s DataID Data [Dest_IP [Flags [Sequence Number]]]\n", argv[0]);
    printf("Check the RoveComm readme for more info\n");
    exit(EXIT_FAILURE);
  }
  
  sscanf(argv[1], "%i", &temp); dataID = temp;
  sscanf(argv[2], "%lX", (long*)hexData);
  dataSize = (strlen(argv[2])+1) /2; //the number of bytes of data should be have of what was entered
  
  if(argc > 3) 
  {
    sscanf(argv[3], "%s", destinationIP);
  }
  
  if(argc > 4) 
  {
    sscanf(argv[4], "%i", &temp); flags = temp;
  }

  if(argc > 5) 
  {
    sscanf(argv[5], "%i", &temp); seqNum = temp;
  }
  
  roveComm_Begin(192,168,1,1);
  *((long*)hexData) = htonl(*((long*)hexData));
  roveComm_SendMsgTo(dataID, dataSize, hexData, seqNum, flags, inet_addr(destinationIP), destinationPort);
  
  return 0;
}
