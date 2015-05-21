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
// Clocking is provided by the PWM generator on lines 8 and 9
// A timer is used to keep the software in sync with the PWM
//
// Datasheet: 
//-------------------------------------

#include <Arduino.h>
#include "DueTimer.h"

//---------------------------------------
// User configurable settings
//---------------------------------------

//Number of times to take a complete image per second
const uint32_t SAMPLE_RATE_HZ = 3;

//Sends one out of every (RESOLUTION_DIVIDER) data points
const uint32_t RESOLUTION_DIVIDER = 5;

//---------------------------------------
// CCD Clocking. Uses PWM generators
//---------------------------------------

const int CLOCK_FREQUENCY = 1000000;  //
const int CLOCK_MAX_DUTY = 2;        // 0 = off, 1 = 50%, 2 = on
const int CLOCKS_PER_SH_PULSE = 4;

//----------------------------
// CCD Pin assignments
//----------------------------

const int CLOCK_PIN   = 8;
const int ICG =         4; //PC26
const int SH =          9; 
const int OS =          0; //Analog

//This is kind of a weird workaround, but I don't know how 
// to tell when the PWM lines go high, so I'm 
// watching the PWM signals with another pin and using
// it to sync up timers
const int SH_TRIGGER =  7; //Wire into SH

//Bitmasks for quick direct port manipulation. This gets ugly fast
const uint32_t ICG_LOW = 0x00000000;
const uint32_t ICG_HIGH = 0x04000000;

//---------------------------
// CCD Data parameters
//---------------------------

const int PRE_SAMPLE_DATA_CLOCKS = 20;
const int JUNK_ELEMENTS_PRE  = 32;
const int SIGNAL_ELEMENTS    = 3648;
const int JUNK_ELEMENTS_POST = 14;
const int TOTAL_ELEMENTS     = 3694;

//----------------------------
// Global Variables
//----------------------------

int data[SIGNAL_ELEMENTS];
int current_pixel;
volatile uint32_t sh_gate_rise;
DueTimer dataTimer(1);

//---------------------------
// Main Program
//---------------------------


void startClockPWM();
void startSH_PWM();
void stopSH_PWM();
void dataInterrupt(); 
void setUpADC(); 
void waitForDataClock();
inline int digitalReadDirect(int pin);
 
void setup() {
  
  startClockPWM();
  startSH_PWM();
  setUpADC();
  
  //Get next unused timer on the Due as the data timer
  dataTimer.attachInterrupt(dataInterrupt);
  dataTimer.setFrequency(CLOCK_FREQUENCY / CLOCKS_PER_SH_PULSE);
  
  pinMode(ICG, OUTPUT);
  pinMode(SH_TRIGGER, INPUT);
  
  //ICG is active low
  digitalWrite(ICG, HIGH);
  
  Serial.begin(115200);
}
 
void loop() 
{
  while(1)
  {
    delay(1000 / SAMPLE_RATE_HZ);
    
    startSH_PWM();
    
    //Sync the data timer up with the PWM generator
    //Ugly and hacky, but it works
    while(!digitalReadDirect(SH_TRIGGER));
    dataTimer.start();

    sh_gate_rise = 0;
    //Start integration
    waitForDataClock();
    REG_PIOC_ODSR = ICG_LOW;
    waitForDataClock();
    waitForDataClock();
    REG_PIOC_ODSR = ICG_HIGH;
    
    current_pixel = 0;
    while(current_pixel < JUNK_ELEMENTS_PRE)
    {
      current_pixel++;
      waitForDataClock();
    }
    
    current_pixel = 0;
    while(current_pixel < SIGNAL_ELEMENTS)
    {
      data[current_pixel] = ADC->ADC_CDR[7];
      current_pixel++;
      waitForDataClock();
    }
    
    current_pixel = 0;
    while(current_pixel < JUNK_ELEMENTS_POST)
    {
      current_pixel++;
      waitForDataClock();  
    }
    
    REG_PIOC_ODSR = ICG_LOW;
    waitForDataClock();
    waitForDataClock();    
    REG_PIOC_ODSR = ICG_HIGH;
    waitForDataClock();
    stopSH_PWM();
    dataTimer.stop();
    //----------------
    // Output to UART
    //----------------
    
    for(int i = 0; i < SIGNAL_ELEMENTS; i+= RESOLUTION_DIVIDER)
    {
      Serial.print(data[i]);
      Serial.print(", ");
    }
    Serial.println();

  } //end while(1)
}   //end loop()

void dataInterrupt()
{
  sh_gate_rise++;
}

void waitForDataClock()
{
  while(!sh_gate_rise); //Wait for next rising edge
  sh_gate_rise = 0;
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
 
}

void startSH_PWM()
{
  pmc_enable_periph_clk(PWM_INTERFACE_ID);
  PWMC_ConfigureClocks(CLOCK_FREQUENCY * CLOCK_MAX_DUTY, 0, VARIANT_MCK);
  
  PIO_Configure(
    g_APinDescription[SH].pPort,
    g_APinDescription[SH].ulPinType,
    g_APinDescription[SH].ulPin,
    g_APinDescription[SH].ulPinConfiguration);
 
  uint32_t channel = g_APinDescription[SH].ulPWMChannel;
  
  //Enable this channel and set parameters
  PWMC_ConfigureChannel(PWM_INTERFACE, channel , PWM_CMR_CPRE_CLKA, 0, 0);
  PWMC_SetPeriod(PWM_INTERFACE, channel, CLOCK_MAX_DUTY * 2 * CLOCKS_PER_SH_PULSE); 
  PWMC_EnableChannel(PWM_INTERFACE, channel);
  PWMC_SetDutyCycle(PWM_INTERFACE, channel, 2 * CLOCKS_PER_SH_PULSE);
}

void stopSH_PWM()
{
  uint32_t channel = g_APinDescription[SH].ulPWMChannel;
  PWMC_SetDutyCycle(PWM_INTERFACE, channel, 0);
}

void setUpADC()
{
  ADC->ADC_MR |= 0x80;  //set free running mode on ADC
  ADC->ADC_CHER = 0x80; //enable ADC on pin A0
}

inline int digitalReadDirect(int pin){
 return !!(g_APinDescription[pin].pPort -> PIO_PDSR & g_APinDescription[pin].ulPin);
};
