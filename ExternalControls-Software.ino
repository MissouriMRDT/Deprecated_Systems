#include <Servo.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <RoveBoard.h>
#include <RoveEthernet.h>

#include <RoveComm.h>

#include <BischoffDyna.h>



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


//Servo pins
#define P00 PK_0
#define P01 PK_1
#define P02 PK_2
#define P03 PK_3
#define P10 PP_0
//#define P11 PP_1
#define P12 PN_4
#define P13 PN_5
#define P20 PL_0
//#define P21 PL_1
#define P22 PL_2
#define P23 PL_3
#define P30 PF_1
#define P31 PF_2
#define P32 PF_3
#define P33 PH_2


//Camera pulse lengths (ms)
#define SHORT_SIGNAL 1000
#define MID_SIGNAL 1500
#define LONG_SIGNAL 2000




//Dynamixel ID's
#define HOR_CAM_1 5
#define VERT_CAM_1 4
#define HOR_CAM_2 11
#define VERT_CAM_2 10

//Dynamixel function ID's
#define ID_CW_LIMIT 6
#define ID_CCW_LIMIT 8
#define ID_SPEED 32


//Basestation command ID's
#define ID_CAMERA_COMMAND 1568
#define ID_GIMBAL_SPEED 1552
#define ID_CAMERA_MENU 1569
#define ID_DROP_BAY 1584

#define ID_CAMERA_COMMAND_2 1570
#define ID_GIMBAL_SPEED_2 1553
#define ID_CAMERA_MENU_2 1571

#define ID_CAMERA_MUXING 1600

#define DROPBAY_ANGLE_OPEN 170


uint16_t dataID = 0;
size_t size = 0;
char data[8];
int counter;


Servo servo0;

Servo servoMux1;
Servo servoMux2;

  


void setup() {
  

  pinMode(PWM0,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(PWM3,OUTPUT);
  pinMode(EN_12V,OUTPUT);
  
  
  pinMode(P00,OUTPUT);
  pinMode(P01,OUTPUT);
  pinMode(P02,OUTPUT);
  pinMode(P03,OUTPUT);
  //digitalWrite(P00,0);
  //digitalWrite(P01,0);
  //digitalWrite(P02,0);
  //digitalWrite(P03,0);
  
  digitalWrite(PWM0,0);
  digitalWrite(PWM1,0);
  digitalWrite(PWM2,0);
  digitalWrite(PWM3,0);
  digitalWrite(EN_12V,1);
  
  
  
  
  

  
  delay(100);
  Serial7.begin(1000000);
  roveComm_Begin(192,168,1,134);
  Serial.begin(9600);
  Ethernet.enableLinkLed();
  Ethernet.enableActivityLed();
  delay(100);
  //init();//initialize Dynamixel library
  delay(100);

  //set dynamixels to be in continuous rotation mode.
  setRegister2(HOR_CAM_1,ID_CW_LIMIT,0);
  setRegister2(HOR_CAM_1,ID_CCW_LIMIT,0);
  setRegister2(VERT_CAM_1,ID_CW_LIMIT,0);
  setRegister2(VERT_CAM_1,ID_CCW_LIMIT,0);


  setRegister2(HOR_CAM_2,ID_CW_LIMIT,0);
  setRegister2(HOR_CAM_2,ID_CCW_LIMIT,0);
  setRegister2(VERT_CAM_2,ID_CW_LIMIT,0);
  setRegister2(VERT_CAM_2,ID_CCW_LIMIT,0);
  
  
  //debug: flash LED's on dynamixel to indicate they are communicating
  blink(5);

 
  

      moveDynamixel(-100,HOR_CAM_2);
      delay(100);
      moveDynamixel(0,HOR_CAM_2);
      delay(100);
      moveDynamixel(100,HOR_CAM_2);
      delay(100);
      moveDynamixel(0,HOR_CAM_2);
      delay(100);
      moveDynamixel(-100,VERT_CAM_2);
      delay(100);
      moveDynamixel(0,VERT_CAM_2);
      delay(100);
      moveDynamixel(100,VERT_CAM_2);
      delay(100);
      moveDynamixel(0,VERT_CAM_2);
      delay(100);
      
      
       blink(5);
       
        //JUDAH COMMENT Mux support in the style of Bischoff : Each pin controls three states PP_1 = Camera 1, 2. or SecondMux, PL_1 = Camera 3, 4, 5
       servoMux1.attach(PP_1,1000, 2000);
       servoMux2.attach(PL_1,1000, 2000);

 
 
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
    if(count>1000){
      moveDynamixel(0,HOR_CAM_1);
      moveDynamixel(0,VERT_CAM_1);
      moveDynamixel(0,HOR_CAM_2);
      moveDynamixel(0,VERT_CAM_2);
    }
    delay(1);
  }
  //delay(1);
}

boolean roveCommCheck(){
  
  roveComm_GetMsg(&dataID, &size, data);
  if(dataID==0) return false;
  
  uint8_t tmp;
  int16_t xSpeed;
  int16_t ySpeed;
  char a[2];
  
  switch(dataID){
    case ID_GIMBAL_SPEED:
      
      
      
      a[0] = data[0];
      a[1] = data[1];
      xSpeed = *(int16_t*)(a);
      
      a[0] = data[2];
      a[1] = data[3];
      ySpeed = *(int16_t*)(a);
      
      
      //xSpeed = 900;
      //ySpeed = 0;
      
      moveDynamixel(xSpeed,HOR_CAM_1);
      moveDynamixel(-ySpeed,VERT_CAM_1);
      
      
      
    break;
    
    case ID_GIMBAL_SPEED_2:
      
      
      
      a[0] = data[0];
      a[1] = data[1];
      xSpeed = *(int16_t*)(a);
      
      a[0] = data[2];
      a[1] = data[3];
      ySpeed = *(int16_t*)(a);
      
      
      //xSpeed = 900;
      //ySpeed = 0;
      
      moveDynamixel(xSpeed,HOR_CAM_2);
      moveDynamixel(-ySpeed,VERT_CAM_2);
      
      
      
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
    
    
    
    
    
    
    case ID_CAMERA_MENU_2:
      tmp = *(uint8_t*)(data);
      if(tmp==0){
        toggleMenu2();
      }
      else if(tmp==1){
        navigateMenuLeft2();
      }
      else if(tmp==2){
        navigateMenuRight2();
      }
      else if(tmp==3){
        navigateMenuUp2();
      }
      else if(tmp==4){
        navigateMenuDown2();
      }
    break;
    
    case ID_CAMERA_COMMAND_2:
      tmp = *(uint8_t*)(data);
      if(tmp==0){
        stopZoomAndFocus2();
      }
      else if(tmp==1){
        zoomIn2();
      }
      else if(tmp==2){
        zoomOut2();
      }
      else if(tmp==3){
        focusIn2();
      }
      else if(tmp==4){
        focusOut2();
      }
    break;
    
    
    //JUDAH COMMENT Mux support in the style of Bischoff : Each pin controls three states PP_1 = Camera 1, 2. or SecondMux, PL_1 = Camera 3, 4, 5
    case ID_CAMERA_MUXING:
    tmp = *(uint8_t*)(data);
      if(tmp==0){
        servoMux1.write(1000);
        delay(1000);
      }
      else if(tmp==1){
        servoMux1.write(1500);
        delay(1000);
      }
      //Mux the daisy chain to the second mux
      else if(tmp==2 || tmp==3 || tmp==3){
        servoMux1.write(2000);
        delay(1000);
      }
      
      if(tmp==2){
        servoMux2.write(1000);
        delay(1000);
      }
      if(tmp==3){
        servoMux2.write(1500);
        delay(1000);
      }
      if(tmp==4){
        servoMux2.write(2000);
        delay(1000);
      }

    break;
    
    
    case ID_DROP_BAY:
      tmp = *(uint8_t*)(data);
      openDropBay(tmp);
    break;
    
   
    
  }
  
  return true;
}


void openDropBay(int bay){
  if(bay==0){
    unsigned long time = millis();
    while(millis()<time+1000){
      servo0.attach(P00);
      servo0.write(DROPBAY_ANGLE_OPEN);
      delay(1000);
      servo0.detach();
    }
  }
  if(bay==1){
    unsigned long time = millis();
    while(millis()<time+1000){
      servo0.attach(P10);
      servo0.write(DROPBAY_ANGLE_OPEN);
      delay(1000);
      servo0.detach();
    }
  }
  if(bay==2){
    unsigned long time = millis();
    while(millis()<time+1000){
      servo0.attach(P20);
      servo0.write(DROPBAY_ANGLE_OPEN);
      delay(1000);
      servo0.detach();
    }
  }
  if(bay==3){
    unsigned long time = millis();
    while(millis()<time+1000){
      servo0.attach(P30);
      servo0.write(DROPBAY_ANGLE_OPEN);
      delay(1000);
      servo0.detach();
    }
  }
}



//moveSpeed: -1000 to 1000
void moveDynamixel(int moveSpeed, int dynaID){
  if(moveSpeed<0){
    moveSpeed = abs(moveSpeed)*1023/1000;
  }
  else{
    moveSpeed = moveSpeed*1023/1000+1024;
  }
  
  
  if(moveSpeed<0){
    moveSpeed=0;
  }
  if(moveSpeed>2047){
    moveSpeed=2047;
  }

  setRegister2(dynaID,ID_SPEED,moveSpeed);
  
  
}


boolean active = false;

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










void zoomIn2(){
  active=true;
  generateSignal(LONG_SIGNAL,PWM0_CAM2);
}
void zoomOut2(){
  active=true;
  generateSignal(SHORT_SIGNAL,PWM0_CAM2);
}
void focusIn2(){
  active=true;
  generateSignal(LONG_SIGNAL,PWM1_CAM2);
}
void focusOut2(){
  active=true;
  generateSignal(SHORT_SIGNAL,PWM1_CAM2);
}
void stopZoomAndFocus2(){
  if(!active)return;
  active=false;
  generateSignal(MID_SIGNAL,PWM0_CAM2);
  generateSignal(MID_SIGNAL,PWM1_CAM2);
}







void toggleMenu2(){
  generateSignal(MID_SIGNAL,PWM2_CAM2);
  generateSignal(LONG_SIGNAL,PWM2_CAM2);
}
void navigateMenuLeft2(){
  generateSignal(MID_SIGNAL,PWM1_CAM2);
  generateSignal(SHORT_SIGNAL,PWM1_CAM2);
}
void navigateMenuRight2(){
  generateSignal(MID_SIGNAL,PWM1_CAM2);
  generateSignal(LONG_SIGNAL,PWM1_CAM2);
}
void navigateMenuUp2(){
  generateSignal(MID_SIGNAL,PWM0_CAM2);
  generateSignal(LONG_SIGNAL,PWM0_CAM2);
}
void navigateMenuDown2(){
  generateSignal(MID_SIGNAL,PWM0_CAM2);
  generateSignal(SHORT_SIGNAL,PWM0_CAM2);
}






void generateSignal(int amt, int pin){
  for(int i = 0; i < 5; i++){
    digitalWrite(pin,1);
    delayMicroseconds(amt);
    digitalWrite(pin,0);
    delayMicroseconds(20000-amt);
  }
}
