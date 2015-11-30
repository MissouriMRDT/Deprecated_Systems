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
#include "roveTiva129.h"

//////////////////////////////////SATTERFIELD/BISCHOFF/MILES TODO-> Rove Dynamixel CONTROL MODES BY MODEL Table Specs

#define INTERFACE_PROTOCOL_SPEEDS 1024

//TODO MRDT shorthand
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
    uint8_t tiva_pin;

    //TODO ??individual state??-> dynamixel_id ...vs ..tiva_pin ...error handling??
    uint8_t error_flag;

    //request/reply: tossin robotics dynamixel serial response model
    uint8_t write_only_flag;
    uint8_t read_reply_id;
    int32_t read_reply;

}__attribute__((packed)) rove_dyna_serial, *rove_dyna_serial_ptr;

int32_t roveDynamixel_Init(rove_dyna_serial* dynamixel, uint8_t dyna_id, int32_t tiva_pin, uint8_t read_reply_flag );

//WHEEL Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynamixel_SetWheelModeCFG(rove_dyna_serial* dynamixel);
int32_t roveDynamixel_SpinWheelCMD(rove_dyna_serial* dynamixel, int16_t wheel_speed);

//JOINT Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynamixel_SetJointModeCFG(rove_dyna_serial* dynamixel);
int32_t roveDynamixel_RotateJointCMD(rove_dyna_serial* dynamixel, uint16_t joint_position, uint16_t joint_speed);

//Handle Dyna Serial Comms
int32_t roveDynamixel_WritePacketMSG(rove_dyna_serial* dynamixel, uint8_t* write_msg_data, int32_t msg_data_byte_count, uint8_t read_reply_flag);
int32_t roveDynamixel_ReadPacketMSG(uint8_t dynamixel_id);
int32_t roveDynamixel_ParseReplyInt32MSG(uint8_t* data_buffer);
//developement hook for empty stub debug:
int32_t roveDynamixel_HandleDynaREPLY(rove_dyna_serial* dynamixel_id, uint8_t* data_buffer);

//I like a big dynamixel model register request configuration lookup script??
int32_t roveDynamixel_ReadRegistersREQ(rove_dyna_serial* dynamixel_id, uint8_t dyna_registers_addr, uint8_t dyna_registers_byte_cnt);


//////////////////////////////////GBENGA TODO-> Rove Dynamixel Software Serial Feedback Aggregation Layer
//dynamixels have  many other registers
//roveDynamixel setDynaConfig aggregate function?
//roveDynamixel getDynaConfig aggregate function?
//More than One "roveDynamixel getTylemetryWeCareAbout request aggregate function?
int32_t roveDynamixel_ReadWheelREQ(rove_dyna_serial* dynamixel);
int32_t roveDynamixel_ReadJointREQ(rove_dyna_serial* dynamixel);




//END TODO??
//#define AX12_ROTATE_AT_TORQUE             71
//#define AX12_ROTATE_AT_ACCELERATION       73
//#define AX12_WHEELSPEED_OFFSET 1024
//#define CLOCKWISE           1
//#define COUNTERCLOCKWISE    0
//#define ZERO_SPEED          0
//#define DONT_LISTEN_FOR_REPLY 0
//#define LISTEN_FOR_REPLY 1



//////////////////////////////////////////TODO->::EEPROM AREA
/*//////////////////////////////////////////////////////////
#define AX_MODEL_NUMBER_L           0
#define AX_MODEL_NUMBER_H           1
#define AX_VERSION                  2
#define AX_ID                       3
#define AX_BAUD_RATE                4
#define AX_RETURN_DELAY_TIME        5
#define AX_CW_ANGLE_LIMIT_L         6
#define AX_CW_ANGLE_LIMIT_H         7
#define AX_CCW_ANGLE_LIMIT_L        8
#define AX_CCW_ANGLE_LIMIT_H        9
#define AX_SYSTEM_DATA2             10
#define AX_LIMIT_TEMPERATURE        11
#define AX_DOWN_LIMIT_VOLTAGE       12
#define AX_UP_LIMIT_VOLTAGE         13
#define AX_MAX_TORQUE_L             14
#define AX_MAX_TORQUE_H             15
#define AX_RETURN_LEVEL             16
#define AX_ALARM_LED                17
#define AX_ALARM_SHUTDOWN           18
#define AX_OPERATING_MODE           19
#define AX_DOWN_CALIBRATION_L       20
#define AX_DOWN_CALIBRATION_H       21
#define AX_UP_CALIBRATION_L         22
#define AX_UP_CALIBRATION_H         23

// RAM AREA  //////////////////////////////////////////////////////////////
#define AX_TORQUE_ENABLE            24
#define AX_LED                      25
#define AX_CW_COMPLIANCE_MARGIN     26
#define AX_CCW_COMPLIANCE_MARGIN    27
#define AX_CW_COMPLIANCE_SLOPE      28
#define AX_CCW_COMPLIANCE_SLOPE     29
#define AX_GOAL_POSITION_L          30
#define AX_GOAL_POSITION_H          31
#define AX_GOAL_SPEED_L             32
#define AX_GOAL_SPEED_H             33
#define AX_TORQUE_LIMIT_L           34
#define AX_TORQUE_LIMIT_H           35
#define AX_PRESENT_POSITION_L       36
#define AX_PRESENT_POSITION_H       37
#define AX_PRESENT_SPEED_L          38
#define AX_PRESENT_SPEED_H          39
#define AX_PRESENT_LOAD_L           40
#define AX_PRESENT_LOAD_H           41
#define AX_PRESENT_VOLTAGE          42
#define AX_PRESENT_TEMPERATURE      43
#define AX_REGISTERED_INSTRUCTION   44
#define AX_PAUSE_TIME               45
#define AX_MOVING                   46
#define AX_LOCK                     47
#define AX_PUNCH_L                  48
#define AX_PUNCH_H                  49

// Instruction Set ///////////////////////////////////////////////////////////////
#define AX_PING                     1
#define AX_READ_DATA                2
#define AX_WRITE_DATA               3
#define AX_REG_WRITE                4
#define AX_ACTION                   5
#define AX_RESET                    6
#define AX_SYNC_WRITE               131

// Specials ///////////////////////////////////////////////////////////////
#define AX_BYTE_READ_ONE            1
#define AX_BYTE_READ_TWO            2
#define BROADCAST_ID                254
#define AX_START_BYTE               255

#define AX_CCW_AL_L                 255
#define AX_CCW_AL_H                 3
#define LOCK                        1

#define TIME_OUT                    10         // This parameter depends on the speed of transmission
#define TX_DELAY_TIME               400        // This parameter depends on the speed of transmission - but can be changed to a higher speed.

#define Tx_MODE                     1
#define Rx_MODE                     0
//END::TODO */




/*JUDAH TODO->::DEPRECATED 2016 Robot Arm Developement
#define ZERO_SPEED 0
#define ENDLESS_ROTATION 0
#define DYNAMIXEL_SPEED_MIN -1022
#define DYNAMIXEL_SPEED_MAX 1022
#define LIN_ACT_FORWARD 0xE1
#define LIN_ACT_REVERSE 0xE0
//command_byte : forward /reverse
typedef struct linear_actuator_struct {

    uint8_t command_byte;
    uint8_t speed;
}__attribute__((packed)) linear_actuator_struct, *linear_actuator_struct_ptr;
//positive is forward, negative is reverse, only 8 bit low_byte is speed
void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed);
*/





#endif // ROVEWARE_CNTRLUTILS_H_
