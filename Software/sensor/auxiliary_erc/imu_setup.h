#ifndef IMU_SETUP_H_
#define IMU_SETUP_H_

#include "auxiliary_erc.h"
#include "lsm9ds1.h"

struct IMU_Data
{
  uint8_t struct_id;
  float heading;
};

IMU_Data imu_data;
lsm9ds1 me;

void imu_setup(IMU_Data &imu_data, lsm9ds1 &me)
{
  //setting default values for voltage sensor data
  imu_data.struct_id = IMU_STRUCT_ID;
  imu_data.heading = 0;
  
  // Initialization of LSM9DS1 Object
  uint16_t status = init_lsm9ds1( &me,
                                G_SCALE_245DPS,
                                A_SCALE_2G,
                                M_SCALE_4GS,
                                G_ODR_119_BW_14,
                                A_ODR_50,
                                M_ODR_40,
                                M_XY_OM_M,
                                M_Z_OM_M);
  if(status != WHO_AM_I)
    Serial.println("ERROR: I2C communication with LSM9DS1");
  
  return;
}

void imu_update(IMU_Data &imu_data, lsm9ds1 &me){
  imu_data.heading = get_heading(&me);
  
  return;
}

#endif
