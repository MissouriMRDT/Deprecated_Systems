/*
  Programmer: Owen Chiaventone
  
  Science Bay Door Controller
  
  Opens and Closes the science bay door with a servo
  
*/
#include <Servo.h>
#include <EasyTransfer.h>

struct control_struct
{
  //1 for on, 0 for off
  uint8_t lb395; 
  
  //1 for on, 0 for off
  uint8_t lb440;
  
  //position. 255 for open, 0 for close
  uint8_t doorserv;
};

const int OPEN = 180; 
const int CLOSED = 0;
const int SERVO_PIN = 11;
const int LB395_PIN = 9;
const int LB440_PIN = 10;
Servo doorServo;
char inchar;

control_struct control_data;
EasyTransfer controls;

void setup()
{
  doorServo.attach(SERVO_PIN);
  control_data.doorserv = CLOSED;
  pinMode(LB395_PIN, OUTPUT);
  pinMode(LB440_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  controls.begin(details(control_data), &Serial);
  Serial.begin(115200);
}

void loop()
{
  controls.receiveData();
  digitalWrite(LB395_PIN, control_data.lb395);
  digitalWrite(LB440_PIN, control_data.lb440);
  doorServo.write(control_data.doorserv);
}
