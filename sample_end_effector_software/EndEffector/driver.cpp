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
//  Serial.println("Current read is " + (String)current);
 
  return current;
}


//int updateMotor(const int desired_speed, const int actual_speed, const int current)
int updateMotor(s_Controls &State, s_Telemetry& telemetry)
{
  telemetry.actualCurrent = currentRead(DRILL_CS, READ_ACC);
  
  //Calculates current that should be seen when operating at desired speed
  telemetry.goalCurrent = calculate_desired_current(State.goalSpeed);
  
  //Check to see if motor is struggling or stuck
  if(telemetry.actualCurrent > telemetry.goalCurrent)
  {
    //Calculates current that should be seen when operating at actual, elevated speed
    float max_current = calculate_desired_current(telemetry.actualSpeed);
    max_current *= MAX_VARIATION;
    
    //Soft current cutoff. Gradually scales back speed if current is excessive
    if(telemetry.actualCurrent > CUTOFF_CURRENT)
    {
      telemetry.actualSpeed -= SPEED_STEP;
    } else if(telemetry.actualSpeed > DRILL_FULL_SPEED)
    {
      telemetry.actualSpeed = DRILL_FULL_SPEED;
    //Drill is still stalled out, not running at max power
    } else if(telemetry.actualCurrent > max_current)
    {
      telemetry.actualSpeed += SPEED_STEP;
    //Drill has broken stall, scale back speed
    } else {  
      telemetry.actualSpeed -= SPEED_STEP;
    } 
  } else
  {
    telemetry.actualSpeed = State.goalSpeed;
  }
  return telemetry.actualSpeed;
}


float calculate_desired_current(int motor_speed)
{  
  float current = (CURRENT_SLOPE * motor_speed) + CURRENT_INTERCEPT;
//  Serial.println("Desired Current");
//  Serial.println(current);
  return current;
}

void setDriverOutput(const int motor_speed)
{
//  Serial.println("Setting motor speed");
  Serial.println(motor_speed);
  analogWrite(MOT_PWM, motor_speed);
}

void SetDrillDirection(const s_Controls &state)
{
  if(state.direction)
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
  analogWrite(MOT_PWM, state.actualSpeed);
  return;
}

