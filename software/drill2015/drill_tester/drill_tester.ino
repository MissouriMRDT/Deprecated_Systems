/*******************
MRDT 2015 Drill
Mike Miles
*******************/

#include <SoftwareSerial.h>

const int pin_M1EN = 6;
const int pin_M1INA = 2;
const int pin_M1INB = 4;
const int pin_M1PWM = 9;
const int pin_M1CS = A0;

SoftwareSerial moboSerial(0, 1); // (Rx, Tx)

const char STOP = 0x00;
const char FORW = 0x01;
const char REV = 0x02;

char motorCmd = STOP;
bool motorCmd_M1EN = 0;
bool motorCmd_M1INA = 0;
bool motorCmd_M1INB = 0;
bool motorCmd_M1PWM = 0;

int DELAY = 4000;

void setup() {
  // Serial with xbee
  Serial.begin(57600);
  
  // config motor driver select pins
  pinMode(pin_M1EN, OUTPUT);
  pinMode(pin_M1INA, OUTPUT);
  pinMode(pin_M1INB, OUTPUT);
  pinMode(pin_M1PWM, OUTPUT);
  pinMode(pin_M1CS, INPUT);
}

void loop() {
  motor_stop();
  delay(DELAY);
  motor_forw();
  delay(DELAY);
  motor_stop();
  delay(DELAY);
  motor_rev();
  delay(DELAY);
}

void motor_forw(){
  Serial.write(FORW);
//  motorCmd_M1EN = 1;
//  motorCmd_M1INA = 1;
//  motorCmd_M1INB = 0;
//  motorCmd_M1PWM = 1;
//  write_cmd();
}

void motor_rev(){
  Serial.write(REV);
//  motorCmd_M1EN = 1;
//  motorCmd_M1INA = 0;
//  motorCmd_M1INB = 1;
//  motorCmd_M1PWM = 1;
//  write_cmd();
}

void motor_stop(){
  Serial.write(STOP);
//  motorCmd_M1EN = 1;
//  motorCmd_M1INA = 0;
//  motorCmd_M1INB = 0; 
//  motorCmd_M1PWM = 0;
//  write_cmd();
}

void write_cmd(){
  digitalWrite(pin_M1EN, motorCmd_M1EN);
  digitalWrite(pin_M1INA, motorCmd_M1INA);
  digitalWrite(pin_M1INB, motorCmd_M1INB);
  digitalWrite(pin_M1PWM, motorCmd_M1PWM);
}
