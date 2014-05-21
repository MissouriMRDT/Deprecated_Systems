/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  Main program
-----------------------------------------------------------*/
#include <Wire.h>
#include <i2cmaster.h>
#include <EasyTransfer.h>
#include "DataStructures.h"
#include "endeffector.h"
#include "driver.h"

EasyTransfer MotherboardReceive;
EasyTransfer MotherboardSend;
s_Controls controls;
//prevState is kept for comparison, to determine what changed
s_Controls prevState;
s_Telemetry telemetry;

void setup() 
{
  // Motherboard handshake
  Serial.begin(115200);
  MotherboardReceive.begin(details(controls), &Serial);
//  MotherboardSend.begin(details(telemetry), &Serial);
  pinMode(MOT_PWM, OUTPUT);
  pinMode(MOT_INA, OUTPUT);
  pinMode(MOT_INB, OUTPUT);
  pinMode(GAS_CTRL, OUTPUT);
  pinMode(HEAT_CTRL, OUTPUT);
  SetDrillDirection(controls);

  telemetry.actualSpeed = 0;
  telemetry.hydrogenReading = 0;
  telemetry.methaneReading = 0;
  telemetry.ammoniaReading = 0;
  telemetry.temp = 0;
  //Initialize Controls and Telemetry Data
  
  
  //Connect Thermometer
  i2c_init(); 
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable internal pullups
}

void loop() 
{
  //Will constantly try to receive data
  if(MotherboardReceive.receiveData())
  {

    discreteUpdates(controls, prevState, telemetry);
    prevState = controls;
  }
  continuousUpdates(controls, telemetry);
//  MotherboardSend.sendData();
  delay(125);

}
