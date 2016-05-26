#include "DualVNH5019MotorShield.h"

// %10 of SPEED_5019_MAX
#define START_UP_ROUTINE_SPEED 40
#define START_UP_ROUTINE_DELAY 300
 
#define SPEED_INC_DELAY 2
#define BRAKE_DELAY 250
 
#define SOFT_WATCHDOG_MILLIS    500     
#define BRAKE_5019_INDUCTIVE    400

#define SPEED_5019_OPEN_MAX    -400
#define SPEED_5019_CLOSE_MAX    400

#define SPEED_NEUTRAL_ZENITH    128

#define SPEED_ZENITH_OPEN_MAX   0
#define SPEED_ZENITH_CLOSE_MAX  255

const int8_t GRIPPER_CURRENT_FAULT = -1.0;

DualVNH5019MotorShield GripperMotor;

 // Default shield Pin map
 // _PWM1 = 9
 // _INA1 = 2;
 // _INB1 = 4;
 // _EN1DIAG1 = 6;
 // _CS1 = A0; 


byte command_speed = 0;
int  motor_speed   = 0;
int  LED_UNO       = 13;

unsigned long last_watch_clear_millis = 0;

////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
 
  pinMode(LED_UNO, OUTPUT); 
  
  GripperMotor.init();
  
  GripperMotor.setM1Speed(START_UP_ROUTINE_SPEED); 
  stopIfFault();
  delay(START_UP_ROUTINE_DELAY);
   
  GripperMotor.setM1Brake(BRAKE_5019_INDUCTIVE);
  stopIfFault();
  delay(BRAKE_DELAY);
   
  GripperMotor.setM1Speed(-START_UP_ROUTINE_SPEED); 
  stopIfFault();
  delay(START_UP_ROUTINE_DELAY); 
  
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
      GripperMotor.setM1Brake(BRAKE_5019_INDUCTIVE);
      stopIfFault();
      delay(BRAKE_DELAY);   
    }else{
      
      motor_speed = map( (int)command_speed, SPEED_ZENITH_OPEN_MAX, SPEED_ZENITH_CLOSE_MAX, SPEED_5019_OPEN_MAX, SPEED_5019_CLOSE_MAX);
      motor_speed = constrain(motor_speed,   SPEED_ZENITH_OPEN_MAX, SPEED_ZENITH_CLOSE_MAX);    

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
      digitalWrite(LED_UNO, HIGH);
      Serial.write(GRIPPER_CURRENT_FAULT);
    }//end while
  }//end if
}//end fnctn
