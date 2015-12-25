#include "RoveComm.h"
/*When you call recv(), it will block until there is some data to 
read. If you want to not block, set the socket to non-blocking 
or check with select() or poll() to see if there is incoming data 
before calling recv() or recvfrom().
*/
int main(void)
{
  uint16_t dataID;
  uint16_t dataSize;
  unsigned char data[30];
  
  RoveCommBegin();
  
  for (;;) {
    RoveCommGetUdpMsg(&dataID, &dataSize, data);
    
    if (dataID != 0) {
      printf("%s","Received Data\n");
      printf("DataID: %X\n", dataID);
      printf("Size:   %d\n", dataSize);
      
      int i;
      for (i=0; i<dataSize; i++){
        printf("%X ", data[i]);
      }
      printf("\n");
    }
    sleep(1);
  }
}
