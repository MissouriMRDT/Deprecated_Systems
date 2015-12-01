// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
//mrdt::rovWare
#ifndef ROVEWARE_CNTRLUTILS_H_
#define ROVEWARE_CNTRLUTILS_H_

//C lib
#include <stdint.h>

//mrdt definitions
#include "roveTiva1294.h"

//TODO REED?:
//TODO MRDT shorthand
#define INTERFACE_PROTOCOL_SPEEDS 1024

enum RoveWristDev16ShortHand {

    DEV16_NO_INSTRUCTION =      0x00
    , DEV16_TEST_INSTRUCTION =  0x01
    , DEV16_TEST_ERROR =        0x02
};//end enum


enum RoveDynaAxSerialMsgCfg {

    AX_PACKET =                 1
    , AX_NO_PACKET =            0
    , AX_MSG_MAX_BYTES =        20
    , AX_READ_REPLY =           1
    , AX_MAX_READ_ATTMPT_CNT =  10
    , AX_ERROR_FREE =           1
    , AX_ERROR =                -1
};//end enum

enum RoveDynaAxRegMsgHeader {

    PACKET_AX_START_BYTE  =   255
    , TX_DELAY_AX_MICRO_SEC = 100
    , WRITE_AX_CMD =            1
    , READ_AX_REQ =             2
    , READ_ONE_BYTE_AX_REQ =    1
    , READ_TWO_BYTES_AX_REQ =   2
};//end enum

enum RoveDynaAxRegConfig {

    JOINT_MODE_AX_CFG =         8
    , WHEEL_MODE_AX_CFG =       8
    , TORQUE_MODE_AX_CFG =      24
    , TORQUE_LIMIT_AX_CFG =     34
};//end enum

enum RoveDynaAxRegCommand {

    GO_ANGLE_AX_REG =           30
    , GO_SPEED_AX_REG =         32
};//end enum

enum RoveDynaAxRegTelemRequest {

    READ_ANGLE_AX_REQ =         36
    , READ_SPEED_AX_REQ =       38
    , READ_LOAD_AX_REQ =        40
    , READ_VOLTAGE_AX_REQ =     42
    , READ_TEMPERATURE_AX_REQ = 43
    , READ_CURRENT_AX_REQ =     68
};//end enum

typedef struct rove_dyna_serial {

    //Dynamixel AX12
    uint8_t dynamixel_id;
    roveUart_Handle uart;
    roveGpio_Handle tri_state_buffer;
    int32_t error_flag;

    //request/reply: tossin robotics dynamixel serial response model
    uint8_t write_only_flag;
    uint8_t read_reply_id;
    int32_t read_reply;
}__attribute__((packed)) rove_dyna_serial, *rove_dyna_serial_ptr;

//constructor
int32_t roveDynamixel_Init(

        rove_dyna_serial* dynamixel
        , uint8_t dyna_id
        , roveUart_Handle serial_port
        , roveGpio_Handle* tri_state_pin
        , uint8_t write_only_flag
);//end fnctn

//WHEEL Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynamixel_SetWheelModeCFG( rove_dyna_serial* dynamixel);

int32_t roveDynamixel_SpinWheelCMD(

        rove_dyna_serial* dynamixel
        , int16_t wheel_speed
);//end fnctn

int32_t roveDynamixel_ReadWheelREQ(rove_dyna_serial* dynamixel);

//JOINT Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynamixel_SetJointModeCFG(rove_dyna_serial* dynamixel);

int32_t roveDynamixel_RotateJointCMD(

        rove_dyna_serial* dynamixel
        , uint16_t joint_position
        , uint16_t joint_speed
);//end fnctn

int32_t roveDynamixel_ReadJointREQ(rove_dyna_serial* dynamixel);

//Handle Dyna Serial Comms
int32_t roveDynamixel_WritePacketMSG(

        rove_dyna_serial* dynamixel
        , uint8_t* write_msg_data
        , int32_t msg_data_byte_count
        , uint8_t read_reply_flag
);//end fnctn

int32_t roveDynamixel_ReadPacketMSG(rove_dyna_serial* dynamixel);

int32_t roveDynamixel_ParseReplyInt32MSG(uint8_t* data_buffer);

//developement hook for empty stub debug:
int32_t roveDynamixel_HandleDynaREPLY(

        rove_dyna_serial* dynamixel_id
        , uint8_t* data_buffer
);//end fnctn

int32_t roveDynamixel_ReadRegistersREQ(

        rove_dyna_serial* dynamixel_id
        , uint8_t dyna_registers_addr
        , uint8_t dyna_registers_byte_cnt
);//end fnctn

#endif // ROVEWARE_CNTRLUTILS_H_
