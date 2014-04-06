/*
  Programmer: Owen Chiaventone
  
  Science Bay Door Controller
  
  Opens and Closes the science bay door with a servo
  
*/
#include <Servo.h>

const int OPEN = 180; 
const int CLOSED = 0;
const int SERVO_PIN = 9;
Servo doorServo;
char inchar;

void setup()
{
  doorServo.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop()
{
  //Open
  while(Serial.available())
  {
    inchar = Serial.read();
    if(inchar=='o')
    {
      Serial.println("Open");
      doorServo.write(OPEN);
    } else if(inchar == 'c')
    {
      Serial.println("Close");
      doorServo.write(CLOSED);
    }
  }
}
