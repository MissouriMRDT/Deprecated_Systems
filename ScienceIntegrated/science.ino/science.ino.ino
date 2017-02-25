#include "science.h"
#include "RoveEthernet.h"
#include <SPI.h>
#include "Servo.h"

//Variable declaration
CommandResult result;
uint16_t commandId;
size_t commandSize;
int16_t commandData;
uint32_t watchdogTimer_us = 0;
Servo flap, carousel;

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

    roveComm_GetMsg(&commandId, &commandSize, &commandData);

    if(commandId != 0)
    {
      watchdogTimer_us = 0;

      Serial.println(commandId);
      Serial.println(commandData);
      Serial.println(commandSize);
      Serial.println("");
      const int response = 0;
      roveComm_SendMsg(commandId, commandSize, &response); //dataID, size, data

//       if(commandId == 0x711)
//        flap(commandData)

        //if(sucsess...)
        
        
    }
    else
    {
      uint8_t microsecondDelay = 10;
      delayMicroseconds(microsecondDelay);

      watchdogTimer_us += microsecondDelay;

      if(watchdogTimer_us >= WATCHDOG_TIMEOUT_US) //if more than our timeout period has passed, then kill arm movement
      {
        Serial.println("Watch out dog!!!!!!");
        watchdogTimer_us = 0;
      }

      //if(checkOvercurrent())
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

void operate_flap(const int16_t data)
{
  if(data==1)
    Serial.println("Closing Flap");
  else if(data==2)
    Serial.println("Opening Flap");
   else
    Serial.println("Neither");
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

void rotateCarousel(int pos)//need to discuss best implementation of this
{
  pos--;
  carousel.write(180/4 * pos);  //cache positions must be tweeked here.
}

void spectroMotorOn(bool dir)
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

