//----------------------------------
// CCD Reader for TCD1304DG CCD and Arduino Due
// 
// Missouri S&T Mars Rover Design Team 2015
// author: Owen Chiaventone
//
// Reads data from the TCD1304DG linear CCD and reports it 
// over UART.
//
// This is a challenge because of the very tight clocking
// requirements and ADC work invovled. 
// A lot of low-level SAM3X8E code was required, so
// this can't be considered "true" arduino code.
//
//-------------------------------------

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
const int ICG =         4; //PC26
const int SH =          5; //PC25
const int OS =          0; //Analog

//We need port manipulation for some of these, so it's best to 
// keep ICG and SH on port C

//Bitmasks for quick direct port manipulation. This gets ugly fast
const uint32_t SH_HIGH_ICG_LOW = 0x02000000;
const uint32_t SH_LOW_ICG_LOW = 0x00000000;
const uint32_t SH_LOW_ICG_HIGH = 0x04000000;
const uint32_t SH_HIGH_ICG_HIGH = 0x06000000;

//---------------------------
// CCD Data parameters
//---------------------------

const int PIXEL_COUNT =      3648;

//The Sensor has several "Dummy" elements that aren't active
const int JUNK_ELEMENTS_PRE = 32;
const int JUNK_ELEMENTS_POST = 14;

//-----------------------------
// CCD Data Clocking
//-----------------------------

//const int DATA_FREQUENCY = CLOCK_FREQUENCY / 3; // 3 clock cycles per data cycle
//Hardcoding to avoid weird FPU dividing behavior
const int DATA_FREQUENCY = 300000;


//This must be volatile and at least 32 bits or timing messes up
volatile uint32_t data_counter = 0;                      
const uint32_t MAX_DATA_COUNT = 900000; //Approx. 3 seconds
    
//Realtime cycles to wait before grabbing another sample. Gives us time to send data out.
const int PRE_SAMPLE_CYCLES = 5000;
const int POST_SAMPLE_CYCLES = 5000;
const int ICG_TIME = 2; //Measured in Data Clocks


//Precalculate times when important things happen to save some runtime cycles
const int FIRST_ELEMENT_TIME = PRE_SAMPLE_CYCLES + ICG_TIME;
const int FIRST_DATA_ELEMENT_TIME = FIRST_ELEMENT_TIME + JUNK_ELEMENTS_PRE;
const int LAST_DATA_ELEMENT_TIME = FIRST_DATA_ELEMENT_TIME + PIXEL_COUNT;
const int LAST_ELEMENT_TIME = LAST_DATA_ELEMENT_TIME + JUNK_ELEMENTS_POST;

//---------------------------
// Main program
//---------------------------

void setUpClocks();

void dataInterrupt();
 
void setup() {
  
  startClockPWM();
  
  //Get next unused timer on the Due as the data timer
  DueTimer dataTimer = DueTimer(6);
  dataTimer.attachInterrupt(dataInterrupt);
  dataTimer.setFrequency(DATA_FREQUENCY);
  dataTimer.start();
  
  pinMode(ICG, OUTPUT);
  pinMode(SH, OUTPUT);
  digitalWrite(ICG, HIGH);
  digitalWrite(SH, LOW);
  
  Serial.begin(115200);
}
 
void loop() 
{
  while(data_counter < PRE_SAMPLE_CYCLES); //Wait to clear out the remaining data

  //--------------------
  // Send the Integration start signal
  //--------------------
  
  //  digitalWrite(ICG, LOW);
  //  digitalWrite(SH, HIGH);
  REG_PIOC_ODSR = SH_HIGH_ICG_LOW;
  
  while(data_counter < PRE_SAMPLE_CYCLES + 1);
  //  digitalWrite(SH, LOW);
  REG_PIOC_ODSR = SH_LOW_ICG_LOW;
  
  while(data_counter < PRE_SAMPLE_CYCLES + 2);
  
  REG_PIOC_ODSR = SH_HIGH_ICG_HIGH;
  //  digitalWrite(ICG, HIGH);
  
  //---------------------
  // Send the integration stop signal
  //---------------------
  while(data_counter < LAST_ELEMENT_TIME); //Wait for last element to clock through
  REG_PIOC_ODSR = SH_HIGH_ICG_LOW;
  
  while(data_counter < LAST_ELEMENT_TIME + 1);
  REG_PIOC_ODSR = SH_LOW_ICG_LOW;
  while(data_counter < LAST_ELEMENT_TIME + 2);
  REG_PIOC_ODSR = SH_HIGH_ICG_HIGH;
  
  
  while(data_counter < MAX_DATA_COUNT - 1);
}

void dataInterrupt()
{
  data_counter++;
  
  //Wrap around and restart on overflow
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
  
  //Enable this channel and set parameters
  PWMC_ConfigureChannel(PWM_INTERFACE, channel , PWM_CMR_CPRE_CLKA, 0, 0);
  PWMC_SetPeriod(PWM_INTERFACE, channel, CLOCK_MAX_DUTY); 
  PWMC_EnableChannel(PWM_INTERFACE, channel);
  PWMC_SetDutyCycle(PWM_INTERFACE, channel, 1);
 
  //pmc_mck_set_prescaler(2);
}
