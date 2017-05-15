#include "RoveBoard.h"
#include "RoveComm.h"
#include <stdint.h>


//enums
typedef enum CommandResult
{
  Success,
  Fail
} CommandResult;

typedef enum CommandIDs
{
  ScienceCommand=0x710,
  ScienceCarousel=0x711  
}CommandIDs;

typedef enum ScienceCommands
{
  sensorAllEnable=0,
  sensorAllDisable=1,
  sensor1Enable=2,
  sensor1Disable=3,
  sensor2Enable=4,
  sensor2Disable=5,
  sensor3Enable=6,
  sensor3Disable=7,
  sensor4Enable=8,
  sensor4Disable=9,
  sensor5Enable=10,
  sensor5Disable=11,
  sensor6Enable=12,
  sensor6Disable=13,
  sensor7Enable=14,
  sensor7Disable=15,
  laserOn=16,
  laserOff=17,
  flapOpen=18,
  flapClose=19,
  spectro=20
    
} ScienceCommands;

typedef enum SensorDataIDs
{
 air_temperature_ID = 0x720,
 soil_temperature_ID = 0x721,
 air_humidity_ID = 0x722,
 soil_humidity_ID = 0x723,
 UV_intensity_ID = 0x729,
 pressure_ID = 0x72A,
 methane_ID = 0x728,
 sensor9_ID = 0x72D 
}SensorDataIDs;


//var or pins
const uint32_t WATCHDOG_TIMEOUT_US = 2000000; //the amount of microseconds that should pass without getting a transmission from base station before the arm ceases moving for safety
const uint8_t IP_ADDRESS [4] = {192, 168, 1, 135};

uint8_t spectro_motor_in_1 = PM_5;
uint8_t spectro_motor_in_2 = PB_3;
uint8_t flapPin = PL_0;
uint8_t carouselPin = PL_2;
int car_positions[5] = {0, 36, 108, 144, 180};


uint8_t laserPin = 46; // PD_5
uint8_t photoPin1 = PD_2;
uint8_t photoPin2 = PD_3;
uint8_t LEDPin = PF_0;

uint8_t UVPin = PE_1;
uint8_t airTempPin = PD_1;
uint8_t soilTempPin = PB_5;
uint8_t methanePin = PK_1;
uint8_t airHumidityPin = PD_0;
uint8_t soilMoisturePin = PE_3;
const uint8_t airPressurePin = PM_4;

//functions

void initialize();//All important pre-loop setup goes here
void spectrometer();//Full spectrometer sub-routine

void turnOnLaser();//Turns On the Spectrometer Laser
void turnOffLaser();//Turns Off the Spectrometer Laser
void openFlap();//Opens the Sample Cache Flap
void closeFlap();//Closes the Sample Cache Flap
void rotateCarousel(const uint16_t pos);//Rotates carosel to position 0-4 from current position given a position (0-4)
void spectroMotorOff();//Turns off the spectrometer motor
float instantSoilTemp();//Returns one Soil Temperature reading
float instantAirTemp();//Returns one Air Termperature reading
float instantUV();//Return one UV intensisty reading
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);//Maps the float value for UV intensity
//float instantPressure();//Returns one pressure reading but has problems so is not implemented
void spectroMotorForward();//Turns the spectrometer motor on, in the forward direction
void spectroMotorReverse();//Turns the spectrometer motor on, but in the reverse direction
float instantAirHumidity();//Returns one Humidity sensor reading
float instantSoilHumidity();//Returns reading from Soil Moisture sensor
float instantMethane();//Returns Methane sensor reading
float instantPressure();//Returns Air Pressure sensor reading
void kill();
