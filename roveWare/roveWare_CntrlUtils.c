// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_CntrlUtils.c
//
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
// mrdt::rovWare

#include "roveWare_CntrlUtils.h"

void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed){

    int16_t microseconds;

    //scale down to the final range to be between 1000 and 2000
    microseconds = speed / 2;

    //offset so that 1500 is neutral
    microseconds += 1500;

    //protect the upper bound on motor pulse width
    if (microseconds > 2000) {

        microseconds = 2000;

    }//endif

    //protect the lower bound on motor pulse width
    if (microseconds < 1000) {

        microseconds = 1000;

    }//endif

    rovePWM_Write(motor, microseconds);

    return;

} //endfnct roveDriveMotor_ByPWM

//TODO
void roveDynamixel_Rotate(uint8_t dynamixel_id, int tiva_pin, int16_t first_command_value, int16_t second_command_value) {

    rove_dynamixel_struct dynamixel;

    dynamixel.protocol_start_byte1 = DYMAMIXEL_MSG_START_BYTE;
    dynamixel.protocol_start_byte2 = DYMAMIXEL_MSG_START_BYTE;

    dynamixel.dynamixel_id = dynamixel_id;

    //TODO
    dynamixel.message_byte_count = 5;
    dynamixel.read_write_flag = DYNAMIXEL_WRITE_DATA;

    //TODO
    dynamixel.dynamixel_register_address = DYNAMIXEL_ROTATE_AT_SPEED_COMMAND;

    //dynamixel.register1_low_byte = (uint8_t)first_command_value;
    //dynamixel.register1_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.register2_low_byte = (uint8_t)second_command_value;
    dynamixel.register2_high_byte = (uint8_t)(second_command_value >> 8);

    //dynamixel.check_sum  = ( ~(dynamixel_id + SIX_BYTES + DYNAMIXEL_WRITE_DATA + dynamixel.dynamixel_register_address + dynamixel.register1_low_byte + dynamixel.register1_high_byte + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

    dynamixel.check_sum  = ( ~(dynamixel_id + dynamixel.message_byte_count + dynamixel.read_write_flag + dynamixel.dynamixel_register_address + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

    roveUART_Write(tiva_pin, (char*)&dynamixel, sizeof(dynamixel) );

    return;

}//end fnctn buildDynamixelStructMessage

//TODO
void roveDynamixel_SetWheelMode(uint8_t dynamixel_id, int tiva_pin, int16_t first_command_value, int16_t second_command_value) {

    rove_dynamixel_struct dynamixel;

    dynamixel.protocol_start_byte1 = DYMAMIXEL_MSG_START_BYTE;
    dynamixel.protocol_start_byte2 = DYMAMIXEL_MSG_START_BYTE;

    dynamixel.dynamixel_id = dynamixel_id;

    //TODO
    dynamixel.message_byte_count = 5;
    dynamixel.read_write_flag = DYNAMIXEL_WRITE_DATA;

    //TODO
    dynamixel.dynamixel_register_address = SET_WHEEL_MODE_CMD_REG_ADDR;

    //dynamixel.register1_low_byte = (uint8_t)first_command_value;
    //dynamixel.register1_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.register2_low_byte = (uint8_t)first_command_value;
    dynamixel.register2_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.check_sum  = ( ~(dynamixel_id + dynamixel.message_byte_count + dynamixel.read_write_flag + dynamixel.dynamixel_register_address + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

    roveUART_Write(tiva_pin, (char*)&dynamixel, sizeof(dynamixel) );

    return;

}//end fnctn buildDynamixelStructMessage


int16_t roveDynamixel_ConvertSpeed(int16_t dynamixel_rotate_at_speed){

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

        //TODO 1024 to 2048 is clockwise speed
        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed + 1024;

    }//endif

    return dynamixel_rotate_at_speed;

}//end fnctn

int16_t roveDynamixel_ReverseSpeed(int16_t dynamixel_rotate_at_speed){

    if(dynamixel_rotate_at_speed < 1024) {

        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed -1024;

    }else{

        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed + 1024;

    }//end if

    return dynamixel_rotate_at_speed;

}//end fnctn

void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed){

    linear_actuator_struct linear_actuator;

    if( speed > 0 ){

        linear_actuator.command_byte = LIN_ACT_FORWARD;

    }else{

        linear_actuator.command_byte = LIN_ACT_REVERSE;

    }//end if


    //bit of an ugly hack to have called this whole int16_t speed
    linear_actuator.speed = (uint8_t)speed;

    roveUART_Write(tiva_pin, (char*)&linear_actuator, sizeof(linear_actuator) );

    return;

}//endfnctn roveDrivePolulu_LinActCmd


