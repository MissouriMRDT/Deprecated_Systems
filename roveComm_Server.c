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
  struct sockaddr_in sa; 
  char buffer[1024];
  ssize_t recsize, sendsize;
  socklen_t fromlen;

  memset(&sa, 0, sizeof sa);
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  sa.sin_port = htons(7654);
  fromlen = sizeof(sa);

  if (-1 == bind(sock, (struct sockaddr *)&sa, sizeof sa)) {
    perror("error bind failed");
    close(sock);
    exit(EXIT_FAILURE);
  }

  for (;;) {
    recsize = recvfrom(sock, (void*)buffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen);
    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    sendsize = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&sa, sizeof(sa));
    printf("recsize: %d\n ", (int)recsize);
    sleep(1);
    printf("datagram: %.*s\n", (int)recsize, buffer);
  }
}
