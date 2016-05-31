#include "VnhHalfBridgeMotorDriver.h"

// %10 of SPEED_5019_MAX

#define SPEED_INC_DELAY         2
#define BRAKE_DELAY             50
 
#define SOFT_WATCHDOG_MILLIS    100

#define BRAKE_5019_INDUCTIVE    400

#define SPEED_5019_OPEN_MAX    -400
#define SPEED_5019_CLOSE_MAX    400

#define SPEED_NEUTRAL_ZENITH    128

#define SPEED_ZENITH_OPEN_MAX   0
#define SPEED_ZENITH_CLOSE_MAX  255

#define SPEED_JUMP_ZENITH_CLOSE_INC_MAX 20

#define SPEED_JUMP_ZENITH_OPEN_INC_MAX -20

#define SPEED_JUMP_INC_DELAY 10

#define SETUP_DELAY 10

const int8_t GRIPPER_CURRENT_FAULT = -1.0;

 // Default shield Pin map
 // _PWM1 = 9
 // _INA1 = 2;
 // _INB1 = 4;
 // _EN1DIAG1 = 6;
 // _CS1 = A0; 
 
//override

#define IN_A1 A2
#define IN_B1 4
#define EN1_DIAG1 17
#define CS_1 A0

#define EN_6V 8
#define SERVO_1 5
#define SERVO_2 6

VnhHalfBridgeMotorDriver GripperMotor(IN_A1, IN_B1, EN1_DIAG1, CS_1);

byte command_speed         = 0;
byte last_command_speed    = 0;

int  motor_speed      = 0;

unsigned long last_watch_clear_millis = 0;

////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  
  delay(SETUP_DELAY);
 
  GripperMotor.init();
  
  delay(SETUP_DELAY);
  
  last_watch_clear_millis = millis();
  
}//end fnctn

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void loop()
{
  while( Serial.available() )
  {
    command_speed = Serial.read();
    
    if(command_speed > SPEED_NEUTRAL_ZENITH)
    {
      if( command_speed > last_command_speed + SPEED_JUMP_ZENITH_CLOSE_INC_MAX)
      {
        command_speed = last_command_speed + SPEED_JUMP_ZENITH_CLOSE_INC_MAX;
        delay(SPEED_JUMP_INC_DELAY);
      }//end if
    }//end if
    
    if(command_speed < SPEED_NEUTRAL_ZENITH)
    {
      if( command_speed < last_command_speed - SPEED_JUMP_ZENITH_OPEN_INC_MAX)
      {
        command_speed = last_command_speed - SPEED_JUMP_ZENITH_OPEN_INC_MAX;
        delay(SPEED_JUMP_INC_DELAY);
      }//end if
    }//end if
      
    last_command_speed = command_speed;
   
    if(command_speed == SPEED_NEUTRAL_ZENITH)
    {
      GripperMotor.setM1Brake(BRAKE_5019_INDUCTIVE);
      stopIfFault();
      delay(BRAKE_DELAY);   
    }else{
      
      motor_speed = map( (int)command_speed, SPEED_ZENITH_OPEN_MAX, SPEED_ZENITH_CLOSE_MAX, SPEED_5019_OPEN_MAX, SPEED_5019_CLOSE_MAX);
      motor_speed = constrain(motor_speed,   SPEED_5019_OPEN_MAX, SPEED_5019_CLOSE_MAX);    

      GripperMotor.setM1Speed(motor_speed); 
      stopIfFault(); 
      delay(SPEED_INC_DELAY);      
    }//end if  
    
    last_watch_clear_millis = millis();
  }//end while
  
  if( (millis() - last_watch_clear_millis ) > SOFT_WATCHDOG_MILLIS)
  {
    GripperMotor.setM1Brake(BRAKE_5019_INDUCTIVE);
    stopIfFault();
    delay(BRAKE_DELAY);
  }//end if 

}//end loop

///////////////////////////////////////////////////////////////
//todo
void stopIfFault()
{
  if (GripperMotor.getM1Fault())
  {
    GripperMotor.setM1Brake(BRAKE_5019_INDUCTIVE);
    
    while(1)
    {
      Serial.write(GRIPPER_CURRENT_FAULT);
    }//end while
  }//end if
}//end fnctn
