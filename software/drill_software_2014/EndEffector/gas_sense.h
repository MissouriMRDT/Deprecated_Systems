/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  Gas sensor control
-----------------------------------------------------------*/
#ifndef GAS_SENSE_H
#define GAS_SENSE_H
#include "Arduino.h"
#include "endeffector.h"

const int WARM_UP_DELAY = 25; //Warm up delay for gas sensors in milliseconds
const int ACCURACY = 20; //Number of reads to average data from
const int READ_SPACE = 1; //ms between reads of the sensor

//Desc: Reads gas sensor data from specified sensor and returns the gas concentration reading
//      on a scale of 0 to 1024
//Pre:  Gas sensors have been turned on with updateHeatingElement
//Post: Sensors are turned on, gas concentration data is returned, and sensors are turned off
int readGas(const int sensor);

//Turns the heating element on / off depending on sensorPower in state
void updateGasHeaters(const bool sensorPower);

//Reads gas data in from all sensors and updates the state
void updateGasData(s_Telemetry &gasData);

#endif  
