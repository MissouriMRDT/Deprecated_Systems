#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include "Arduino.h"

//id = 1
struct s_Controls
{

  //Drill Ctrl
  uint8_t goalSpeed;
  uint8_t direction;
  
  //Thermo Ctrl
  uint8_t heaterPower;
  uint8_t thermoReadings;
  
  //Gas Ctrl
  uint8_t sensorPower;
  uint8_t gasReadings; //Readings will only be updated when true
};

struct s_Telemetry
{
    //Gas Data
  uint16_t hydrogenReading;
  uint16_t methaneReading;
  uint16_t ammoniaReading;
  
  //Thermo Data
  float temp;
  
  //Drill Data
  uint8_t actualSpeed;
  uint16_t goalCurrent;
  uint16_t actualCurrent;
  
};

const int SIZE_CONTROLS = sizeof(s_Controls) / 8;
//Telemetry Data
#endif
