/*----------------------------------------------------------
  Programmer: Owen Chiaventone   2014
  Missouri S&T Mars Rover Design Team
  
  Sample Return End Effector control software
  General control - headers
-----------------------------------------------------------*/

#ifndef ENDEFFECTOR_H
#define ENDEFFECTOR_H
#include "Arduino.h"
#include "DataStructures.h"
//Pin Definitions
const int ADC0 = 0;
const int ADC1 = 1;
const int ADC2 = 2;
const int DRILL_CS = 3;
const int IR_SDA = 4;
const int IR_SCL = 5;
const int MOT_INA = 7;
const int MOT_INB = 8;
const int MOT_PWM = 9;
const int GAS_CTRL = 10;
const int HEAT_CTRL = 12;

//Detects changes in input and updates accordingly
//will update heater
void discreteUpdates(s_Controls& state, const s_Controls& prev_state, s_Telemetry& telemetry);

//Updates sensors, drill, or heater depending on what is powered
//Should be run as frequently as possible
void continuousUpdates(s_Controls& state, s_Telemetry& telemetry);

#endif
