#include <Servo.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <RoveBoard.h>
#include <RoveEthernet.h>
#include <RoveComm.h>
#include <RoveDynamixel.h>

//---Pin assignments:
// Camera PWM Controls
#define PWM0 PD_2
#define PWM1 PD_3
#define PWM2 PD_1
#define PWM3 PD_0

// Dropbays
#define DROPBAY0 PK_0
#define DROPBAY1 PF_1
#define DROPBAY2 PP_0
#define DROPBAY3 PL_0

// Dynamixel Channels
#define GIMB1_SER 7
#define GIMB2_SER 5
#define DYN1_SER  3
#define DYN2_SER  2
//-------------------

//Camera pulse lengths (ms)
#define SHORT_SIGNAL 1000
#define MID_SIGNAL 1500
#define LONG_SIGNAL 2000

//Dynamixel ID's
#define HOR_CAM_1  0 
#define VERT_CAM_1 0
#define HOR_CAM_2  0
#define VERT_CAM_2 0

//Dynamixel function ID's
#define ID_CW_LIMIT 6
#define ID_CCW_LIMIT 8
#define ID_SPEED 32

//Basestation command ID's
#define ID_CAMERA_COMMAND 1568
#define ID_GIMBAL_SPEED 1552
#define ID_CAMERA_MENU 1569
#define ID_DROP_BAY 1584
#define ID_GIMBAL_SPEED_2 1553

#define DROPBAY_ANGLE_OPEN 170

#define TIMEOUT_TICKS 1000

#define DYNA_BAUD 1000000

Dynamixel gimb1_hor, gimb1_vert;
Dynamixel gimb2_hor, gimb2_vert;

uint16_t dataID = 0;
size_t size = 0;
char data[8];
int counter;

Servo Dropbay[4];

void setup() {
  // initialize gimbal dynamixels ??? does this function need a 5 second wait time?
  DynamixelInit(&gimb1_hor,  AX, HOR_CAM_1, GIMB1_SER, DYNA_BAUD);
  DynamixelInit(&gimb1_vert, AX, HOR_CAM_1, GIMB1_SER, DYNA_BAUD);
  DynamixelInit(&gimb2_hor,  AX, HOR_CAM_2, GIMB2_SER, DYNA_BAUD);
  DynamixelInit(&gimb2_vert, AX, HOR_CAM_2, GIMB2_SER, DYNA_BAUD);

  //set dynamixels to be in continuous rotation (Wheel) mode.
  DynamixelSetMode(gimb1_hor, Wheel);
  DynamixelSetMode(gimb1_vert, Wheel);
  DynamixelSetMode(gimb2_hor, Wheel);
  DynamixelSetMode(gimb1_vert, Wheel);
    
  // set camera control pins to output
  pinMode(PWM0,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(PWM3,OUTPUT);
  
  // write low signal to camera pins
  digitalWrite(PWM0,0);
  digitalWrite(PWM1,0);
  digitalWrite(PWM2,0);
  digitalWrite(PWM3,0);
  
  // pair servos to correct PWM pins
  Dropbay[0].attach(DROPBAY0);
  Dropbay[1].attach(DROPBAY1);
  Dropbay[2].attach(DROPBAY2);
  Dropbay[3].attach(DROPBAY3);
  
  delay(100);

  // begin communicating with Monitor and RED
  roveComm_Begin(192,168,1,134);
  Serial.begin(9600);
  Ethernet.enableLinkLed();
  Ethernet.enableActivityLed();
  
  delay(100);

  //TODO: debug: flash LED's on dynamixel to indicate they are communicating
//  blink(3);
}

void blink(int num_times){
  for(int i = 0; i < num_times; i++)
  {
    
  }
}

int count = 0;
void loop()
{
  // ensure constant connection with RED
  if(roveCommCheck()) 
    count = 0;
  else
  {
    count++;
    if(count > TIMEOUT_TICKS)
    {
      // currently set to 500 to check speed writing without RoveComm
      moveDynamixel(gimb1_hor,  500);
      moveDynamixel(gimb1_vert, 500);
      moveDynamixel(gimb2_hor,  500);
      moveDynamixel(gimb2_vert, 500);
      // TODO: stop dynamixels
    }
    delay(1);
  }
}

boolean roveCommCheck()
{  
  roveComm_GetMsg(&dataID, &size, data);
  if(dataID==0) return false;
  
  uint8_t tmp;
  int16_t xSpeed;
  int16_t ySpeed;
  char a[2];
  
  switch(dataID){
    case ID_DROP_BAY:
      tmp = *(uint8_t*)(data);
      openDropBay(tmp);
      break;
  }
  return true;
}

void openDropBay(int bay){
  unsigned long time = millis();
  while(millis()<time+1000){
    Dropbay[bay].write(DROPBAY_ANGLE_OPEN);
    delay(1000);
  }
}

//moveSpeed: -1000 to 1000
void moveDynamixel(Dynamixel dyn, int moveSpeed){
  if(moveSpeed<0)
  {
    moveSpeed = abs(moveSpeed)*1023/1000;
  }
  else
  {
    moveSpeed = moveSpeed*1023/1000+1024;
  }
  
  if(moveSpeed<0){ moveSpeed=0; }
  if(moveSpeed>2047){ moveSpeed=2047; }

  // write speed to dynamixel
  DynamixelSpinWheel(dyn, moveSpeed);
}

/// Camera Control
boolean active = false;
/*   CAMERA 1 CONTROLS   */
void zoomIn(){
  active=true;
  generateSignal(LONG_SIGNAL,PWM0);
}
void zoomOut(){
  active=true;
  generateSignal(SHORT_SIGNAL,PWM0);
}
void focusIn(){
  active=true;
  generateSignal(LONG_SIGNAL,PWM1);
}
void focusOut(){
  active=true;
  generateSignal(SHORT_SIGNAL,PWM1);
}
void stopZoomAndFocus(){
  if(!active)return;
  active=false;
  generateSignal(MID_SIGNAL,PWM0);
  generateSignal(MID_SIGNAL,PWM1);
}

void toggleMenu(){
  generateSignal(MID_SIGNAL,PWM2);
  generateSignal(LONG_SIGNAL,PWM2);
}
void navigateMenuLeft(){
  generateSignal(MID_SIGNAL,PWM1);
  generateSignal(SHORT_SIGNAL,PWM1);
}
void navigateMenuRight(){
  generateSignal(MID_SIGNAL,PWM1);
  generateSignal(LONG_SIGNAL,PWM1);
}
void navigateMenuUp(){
  generateSignal(MID_SIGNAL,PWM0);
  generateSignal(LONG_SIGNAL,PWM0);
}
void navigateMenuDown(){
  generateSignal(MID_SIGNAL,PWM0);
  generateSignal(SHORT_SIGNAL,PWM0);
}

void generateSignal(int amt, int pin){
  for(int i = 0; i < 5; i++){
    digitalWrite(pin,1);
    delayMicroseconds(amt);
    digitalWrite(pin,0);
    delayMicroseconds(20000-amt);
  }
}
