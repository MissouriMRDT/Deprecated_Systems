#include <kernel.h>
#include <sema.h>


/*
 * ISRDemo 
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

OSSema sema;
unsigned char flag=HIGH;

/* 
	This program demonstrates the use of semaphores from within ISRs.
	
	It assumes that LEDs are connected to pins 6 and 9, and that a pushbutton has been connected to pull pin 2 high when pressed 
	The LED at pin 9 will flash at a rate of 4 times per second, while the LED at pin 6 will be toggled whenever you press the push button. Task
        3 sends OSticks() to the serial port, which shows the number of milliseconds since OSRun was called.
*/

void task1(void *p)
{
	
	while(1)
	{		
		OSTakeSema(&sema);
                digitalWrite(6, flag);
	}
}

void task2(void *p)
{
	while(1)
	{
		digitalWrite(9, HIGH);
		OSSleep(125);
		digitalWrite(9, LOW);
		OSSleep(125);		
	}
}

void task3(void *p)
{
  char buffer[16];
  
  while(1)
  {
    sprintf(buffer,"%lu", OSticks());
    Serial.println(buffer);
    OSSleep(125);
  }
}

void int0ISR()
{
  flag=!flag;
  OSGiveSema(&sema);
}

#define NUM_TASKS  3

void setup()
{
	OSInit(NUM_TASKS);
        attachInterrupt(0, int0ISR, RISING);
        Serial.begin(115200);
        
	pinMode(9, OUTPUT);
	pinMode(6, OUTPUT);
	
	// Create a binary semaphore with initial value 0
	OSCreateSema(&sema, 0, 1);		
	OSCreateTask(0, task1, NULL);
	OSCreateTask(1, task2, NULL);
        OSCreateTask(2, task3, NULL);
	OSRun();
}

void loop()
{
  // Does nothing

}
