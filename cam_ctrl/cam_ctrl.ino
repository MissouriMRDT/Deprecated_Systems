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
  uint8_t pitch;
  uint8_t yaw;
//  uint8_t roll;
//  uint8_t mode;
};

const int PITCH = 6; //Blue
const int YAW = 9;   //Green
const int ROLL = 10; //Red
const int MODE = 11; //White
Servo pitch;
Servo yaw;
//Servo roll;
//Servo mode;


control_struct control_data;
EasyTransfer controls;

void setup()
{
  Serial.begin(115200);  
  pitch.attach(PITCH);
  yaw.attach(YAW);
  //roll.attach(ROLL);
  //mode.attach(MODE);
  pinMode(PITCH, OUTPUT);
  pinMode(YAW, OUTPUT);
  //pinMode(ROLL, OUTPUT);
  //pinMode(MODE, OUTPUT);
  control_data.pitch = 90;
  control_data.yaw = 90;
  //control_data.roll = 90;
  //control_data.mode = 90;
  controls.begin(details(control_data), &Serial);
  
  //Wait for camera module to initialize
  //delay(10000);
}

void loop()
{

  controls.receiveData();
  pitch.write(control_data.pitch);
  yaw.write(control_data.yaw);
  //roll.write(control_data.roll);
  //mode.write(control_data.mode);

  
}
