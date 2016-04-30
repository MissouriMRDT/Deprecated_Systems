#include "pins_energia.h"
#include "wiring_private.h"

void blink();

void setup()
{
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 0; i < 19; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(27, OUTPUT);
  pinMode(81, OUTPUT); // D1
  pinMode(82, OUTPUT); // D2
  pinMode(83, OUTPUT); // D3
  pinMode(84, OUTPUT); // D4
  
  attachInterrupt(27, blink, CHANGE);
}

volatile bool toggle = false;

void loop()
{
  // Energia pin file under lm4f/variants folder
  // put your main code here, to run repeatedly:
  PWMWrite(27, 255, 255/2, 5000);
  
  /*for(int i = 81; i < 85; i++){
    digitalWrite(i, HIGH);
  }*/
  /*for(int i = 2; i <= 19; i++) {
    PWMWrite(i, 4096, 4090, 50);
    uint8_t timer = digitalPinToTimer(i);
    uint8_t timerInterrupt = getTimerInterrupt(timer);
    Serial.print("Timer: ");
    Serial.println(timer);
    Serial.print("Timer Int: ");
    Serial.println(timerInterrupt);
    delay(1000);
    attachInterrupt(i, blink, CHANGE);
    PWMWrite(84, 4096, 4090, 50);
    timer = digitalPinToTimer(i);
    timerInterrupt = getTimerInterrupt(timer);
    Serial.print("Timer: ");
    Serial.println(timer);
    Serial.print("Timer Int: ");
    Serial.println(timerInterrupt);
    delay(1000);
    detachInterrupt(i);
  } *//* for(int i = 23; i <= 40; i++) {
    
  } for(int i = 42; i <= 55; i++) {
    
  } for(int i = 57; i <= 59; i++) {
    
  } for(int i = 63; i <= 80; i++) {
    
  } */
}

void blink() {
  digitalWrite(84, toggle);
  toggle = !toggle;
}
