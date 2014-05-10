/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  Thermal Conductivity Test headers
  Contains functions necessary to interface with MLX90614 
    thermometer
    
  Depends on the third party I2C Master libraries for Arduino. 
  Will fail with the built in wire library as of Arduino 1.05.
-----------------------------------------------------------*/
#ifndef THERMO_TEST_H
#define THERMO_TEST_H
#include "Arduino.h"
#include <i2cmaster.h>

const int HEATER_CURRENT = 29; //goal current to pass through heating element
                               //Currently set to hold output at 12W

/*----Data Acquisition----*/

//get_temp_c() Gets temperature from MLX90614 IR thermometer in centigrade
//Pre: I2C has been initialized
//Post: Temperature is read and returned as floating point to two decimal places
float get_temp_c();

/*----Data Processing----*/

#endif
