
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
#define ENABLE_GPS    true
#define ENABLE_IMU    false
#define ENABLE_SONAR  true
#define ENABLE_VOLT   true

// sensor struct ids
#define SENSOR_STRUCT_ID     144;
#define GPS_STRUCT_ID        140;
#define IMU_STRUCT_ID        141;
#define SONAR_STRUCT_ID      142;
#define VOLT_STRUCT_ID       143;

// Arduino to sensor pinout
#define DUMMY_PIN   10    // dummy pin - DNC
#define MOBO_RX      5    // brd <- mobo, software serial digital pin
#define MOBO_TX     13    // brd -> mobo, software serial digital pin
#define GPS_RX       2    // brd <- gps, software serial digital pin
#define GPS_TX       0    // brd -> gps, software serial digital pin
#define SON0_TX      DUMMY_PIN 
#define SON0_RX      1    // brd <- sonar, software serial digital pin
#define SON0_PULSE   4    // brd -> sonar, digital pin
#define SON1_TX      DUMMY_PIN     
#define SON1_RX     12    // brd <- sonar, software serial digital pin
#define SON1_PULSE   6    // brd -> sonar, digital pin
#define SON2_TX      DUMMY_PIN    
#define SON2_RX      8    // brd <- sonar, software serial digital pin
#define SON2_PULSE   9    // brd -> sonar, digital pin
#define VOLT_PIN     0    // brd <- voltmeter, analog pin

//#define PRINT
#define send_delay 100 // ms between transmitting ET data
#define pulse_delay 200 // ms to hold pulse pin high to prompt for reading

// gps-specific setup
// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false
#define PRINT_TO_SERIAL true

struct Sensor_Data
{
  uint8_t struct_id;
  bool gps_fix;
  uint8_t gps_fixquality;
  uint8_t gps_satellites;
  int32_t gps_latitude_fixed;
  int32_t gps_longitude_fixed;
  float gps_altitude;
  float gps_speed;
  float gps_angle;
  float imu_heading;
  uint8_t son0_dist;
  uint8_t son1_dist;
  uint8_t son2_dist;
  uint16_t rawvoltage;
};

#endif
