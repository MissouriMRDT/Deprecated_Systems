#ifndef test_functions
#define test_functions
#include "Arduino.h"
#include "control_functions.h"
#include "DataStructures.h"

//Description: Tests motor by switching it on and off rapidly
//Pre: Motor is connected to motor driver, 12v is available
//Post: Motor turns on and off in various speeds and directions
//      Returns 1 if test successful
int motorTest();

//Description: Tests Gas Sensors
//Pre: Gas sensors are connected using ribbon cable and properly
//     calibrated (use potentiometers to calibrate)
//Post: Gas sensors are read, gas concentrations are returned
SgasData gasSensorTest();

//Description: Runs drill at around half speed to test soil 
//             collecting capabilities
//Pre: None
//Post: Motor is on and running.
int soilTest();

int motorTest()
{
  SetDrillDirection(0);
  SetDrillSpeed(255);
  delay(10000);
  SetDrillSpeed(0);
  delay(1000);

  SetDrillDirection(1);
  SetDrillSpeed(255);
  delay(10000);
  SetDrillSpeed(0);
  delay(1000);  
  
  return 0; //Successfull test run
}

int soilTest(int speedctrl)
{
  SetDrillDirection(1);
  SetDrillSpeed(speedctrl);
  delay(10000);
  return 1;
}

#endif
