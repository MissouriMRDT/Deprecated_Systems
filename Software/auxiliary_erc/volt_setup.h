#ifndef VOLT_SETUP_H_
#define VOLT_SETUP_H_

#include "auxiliary_erc.h"

struct Volt_Data
{
  uint8_t struct_id;
  uint8_t voltage;
};

Volt_Data volt_data;

EasyTransfer volt_ET;

void volt_setup(Volt_Data &volt_data)
{
  //setting default values for voltage sensor data
  volt_data.struct_id = VOLT_STRUCT_ID;
  volt_data.voltage = 0;
  
  // init EasyTransfer
  volt_ET.begin(details(volt_data), &Serial);
  
  return;
}

void volt_update(Volt_Data &volt_data){
  volt_data.voltage = analogRead(VOLT_PIN);
  
  return;
}

void volt_send(){
  send_data(volt_ET);
  
  return;
}

#endif
