//Programmers: Chris Dutcher & Jimmy Haviland
//Science board Main program

#include "science.h"
#include "RoveEthernet.h"
#include <SPI.h>
#include "Servo.h"
#include <Wire.h>
#include "BMP085_t.h"

//Variable declaration
CommandResult result;
uint16_t commandId;
size_t commandSize;
int16_t commandData;
uint32_t watchdogTimer_us = 0;
Servo flap, carousel;
BMP085<0> PSensor;

void setup() {}

void loop() {



  //Initialize
  initialize();

  //Main execution loop
  while(1)
  {
    commandSize = 0;
    commandId = 0;
    commandData = 0;
    bool sensor_enable[7] = {1,1,1,1,1,1,1};//Determines which sensors send data back


    roveComm_GetMsg(&commandId, &commandSize, &commandData);

    if(commandId != 0)
    {
      watchdogTimer_us = 0;

      Serial.println(commandId);
      Serial.println(commandData);
      Serial.println(commandSize);
      Serial.println("");

       if(commandId == 0x720)
         sensor_enable[0]=commandId;
       else if(commandId == 0x721)
         sensor_enable[1]=commandId;
       else if(commandId == 0x722)
         sensor_enable[2]=commandId;
       else if(commandId == 0x723)
         sensor_enable[3]=commandId;
       else if(commandId == 0x728)
         sensor_enable[4]=commandId;
       else if(commandId == 0x729)
         sensor_enable[5]=commandId;
       else if(commandId == 0x72A)
         sensor_enable[6]=commandId;
       else if(commandId == 0x711)//Carosel
         rotateCarousel(commandData);
       else if(commandId == 0x710)//Spectrometer sub-routine
         spectrometer();
       else if(commandId == 0x72B)//
         partial_spec(commandData);
       
       //check for sensors, and then send through rovecomm if applicable
       if(sensor_enable[0])
         //AirTemp
         delay(1);
       else if(sensor_enable[1])
         //AirHumidity
         delay(1);
       else if(sensor_enable[2])
         //Soil Temp
         delay(1);
       else if(sensor_enable[3])
         //Soil Humidity
         delay(1);
         else if(sensor_enable[4])
         //Methane
         delay(1);
       else if(sensor_enable[5])
         //UV Intensity
         delay(1);
       else if(sensor_enable[6])
         //Pressure
         delay(1);      
        
    }
    else//No message
    {
      uint8_t microsecondDelay = 10;
      delayMicroseconds(microsecondDelay);

      watchdogTimer_us += microsecondDelay;

      if(watchdogTimer_us >= WATCHDOG_TIMEOUT_US) //if more than our timeout period has passed, then kill arm movement
      {
        Serial.println("Watch out dog!!!!!!");
        watchdogTimer_us = 0;
      }

      //if(checkOvercurrent())?
    }
    
  }
}

void initialize()
{
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  Serial.begin(9600);
  pinMode(PQ_3, OUTPUT);//laser
  pinMode(PF_0, OUTPUT);//LED
  pinMode(PD_0, INPUT);//photodiode1
  pinMode(PD_1, INPUT);//photodiode2
  flap.attach(PM_5);
  carousel.attach(PM_4);
  PSensor.begin();//Initalize pressure Sensor
  /************************************
  * Spectrometer motor Initiaslization
  /***********************************/
  pinMode(PM_6, OUTPUT);//sleep
  pinMode(PQ_1, OUTPUT);//phase
  pinMode(PP_3, OUTPUT);//enable
  pinMode(PF_0, OUTPUT);//LED
  pinMode(PK_7, OUTPUT);//enable voltage reg
  digitalWrite(PK_7, HIGH);//turn on voltage reg
  
  Serial.println("Initialized!");
}



void spectrometer()//Spec sub-routine
{
  //Motor on
  //5 sec
  //laser on
  //start reading pd
  //30 sec
  //laser off
  //motor off
  //delay 2
  //motor reverse
  //stop reading 
  //delay 35
  //motor off
}

void partial_spec(const uint16_t data)
{
    if(data==0)
    openFlap();
    else if(data==1)
    closeFlap();
    else if(data==2)
    turnOnLaser();
    else if(data==3)
    turnOffLaser();
    else if(data==4)
    spectroMotorOn(0);
    else if(data==5)
    spectroMotorOn(1);
    else if(data==6)
    spectroMotorOff();
    else if(data==7)
    //Read PD1 and sends back result
    delay(1000);
    else if(data==8)
    //Read PD2 and sends back result
    delay(1000);
}

void turnOnLaser()
{
  //turn on laser by setting pin to High
  digitalWrite(PQ_3, HIGH);//laser
  digitalWrite(PF_0, HIGH);//LED
}

void turnOffLaser()
{
  //turn off laser by setting pin to low
  digitalWrite(PQ_3, LOW);//laser
  digitalWrite(PF_0, LOW);//led
}

void openFlap()
{
  //does flap open at 180 degrees or 0?
  flap.write(170);
}

void closeFlap()
{
  //again, does flap close at 180 degrees or 0?
  flap.write(0);
}

void rotateCarousel(const uint16_t pos)//need to discuss best implementation of this
{
  carousel.write(180/4 * pos);  //cache positions must be tweeked here.
}

void spectroMotorOn(const bool dir)
{
  digitalWrite(PM_6, HIGH);//nsleep
  if (dir)
    digitalWrite(PQ_1, HIGH);//phase
  if (!dir)
    digitalWrite(PQ_1, LOW);//opposoite phase
  
  digitalWrite(PP_3, HIGH);//ennable the motor
}

void spectroMotorOff()
{
  digitalWrite(PP_3, LOW);//en
  digitalWrite(PM_6, LOW);//nsleep
}

float instantSoilTemp()
{
  const int analogRes = 4095;
  float voltage = (analogRead(PB_5) * 3.24 / analogRes);
  float degC = (voltage - 0.5) * 100.0;
  return degC;
}


float instantAirTemp()
{
  const int analogRes = 4095;
  float voltage = (analogRead(PK_2) * 3.24 / analogRes);
  float degC = (voltage - 0.5) * 100.0;
  return degC;
}

float instantUV()
{
 //Enable pin here
  float uvInten = mapfloat(analogRead(PK_0), .99, 2.8, 0, 15);
  return uvInten;


  /*  //Old unused version of UV reading
  int uvLevel = averageAnalogRead();         //Needs correct PIN   PK_0
  int refLevel = averageAnalogRead();      //Needs correct PIN

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
  return uvIntensity;
  */
}

/*  //Old function for UV reading
//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}
*/

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float instantPressure()
{
  PSensor.refresh();
  PSensor.calculate();
  return PSensor.pressure;
}

int readPhotoDiode1()
{
  return analogRead(PD_0);  
}

int readPhotoDiode2()
{
  return analogRead(PD_1);
}

