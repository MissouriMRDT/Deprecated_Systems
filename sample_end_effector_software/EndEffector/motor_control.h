#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

  


/* 
   Current Draw Prediction: These values are based on the linear regression of the 
   current sense data vs pwm of the motor running with no resistance. To get this data
   see MotCurrentSenseTest
*/
const float CURRENT_SLOPE = 0.146191; //Slope from linear regression of current sense vs pwm
const float CURRENT_INTERCEPT = 10.3973; //Intercept from linear regression of current sense vs pwm

//Reads voltage average over acc milliseconds from pin, meant for use with current sense pins
//Pre: 
//Post:
int currentRead(int pin, int acc = 0);

//Calculates and returns new PWM speed to set motor to. Increases power until current use
// is within bounds
int updateMotor(const int desired_speed, const int actual_speed, const int current);

//Calculates expected reading on the current sense pin for a given speed
// based on data from testing
float calculate_desired_current(int motor_speed);


int currentRead(const int pin, const int acc)
{
  int current = 0;
  for(int i = 0; i<acc; i++)
  {
    current += analogRead(pin);
    delay(1);
  }
  current /= acc;
  Serial.println("Current read is " + (String)current);
 
  return current;
}

int updateMotor(const int desired_speed, const int actual_speed, const int current)
{
  int new_speed;
  float max_goal_current;
  float min_goal_current;
  float desired_current = calculate_desired_current(desired_speed);
  
  desired_current *= MAX_VARIATION;
  if(current > desired_current)
  {
    float goal_current = calculate_desired_current(actual_speed);
    max_goal_current *= MAX_VARIATION;
    min_goal_current *= MIN_VARIATION;
    
    /* Drill is running at full power, still stalled */
    if(actual_speed > MAX_SPEED)
    {
      Serial.println("Maximum Capacity. Reccomend Shutdown.");
      new_speed = MAX_SPEED;
      
    /* Drill is too slow, stalled */
    } else if(current > max_goal_current)
    {
      new_speed = actual_speed + SPEED_STEP;
      Serial.println("Stepping up speed");
    
    /* Drill is too fast, clog is cleared */
    } else if (current < min_goal_current)  
    {
      new_speed = actual_speed - SPEED_STEP;
      Serial.println("Stepping down speed");
    } else
    {
      Serial.println("Keeping constant elevated speed.");
      new_speed = desired_speed;
    }
  } else
  {
    Serial.println("Current levels good.");
    new_speed = desired_speed;
  }
  Serial.println("Tyring to run at " + (String)new_speed);
  return new_speed;
}

float calculate_desired_current(int motor_speed)
{  
  float current = (CURRENT_SLOPE * motor_speed) + CURRENT_INTERCEPT;
  Serial.println("Desired Current");
  Serial.println(current);
  return current;
}


#endif
