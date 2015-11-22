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

//mrdt definitions
#include "roveWare_hardwareWrappers.h"

//mrdt Shorthand
#define SINGLE_BYTE 1
#define NO_ERRORS 1
#define ERROR -1
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0
#define ZERO_SPEED 0

//TODO
//roveWare Control Routines
#define TRI_STATE_PIN                   0x01
#define TX_HIGH                         0x01
#define RX_LOW                          0x00

//dynamixel Config
#define DYNAMIXEL_TX_DELAY_MICRO_SEC    100

//dynamixel Protocol
#define DYNAMIXEL_PACKET_START_BYTE     255

#define AX12_IMMEDIATE_CMD              3
#define AX12_SET_MODE                   8
#define AX12_TARGET_POSITN_REG          30
#define AX12_TARGET_SPEED_REG           32

//standard rcservo : 1000uS full reverse : 1500uS stop : 2000uS full forward
void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed);

void roveDynamixel_SendByteMSG(uint8_t tiva_pin, uint8_t data_byte);

int8_t roveDynamixel_SendPacketMSG(uint8_t dynamixel_id, uint8_t* data_buffer, uint16_t data_byte_count);

int8_t roveDynamixel_CatchErrorMSG();

//////////////////////////////////////////TODO

/*

// EEPROM AREA  ///////////////////////////////////////////////////////////
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

typedef enum {
    AX_OFF = 0,
    AX_ON = 1
} dynamixel_errors;

typedef enum {
    AX_COUNTERCLOCKWISE = 0,
    AX_CLOCKWISE = 1
} DynamixelDirection;

typedef enum {
    AX_RETURN_NONE = 0,
    AX_RETURN_READ = 1,
    AX_RETURN_ALL = 2
} DynamixelStatusReturnLevel;

#include <inttypes.h>

unsigned char Direction_Pin;

//TODO
#define ZERO_SPEED 0
#define ENDLESS_ROTATION 0

#define DYNAMIXEL_SPEED_MIN -1022
#define DYNAMIXEL_SPEED_MAX 1022

#define LIN_ACT_FORWARD 0xE1
#define LIN_ACT_REVERSE 0xE0

//TODO
#define SIX_BYTES 6

#define FOUR__BYTES 4

#define SET_WHEEL_MODE_CMD_REG_ADDR 8

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

    //uint8_t register1_low_byte;
    //uint8_t register1_high_byte;

    uint8_t register2_low_byte;
    uint8_t register2_high_byte;

    uint8_t check_sum;

}__attribute__((packed)) rove_dynamixel_struct, *rove_dynamixel_struct_ptr;


//command_byte : forward /reverse
typedef struct linear_actuator_struct {

    uint8_t command_byte;
    uint8_t speed;

}__attribute__((packed)) linear_actuator_struct, *linear_actuator_struct_ptr;



//0 is full speed reverse : 2048 is stop : 4096 is full speed forward
void roveDynamixel_Rotate(uint8_t dynamixel_id, int tiva_pin, int16_t first_command_value, int16_t second_command_value);

void roveDynamixel_SetWheelMode(uint8_t dynamixel_id, int tiva_pin, int16_t first_command_value, int16_t second_command_value);

//base_station protocol : -1000 is reverse : 0 stop : 1000 is full speed forward : must scale to dynamixel proto
int16_t roveDynamixel_ConvertSpeed(int16_t dynamixel_rotate_at_speed);
int16_t roveDynamixel_ReverseSpeed(int16_t dynamixel_rotate_at_speed);

//positive is forward, negative is reverse, only 8 bit low_byte is speed
void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed);

//TODO Add New Member Functions (Dynamixel and Polulo Wrappers)
*/
#endif // ROVEWARE_CNTRLUTILS_H_
