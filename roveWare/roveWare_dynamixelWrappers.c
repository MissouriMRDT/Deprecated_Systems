// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// Dynamixel Wrapper on URC 2015 Horizon Protocol
//
// mrdt::rovWare

#include "roveWare_dynamixelWrappers.h"

//TODO
void roveDynamixel_Command(int tiva_pin, int16_t command_type, uint8_t dynamixel_id, int16_t first_command_value, int16_t second_command_value) {

    rove_dynamixel_struct dynamixel;

    dynamixel.protocol_start_byte1 = DYMAMIXEL_MSG_START_BYTE;
    dynamixel.protocol_start_byte2 = DYMAMIXEL_MSG_START_BYTE;

    dynamixel.dynamixel_id = dynamixel_id;

    dynamixel.message_byte_count = FOUR_BYTES;
    dynamixel.read_write_flag = DYNAMIXEL_WRITE_DATA;

    dynamixel.dynamixel_register_address = (uint8_t)command_type;

    dynamixel.register1_low_byte = (uint8_t)first_command_value;
    dynamixel.register1_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.register2_low_byte = (uint8_t)second_command_value;
    dynamixel.register2_high_byte = (uint8_t)(second_command_value >> 8);


    dynamixel.check_sum  = ( ~(dynamixel_id + FOUR_BYTES + DYNAMIXEL_WRITE_DATA + dynamixel.dynamixel_register_address + dynamixel.register1_low_byte + dynamixel.register1_high_byte + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

    roveUART_Write(tiva_pin, (char*)&dynamixel, sizeof(dynamixel) );

    return;

}//end fnctn buildDynamixelStructMessage

int16_t roveConverRedProtocol_toDynamixelSpeed(int16_t dynamixel_rotate_at_speed){

    if(dynamixel_rotate_at_speed < DYNAMIXEL_SPEED_MIN) {

        dynamixel_rotate_at_speed = DYNAMIXEL_SPEED_MIN;

    }//end if

    if(dynamixel_rotate_at_speed > DYNAMIXEL_SPEED_MAX) {

        dynamixel_rotate_at_speed = DYNAMIXEL_SPEED_MAX;

    }//end if

    //dynamixel internal protocol
    if(dynamixel_rotate_at_speed < 0) {

        //0 to 1024 is counterclockwise speed
        dynamixel_rotate_at_speed = -dynamixel_rotate_at_speed;

    }else{

        //1024 to 2048 is clockwise speed
        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed + 1024;

    }//endif

    return dynamixel_rotate_at_speed;

}//end fnctn

int16_t roveReverseDynamixelSpeed(int16_t dynamixel_rotate_at_speed){

    if(dynamixel_rotate_at_speed < 1024) {

        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed -1024;

    }else{

        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed + 1024;

    }//end if

    return dynamixel_rotate_at_speed;

}//end fnctn


/*   AX   12 Savage Electronics
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


#define OFF                         0
#define ON                          1

#define LEFT                        0
#define RIGTH                       1

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
#define Tx_MODE                     1
#define Rx_MODE                     0
#define LOCK                        1

*/
