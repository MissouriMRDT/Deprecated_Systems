#include <Servo.h>
#include <EasyTransfer.h>

EasyTransfer ET;

Servo gripper;

int pos = 0;
struct TELEDATA
{
  uint8_t openGrip;
  uint8_t closeGrip;
};
TELEDATA driveData;

void setup()
{
  pinMode(10,OUTPUT);
  gripper.attach(10);
  Serial.begin(9600);
  ET.begin(details(driveData), &Serial);
  driveData.openGrip = 0;
  driveData.closeGrip = 0;
}

void loop()
{
  if(ET.receiveData())
  {
    if(driveData.openGrip)
    {
      pos = 180;
      gripper.write(pos);
      delay(10);
    }
    else if(driveData.closeGrip)
    {
      pos = 0;
      gripper.write(pos);
      delay(10);
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
    
