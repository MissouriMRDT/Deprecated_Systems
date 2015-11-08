// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_CntrlUtils.h
//
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
// mrdt::rovWare

#ifndef ROVEWARE_CNTRLUTILS_H_
#define ROVEWARE_CNTRLUTILS_H_

//C lib
#include <stdint.h>

//MRDT definitions
#include "roveWare_hardwareWrappers.h"

//TODO
#define ZERO_SPEED 0
#define ENDLESS_ROTATION 359

#define DYNAMIXEL_SPEED_MIN -1022
#define DYNAMIXEL_SPEED_MAX 1022

#define LIN_ACT_FORWARD 0xE1
#define LIN_ACT_REVERSE 0xE0

//TODO
#define FOUR_BYTES 4

//Dynamixel Commands
#define ROTATE_TO_POSITION_CMD_REG_ADDR             30
#define DYNAMIXEL_ROTATE_AT_SPEED_COMMAND           32

//Dynamixel Telemetry Requests
#define DYNAMIXEL_PRESENT_POSITION_REQUEST          36
#define DYNAMIXEL_PRESENT_SPEED_REQUEST             38
#define DYNAMIXEL_PRESENT_VOLTAGE_REQUEST           42
#define DYNAMIXEL_CONSUMING_CURRENT_REQUEST         68
#define DYNAMIXEL_PRESENT_TEMPERATURE_REQUEST       43
#define DYNAMIXEL_PRESENT_LOAD_REQUEST              40

//Dynamixel Run Time Config
#define DYNAMIXEL_TORQUE_ENABLE_SETTING             24
#define DYNAMIXEL_TORQUE_LIMIT_SETTING              34
#define DYNAMIXEL_ROTATE_AT_TORQUE_SETTING          71
#define DYNAMIXEL_ROTATE_AT_ACCELERATION_SETTING    73

//Dynamixel Instruction Set
#define DYMAMIXEL_MSG_START_BYTE                    255

//Immediate Actions
//#define DYNAMIXEL_PING                              1
//#define DYNAMIXEL_READ_DATA                         2
#define DYNAMIXEL_WRITE_DATA                          3

//Delayed Actions
//#define DYNAMIXEL_REG_WRITE                         4
//#define DYNAMIXEL_ACTION                            5
//#define DYNAMIXEL_RESET                             6
//#define DYNAMIXEL_SYNC_WRITE                        131

//persist
typedef struct rove_dynamixel_struct {

    uint8_t protocol_start_byte1;
    uint8_t protocol_start_byte2;

    uint8_t dynamixel_id;

    uint8_t message_byte_count;
    uint8_t read_write_flag;

    uint8_t dynamixel_register_address;

    uint8_t register1_low_byte;
    uint8_t register1_high_byte;

    uint8_t register2_low_byte;
    uint8_t register2_high_byte;

    uint8_t check_sum;

}__attribute__((packed)) rove_dynamixel_struct, *rove_dynamixel_struct_ptr;


//command_byte : forward /reverse
typedef struct linear_actuator_struct {

    uint8_t command_byte;
    uint8_t speed;

}__attribute__((packed)) linear_actuator_struct, *linear_actuator_struct_ptr;

//roveWare Control Routines

//standard rcservo : 1000uS full reverse : 1500uS stop : 2000uS full forward
void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed);

//0 is full speed reverse : 2048 is stop : 4096 is full speed forward
void roveDynamixel_Rotate(uint8_t dynamixel_id, int tiva_pin, int16_t first_command_value, int16_t second_command_value);

//base_station protocol : -1000 is reverse : 0 stop : 1000 is full speed forward : must scale to dynamixel proto
int16_t roveDynamixel_ConvertSpeed(int16_t dynamixel_rotate_at_speed);
int16_t roveDynamixel_ReverseSpeed(int16_t dynamixel_rotate_at_speed);

//positive is forward, negative is reverse, only 8 bit low_byte is speed
void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed);

//TODO Add New Member Functions (Dynamixel and Polulo Wrappers)

#endif // ROVEWARE_CNTRLUTILS_H_
