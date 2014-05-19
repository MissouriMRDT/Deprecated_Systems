/*
  Programmer: Owen Chiaventone
  
  Science Bay Door Controller
  
  Opens and Closes the science bay door with a servo
  
*/
#include <Servo.h>
#include <EasyTransfer.h>

const unsigned char SERVO_BIT = 0b00000001;
const unsigned char LB395_BIT = 0b00000010;
const unsigned char LB440_BIT = 0b00000100;

struct control_struct
{
  unsigned char state; 
  // takes form 0b00000abc
  //Where A is status of 395nm lighting bank
  //B is status of 440nm lighting bank
  //C is status of servo
};

const int OPEN = 180; 
const int CLOSED = 0;
const int SERVO_PIN = 9;
const int LB395_PIN = 10;
const int LB440_PIN = 11;
Servo doorServo;
char inchar;

control_struct control_data;
EasyTransfer controls;

void setup()
{
  doorServo.attach(SERVO_PIN);
  controls.begin(details(control_data), &Serial);
  Serial.begin(9600);
}

void loop()
{
  //Open
  while(Serial.available())
  {
    if(controls.receiveData())
    {
      digitalWrite(LB395_PIN, (control_data.state & LB395_BIT));
      digitalWrite(LB440_PIN, (control_data.state & LB440_BIT));
    }
  }
  
  //Opens servo if least significant bit of state is 1
  //Closes door servo otherwise
  doorServo.write(180*(control_data.state & SERVO_BIT));
}
