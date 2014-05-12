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

EasyTransfer MotherboardComm;
s_State state;
//prevState is kept for comparison, to determine what changed
s_State prevState;

void setup() 
{
  // Motherboard handshake
  Serial.begin(9600);
  MotherboardComm.begin(details(state), &Serial);
 
  //Connect Thermometer
  i2c_init(); 
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable internal pullups
  
}

void loop() 
{
  if(Serial.available())
  {
    if(MotherboardComm.receiveData())
    {
      //Integrity Check
      MotherboardComm.sendData(); 
      discreteUpdates(state, prevState);
      prevState = state;
    }
  }
  continuousUpdates(state);
}
