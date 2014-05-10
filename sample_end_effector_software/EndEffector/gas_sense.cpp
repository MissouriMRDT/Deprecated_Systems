/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  Gas sensor control
-----------------------------------------------------------*/
#include "Arduino.h"
#include "gas_sense.h"

int readGas(const int sensor)
{
  int result;
    
  //Gets average reading 
  for(int i=0; i<ACCURACY; i++)
  {
    result += analogRead(sensor);
    delay(READ_SPACE);
  }
  result /= ACCURACY;
  return result;
}

void updateGasHeaters(const bool sensorPower)
{
  sensorPower ? digitalWrite(HEAT_CTRL, HIGH) : digitalWrite(HEAT_CTRL, LOW);
  return;
}

void updateGasData(s_State &gasData)
{
  gasData.hydrogenReading = readGas(ADC0);
  gasData.methaneReading = readGas(ADC1);
  gasData.ammoniaReading = readGas(ADC2);
  return;
}
