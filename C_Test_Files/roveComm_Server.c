#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> /* for close() for socket */ 
#include <stdlib.h>
/*When you call recv(), it will block until there is some data to 
read. If you want to not block, set the socket to non-blocking 
or check with select() or poll() to see if there is incoming data 
before calling recv() or recvfrom().
*/
int main(void)
{
  // Create a UDP Socket
  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  struct sockaddr_in sa, incoming; 
  char buffer[1024];
  ssize_t recsize, sendsize;
  socklen_t fromlen;
  fd_set socketSet;
  struct timeval timeout;

  memset(&sa, 0, sizeof sa);
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  sa.sin_port = htons(11000);
  fromlen = sizeof(sa);

  if (-1 == bind(sock, (struct sockaddr *)&sa, sizeof sa)) {
    perror("error bind failed");
    close(sock);
    exit(EXIT_FAILURE);
  }
  

  for (;;) {
    FD_ZERO(&socketSet);
    FD_SET(sock,&socketSet);
    timeout.tv_usec = 0;
    timeout.tv_sec = 3;
    select(sock +1, &socketSet,NULL,NULL,&timeout);
    if (FD_ISSET(sock, &socketSet)){
      memcpy(&incoming, &sa, fromlen);
      
      recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&incoming, &fromlen);

      if (recsize < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
      }
      
      int i = 0;
      for (i=0; i<recsize; i++){
        printf("%X ", (uint8_t)buffer[i]);
      }
      printf("\n");
      printf("recsize: %d\n", (int)recsize);
      sa.sin_port = htons(11000);
      sendsize = sendto(sock, buffer, recsize, 0, (struct sockaddr*)&incoming, sizeof(incoming));
      printf("Sent %d bytes\n", (int)sendsize);
      sleep(1);
    } else
      printf("%s", "No packet\n");
  }
}
