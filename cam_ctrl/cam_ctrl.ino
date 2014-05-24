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
  uint8_t roll;
  uint8_t mode;
};
  uint8_t lb395; 
  
  //1 for on, 0 for off
  uint8_t lb440;
  
  //position. 255 for open, 0 for close
  uint8_t doorserv;
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
  pitch.write(control_data.pitch);
  yaw.write(control_data.yaw);
  roll.write(control_data.roll);
  mode.write(control_data.mode);

  /*Debug, please ignore
  pitch.write(0);
  yaw.write(0);
  roll.write(0);
  mode.write(0);
  delay(500);
  pitch.write(180);
  delay(500);
  yaw.write(180);
  delay(500);
  roll.write(180);
  delay(500);
  mode.write(180);
  delay(500);
  */
}
