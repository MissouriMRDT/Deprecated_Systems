//Programmers: Chris Dutcher & Jimmy Haviland
//Febuary 24, 2017
//Missouri S&T  Mars Rover Design Team
//Science Board Main program

#include "science.h"
#include "RoveEthernet.h"
#include <SPI.h>
#include "Servo.h"
#include <Wire.h>
//#include "BMP085_t.h"   This file is causing compilation problems


//Variable declaration:
//Stores the result (if any) of commands received and executed
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

//Device objects
//Energia standard servo device class from Servo.h
Servo flap, carousel;
//Pressure sensor object, currently uses problematic file
//BMP085<0> PSensor;

//All non-important pre-loop setup is done here
void setup() {}


void loop() {
  //All important pre-loop setup is done here
  initialize();
  bool sensor_enable[7] = {false,false,false,false,false,false,false}; //Determines which sensors will send data back

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

       //Checks the value of the command, and if applicable, executes it
       if(commandId == ScienceCommand)
       {
        //Switch case
        switch(commandData) {
        case sensorAllEnable:
        for(int i=0;i<7;i++)
        {
          sensor_enable[i]=true;
        }
        break;
        case sensorAllDisable:
        for(int i=0;i<7;i++)
        {
          sensor_enable[i]=false;
        }
        break;
        case sensor1Enable:
        sensor_enable[0]=true;
        break;
        case sensor1Disable:
        sensor_enable[0]=false;
        break;
        case sensor2Enable:
        sensor_enable[1]=true;
        break;
        case sensor2Disable:
        sensor_enable[1]=false;
        break;
        case sensor3Enable:
        sensor_enable[2]=true;
        break;
        case sensor3Disable:
        sensor_enable[2]=false;
        break;
        case sensor4Enable:
        sensor_enable[3]=true;
        break;
        case sensor4Disable:
        sensor_enable[3]=false;
        break;
        case sensor5Enable:
        sensor_enable[4]=true;
        break;
        case sensor5Disable:
        sensor_enable[4]=false;
        break;
        case sensor6Enable:
        sensor_enable[5]=true;
        break;
        case sensor6Disable:
        sensor_enable[5]=false;
        break;
        case sensor7Enable:
        sensor_enable[6]=true;
        break;
        case sensor7Disable:
        sensor_enable[6]=false;
        break;
        case laserOn:
        turnOnLaser();
        break;
        case laserOff:
        turnOffLaser();
        break;
        case flapOpen:
        openFlap();
        break;
        case flapClose:
        closeFlap();
        break;
        case spectro:
        spectrometer();
        break;
         }//End Switch   
       }
       else if(commandId == ScienceCarousel)//Carousel
       {
         rotateCarousel(commandData);
       }
    }
    else //No message was received and we send sensor data
    {
       //millis()   returns milliseconds since program started, can use like a watch dog, but for sensors
       //Temporary sensor variable, future variable will be altered by sensor functions before being sent
       float sensorTestData = 100.0;
       //check for which sensors to record, and then send through rovecomm
    if((millis()-sensorTimer)>250)
    {
      //Serial.println("Checking Sensors");
       sensorTimer=millis();
       if(sensor_enable[0])//AirTemp
       {
        sensorTestData = 100.0;
        roveComm_SendMsg(0x720, sizeof(sensorTestData), &sensorTestData); 
       }
       if(sensor_enable[1]) //AirHumidity
       {
        sensorTestData = 101.0;
        roveComm_SendMsg(0x721, sizeof(sensorTestData), &sensorTestData);
       }
       if(sensor_enable[2]) //Soil Temp
       {
        sensorTestData = 102.0;
        roveComm_SendMsg(0x722, sizeof(sensorTestData), &sensorTestData);
       }
       if(sensor_enable[3]) //Soil Humidity
       {
        sensorTestData = 103.0;
        roveComm_SendMsg(0x723, sizeof(sensorTestData), &sensorTestData);
       }
       if(sensor_enable[4]) //Methane
       {
        sensorTestData = 104.0;
        roveComm_SendMsg(0x728, sizeof(sensorTestData), &sensorTestData);
       }
       if(sensor_enable[5]) //UV Intensity
       {
        sensorTestData = 105.0;
        roveComm_SendMsg(0x729, sizeof(sensorTestData), &sensorTestData);
       }
       if(sensor_enable[6]) //Pressure
       {
        sensorTestData = 106.0;
        roveComm_SendMsg(0x72A, sizeof(sensorTestData), &sensorTestData);
       }        
    }
      //Delay before we check for another command from base station
      uint8_t microsecondDelay = 10;
      delayMicroseconds(microsecondDelay);
      watchdogTimer_us += microsecondDelay;
      //Once we have spend two seconds delaying for commands, we terminate potentially dangerous (to astronaughts or the rover) operations and keep them disabled until we receive a command again
      if(watchdogTimer_us >= WATCHDOG_TIMEOUT_US)
      {
        //End dangerous operations here
        //Serial.println("Watch out dog!!!!!!");
        watchdogTimer_us = 0;
      }

    }//End else
  }//End while
}//End loop()

//Functions:

//All important pre-loop setup is done here outside of setup, for some reason
void initialize()
{
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  Serial.begin(9600);
  pinMode(PD_5, OUTPUT);//laser
  pinMode(PF_0, OUTPUT);//LED
  pinMode(PD_2, INPUT);//photodiode1
  pinMode(PD_3, INPUT);//photodiode2
  flap.attach(PL_0);
  carousel.attach(PL_2);
  //PSensor.begin();//Initalize pressure Sensor (non-compiling)
  /************************************
  * Spectrometer motor Initiaslization
  /***********************************/
  pinMode(PM_5, OUTPUT);//in 1
  pinMode(PB_3, OUTPUT);//in 2
  
  Serial.println("Initialized!");
}


//Spectometer sub-routine TODO: roveComm_SendMsg(...) the data
void spectrometer()
{
   Serial.println("Start spectro routine.");
   uint16_t photo1, photo2;
   //turn on motor, run for 5s before continuing
   //direction is a bool! change true/false for direction
   spectroMotorForward();   
   //do nothing except leave motor on for 5s
   delay(5000);
   //turn on laser
   turnOnLaser();   
   //laser is on, motor should still be going?
   //keep laser and motor on for 30s
   int timer = 0;
   //loop takes analog readings 
   //delays for 1/8 second
   //should repeat until roughly 30s have passed.
   while (timer <= 30000)
   {
    //read photo diodes
    photo1 = analogRead(PD_0);
    photo2 = analogRead(PD_1);
    //print data
    Serial.println("Data for photodiodes 1 & 2, respectively:");
    Serial.println(photo1);
    Serial.println(photo2);
    //roveComm_SendMsg(...) here
    timer += 125;
    delay(125); 
   }
   //turn off laser
   turnOffLaser();
   //turn off motor
   spectroMotorOff();
   //delay couple seconds
   delay(2000);
   //return motor to start position
   //opposite direction than what was called earlier!
   spectroMotorReverse();
   //wait 35s for motor to return
   delay(35000);
   //stop motor again
   spectroMotorOff();
   //wait 10 seconds before repeating the loop
   delay(10000); 
   return;
}

//Turns on the spectrometer laser
void turnOnLaser()
{
  Serial.println("Laser on");
  //turn on laser by setting pin to High
  digitalWrite(PD_5, HIGH);//laser
  digitalWrite(PF_0, HIGH);//LED
  return;
}

//Turns off the spectormeter laser
void turnOffLaser()
{
  Serial.println("Laser off");
  //turn off laser by setting pin to low
  digitalWrite(PD_5, LOW);//laser
  digitalWrite(PF_0, LOW);//led
  return;
}

//Opens the sample cache cover flap
void openFlap()
{
  Serial.println("Opening flap.");
  //Flap should open as it goes away from 180
  flap.write(0);
  //flap.writeMicroseconds(1);
  //delay(5000);//Delay to let servo catch up
  return;
}

//Closes the sample cache cover flap
void closeFlap()
{
  Serial.println("Closing flap.");
  //Flap should close at 180
  flap.write(90);
  //flap.writeMicroseconds(2);
  //delay(5000);//Delay to let servo catch up
  return;
}

//Rotates the sample cache carousel to the given position
void rotateCarousel(const uint16_t pos)
{
  Serial.print("Rotating carousel to pos = ");
  Serial.print(pos);
  Serial.print("\n");
  carousel.write(170/4 * pos);  // TODO: cache positions must be tweeked here.
  //delay(5000);//Delay to let servo catch up
  return;
}


//Returns one soil temperature reading
float instantSoilTemp()
{
  const int analogRes = 4095;
  float voltage = (analogRead(PB_5) * 3.24 / analogRes);
  float degC = (voltage - 0.5) * 100.0;
  return degC;
}

//Returns one air temperature reading
float instantAirTemp()
{
  const int analogRes = 4095;
  float voltage = (analogRead(PK_2) * 3.24 / analogRes);
  float degC = (voltage - 0.5) * 100.0;
  return degC;
}

//Returns on UV intensity reading
float instantUV()
{
 //Enable pin here
  float uvInten = mapfloat(analogRead(PK_0), .99, 2.8, 0, 15);
  return uvInten;
}

//The Arduino Map function but for floats (used in UV intensity)
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Returns one PhotoDiode 1 reading
int readPhotoDiode1()
{
  return analogRead(PD_0);  
}

//Returns one PhotoDiode 2 reading
int readPhotoDiode2()
{
  return analogRead(PD_1);
}

//Turns on the spectrometer motor on in the forward direction (the direction it will go when reading the photo-diodes)
void spectroMotorForward()
{
   Serial.println("Spectro motor forward");
   digitalWrite(PM_5, HIGH);//phase, low = forward
   digitalWrite(PB_3, LOW);//enable
   return;
}

//Turns the spectrometer motor on in the backwards direciton (when the spectrometer resets)
void spectroMotorReverse()
{
   Serial.println("Spectro motor reverse");
   digitalWrite(PM_5, LOW);
   digitalWrite(PB_3, HIGH);

   return;
}

//Turns off the spectrometer motor
void spectroMotorOff()
{
  Serial.println("Spectro motor off");
  digitalWrite(PB_3, LOW);
  digitalWrite(PM_5, LOW);
  return;
}

//Returns one reading of the air humidity TODO: Insert actual sensor code
float instantAirHumidity()
{
  float holderOfPlace = 0.0;
  return holderOfPlace;  
}

//Returns one reading of the soil humidity TODO: Insert actual sensor code
float instantSoilHumidity()
{
  float holderOfPlace = 0.0;
  return holderOfPlace;    
}

//Returns one reading of methane TODO: Insert actual sensor code
float instantMethane()
{
  float holderOfPlace = 0.0;
  return holderOfPlace;  
}

//Returns one air pressure reading TODO: Insert actual sensor code
float instantPressure()
{
  float holderOfPlace = 0.0;
  return holderOfPlace;
}

