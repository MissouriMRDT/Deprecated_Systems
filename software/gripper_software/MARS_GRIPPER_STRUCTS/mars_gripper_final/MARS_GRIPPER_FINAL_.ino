#include <Servo.h>
#include "EasyTransfer.h"

EasyTransfer ET;

Servo gripper;

int pos = 0;
struct TELEDATA
{
  uint8_t cmd;
};
TELEDATA driveData;

void setup()
{
  pinMode(10,OUTPUT);
  gripper.attach(10);
  Serial.begin(115200);
  ET.begin(details(driveData), &Serial);
}

void loop()
{
  if(ET.receiveData())
  {
    if(driveData.cmd == 0)
    {
      pos = 180;
      gripper.write(pos);
      delay(100);
    }
    else if(driveData.cmd == 1)
    {
      pos = 0;
      gripper.write(pos);
      delay(100);
    }
    else
    {
      pos = 136;
      gripper.write(pos);
      delay(10);
    }
  }
  else
  {
     pos = 136;
     gripper.write(pos);
     delay(10);
  }
}
    
