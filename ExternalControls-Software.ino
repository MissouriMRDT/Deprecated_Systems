// github version
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

// Dynamixel Channels
#define GIMB1_SER 3 //3
#define GIMB2_SER 2 //2
#define DYN1_SER  5 //5
#define DYN2_SER  7 //7
//-------------------

//Camera pulse lengths (ms)
#define SHORT_SIGNAL 1000
#define MID_SIGNAL 1500
#define LONG_SIGNAL 2000

//Dynamixel ID's
#define HOR_CAM_1  1
#define VERT_CAM_1 2
#define HOR_CAM_2  1
#define VERT_CAM_2 2

//Basestation command ID's
#define ID_CAMERA_COMMAND 1568
#define ID_GIMBAL1_SPEED 1552
#define ID_CAMERA_MENU 1569
#define ID_GIMBAL2_SPEED 1553

#define CARABINER_CONTROL 1616

#define OPEN_DROP_BAY 1584
#define CLOSE_DROP_BAY 1585
#define LED_CHANGE_COLOR 2320

#define GREEN 75
#define BLUE  76
#define RED   77

#define TIMEOUT_TICKS 1000

#define DYNA_BAUD 1000000

// bools for use of gimbals (writing to unused Dynamixels results in program hangs)
#define USE_GIMB1 true
#define USE_GIMB2 true
#define USE_CARABINER true

Dynamixel gimb1_hor, gimb1_vert;
Dynamixel gimb2_hor, gimb2_vert;
Dynamixel carabiner;

const uint16_t CARABINER_OPEN_SPEED = 1000;
const uint16_t CARABINER_CLOSE_SPEED = 1074;

uint16_t dataID = 0;
size_t size = 0;
char data[8];
int counter;

Servo Dropbay[2];

void setup() {
  // begin comms with Monitor
  Serial.begin(9600);
  delay(100);
  // initialize gimbal dynamixels
  if(USE_GIMB1){
    DynamixelInit(&gimb1_hor,  AX, HOR_CAM_1, GIMB1_SER, DYNA_BAUD);
    DynamixelInit(&gimb1_vert, AX, VERT_CAM_1, GIMB1_SER, DYNA_BAUD);
    DynamixelSetMode(gimb1_hor, Wheel);
    DynamixelSetMode(gimb1_vert, Wheel);
    blink(5, gimb1_hor);
    blink(5, gimb1_vert);
 }
  if(USE_GIMB2){
    DynamixelInit(&gimb2_hor,  AX, HOR_CAM_2, GIMB2_SER, DYNA_BAUD);
    DynamixelInit(&gimb2_vert, MX, VERT_CAM_2, GIMB2_SER, DYNA_BAUD);
    DynamixelSetMode(gimb2_hor, Wheel);
    DynamixelSetMode(gimb2_vert, Wheel);
    blink(5, gimb2_hor);
    blink(5, gimb2_vert);
  }

  if (USE_CARABINER){
    DynamixelInit(&carabiner, AX, 3, DYN1_SER, DYNA_BAUD);
    DynamixelSetMode(carabiner, Wheel);
  }

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

  Dropbay[0].write(0);
  Dropbay[1].write(255);

  // Setup LED pins
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  // pulse testing
  //pulse(0,255,0,3);

  delay(100);

  // begin communicating with RED
  roveComm_Begin(192,168,1,134);

  // enable connection LEDs
  Ethernet.enableLinkLed();
  Ethernet.enableActivityLed();

  delay(100);
}

uint8_t* OFF = new uint8_t(0);
uint8_t* ON = new uint8_t(1);
void blink(int num_times, Dynamixel dyn){
  for(int i = 0; i < num_times; i++)
  {
    DynamixelSendWriteCommand(dyn, DYNAMIXEL_LED, 1, ON); // turn on LED
    delay(100);
    DynamixelSendWriteCommand(dyn, DYNAMIXEL_LED, 1, OFF); // turn off LED
    delay(100);
  }
}

int count = 0;
void loop()
{
  // ensure constant connection with RED
  if(roveCommCheck())
  {
    count = 0;
  }
  else
  {
    count++;
    //stop dynamixels if no comms
    if(count > TIMEOUT_TICKS)
    {
      if(USE_GIMB1)
      {
        moveDynamixel(gimb1_hor,  0);
        moveDynamixel(gimb1_vert, 0);
      }
      if(USE_GIMB2)
      {
        moveDynamixel(gimb2_hor,  0);
        moveDynamixel(gimb2_vert, 0);
      }
      if (USE_CARABINER){
        moveDynamixel(carabiner, 0);
      }
    }
    delay(1);
  }
}

boolean roveCommCheck()
{
  roveComm_GetMsg(&dataID, &size, data);
  if(dataID==0)
  {
    return false;
  }
  else
  {
    uint8_t tmp;
    int16_t xSpeed;
    int16_t ySpeed;
    char a[2];

    switch(dataID){
      case ID_GIMBAL1_SPEED:
        if(USE_GIMB1)
        {
          a[0] = data[0];
          a[1] = data[1];
          xSpeed = *(int16_t*)(a);

          a[0] = data[2];
          a[1] = data[3];
          ySpeed = *(int16_t*)(a);

          moveDynamixel(gimb1_hor,  xSpeed);
          moveDynamixel(gimb1_vert, ySpeed);
        }
        break;

      case ID_GIMBAL2_SPEED:
        if(USE_GIMB2)
        {
          a[0] = data[0];
          a[1] = data[1];
          xSpeed = *(int16_t*)(a);

          a[0] = data[2];
          a[1] = data[3];
          ySpeed = *(int16_t*)(a);

          moveDynamixel(gimb2_hor,  xSpeed);
          moveDynamixel(gimb2_vert, ySpeed);
        }
        break;

      case OPEN_DROP_BAY:
        if (data[0] == 0)
          Dropbay[0].write(255);
        else if (data[0] == 1)
          Dropbay[1].write(0);
        break;

      case CLOSE_DROP_BAY:
        if (data[0] == 0)
          Dropbay[0].write(0);
        else if (data[0] == 1)
          Dropbay[1].write(255);
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

      case CARABINER_CONTROL:
        if (USE_CARABINER) {
          if (*(int16_t*)(data) == 0)
            DynamixelSpinWheel(carabiner,0);
          else if (*(int16_t*)(data) > 0)
            DynamixelSpinWheel(carabiner,CARABINER_OPEN_SPEED);
          else if (*(int16_t*)(data) < 0)
            DynamixelSpinWheel(carabiner,CARABINER_CLOSE_SPEED);
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
      case LED_CHANGE_COLOR:
        setLEDColor(data[0], data[1], data[2]);
        break;
    }
    return true;
  }
}

//moveSpeed: -1000 to 1000
void moveDynamixel(Dynamixel dyna, int moveSpeed){
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
  DynamixelSpinWheel(dyna,moveSpeed);
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

void pulse(int r, int g, int b, int times)
{
  for(int j = 0; j < times; j++)
  {
    for(int i = 0; i <= 255; i++)
    {
      setLEDColor(r*i/255.0,g*i/255.0,b*i/255.0);
      delay(5);
    }
    for(int i = 255; i > 0; i--)
    {
      setLEDColor(r*i/255.0,g*i/255.0,b*i/255.0);
      delay(5);
    }
  }
  setLEDColor(0,0,0);
}
void setLEDColor(byte r, byte g, byte b)
{
  analogWrite(RED,  r);
  analogWrite(GREEN,g);
  analogWrite(BLUE, b);
}
void generateSignal(int amt, int pin){
  for(int i = 0; i < 5; i++){
    digitalWrite(pin,1);
    delayMicroseconds(amt);
    digitalWrite(pin,0);
    delayMicroseconds(20000-amt);
  }
}
