#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include "Arduino.h"

//id = 1
struct s_State
{
  //Gas Data
  uint16_t hydrogenReading;
  uint16_t methaneReading;
  uint16_t ammoniaReading;
  
  //Thermo Data
  float temp;
  
  //Drill Ctrl
  uint8_t goalSpeed;
  uint8_t actualSpeed;
  uint16_t goalCurrent;
  uint16_t actualCurrent;
  bool direction;
  
  //Thermo Ctrl
  bool heaterPower;
  
  //Gas Ctrl
  bool sensorPower;
  bool takeReadings; //Readings will only be updated when true
};


#endif
