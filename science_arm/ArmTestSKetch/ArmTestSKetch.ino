#include "JointControlFramework.h"

  JointInterface * mainArm;
  OutputDevice * controller;
  FeedbackDevice* encoder;

void setup() {
  // put your setup code here, to run once:
 // controller = new DRV8842(PD_1, PD_0, PN_2, PL_2, PN_3, PL_3, PL_4, PH_3, PG_0, PH_2, PF_3);
  //mainArm = new SingleMotorJoint(spd, controller);
  //encoder = new Ma3Encoder10b(PD_2);
  Serial.begin(9600);

  pinMode(PF_0, OUTPUT);

  /*****************************
   * initialize the main motor
   ****************************/
   pinMode(PD_1, OUTPUT);//IN1
   pinMode(PD_0, OUTPUT);//IN2
   pinMode(PN_2, OUTPUT);//decay
   pinMode(PL_2, INPUT); //THE ONLY INPUT//nFault
   pinMode(PN_3, OUTPUT);//nSLeep
   pinMode(PL_3, OUTPUT);//nReset
   pinMode(PL_4, OUTPUT);//I0
   pinMode(PH_3, OUTPUT);//I1
   pinMode(PG_0, OUTPUT);//I2
   pinMode(PH_2, OUTPUT);//I3
   pinMode(PF_3, OUTPUT);//I4
   ///
  digitalWrite(PF_3, HIGH);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, HIGH);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0
  digitalWrite(PN_2, HIGH);//Decay
  digitalWrite(PL_3, HIGH);//disable Reset Mode

  
}

void loop() {
  // put your main code here, to run repeatedly: 
  //this sketch turns on and off the main motor
  //also attempt to read the encoder
 // mainArm -> runOutputControl(100);
  //Serial.println(encoder -> getFeedback());
  motorOn();
  
  /*digitalWrite(PD_0, LOW);//I1
  digitalWrite(PD_1, LOW);//IN2
  digitalWrite(PF_0, LOW);//LED
  digitalWrite(PN_3, LOW);//nSleep
  */
  delay(5000);
  
  motorOff();
  /*digitalWrite(PN_3, HIGH);//nSleep
  digitalWrite(PD_0, HIGH);//IN1
  digitalWrite(PD_1, HIGH);//IN2
  digitalWrite(PF_0, HIGH);//LED*/
  
  delay(5000);

  motorReverse();
  delay(5000);

  motorBrake();
  delay(2000);
 // mainArm -> runOutputControl(0);
 // Serial.println(encoder -> getFeedback());
 // delay(1000);
  //mainArm -> runOutputControl(-100);
  //delay(10000);
  //mainArm -> runOutputControl(0);
 // delay(1000); 
}

void motorOn()
{
  digitalWrite(PN_3, HIGH);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor current speed
  digitalWrite(PF_3, HIGH);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, HIGH);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //one high, one low. swap for other direction
  digitalWrite(PD_1, HIGH);//IN1
  digitalWrite(PD_0, LOW);//IN2
  digitalWrite(PF_0, HIGH);//LED

  
}

void motorReverse()
{
  digitalWrite(PN_3, HIGH);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor current speed
  digitalWrite(PF_3, HIGH);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, HIGH);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //one high, one low. swap for other direction
  digitalWrite(PD_1, LOW);//IN1
  digitalWrite(PD_0, HIGH);//IN2
  digitalWrite(PF_0, HIGH);//LED
}


void motorOff()
{
  digitalWrite(PN_3, LOW);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor curent speed
  digitalWrite(PF_3, LOW);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, LOW);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //brake = both high
  //coast = both low
  digitalWrite(PD_1, LOW); //IN1   
  digitalWrite(PD_0, LOW);//IN2
  digitalWrite(PF_0, LOW);//LED
  
}

void motorBrake()
{
  digitalWrite(PN_3, LOW);//nSLeep
  digitalWrite(PN_2, LOW);//Decay
  //0x0B = 01011 = 50% for testing purposes, I4 is MSB, I0 is LSB
  //the I-Bus is used to control motor curent speed
  digitalWrite(PF_3, LOW);//I4
  digitalWrite(PH_2, HIGH);//I3
  digitalWrite(PG_0, LOW);//I2
  digitalWrite(PH_3, HIGH);//I1
  digitalWrite(PL_4, HIGH);//I0

  //brake = both high
  //coast = both low
  digitalWrite(PD_1, HIGH); //IN1   
  digitalWrite(PD_0, HIGH);//IN2
  digitalWrite(PF_0, LOW);//LED
}

