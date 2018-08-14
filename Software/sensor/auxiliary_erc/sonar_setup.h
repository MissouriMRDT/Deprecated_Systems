#ifndef SONAR_SETUP_H_
#define SONAR_SETUP_H_

#include "auxiliary_erc.h"

#define PULSE_DELAY 1 // ms to hold pulse pin high to prompt for reading

struct Sonar_Data{
  uint8_t struct_id;
  uint8_t sonar_id;
  uint8_t dist;
};

Sonar_Data son0_data;
Sonar_Data son1_data;
Sonar_Data son2_data;

SoftwareSerial son0_ser(SON0_RX, SON0_TX);
SoftwareSerial son1_ser(SON1_RX, SON1_TX);
SoftwareSerial son2_ser(SON2_RX, SON2_TX);

void sonar_setup(Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data);
void sonar_setup_solo(Sonar_Data &sonar_data, uint8_t sonar_id);
void sonar_update(Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data);
void sonar_update_solo(Sonar_Data &sonar_data);
uint8_t sonar_read(uint8_t sonar_id);
uint8_t sonar_read_solo(int pulse_pin, SoftwareSerial &ser);
void sonar_send();

void sonar_setup(Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data){
//  digitalWrite(SON0_PULSE, LOW);
//  digitalWrite(SON1_PULSE, LOW);
//  digitalWrite(SON2_PULSE, LOW);
  
  son0_ser.begin(9600); delay(10);
  son1_ser.begin(9600); delay(10);
  son2_ser.begin(9600); delay(10);
  
  sonar_setup_solo(son0_data, 0);
  sonar_setup_solo(son1_data, 1);
  sonar_setup_solo(son2_data, 2);
  
  return;
}

void sonar_setup_solo(Sonar_Data &sonar_data, uint8_t sonar_id){
  sonar_data.struct_id = SONAR_STRUCT_ID;
  sonar_data.sonar_id = sonar_id;
  sonar_data.dist = 0;
  
  return;
}

void sonar_update(Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data){
  sonar_update_solo(son0_data);
  sonar_update_solo(son1_data);
  sonar_update_solo(son2_data);
  
  return;
}

// Pulse sonar and read serial output.
// Returns:
//   -1 : No data to read
//   else : value of distance
void sonar_update_solo(Sonar_Data &sonar_data){
  sonar_data.dist = sonar_read(sonar_data.sonar_id);
  delay(send_delay);
  
  return;
}

uint8_t sonar_read(uint8_t sonar_id){
  uint8_t data;
  
  switch(sonar_id){
    case 0:
      data = sonar_read_solo(SON0_PULSE, son0_ser);
      break;
    case 1:
      data = sonar_read_solo(SON1_PULSE, son1_ser);
      break;
    case 2:
      data = sonar_read_solo(SON2_PULSE, son2_ser);
      break;
    default:
      break;
  }
  
  return data;
}

uint8_t sonar_read_solo(int pulse_pin, SoftwareSerial &ser){
  uint8_t reading[5];
  uint8_t value = 0;
  char c = 0;
  
//  digitalWrite(pulse_pin, HIGH);
//  delay(PULSE_DELAY);
//  digitalWrite(pulse_pin, LOW);
//  delay(send_delay);
  
  c = ser.read();
  Serial.println(c);
  return 0;
  
//  for(int i=0; i<5; i++){
//    reading[i] = ser.read();
//  }
//  
//  if(reading[0] != 'R'){
//    return -1;
//  }
//  
//  value = ( ( reading[1] - 48 ) * 100 ) + ( ( reading[2] - 48 ) * 10 ) + ( reading[3] - 48 );
//  return value;
}

#endif
