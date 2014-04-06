#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include "Arduino.h"

struct SgasData
{
  uint16_t hydrogenReading;
  uint16_t methaneReading;
  uint16_t ammoniaReading;
};

struct SthermoData
{
  float temp;
};

struct SdrillCtrlState
{
  uint8_t goalSpeed;
  uint8_t actualSpeed;
  uint8_t goalCurrent;
  uint8_t actualCurrent;
};

struct SthermoCtrl
{
  bool heaterPower;
};

struct SgasCtrl
{
  bool sensorPower;
};

#endif
