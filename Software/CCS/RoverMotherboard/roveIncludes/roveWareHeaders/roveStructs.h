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

// sent from mobo to roboticArm to control the peripheral

struct robot_arm_command{

	uint8_t struct_id;
	int16_t speed;

}__attribute__((packed));

// sent from mobo to gripper to control the peripheral

struct gripper_command{

	uint8_t struct_id;
	int speed;

}__attribute__((packed));

// sent from mobo to drill to control the peripheral

struct drill_command{

	uint8_t struct_id;
	//drill ctrl
	uint8_t goalSpeed;
	uint8_t direction;

	//thermo ctrl
	uint8_t heaterPower;
	uint8_t thermoReadings;

	//gas ctrl
	uint8_t sensorPower;

	//readings will only be updated when true
	uint8_t gasReadings;

}__attribute__((packed));


struct bms_emergency_stop_command
{
	uint8_t struct_id;
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





// this struct should only be used for type casting as it does not have a corresponding id

// may not work with non void pointer casts

struct rovecom_id_cast{

	uint8_t struct_id;

}__attribute__((packed));

#endif // ROVESTRUCTS_H_
