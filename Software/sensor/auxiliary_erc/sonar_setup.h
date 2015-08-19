#ifndef SONAR_SETUP_H_
#define SONAR_SETUP_H_

#include "auxiliary_erc.h"

struct Sonar_Data{
  uint8_t struct_id;
  uint8_t sonar_id;
  uint8_t dist;
};

Sonar_Data son0_data;
Sonar_Data son1_data;
Sonar_Data son2_data;

SoftwareSerial sonar0_ser(SON0_RX, SON0_TX);
SoftwareSerial sonar1_ser(SON1_RX, SON1_TX);
SoftwareSerial sonar2_ser(SON2_RX, SON2_TX);

void sonar_setup(Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data);
void sonar_setup_solo(Sonar_Data &sonar_data, uint8_t sonar_id);
void sonar_update(Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data);
void sonar_update_solo(Sonar_Data &sonar_data);
int8_t sonar_read(uint8_t sonar_id);
int8_t sonar_read_solo(int pulse_pin, SoftwareSerial &ser);
void sonar_send();

void sonar_setup(Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data){
  //setting default values for sonar sensor data
  sonar_setup_solo(son0_data, 0);
  sonar_setup_solo(son1_data, 1);
  sonar_setup_solo(son2_data, 2);
  
  return;
}

void sonar_setup_solo(Sonar_Data &sonar_data, uint8_t sonar_id){
  delay(500);
  
  digitalWrite(SON0_PULSE, LOW);
  digitalWrite(SON1_PULSE, LOW);
  digitalWrite(SON2_PULSE, LOW);
  
  sonar_data.struct_id = SONAR_STRUCT_ID;
  sonar_data.sonar_id = sonar_id;
  sonar_data.dist = 0;
  
  switch(sonar_id){
    case 0:
      sonar0_ser.begin(9600);
      break;
    case 1:
      sonar1_ser.begin(9600);
      break;
    case 2:
      sonar2_ser.begin(9600);
      break;
    default:
      break;
  }
      
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

int8_t sonar_read(uint8_t sonar_id){
  int8_t data;
  
  switch(sonar_id){
    case 0:
      data = sonar_read_solo(SON0_PULSE, sonar0_ser);
      break;
    case 1:
      data = sonar_read_solo(SON1_PULSE, sonar1_ser);
      break;
    case 2:
      data = sonar_read_solo(SON2_PULSE, sonar2_ser);
      break;
    default:
      break;
  }
  
  return data;
}

int8_t sonar_read_solo(int pulse_pin, SoftwareSerial &ser){
  uint8_t reading[5];
  int8_t value = 0;
  
  digitalWrite(pulse_pin, HIGH);
  delay(pulse_delay);
  digitalWrite(pulse_pin, LOW);
  delay(send_delay);
  
//  for(int i=0; i<5; i++){
//    reading[i] = ser.read();
//  }
  
//  if(reading[0] != 'R'){
//    return -1;
//  }
  
  value = ( ( reading[1] - 48 ) * 100 ) + ( ( reading[2] - 48 ) * 10 ) + ( reading[3] - 48 );
  return value;
}

#endif
