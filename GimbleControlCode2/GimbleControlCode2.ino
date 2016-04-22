#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <RoveBoard.h>
#include <RoveEthernet.h>

#include <RoveComm.h>

#include <dyna.h>



//Pin assignments:
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




//Camera pulse lengths (ms)
#define SHORT_SIGNAL 1000
#define MID_SIGNAL 1500
#define LONG_SIGNAL 2000




//Dynamixel ID's
#define HOR_CAM_1 5
#define VERT_CAM_1 4
#define HOR_CAM_2 254
#define VERT_CAM_2 254

//Dynamixel function ID's
#define ID_CW_LIMIT 6
#define ID_CCW_LIMIT 8
#define ID_SPEED 32


//Basestation command ID's
#define ID_CAMERA_COMMAND 1568
#define ID_GIMBAL_SPEED 1552
#define ID_CAMERA_MENU 1569





uint16_t dataID = 0;
size_t size = 0;
char data[8];
int counter;





void setup() {
  

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
  
  roveComm_Begin(192,168,1,134);
  Serial.begin(9600);
  Ethernet.enableLinkLed();
  Ethernet.enableActivityLed();
  delay(100);
  init();//initialize Dynamixel library
  delay(100);

  //set dynamixels to be in continuous rotation mode.
  setRegister2(HOR_CAM_1,ID_CW_LIMIT,0);
  setRegister2(HOR_CAM_2,ID_CCW_LIMIT,0);
  setRegister2(VERT_CAM_1,ID_CW_LIMIT,0);
  setRegister2(VERT_CAM_1,ID_CCW_LIMIT,0);

  //debug: flash LED's on dynamixel to indicate they are communicating
  blink(5);

 
  
 

 
 
}

void blink(int num){
  for(int i = 0; i < num; i++){
    setRegister(254,0x19,1);        
    delay(100);
    setRegister(254,0x19,0);        
    delay(100);
  }
}

int count = 0;
void loop(){
  if(roveCommCheck()) count=0;
  else{
    count++;
    if(count>25){
      moveDynamixel(0,HOR_CAM_1);
      moveDynamixel(0,VERT_CAM_1);
    }
    delay(5);
  }
  delay(1);
}

boolean roveCommCheck(){
  
  roveComm_GetMsg(&dataID, &size, data);
  if(dataID==0) return false;
  
  uint8_t tmp;
  int16_t xSpeed;
  int16_t ySpeed;
  
  switch(dataID){
    case ID_GIMBAL_SPEED:
      
      char a[2];
      
      a[0] = data[0];
      a[1] = data[1];
      xSpeed = *(int16_t*)(a);
      
      a[0] = data[2];
      a[1] = data[3];
      ySpeed = *(int16_t*)(a);
      
      
      //xSpeed = 900;
      //ySpeed = 0;
      
      moveDynamixel(xSpeed,HOR_CAM_1);
      moveDynamixel(ySpeed,VERT_CAM_1);
      
      
      
    break;
    
    case ID_CAMERA_MENU:
      tmp = *(uint8_t*)(data);
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
      tmp = *(uint8_t*)(data);
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
  
  return true;
}





//moveSpeed: -1000 to 1000
void moveDynamixel(int moveSpeed, int dynaID){
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

  setRegister2(dynaID,ID_SPEED,moveSpeed);
  
  delay(50);
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


