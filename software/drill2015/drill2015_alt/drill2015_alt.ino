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

SoftwareSerial ser(0, 1); // (Rx, Tx)

const char STOP = 0x30;
const char FORW = 0x31;
const char REV = 0x32;

char cmd = STOP;
bool cmd_M1EN = 0;
bool cmd_M1INA = 0;
bool cmd_M1INB = 0;
bool cmd_M1PWM = 0;

void setup() {
  // serial with xbee
  Serial.begin(9600);
  ser.begin(9600);
  
  // config motor driver select pins
  pinMode(pin_M1EN, OUTPUT);
  pinMode(pin_M1INA, OUTPUT);
  pinMode(pin_M1INB, OUTPUT);
  pinMode(pin_M1PWM, OUTPUT);
  pinMode(pin_M1CS, INPUT);
}

void loop() {
  // read in command from xbee
  if(ser.available() > 0){
    cmd = ser.read();
  }
  
  // decide how to operate drill
  if(cmd == FORW){ // drill forward
    Serial.println("FORWARD");
    cmd_M1EN = 1;
    cmd_M1INA = 1;
    cmd_M1INB = 0;
    cmd_M1PWM = 1;
    
  }
  else if(cmd == REV){ // drill reverse
    Serial.println("REVERSE");
    cmd_M1EN = 1;
    cmd_M1INA = 0;
    cmd_M1INB = 1;
    cmd_M1PWM = 1;
  }
  else{
    Serial.println("STOP");
    cmd = STOP;
    cmd_M1EN = 1;
    cmd_M1INA = 0;
    cmd_M1INB = 0; 
    cmd_M1PWM = 0;
  }
  
  digitalWrite(pin_M1EN, cmd_M1EN);
  digitalWrite(pin_M1INA, cmd_M1INA);
  digitalWrite(pin_M1INB, cmd_M1INB);
  digitalWrite(pin_M1PWM, cmd_M1PWM);
  
//  Serial.print(cmd_INH); 
//  Serial.print(" "); 
//  Serial.print(cmd_IN1);
//  Serial.print(" ");
//  Serial.println(cmd_IN2);
  
  delay(20);
}
