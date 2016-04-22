#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <RoveBoard.h>
#include <RoveEthernet.h>

#include <RoveComm.h>




#include <dyna.h>


#define EN_12V PM_6
#define I_MEAS_12V PB_4


#define PWM0 26
#define PWM1 25
#define PWM2 24
#define PWM3 23


#define PWM0_CAM2 PA_5
#define PWM1_CAM2 PA_4
#define PWM2_CAM2 PD_5
#define PWM3_CAM2 PD_1





#define SHORT_SIGNAL 1000
#define MID_SIGNAL 1500
#define LONG_SIGNAL 2000




#define HORIZONTAL_DYNAMIXEL_ID 5//5
#define VERTICAL_DYNAMIXEL_ID 4//4


#define ID_CW_LIMIT 6
#define ID_CCW_LIMIT 8
#define ID_SPEED 32



#define ID_CAMERA_COMMAND 1568
#define ID_GIMBAL_SPEED 1552
#define ID_CAMERA_MENU 1569




void setup() {
  
  
  
  //initialize pin modes
  pinMode(PWM0,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(PWM3,OUTPUT);
  pinMode(EN_12V,OUTPUT);
  
  
  digitalWrite(PWM0,0);
  digitalWrite(PWM1,0);
  digitalWrite(PWM2,0);
  digitalWrite(PWM3,0);
  digitalWrite(EN_12V,1);
  
  delay(5000);
  
  Serial.begin(9600);

  init();//initialize Dynamixel library
  delay(100);
  
  
  //setRegister(254,3,4);
  //setRegister2(254,14,0x3ff);
  
  
  
  
  //set dynamixels to be in continuous rotation mode.
  setRegister2(HORIZONTAL_DYNAMIXEL_ID,ID_CW_LIMIT,0);
  setRegister2(HORIZONTAL_DYNAMIXEL_ID,ID_CCW_LIMIT,0);
  setRegister2(VERTICAL_DYNAMIXEL_ID,ID_CW_LIMIT,0);
  setRegister2(VERTICAL_DYNAMIXEL_ID,ID_CCW_LIMIT,0);

  //debug: flash LED's on dynamixel to indicate they are communicating
 blink(5);

 
 //roveComm_Begin(192,168,1,52);
 
  
 delay(300);

  int spd = 900;
  
  for(int i = 9; i >=0; i--){
    spd = i*100;
 moveCameraVertically(spd);
 delay(100);
 moveCameraHorizontally(spd);
 delay(1000);
 
 moveCameraVertically(-spd);
 delay(100);
 moveCameraHorizontally(-spd);
 delay(1000);
 
 moveCameraVertically(0);
 delay(100);
 moveCameraHorizontally(0);
 delay(1000);
 
 
 //if(i%2==0)zoomIn();
 //else zoomOut();
 
 
  }

 
 
}

void blink(int num){
  for(int i = 0; i < num; i++){
    setRegister(254,0x19,1);        
    delay(100);
    setRegister(254,0x19,0);        
    delay(100);
  }
}


void loop(){
   blink(2);
}

void roveComm(){

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
  if(moveSpeed<0){
    moveSpeed = abs(moveSpeed)*1023/1000+1024;
  }
  else{
    moveSpeed = moveSpeed*1023/1000;
  }
  
  
  if(moveSpeed<0){
    moveSpeed=0;
  }
  if(moveSpeed>2047){
    moveSpeed=2047;
  }

  setRegister2(HORIZONTAL_DYNAMIXEL_ID,ID_SPEED,moveSpeed);
}

//moveSpeed: -1000 to 1000
void moveCameraVertically(int moveSpeed){
  if(moveSpeed<0){
    moveSpeed = abs(moveSpeed)*1023/1000+1024;
  }
  else{
    moveSpeed = moveSpeed*1023/1000;
  }
  
  
  if(moveSpeed<0){
    moveSpeed=0;
  }
  if(moveSpeed>2047){
    moveSpeed=2047;
  }
  
  setRegister2(VERTICAL_DYNAMIXEL_ID,ID_SPEED,moveSpeed);
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


