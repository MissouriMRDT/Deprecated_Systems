#include "VnhHalfBridgeMotorDriver.h"

// %10 of SPEED_5019_MAX
#define START_UP_ROUTINE_SPEED 40
#define START_UP_ROUTINE_DELAY 300
 
#define SPEED_INC_DELAY 2
#define BRAKE_DELAY 250
 
#define SOFT_WATCHDOG_MILLIS    500     
#define BRAKE_VNH_INDUCTIVE    400

#define SPEED_VNH_OPEN_MAX    -400
#define SPEED_VNH_CLOSE_MAX    400

#define SPEED_NEUTRAL_ZENITH    128

#define SPEED_ZENITH_OPEN_MAX   0
#define SPEED_ZENITH_CLOSE_MAX  255

#define SPEED_JUMP_MAX_FORWARD 25
#define SPEED_JUMP_MAX_REVERSE -25
#define RAMP_DELAY_INC_MILLIS 2

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

byte command_speed    = 0;
int  motor_speed      = 0;
int  last_motor_speed = 0;

unsigned long last_watch_clear_millis = 0;

////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
 
  GripperMotor.init();
  
  last_watch_clear_millis = millis();
}//end fnctn

/////////////////////////////////////////////////////////////
void loop()
{
  while(Serial.available())
  {
    command_speed = Serial.read();
   
    if(command_speed == SPEED_NEUTRAL_ZENITH)
    {
      GripperMotor.setM1Brake(BRAKE_VNH_INDUCTIVE);
      stopIfFault();
      last_motor_speed = 0;          
      delay(BRAKE_DELAY);  
    }else{
      
      motor_speed = map( (int)command_speed, SPEED_ZENITH_OPEN_MAX, SPEED_ZENITH_CLOSE_MAX, SPEED_VNH_OPEN_MAX, SPEED_VNH_CLOSE_MAX);
     
      last_motor_speed = Gripper_RampM1Speed(motor_speed, last_motor_speed);
      
      stopIfFault(); 
      delay(SPEED_INC_DELAY);      
    }//end if  
    
    last_watch_clear_millis = millis();
  }//end while
  
  if( (millis() - last_watch_clear_millis ) > SOFT_WATCHDOG_MILLIS)
  {
    GripperMotor.setM1Brake(BRAKE_VNH_INDUCTIVE);
    last_motor_speed = 0; 
     
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
    GripperMotor.setM1Brake(BRAKE_VNH_INDUCTIVE);
    delay(BRAKE_DELAY);
  
    while(1)
    {
      Serial.write(GRIPPER_CURRENT_FAULT);
    }//end while
  }//end if
}//end fnctn

uint8_t Gripper_RampM1Speed(uint8_t speed, uint8_t last_speed)
{
  if(speed > 0)
  {
    if( speed - last_speed > SPEED_JUMP_MAX_FORWARD )
    {
      speed = last_speed + SPEED_JUMP_MAX_FORWARD;   
      speed = constrain(speed,   SPEED_VNH_OPEN_MAX, SPEED_VNH_CLOSE_MAX);    

      GripperMotor.setM1Speed(speed);
      stopIfFault(); 
      
      delay(RAMP_DELAY_INC_MILLIS);
     
      last_speed = speed;
      return last_speed; 
    }//end if
  }//end if
  
  if(speed < 0)
  {  
    if( speed + last_speed < SPEED_JUMP_MAX_REVERSE )
    { 
      speed = last_speed - SPEED_JUMP_MAX_REVERSE;
      speed = constrain(speed,   SPEED_VNH_OPEN_MAX, SPEED_VNH_CLOSE_MAX);    

      GripperMotor.setM1Speed(speed);
      stopIfFault();  

      delay(RAMP_DELAY_INC_MILLIS); 
      
      last_speed = speed; 
      
      return last_speed;  
    }//end if
    
  }//end if
  
  GripperMotor.setM1Speed(speed);
  last_speed = speed;
  return last_speed; 
}//end RampSpeed
