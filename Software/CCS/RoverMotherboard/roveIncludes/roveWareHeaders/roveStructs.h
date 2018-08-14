// roveStructs.h MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad jrs6w7@mst.edu

#pragma once

#ifndef ROVESTRUCTS_H_
#define ROVESTRUCTS_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoverMotherboardMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

// returns the size of the struct with the associated id, returns -1 for error

int getStructSize(char structId);

typedef struct base_station_msg_struct{

	char id;
	char value[MAX_COMMAND_SIZE];

}__attribute__((packed)) base_station_msg_struct, *base_msg;

//normally the compiler implicitly optimizes memory allocations for member variables by padding to the nearest 32 bits

//attribute__((packed)) explicitly overides this and is necessary because the TI board is 32 bit and the ATMegas are 8 bit

struct motor_control_struct{

	char id;
	int speed;

}__attribute__((packed));

// sent from mobo to device to request identify

struct device_telem_req{

	uint8_t struct_id;
	uint8_t telem_device_req_id;

}__attribute__((packed));

struct mobo_identify_req{

	uint8_t struct_id;

}__attribute__((packed));

// sent from device to mobo to ack request for identification

struct dev_identify_reply{

	uint8_t struct_id;
	uint8_t device_id;

}__attribute__((packed));

// sent from mobo to tell device to begin operating mode

struct mobo_begin_op_req{

	uint8_t struct_id;

}__attribute__((packed));

// sent from dev to mobo to acknoledge request and begin operation mode

struct dev_begin_op_reply{

	uint8_t struct_id;

	// this field may not be necessary

	uint8_t device_id;

}__attribute__((packed));

//this is the key value pair from Base
//mob will then assemble the full robot_arm_command for the device

struct base_station_robot_arm_command{

	uint8_t struct_id;
	int16_t value;

}__attribute__((packed));

struct erc_drill_actuator_robot_arm_command{

    uint8_t struct_id;
    int16_t drill_cmd;
    int16_t lin_act_cmd;

}__attribute__((packed));

// sent from mobo to roboticArm to control the peripheral

struct robot_arm_command{

	uint8_t struct_id;
	int16_t speed;

}__attribute__((packed));

// sent from mobo to gripper to control the peripheral


struct bms_emergency_command
{
	uint8_t struct_id;
	uint8_t command;
};

struct power_board_command
{
	uint8_t struct_id;
	uint8_t commmand[2];
}__attribute__((packed));

struct power_board_bms_telem
{
	uint8_t struct_id;
	float value;
};

/* Keenans:
struct gps_data_struct
{
  uint8_t fix;
  uint16_t latitude_whole;
  uint16_t latitude_frac;
  uint16_t longitude_whole;
  uint16_t longitude_frac;
  uint16_t altitude_whole;
  uint16_t altitude_frac;
  uint8_t lat_dir;
  uint8_t lon_dir;
  uint8_t satellites;
}__attribute__((packed));
*/

struct gps_telem
{
    uint8_t struct_id;
    bool fix;
    uint8_t fix_quality;
    uint8_t satellites;
    int32_t latitude_fixed;
    int32_t longitude_fixed;
    float altitude;
    float speed;
    float angle;
}__attribute__((packed));

struct sensor_heading_telem
{
    uint8_t struct_id;
    float heading;

}__attribute__((packed));

struct sensor_ultrasonic_telem
{
    uint8_t struct_id;
    uint8_t sensor;
    uint8_t distance;

}__attribute__((packed));

struct sensor_voltage_telem
{
    uint8_t struct_id;
    int16_t voltage;

}__attribute__((packed));

struct all_sensor_telem
{
    uint8_t struct_id;
    bool fix;
    uint8_t fix_quality;
    uint8_t satellites;
    int32_t latitude_fixed;
    int32_t longitude_fixed;
    float altitude;
    float speed;
    float angle;
    float heading;
    uint8_t sensor;
    uint8_t distance;
    int16_t voltage;
}__attribute__((packed));

// this struct should only be used for type casting as it does not have a corresponding id

// may not work with non void pointer casts

struct rovecom_id_cast{

	uint8_t struct_id;

}__attribute__((packed));

struct PTZ_Cam_Ctrl{

	uint8_t struct_id;
	uint8_t pan;
	uint8_t tilt;

}__attribute__((packed));

struct science_telem_request
{
  uint8_t struct_id;
  uint8_t requestType;
}__attribute__((packed));

struct PH_telem
{
  uint8_t struct_id;
  float PH;
}__attribute__((packed));

struct moisture_telem
{
  uint8_t struct_id;
  uint16_t moisture;
}__attribute__((packed));

struct CCD_telem_packet
{
  uint8_t struct_id;
  uint16_t packetIndex;
  uint16_t data[12];
}__attribute__((packed));

#endif // ROVESTRUCTS_H_
