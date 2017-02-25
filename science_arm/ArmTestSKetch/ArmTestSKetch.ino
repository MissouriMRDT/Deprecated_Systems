#include "JointControlFramework.h"

  JointInterface * mainArm;
  OutputDevice * controller;
  FeedbackDevice* encoder;

void setup() {
  // put your setup code here, to run once:
  controller = new DRV8842(PD_1, PD_0, PN_2, PL_2, PN_3, PL_3, PL_4, PH_3, PG_0, PH_2, PF_3);
  mainArm = new SingleMotorJoint(spd, controller);
  encoder = new Ma3Encoder10b(PD_2);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  //this sketch turns on and off the main motor
  //also attempt to read the encoder
  mainArm -> runOutputControl(100);
  Serial.println(encoder -> getFeedback());
  delay(10000);
  mainArm -> runOutputControl(0);
  Serial.println(encoder -> getFeedback());
  delay(1000);
  mainArm -> runOutputControl(-100);
  delay(10000);
  mainArm -> runOutputControl(0);
  delay(1000); 
}
