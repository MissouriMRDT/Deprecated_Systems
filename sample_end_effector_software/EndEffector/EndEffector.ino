
#include <Wire.h>
#include <i2cmaster.h>
#include <EasyTransfer.h>
#include "DataStructures.h"
#include "control_functions.h"
#include "TestFunctions.h"

// Sample Collection End Effector
// Author: Owen Chiaventone
//
// Manages Sample Collection End Effector
// for 2014 Missouri S&T University Rover
// Challenge Rover.
//
// Hardware designs available on the Mars 
// Rover Design Team OrgSync Page.

//Communication object for talking to Mobo
EasyTransfer gasDataComm;
EasyTransfer thermoDataComm;
EasyTransfer drillCtrlComm;
EasyTransfer thermoCtrlComm;
EasyTransfer gasCtrlComm;

//Data Structures used for communication
SgasData gasData;
SthermoData thermoData;
SdrillCtrlState drillCtrlState;
SthermoCtrl thermoCtrl;
SgasCtrl gasCtrl;

void setup() 
{
  // Motherboard handshake
  // 
  
  //Initialize EasyTranser Objects
  /*
  gasDataComm.begin(details(gasData), &Serial);
  thermoDataComm.begin(details(thermoData), &Serial);
  drillCtrlComm.begin(details(drillCtrlState), &Serial);
  thermoCtrlComm.begin(details(thermoCtrl), &Serial);
  gasCtrlComm.begin(details(gasCtrl), &Serial);
  */
  Serial.begin(9600);
  Serial.println("Begin test");
  Serial.println("Current time");
  Serial.println(millis());
  
  /*Heat Element Test*/
  pinMode(HEAT_CTRL, OUTPUT);
  digitalWrite(HEAT_CTRL, LOW);
 
  //I2C Connect Thermometer
  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
  
}

void loop() 
{
  delay(2000);
  //motorTest();
  
  //Update state of communications
  Serial.println("This is a test of communications systems");
  /*
  if(Serial.available())
  {
    if(gasDataComm.receiveData())
    {
      
    }
    if(thermoDataComm.receiveData())
    {
      
    }
    if(drillCtrlComm.receiveData())
    {
      
    }
    if(thermoCtrlComm.receiveData())
    {
      
    }
    if(gasCtrlComm.receiveData())
    {
      
    }
  }
  */
  // Send Data
  
  //Update state of Drill
  
}


