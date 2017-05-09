#include "RoveBoard.h"
#include "RoveComm.h"
#include <stdint.h>

//enums
typedef enum CommandResult
{
  Success,
  Fail
} CommandResult;

typedef enum CommmandID
{
  ScienceArmDrive = 0x730,
  ScienceArmPosition = 0x731,//not yet used 
  ScienceDrillDrive = 209,//TODO: Wrong value, use 0x362
  ScienceSoilSensors = 0x710//TODO need command ID for soil sensors
}CommandID;

typedef enum DataID
{
  ScienceSoilTemp = 0x72B,
  ScienceSoilMoisture = 0x72C
} DataID;

typedef enum ArmDrive
{
  armForward=775,
  armReverse=-775,
  armOff=0    
}ArmDrive;

typedef enum DrillDrive
{
  DrillF=775,
  DrillOff=0,
  DrillR=-775
}DrillDrive;

typedef enum SoilSensor
{
  temp_ON = 4,
  temp_OFF = 5,
  moisture_ON = 8,
  moisture_OFF = 9
}SoilSensor;

//var or pins
const uint32_t WATCHDOG_TIMEOUT_US = 2000000; //the amount of microseconds that should pass without getting a transmission from base station before the arm ceases moving for safety
const uint8_t IP_ADDRESS [4] = {192, 168, 1, 139};//TODO: 135 is the science IP and is used for testing only, 139 is science arm board

//functions
void kill();//Disables all motion to the arm
void motorOn();//Turns the arm's motor on, in the forward direction
void motorReverse();//Turns the arm's motor on, in the backward direction
void motorCoast();//Turns the arm's motor to a low off state
void motorBrake();//Turns the arm's motor to an activly stopped state

void drillForward();//Turns the drill on, forward
void drillReverse();//Turns the drill on, backward
void drillCoast();//Turns the drill off

float instantSoilHumidity();//Placeholder
float instantSoilTemp();//Returns one Soil Temperature reading


//pin definitions
//arm motor pins
uint8_t arm_in_1 = PL_5;
uint8_t arm_in_2 = PD_0;
uint8_t arm_decay = PN_2;
uint8_t arm_nFault = PL_2;
uint8_t arm_nSleep = PN_3;
uint8_t arm_nReset = PL_3;
uint8_t arm_I0 = PL_4;
uint8_t arm_I1 = PH_3;
uint8_t arm_I2 = PG_0;
uint8_t arm_I3 = PH_2;
uint8_t arm_I4 = PF_3;

//drill pins
uint8_t drill_pin_1 = PB_3;
uint8_t drill_pin_2 = PB_2;

//other pins
uint8_t LEDPin = PF_0;
uint8_t moistPin = PE_3;
uint8_t tempPin = PE_2;


