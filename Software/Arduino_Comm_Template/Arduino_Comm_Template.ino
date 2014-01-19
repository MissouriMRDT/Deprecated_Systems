#include <kernel.h>
#include <queue.h>
#include <sema.h>

/*
The following is a boilerplate sketch for Atmega 328 devices to connect to the motherboard.

This template uses ArdOS, a real time operating system for Arduino 
and includes the basic 
communication library for the motherboard. 
*/ 

// Writes OSticks to the serial port every 100ms.
void task1(void *p)
{
  char buffer[16];
  unsigned char sreg;
  while(1)
  {
    sprintf(buffer, "Time: %lu", OSticks());
    Serial.println(buffer);
    OSSleep(500);
  }
}

void task2(void* p){
        while(1){
            while(Serial.available()){
                Serial.write(Serial.read());
            }
            OSSleep(100);
        }
    }

#define NUM_TASKS    2

void setup()
{
  OSInit(NUM_TASKS);
  
  Serial.begin(115200);
  
  OSCreateTask(0, task1, NULL);
  OSCreateTask(1, task2, NULL);
  
  OSRun();
}

void loop()
{
  // Empty
}
