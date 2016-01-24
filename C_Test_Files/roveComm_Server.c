#include "RoveComm.h"

#include <stdio.h>

int main(void)
{
  uint16_t dataID;
  uint16_t dataSize;
  unsigned char data[30];
  
  RoveCommBegin(192,168,1,1);
  
  for (;;) {
    RoveCommGetMsg(&dataID, &dataSize, data);
    
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
