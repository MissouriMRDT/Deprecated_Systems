#include "EasyTransfer.h"

EasyTransfer ET;

struct RECEIVE_DATA_STRUCTURE
{
  unsigned char motor_speed;
};

RECEIVE_DATA_STRUCTURE mydata;

void setup()
{
  Serial.begin(115200);
  TCCR2A = 0b10000001;
  TCCR2B = 0b00000001;
  OCR2A = 128;
  DDRB = 0b00101000;// set PWM pin as output
  PORTB = 0x0;
  
  ET.begin(details(mydata), &Serial);
}

void loop()
{
  if(ET.receiveData())
  {
    OCR2A = mydata.motor_speed;
  }
}
