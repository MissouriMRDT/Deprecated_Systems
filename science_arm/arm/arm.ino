//Programmers: Chris Dutcher & Jimmy Haviland
//March 22, 2017
//Missouri S&T  Mars Rover Design Team
//Science Board Main program

#include "arm.h"
#include "RoveEthernet.h"
#include <SPI.h>
#include "Servo.h"
#include <Wire.h>



//Variable declaration:
//Stores the result (if any) of commands received and executed (not used)
CommandResult result;
//Stores the value received from base station, of which command to execute
uint16_t commandId;
//Stores the size of the commandData received from base station
size_t commandSize;
//Stores the command arguement, sent by base station, to send through to the command
int16_t commandData;
//Stores the value of watchdog, which times out after not receiving a command from base station, to terminate any potential dangerous operations
uint32_t watchdogTimer_us = 0;


//Device objects


//All non-important pre-loop setup is done here
void setup() {}


void loop() {
  //All important pre-loop setup is done here
  initialize();

  //Main execution loop
  while(1)
  {
    //Resets the message to nothing
    commandSize = 0;
    commandId = 0;
    commandData = 0;
    //Receives a command form base station and stores the message
    roveComm_GetMsg(&commandId, &commandSize, &commandData);
    
    //Checks the message for an actual command
    if(commandId != 0)
    {
      //We have received a command, so watchdog is reset
      watchdogTimer_us = 0;

      Serial.println(commandId);
      Serial.println(commandData);
      Serial.println(commandSize);
      Serial.println("");

       //Science Arm Drive
       if(commandId == 0x710)//TODO: Wrong commandID, this is for science board
       {   
         if(commandData==18)
             motorOn();
         else if(commandData==19)
             motorReverse();
         else if(commandData==20)
             motorCoast();
       }
       //Science Arm Position
       else if(commandId == 0x711)//TODO: Wrong commandID, this is for science board
       {
          if(commandData==0)
             drillForward();
          else if(commandData==2)
             drillCoast();
          else if(commandData==4)
             drillReverse();
       }
    }
    
    //Future Code 
    /*
     if(commandId == ScienceArmDrive)
       {
         if(commandData==armForward)
           motorOn();
         else if(commandData==armReverse)
           motorReverse();
         else if(commandData==armOff)
           motorCoast();
       }
       else if(commandId == ScienceArmPosition)
       {
         //Some positional arm movement function, if we even get that far       
       }
       else if(commandId == ScienceDrillDrive)
       {
         if(commandData==DrillF)
           drillForward();
         else if(commandData==DrillR)
           drillReverse();
         else if(commandData==DrillOff)
           drillCoast();
       }
       */
 
    
    else //No message was received and we send sensor data
    {
      //Delay before we check for another command from base station
      uint8_t microsecondDelay = 10;
      delayMicroseconds(microsecondDelay);
      watchdogTimer_us += microsecondDelay;
      //Once we have spend two seconds delaying for commands, we terminate potentially dangerous (to astronaughts or the rover) operations and keep them disabled until we receive a command again
      if(watchdogTimer_us >= WATCHDOG_TIMEOUT_US)
      {
        //End dangerous operations here
        Serial.println("Watch out dog!!!!!!");
        watchdogTimer_us = 0;
      }//End if
    }//End else
  }//End while
}//End loop()

//Functions:

//All important pre-loop setup is done here outside of setup, for some reason
void initialize()
{
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  Serial.begin(9600);
  //Arm Initialization
    pinMode(PF_0, OUTPUT);
  //main motor
   pinMode(PD_1, OUTPUT);//IN1
   pinMode(PD_0, OUTPUT);//IN2
   pinMode(PN_2, OUTPUT);//decay
   pinMode(PL_2, INPUT); //THE ONLY INPUT//nFault
   pinMode(PN_3, OUTPUT);//nSLeep
   pinMode(PL_3, OUTPUT);//nReset
   pinMode(PL_4, OUTPUT);//I0
   pinMode(PH_3, OUTPUT);//I1
   pinMode(PG_0, OUTPUT);//I2
   pinMode(PH_2, OUTPUT);//I3
   pinMode(PF_3, OUTPUT);//I4
   //
  digitalWrite(PF_3, HIGH);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, HIGH);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0
  digitalWrite(PN_2, HIGH);//Decay
  digitalWrite(PL_3, HIGH);//disable Reset Mode

  //Drill Initialization
  pinMode(PB_3, OUTPUT);//pin one of drill H bridge
  pinMode(PB_2, OUTPUT);//pin two of drill H bridge  
  
  Serial.println("Initialized!");
}

/*
 *   Arm Functions
 */


void motorOn()
{
  digitalWrite(PN_3, HIGH);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor current speed
  digitalWrite(PF_3, HIGH);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, HIGH);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //one high, one low. swap for other direction
  digitalWrite(PD_1, HIGH);//IN1
  digitalWrite(PD_0, LOW);//IN2
  digitalWrite(PF_0, HIGH);//LED 
}

void motorReverse()
{
  digitalWrite(PN_3, HIGH);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor current speed
  digitalWrite(PF_3, HIGH);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, HIGH);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //one high, one low. swap for other direction
  digitalWrite(PD_1, LOW);//IN1
  digitalWrite(PD_0, HIGH);//IN2
  digitalWrite(PF_0, HIGH);//LED
}


void motorCoast()
{
  digitalWrite(PN_3, LOW);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor curent speed
  digitalWrite(PF_3, LOW);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, LOW);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //brake = both high
  //coast = both low
  digitalWrite(PD_1, LOW); //IN1   
  digitalWrite(PD_0, LOW);//IN2
  digitalWrite(PF_0, LOW);//LED
}

void motorBrake()
{
  digitalWrite(PN_3, LOW);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor curent speed
  digitalWrite(PF_3, LOW);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, LOW);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //brake = both high
  //coast = both low
  digitalWrite(PD_1, HIGH); //IN1   
  digitalWrite(PD_0, HIGH);//IN2
  digitalWrite(PF_0, LOW);//LED
}

/*
 *   DRILL Functions 
 */

void drillForward()
{
   digitalWrite(PB_3, HIGH);
   digitalWrite(PB_2, LOW);
}

void drillReverse()
{
    digitalWrite(PB_3, LOW);
    digitalWrite(PB_2, HIGH);
}

void drillCoast()
{
  digitalWrite(PB_3, LOW);
  digitalWrite(PB_2, LOW);
}

void kill()
{
  //add digitalWrite(..) to disable the pins that turn off the arm and the drill (or just call motorCoast() and drillCoast()?)
}

