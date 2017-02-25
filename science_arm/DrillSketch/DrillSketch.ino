#include "JointControlFramework.h"

  JointInterface * drill;
  OutputDevice * controller;

void setup() {
  // put your setup code here, to run once:
  controller = new DRV8871(PB_3, PB_2, false);
  drill = new SingleMotorJoint(spd, controller);
}

void loop() {
  // put your main code here, to run repeatedly: 
  //this program turns the drill motor on and off
  drill -> runOutputControl(100);
  delay(10000);
  drill -> runOutputControl(0);
  delay(1000);
  drill -> runOutputControl(-100);
  delay(10000);
  drill -> runOutputControl(0);
  delay(1000);
}
