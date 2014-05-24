/*
  Missouri University of Science and Technology
  MRDT 2014
  Programmer: Owen Chiaventone
  
  Camera Controller
  
  Controls the rover camera
  
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

const int PITCH = 6; //Blue
const int YAW = 9;   //Green
const int ROLL = 10; //Red
const int MODE = 11; //White
Servo pitch;
Servo yaw;
Servo roll;
Servo mode;


control_struct control_data;
EasyTransfer controls;

void setup()
{
  pitch.attach(PITCH);
  yaw.attach(YAW);
  roll.attach(ROLL);
  mode.attach(MODE);
  pinMode(PITCH, OUTPUT);
  pinMode(YAW, OUTPUT);
  pinMode(ROLL, OUTPUT);
  pinMode(MODE, OUTPUT);
  controls.begin(details(control_data), &Serial);
  Serial.begin(115200);
}

void loop()
{
  controls.receiveData();
  pitch.write(controls.pitch);
  yaw.write(controls.yaw);
  roll.write(controls.roll);
  mode.write(controls.mode);
}
