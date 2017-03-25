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
  ScienceArmPosition = 0x731, 
  ScienceDrillDrive = 0x362
}CommandID;

typedef enum ArmDrive
{
  armForward=3,
  armReverse=4,
  armOff=5    
}ArmDrive;

typedef enum DrillDrive
{
  DrillF=1,
  DrillOff=0,
  DrillR=2
}DrillDrive;

//var or pins
const uint32_t WATCHDOG_TIMEOUT_US = 2000000; //the amount of microseconds that should pass without getting a transmission from base station before the arm ceases moving for safety
const uint8_t IP_ADDRESS [4] = {192, 168, 1, 135};//TODO: 135 is the science IP and is used for testing only, 139 is science arm board

//functions
void initialize();//All important pre-loop setup goes here
void kill();//Disables all motion to the arm
void motorOn();//Turns the arm's motor on, in the forward direction
void motorReverse();//Turns the arm's motor on, in the backward direction
void motorCoast();//Turns the arm's motor to a low off state
void motorBrake();//Turns the arm's motor to an activly stopped state

void drillForward();//Turns the drill on, forward
void drillReverse();//Turns the drill on, backward
void drillCoast();//Turns the drill off



