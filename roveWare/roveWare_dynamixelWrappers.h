// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// Dynamixel Wrapper on URC 2015 Horizon Protocol
//
// mrdt::rovWare

#ifndef ROVEWARE_DYNAMIXELWRAPPERS_H_
#define ROVEWARE_DYNAMIXELWRAPPERS_H_

#include "roveWare_tivaWrappers.h"

typedef struct rove_dynamixel_struct {

    uint8_t protocol_start_byte1;
    uint8_t protocol_start_byte2;

    uint8_t dynamixel_id;

    uint8_t message_byte_count;
    uint8_t read_write_flag;

    //address of registers low byte
    uint8_t dynamixel_register_address;

    uint8_t register1_low_byte;
    uint8_t register1_high_byte;

    uint8_t register2_low_byte;
    uint8_t register2_high_byte;

    uint8_t check_sum;

}__attribute__((packed)) rove_dynamixel_struct, *rove_dynamixel_struct_ptr;

//Left Over from Horizon protocol//positive is clockwise, negative is counterclockwise
#define wrist_rotate 201
#define wrist_vertical 202
#define elbow_rotate 203
#define elbow_vertical 204
#define base_rotate 205
#define e_stop_arm 206
#define gripper_open 208

#define WRIST_A_ID  0x01
#define WRIST_B_ID  0x02
#define ELBOW_A_ID  0x03
#define ELBOW_B_ID  0x04
#define BASE_ID     0x05
#define LIN_ACT_ID  0x06

#define GRIPPER_ID  0x08

#define ZERO_SPEED 0

//TODO
#define ENDLESS_ROTATION 359

#define DYNAMIXEL_SPEED_MIN -1022
#define DYNAMIXEL_SPEED_MAX 1022

#define WRIST_UART      TEST_DEVICE_PIN
#define ELBOW_UART      TEST_DEVICE_PIN
#define ELBOW_UART      TEST_DEVICE_PIN
#define BASE_UART       TEST_DEVICE_PIN
#define GRIPPER_UART    TEST_DEVICE_PIN
#define LIN_ACT_UART    TEST_DEVICE_PIN

//PINMAP for 123G:

// GPIO: SET_TRI_ST_BUF_Tx                  PB3
// GPIO: MOTOR_CONTROLLER_ENABLE            PD2
// GPIO: MOTOR_CONTROLLER_INPUT_1           PD3
// GPIO: MOTOR_CONTROLLER_INPUT_2           PE2
//UART 0:   TX PA1, RX PA0
//UART 1:   TX PB1, RX PB0
//UART 2:   TX PD7, RX PD6  MOTHERBOARD_UART
//UART 3:   TX PC7, RX PC6  END_EFFECTOR_UART
//UART 4:   TX PC5, RX PC4  DYNAMIXEL_UART
//UART 5:   TX PE5, RX PE4
//UART 6:   TX PD5, RX PD4
//UART 7:   TX PE1, RX PE0  LINEAR_ACTUATOR_UART

//TODO wtf
#define FOUR_BYTES 4

//Dynamixel Commands
#define DYNAMIXEL_ROTATE_TO_POSITION_COMMAND        30
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
#define DYNAMIXEL_ROTATE_AT_ACCELERATION_SETTING   73

//Dynamixel Instruction Set
#define DYMAMIXEL_MSG_START_BYTE                    255

//Immediate Actions
//#define DYNAMIXEL_PING                              1
//#define DYNAMIXEL_READ_DATA                         2
#define DYNAMIXEL_WRITE_DATA                        3

//Delayed Actions
//#define DYNAMIXEL_REG_WRITE                         4
//#define DYNAMIXEL_ACTION                            5
//#define DYNAMIXEL_RESET                             6
//#define DYNAMIXEL_SYNC_WRITE                        131

void roveDynamixel_SendCommand(int tiva_pin, int16_t command_type, uint8_t dynamixel_id, int16_t first_command_value, int16_t second_command_value);

int16_t roveConverRedProtocol_toDynamixelSpeed(int16_t dynamixel_rotate_at_speed);

int16_t roveReverseDynamixelSpeed(int16_t dynamixel_rotate_at_speed);

#endif // ROVEWARE_DYNAMIXELWRAPPERS_H_
