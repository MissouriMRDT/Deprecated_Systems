
////////////////////////// Missouri University of Science and Technology Mars Rover Design Team 2016
// John Maruska jwmbq6@mst.edu
// Judah Schad jrs6w7@mst.edu
//
// Software Sketch of a Rover Device to read Raman Spectrometer Camera using Toshiba TCD1304DG CCD Linear Image Sensor
//////////////////////////

#include "EasyTransfer.h"

#include "wiring_private.h"  // fast analog read libraries
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#define ICG_PIN_REG      GPIO_PORTB_BASE + (GPIO_O_DATA + (8 << 2))
#define SH_PIN_REG       GPIO_PORTC_BASE + (GPIO_O_DATA + (16 << 2))
#define MASTER_PIN_REG   GPIO_PORTB_BASE + (GPIO_O_DATA + (16 << 2))

#define PIXEL_BASE       1073942528
#define PIXEL_AB         255
#define ICG_BASE         1073950720
#define ICG_AB           65280

const int pinA = 27;
const int32_t portBaseA = 0;
const uint8_t bitA = 2;
const uint8_t portA = 5;
const uint32_t channelA = 2;
volatile uint16_t value[1];

////////////////////////// The TCD1304DG is a high sensitive and low dark current pn Photodiode CCD
// Sample and Hold: 22 PinCERDIP
//
// PINS: 3.0 V Min / 4.0 V Typical / 5.5 V Max 
// tINT (INTEGRATION TIME) = 10µs
// LOAD RESISTANCE = 100k
// DataRate : 500 Khz Typical
// Pixel Number : 3648 pixels
// Pixel Size : 8 µm ×200 µm
//
// Clocked Data Sync Control Scheme:
//
// Clock_In
// Shift_Gate
// Integration_Clear_Gate
//////////////////////////

////////////////////////// The Toshiba Process Loop
// 1) Reset the Clear Gate and Shift Gate
// 2) Shift the sum value of each diode pixel into the CCD Register on 3648 light sensing diode array
// 3) Read this value of each pixel into a buffer of header_cnt + 3648 pixel_cnt + footer_cnt, as a time series of clocked analog voltages
//////////////////////////

const int MASTER_CLOCK_CCD_PIN = 7;    // WriteTone Drive the Camera Master Clock at the MASTER_CLOCK_FREQ: 0.8 Mhz Min /2 Mhz Typical /4 Mhz Max
const int SHIFT_DATA_CCD_PIN = 37;     // SyncTone Shift Pixel one at a time through the diode array at 1/4 MASTER_CLOCK_FREQ edge aligned 
const int INTEGRATE_DATA_CCD_PIN = 38; // SyncTone Drive the Camera Data Transfer Clockt at 1/4 MASTER_CLOCK_FREQ edge aligned
const int READ_DATA_CCD_PIN = 28;      // AnalogRead each Pixel into a ccd_packet_data_buffer

const int ICG_DUMMY_PIN = 40;
const int PIXEL_DUMMY_PIN = 39;

////////////////////////// Todo: Test, consolidate code, write a timer based version
// TODO: Current issues: 1) Every other element printing 0. Could be word-size,  more likely timing issue.
//                       3) Logic analyzer shows no cleanup signaling after packet.
//                       4) Have to switch off analogRead. Too slow. 
// Datasheet: http://www.eureca.de/datasheets/01.xx.xxxx/01.04.xxxx/01.04.0060/TCD1304DG.pdf
// Reset : the Clear Gate and Shift Gate
// Shift the diode sum value of each pixel into the Register as a single step on 3648 light sensing diode array
// Read this value of each pixel, and read it as an analog voltage and get the dat stream at a SensorDataRate that is somewhere around 1/4 the SensorClockRate
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////// ////////////////////////// ////////////////////////// 
// Pin Map: OPTIONAL Electronic Shutter
//
//  MASTER_CLOCK_CCD_PIN    :  PB_4
//  SHIFT_DATA_CCD_PIN      :  PC_4
//  INTEGRATE_DATA_CCD_PIN  :  PB_3
//  READ_DATA_CCD_PIN       :  PE_2
//
// TODO: Cross Org RoveSci_CHALLENGE: RoveBoard::Wrappers in Cplus Energia
//
// TODO: Cross Org RoveSci_CHALLENGE_DBL_BONUS::CCS Rtos Cfg in RoveWareRealTimeia
////////////////////////// ////////////////////////// ////////////////////////// 

// CCD Data Protocol
const int TOTAL_ELEMENTS           = 3648;
const int CCD_HEADER_END_INDEX     = 32;
const int CCD_PIXEL_END_INDEX      = TOTAL_ELEMENTS + CCD_HEADER_END_INDEX;
const int CCD_FOOTER_END_INDEX     = 14 + CCD_PIXEL_END_INDEX;      

const int CCD_TOTAL_MASTER_TICKS   = 2 * (CCD_FOOTER_END_INDEX * 4);

// Used as a Quick and Dirty Software Clock 
// Output Pins sit and wait on a rising edge of our own device pin driving the MasterClock 
// At the lowest setting, a 1 MHZ CCD Master Clock gives us 480 Clock Cycles between Data on a Tiva at 80Mhz and a DataRate of 250 Khz

const int CCD_MASTER_CLOCK_FREQ = 1000000; // 1MHz

// Rove Data Handling
int ccd_packet_data_buffer[CCD_FOOTER_END_INDEX]; 
int ccd_send_data_buffer[TOTAL_ELEMENTS];

volatile int master_clock_tick_count = 0;
volatile int shutter_tick_count = 0;
volatile bool master_toggle = true;
volatile bool icg_toggle = false;
volatile bool sh_toggle = true;
volatile bool image_read_complete = false;
volatile bool icg_complete = false;

//////// RoveSci_CCD Public Api
void RoveSci_CCD_ReadPacket
(
const int clock_pin
, const int shift_data_pin
, const int integrate_data_pin  // TODO: Figure out exact ICG stuff for better name
, const int read_data_pin
, int ccd_raw_data[]
);

void RoveSci_CCD_PrintPacket(int ccd_raw_data[]);

//////// RoveSci_CCD Private Method
uint16_t fastCCDPixelRead();

/////////////////////////////////////////////////////////////////////////////Setup
void setup()
{
  delay(2000);
  pinMode(MASTER_CLOCK_CCD_PIN, OUTPUT);  
  pinMode(SHIFT_DATA_CCD_PIN, OUTPUT);     
  pinMode(INTEGRATE_DATA_CCD_PIN, OUTPUT);
  pinMode(READ_DATA_CCD_PIN, INPUT);    
  
  attachInterrupt(ICG_DUMMY_PIN, RoveSci_CCD_ICGToggle, RISING); 
  attachInterrupt(PIXEL_DUMMY_PIN, RoveSci_CCD_PixelRead, RISING);
  
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  if(channelA != ADC_CTL_TS)
    ROM_GPIOPinTypeADC((uint32_t) portBASERegister(portA), digitalPinToBitMask(pinA));
  ROM_ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
  ROM_ADCSequenceStepConfigure(ADC0_BASE, 3, 0, channelA | ADC_CTL_IE | ADC_CTL_END);
  ROM_ADCSequenceEnable(ADC0_BASE, 3);

  Serial.begin(115200);
}

///////////////////////////////////////////////////////////////////////////Loop
void loop()
{  
  RoveSci_CCD_ReadPacket
    (
  MASTER_CLOCK_CCD_PIN
    , SHIFT_DATA_CCD_PIN
    , INTEGRATE_DATA_CCD_PIN
    , READ_DATA_CCD_PIN
    , ccd_packet_data_buffer 
    ); // end function call
}
///////////////////////////////////////////////////////////////////////////End Sketch

void RoveSci_CCD_SendPacket(int ccd_raw_data [])
{
  for(int i = 0; i < 3648; i++)
  {
     ccd_send_data_buffer[i] = ccd_raw_data[i+32];
  } 
  
  return;
}

// The trick is to wait for a rising edge while blocking on OUR OWN OUTPUT PIN to go high 
// before writing the shift rate and transfer rate
void RoveSci_CCD_ReadPacket( 
//function args
const int clock_pin
, const int shift_data_pin
, const int integrate_data_pin
, const int read_data_pin
, int ccd_raw_data [] 
){
  
  image_read_complete = false;
  shutter_tick_count = 0;
  master_clock_tick_count = 0;

  PWMWrite(ICG_DUMMY_PIN, 255, (255 / 2), CCD_MASTER_CLOCK_FREQ); 
  PWMWrite(PIXEL_DUMMY_PIN, 255, (255 / 2), CCD_MASTER_CLOCK_FREQ); 
  ROM_TimerDisable(PIXEL_BASE, PIXEL_AB);
  ROM_TimerDisable(ICG_BASE, ICG_AB);
  
  ROM_TimerEnable(ICG_BASE, ICG_AB);
  while(!icg_complete);
  ROM_TimerDisable(ICG_BASE, ICG_AB);
  icg_complete = false;
  
  master_clock_tick_count = 0;
  ROM_TimerEnable(PIXEL_BASE, PIXEL_AB);
  while(!image_read_complete);
  ROM_TimerDisable(PIXEL_BASE, PIXEL_AB);
  
  master_clock_tick_count = 0;
  ROM_TimerEnable(ICG_BASE, ICG_AB);
  while(!icg_complete);
  ROM_TimerDisable(ICG_BASE, ICG_AB);

  RoveSci_CCD_SendPacket(ccd_raw_data);
}

void RoveSci_CCD_PixelRead()
{
  master_clock_tick_count++;
  if(!(master_clock_tick_count % 8)){
    HWREG(MASTER_PIN_REG) = master_toggle;
    HWREG(SH_PIN_REG) = sh_toggle; 
    ccd_packet_data_buffer[shutter_tick_count] = fastCCDPixelRead();
 
    shutter_tick_count++;
  }
  else {
    HWREG(MASTER_PIN_REG) = master_toggle;
    master_toggle = !master_toggle; 
  }
  
  if(master_clock_tick_count == CCD_TOTAL_MASTER_TICKS)
  {
    image_read_complete = true;
  }
}

void RoveSci_CCD_ICGToggle() {
  master_clock_tick_count++;
  if(!(master_clock_tick_count % 8)){
    HWREG(MASTER_PIN_REG) = master_toggle;
    HWREG(SH_PIN_REG) = sh_toggle; 
    
    ccd_packet_data_buffer[shutter_tick_count] = fastCCDPixelRead();
    
    master_toggle = !master_toggle;
    sh_toggle = !sh_toggle;
    shutter_tick_count++;
  }
  else {
    HWREG(MASTER_PIN_REG) = master_toggle; 
    master_toggle = !master_toggle; 
  }
  
  if(master_clock_tick_count == 4) { 
    HWREG(ICG_PIN_REG) = icg_toggle;
    icg_toggle = !icg_toggle;
  }
  if(master_clock_tick_count == 22) {
    HWREG(ICG_PIN_REG) = icg_toggle;
    icg_toggle = !icg_toggle;
    icg_complete = true;
  }
}

static inline uint16_t fastCCDPixelRead()
{
  ROM_ADCIntClear(ADC0_BASE, 3);
  ROM_ADCProcessorTrigger(ADC0_BASE, 3);
  while(!ROM_ADCIntStatus(ADC0_BASE, 3, false)) {
  }
  ROM_ADCIntClear(ADC0_BASE, 3);
  ROM_ADCSequenceDataGet(ADC0_BASE, 3, (unsigned long*) value);

  return value[0];  
}


