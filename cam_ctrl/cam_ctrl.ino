/*
  Missouri University of Science and Technology
  MRDT 2014
  Programmer: Owen Chiaventone
  
  Camera Controller
  
  Controls the rover camera
  
*/
#include <Servo.h>
#include "EasyTransfer.h"

struct control_struct
{
  uint8_t struct_id;
  uint8_t pan;
  uint8_t tilt;
};

const int PAN = 6; //Blue
const int TILT = 9;   //Green
Servo pan;
Servo tilt;


control_struct control_data;
EasyTransfer controls;

void setup()
{
  Serial.begin(115200);  
  pan.attach(PAN);
  tilt.attach(TILT);
  
  pinMode(PAN, OUTPUT);
  pinMode(TILT, OUTPUT);

  control_data.pan = 90;
  control_data.tilt = 90;

  controls.begin(details(control_data), &Serial);
  
}

void loop()
{

  controls.receiveData();
  pan.write(control_data.pan);
  tilt.write(control_data.tilt);
  
}
