#include <Arduino.h>
#include "DueTimer.h"

//---------------------------------------
// CCD Master Clock. Too fast to bit-bang
//---------------------------------------

#define CLOCK_FREQUENCY 900000 //900 kHz
#define CLOCK_MAX_DUTY  2       // 0 = off, 1 = 50%, 2 = on

//----------------------------
// CCD Pin assignments
//----------------------------

#define CLOCK_PIN       8
const int ICG =         4;
const int SH =          5;
const int OS =          0; //Analog

//We need port manipulation for some of these

//---------------------------
// CCD Data parameters
//---------------------------

const int PIXEL_COUNT =      3648;

//The Sensor has several "Dummy" elements that aren't active
const int JUNK_ELEMENTS_PRE = 32;
const int JUNK_ELEMENTS_POST = 14;

//Realtime cycles to wait before grabbing another sample. Gives us time to send data out.
const int PRE_SAMPLE_CYCLES = 300;
const int POST_SAMPLE_CYCLES = 300;
const int ICG_TIME = 2; //Measured in Data Clocks

//Timing Parameters

//-----------------------------
// CCD Data Clocking
//-----------------------------

const int DATA_FREQUENCY = CLOCK_FREQUENCY / 3; // 6 clock cycles per data cycle
uint32_t data_counter = 0;                      // This MUST be a 32 bit value
const uint32_t MAX_DATA_COUNT = 
    PRE_SAMPLE_CYCLES +
    ICG_TIME +
    JUNK_ELEMENTS_PRE +
    PIXEL_COUNT +
    JUNK_ELEMENTS_POST +
    POST_SAMPLE_CYCLES;
    
void setUpClocks();

void dataInterrupt();
 
void setup() {
  
  startClockPWM();
  
  //Get next unused timer on the Due as the data timer
  DueTimer dataTimer = DueTimer::getAvailable();
  dataTimer.attachInterrupt(dataInterrupt);
  dataTimer.setFrequency(DATA_FREQUENCY);
  
  
  Serial.begin(115200);
}
 
void loop() 
{
  while(data_counter < PRE_SAMPLE_CYCLES); //Wait to clear out the remaining data
  
  //DigitalWrite isn't fast enough, so we use port manipulation
  //Set ICG to low
  
}

void dataInterrupt()
{
  data_counter++;
  data_counter %= MAX_DATA_COUNT;
}

void startClockPWM()
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
