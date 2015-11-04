#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define ROVECOMM_VERSION 0x01

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
  
  sscanf(argv[1], "%X", (int*)&dataID);
  sscanf(argv[2], "%X", (int*)hexData);
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
  
  
  uint8_t buffer[1024];
 
  buffer[0] = verNum;
  buffer[1] = seqNum >> 8;
  buffer[2] = seqNum;
  buffer[3] = dataID >> 8;
  buffer[4] = dataID;
  buffer[5] = dataSize >> 8;
  buffer[6] = dataSize;
  
  int i;
  for (i=0; i<dataSize; i++)
    buffer[7+i] = hexData[dataSize -1 -i];
    
  /* create an Internet, datagram, socket using UDP */
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (-1 == sock) {
      /* if socket failed to initialize, exit */
      printf("Error Creating Socket\n");
      exit(EXIT_FAILURE);
    }
 
  /* Zero out socket address */
  memset(&sa, 0, sizeof sa);
  /* The address is IPv4 */
  sa.sin_family = AF_INET;
   /* IPv4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value */
  sa.sin_addr.s_addr = inet_addr(destinationIP);
  /* sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to our given or default port */
  sa.sin_port = htons(destinationPort);
 
  bytes_sent = sendto(sock, buffer, dataSize + 7, 0,(struct sockaddr*)&sa, sizeof sa);
  printf ("Sent %d bytes: ", bytes_sent);
  for (i=0; i<dataSize + 7; i++)
    printf("%X ", buffer[i]);
  printf("\n");
  
  if (bytes_sent < 0) {
    printf("Error sending packet: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  //bytes_sent = recvfrom(sock, (void *)buffer, sizeof(buffer), 0, (struct sockaddr*)&sa, &fromlen);
  //printf("%s\n", buffer);
 
  close(sock); /* close the socket */
  return 0;
}
