#include <kernel.h>
#include <sema.h>

/*
 * semaDemo
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
    This program demonstrates the use of semaphores to coordinate tasks. Every 2 seconds task2 will release the semaphore that is holding task 1 back, and task1 will
    blink the LED at pin 9 rapidly 3 times and wait for task 2 to release its (task1's) semaphore again.
    
    This program also demonstrates the use of the task parameters.
    
    In addition we set up an interrupt handler for INT0 to switch the LED at pin 6 again using semaphores */
    
OSSema sem, sem1;

void task1(void *p)
{
  // Convert parameter p from a void * into an int.
  unsigned int count=(unsigned int) p;
  
  while(1)
  {
    // Wait for task 2 to release the semaphore
    OSTakeSema(&sem);
    
    // Blink rapidly for the number of times specified in parameter p
    for(int i=0; i<count; i++)
    {
      digitalWrite(9, HIGH);
      OSSleep(125);
      digitalWrite(9, LOW);
      OSSleep(125);
    }
  }
}

void task2(void *p)
{
  // Release task 1 every 2 seconds.
  while(1)
  {
    OSGiveSema(&sem);
    OSSleep(2000);
  }
}

void task3(void *p)
{
  // Just prints OSticks
  while(1)
  {
    Serial.println(OSticks());
    OSSleep(100);
  }
}

void task4(void *p)
{
  unsigned char flag=HIGH;
  
  // Waits for INT0's interrupt handler to release the interrupt to toggle the LED at pin 6.
  while(1)
  {
    OSTakeSema(&sem1);
    digitalWrite(6, flag);
    flag=!flag;
  }
}

// Interrupt handler for INT0
void myclick()
{
  OSGiveSema(&sem1);
}

#define NUM_TASKS  4

void setup()
{
  OSInit(NUM_TASKS);
  
  // Set up serial port, pins 6 and 9.
  Serial.begin(115200);
  pinMode(9, OUTPUT);  
  pinMode(6, OUTPUT);
  
  // Attach interrupt handler for INT0
  attachInterrupt(0, myclick, RISING);

  // Create binary semaphores with initial value of 0.  
  OSCreateSema(&sem, 0, 1);
  OSCreateSema(&sem1, 0, 1);
  
  // Create task 1, telling it to blink the LED at pin 9 rapidly 3 times each time the semaphore is released by task 2. Demonstrates the use
  // of the task parameters.
  OSCreateTask(0, task1, (void *) 3);
  
  // Create the other tasks.
  OSCreateTask(1, task2, NULL);
  OSCreateTask(2, task3, NULL);
  OSCreateTask(3, task4, NULL);
  OSRun();
}

void loop()
{
  // Does nothing
}

