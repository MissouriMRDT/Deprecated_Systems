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

} rove_dynamixel_struct, *rove_dynamixel_struct_ptr;


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

void roveDynamixel_DualCommand(int tiva_pin, int16_t command_type, uint8_t dynamixel_id, int16_t first_command_value, int16_t second_command_value);

#endif // ROVEWARE_DYNAMIXELWRAPPERS_H_
