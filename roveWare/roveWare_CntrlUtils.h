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

// Horizon protocol robot arm values

//TODO
#define deviceWrite roveUART_Write

// clockwise is positive, counter clockwise is negative
#define wrist_clock_wise 201
#define wrist_up 202
#define elbow_clock_wise 203
#define elbow_up 204
#define base_clock_wise 205
#define e_stop_arm 206
#define actuator_increment 207
#define gripper_open 208

//drill
#define drill_forward 209

void roboArmForwardCmd(uint8_t struct_id, int16_t speed);

void roboArmReverseCmd(uint8_t struct_id, int16_t speed);

void dynamixelSetEndlessCmd(uint8_t dynamixel_id);

void dynamixelSetSpeedLeftCmd(uint8_t dynamixel_id, int16_t speed);

void dynamixelSetSpeedRightCmd(uint8_t dynamixel_id, int16_t speed);

void setLinActuatorCmd(uint8_t device_id, int16_t speed);

void setDrillCmd(uint8_t device_id, int16_t command);

//fills a write char* write_buffer with the dynamixel formatted putput message
void buildDynamixelStructMessage(char* write_buffer, uint8_t dynamixel_id, uint8_t struct_id, int16_t command_value );

//fills a write char* write_buffer with the linear actuated formatted putput message
void buildLinActuatorStructMessage(char* write_buffer, uint8_t struct_id, int16_t speed);

void do_nothing();

int getDevicePort(uint8_t device_id);

int getStructSize(uint8_t struct_id);

typedef struct set_dyna_speed_struct{

    uint8_t start_byte1;
    uint8_t start_byte2;

    // arg0
    uint8_t dynamixel_id;

    //message
    uint8_t msg_size;
    uint8_t read_write_flag;

    //address of low byte
    uint8_t speed_low_byte_reg_addr;
    uint8_t speed_low_byte;
    uint8_t speed_high_byte;
    uint8_t check_sum;

}__attribute__((packed)) set_dyna_speed_struct;

typedef struct set_dyna_endless_struct{

    uint8_t start_byte1;
    uint8_t start_byte2;

    // arg0
    uint8_t dynamixel_id;

    //message
    uint8_t msg_size;
    uint8_t read_write_flag;

    //address of low byte
    uint8_t ccw_angle_limit_reg_addr;
    uint8_t ccw_angle_limit_low_byte;
    uint8_t ccw_angle_limit_high_byte;
    uint8_t check_sum;

}__attribute__((packed)) set_dyna_endless_struct;

typedef struct linear_actuator_struct{

    //address of low byte
    uint8_t command_byte;
    uint8_t speed;

}__attribute__((packed)) linear_actuator_struct;

typedef struct drill_struct{

    //address of low byte
    uint8_t command_byte;

}__attribute__((packed)) drill_struct;

typedef struct speed_struct{

    uint8_t struct_id;
    int16_t speed;

}__attribute__((packed)) speed_struct;

//mrdt shorthand
#define LOW 0
#define HIGH 1
#define FOREVER 1

//timing cfg
#define DO_NOTHING_CNT 20000

//tiva cfg
#define SET_TRI_ST_BUF_Tx 0
#define DYNAMIXEL_UART 0
#define LINEAR_ACTUATOR_UART 1
#define MOTHERBOARD_UART 2
#define END_EFFECTOR_UART 3

//msg cfg
#define BUFFER_SIZE 30
#define RECIEVE_RESET_CNT 800000

//dynamixel cfg
#define SET_ENDLESS_CMD 0
#define SET_SPEED_LEFT_CMD  1
#define SET_SPEED_RIGHT_CMD 2
#define SET_LIN_ACTUATOR_CMD 3
#define GET_DRILL_CMD 4

#define WRIST_A_ID  0x01
#define WRIST_B_ID  0x02
#define ELBOW_A_ID  0x03
#define ELBOW_B_ID  0x04
#define BASE_ID     0x05
#define LIN_ACT_ID  0x06
#define MOB_ID      0x07
#define GRIPPER_ID  0x08
#define DRILL_ID    0x09

#define NULL_COMAND_VALUE 0
#define ZERO_SPEED 0

#define SPEED_MIN -1022
#define SPEED_MAX 1022

#define BASE_SPEED_MAX 50
#define BASE_SPEED_MIN -50

//polulu cfg
#define LIN_ACT_FORWARD 0xE1
#define LIN_ACT_REVERSE 0xE0

#define MIN_LIN_ACT_SPEED -127
#define MAX_LIN_ACT_SPEED 127

//mrdt scope casting arg structs shorthand
#define SPEED_STRUCT            ((speed_struct*)(&buffer_struct))
#define TEST_STRUCT             ((speed_struct*)(&buffer_struct))
#define MESSAGE_STRUCT          ((message_struct*)write_buffer)
#define SET_ENDLESS_STRUCT      ((set_dyna_endless_struct*)write_buffer)
#define SET_DYNA_SPEED_STRUCT   ((set_dyna_speed_struct*)write_buffer)
#define SET_LIN_ACT_STRUCT      ((linear_actuator_struct*)write_buffer)
#define SET_DRILL_STRUCT        ((drill_struct*)write_buffer)

//drill values
#define DRILL_STOP 0x00
#define DRILL_FORWARD 0x01
#define DRILL_REVERSE 0x02

//From Savage Electronics Dynamixel Arduino Library Cfg

//TODO      #define these to make sense in rove so english
#define OFF                         0
#define ON                          1
#define LEFT                        0
#define RIGHT                       1
#define AX_BYTE_READ                1
#define AX_BYTE_READ_POS            2
#define AX_RESET_LENGTH             2
#define AX_ACTION_LENGTH            2
#define AX_ID_LENGTH                4
#define AX_LR_LENGTH                4
#define AX_SRL_LENGTH               4
#define AX_RDT_LENGTH               4
#define AX_LEDALARM_LENGTH          4
#define AX_SALARM_LENGTH            4
#define AX_TL_LENGTH                4
#define AX_VL_LENGTH                6
#define AX_CM_LENGTH                6
#define AX_CS_LENGTH                6
#define AX_CCW_CW_LENGTH            8
#define AX_BD_LENGTH                4
#define AX_TEM_LENGTH               4
#define AX_MOVING_LENGTH            4
#define AX_RWS_LENGTH               4
#define AX_VOLT_LENGTH              4
#define AX_LED_LENGTH               4
#define AX_TORQUE_LENGTH            4
#define AX_POS_LENGTH               4
#define AX_GOAL_LENGTH              5
#define AX_MT_LENGTH                5
#define AX_PUNCH_LENGTH             5
#define AX_SPEED_LENGTH             5
#define AX_GOAL_SP_LENGTH           7
#define AX_ACTION_CHECKSUM          250
#define BROADCAST_ID                254
#define AX_START                    255
#define AX_CCW_AL_L                 255
#define AX_CCW_AL_H                 3
#define TIME_OUT                    10         // Este parametro depende de la velocidad de transmision
#define TX_DELAY_TIME               400        // Este parametro depende de la velocidad de transmision - pero pueden ser cambiados para mayor velocidad.
#define TX_MODE                     1
#define RX_MODE                     0
#define LOCK                        1


//EEPROM AREA
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

// RAM AREA
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

    // Status Return Levels ///////////////////////////////////////////////////////////////
#define AX_RETURN_NONE              0
#define AX_RETURN_READ              1
#define AX_RETURN_ALL               2

    // Instruction Set ///////////////////////////////////////////////////////////////
#define AX_PING                     1
#define AX_READ_DATA                2
#define AX_WRITE_DATA               3
#define AX_REG_WRITE                4
#define AX_ACTION                   5
#define AX_RESET                    6
#define AX_SYNC_WRITE               131

    // Specials ///////////////////////////////////////////////////////////////

//TODO Add New Member Functions (Dynamixel and Polulo Wrappers)

/*
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
*/


#endif // ROVEWARE_CNTRLUTILS_H_
