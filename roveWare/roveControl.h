// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// Public interface for Control Utilities for URC 2016
//
//mrdt::rovWare
#ifndef ROVECONTROL_H_
#define ROVECONTROL_H_

//C lib
#include <stdint.h>

//mrdt definitions
#include "roveBoard/roveBOARD_TIVA1294.h"

//instance defintion
typedef struct rove_dyna_serial {

    //Dynmxl AX12
    uint8_t dynmxl_id;
    roveUART_Handle uart;
    roveGPIO_Handle tri_state_buffer;

    uint8_t read_reply_flag;
    uint8_t reply_id;
    int32_t reply;
    int32_t err_no;

}__attribute__((packed)) rove_dyna_serial, *rove_dyna_serial_ptr;

//config constructor
int32_t roveDynmxl_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);



//WHEEL mode
    //////////speed schema -> rpm
            //range: 0~2047( 0X7FF)
            //unit:  0.1%.
            //speed = 0 Full Reverse
            //speed = 1023 = 1024 Full Stop
            //speed = 1025~2047 Full forward
            //i.e. speed = 512 means 50% of max motor output in reverse
    //angle schema = undefined -> has no affect

//WHEEL Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxl_SetWheelModeCFG( rove_dyna_serial* dynmxl);
int32_t roveDynmxl_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
int32_t roveDynmxl_ReadWheelREQ(rove_dyna_serial* dynmxl);
int32_t roveDynmxl_TestWheelMode(rove_dyna_serial* dynmxl, uint32_t pause_microseconds);



//JOINT mode
    //////////speed schema-> rpm
            //range:  0~1023 (0X3FF)
            //unit:   0.111rpm
            //speed =  0 = 1024 is max rpm of the motor (114rpm)
            //speed =  1~1023 (up to 114rpm)
            //ie: speed = 300 is about 33.3 rpm
    //angle schema -> 10 bit absolute joint position (Goal Position): dead band at 300-360 degrees
            //range:   0~1023 (0x3FF)
            //unit:    0.29 degree
            //ie: angle = 1024 is 300 degree

//JOINT Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxl_SetJointModeCFG(rove_dyna_serial* dynmxl);
int32_t roveDynmxl_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
int32_t roveDynmxl_ReadJointREQ(rove_dyna_serial* dynmxl);
int32_t roveDynmxl_TestJointMode(rove_dyna_serial* dynmxl, uint32_t pause_microseconds);

#endif // ROVECONTROL_H_
