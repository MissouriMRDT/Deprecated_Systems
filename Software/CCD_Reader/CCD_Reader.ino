#include <Arduino.h>

#define CLOCK_PIN        8
const int ICG =         4;
const int SH =          5;
const int OS =          0; //Analog

#define CLOCK_FREQUENCY 800000 //800 kHz
#define CLOCK_MAX_DUTY  2       // 0 = off, 1 = 50%, 2 = on

void setUpClocks();
 
void setup() {
  
  setUpClocks();
  Serial.begin(115200);
}
 
void loop() 
{

}

void setUpClocks()
{
  //Enable PWM controller peripheral
  pmc_enable_periph_clk(PWM_INTERFACE_ID);
  PWMC_ConfigureClocks(CLOCK_FREQUENCY * CLOCK_MAX_DUTY, 0, VARIANT_MCK);
 
  PIO_Configure(
    g_APinDescription[CLOCK_PIN].pPort,
    g_APinDescription[CLOCK_PIN].ulPinType,
    g_APinDescription[CLOCK_PIN].ulPin,
    g_APinDescription[CLOCK_PIN].ulPinConfiguration);
 
  uint32_t channel = g_APinDescription[CLOCK_PIN].ulPWMChannel;
  
  PWMC_ConfigureChannel(PWM_INTERFACE, channel , PWM_CMR_CPRE_CLKA, 0, 0);
  PWMC_SetPeriod(PWM_INTERFACE, channel, CLOCK_MAX_DUTY); //1 uS pulses
  PWMC_EnableChannel(PWM_INTERFACE, channel);
  PWMC_SetDutyCycle(PWM_INTERFACE, channel, 1);
 
  //pmc_mck_set_prescaler(2);
}
