#ifndef Struct_Xfer_h
#define Struct_Xfer_h

//make it a little prettier on the front end. 
#define details(name) (byte*)&name,sizeof(name)

//Not neccessary, but just in case. 
#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "HardwareSerial.h"
//#include <NewSoftSerial.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

class Struct_Xfer {
public:
  void begin(uint8_t *, uint8_t, HardwareSerial *theSerial);
  //void begin(uint8_t *, uint8_t, NewSoftSerial *theSerial);
  void sendData();
  boolean receiveData();
private:
  HardwareSerial *_serial;
  //NewSoftSerial *_serial;
  uint8_t * address;  //address of struct
  uint8_t size;       //size of struct
  uint8_t * rx_buffer; //address for temporary storage and parsing buffer
  uint8_t rx_array_inx;  //index for RX parsing buffer
  uint8_t rx_len;		//RX packet length according to the packet
  uint8_t calc_CS;	   //calculated Chacksum
};



#endif

