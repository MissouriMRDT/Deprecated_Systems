/*MRDT 2014 BPS Software v0.2
Written by Lukas Müller
E-mail:lkm8c3@mail.mst.edu
*/

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
const uint8_t BUTTON = 4;//Charger Button PIN
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
int tempmax = 82; // Max ambient temperature 40C

//Battery Constraints to restart
int vmaxR = 430; //Max cell voltage 4.2V
int vminR = 350; //Min cell voltage 3.3V
int tempmaxR = 62; // Max ambient temperature 30C

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

Serial.begin(9600);

}

void loop(){
  estop=analogRead(4); //If estop button is pressed, turn of battery and do nothing else
  if(estop>512){
   PORTB = PORTB & B11111101; 
   Serial.println("E-Stop");
  }
  else{
  if( fault == false){ //if battery is ok check if it is ok
    PORTB = PORTB | B00000010;
  batterydata();
   if( B0F>10 || B1F>10 || B2F>10 || B3F>10 || B4F>10 || B5F>10 || B6F>10 || CF>10){// if fault is measured to often turn battery off
     PORTB = PORTB & B11111101;
     Serial.println("Sustained Battery Fault");
     fault = true;
     ctn = 0;
   }
   ctn++;
   if(ctn>100){
    B0F = 0;
    B1F = 0;
    B2F = 0;
    B3F = 0;
    B4F = 0;
    B5F = 0;
    B6F = 0;
    CF = 0;
    ctn = 0;
   }}
   else{
     if(ctn == 1){
      //delay(10000); 
     }
     batteryretry();
     ctn++;
    if(ctn>=1000){ // if fault is cleared turn it back on
    if( B0R>50 || B1R>50 || B2R>50 || B3R>50 || B4R>50 || B5R>50 || B6R>50){
     Serial.println("Fault not cleared");
    }
    else{
     Serial.println("Battery On");
     fault = false;
     PORTB = PORTB | B00000010;
      B0F = 0;
      B1F = 0;
      B2F = 0;
      B3F = 0;
      B4F = 0;
      B5F = 0;
      B6F = 0;
      CF = 0;
    }  
 ctn=0;
 B0R=0;
 B1R=0;
 B2R=0;
 B3R=0;
 B4R=0;
 B5R=0;
 B6R=0;
    }}
  } //Print all the battery states as serial data
Serial.print("{Vb0,T,"); 
Serial.print(VB0);
Serial.println("}");
Serial.print("{Vb1,T,"); 
Serial.print(VB1);
Serial.println("}");
Serial.print("{Vb2,T,"); 
Serial.print(VB2);
Serial.println("}");
Serial.print("{Vb3,T,"); 
Serial.print(VB3);
Serial.println("}");
Serial.print("{Vb4,T,"); 
Serial.print(VB4);
Serial.println("}");
Serial.print("{Vb5,T,"); 
Serial.print(VB5);
Serial.println("}");
Serial.print("{Vb6,T,"); 
Serial.print(VB6);
Serial.println("}");    
Serial.print("{Tb0,T,"); 
Serial.print(TB0);
Serial.println("}");
Serial.print("{Tb1,T,"); 
Serial.print(TB1);
Serial.println("}");
Serial.print("{Tb2,T,"); 
Serial.print(TB2);
Serial.println("}");
Serial.print("{Tb3,T,"); 
Serial.print(TB3);
Serial.println("}");
Serial.print("{Tb4,T,"); 
Serial.print(TB4);
Serial.println("}");
Serial.print("{Tb5,T,"); 
Serial.print(TB5);
Serial.println("}");
Serial.print("{Tb6,T,"); 
Serial.print(TB6);
Serial.println("}");
Serial.print("{MC,T,"); 
Serial.print(MC);
Serial.println("}");
    
    
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
}

void batteryretry(){// this checks the battery to see if they are in a safe state again
  switchport(0);
  VB0=long_adc(VOLTS);
  TB0=long_adc(TEMP);
  switchport(1);
  if ( VB0 > vmaxR || TB0 > tempmaxR || VB0 < vminR){
    B0R++;
  }
  VB1=long_adc(VOLTS);
  TB1=long_adc(TEMP);
  switchport(2);
  if ( VB1 > vmaxR || TB1 > tempmaxR || VB1 < vminR){
    B1R++;
  }
  VB2=long_adc(VOLTS);
  TB2=long_adc(TEMP);
  switchport(3);
  if ( VB2 > vmaxR || TB2 > tempmaxR || VB2 < vminR){
    B2R++;
  }
  VB3=long_adc(VOLTS);
  TB3=long_adc(TEMP);
  switchport(4);
  if ( VB3 > vmaxR || TB3 > tempmaxR || VB3 < vminR){
    B3R++;
  }
  VB4=long_adc(VOLTS);
  TB4=long_adc(TEMP);
  switchport(5);
  if ( VB4 > vmaxR || TB4 > 1024 || VB4 < vminR){
    B4R++;
  }
  VB5=long_adc(VOLTS);
  TB5=long_adc(TEMP);
  switchport(6);
  if ( VB5 > vmaxR || TB5 > tempmaxR || VB5 < vminR){
    B5R++;
  }
  VB6=long_adc(VOLTS);
  TB6=long_adc(TEMP);
  if ( VB6 > vmaxR || TB6 > tempmaxR || VB6 < vminR){
    B6R++;
  }
 }