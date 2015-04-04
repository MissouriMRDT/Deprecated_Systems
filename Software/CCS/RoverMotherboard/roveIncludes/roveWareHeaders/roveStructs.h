// roveStructs.h
//
// first created:
//
// 04_20_2014_Keenan Johnson
//
// last edited:
//
//02_25_2015_Judah Schad_jrs6w7@mst.edu
//03_08_2015 Connor Walsh cwd8d@mst.edu ~ add stubs for RoveComm structs

#pragma once

#ifndef ROVESTRUCTS_H_
#define ROVESTRUCTS_H_

//includes globally scoped Texas Instruments (TI) header files

#include "../RoverMotherboardMain.h"

//size in bytes of longest command that can be recieved from the base station

#define MAX_COMMAND_SIZE 30

#define MAX_TELEM_SIZE 30


// Device id

#define	onenull_device_id 111
#define	test_device_id 99
#define	motor_left_id 100
#define	motor_right_id 101
#define	robot_arm_id 102
#define	gripper_id 103
#define	drill_id 104

//struct id

/*#define	blank_id_zero 0
#define	mobo_identify_req 1
#define	dev_identify_reply 2
#define	mobo_begin_op_req 3
#define	dev_begin_op_reply 4
#define	mobo_telem_req 5
#define	dev_command_reply 6
#define	blank_id_seven 7
#define	mobo_robo_arm_command 8
#define	mobo_gripper_command 9
#define	mobo_drill_command 10
*/

//Returns the size of the struct with the associated ID
//-1 for error
int getStructSize(char structId);

typedef struct base_station_msg_struct{

	char id;
	char value[MAX_COMMAND_SIZE];

}__attribute__((packed)) base_station_msg_struct, *base_msg;

//normally the compiler implicitly optimizes memory allocations for member variables by padding to the nearest 32 bits

//attribute__((packed)) explicitly overides this and is necessary because the TI board is 32 bit and the ATMegas are 8 bit

// TODO remove last years structs, they will not be used for new RoveComm

struct motor_control_struct{

	char id;
	int speed;

}__attribute__((packed));

struct mobo_identify_req // Sent from mobo to device to request identify
{
	uint8_t struct_id;

}__attribute__((packed));

struct dev_identify_reply  // Sent from device to mobo to ack request for identification
{
	uint8_t struct_id;
	uint8_t device_id;

}__attribute__((packed));

struct mobo_begin_op_req  // Sent from mobo to tell device to begin operating mode
{
	uint8_t struct_id;

}__attribute__((packed));

struct dev_begin_op_reply // Sent from dev to mobo to acknoledge request and begin operation mode
{
	uint8_t struct_id;
	uint8_t device_id; // this field may not be necessary

}__attribute__((packed));

struct robot_arm_command // sent from mobo to roboticArm to control the peripheral
{
	uint8_t struct_id;
	uint8_t reset;
	uint8_t wristUp;
	uint8_t wristDown;
	uint8_t wristClockWise;
	uint8_t wristCounterClockWise;
	uint8_t elbowUp;
	uint8_t elbowDown;
	uint8_t elbowClockWise;
	uint8_t elbowCounterClockWise;
	uint8_t actuatorForward;
	uint8_t actuatorReverse;
	uint8_t baseClockWise;
	uint8_t baseCounterClockWise;

}__attribute__((packed));

struct gripper_command // Sent from mobo to gripper to control the peripheral
{
	uint8_t struct_id;
	uint8_t grip_cmd;

}__attribute__((packed));

struct drill_command // Sent from mobo to drill to control the peripheral
{
	uint8_t struct_id;
	uint8_t grip_cmd;
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

// This struct should only be used for type casting as it does not have a corresponding id;
struct rovecom_id_cast
{
	uint8_t struct_id;
}__attribute__((packed)); // may not work with non void pointer casts

#endif // ROVESTRUCTS_H_
