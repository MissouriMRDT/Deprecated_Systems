#ifndef control_functions
#define control_functions
#include "Arduino.h"

//Pin Definitions
const int ADC0 = 0;
const int ADC1 = 1;
const int ADC2 = 2;
const int IR_SDA = 4;
const int IR_SCL = 5;
const int MOT_INA = 7;
const int MOT_INB = 8;
const int MOT_PWM = 9;
const int GAS_CTRL = 10;
const int HEAT_CTRL = 12;

const int DRILL_FULL_SPEED = 255;
const int DRILL_OFF = 0;

int InitializeIrThermo();
void SetDrillSpeed(byte speed);
void SetDrillDirection(byte direct);
void CollectGasData(byte unused);
void ToggleHeatingElement(byte state);
void CollectHeatData(byte unused);
void DebugBlink(byte onoff);
void Shake(unsigned long duration); // Duration is time to shake in milliseconds

void SetDrillSpeed(byte speed)
{
  analogWrite(MOT_PWM, speed);
}

//0 for reverse, 1 for forward
void SetDrillDirection(byte direct)
{
  if(direct!=0)
  {
    digitalWrite(MOT_INA,HIGH);
    digitalWrite(MOT_INB,LOW);
  }
  else
  {
    digitalWrite(MOT_INA,LOW);
    digitalWrite(MOT_INB,HIGH);
  }
}

void CollectGasData(byte unused)
{
  digitalWrite(GAS_CTRL, HIGH);
  delay(1000); //allows the gas sensors to heat up and stabilize
  int methane_reading=analogRead(ADC0);
  int hydrogen_reading=analogRead(ADC0);
  int ammonia_reading=analogRead(ADC0);
  
  //Replace with code to send data to MOBO
  Serial.println("methane reading: " + methane_reading);
  Serial.println("hydrogen reading: " + hydrogen_reading);
  Serial.println("ammonia reading: " + ammonia_reading);    
}

//1 for on, 0 for off


void CollectHeatData(byte unused)
{
  //i2c thermometer reading here
  //transmit data
}

//Turns the debug LED on if 
void DebugBlink(byte onoff)
{
  pinMode(13, OUTPUT);
  if(onoff = 0)
  {
    digitalWrite(13, LOW);
    Serial.println("Blink off at" + millis());
  } 
  else
  {
    digitalWrite(13, HIGH);
    Serial.println("Blink on at" + millis());
  }
}

void Shake(unsigned long duration)
{
  const unsigned long timer = millis() + duration; //Calculates Finish time for shake operation
  while(timer <= millis())
  {
    SetDrillSpeed(0);
    SetDrillDirection(1);
    SetDrillSpeed(DRILL_FULL_SPEED);
    delay(10);
    SetDrillSpeed(0);
    SetDrillDirection(0);
    SetDrillSpeed(DRILL_FULL_SPEED);
    delay(10);
  }
  SetDrillSpeed(0);
}

#endif

