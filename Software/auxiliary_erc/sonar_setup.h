#ifndef SONAR_SETUP_H_
#define SONAR_SETUP_H_

#include "auxiliary_erc.h"

struct Sonar_Data{
  uint8_t struct_id;
  uint8_t sonar_id;
  uint8_t dist;
};

Sonar_Data sonar_data0;
Sonar_Data sonar_data1;
Sonar_Data sonar_data2;

EasyTransfer sonar0_ET;
EasyTransfer sonar1_ET;
EasyTransfer sonar2_ET;

SoftwareSerial sonar0_ser(SON0_RX, SON0_TX);
SoftwareSerial sonar1_ser(SON1_RX, SON1_TX);
SoftwareSerial sonar2_ser(SON2_RX, SON2_TX);

void sonar_setup(Sonar_Data &sonar_data0, Sonar_Data &sonar_data1, Sonar_Data &sonar_data2);
void sonar_setup_solo(Sonar_Data &sonar_data, uint8_t sonar_id);
void sonar_update(Sonar_Data &sonar_data0, Sonar_Data &sonar_data1, Sonar_Data &sonar_data2);
void sonar_update_solo(Sonar_Data &sonar_data);
int8_t sonar_read(uint8_t sonar_id);
int8_t sonar_read_solo(int pulse_pin, SoftwareSerial &ser);
void sonar_send();

void sonar_setup(Sonar_Data &sonar_data0, Sonar_Data &sonar_data1, Sonar_Data &sonar_data2){
  //setting default values for sonar sensor data
  sonar_setup_solo(sonar_data0, 0);
  sonar_setup_solo(sonar_data1, 1);
  sonar_setup_solo(sonar_data2, 2);
  
  // init EasyTransfer
  sonar0_ET.begin(details(sonar_data0), &Serial);
  sonar1_ET.begin(details(sonar_data1), &Serial);
  sonar2_ET.begin(details(sonar_data2), &Serial);
  
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

void sonar_update(Sonar_Data &sonar_data0, Sonar_Data &sonar_data1, Sonar_Data &sonar_data2){
  sonar_update_solo(sonar_data0);
  sonar_update_solo(sonar_data1);
  sonar_update_solo(sonar_data2);
  
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
  
  Serial.println(ser.read());
  
//  if(reading[0] != 'R'){
//    return -1;
//  }
  
  value = ( ( reading[1] - 48 ) * 100 ) + ( ( reading[2] - 48 ) * 10 ) + ( reading[3] - 48 );
  return value;
}

void sonar_send(){
  send_data(sonar0_ET);
  send_data(sonar1_ET);
  send_data(sonar2_ET);
  
  return;
}

#endif
