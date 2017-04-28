//Programmers: Chris Dutcher™ & Jimmy Haviland
//March 22, 2017
//Missouri S&T  Mars Rover Design Team
//Science Board Main program

//TODO: Clean up includes (move to energia's folder, not github's)
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
void setup() {}


void loop() {
  //All important pre-loop setup is done here
  initialize();//TODO: Move initialization into setup(), use the globals

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

    //TODO: Switch to switch case
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
          float soilTemp = instantSoilTemp();
          roveComm_SendMsg(0x721, sizeof(soilTemp), &soilTemp);
        }
        else if(commandData == temp_OFF)
        {
          sensor_enable[0] = false;
        }
        else if (commandData == moisture_ON)
        {
          sensor_enable[1] = true;
          float soilMoist = instantSoilHumidity();
          roveComm_SendMsg(0x723, sizeof(soilMoist), &soilMoist);
          //TODO: send this data back to RED
          //TODO: copy millis setup from science.ino to get continuous readings from sensors
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
      roveComm_SendMsg(0x721, sizeof(soilTemp), &soilTemp);
     }
    if(sensor_enable[1]) //soil moisture
    {
      float soilMoist = instantSoilHumidity();
      roveComm_SendMsg(0x721, sizeof(soilMoist), &soilMoist);
    }
   }//end if millis (send sensor data every ¼ second
  }//End while
}//End loop()

//Functions:
//TODO: Define pins as constants in header

//All important pre-loop setup is done here outside of setup, for some reason
void initialize()
{
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  Serial.begin(9600);
  //Arm Initialization
    pinMode(PF_0, OUTPUT);
  //main motor
   pinMode(PL_5, OUTPUT);//IN1
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

   //init sensor pins
  pinMode(tempPin, INPUT);
  pinMode(moistPin, INPUT);
  
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
  digitalWrite(PL_5, HIGH);//IN1
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
  digitalWrite(PL_5, LOW);//IN1
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
  digitalWrite(PL_5, LOW); //IN1   
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
  digitalWrite(PL_5, HIGH); //IN1   
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
