// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#pragma once
#ifndef ROVECONTROL_H_
#define ROVECONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

//C lib
#include <stdint.h>

//Rover Wrappers for Tiva C Connected
#include "../RoveBoard/RoveBoardPins.h"
/*
// TODO Judah Factor Out Dev Shorthand
//Public
// 12 bit for MX
// AX_12_SCALE_REG_MSB = 1023 clockwise direction is the 10th bit
// Which is likely why most savage electronics control schemes fail out erratically on the 12 bit mx series btw
typedef enum ROVECNTRL_DEV_16
{
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

//instance defintion
typedef struct rove_dyna_serial
{
    //Dynmxl AX12
    uint8_t dynmxl_id;
    roveUART_Handle uart;
    roveGPIO_Handle tri_state_buffer;
    uint8_t read_reply_flag;
    uint8_t reply_id;
    int32_t reply;
    int32_t err_no;
}__attribute__((packed)) rove_dyna_serial, *rove_dyna_serial_ptr;


#ifdef __cplusplus
// ========  roveControl  ========
// Cplus object wrappers
class RoveControl
{
    private:
        rove_dyna_serial _rove_dynamxl;

    public:
        RoveControl(int newId);
        ~RoveControl();

        int BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin);
        //TODO https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Constructor
        //BeginMx(serial_pin, dyna_id, baud_ra);
};// end class
#endif

int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

//WHEEL Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

//JOINT Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);
*/
#ifdef __cplusplus
}
#endif

#endif // ROVECONTROL_H_
