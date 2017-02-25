#include "RoveBoard.h"
#include "RoveComm.h"
#include <stdint.h>
#include "JointControlFramework.h"

//enums
typedef enum CommandResult
{
  Success,
  Fail
} CommandResult;


//var/pins
const uint32_t WATCHDOG_TIMEOUT_US = 2000000; //the amount of microseconds that should pass without getting a transmission from base station before the arm ceases moving for safety
const uint8_t IP_ADDRESS [4] = {192, 168, 1, 135};

//functions

void initialize();

void operate_flap(const int16_t flap);
void turnLaserOn();
void turnLaserOff();
