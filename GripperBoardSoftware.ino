#include "DualVNH5019MotorShield.h"

 // Default shield Pin map
 // _INA1 = 2;
 // _INB1 = 4;
 // _EN1DIAG1 = 6;
 // _CS1 = A0; 

#define CW_CHAR 'A'
#define CCW_CHAR 'B'
#define STOP_CHAR 'X'

DualVNH5019MotorShield GripperMotor;

void stopIfFault()
{
  if (GripperMotor.getM1Fault())
  {
    Serial.println("GripperMotor fault");
    while(1);
  }
}//end fnctn

void setup()
{
  Serial.begin(9600);
  
  //Serial.println("Dual VNH5019 Motor Shield");
  
  GripperMotor.init();
}//end fnctn

void loop()
{
  // 0-255 speed values
 
  if(Serial.available() > 0)
  {
    char tmp = Serial.read();
    
    //Serial.println(tmp);
    
    if(tmp == CW_CHAR)
    {
      while(Serial.available()==0);
      byte command_speed = Serial.read();
      
      int motor_speed = map( (int)command_speed, 0, 255, -400, 400);
      motor_speed = constrain(motor_speed, -400, 400);
      
      GripperMotor.setM1Speed(motor_speed);
      stopIfFault();
      delay(2);

    }//end if
    
    else if(tmp == CCW_CHAR)
    {
      while(Serial.available()==0);
      byte command_speed = Serial.read();
      
      int motor_speed = map( (int)command_speed, 0, 255, -400, 400);
      motor_speed = constrain(motor_speed, -400, 400);
      
      GripperMotor.setM1Speed(motor_speed);
      stopIfFault();
      delay(2); 
    }//end if
    
    else if(tmp == STOP_CHAR)
    {
      GripperMotor.setM1Brake(400);    
    }//end if
     
  }//end if
  
}//end loop


