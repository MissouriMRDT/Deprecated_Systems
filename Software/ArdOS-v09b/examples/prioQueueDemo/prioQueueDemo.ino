#include <kernel.h>
#include <queue.h>
#include <sema.h>
#include <mutex.h>

/*
 * prioQueueDemo 
 *
 * Created: 4/18/2013 7:22:55 PM
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


/*
    This program demonstrates the use of prioritized message queues. Task 2 enqueues four numbers with priorities while task 1 dequeues them in priority order. Note however
    that if task 1 dequeues as fast as task 2 enqueues, then the messages will come out in FIFO order. To demonstrate the prioritization semaphores are used to prevent task 1
    from dequeueing until task 2 completes 
    
    You can view the sorted queue on the Serial Monitor set to 115200 bps.
    
    */
    
#define BUFLEN  4
OSQueue prioQ;
TPrioNode data[BUFLEN];
OSMutex mutex;

OSSema sem1, sem2;

void printSerial(unsigned int buffer[])
{
  while(1)
  {
    OSTakeMutex(&mutex);
    for(int i=0; i<BUFLEN; i++)
      Serial.println(buffer[i], DEC);
      
    Serial.println("--------------");
    Serial.println();
    OSSleep(10);
    OSGiveMutex(&mutex);
  }
}

void task1(void *p)
{
  unsigned int array[BUFLEN];
  
  while(1)
  {
    // Wait for Task 2 to finish enqueueing.
    OSTakeSema(&sem1);

    // Print out the enqueued messages.

    for(int i=0; i<BUFLEN; i++)
      array[i]=(unsigned int) OSDequeue(&prioQ);

    printSerial(array);
    
    // Let task 2 start enqueueing again.
    OSGiveSema(&sem2);
   }
}

void task2(void *p)
{
  while(1)
  {
    // Call priority enqueue. First argument is the data, second is priority (0 = highest), third is the queue to enqueue to
    // This loop enqueues from BUFLEN-1 to 0 with priority numbers BUFLEN-1 to 0, i.e. with from lowest priority to highest.
    // the priority queue will re-sort so that the numbers are dequeued from 0 to BUFLEN-1.
    
    for(int i=BUFLEN-1; i>=0; i--)
      OSPrioEnqueue(i, i, &prioQ);

    // Allow task 1 to dequeue
    OSGiveSema(&sem1);    
    // And wait for task 1 to complete dequeueing
    OSTakeSema(&sem2);

    
  }
}

#define NUMTASKS  2

void setup()
{
  OSInit(NUMTASKS);
  Serial.begin(115200);
  pinMode(9, OUTPUT);
  OSSetStackSize(60);
  
  // To create a priority queue create an array of TPrioNode, then call 
  // OSCreatePrioQueue with this array, the size of the array, and the 
  // queue to be initialized.
  OSCreatePrioQueue(data, BUFLEN, &prioQ);
  
  // Create semaphores.
  OSCreateSema(&sem1, 0, 1);
  OSCreateSema(&sem2, 0, 1);
  OSCreateMutex(&mutex);
  
  // Create tasks.
  OSCreateTask(0, task1, NULL);
  OSCreateTask(1, task2, NULL);
  OSRun();
}

void loop()
{
}
