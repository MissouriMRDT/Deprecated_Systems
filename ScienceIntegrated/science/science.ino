//Programmers: Chris Dutcher™ & Jimmy Haviland
//Febuary 24, 2017
//Missouri S&T  Mars Rover Design Team
//Science Board Main program

//TODO: Clean up includes (move to energia's folder, not github's)
#include "config.h"
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

//global current position for carousel
int curPos = 0;

//All non-important pre-loop setup is done here
void setup() {
  roveComm_Begin(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
  Serial.begin(9600);
  PhotoServer.begin();
  pinMode(laserPin, OUTPUT);//laser
  pinMode(LEDPin, OUTPUT);//LED
  pinMode(photoPin1, INPUT);//photodiode1
  pinMode(photoPin2, INPUT);//photodiode2
  flap.attach(flapPin);
  carousel.attach(carouselPin);
  Wire.begin();
  //PSensor.begin();//Initalize pressure Sensor
  /************************************
  * Spectrometer motor Initiaslization
  /***********************************/
  pinMode(spectro_motor_in_1, OUTPUT);//in 1
  pinMode(spectro_motor_in_2, OUTPUT);//in 2

  //Init sensor pins
  pinMode(UVPin, INPUT);//UV
  pinMode(airTempPin, INPUT);//air temp
  pinMode(soilTempPin, INPUT);
  pinMode(methanePin, INPUT);
  pinMode(airHumidityPin, INPUT);
  pinMode(soilMoisturePin, INPUT);
  
  Serial.println("Initialized!");
  closeFlap();
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
              if(i!=1||i!=3)
                 sensor_enable[i]=true;
            }
            break;
        case sensorAllDisable:
          for(int i=0;i<7;i++)
            {
              sensor_enable[i]=false;
            }
            break;
        case sensor0Enable:
          sensor_enable[0]=true;
          break;
        case sensor0Disable:
          sensor_enable[0]=false;
          break;
        case sensor1Enable:
          sensor_enable[1]=true;
          break;
        case sensor1Disable:
          sensor_enable[1]=false;
          break;
        case sensor2Enable:
          sensor_enable[2]=true;
          break;
        case sensor2Disable:
          sensor_enable[2]=false;
          break;
        case sensor3Enable:
          sensor_enable[3]=true;
          break;
        case sensor3Disable:
          sensor_enable[3]=false;
          break;
        case sensor4Enable:
          sensor_enable[4]=true;
          break;
        case sensor4Disable:
          sensor_enable[4]=false;
          break;
        case sensor5Enable:
          sensor_enable[5]=true;
          break;
        case sensor5Disable:
          sensor_enable[5]=false;
          break;
        case sensor6Enable:
          sensor_enable[6]=true;
          break;
        case sensor6Disable:
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
      //kill();
      //Serial.println("Watch out dog!!!!!!");
      watchdogTimer_us = 0;
    }//end if for watchdog timeout
    
  }//End else go to watchdog (no message received)

   //TODO: Remove sending from sensors moved to arm
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
      roveComm_SendMsg(air_temperature_ID, sizeof(temp), &temp); 
     }
     if(sensor_enable[1]) //Soil Temp
     {
      float temp = instantSoilTemp();
      roveComm_SendMsg(soil_temperature_ID, sizeof(temp), &temp);
     }
     if(sensor_enable[2]) //AirHumidity
     {
      sensorTestData = 101.0;
      float airHum = instantAirHumidity();
      roveComm_SendMsg(air_humidity_ID, sizeof(airHum), &airHum);
     }
     if(sensor_enable[3]) //Soil Humidity
     {
      float temp = instantSoilHumidity();
      roveComm_SendMsg(soil_humidity_ID, sizeof(temp), &temp);
     }
     if(sensor_enable[4]) //UVIntensity
     {
      float temp = instantUV();
      roveComm_SendMsg(UV_intensity_ID, sizeof(temp), &temp);
      
     }
     if(sensor_enable[5]) //Pressure
     {
      float temp = instantPressure();
      roveComm_SendMsg(pressure_ID, sizeof(temp), &temp);
     }
     if(sensor_enable[6]) //Methane
     {
      float temp = instantMethane();
      roveComm_SendMsg(methane_ID, sizeof(temp), &temp);
     }
  }//end if millis, send sensor data

}//End loop()

//Functions:
//TODO: Add a calibration file for sensors

//Spectometer sub-routine
void spectrometer()
{
   Serial.println("Start spectro routine.");

   EthernetClient client = PhotoServer.available();

   if(client)//only run the routine if TCP available!
   {
     uint16_t photo1, photo2;
     String tcp_buffer;
     //turn on motor, run for 5s before continuing
     //direction is a bool! change true/false for direction
     spectroMotorForward();   
     //do nothing except leave motor on for 5s
     delay(5000);
     //turn on laser
     turnOnLaser();   
     //keep laser and motor on for 30s
     int timer = 0;
     //loop takes analog readings 
     //delays for 1/8 second
     //should repeat until roughly 30s have passed.
     while (timer <= 30000)
     {
      //read photo diodes
      photo1 = analogRead(photoPin1);//analog read returns 10 bit integer (0 to 1023)
      photo2 = analogRead(photoPin2);
      //print data
      Serial.println("Data for photodiodes 1 & 2, respectively:");
      Serial.println(photo1);
      Serial.println(photo2);
      //roveComm_SendMsg(sensor9_ID, sizeof(photo1), &photo1);
      //roveComm_SendMsg(0x, sizeof(photo2), &photo2);

      if(photo1 > 255 || photo2 > 255)
      {
        Serial.println("Photo data greater than 8 bit!!!!!!!!!!!!!!!!!!!!!!!!!! ");
      }

      PhotoServer.println("photodiode 1:");
      PhotoServer.println(photo1);
      //PhotoServer.print("\n");

      PhotoServer.println("photodiode 2:");
      PhotoServer.println(photo2);
      //PhotoServer.print("\n");

      //TCP needs 8 bit values
      uint8_t photo1_8 = photo1;
      uint8_t photo2_8 = photo2;

      //PhotoServer.write(&photo1_8,sizeof(photo1_8));
      //PhotoServer.write(&photo2_8,sizeof(photo2_8));
      
      timer += 125;
      delay(125); 
     }

     //turn off laser
     turnOffLaser();
     
     //turn off motor
     spectroMotorOff();

     //end tcp connection
     client.stop();
     
     //delay couple seconds
     delay(2000);
     
     //return motor to start position
     //opposite direction than what was called earlier!
     spectroMotorReverse();
     
     //wait 35s for motor to return
     delay(40000);
     
     //stop motor again
     spectroMotorOff();
     
     //wait 10 seconds before repeating the loop
     delay(10000); 

     
   }//end if client
   else
   {
    Serial.println("TCP not available. Spectrometer routine not run.");
   }
   
     
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
  flap.write(20);
  //flap.writeMicroseconds(1);
  //delay(5000);//Delay to let servo catch up
  return;
}

//Closes the sample cache cover flap
void closeFlap()
{
  Serial.println("Closing flap.");
  //Flap should close at 180
  flap.write(170);
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
  carousel.write(car_positions[pos]);
  //carousel.write(170/4 * pos);  // TODO: cache positions must be tweeked here. 
  //delay(5000);//Delay to let servo catch up

/******This is my attempt to slow down the carousel servo motor. 
  Serial.print("carousel rotate: from pos = ");
  Serial.print(curPos);
  Serial.print(". to pos = ");
  Serial.print(pos);
  Serial.print(". \n");
  
  int delay_val = 100; //Change this val to slow down motor.
  if(pos>curPos)       //Do not make it too small or the servo will freak out!
  {
    Serial.println("Going up! (rotating to greater pos)");
    for(int i = car_positions[curPos]; i < car_positions[pos]; i++)
    {
      Serial.print(i);
      carousel.write(i);
      delay(delay_val);
    }
  }
  else if(pos<curPos)
  {
    Serial.println("Goin' Down. (rotating to lower pos)");
    for(int i = car_positions[curPos]; i > car_positions[pos]; i--)
    {
      Serial.print(i);
      carousel.write(i);
      delay(delay_val);
    }
  }
   else
   {
    Serial.println("pos is same");
   }
   
  Serial.print("\n");
*/
  
  curPos = pos;
  return;
}

//Turns on the spectrometer motor on in the forward direction (the direction it will go when reading the photo-diodes)
void spectroMotorForward()
{
   Serial.println("Spectro motor forward");
   digitalWrite(spectro_motor_in_1, HIGH);//phase, low = forward
   digitalWrite(spectro_motor_in_2, LOW);//enable
   return;
}

//Turns the spectrometer motor on in the backwards direciton (when the spectrometer resets)
void spectroMotorReverse()
{
   Serial.println("Spectro motor reverse");
   digitalWrite(spectro_motor_in_1, LOW);
   digitalWrite(spectro_motor_in_2, HIGH);

   return;
}

//Turns off the spectrometer motor
void spectroMotorOff()
{
  Serial.println("Spectro motor off");
  digitalWrite(spectro_motor_in_2, LOW);
  digitalWrite(spectro_motor_in_1, LOW);
  return;
}

//Returns one soil temperature reading
float instantSoilTemp()
{
  //const int analogRes = 4095;
  //float voltage = (analogRead(soilTempPin) * 5 / analogRes);
  //float degC = (voltage - 0.5) * 100.0;
  //float degC = -1.0;
  //return degC;
}

//Returns one air temperature reading
float instantAirTemp()
{
  const int analogRes = 4095;
  float voltage = analogRead(airTempPin) * 5;
  Serial.print("voltage:");Serial.print(voltage);Serial.print("\n");
  voltage = voltage / analogRes;
  float degC = (voltage - 0.5) * 100.0;
  float degF = (degC * 1.8)+32;
  Serial.print("TempF:");Serial.print(degF);Serial.print("\n");
  return degF;
}

//TODO: determine if all pins are 5V or 3.3V for the conversion to voltage in these sensor equations

//Returns on UV intensity reading
float instantUV()
{
  //Enable pin here
  int reading = analogRead(UVPin);
  float outputVoltage = (reading * 3.3333) / 4095;
  float uvInten = mapfloat(outputVoltage, UV_in_min, UV_in_max, UV_out_min, UV_out_max); // these values defined in config.h
  Serial.print("UV:"); Serial.print(uvInten); Serial.print("\n");
  return uvInten;
}

//The Arduino Map function but for floats (used in UV intensity)
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Returns one reading of the air humidity
float instantAirHumidity()
{
  int reading = analogRead(airHumidityPin);
  Serial.print("reading:");Serial.print(reading);Serial.print("\n");
  int max_voltage = 5;
  float RH = reading/1023;
  RH=RH*5;
  RH=RH-2.4;
  RH=RH/max_voltage;
  Serial.print(" data: "); Serial.print(RH); Serial.print("\n");
  RH=RH*100;
  Serial.print("air humidity: "); Serial.print(RH); Serial.print("\n");
  return RH;  
}

//Returns one reading of the soil humidity
float instantSoilHumidity()
{
  //int reading = analogRead(soilMoisturePin);
  //float voltage = ((reading * 5.0) / 4095);
  //float voltage = -1.0;
  //return voltage; //returning raw voltage for now
                  //TODO: convert to measurement of moisture
}

//Returns one reading of methane
float instantMethane()
{
  int reading = analogRead(methanePin);
  float voltage = (reading * 5.0) / 4095.0;
  Serial.print("methane data:"); Serial.print(voltage); Serial.print("\n");
  return voltage;
  //TODO: convert voltage to measurement of methane
}

//Returns one air pressure reading 
float instantPressure()
{
  //PSensor.refresh();
  //PSensor.calculate();
  //float pressure = (PSensor.pressure + 50) / 100;
  int pressure = 99;
  Serial.print("Pressure:");Serial.print(pressure);Serial.print("\n");
  return pressure;
  //TODO: adjust this conversion? current unit is hPa
  //TODO: this sensor only works on pins configuerd for I2C
          //change pins this sensor connects to so it will function
}

void kill()
{
  turnOffLaser();
}


