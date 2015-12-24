#include "RoveComm.h"
/*When you call recv(), it will block until there is some data to 
read. If you want to not block, set the socket to non-blocking 
or check with select() or poll() to see if there is incoming data 
before calling recv() or recvfrom().
*/
int main(void)
{
  RoveCommBegin();
  

  for (;;) {
    RoveCommGetUdpMsg();
    sleep(1);
  }
}
