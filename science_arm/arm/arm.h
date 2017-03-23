#include "RoveBoard.h"
#include "RoveComm.h"
#include <stdint.h>


//enums
typedef enum CommandResult
{
  Success,
  Fail
} CommandResult;


//var or pins
const uint32_t WATCHDOG_TIMEOUT_US = 2000000; //the amount of microseconds that should pass without getting a transmission from base station before the arm ceases moving for safety
const uint8_t IP_ADDRESS [4] = {192, 168, 1, 135};//135 is the science IP and is used for testing only

//functions

void initialize();//All important pre-loop setup goes here
void doArmStuff();
void doOtherArmStuff();

void motorOn();
void motorReverse();
void motorCoast();
void motorBrake();

void drillForward();
void drillReverse();
void drillCoast();



