#include "JointControlFramework.h"

  //JointInterface * drill;
  //OutputDevice * controller;

void setup() {
  // put your setup code here, to run once:
  //controller = new DRV8871(PB_3, PB_2, false);
  //drill = new SingleMotorJoint(spd, controller);
  
  pinMode(PB_3, OUTPUT);//pin one of drill H bridge
  pinMode(PB_2, OUTPUT);//pin two of drill H bridge
}

void loop() {
  // put your main code here, to run repeatedly: 
  //this program turns the drill motor on and off
  //drill -> runOutputControl(100);
 drillForward();
  delay(10000);
 // drill -> runOutputControl(0);
  drillCoast();
   delay(1000);
 // drill -> runOutputControl(-100);
   drillReverse();
  delay(10000);
  //drill -> runOutputControl(0);
  drillCoast();
  delay(1000);
}

void drillForward()
{
   digitalWrite(PB_3, HIGH);
   digitalWrite(PB_2, LOW);
}

void drillReverse()
{
    digitalWrite(PB_3, LOW);
    digitalWrite(PB_2, HIGH);
}

void drillCoast()
{
  digitalWrite(PB_3, LOW);
  digitalWrite(PB_2, LOW);
}

