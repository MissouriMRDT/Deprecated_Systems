#include <kernel.h>
#include <queue.h>
#include <sema.h>

/*
 * bigExample 
 *
 
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


// Reads the potentiometer at analog input 0 every 10 ms and places it onto the message queue.
#define QLEN  8
int qbuf[QLEN];
OSQueue msg;

// Reads the message queue and controls the brightness of the LED at PWM output 11.
void task2(void *p)
{
  unsigned int  val;
  while(1)
  {
    val=(unsigned int) OSDequeue(&msg);
    analogWrite(11, val);
  }
}

void task3(void *p)
{
  unsigned int val, remap;
  while(1)
  {
    val=analogRead(0);
    remap=map(val, 0, 1023, 0, 255);
    OSEnqueue(remap, &msg);
    OSSleep(5);
  }
}


OSSema sem;

  unsigned char flag=HIGH;

// Toggles the LED at pin 9 every time the push button is pressed.
void task4(void *p)
{
  while(1)
  {
    OSTakeSema(&sem);
    digitalWrite(9, flag);
    flag=!flag;
  }
}

void task5(void *p)
{
  unsigned int pause=(unsigned int) p;
  while(1)
  {
    digitalWrite(6, HIGH);
    OSSleep(pause);
    digitalWrite(6, LOW);
    OSSleep(pause);
  }
}

// Interrupt service routine for external interrupt INT0 (digital pin 2)

void int0handler()
{
  OSGiveSema(&sem);
}

#define NUM_TASKS    5

void setup()
{
  OSInit(NUM_TASKS);
  
  Serial.begin(115200);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  attachInterrupt(0, int0handler, RISING);
  
  OSCreateSema(&sem, 0, 1);
  OSCreateQueue(qbuf, QLEN, &msg);
  
  OSCreateTask(0, task1, NULL);
  OSCreateTask(1, task2, NULL);
  OSCreateTask(2, task3, NULL);
  OSCreateTask(3, task4, NULL);
  OSCreateTask(4, task5, (void *) 250);
  
  OSRun();
}

void loop()
{
  // Empty
}



