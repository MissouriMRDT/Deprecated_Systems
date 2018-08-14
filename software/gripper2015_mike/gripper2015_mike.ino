#include "DynamixelSerial.h"

const int ID = 1;

//Dynamixel d;

void setup() {
  // put your setup code here, to run once:
  Dynamixel.begin(115200);
  delay(100);
  Dynamixel.setEndless(ID, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  Dynamixel.turn(ID, RIGTH, 255);
}
