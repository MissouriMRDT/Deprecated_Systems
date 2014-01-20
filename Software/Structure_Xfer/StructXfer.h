#ifndef StructXfer_h
#define StructXfer_h

//make it a little prettier on the front end. 
#define details(name) (byte*)&name,sizeof(name)

#include "Arduino.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

class StructXfer {
public:
void begin(uint8_t *, uint8_t, HardwareSerial *theSerial);
void sendData();
boolean receiveData();
private:
HardwareSerial *_serial;
uint8_t * address;  //address of struct
uint8_t size;       //size of struct
uint8_t * rx_buffer; //address for temporary storage and parsing buffer
uint8_t rx_array_inx;  //index for RX parsing buffer
uint8_t rx_len;		//RX packet length according to the packet
uint8_t calc_CS;	   //calculated Chacksum
};

#endif
