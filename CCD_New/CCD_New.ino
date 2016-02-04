
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

 int MASTER_CLOCK_CCD_PIN = 23;               // WriteTone Drive the Camera Master Clock at the MASTER_CLOCK_FREQ: 0.8 Mhz Min /2 Mhz Typical /4 Mhz Max
 int SHIFT_DATA_CCD_PIN = 24;                 // SyncTone Shift Pixel one at a time through the diode array at 1/4 MASTER_CLOCK_FREQ edge aligned 
 int INTEGRATE_DATA_CCD_PIN = 25;             // SyncTone Drive the Camera Data Transfer Clockt at 1/4 MASTER_CLOCK_FREQ edge aligned
 int READ_DATA_CCD_PIN = 26;                  // AnalogRead each Pixel into a ccd_packet_data_buffer
 
////////////////////////// Todo: John Maruska : critique, review,rewrite, contrast, refactor, edit proccess Flow: 
//Page2 http://www.eureca.de/datasheets/01.xx.xxxx/01.04.xxxx/01.04.0060/TCD1304DG.pdf
// Reset : the Clear Gate and Shift Gate
// Shift the diode sum value of each pixel into the Register as a single step on 3648 light sensing diode array
// Read this value of each pixel, and read it as an analog voltage and get the dat stream at a SensorDataRate that is somewhere around 1/4 the SensorClockRate
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////// ////////////////////////// ////////////////////////// 
// Pin Map: OPTIONAL Electronic Shutter
//
//  MASTER_CLOCK_CCD_PIN    :  PE_0
//  SHIFT_DATA_CCD_PIN      :  PE_1
//  INTEGRATE_DATA_CCD_PIN  :  PE_2
//  READ_DATA_CCD_PIN       :  PE_3
//
// TODO: Cross Org RoveSci_CHALLENGE: RoveBoard::Wrappers in Cplus Energia
//
// TODO: Cross Org RoveSci_CHALLENGE_DBL_BONUS::CCS Rtos Cfg in RoveWareRealTimeia
////////////////////////// ////////////////////////// ////////////////////////// 

// CCD Data Protocol
const int CCD_HEADER_END_INDEX     = 32;
const int CCD_PIXEL_END_INDEX      = 3648 + CCD_HEADER_END_INDEX;
const int CCD_FOOTER_END_INDEX     = 14 + CCD_PIXEL_END_INDEX;

/////////////////////////////////////////////////////////////////////////////Begin Sketch

// Used as a Quick and Dirty Software Clock 
// Output Pins sit and wait on a rising edge of our own device pin driving the MasterClock 
// (i.e : tone.h is a valid, non blocking, timer interrupt based service that goes up to 8 Mhz):
// At the lowest setting, a 1 MHZ CCD Master Clock gives us 480 Clock Cycles between Data on a Tiva at 120 Mhz and a DataRate of 250 Khz

// TODO: How long for DigitalWrite. How long for DigitalRead. How long for AnalogRead?

const int CCD_MASTER_CLOCK_FREQ = 1000000; 

//TODO -> Hardware Library Hack for Calibration Timing/Tuning Variable
// const int TUNING_VAR = 1;
// const int READ_PACKET_DURATION = (1/TOSHIBA_DATA_READ_CLOCK_TICKS) * (1/TOSHIBA_MASTER_CLOCK_FREQ) * (CCD_PACKET_DATA_FRAME_CNT) + TUNING_VAR;

// Rove Data Handling
int ccd_packet_data_buffer[CCD_FOOTER_END_INDEX];

//////// RoveSci_CCD Public Api
void RoveSci_CCD_ReadPacket
(
const int clock_pin
, const int shift_data_pin
, const int integrate_data_pin  // TODO: Figure out exact ICG stuff for better name
, const int read_data_pin
//  , int read_byte_ticks
, int ccd_picture_data[] // TODO: cannot convert 'int(*)[3694] to 'int*' 
);

//////// RoveSci_CCD Private Method
void RoveSci_CCD_SyncNextClockTick(int sync_to_clock_pin);

/////////////////////////////////////////////////////////////////////////////Setup
void setup()
{
  pinMode(MASTER_CLOCK_CCD_PIN, OUTPUT);  
  pinMode(SHIFT_DATA_CCD_PIN, OUTPUT);     
  pinMode(INTEGRATE_DATA_CCD_PIN, OUTPUT);
  pinMode(READ_DATA_CCD_PIN, INPUT);    
  //This tone.h PIN syncs the Hardware Sensor Master Clock AND our own Software Data Clock by digitalReadSelf(SYNC_DATA_TRANSFER_PIN);
  //ToshibaMasterClock.begin(MasterClock_ToshibaCCD_Pin);
  Serial.begin(9600);
}//end setup

///////////////////////////////////////////////////////////////////////////Loop
void loop()
{
  RoveSci_CCD_ReadPacket
    (
  MASTER_CLOCK_CCD_PIN
    , SHIFT_DATA_CCD_PIN
    , INTEGRATE_DATA_CCD_PIN
    , READ_DATA_CCD_PIN
    , ccd_packet_data_buffer // TODO: cannot convert 'int(*)[3694] to 'int*' 
    ); // end function call

  delayMicroseconds(2);

  // TODO: Serial.println(ccd_packet_data_buffer); 
  // data_buffer is an array of 3964 elements. Need to create a custom print function. 
  
  delayMicroseconds(2); // Why are we delaying on each side of the println? 

}//end loop
///////////////////////////////////////////////////////////////////////////End Sketch

//Spins on a pin waiting and returns at a rising edge
void RoveSci_CCD_SyncNextClockTick(int sync_to_clock_pin)
{
  bool clock_synced = false;

  while(!clock_synced)
  {   
    clock_synced = digitalRead(sync_to_clock_pin);
  }//end while
} //end_function

    // The trick is to wait for a rising edge while blocking on OUR OWN OUTPUT PIN to go high before writing the shift rate and transfer rate
void RoveSci_CCD_ReadPacket( 
  //ToshibaMasterClock.play(TOSHIBA_MASTER_CLOCK_FREQ, READ_PACKET_DURATION);

  //function args
  const int clock_pin
  , const int shift_data_pin
  , const int integrate_data_pin
  , const int read_data_pin
  , int ccd_picture_data [] // TODO: cannot convert 'int(*)[3694] to 'int*' 
  ){
  tone(clock_pin, CCD_MASTER_CLOCK_FREQ);

  int data_read_count = 0; 

  // This digitalWrite block is to manually replicate the timing chart on the datasheet. 
  //wait for the next rising edge of master clock
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(shift_data_pin, LOW);
  digitalWrite(integrate_data_pin, HIGH);

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(integrate_data_pin, LOW);

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(shift_data_pin, HIGH); 

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(shift_data_pin, LOW);

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(integrate_data_pin, HIGH);

  bool shift_toggle = HIGH;
  while(data_read_count != CCD_FOOTER_END_INDEX) 
  {
    digitalWrite(shift_data_pin, shift_toggle);

    RoveSci_CCD_SyncNextClockTick(clock_pin);
    RoveSci_CCD_SyncNextClockTick(clock_pin);
    ccd_picture_data[data_read_count] = analogRead(read_data_pin);
    RoveSci_CCD_SyncNextClockTick(clock_pin);
    RoveSci_CCD_SyncNextClockTick(clock_pin);

    shift_toggle = !shift_toggle;
    data_read_count++;
  } // end while

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(shift_data_pin, LOW);
  digitalWrite(integrate_data_pin, HIGH);

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(integrate_data_pin, LOW);

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(shift_data_pin, HIGH); 

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(shift_data_pin, LOW);

  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  RoveSci_CCD_SyncNextClockTick(clock_pin);
  digitalWrite(integrate_data_pin, HIGH);

  noTone(clock_pin);

  //TODO? RoveSci_CCDParsePacket(&ccd_packet_data_buffer);

}//end function

