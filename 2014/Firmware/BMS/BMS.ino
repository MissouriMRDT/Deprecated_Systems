#include <EasyTransfer.h>

EasyTransfer ET;

struct SEND_DATA
{
  int volt0;
  int temp0;
  int volt1;
  int temp1;
  int volt2;
  int temp2;
  int volt3;
  int temp3;
  int volt4;
  int temp4;
  int volt5;
  int temp5;
  int volt6;
  int temp6;
  int main_bat_cur;
  int main_bat_volt;
};
SEND_DATA batteryData;

//Setting up port names
const uint8_t A = 2;//Multiplexer Selector A
const uint8_t B = 3;//Multiplexer Selector B
const uint8_t C = 4;//Multiplexer Selector C
const uint8_t GB1 = 6;//Battery 1 Balance control
const uint8_t GB2 = 11;//Battery 2 Balance control
const uint8_t GB3 = 7;//Battery 3 Balance control
const uint8_t GB4 = 13;//Battery 4 Balance control
const uint8_t GB5 = 5;//Battery 5 Balance control
const uint8_t GB6 = 12;//Battery 6 Balance control
const uint8_t GB7 = 8;//Battery 7 Balance control
const uint8_t MV_PIN = 0;//MAIN Bus Voltage ADC pin
const uint8_t MC_PIN = 1;//MAIN Battery Current ADC pin
const uint8_t CC_PIN = 2;//Charger Current Measurment pin
const uint8_t VOLTS = 3;//Voltage measurment from multiplexer
const uint8_t BUTTON = 4;//E-Stop Button
const uint8_t TEMP = 5;//Temperature mesurment from multiplexer
const uint8_t MAIN = 9;//Main Battery Control
const uint8_t ChargerPWM = 10;//PWM pin for charger

//Setting up battery information memeory
int VB0 = 0; // Battery 1 Voltage
int VB1 = 0; // Battery 2 Voltage
int VB2 = 0; // Battery 3 Voltage
int VB3 = 0; // Battery 4 Voltage
int VB4 = 0; // Battery 5 Voltage
int VB5 = 0; // Battery 6 Voltage
int VB6 = 0; // Battery 7 Voltage
int TB0 = 0; // Battery 1 Temp
int TB1 = 0; // Battery 2 Temp
int TB2 = 0; // Battery 3 Temp
int TB3 = 0; // Battery 4 Temp
int TB4 = 0; // Battery 5 Temp
int TB5 = 0; // Battery 6 Temp
int TB6 = 0; // Battery 7 Temp
int MC = 0;//Battery Main Current
int MV = 0;//Battery Main Voltage
int CC = 0;//Chareger Current
int CV = 0;//Charger Voltage
const int AVG_NUM = 50;

//Program variables:
int B0F=0;
int B1F=0;
int B2F=0;
int B3F=0;
int B4F=0;
int B5F=0;
int B6F=0;
int CF=0;
int ctn=0;
int B0R=0;
int B1R=0;
int B2R=0;
int B3R=0;
int B4R=0;
int B5R=0;
int B6R=0;
boolean fault = false;

//Battery Safety Variable
int vmax = 430; //Max cell voltage 4.2V
int vmin = 297; //Min cell voltage 2.85V
int cmax = 1000 ; //Max current
int tempmax = 102; // Max ambient temperature 50C

//Battery Constraints to restart
int vmaxR = 425; //Max cell voltage 4.2V
int vminR = 350; //Min cell voltage 3.3V
int tempmaxR = 92; // Max ambient temperature 45C

//Battery Charger Constants
int vcharge = 363;
int icharge = 600;
int vkp=64;
int vki=32;
int ikp=64;
int iki=32;
int PWM_Min=0;
int PWM_Max=200;
//Battery Charger Program Variables
int vset = 0;
int verror = 0;
unsigned int vintegral = 0;
int iset=100;
int ierror=0;
unsigned int iintegral = 0;
int pwm = 0;
boolean CVchargin = false;

int estop = 0;


void setup(){

pinMode(MAIN, OUTPUT);
pinMode(ChargerPWM, OUTPUT);
pinMode(A, OUTPUT);
pinMode(B, OUTPUT);
pinMode(C, OUTPUT);
pinMode(GB1, OUTPUT);
pinMode(GB2, OUTPUT);
pinMode(GB3, OUTPUT);
pinMode(GB4, OUTPUT);
pinMode(GB5, OUTPUT);
pinMode(GB6, OUTPUT);
pinMode(GB7, OUTPUT);
pinMode(A4, INPUT_PULLUP);
digitalWrite(MAIN, LOW);
digitalWrite(ChargerPWM, LOW);
digitalWrite(A, LOW);
digitalWrite(B, LOW);
digitalWrite(C, LOW);
digitalWrite(GB1, LOW);
digitalWrite(GB2, LOW);
digitalWrite(GB3, LOW);
digitalWrite(GB4, LOW);
digitalWrite(GB5, LOW);
digitalWrite(GB6, LOW);
digitalWrite(GB7, LOW);

Serial.begin(115200);
ET.begin(details(batteryData),&Serial);


//Setup Timer 1 for Charging Algorithm
TCCR1A=0;
TCCR1B=0;
ICR1 = 250;
OCR1B = 0;
TCCR1A |= (1 << WGM11);
TCCR1B |= (1 << WGM12)|(1 << WGM13);
//set Fast PWM mode using ICR1 as TOP
TCCR1B |= (1 << CS10);
TCCR1A |= (1 << COM1B1);
//Start PWM with zero duty cycle
}

void loop(){
  
  ////////////////////
  // EStop
  ////////////////////
  estop=analogRead(4);
  if(estop>512){
   PORTB = PORTB & B11111101; 

   
   fault = false;

  }
  
  /////////////////////
  // Charging
  /////////////////////
  else{
  switchport(7);
  CV=analogRead(VOLTS);
  if(CV > vcharge)
  { 
    Serial.println("Charging");
    PORTB = PORTB | B00000010;
    batterydata();
    senddata();
    while(check() && CV > vcharge)
    { 
      CC=(508-analogRead(CC_PIN));
      Serial.println(CC);
      ierror=iset-CC;
      iintegral+=ierror;
      iintegral=constrain(iintegral,0,65000);
      pwm = ierror/ikp+iintegral/iki;
      pwm = constrain(pwm,PWM_Min, PWM_Max);
      OCR1B = pwm;
      
      batterydata();
      switchport(7);
      CV=analogRead(VOLTS);
      senddata();
      Serial.println("Updating PWM");
      Serial.println(pwm);    
    }
    iintegral = 0;
    OCR1B = 0;
    B0F = 0;
    B1F = 0;
    B2F = 0;
    B3F = 0;
    B4F = 0;
    B5F = 0;
    B6F = 0;
    CF = 0;
    ctn = 0;
    Serial.println("Done Charging");
  }
  batterydata();
  senddata();
  fault = false;
  PORTB = PORTB | B00000010; 
 }
}
//This Function reads the average from a port
int long_adc(int channel){ 
    unsigned int sum = 0;
int temp;
 int i;
  for (i=0; i<AVG_NUM; i++) {            // loop through reading raw adc values AVG_NUM number of times  
    temp = analogRead(channel);          // read the input pin  
    sum += temp;                        // store sum for averaging  
 }
  return(sum / AVG_NUM);                // divide sum by AVG_NUM to get average and return it
}

//This Function changes between different batteries
void switchport(int port){
  switch (port){
    case 0:
    PORTD = PORTD & B11100011;
    break;
    case 1:
    PORTD = PORTD & B11100011;
    PORTD = PORTD | B00000100;
    break;
    case 2:
    PORTD = PORTD & B11100011;
    PORTD = PORTD | B00001000;
    break;
    case 3:
    PORTD = PORTD & B11100011;
    PORTD = PORTD | B00001100;
    break;
    case 4:
    PORTD = PORTD & B11100011;
    PORTD = PORTD | B00010000;
    break;
    case 5:
    PORTD = PORTD & B11100011;
    PORTD = PORTD | B00010100;
    break;
    case 6:
    PORTD = PORTD & B11100011;
    PORTD = PORTD | B00011000;
    break;
    case 7:
    PORTD = PORTD & B11100011;
    PORTD = PORTD | B00011100;
    break;
  }
}

//Function that updates the battery measurments & checks for faults
void batterydata(){
  switchport(0);
  VB0=long_adc(VOLTS);
  TB0=long_adc(TEMP);
  switchport(1);
  if ( VB0 > vmax || TB0 > tempmax || VB0 < vmin){
    B0F++;
  }
  VB1=long_adc(VOLTS);
  TB1=long_adc(TEMP);
  switchport(2);
  if ( VB1 > vmax || TB1 > tempmax || VB1 < vmin){
    B1F++;
  }
  VB2=long_adc(VOLTS);
  TB2=long_adc(TEMP);
  switchport(3);
  if ( VB2 > vmax || TB2 > tempmax || VB2 < vmin){
    B2F++;
  }
  VB3=long_adc(VOLTS);
  TB3=long_adc(TEMP);
  switchport(4);
  if ( VB3 > vmax || TB3 > tempmax || VB3 < vmin){
    B3F++;
  }
  VB4=long_adc(VOLTS);
  TB4=long_adc(TEMP);
  switchport(5);
  if ( VB4 > vmax || TB4 > 1024 || VB4 < vmin){
    B4F++;
  }
  VB5=long_adc(VOLTS);
  TB5=long_adc(TEMP);
  switchport(6);
  if ( VB5 > vmax || TB5 > tempmax || VB5 < vmin){
    B5F++;
  }
  VB6=long_adc(VOLTS);
  TB6=long_adc(TEMP);
  if ( VB6 > vmax || TB6 > tempmax || VB6 < vmin){
    B6F++;
  }
  MC=long_adc(MC_PIN);
  if(MC > cmax){
   CF++; 
  }
  MV=long_adc(MV_PIN);
}

void updatecharger(){
CC=long_adc(CC_PIN);
MV=long_adc(MV_PIN);
switch (CVchargin){
    case(true):
    verror=vset-MV;
    vintegral+=verror;
    vintegral=constrain(vintegral,0,7680);
    iset = verror/vkp+vintegral/vki;
    break;
    case(false):
    iset=icharge;
    break;   
  }
ierror=iset-CC;
iintegral+=ierror;
iintegral=constrain(iintegral,0,65000);
pwm = ierror/ikp+iintegral/iki;
pwm = constrain(pwm,PWM_Min, PWM_Max);
OCR1B = pwm;  
}

bool check()
{
  if ( VB0 > vmaxR || TB0 > tempmaxR || VB1 > vmaxR || TB1 > tempmaxR ||VB2 > vmaxR || TB2 > tempmaxR ||VB3 > vmaxR || TB3 > tempmaxR ||VB4 > vmaxR || TB4 > 1024 ||VB5 > vmaxR || TB5 > tempmaxR ||VB6 > vmaxR || TB6 > tempmaxR)
  {
    return false;
  }
  else{
    return true;
  }
}

void senddata()
{
  batteryData.volt0 = VB0;
  batteryData.temp0 = TB0;
  batteryData.volt1 = VB1;
  batteryData.temp1 = TB1;
  batteryData.volt2 = VB2;
  batteryData.temp2 = TB2;
  batteryData.volt3 = VB3;
  batteryData.temp3 = TB3;
  batteryData.volt4 = VB4;
  batteryData.temp4 = TB4;
  batteryData.volt5 = VB5;
  batteryData.temp5 = TB5;
  batteryData.volt6 = VB6;
  batteryData.temp6 = TB6;
  batteryData.main_bat_cur = MC;
  batteryData.main_bat_volt = MV;
  
  ET.sendData();
}
