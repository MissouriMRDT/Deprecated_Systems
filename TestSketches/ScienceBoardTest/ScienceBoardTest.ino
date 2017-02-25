#include "JointControlFramework.h"
#include "Servo.h"

/* Programmers: Jimmy Haviland & Chris Dutcher
 * Date of creation: 1/22/2017
 * Sub system: science board
 * 
 * program overhead:
 * testing stuff
 * //need to add rove comm functionality and feedback for photodiode and error messages
 */




FeedbackDevice* feedbackDevice;//encoder
JointInterface * interFace;//abstract joint/motor
OutputDevice * controller;//the motor controller


  CommandResult result;
  uint16_t commandId;
  size_t commandSize;
  int16_t commandData;
  uint32_t watchdogTimer_us = 0; //increment this value everytime we don't get a command. When we've waited for a command for longer than our timeout value, stop all arm movement

  //declare integers for analog input, will be between 0 and 1023
  uint16_t analog1, analog2;
  
  //create servos
  Servo flap, carousel;

  

void setup() {

  flap.attach(PM_5);
  carousel.attach(PM_4);

  roveComm_Begin(192, 168, 1, 131);
  Serial.begin(9600);

  pinMode(PQ_3, OUTPUT);
 // pinMode(PP_3, OUTPUT);
  //pinMode(PQ_1, OUTPUT);
//  pinMode(PM_6, OUTPUT);

  //init control devices
  //feedbackDevice = new Ma3Encoder12b(PA_2); //used for absolutely nothing, but hey demonstration of setting it up. 

/**************************************/
  controller = new DRV8388(PP_3, PQ_1, PM_6, false);
  interFace = new SingleMotorJoint(spd, controller);

 /************************************/
  
  //algorithm = new PIAlgorithm(3,3,3);
  
}


void loop() {
 


  //move motor
  interFace -> runOutputControl(500);

  //digitalWrite(
  

/*
  //read analog data
  analog1 = analogRead(PD_0);
  //some command here to send this value to base station
  analog2 = analogRead(PD_1);
  //some command here to send this value to base station
  //NEED command send data to base station

  //turn on laser function
  turnOnLaser();

  //turn off laser function
  turnOffLaser();

  //function to open flap
  openFlap();

  //function to close flap
  closeFlap();
  
  
  //stop analog read
  //return motor to original position


  delay(1000);
  flap.write(0);
  
  //turn the sample cache carousel 
  carousel.write(0);
  delay(500);
  carousel.write(45);
  delay(500);
  carousel.write(90);
  delay(500);
  carousel.write(135);
  delay(500);
  carousel.write(180);
  delay(500);
  */
 
}

void rotateCarousel(int pos)//need to discuss bets implementation of this
{
  carousel.write(180/5 * pos);  //cache positions must be tweeked here.
}

void openFlap()
{
  //does flap open at 180 degrees or 0?
  flap.write(180);
}

void closeFlap()
{
  //again, does flap close at 180 degrees or 0?
  flap.write(0);
}

void turnOnLaser()
{
  //turn on laser by setting pin to High
  digitalWrite(PQ_3, HIGH);
}

void turnOffLaser()
{
  //turn off laser by setting pin to low
  digitalWrite(PQ_3, LOW);
}
