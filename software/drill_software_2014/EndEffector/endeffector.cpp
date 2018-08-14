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

void discreteUpdates(s_Controls& state, const s_Controls& prev_state,s_Telemetry& telemetry)
{
  if(state.sensorPower != prev_state.sensorPower)
    updateGasHeaters(state.sensorPower);
  if(state.direction != prev_state.direction)
    SetDrillDirection(state);
  if(state.heaterPower != prev_state.heaterPower)
    //inverts state.heaterPower to compensate for the fact that
    //The relay used to change outputs is active low
    if(state.heaterPower)
    {
      digitalWrite(MOT_PWM, LOW);
      digitalWrite(HEAT_CTRL, LOW);
    } else
    {
      digitalWrite(MOT_PWM, LOW);
      digitalWrite(HEAT_CTRL, HIGH);
    }
  
  //Emergency kill, skips current prediction calculations for fast response
  if(0 == state.goalSpeed)
    telemetry.actualSpeed = 0;
    analogWrite(MOT_PWM, 0);    
  return;
}

void continuousUpdates(s_Controls& state, s_Telemetry& telemetry)
{
  if(state.goalSpeed && (!state.heaterPower))
  {
    //DEBUG: Skips calculations and directly passes control through
    //telemetry.actualSpeed = state.goalSpeed;
    
    //Uncomment when debug stuff is done
    updateMotor(state, telemetry);
    analogWrite(MOT_PWM, telemetry.actualSpeed);
  }
  if(state.gasReadings)
  {
    updateGasData(telemetry);
  }
  if(state.thermoReadings)
  {
    telemetry.temp = get_temp_c();
  }
  if(state.heaterPower)
  {
    maintainCurrent(telemetry, HEATER_CURRENT);
  }
}
