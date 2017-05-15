//Programmers: Chris Dutcher™ & Jimmy Haviland
//March 22, 2017
//Missouri S&T  Mars Rover Design Team
//Science Board Main program

//TODO: Clean up includes (move to energia's folder, not github's)
#include "config.h"
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

//Stores the time value since the most recent sensor information send
uint32_t sensorTimer = 0;

//Determines which sensors will send data back
bool sensor_enable[2] = {false,false};

//Device objects


//All non-important pre-loop setup is done here
void setup() 
{
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  Serial.begin(9600);
  //Arm Initialization
   pinMode(LEDPin, OUTPUT);
  //main motor
   pinMode(arm_in_1, OUTPUT);//IN1
   pinMode(arm_in_2, OUTPUT);//IN2
   pinMode(arm_decay, OUTPUT);//decay
   pinMode(arm_nFault, INPUT); //THE ONLY INPUT//nFault
   pinMode(arm_nSleep, OUTPUT);//nSLeep
   pinMode(arm_nReset, OUTPUT);//nReset
   pinMode(arm_I0, OUTPUT);//I0
   pinMode(arm_I1, OUTPUT);//I1
   pinMode(arm_I2, OUTPUT);//I2
   pinMode(arm_I3, OUTPUT);//I3
   pinMode(arm_I4, OUTPUT);//I4
   
  digitalWrite(arm_I4, HIGH);//I4
  digitalWrite(arm_I3, HIGH);//I3
  digitalWrite(arm_I2, HIGH);//I2
  digitalWrite(arm_I1, HIGH);//I1
  digitalWrite(arm_I0, HIGH);//I0
  digitalWrite(arm_decay, HIGH);//Decay
  digitalWrite(arm_nReset, HIGH);//disable Reset Mode

  //Drill Initialization
  pinMode(drill_pin_1, OUTPUT);//pin one of drill H bridge
  pinMode(drill_pin_2, OUTPUT);//pin two of drill H bridge 

   //init sensor pins
  pinMode(tempPin, INPUT);
  pinMode(moistPin, INPUT);
  
  Serial.println("Initialized!");
  }


void loop() {
  //All important pre-loop setup is done here

  //TESTING to see if i can send anything to RED at all
  float testData = 77;
  roveComm_SendMsg(0x729, sizeof(testData), &testData);
  
  //Main execution loop
  while(1)
  {
    //Resets the message to nothing
    commandSize = 0;
    commandId = 0;
    commandData = 0;
    //Receives a command from base station and stores the message
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

     if(commandId == ScienceArmDrive)
       {
         if(commandData>=armForward)
           motorOn();
         else if(commandData<=armReverse)
           motorReverse();
         else// if(commandData==armOff)
           motorCoast();
       }
       else if(commandId == ScienceArmPosition)
       {
         //Some positional arm movement function, if we even get that far       
       }
       else if(commandId == ScienceDrillDrive)
       {
         if(commandData>=DrillF)
         {
           drillForward();
         }
         else if(commandData<=DrillR)
         {
           drillReverse();
         }
         else
           drillCoast();
       }
       else if (commandId == ScienceSoilSensors)
       {
        if(commandData == temp_ON)
        {
          sensor_enable[0] = true;
          //float soilTemp = instantSoilTemp();
          //roveComm_SendMsg(0x72B, sizeof(soilTemp), &soilTemp);
          //Serial.print("Soil temp = ");
          //Serial.print(soilMoist);
          //Serial.print("\n");
        }
        else if(commandData == temp_OFF)
        {
          sensor_enable[0] = false;
        }
        else if (commandData == moisture_ON)
        {
          sensor_enable[1] = true;
          //float soilMoist = instantSoilHumidity();
          //roveComm_SendMsg(0x72C, sizeof(soilMoist), &soilMoist);
          //Serial.print("Soil moisture = ");
          //Serial.print(soilMoist);
          //Serial.print("\n");
        }
        else if (commandData == moisture_OFF)
        {
          sensor_enable[1] = false;
        }
       }
    }//end if there was a message, else.....
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
        kill();
        Serial.println("Watch out dog!!!!!!");
        watchdogTimer_us = 0;
      }//End if
    }//End else no message

   if((millis()-sensorTimer)>250)
  {
    //Serial.println("Checking Sensors");
     sensorTimer=millis();
    if(sensor_enable[0]) //Soil Temp
     {
      float soilTemp = instantSoilTemp();
      roveComm_SendMsg(ScienceSoilTemp, sizeof(soilTemp), &soilTemp);
     }
    if(sensor_enable[1]) //soil moisture
    {
      float soilMoist = instantSoilHumidity();
      roveComm_SendMsg(ScienceSoilMoisture, sizeof(soilMoist), &soilMoist);
    }
   }//end if millis (send sensor data every ¼ second
  }//End while
}//End loop()

//Functions:
/*
 *   Arm Functions
 */


void motorOn()
{
  digitalWrite(arm_nSleep, HIGH);//nSLeep
  digitalWrite(arm_decay, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor current speed
  digitalWrite(arm_I4, HIGH);//I4
  digitalWrite(arm_I3, HIGH);//I3
  digitalWrite(arm_I2, HIGH);//I2
  digitalWrite(arm_I1, HIGH);//I1
  digitalWrite(arm_I0, HIGH);//I0

  //one high, one low. swap for other direction
  digitalWrite(arm_in_1, HIGH);//IN1
  digitalWrite(arm_in_2, LOW);//IN2
  digitalWrite(LEDPin, HIGH);//LED 
}

void motorReverse()
{
  digitalWrite(arm_nSleep, HIGH);//nSLeep
  digitalWrite(arm_decay, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor current speed
  digitalWrite(arm_I4, HIGH);//I4
  digitalWrite(arm_I3, HIGH);//I3
  digitalWrite(arm_I2, HIGH);//I2
  digitalWrite(arm_I1, HIGH);//I1
  digitalWrite(arm_I0, HIGH);//I0

  //one high, one low. swap for other direction
  digitalWrite(arm_in_1, LOW);//IN1
  digitalWrite(arm_in_2, HIGH);//IN2
  digitalWrite(LEDPin, HIGH);//LED
}


void motorCoast()
{
  digitalWrite(arm_nSleep, LOW);//nSLeep
  digitalWrite(arm_decay, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor curent speed
  digitalWrite(arm_I4, LOW);//I4
  digitalWrite(arm_I3, HIGH);//I3
  digitalWrite(arm_I2, LOW);//I2
  digitalWrite(arm_I1, HIGH);//I1
  digitalWrite(arm_I0, HIGH);//I0

  //brake = both high
  //coast = both low
  digitalWrite(arm_in_1, LOW); //IN1   
  digitalWrite(arm_in_2, LOW);//IN2
  digitalWrite(LEDPin, LOW);//LED
}

void motorBrake()
{
  digitalWrite(arm_nSleep, LOW);//nSLeep
  digitalWrite(arm_decay, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor curent speed
  digitalWrite(arm_I4, LOW);//I4
  digitalWrite(arm_I3, HIGH);//I3
  digitalWrite(arm_I2, LOW);//I2
  digitalWrite(arm_I1, HIGH);//I1
  digitalWrite(arm_I0, HIGH);//I0

  //brake = both high
  //coast = both low
  digitalWrite(arm_in_1, HIGH); //IN1   
  digitalWrite(arm_in_2, HIGH);//IN2
  digitalWrite(LEDPin, LOW);//LED
}

/*
 *   DRILL Functions 
 */

void drillForward()
{
   digitalWrite(drill_pin_1, HIGH);
   digitalWrite(drill_pin_2, LOW);
}

void drillReverse()
{
    digitalWrite(drill_pin_1, LOW);
    digitalWrite(drill_pin_2, HIGH);
}

void drillCoast()
{
  digitalWrite(drill_pin_1, LOW);
  digitalWrite(drill_pin_2, LOW);
}

void kill()
{
  //add digitalWrite(..) to disable the pins that turn off the arm and the drill (or just call motorCoast() and drillCoast()?)
  drillCoast();
  motorCoast();
}

//Returns one soil temperature reading
float instantSoilTemp()
{
  const int analogRes = 4095;
  float voltage = analogRead(tempPin) * 5;
  voltage = voltage / analogRes;
  float degC = (voltage - 0.5) * 100.0;
  float degF = (degC * 1.8) + 32;
  Serial.print("soil temp sensor read val celsius: ");
  Serial.print(degC);
  Serial.print("\n");
  Serial.print("soil temp sensor read val farenheit: ");
  Serial.print(degF);
  Serial.print("\n");
  Serial.print("raw temp data = ");
  Serial.print(analogRead(tempPin));
  Serial.print("\n");
  Serial.print("raw temp voltaghe = ");
  Serial.print(voltage);
  Serial.print("\n");
  return degF;
}

//Returns one reading of the soil humidity
float instantSoilHumidity()
{
  int reading = analogRead(moistPin);
  float voltage = ((reading * 5.0) / 4095);
  Serial.print("soil moisture sensor value read: ");
  Serial.print(voltage);
  Serial.print("\n");
  return voltage; //returning raw voltage for now
                  //TODO: convert to measurement of moisture
}
