#include "Servo.h"

/* Programmers: Jimmy Haviland & Chris Dutcher
   Date of creation: 1/22/2017
   Sub system: science board

   program overhead:
   testing stuff
   //need to add rove comm functionality and feedback for photodiode and error messages
*/

//create servos
Servo flap, carousel;



void setup() {

  flap.attach(PL_0);
  carousel.attach(PL_2);

  Serial.begin(9600);

  pinMode(PF_0, OUTPUT);//LED
  // pinMode(PP_3, OUTPUT);
  // pinMode(PQ_3, OUTPUT);//LED
  //  pinMode(PM_6, OUTPUT);
}


void loop() {

  /*carousel.write(0);
    int ms_delay = 20;
    int l_delay = 3500;
    int pos1 = 0, pos2 = 45, pos3 = 90, pos4 = 135, pos5 = 170;

    blink_LED(1);
    delay(l_delay);

    //loop through carousel positions
    for (int i = pos1; i < pos2; i++)
    {
    carousel.write(i);
    delay(ms_delay);
    }
    blink_LED(2);
    delay(l_delay);

    for (int i = pos2; i < pos3; i++)
    {
    carousel.write(i);
    delay(ms_delay);
    }
    blink_LED(3);
    delay(l_delay);

    for (int i = pos3; i < pos4; i++)
    {
    carousel.write(i);
    delay(ms_delay);
    }
    blink_LED(4);
    delay(l_delay);*/

  /*for (int i = pos4; i < pos5; i++)
    {
    carousel.write(i);
    delay(ms_delay);
    }
    delay(l_delay);*/



  //function to open flap
  openFlap();

  delay(3000);

  closeFlap();

  delay(3000);

  /*for(int i = 0; i <= 4; i++)
    {
    flapToPos(i*45);
    delay(5000);
    }*/
  /*servoToPos(10);//pos 1
  delay (5000);
  servoToPos(55);//pos2
  delay(5000);
  servoToPos(110);//pos3
  delay(5000);
  servoToPos(155);//pos4
  delay(5000);
  servoToPos(159);//pos5
  delay(5000);
  digitalWrite(PF_0, HIGH);//led*/

  //delay(5000);//wait 5 seconds to repeat loop. LED indicates wait
  //flapToPos(0);
  //function to close flap
  //closeFlap();


  //digitalWrite(PF_0, LOW);

  // delay(5000);

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

void blink_LED(int num)
{
  for (int i = 0; i < num; i++)
  {
    digitalWrite(PF_0, HIGH);
    delay(500);
    digitalWrite(PF_0, LOW);
    delay(500);
  }
}

void servoToPos(int pos)
{
  if (pos > 180)
  {
    pos = 180;
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
  int ms_delay;
  carousel.write(180 / 5 * pos); //cache positions must be tweeked here.
}

void openFlap()
{
  //does flap open at 180 degrees or 0?
  flap.write(0);
}

void closeFlap()
{
  //again, does flap close at 180 degrees or 0?
  flap.write(100);
}

void flapToPos(int pos)
{
  flap.write(pos);
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
