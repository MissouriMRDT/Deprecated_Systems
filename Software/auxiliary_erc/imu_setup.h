#ifndef IMU_SETUP_H_
#define IMU_SETUP_H_

#include "auxiliary_erc.h"

struct IMU_Data
{
  uint8_t struct_id;
  uint8_t heading;
};

IMU_Data imu_data;

EasyTransfer imu_ET;

void imu_setup(IMU_Data &imu_data)
{
  //setting default values for voltage sensor data
  imu_data.struct_id = IMU_STRUCT_ID;
  imu_data.heading = 0;
  
  Wire.begin();
  
  // init EasyTransfer
  imu_ET.begin(details(imu_data), &Serial);
  
  return;
}

void imu_update(IMU_Data &imu_data){
  
  
  return;
}

void imu_send(){
  send_data(imu_ET);
  
  return;
}

#endif
