
/**** Pin Connection Diagram **** 
Sensors            Arduino

gps ser rx ------- D2
gps ser tx ------- D3

sonar0 ser rx ---- D4
sonar0 ser tx ---- D5
sonar1 ser rx ---- D6
sonar1 ser tx ---- D7
sonar2 ser rx ---- D8
sonar2 ser tx ---- D9

imu i2c clock ---- SCL
imu i2c data ----- SDA

volt sense pin --- A0
volt ref pin ----- GND/AREF?
*********************************/

#ifndef AUXILIARY_ERC_H_
#define AUXILIARY_ERC_H_

//#include "Arduino.h"


// enable sensors
//#define ENABLE_GPS    TRUE
//#define ENABLE_IMU    TRUE
#define ENABLE_SONAR  TRUE
//#define ENABLE_VOLT   TRUE

// sensor struct ids
#define GPS_STRUCT_ID 140;
#define IMU_STRUCT_ID 141;
#define SONAR_STRUCT_ID 142;
#define VOLT_STRUCT_ID 143;

// Arduino to sensor pinout
#define DUMMY_PIN   10    // dummy pin - DNC
#define MOBO_RX      5    // software serial digital pin
#define MOBO_TX     13    // software serial digital pin
#define GPS_RX       2    // software serial digital pin
#define GPS_TX       0    // software serial digital pin
#define SON0_TX      DUMMY_PIN 
#define SON0_RX      1    // software serial digital pin
#define SON0_PULSE   4    // digital pin
#define SON1_TX      DUMMY_PIN     
#define SON1_RX     12    // software serial digital pin
#define SON1_PULSE   6    // digital pin
#define SON2_TX      DUMMY_PIN    
#define SON2_RX      8    // software serial digital pin
#define SON2_PULSE   9    // digital pin
#define VOLT_PIN     0    // analog pin

//#define PRINT
#define send_delay 100 // ms between transmitting ET data
#define pulse_delay 200 // ms to hold pulse pin high to prompt for reading

// gps-specific setup
#define GPSECHO false //set to true if you want raw GPS data printed to serial monitor

void send_data(EasyTransfer &et){
  et.sendData();
  delay(send_delay);
  return;
}

#endif
