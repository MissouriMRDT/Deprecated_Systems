/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  General control functions - implementation
-----------------------------------------------------------*/
#include "Arduino.h"
#include "endeffector.h"
#include "driver.h"
#include "gas_sense.h"
#include "thermo_test.h"

void discreteUpdates(s_State& state, const s_State& prev_state)
{
  if(state.sensorPower != prev_state.sensorPower)
    updateGasHeaters(state.sensorPower);
  if(state.direction != prev_state.direction)
    SetDrillDirection(state);
  if(state.heaterPower != prev_state.heaterPower)
    changeOutput(state.heaterPower);
  
  //Emergency kill, skips current prediction calculations for fast response
  if(0 == state.goalSpeed)
    state.actualSpeed = 0;
    setDriverOutput(0);    
  return;
}

void continuousUpdates(s_State& state)
{
  if(state.goalSpeed && (!state.heaterPower))
  {
    updateMotor(state);
    setDriverOutput(state.actualSpeed);
  }
  if(state.takeReadings)
  {
    updateGasData(state);
  }
  if(state.heaterPower)
  {
    maintainCurrent(state, HEATER_CURRENT);
  }
}
