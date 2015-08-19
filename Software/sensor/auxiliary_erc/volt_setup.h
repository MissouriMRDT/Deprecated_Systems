#ifndef VOLT_SETUP_H_
#define VOLT_SETUP_H_

#include "auxiliary_erc.h"

struct Volt_Data
{
  uint8_t struct_id;
  uint16_t rawvoltage;
};

Volt_Data volt_data;

void volt_setup(Volt_Data &volt_data)
{
  //setting default values for voltage sensor data
  volt_data.struct_id = VOLT_STRUCT_ID;
  volt_data.rawvoltage = 0;
  
  return;
}

void volt_update(Volt_Data &volt_data){
  volt_data.rawvoltage = analogRead(VOLT_PIN);
  
  return;
}

#endif
