#include "Servo.h"

/* Programmers: Jimmy Haviland & Chris Dutcher
 * Date of creation: 1/22/2017
 * Sub system: science board
 * 
 * program overhead:
 * testing stuff
 * //need to add rove comm functionality and feedback for photodiode and error messages
 */

//create servos
Servo flap, carousel;

  

void setup() {

  flap.attach(PM_5);
  carousel.attach(PM_4);
  
  Serial.begin(9600);

  pinMode(PF_0, OUTPUT);//LED
 // pinMode(PP_3, OUTPUT);
 // pinMode(PQ_3, OUTPUT);//LED
//  pinMode(PM_6, OUTPUT);
}


void loop() {

  //function to open flap
  openFlap();

  digitalWrite(PF_0, HIGH);

  delay(5000);

  //function to close flap
  closeFlap();

  digitalWrite(PF_0, LOW);
  
  delay(5000);

  //return motor to original position

/*
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

void servoToPos(int pos)
{
  if(pos > 170)
  {
    pos = 170;
  }
  if (pos < 0)
  {
    pos = 0;
  }
  flap.write(pos);
  carousel.write(pos);
}

void rotateCarousel(int pos)//need to discuss bets implementation of this
{
  carousel.write(180/5 * pos);  //cache positions must be tweeked here.
}

void openFlap()
{
  //does flap open at 180 degrees or 0?
  flap.write(0);
}

void closeFlap()
{
  //again, does flap close at 180 degrees or 0?
  flap.write(110);
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
