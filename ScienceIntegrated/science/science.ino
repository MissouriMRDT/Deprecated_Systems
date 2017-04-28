//Programmers: Chris Dutcher™ & Jimmy Haviland
//Febuary 24, 2017
//Missouri S&T  Mars Rover Design Team
//Science Board Main program

//TODO: Clean up includes (move to energia's folder, not github's)
#include "science.h"
#include "RoveEthernet.h"
#include <SPI.h>
#include "Servo.h"
#include <Wire.h>
//#include "BMP085_t.h"


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

 //Determines which sensors will send data back
bool sensor_enable[7] = {false,false,false,false,false,false,false};

//Device objects
//Energia standard servo device class from Servo.h
Servo flap, carousel;
//Pressure sensor object
//BMP085<0, airPressurePin> PSensor;

//All non-important pre-loop setup is done here
void setup() {
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);//laser
  pinMode(LEDPin, OUTPUT);//LED
  pinMode(PD_2, INPUT);//photodiode1
  pinMode(PD_3, INPUT);//photodiode2
  flap.attach(PL_0);
  carousel.attach(PL_2);
  Wire.begin();
  //PSensor.begin();//Initalize pressure Sensor
  /************************************
  * Spectrometer motor Initiaslization
  /***********************************/
  pinMode(PM_5, OUTPUT);//in 1
  pinMode(PB_3, OUTPUT);//in 2

  //Init sensor pins
  pinMode(UVPin, INPUT);//UV
  pinMode(airTempPin, INPUT);//air temp
  pinMode(soilTempPin, INPUT);
  pinMode(methanePin, INPUT);
  pinMode(airHumidityPin, INPUT);
  pinMode(soilMoisturePin, INPUT);
  //TODO: set pinmodes for all sensor pins to INPUT
  
  Serial.println("Initialized!");
  }


void loop() {
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
    }//end if for watchdog timeout
    
  }//End else go to watchdog (no message received)
  
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
      float temp = instantAirTemp();
      Serial.print("MAIN__temp data received: ");
      Serial.print(temp);
      Serial.print("\n");
      roveComm_SendMsg(0x720, sizeof(temp), &temp); 
     }
     if(sensor_enable[1]) //Soil Temp
     {
      sensorTestData = 102.0;
      roveComm_SendMsg(0x721, sizeof(sensorTestData), &sensorTestData);
     }
     if(sensor_enable[2]) //AirHumidity
     {
      sensorTestData = 101.0;
      float airHum = instantAirHumidity();
      Serial.print("MAIN__humidity data received: ");
      Serial.print(airHum);
      Serial.print("\n");
      roveComm_SendMsg(0x722, sizeof(airHum), &airHum);
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
  }//end if millis, send sensor data

}//End loop()

//Functions:
//TODO: Eventually, define all pins in the header
//TODO: Add a calibration file for sensors

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
  digitalWrite(laserPin, HIGH);//laser
  digitalWrite(LEDPin, HIGH);//LED
  return;
}

//Turns off the spectormeter laser
void turnOffLaser()
{
  Serial.println("Laser off");
  //turn off laser by setting pin to low
  digitalWrite(laserPin, LOW);//laser
  digitalWrite(LEDPin, LOW);//led
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
  int positions[5] = {0, 45, 90, 135, 170};
  Serial.print("Rotating carousel to pos = ");
  Serial.print(pos);
  Serial.print("\n");
  carousel.write(positions[pos - 1]);
  //carousel.write(170/4 * pos);  // TODO: cache positions must be tweeked here. //TODO: have array to store cache positions and use pos as index
  //delay(5000);//Delay to let servo catch up
  return;
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

//Returns one soil temperature reading
float instantSoilTemp()
{
  const int analogRes = 4095;
  float voltage = (analogRead(soilTempPin) * 5 / analogRes);
  float degC = (voltage - 0.5) * 100.0;
  return degC;
}

//Returns one air temperature reading
float instantAirTemp()
{
  const int analogRes = 4095;
  float voltage = analogRead(airTempPin) * 5;
  voltage = voltage / analogRes;
  float degC = (voltage - 0.5) * 100.0;
  float degF = (degC * 1.8) + 32;
  return degF;
}

//Returns on UV intensity reading
float instantUV()
{
  //Enable pin here
  int reading = analogRead(UVPin);
  float outputVoltage = (reading * 3.3333) / 4095;
  float uvInten = mapfloat(outputVoltage, 0.99, 2.8, 0, 15);
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


//Returns one reading of the air humidity
float instantAirHumidity()
{
  int reading = analogRead(airHumidityPin);
  int max_voltage = 5;
  float RH = ((((reading/1023)*5)-0.8)/max_voltage)*100;
  Serial.print("air humidity: "); Serial.print(RH);
  Serial.print(" data: "); Serial.print(reading); Serial.print("\n");
  return RH;  
}

//Returns one reading of the soil humidity
float instantSoilHumidity()
{
  int reading = analogRead(soilMoisturePin);
  float voltage = ((reading * 5.0) / 4095);
  return voltage; //returning raw voltage for now
                  //TODO: convert to measurement of moisture
}

//Returns one reading of methane
float instantMethane()
{
  int reading = analogRead(methanePin);
  float voltage = (reading * 5.0) / 4095.0;
  return voltage;
  //TODO: convert voltage to measurement of methane
}

//Returns one air pressure reading TODO: Insert actual sensor code
float instantPressure()
{
  //PSensor.refresh();
  //PSensor.calculate();
  //float pressure = (PSensor.pressure + 50) / 100;
  int pressure = 99;
  return pressure;
  //TODO: adjust this conversion? current unit is hPa
}

