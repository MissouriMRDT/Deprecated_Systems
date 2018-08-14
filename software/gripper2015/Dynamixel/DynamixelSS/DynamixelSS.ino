#include <DynamixelSoftSerial.h>
#include <SoftwareSerial.h>
#include <Serial.h>

/*
THIS IS MY SCRATCH PAN FOR CODE
IT CONTAINS ALL OF THE FUNCTIONS
THAT WILL EB NEEDED TO CONTROL THE DYNAMIXELS

BEST BET IS TO MEASURE THE MESSAGES COMING OFF OF THE USB2DYNAMIXEL
*/




//SoftwareSerial mySerial(8,9);

void setup(){
Dynamixel.begin(115200,8,9,4);  // Inicialize the servo at 1Mbps and Pin Control 2

//mySerial.begin(9600);
//Serial.begin(9600);


//delay(1000);
}

void loop(){

  Dynamixel.move(2,random(200,800));  // Move the Servo radomly from 200 to 800
  delay(1000);
  //Dynamixel.moveSpeed(1,random(200,800),random(200,800));
  //delay(2000);
  //Dynamixel.setEndless(2,ON);
  //Dynamixel.turn(2,RIGTH,1000);
  //delay(3000);
  //Dynamixel.turn(2,LEFT,1000);
  //delay(500);
  //Dynamixel.setEndless(1,OFF);
  //Dynamixel.ledStatus(1,ON);
  //Dynamixel.moveRW(1,512);
  //delay(1000);
  //Dynamixel.action();
  //Dynamixel.ledStatus(1,OFF);
 
//delay(1000);

}
