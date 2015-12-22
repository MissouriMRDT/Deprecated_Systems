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

// TODO Judah Factor Out Dev Shorthand
//Public
// 12 bit for MX
// AX_12_SCALE_REG_MSB = 1023 clockwise direction is the 10th bit
// Which is likely why most savage electronics control schemes fail out erratically on the 12 bit mx series btw
typedef enum ROVECNTRL_DEV_16 {

    CNTRLS_CUR_TODO_BOOKMRK_RET_ERRNO = 777

    , DEV16_NO_INSTRUCTION =          0x00
    , DEV16_TEST_INSTRUCTION =      0x01
    , DEV16_TEST_ERROR =            0x02

    //Dyna cntrl Flags
    , AX_ERROR =                    -1
    , AX_NO_PACKET =                0
    , AX_ERROR_FREE =               1
    , AX_PACKET =                   1

    , AX_READ_REPLY =               1
    , READ_ONE_BYTE_AX_REQ =        1
    , READ_TWO_BYTES_AX_REQ =       2

     //Dyna cfg
    , AX_MAX_READ_ATTMPT_CNT =      10
    , AX_MSG_MAX_BYTES =            20

    , AX_12_MAX_WHEEL_SPEED =       2047
    , AX_12_MAX_JOINT_SPEED =       1023

} ROVECNTRL_DEV_16;
int16_t roveDynmxAx_ScaleReg_ByAngleDegrees(int16_t joint_angle_degrees, int16_t scale_joint_reg_bias);
//end TODO


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

extern "C"
{
//config constructor
int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

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
int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

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
int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);
} // end extern "C"
//BEGIN JUDAH TODO factor MRDT shorthand
typedef struct rovecntrl_test_metrics {

    //negative sign cntrl values allowed
    int16_t min_speed;

    //negative sign cntrl values not allowed
    uint16_t max_speed;
    uint16_t speed_increment;

    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle_increment;

    uint32_t pause_microseconds;
} rovecntrl_test_metrics;

int32_t roveDynmxAx_TestWheelMode(rove_dyna_serial* dynmxl, rovecntrl_test_metrics* test);
int32_t roveDynmxAx_TestJointMode(rove_dyna_serial* dynmxl, rovecntrl_test_metrics* test);

#endif // ROVECONTROL_H_
