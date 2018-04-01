#include "EasyTransfer.h"

const int PWM1 = 3;  //R
const int PWM2 = 5;  //G
const int PWM3 = 6;  //B
const int PWM4 = 9;  //1
const int PWM5 = 10; //2
const int PWM6 = 11; //3
const int D1 = 7;    //5
const int D2 = 8;    //4

int lev1 = 0;
int lev2 = 0;
int lev3 = 0;
int lev4 = 0;
int lev5 = 0;
int lev6 = 0;

#define MAX_LOG_LENGTH 100

EasyTransfer ETsend;
EasyTransfer ETreceive;

struct SEND_DATA_STRUCTURE{
  char log_data[MAX_LOG_LENGTH];
};

struct RECEIVE_DATA_STRUCTURE{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t pwm1;
  uint8_t pwm2;
  uint8_t pwm3;
  uint8_t d1;
  uint8_t d2;
};

SEND_DATA_STRUCTURE sendData;
RECEIVE_DATA_STRUCTURE receiveData;

boolean DEBUG_MODE = false;

void setup() {
  if(DEBUG_MODE)
    Serial.begin(9600);
  else
    Serial.begin(115200);
    
  resetStruct();
  sendData.log_data[0]='\0';
  ETsend.begin(details(sendData), &Serial);
  ETreceive.begin(details(receiveData), &Serial);
  
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);
  pinMode(PWM4, OUTPUT);
  pinMode(PWM5, OUTPUT);
  pinMode(PWM6, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
}

void loop() {
  if(!DEBUG_MODE && ETreceive.receiveData()){ 
    if(receiveData.red=>0)
      analogWrite(PWM1, receiveData.red);
    if(receiveData.green=>0)
      analogWrite(PWM2, receiveData.green);
    if(receiveData.blue=>0)
      analogWrite(PWM3, receiveData.blue);
    if(receiveData.pwm1=>0)
      analogWrite(PWM4, receiveData.pwm1);
    if(receiveData.pwm2=>0)
      analogWrite(PWM5, receiveData.pwm2);
    if(receiveData.pwm3=>0)
      analogWrite(PWM6, receiveData.pwm3);
    if(receiveData.d1)
      digitalWrite(D1, receiveData.d1);
    if(receiveData.d2)
      digitalWrite(D2, receiveData.d2);
  }
  else if(DEBUG_MODE && Serial.available()>0){
    char x = Serial.read();
    switch (x) {
      case 'q':
        if (lev1<254)
          lev1++;
        analogWrite(PWM1, lev1);
        break;
      case 'a':
        if (lev1>0)
          lev1--;
        analogWrite(PWM1, lev1);
        break;
      case 'w':
        if (lev2<254)
          lev2++;
        analogWrite(PWM2, lev2);
        break;
      case 's':
        if (lev2>0)
          lev2--;
        analogWrite(PWM2, lev2);
        break;
      case 'e':
        if (lev3<254)
          lev3++;
        analogWrite(PWM3, lev3);
        break;
      case 'd':
        if (lev3>0)
          lev3--;
        analogWrite(PWM3, lev3);
        break;
      case 'r':
        if (lev4<254)
          lev4++;
        analogWrite(PWM4, lev4);
        break;
      case 'f':
        if (lev4>0)
          lev4--;
        analogWrite(PWM4, lev4);
        break;
      case 't':
        if (lev5<254)
          lev5++;
        analogWrite(PWM5, lev5);
        break;
      case 'g':
        if (lev5>0)
          lev5--;
        analogWrite(PWM5, lev5);
        break;
      case 'y':
        if (lev6<254)
          lev6++;
        analogWrite(PWM6, lev6);
        break;
      case 'h':
        if (lev6>0)
          lev6--;
        analogWrite(PWM6, lev6);
        break;
      case 'u':
        digitalWrite(D2, HIGH);
        break;
      case 'j':
        digitalWrite(D2, LOW);
        break;
      case 'i':
        digitalWrite(D1, HIGH);
        break;
      case 'k':
        digitalWrite(D1, LOW);
        break;  
    }  
  }  
}

void resetStruct(){
  receiveData.red = 0;
  receiveData.green = 0;
  receiveData.blue = 0;
  receiveData.pwm1 = 0;
  receiveData.pwm2 = 0;
  receiveData.pwm3 = 0;
  receiveData.d1 = 0;
  receiveData.d2 = 0;
}
