/*******************
MRDT 2015 Drill
Mike Miles
*******************/

/*******************
Pinout
Drill Board         32u4
unused  unused      PD6(D12)      PD4(D4)
unused  unused      PD7(D6)       PD5
unused  TX_0        PB4(D8)       PD3(D1)(TX)
IS      RX_0        PB5(D9)       PD2(D0)(RX)
IN1     unused      PB6(D10)(IN1) PD1(D2)
IN2     unused      PC6(D5)(IN2)  PD0(D3)
INH     unused      PC7(D13)(INH) RST
unused  N$12        PE2           PB7(D11)
unused  N$11        PF7(A0)       MISO
unused  N$10        PF6(A1)       MOSI
unused  N$9         PF5(A2)       SCK
unused  N$8         PF4(A3)       PB0
unused  N$7         PF1(A4)       PE6(D7)
unused  3.3V        PF0(A5)       VCC
unused  GND         AREF          GND
GND     unused      GND           VBUS
*****************/

#include <SoftwareSerial.h>

const int pin_M1EN = 6;
const int pin_M1INA = 2;
const int pin_M1INB = 4;
const int pin_M1PWM = 9;
const int pin_M1CS = A0;

SoftwareSerial moboSerial(0, 1); // (Rx, Tx)

const char STOP = 0x00;
const char FORW = 0x01;
const char REV = 0x02;

char motorCmd = STOP;
bool motorCmd_M1EN = 0;
bool motorCmd_M1INA = 0;
bool motorCmd_M1INB = 0;
bool motorCmd_M1PWM = 0;

void setup() {
  // Serial with xbee
  Serial.begin(9600);
  moboSerial.begin(57600);
  
  // config motor driver select pins
  pinMode(pin_M1EN, OUTPUT);
  pinMode(pin_M1INA, OUTPUT);
  pinMode(pin_M1INB, OUTPUT);
  pinMode(pin_M1PWM, OUTPUT);
  pinMode(pin_M1CS, INPUT);
}

void loop() {
  // read in command from xbee
  if(moboSerial.available() > 0){
    motorCmd = moboSerial.read();
    Serial.println(motorCmd, HEX);
  }
  
  // decide how to operate drill
  if(motorCmd == FORW){ // drill forward
    Serial.println("FORWARD");
    motorCmd_M1EN = 1;
    motorCmd_M1INA = 1;
    motorCmd_M1INB = 0;
    motorCmd_M1PWM = 1;
    
  }
  else if(motorCmd == REV){ // drill reverse
    Serial.println("REVERSE");
    motorCmd_M1EN = 1;
    motorCmd_M1INA = 0;
    motorCmd_M1INB = 1;
    motorCmd_M1PWM = 1;
  }
  else{ // drill stop or bad transmission
    Serial.println("STOP");
    motorCmd = STOP;
    motorCmd_M1EN = 1;
    motorCmd_M1INA = 0;
    motorCmd_M1INB = 0; 
    motorCmd_M1PWM = 0;
  }
  
  digitalWrite(pin_M1EN, motorCmd_M1EN);
  digitalWrite(pin_M1INA, motorCmd_M1INA);
  digitalWrite(pin_M1INB, motorCmd_M1INB);
  digitalWrite(pin_M1PWM, motorCmd_M1PWM);
  
//  Serial.print(motorCmd_INH); 
//  Serial.print(" "); 
//  Serial.print(motorCmd_IN1);
//  Serial.print(" ");
//  Serial.println(motorCmd_IN2);
  
  delay(20);
}
