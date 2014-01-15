#include <kernel.h>
#include <queue.h>

/*
 * queueDemo
 *
 * Created: 5/21/2013 8:56:57 PM
 *  Author: dcstanc
    	Copyright (C) 2013 Colin Tan
    	
    	
    	This file is part of ArdOS.

    	ArdOS is free software: you can redistribute it and/or modify
    	it under the terms of the GNU Lesser General Public License as published by
    	the Free Software Foundation, either version 3 of the License, or
    	(at your option) any later version.

    	ArdOS is distributed in the hope that it will be useful,
    	but WITHOUT ANY WARRANTY; without even the implied warranty of
    	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    	GNU Lesser General Public License for more details.

    	You should have received a copy of the GNU Lesser General Public License
    	along with ArdOS.  If not, see <http://www.gnu.org/licenses/>.

 */ 

/* In this demo we assume a pot connected to analog input 0. Task 2 will read from the pot and write to a queue
   task1Q, which Task 1 will read and use it to control the brightness of an LED connected to pin 9. It will pass the
   value to Task 3 using task3Q, which will print it onto the serial port 115200 bps */
 
#define BUFLEN  8

int q1buffer[BUFLEN], q2buffer[BUFLEN];
OSQueue t1Queue, t3Queue;

void task1(void *p)
{
  unsigned int val; 
  unsigned char mapval;
  
  while(1)
  {
    val=(unsigned int) OSDequeue(&t1Queue);
    mapval=map(val, 0, 1023, 0, 255);
    analogWrite(9, mapval);
    OSEnqueue(mapval, &t3Queue);
    OSSleep(50);
  }
}

void task2(void *p)
{
  unsigned int val;
  
  while(1)
  {
    val=analogRead(0);
    OSEnqueue(val, &t1Queue);
    OSSleep(50);
  }
}

void task3(void *p)
{
  unsigned int val;
  char buffer[32];
  while(1)
  {
    val=OSDequeue(&t3Queue);
    sprintf(buffer, "Analog value: %u", val);
    Serial.println(buffer);
    OSSleep(50);
  }
}

#define NUM_TASKS    3

void setup()
{
  OSInit(NUM_TASKS);
  Serial.begin(115200);
  
  // Create a FIFO queue. To do so create an array of integers, then pass the array as
  // parameter 1, the length of the array as parameter 2, and the queue variable as parameter
  // 3 to OSCreateQueue
  OSCreateQueue(q1buffer, BUFLEN, &t1Queue);
  OSCreateQueue(q2buffer, BUFLEN, &t3Queue);
  
  // Create the tasks
  OSCreateTask(0, task1, NULL);
  OSCreateTask(1, task2, NULL);
  OSCreateTask(2, task3, NULL);
  OSRun();
  
}

void loop()
{
  // Nothing
}
