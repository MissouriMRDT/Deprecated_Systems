///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Robitis smart servo J1, (Base Roll), DualDiff J3/J4 (elbow pitch, roll), DualDiff J5/J6 (wrist pitch, roll), 
////////////////////////////////////////
typedef struct
{
  uint8_t         motor_ID;
  //HardwareSerial *comms_SERIAL;
} RoveDyna_MX;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  UsDigital Absolute Encoders feedback for J1, (Base Roll), J2 (Shoulder Pitch) , DualDiff J3/J4 (elbow pitch/roll), DualDiff J5/J6 (wrist pitch/roll) 
////////////////////////////////////////
typedef struct
{
  uint8_t  pin_PULSE;
  uint16_t resolution_STEP;
} RoveEncoder_PULSE;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Rove Joint State for PID Control of Dual Dynamixel Differential USDigital Encoder DVO Joint 
////////////////////////////////////////
typedef struct
{
  RoveDyna_MX motor_RIGHT;
  RoveDyna_MX motor_LEFT;

  RoveEncoder_PULSE pin_PITCH;  
  RoveEncoder_PULSE pin_ROLL;
  
  uint16_t limit_PITCH_MAX;
  uint16_t limit_PITCH_MIN;  
  uint16_t limit_ROLL_MAX;
  uint16_t limit_ROLL_MIN; 
  
  uint16_t controller_PITCH_MAX;
  uint16_t controller_PITCH_MIN;
  uint16_t controller_ROLL_MAX;
  uint16_t contoller_ROLL_MIN;
} RoveDyna_DVO;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Maps a dual DVO dynamixel MX series dual motor joints : drives by left/right serial speed commands with PID read from pitch/roll pulseIn encoder feedback for two connected joints (four dynamixel motors, four encoder angles)
////////////////////////////////////////

// todo FLOAT?
typedef struct
{
  uint16_t dx_STEPS;
  uint16_t pulse_TRIES;
  uint16_t duration_MILLIS;
  
  uint16_t speed_MAX;
  float speed_GAIN;
  
  uint16_t dx;
  uint16_t step_dx;
  uint16_t previous_dx;
  
  uint16_t P;
  uint16_t I;
  uint16_t D;
} RoveDyna_PID;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Wraps for Energia idiom
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoveDynaDVO 
{
private:

  RoveDyna_DVO Dvo;
  RoveDyna_PID Pid;
  
  void attachMX(   byte id,  byte serial_index, int baud_rate, RoveDyna_MX* Dyna);
  void attachPULSE(byte pin, int resolution,    RoveEncoder_PULSE* Encoder); 
  void convertSpeeds(int* speed_right, int* speed_left);
  int  convertPitch( int goal_pitch);
  int  convertRoll(  int goal_roll);
  int  unitStepPID(int angle_TO, int angle_AT, int* motor_speed_RIGHT, int* motor_speed_LEFT); 
public:

  void attachDVO(byte right_dyna_id,  byte left_dyna_id, byte serial_index, int baud_rate, byte pitch_pin, byte roll_pin, int encoder_resolution); 
  void attachPID(int system_step_cnt, int capture_restart_try_cnt, int loop_duration_millis, int speed_max, float speed_gain, int P, int I, int D); 
  void twist(int pitch_TO, int roll_TO);
};//end class

// C/C++ Instance interface
void RoveDynaDVO::attachDVO(byte right_dyna_id, byte left_dyna_id, byte serial_index, int baud_rate, byte pitch_pin, byte roll_pin, int encoder_resolution)
{ 
  attachMX( (uint8_t)right_dyna_id, (uint8_t)serial_index, (uint32_t)baud_rate, &(this->Dvo.motor_RIGHT) );
  attachMX( (uint8_t)left_dyna_id,  (uint8_t)serial_index, (uint32_t)baud_rate, &(this->Dvo.motor_LEFT) );
  
  attachPULSE( (uint8_t)pitch_pin, (uint16_t)encoder_resolution, &(this->Dvo.pin_PITCH) );
  attachPULSE( (uint8_t)roll_pin,  (uint16_t)encoder_resolution, &(this->Dvo.pin_ROLL) );
}//end begin

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Instance Constructors
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" 
{
  void RoveDyna_attachMX(uint8_t id, uint8_t serial_index, uint32_t baud_rate, RoveDyna_MX* Dyna);
  void RoveDyna_attachMX(uint8_t id, uint8_t serial_index, uint32_t baud_rate, RoveDyna_MX* Dyna) 
  {
    //Dyna->comms_SERIAL = RoveBoard_UART_open(serial_index, baud_rate);
    Dyna->motor_ID     = id;
  }//end fnctn
}//end extern

// Dynamixel Mx Motor
void RoveDynaDVO::attachMX(byte id, byte serial_index, int baud_rate, RoveDyna_MX* Dyna)
{
  RoveDyna_attachMX( (uint8_t)id, (uint8_t)serial_index, (uint32_t)baud_rate, Dyna);
}//end fnctn

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pulse Encoder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" 
{
  void RoveEncoder_attachPULSE(uint8_t pin, uint16_t resolution, RoveEncoder_PULSE* Encoder) 
  {
    Encoder->resolution_STEP = resolution;
    Encoder->pin_PULSE       = pin;
  }//end fnctbn
}//end extern

void RoveDynaDVO::attachPULSE(byte pin, int resolution, RoveEncoder_PULSE* Encoder)
{
  RoveEncoder_attachPULSE( (uint8_t)pin, (uint16_t)resolution, Encoder); 
}//end fnctn

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Differential Joint by Joint Control Loop 
extern "C" 
{
  void RoveDyna_attachPID( uint16_t system_step_cnt, uint16_t capture_restart_try_cnt, uint16_t loop_duration_millis, uint16_t speed_max, float speed_gain, uint16_t P, uint16_t I, uint16_t D, RoveDyna_PID* DynaPID);
  void RoveDyna_attachPID( uint16_t system_step_cnt, uint16_t capture_restart_try_cnt, uint16_t loop_duration_millis, uint16_t speed_max, float speed_gain, uint16_t P, uint16_t I, uint16_t D, RoveDyna_PID* DynaPID)
  {
    DynaPID->dx_STEPS        = system_step_cnt; 
    DynaPID->pulse_TRIES     = capture_restart_try_cnt;
    DynaPID->duration_MILLIS = loop_duration_millis; 
    
    DynaPID->speed_GAIN      = speed_gain;
    DynaPID->speed_MAX       = speed_max;
  
    DynaPID->P = P;
    DynaPID->I = I;
    DynaPID->D = D;
  }//end fnctn
}//end extern

void RoveDynaDVO::attachPID(int system_step_cnt, int capture_restart_try_cnt, int loop_duration_millis, int speed_max, float speed_gain, int P, int I, int D)
{
  RoveDyna_attachPID( (uint16_t)system_step_cnt, (uint16_t)capture_restart_try_cnt, (uint16_t)loop_duration_millis, (uint16_t)speed_max, speed_gain, (uint16_t)P, (uint16_t)I, (uint16_t)D, &(this->Pid) );
}//end begin

////////////////////////////////////////////////////////////////////
// Functional Methods
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo
extern "C" 
{
  void RoveDyna_convertPitchDVO(uint16_t* goal_pitch, RoveDyna_DVO* DynaDVO);
  void RoveDyna_convertPitchDVO(uint16_t* goal_pitch, RoveDyna_DVO* DynaDVO)
  {
    // convert units and constrain limits
    *goal_pitch = map(      *goal_pitch, 0, DynaDVO->pin_PITCH.resolution_STEP, DynaDVO->controller_PITCH_MIN, DynaDVO->controller_PITCH_MAX);
    *goal_pitch = constrain(*goal_pitch,    DynaDVO->limit_PITCH_MIN,            DynaDVO->limit_PITCH_MAX);
    
  }//end fnctn
}//end extern

int RoveDynaDVO::convertPitch(int goal_pitch)
{
  uint16_t pitch = goal_pitch;
  RoveDyna_convertPitchDVO( &pitch, &(this->Dvo) );
  return (int32_t) pitch;
}//end begin

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo
extern "C" 
{
  void RoveDyna_convertRollDVO(uint16_t* goal_roll, RoveDyna_DVO* DynaDVO);
  void RoveDyna_convertRollDVO(uint16_t* goal_roll, RoveDyna_DVO* DynaDVO)
  {
   // convert units and constrain limits
    *goal_roll = map(      *goal_roll, 0, DynaDVO->pin_ROLL.resolution_STEP, DynaDVO->contoller_ROLL_MIN, DynaDVO->controller_ROLL_MAX);
    *goal_roll = constrain(*goal_roll,    DynaDVO->limit_ROLL_MIN,            DynaDVO->limit_ROLL_MAX);
  }//end fnctn
}//end extern

int RoveDynaDVO::convertRoll(int goal_roll)
{
  uint16_t roll = goal_roll;
  RoveDyna_convertRollDVO( &roll, &(this->Dvo) );
  return (int32_t) roll;
}//end begin

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo
extern "C" 
{
  void RoveDyna_convertSpeedsDVO( uint16_t* speed_right, uint16_t* speed_left, RoveDyna_PID* DynaPID);
  void RoveDyna_convertSpeedsDVO( uint16_t* speed_right, uint16_t* speed_left, RoveDyna_PID* DynaPID)
  {    
    *speed_right = (*speed_right) * (DynaPID->speed_GAIN);    
    *speed_left  = (*speed_left)  * (DynaPID->speed_GAIN);
  }//end fnctn
}//end extern

void RoveDynaDVO::convertSpeeds(int* speed_right, int* speed_left)
{
  RoveDyna_convertSpeedsDVO( (uint16_t*)speed_right, (uint16_t*)speed_left, &(this->Pid) );
}//end begin

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" 
{
  // todo
  void RoveDyna_unitStepPID(uint16_t angle_TO, uint16_t angle_AT,  uint16_t* motor_speed_RIGHT, uint16_t* motor_speed_LEFT, RoveDyna_PID* DynaPID);
  void RoveDyna_unitStepPID(uint16_t angle_TO, uint16_t angle_AT,  uint16_t* motor_speed_RIGHT, uint16_t* motor_speed_LEFT, RoveDyna_PID* DynaPID)
  {
    DynaPID->dx = angle_TO - angle_AT;
    
    // todo
    *motor_speed_RIGHT = angle_TO + ( (DynaPID->P * DynaPID->dx) + (DynaPID->I) + (DynaPID->D * (DynaPID->dx - DynaPID->previous_dx) / DynaPID->step_dx) );
    *motor_speed_LEFT  = angle_TO - ( (DynaPID->P * DynaPID->dx) + (DynaPID->I) + (DynaPID->D * (DynaPID->dx - DynaPID->previous_dx) / DynaPID->step_dx) );
   
    DynaPID->previous_dx = DynaPID->dx;
  }//end fnctn
}//end extern

int RoveDynaDVO::unitStepPID(int angle_TO, int angle_AT, int* motor_speed_RIGHT, int* motor_speed_LEFT)
{
  RoveDyna_unitStepPID( (uint16_t)angle_TO, (uint16_t)angle_AT, (uint16_t*)motor_speed_RIGHT, (uint16_t*)motor_speed_LEFT, &(this->Pid) );
}//end begin

//TODO:
uint32_t RoveSoft_pulseIn(uint8_t pin, uint8_t pin_state, uint32_t time_out)
{
  return pulseIn(pin, pin_state, time_out);
}//end fnctn


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo
extern "C" 
{
  void RoveDyna_twistDVO(uint16_t pitch_TO, uint16_t roll_TO, RoveDyna_DVO* DynaDVO, RoveDyna_PID* DynaPID)
  { 
    // pitch/roll commands
    uint16_t pitch_AT = 0; 
    uint16_t roll_AT  = 0;
    
    // with pid
    uint16_t pitch_dx_LAST = 0; 
    uint16_t roll_dx_LAST  = 0;
   
    uint16_t pitch_dx = 0; 
    uint16_t roll_dx  = 0;
  
    // to x/y total
    uint16_t motor_speed_RIGHT = 0;
    uint16_t motor_speed_LEFT  = 0; 
    
    uint16_t motor_speed_pitch_component_RIGHT = 0;
    uint16_t motor_speed_pitch_component_LEFT  = 0; 
    
    uint16_t motor_speed_roll_component_RIGHT = 0; 
    uint16_t motor_speed_roll_component_LEFT  = 0;
  
    // Broadcast Stop to all motors
    //RoveDyna_BROADCAST_STOP();
    
    // convert units and constrain limits
    RoveDyna_convertPitchDVO(&pitch_TO, DynaDVO); 
    RoveDyna_convertRollDVO( &roll_TO,  DynaDVO);
    
    DynaPID->step_dx                     = 0;
    
    uint32_t pid_step_millis             = 0; 
    uint32_t sync_twist_timestamp_millis = millis(); 
    
    while( pid_step_millis < (sync_twist_timestamp_millis + DynaPID->duration_MILLIS) )
    {
      // todo: RoveHard_pulseIn-> interrupt driven capture...see notes at eof
      pitch_AT = RoveSoft_pulseIn(DynaDVO->pin_PITCH.pin_PULSE, HIGH, (DynaPID->pulse_TRIES * DynaDVO->pin_PITCH.resolution_STEP) );
      roll_AT  = RoveSoft_pulseIn(DynaDVO->pin_ROLL.pin_PULSE,  HIGH, (DynaPID->pulse_TRIES * DynaDVO->pin_ROLL.resolution_STEP) );
        
      //translate each angle to a coordinate speed   
      RoveDyna_unitStepPID(pitch_TO, pitch_AT, &motor_speed_pitch_component_RIGHT, &motor_speed_pitch_component_LEFT, DynaPID);
      RoveDyna_unitStepPID(roll_TO,  roll_AT,  &motor_speed_roll_component_RIGHT,  &motor_speed_roll_component_LEFT,  DynaPID); 
      
      DynaPID->step_dx++;
      
      // in a differential joint, both pitch and roll angles have speed components
      motor_speed_RIGHT = motor_speed_pitch_component_RIGHT - motor_speed_roll_component_RIGHT;
      motor_speed_LEFT  = motor_speed_pitch_component_LEFT  - motor_speed_roll_component_LEFT;
      
      RoveDyna_convertSpeedsDVO(&motor_speed_RIGHT, &motor_speed_LEFT, DynaPID);
      
      //translate each angle to a coordinate speed
      //RoveDyna_setSpinWheelOnACTION(motor_speed_RIGHT, DynaDVO->motor_left);
      //RoveDyna_setSpinWheelOnACTION(motor_speed_LEFT,  DynaDVO->motor_left);
        
      //Brodcast Action to all motors
      //RoveDyna_broadcastACTION();
     
      pid_step_millis = millis();
    
    }//end while
    
    // Broadcast Stop to all motors
    //RoveDyna_BROADCAST_STOP();
  }//end fnctn
}//end extern

void RoveDynaDVO::twist(int pitch_TO, int roll_TO)
{
  RoveDyna_twistDVO( (uint16_t)pitch_TO, (uint16_t)roll_TO, &(this->Dvo), &(this->Pid) );
}//end begin

void setup(){}
void loop(){}


