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

void do_nothing(){

    int i = 0;

    while(i < DO_NOTHING_CNT){

        i++;

    }//endwhile

    return;

}//end fnctn

int getDevicePort(uint8_t device_id)
{
    switch(device_id)
    {
        case WRIST_A_ID...BASE_ID:

        //return DYNAMIXEL_UART;
        return ARM_UART;

        case LIN_ACT_ID:

        //return LINEAR_ACTUATOR_UART;
        return LIN_ACT_UART;

        case GRIPPER_ID:

        //return END_EFFECTOR_UART;
        return END_EFX_UART;

        case DRILL_ID:

        //return END_EFFECTOR_UART;
        return END_EFX_UART;

        default:
            printf("getDevicePort passed invalid device_id %d\n", device_id);;
        return -1;

    }//endswitch (device)

}//endfnctn getDevicePort

int getStructSize(uint8_t struct_id)
{
    switch(struct_id)
    {
        case SET_ENDLESS_CMD:

            return sizeof(set_dyna_endless_struct);

        case SET_SPEED_LEFT_CMD...SET_SPEED_RIGHT_CMD:

            return sizeof(set_dyna_speed_struct);

        case SET_LIN_ACTUATOR_CMD:

            return sizeof(linear_actuator_struct);

        case GET_DRILL_CMD:

            return sizeof(drill_struct);

        default:
            printf("getStructSize passed invalid struct_id %d\n", struct_id);
        return -1;

    }//endswitch

}//endfnctn getDevicePort

//right is forward
void roboArmForwardCmd(uint8_t struct_id, int16_t speed)
{
    switch(struct_id)
    {
        case wrist_clock_wise:

            dynamixelSetSpeedRightCmd(WRIST_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);
            break;

        case wrist_up:

            dynamixelSetSpeedRightCmd(WRIST_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);
            break;

        case elbow_clock_wise:

            dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);
            break;

        case elbow_up:

            dynamixelSetSpeedLeftCmd(ELBOW_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);
            break;

        case base_clock_wise:

            dynamixelSetSpeedRightCmd(BASE_ID, speed);
            break;

        case gripper_open:

            dynamixelSetSpeedRightCmd(GRIPPER_ID, speed);
            break;

        default:
            printf("\nERROR in RoboticArm.c!   roboArmForwardCmd struct_id %d cannot be handled \n", struct_id);
            return;

    }//endswitch struct_id

    return;

}//endfnctn roboArmForwardCmd

//left is reverse
void roboArmReverseCmd(uint8_t struct_id, int16_t speed)
{
    switch(struct_id)
    {
        //reverse (left) clockwise is counterclockwise
        case wrist_clock_wise:

            dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedLeftCmd(WRIST_B_ID, speed);
            break;

        case wrist_up:

            dynamixelSetSpeedLeftCmd(WRIST_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedRightCmd(WRIST_B_ID, speed);
            break;

        //reverse (left) clockwise is counterclockwise
        case elbow_clock_wise:

            dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedRightCmd(ELBOW_B_ID, speed);
            break;

        //reverse (left) up is down
        case elbow_up:

            dynamixelSetSpeedRightCmd(ELBOW_A_ID, speed);
            do_nothing();
            dynamixelSetSpeedLeftCmd(ELBOW_B_ID, speed);
            break;

        //reverse (left) clockwise is counterclockwise
        case base_clock_wise:

            dynamixelSetSpeedLeftCmd(BASE_ID, speed);
            break;

        case gripper_open:

            dynamixelSetSpeedLeftCmd(GRIPPER_ID, speed);
            break;

        default:

            printf("\nERROR in RoboticArm.c!  roboArmReverseCmd  struct_id %d cannot be handled \n", struct_id);

            return;

    }//endswitch struct_id

    return;

}//endfnctn roboArmReverseCmd

void dynamixelSetEndlessCmd(uint8_t dynamixel_id)
{
        char write_buffer[BUFFER_SIZE];

        int device_port;
        int bytes_to_write;

        // get the uart
        device_port = getDevicePort(dynamixel_id);

        // size of message
        bytes_to_write = getStructSize(SET_ENDLESS_CMD);

        // populate the buffer_struct for dynamixel format frame, command_value not used
        buildDynamixelStructMessage(write_buffer, dynamixel_id, SET_ENDLESS_CMD, NULL_COMAND_VALUE);

        bytes_to_write = deviceWrite(device_port, write_buffer, bytes_to_write);

        return;

}//endfnctn  dynamixelSetEndless

void dynamixelSetSpeedLeftCmd(uint8_t dynamixel_id, int16_t speed)
{
        char write_buffer[BUFFER_SIZE];

        int device_port;
        int bytes_to_write;

        //get the uart
        device_port = getDevicePort(dynamixel_id);

        //size of message
        bytes_to_write = getStructSize(SET_SPEED_LEFT_CMD);

        // populate the buffer_struct for dynamixel format frame
        buildDynamixelStructMessage(write_buffer, dynamixel_id, SET_SPEED_LEFT_CMD, speed);

        bytes_to_write = deviceWrite(device_port, write_buffer, bytes_to_write);

        return;

}//endfnctn  dynamixelSetSpeedLeftCmd

void dynamixelSetSpeedRightCmd(uint8_t dynamixel_id, int16_t speed)
{
        char write_buffer[BUFFER_SIZE];

        int device_port;
        int bytes_to_write;

        //get the uart
        device_port = getDevicePort(dynamixel_id);

        //size of message
        bytes_to_write = getStructSize(SET_SPEED_RIGHT_CMD);

        // populate the buffer_struct for dynamixel format frame
        buildDynamixelStructMessage(write_buffer, dynamixel_id, SET_SPEED_RIGHT_CMD, speed);

        bytes_to_write = deviceWrite(device_port, write_buffer, bytes_to_write);

        return;

}//endfnctn  dynamixelSetSpeedRightCmd

void setLinActuatorCmd(uint8_t device_id, int16_t speed)
{
        char write_buffer[BUFFER_SIZE];

        int device_port;
        int bytes_to_write;

        // get the uart
        device_port = getDevicePort(device_id);

        // size of message
        bytes_to_write = getStructSize(SET_LIN_ACTUATOR_CMD);

        // populate the buffer_struct for dynamixel format frame
        buildLinActuatorStructMessage(write_buffer, SET_LIN_ACTUATOR_CMD, speed);

        bytes_to_write = deviceWrite(device_port, write_buffer, bytes_to_write);

        return;

}//endfnctn  setActuatorCmd

void setDrillCmd(uint8_t device_id, int16_t command)
{
        char write_buffer[BUFFER_SIZE];

        int device_port;
        int bytes_to_write;

        // get the uart
        device_port = getDevicePort(device_id);

        // size of message
        bytes_to_write = getStructSize(GET_DRILL_CMD);

        //populate message stop = 0x00, forward = 0x01, reverse = 0x02
        SET_DRILL_STRUCT->command_byte = command;

        bytes_to_write = deviceWrite(device_port, write_buffer, bytes_to_write);

        return;

}//endfnctn  setActuatorCmd

//see roveStructs.h and rovWare.h for config
void buildDynamixelStructMessage(char* write_buffer, uint8_t dynamixel_id, uint8_t struct_id, int16_t command_value)
{
    uint8_t speed_low_byte = (uint8_t)command_value;
    uint8_t speed_high_byte = (uint8_t)(command_value >> 8);

    switch(struct_id)
    {
        case SET_ENDLESS_CMD:

            // macro casting the buffer_struct instance see roveWare.h and roveStruct.h
            SET_ENDLESS_STRUCT->start_byte1 = AX_START;
            SET_ENDLESS_STRUCT->start_byte2 = AX_START;
            SET_ENDLESS_STRUCT->dynamixel_id = dynamixel_id;
            SET_ENDLESS_STRUCT->msg_size = AX_GOAL_LENGTH;
            SET_ENDLESS_STRUCT->read_write_flag = AX_WRITE_DATA;
            SET_ENDLESS_STRUCT->ccw_angle_limit_reg_addr = AX_CCW_ANGLE_LIMIT_L;
            SET_ENDLESS_STRUCT->ccw_angle_limit_low_byte = 0x00;
            SET_ENDLESS_STRUCT->ccw_angle_limit_high_byte = 0x00;

            SET_ENDLESS_STRUCT->check_sum = ( ~(dynamixel_id + AX_GOAL_LENGTH + AX_WRITE_DATA + AX_CCW_ANGLE_LIMIT_L) ) & 0xFF;
            break;

        case SET_SPEED_LEFT_CMD:

            // macro casting the buffer_struct instance see roveWare.h and roveStruct.h
            SET_DYNA_SPEED_STRUCT->start_byte1 = AX_START;
            SET_DYNA_SPEED_STRUCT->start_byte2 = AX_START;
            SET_DYNA_SPEED_STRUCT->dynamixel_id = dynamixel_id;
            SET_DYNA_SPEED_STRUCT->msg_size = AX_SPEED_LENGTH;
            SET_DYNA_SPEED_STRUCT->read_write_flag = AX_WRITE_DATA;
            SET_DYNA_SPEED_STRUCT->speed_low_byte_reg_addr = AX_GOAL_SPEED_L;
            SET_DYNA_SPEED_STRUCT->speed_low_byte = speed_low_byte;
            SET_DYNA_SPEED_STRUCT->speed_high_byte = speed_high_byte;

            SET_DYNA_SPEED_STRUCT->check_sum  = ( ~(dynamixel_id + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + speed_low_byte + speed_high_byte) ) & 0xFF;
            break;

        case SET_SPEED_RIGHT_CMD:

            // macro casting the buffer_struct instance see roveWare.h and roveStruct.h
            SET_DYNA_SPEED_STRUCT ->start_byte1 = AX_START;
            SET_DYNA_SPEED_STRUCT ->start_byte2 = AX_START;
            SET_DYNA_SPEED_STRUCT ->dynamixel_id = dynamixel_id;
            SET_DYNA_SPEED_STRUCT ->msg_size = AX_SPEED_LENGTH;
            SET_DYNA_SPEED_STRUCT ->read_write_flag = AX_WRITE_DATA;
            SET_DYNA_SPEED_STRUCT ->speed_low_byte_reg_addr = AX_GOAL_SPEED_L;
            SET_DYNA_SPEED_STRUCT ->speed_low_byte = speed_low_byte;
            SET_DYNA_SPEED_STRUCT ->speed_high_byte = (speed_high_byte + 4);

            SET_DYNA_SPEED_STRUCT->check_sum = ( ~(dynamixel_id + AX_SPEED_LENGTH + AX_WRITE_DATA + AX_GOAL_SPEED_L + speed_low_byte + speed_high_byte + 4) ) & 0xFF;
            break;

        default:
                printf("Error in function: buildDynamixelStructMessage() - struct_id is not valid\n");

        }//endswitch

    return;

}//end fnctn buildDynamixelStructMessage

//current_position = buildLinActuatorMessage((void*)(&buffer_struct), write_buffer, device_id, current_position, target_increment);

void buildLinActuatorStructMessage(char* write_buffer, uint8_t struct_id, int16_t speed)
{
    switch(struct_id)
    {
        case SET_LIN_ACTUATOR_CMD:

            if (speed > MAX_LIN_ACT_SPEED)
            {
                speed = MAX_LIN_ACT_SPEED;

            }//endif

            if (speed < MIN_LIN_ACT_SPEED)
            {
                speed = MIN_LIN_ACT_SPEED;

            }//endif

            SET_LIN_ACT_STRUCT->command_byte = LIN_ACT_FORWARD;

            if (speed < 0)
            {
                speed = -speed;
                SET_LIN_ACT_STRUCT->command_byte = LIN_ACT_REVERSE;

            }//endif

            SET_LIN_ACT_STRUCT->speed = (uint8_t)speed;
        break;
        default:
            printf("Error in function: buildDynamixelStructMessage() - struct_id is not valid");

    }//endswitch

    return;

}//end fnctn buildLinActuatorStructMessage




/////////////////////////////////END RoboArmHoroizon



/////////////////////////////////BEGIN RoboArm2016

/*
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
    dynamixel.message_byte_count = FOUR_BYTES;
    dynamixel.read_write_flag = DYNAMIXEL_WRITE_DATA;

    //TODO
    dynamixel.dynamixel_register_address = ROTATE_TO_POSITION_CMD_REG_ADDR;

    dynamixel.register1_low_byte = (uint8_t)first_command_value;
    dynamixel.register1_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.register2_low_byte = (uint8_t)second_command_value;
    dynamixel.register2_high_byte = (uint8_t)(second_command_value >> 8);

    dynamixel.check_sum  = ( ~(dynamixel_id + FOUR_BYTES + DYNAMIXEL_WRITE_DATA + dynamixel.dynamixel_register_address + dynamixel.register1_low_byte + dynamixel.register1_high_byte + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

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

*/

//This is where the function library porting goes:

//int DynamixelClass::setEndless(unsigned char ID, bool Status)

//Runtime Command to turn on and off endless rotation ( maaaybeee feeels a bit liiike Open Loop emulation)



