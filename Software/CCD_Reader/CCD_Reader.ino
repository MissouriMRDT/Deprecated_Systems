
//Clock is on Port C, pin 26 (arduino pin 4)
#define CLK_PORT             REG_PIOC_ODSR
#define CLK_LINE             26
#define CLK_LINE_ARDUINO     4

#define CCD_SHUTTER 5
#define CCD_ICG 6
#define CCD_OS 0

#include "DueTimer.h"

//32-bit integer
volatile uint32_t clockCycle = 0;
volatile bool bclock = false;

const int CLOCKS_PER_CCD_CYCLE = 3;
const int SIGNAL_ELEMENTS = 3648;
const int PRE_DUMMY_ELEMENTS = 32;
const int POST_DUMMY_ELEMENTS = 14;

//Number of clocks in a complete read cycle
const uint32_t MAX_CLOCK = 1000000;

uint32_t pwmPin = 8;
uint32_t maxDutyCount = 2;

//Set up clocks for 1 Mhz
uint32_t clkAFreq = 42000000ul;
uint32_t pwmFreq = 1000000ul; 


void fastDigitalWrite();
void setUpClocks();


void ccd_clock_ISR()
{
//  clockCycle ++;
//  clockCycle %= MAX_CLOCK;
  
  //Flip the clock line with a bitwise XOR
  CLK_PORT ^= 1 << CLK_LINE;
}
 
void setup() {
  
  pinMode(CLK_LINE_ARDUINO, OUTPUT);
//  setUpClocks();
  Timer1.attachInterrupt(ccd_clock_ISR);
  
  //Call every microsecond
  Timer1.setFrequency(1000000);
  Timer1.start();

  
  Serial.begin(115200);
}
 
void loop() 
{
  Serial.print("Time: ");
  Serial.println(clockCycle, DEC);
  delay(300);
}

void setUpClocks()
{
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
