#define CCD_CLOCK_LINE 4
#define CCD_SHUTTER 5
#define CCD_ICG 6
#define CCD_OS 0

//32-bit integer
int clockCycle;

const int CLOCKS_PER_CCD_CYCLE = 3;
const int SIGNAL_ELEMENTS = 3648;
const int PRE_DUMMY_ELEMENTS = 32;
const int POST_DUMMY_ELEMENTS = 14;

#include "DueTimer.h"

uint32_t pwmPin = 8;
uint32_t maxDutyCount = 2;
uint32_t clkAFreq = 1000ul;
uint32_t pwmFreq = 1000ul; 
 
void setup() {
  pmc_enable_periph_clk(PWM_INTERFACE_ID);
  PWMC_ConfigureClocks(clkAFreq, 0, VARIANT_MCK);
 
  PIO_Configure(
    g_APinDescription[pwmPin].pPort,
    g_APinDescription[pwmPin].ulPinType,
    g_APinDescription[pwmPin].ulPin,
    g_APinDescription[pwmPin].ulPinConfiguration);
 
  uint32_t channel = g_APinDescription[pwmPin].ulPWMChannel;
  PWMC_ConfigureChannel(PWM_INTERFACE, channel , pwmFreq, 0, 0);
  PWMC_SetPeriod(PWM_INTERFACE, channel, maxDutyCount);
  PWMC_EnableChannel(PWM_INTERFACE, channel);
  PWMC_SetDutyCycle(PWM_INTERFACE, channel, 1);
 
  pmc_mck_set_prescaler(2);
}
 
void loop() 
{
}
