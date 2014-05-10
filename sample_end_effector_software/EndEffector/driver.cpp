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
int updateMotor(s_State &State)
{
  int new_speed = State.actualSpeed;
  State.actualCurrent = currentRead(DRILL_CS, READ_ACC);
  
  //Calculates current that should be seen when operating at desired speed
  State.goalCurrent = calculate_desired_current(State.goalSpeed);
  
  //Check to see if motor is struggling or stuck
  if(State.actualCurrent > State.goalCurrent)
  {
    //Calculates current that should be seen when operating at actual, elevated speed
    float max_current = calculate_desired_current(State.actualSpeed);
    max_current *= MAX_VARIATION;
    if(State.actualCurrent > CUTOFF_CURRENT)
    {
      new_speed = State.actualSpeed - SPEED_STEP;
    } else if(State.actualSpeed > DRILL_FULL_SPEED)
    {
      new_speed = DRILL_FULL_SPEED;
    //Drill is still stalled out, not running at max power
    } else if(State.actualCurrent > max_current)
    {
      new_speed = State.actualSpeed + SPEED_STEP;
    //Drill has broken stall, scale back speed
    } else {  
      new_speed = State.actualSpeed - SPEED_STEP;
    } 
  }
  State.actualSpeed = new_speed;
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

void SetDrillDirection(const s_State &state)
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

void maintainCurrent(s_State& state, const int current)
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
