////////////////////////// Missouri Science and Technology Mars Rover Design Team 2015
// Judah Schad jrs6w7@mst.edu
//
// Software Sketch of a Rover Device to read Raman Spectrometer Camera using Toshiba TCD1304DG
//////////////////////////



////////////////////////// The TCD1304DG is a high sensitive and low dark current pn Photodiode CCD
// Sample and Hold: 22 PinCERDIP
//
// PINS: 3.0 V Min / 4.0 V Typical / 5.5 V Max 
// tINT (INTEGRATION TIME) = 10ms
// LOAD RESISTANCE = 100k
// DataRate : 500 Khz Typical
// Pixel Number : 3648 pixels
// Pixel Size : 8 µm ×200 µm
//
// Clocked Data Synch Control Scheme:
//
// Clock_In
// Shift_Gate
// Integration_Clear_Gate
//////////////////////////

////////////////////////// The Toshiba Procces Loop
// 1) Reset the Clear Gate and Shift Gate
// 2) Shift the sum value of each diode pixel into the CCD Register on 3648 light sensing diode array
// 3) Read this value of each pixel into a buffer of header_cnt + 3648 pixel_cnt + footer_cnt, as a time series of clocked analog voltages
//////////////////////////

////////////////////////// TODO Testing and Debug:
// OUTPUT_PIN_1 MasterClock_ToshibaCCD_Pin          WriteTone Drive the Camera Master Clock at the MASTER_CLOCK_FREQ: 0.8 Mhz Min /2 Mhz Typical /4 Mhz Max 
// OUTPUT_PIN_2 DataShiftRate_ToshibaCCD_Pin        SynchTone Shift Pixel one at a time through the diode array at 1/4 MASTER_CLOCK_FREQ edge aligned 
// OUTPUT_PIN_3 DataClockRate_ToshibaCCD_Pin        SynchTone Drive the Camera Data Transfer Clockt at 1/4 MASTER_CLOCK_FREQ edge aligned 
//
// INPUT_PIN_1  ReadCCD_DataPin                     AnalogRead each Pixel into a ccd_packet_data_buffer
//////////////////////////

////////////////////////// Todo: John Maruska : crituqe, review,rewrite, contrast, refactor, edit proccess Flow: 
//Page2 http://www.eureca.de/datasheets/01.xx.xxxx/01.04.xxxx/01.04.0060/TCD1304DG.pdf
// Reset : the Clear Gate and Shift Gate
// Shift the diode sum value of each pixel into the Register as a single step on 3648 light sensing diode array
// Read this value of each pixel, and read it as an analog voltage and get the dat stream at a SensorDataRate that is somewhere around 1/4 the SensorClockRate
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////// ////////////////////////// ////////////////////////// 
// TODO Pin Map: OPTIONAL Electronic Shutter
//
// Todo Cross Org RoveSci_CHALLENGE: RoveBoard::Wrappers in Cplus Energia
//
// Todo Cross Org RoveSci_CHALLENGE_DBL_BONUS::CCS Rtos Cfg in RoveWareRealTimeia
////////////////////////// ////////////////////////// ////////////////////////// 

// CCD Data Protocol
const int CCD_HEADER_END_INDEX              = 32;
const int CCD_PIXEL_END_INDEX               = 3648 + CCD_HEADER_END_INDEX;
const int CCD_FOOTER_END_INDEX              = 14 + CCD_PIXEL_END_INDEX;

/////////////////////////////////////////////////////////////////////////////Begin Sketch

// Used as a Quick and Dirty Software Clock 
// Output Pins sit and wait on a rising edge of our own device pin driving the MasterClock 
// (i.e : tone.h is a valid, non blocking, timer interrupt based service that goes up to 8 Mhz):
// At the lowest setting, a 1 MHZ CCD Master Clock gives us 480 Clock Cycles between Data on a Tiva at 120 Mhz and a DataRate of 250 Khz

// TODO: How long for DigitalWrite. How long for DigitalRead. How long for AnalogRead?

const int CCD_MASTER_CLOCK_FREQ = 1000000;  // TODO: Naming convention. 

//TODO -> Hardware Library Hack for Calibration Timing/Tuning Variable
// const int TUNING_VAR = 1;
// const int READ_PACKET_DURATION = (1/TOSHIBA_DATA_READ_CLOCK_TICKS) * (1/TOSHIBA_MASTER_CLOCK_FREQ) * (CCD_PACKET_DATA_FRAME_CNT) + TUNING_VAR;

// Rove Data Handling
int ccd_packet_data_buffer[CCD_FOOTER_END_INDEX];

//////// RoveSci_CCD Public Api
void RoveSci_CCDReadPacket(

  int clock_pin
  , int shift_data_pin
  , int integrate_data_pin  // TODO: Figure out exact ICG stuff for better name
  , int read_data_pin
//  , int read_byte_ticks
  , int* ccd_picture_data 
  , int read_bytes_count);

//////// RoveSci_CCD Private Method
void RoveSci_CCD_SynchNextClockTick();

/////////////////////////////////////////////////////////////////////////////Setup
void setup()
{
  //This tone.h PIN synchs the Hardware Sensor Master Clock AND our own Software Data Clock by digitalReadSelf(SYNCH_DATA_TRANSFER_PIN);
  ToshibaMasterClock.begin(MasterClock_ToshibaCCD_Pin);

}//end setup

///////////////////////////////////////////////////////////////////////////Loop
void loop()
{
  ToshibaMasterClock.play(TOSHIBA_MASTER_CLOCK_FREQ, READ_PACKET_DURATION);
  
  RoveSci_CCDReadPacket(
  
    MasterClock_ToshibaCCD_Pin
    , DataShiftRate_ToshibaCCD_Pin
    , DataClockRate_ToshibaCCD_Pin
    , ReadCCD_DataPin
    
    , TOSHIBA_DATA_READ_CLOCK_TICKS
    , CCD_FOOTER_END_INDEX
    
    , &ccd_packet_data_buffer );
       
  delay_uS(2);
  
  SerialPrintLn(ccd_packet_data_buffer); 
  delay_uS(2);
  
}//end loop
///////////////////////////////////////////////////////////////////////////End Sketch

//Spins on a pin waiting and returns at a rising edge
void RoveSci_CCD_SynchNextClockTick(synch_to_clock_pin)
{
  bool clock_synched = false;
  
  while(!clock_synched)
  {   
    synch_data_read = digitalRead(synch_to_clock_pin)
    
  }//end while
}//end_function



// The trick is to wait for a rising edge while blocking on OUR OWN OUTPUT PIN to go high before writing the shift rate and transfer rate
void RoveSci_CCDReadPacket( 

  //function args
  int clock_pin
  , int shift_data_pin
  , int transfer_data_pin
  , int read_data_pin
  , int read_byte_ticks
  , int read_bytes_cnt
  , int* ccd_picture_data 
){
  
  int data_read_cnt = 0; 
  while(ccd_picture_data[data_read_cnt] != read_bytes_cnt )
  {  
    //wait for the next rising edge of master clock
    RoveSci_CCD_SynchNextClockTick(clock_pin);
    
    //begin pulse the shift and transfer
    digitalWrite(shift_data_pin, HIGH);
    digitalWrite(transfer_data_pin, HIGH);
  
    //read after two ticks (in the middle for the next four ticks) 
    RoveSci_CCD_SynchNextClockTick(clock_pin);
    RoveSci_CCD_SynchNextClockTick(clock_pin);
    
    //read one pixel
    ccd_picture_data[data_read_crit] = analogRead(read_data_pin);   
    RoveSci_CCD_SynchNextClockTick(clock_pin);
    RoveSci_CCD_SynchNextClockTick(clock_pin);
 
    //end pulse the shift and transfer
    digitalWrite(shift_data_pin, LOW);
    digitalWrite(transfer_data_pin, LOW);
    
    //wait low for the next three ticks of the master clock  
    RoveSci_CCD_SynchNextClockTick(clock_pin);
    RoveSci_CCD_SynchNextClockTick(clock_pin);
    RoveSci_CCD_SynchNextClockTick(clock_pin);
    //RoveSci_CCD_SynchNextClockTick(clock_pin);
    
  }//end while
  
  //TODO? RoveSci_CCDParsePacket(&ccd_packet_data_buffer);
   
}//end function
