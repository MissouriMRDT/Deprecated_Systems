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

const int pinA = 27;
int32_t portBaseA = 0;
uint8_t bitA = 2;
uint8_t portA = 5;
uint32_t channelA = 2;
uint16_t value[1];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  if(channelA != ADC_CTL_TS)
    ROM_GPIOPinTypeADC((uint32_t) portBASERegister(portA), digitalPinToBitMask(pinA));
  ROM_ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
  ROM_ADCSequenceStepConfigure(ADC0_BASE, 3, 0, channelA | ADC_CTL_IE | ADC_CTL_END);
  ROM_ADCSequenceEnable(ADC0_BASE, 3);
}

void loop()
{ 
  int hold = 0;
  int msdelay = micros();
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 1000; i++)
  {
    ROM_ADCIntClear(ADC0_BASE, 3);
    ROM_ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ROM_ADCIntStatus(ADC0_BASE, 3, false)) {
    }
    ROM_ADCIntClear(ADC0_BASE, 3);
    ROM_ADCSequenceDataGet(ADC0_BASE, 3, (unsigned long*) value);

    hold = value[0]; 
    
  }
  msdelay = micros() - msdelay;
  Serial.println(msdelay); 
}
