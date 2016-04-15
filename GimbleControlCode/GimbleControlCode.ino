#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <RoveBoard.h>
#include <RoveEthernet.h>

#include <RoveComm.h>




#include <dyna.h>



#define PWM0 26
#define PWM1 25
#define PWM2 24
#define PWM3 23

#define SHORT_SIGNAL 1000
#define MID_SIGNAL 1500
#define LONG_SIGNAL 2000




#define HORIZONTAL_DYNAMIXEL_ID 4
#define VERTICAL_DYNAMIXEL_ID 5


#define ID_CW_LIMIT 7
#define ID_CCW_LIMIT 9
#define ID_GOAL_POSITION 30



#define ID_CAMERA_COMMAND 1568
#define ID_GIMBAL_SPEED 1552
#define ID_CAMERA_MENU 1569




void setup() {
  
  Serial.begin(9600);
  
  
  
  init();//initialize Dynamixel library
  
  //set dynamixels to be in continuous rotation mode.
  setRegister2(HORIZONTAL_DYNAMIXEL_ID,ID_CW_LIMIT,0);
  setRegister2(HORIZONTAL_DYNAMIXEL_ID,ID_CCW_LIMIT,0);
  setRegister2(VERTICAL_DYNAMIXEL_ID,ID_CW_LIMIT,0);
  setRegister2(VERTICAL_DYNAMIXEL_ID,ID_CCW_LIMIT,0);
  
  //initialize pin modes
  pinMode(PWM0,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(PWM3,OUTPUT);
  digitalWrite(PWM0,0);
  digitalWrite(PWM1,0);
  digitalWrite(PWM2,0);
  digitalWrite(PWM3,0);

  //debug: flash LED's on dynamixel once to indicate they are communicating
  setRegister(254,0x19,1);        
  delay(100);
  setRegister(254,0x19,0);
  delay(100);

 
 roveComm_Begin(192,168,1,52);
 
}



void loop(){
  uint16_t* dataID;
  byte msg[100];
  byte tmp;
  roveComm_GetMsg(dataID, 0, msg);
  
  switch(msg[2]){
    case ID_GIMBAL_SPEED:
      tmp = msg[3];
      //TODO
    break;
    
    case ID_CAMERA_MENU:
      tmp = msg[3];
      if(tmp==0){
        toggleMenu();
      }
      else if(tmp==1){
        navigateMenuLeft();
      }
      else if(tmp==2){
        navigateMenuRight();
      }
      else if(tmp==3){
        navigateMenuUp();
      }
      else if(tmp==4){
        navigateMenuDown();
      }
    break;
    
    case ID_CAMERA_COMMAND:
      tmp = msg[3];
      if(tmp==0){
        stopZoomAndFocus();
      }
      else if(tmp==1){
        zoomIn();
      }
      else if(tmp==2){
        zoomOut();
      }
      else if(tmp==3){
        focusIn();
      }
      else if(tmp==4){
        focusOut();
      }
    break;
    
   
    
  }
  
}





//moveSpeed: -1000 to 1000
void moveCameraHorizontally(int moveSpeed){
  moveSpeed=moveSpeed*2000/1023-1000;
  setRegister(HORIZONTAL_DYNAMIXEL_ID,ID_GOAL_POSITION,moveSpeed);
}
//moveSpeed: -1000 to 1000
void moveCameraVertically(int moveSpeed){
  moveSpeed=moveSpeed*2000/1023-1000;
  setRegister(VERTICAL_DYNAMIXEL_ID,ID_GOAL_POSITION,moveSpeed);
}




void zoomIn(){
  generateSignal(LONG_SIGNAL,PWM0);
}
void zoomOut(){
  generateSignal(SHORT_SIGNAL,PWM0);
}
void focusIn(){
  generateSignal(LONG_SIGNAL,PWM1);
}
void focusOut(){
  generateSignal(SHORT_SIGNAL,PWM1);
}
void stopZoomAndFocus(){
  generateSignal(MID_SIGNAL,PWM0);
  generateSignal(MID_SIGNAL,PWM1);
}




void zoomIn(int time){
  zoomIn();
  delay(time);
  stopZoomAndFocus();
}
void zoomOut(int time){
  zoomOut();
  delay(time);
  stopZoomAndFocus();
}
void focusIn(int time){
  focusIn();
  delay(time);
  stopZoomAndFocus();
}
void focusOut(int time){
  focusOut();
  delay(time);
  stopZoomAndFocus();
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


