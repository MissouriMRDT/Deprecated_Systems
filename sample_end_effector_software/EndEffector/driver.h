/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  VNH5019 Motor Driver Control - Header
  Used to control the drill and the thermo test heater
-----------------------------------------------------------*/

#ifndef DRIVER_H
#define DRIVER_H
#include "Arduino.h"
#include "DataStructures.h"
#include "endeffector.h"

//Constants
const int DRILL_FULL_SPEED = 255;
const int DRILL_OFF = 0;
//Current cutoff: calculated using VNH5019 datasheet. 
//Assumes linear response for CS pin. Cuts off at approx 6A.
const int CUTOFF_CURRENT = 172; 
const int MAINTAIN_TOLERANCE = 2; //Variation allowed in maintainCurrent before changing power

/* 
   Current Draw Prediction: These values are based on the linear regression of the 
   current sense data vs pwm of the motor running with no resistance. To get this data
   see MotCurrentSenseTest
*/
const float CURRENT_SLOPE = 0.07614379; //Slope from linear regression of current sense vs pwm
const float CURRENT_INTERCEPT = 27.0147; //Intercept from linear regression of current sense vs pwm
const float MAX_VARIATION = 1.3; //Maximum amount current draw is allowed to deviate from model
const int READ_ACC = 10; //milliseconds current sense reading is averaged over
const int SPEED_STEP = 16; //Smallest amount motor will increase its speed to overcome stalls

//Reads voltage average over acc milliseconds from pin, meant for use with current sense pins
//Pre: 
//Post:
int currentRead(int pin, int acc = 0);

// Ensures that a motor is performing within bounds defined in State
// Pre: goalSpeed is defined in state
// Post: goalCurrent, actualCurrent, actualSpeed updated in State. 
// Note: New speed is not actually applied, just calculated.
int updateMotor(s_Controls &State, s_Telemetry& telemetry);

//Calculates expected reading on the current sense pin for a given speed
// based on data from testing
float calculate_desired_current(int motor_speed);

//Sets the drill direction based on the direction variable of the given state
void SetDrillDirection(const s_Controls &state);

//Tries to keep the output at a constant current
//
void maintainCurrent(s_Telemetry& telemetry, const int current);

#endif
