#include "wiring_private.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"

const int ICG_PIN = 38;
const int SH_PIN = 37;
const int MASTER_PIN = 7;

uint8_t icg_timer;
uint8_t sh_timer;
uint8_t master_timer;

uint32_t icg_timerBase;
uint32_t sh_timerBase;
uint32_t master_timerBase;

uint32_t master_timerAB;
uint32_t icg_timerAB;
uint32_t sh_timerAB;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  icg_timer = digitalPinToTimer(ICG_PIN);
  sh_timer = digitalPinToTimer(SH_PIN);
  master_timer = digitalPinToTimer(MASTER_PIN);
  
  master_timerBase = getTimerBase(timerToOffset(master_timer));
  icg_timerBase = getTimerBase(timerToOffset(icg_timer));
  sh_timerBase = getTimerBase(timerToOffset(sh_timer));
  
  master_timerAB = TIMER_A << timerToAB(master_timer);
  icg_timerAB = TIMER_A << timerToAB(icg_timer);
  sh_timerAB = TIMER_A << timerToAB(sh_timer);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.print("Master Pin: ");
  Serial.println(MASTER_PIN);
  Serial.print("Master Timer: ");
  Serial.println(master_timer);
  Serial.print("Master TimerBase: ");
  Serial.println(master_timerBase);
  Serial.print("Master TimerAB: ");
  Serial.println(master_timerAB);
  
  Serial.print("SH Pin: ");
  Serial.println(SH_PIN);
  Serial.print("SH Timer: ");
  Serial.println(sh_timer);
  Serial.print("SH TimerBase: ");
  Serial.println(sh_timerBase);
  Serial.print("SH TimerAB: ");
  Serial.println(sh_timerAB);
  
  Serial.print("ICG Pin: ");
  Serial.println(ICG_PIN);
  Serial.print("ICG Timer: ");
  Serial.println(icg_timer);
  Serial.print("ICG TimerBase: ");
  Serial.println(icg_timerBase);
  Serial.print("ICG TimerAB: ");
  Serial.println(icg_timerAB);
}


/* 
Master Pin: 7
Master Timer: 4
Master TimerBase: 1073942528
Master TimerAB: 255

SH Pin: 37
SH Timer: 13
SH TimerBase: 1073963008
SH TimerAB: 255

ICG Pin: 38
ICG Timer: 12
ICG TimerBase: 1073950720
ICG TimerAB: 65280
*/
