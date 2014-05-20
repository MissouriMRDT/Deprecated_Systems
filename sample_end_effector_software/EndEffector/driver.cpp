/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  VNH5019 Motor Driver Control - Implementation
  Used to control the drill and the thermo test heater
-----------------------------------------------------------*/
#include "Arduino.h"
#include "driver.h"

int currentRead(const int pin, const int acc)
{
  int current = 0;
  for(int i = 0; i<acc; i++)
  {
    current += analogRead(pin);
    delay(1);
  }
  current /= acc;
  Serial.println("Current read is " + (String)current);
 
  return current;
}


//int updateMotor(const int desired_speed, const int actual_speed, const int current)
int updateMotor(s_Controls &State, s_Telemetry& telemetry)
{
  int new_speed = telemetry.actualSpeed;
  telemetry.actualCurrent = currentRead(DRILL_CS, READ_ACC);
  
  //Calculates current that should be seen when operating at desired speed
  telemetry.goalCurrent = calculate_desired_current(State.goalSpeed);
  
  //Check to see if motor is struggling or stuck
  if(telemetry.actualCurrent > telemetry.goalCurrent)
  {
    //Calculates current that should be seen when operating at actual, elevated speed
    float max_current = calculate_desired_current(telemetry.actualSpeed);
    max_current *= MAX_VARIATION;
    if(telemetry.actualCurrent > CUTOFF_CURRENT)
    {
      new_speed = telemetry.actualSpeed - SPEED_STEP;
    } else if(telemetry.actualSpeed > DRILL_FULL_SPEED)
    {
      new_speed = DRILL_FULL_SPEED;
    //Drill is still stalled out, not running at max power
    } else if(telemetry.actualCurrent > max_current)
    {
      new_speed = telemetry.actualSpeed + SPEED_STEP;
    //Drill has broken stall, scale back speed
    } else {  
      new_speed = telemetry.actualSpeed - SPEED_STEP;
    } 
  }
  telemetry.actualSpeed = new_speed;
  return new_speed;
}


float calculate_desired_current(int motor_speed)
{  
  float current = (CURRENT_SLOPE * motor_speed) + CURRENT_INTERCEPT;
  Serial.println("Desired Current");
  Serial.println(current);
  return current;
}

void setDriverOutput(const int motor_speed)
{
  analogWrite(MOT_PWM, motor_speed);
}

void SetDrillDirection(const s_Controls &state)
{
  if(state.direction!=false)
  {
    digitalWrite(MOT_INA,HIGH);
    digitalWrite(MOT_INB,LOW);
  }
  else
  {
    digitalWrite(MOT_INA,LOW);
    digitalWrite(MOT_INB,HIGH);
  }
  return;
}

void maintainCurrent(s_Telemetry& state, const int current)
{
  state.actualCurrent = currentRead(DRILL_CS, READ_ACC);
  if(state.actualCurrent > (current + MAINTAIN_TOLERANCE))
  {
    state.actualSpeed -= SPEED_STEP;
  } else if(state.actualCurrent < (current - MAINTAIN_TOLERANCE))
  {
    state.actualSpeed += SPEED_STEP;
  }
  setDriverOutput(state.actualSpeed);
  return;
}

void changeOutput(const bool driv_output)
{
  digitalWrite(HEAT_CTRL, driv_output);
}
