// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#ifndef ROVECNTRL_H_
#define ROVECNTRL_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../RoveBoard/RoveBoard.h"

//Todo: MOVE TO SEPERATE FILE
//standard rcservo : 1000uS full reverse : 1500uS stop : 2000uS full forward
void roveCntrl_RcServo_Spin(PWM_Handle motor, int16_t speed);

#ifdef __cplusplus
}
#endif

#endif // ROVECNTRL_H_

//TODO Code Review

/*
typedef enum {
  AX,
  MX
} DynamixelType;

typedef enum {
  Wheel = 0,
  Joint = 1,
  MultiTurn = 2
} DynamixelMode;

typedef struct {
  uint8_t id;
  DynamixelType type;
  roveUART_Handle uart;
} Dynamixel;

typedef enum {
  DYNAMIXEL_ERROR_SUCCESS = 0,
  DYNAMIXEL_ERROR_VOLTAGE = 1,
  DYNAMIXEL_ERROR_ANGLE_LIMIT = 2,
  DYNAMIXEL_ERROR_OVERHEATING = 4,
  DYNAMIXEL_ERROR_RANGE = 8,
  DYNAMIXEL_ERROR_CHECKSUM = 16,
  DYNAMIXEL_ERROR_OVERLOAD = 32,
  DYNAMIXEL_ERROR_UNKNOWN = 64
} Dynamixel_Error;

void DynamixelInit(Dynamixel* dyna, DynamixelType type, uint8_t id, uint8_t uartIndex, int baud);

void DynamixelSendPacket(Dynamixel dyna, uint8_t length, uint8_t* instruction);
uint8_t DynamixelGetReturnPacket(Dynamixel dyna, uint8_t* buffer, size_t bufferSize);
uint8_t DynamixelGetError(Dynamixel dyna);

uint8_t DynamixelPing(Dynamixel dyna);
uint8_t DynamixelSetId(Dynamixel* dyna, uint8_t id);

uint8_t DynamixelMoveTo(Dynamixel dyna, uint16_t position);
uint8_t DynamixelTurnAt(Dynamixel dyna, uint16_t position, uint16_t speed);

uint8_t DynamixelSetStatusReturnLevel(Dynamixel dyna, uint8_t level);
uint8_t DynamixelSetMode(Dynamixel dyna, DynamixelMode mode);

uint8_t DynamixelGetMode(Dynamixel dyna, DynamixelMode* mode);
uint8_t DynamixelGetPresentPosition(Dynamixel dyna, uint16_t* pos);
uint8_t DynamixelGetPresentSpeed(Dynamixel dyna, uint16_t* speed);
uint8_t DynamixelGetLoad(Dynamixel dyna, uint16_t* load);
uint8_t DynamixelGetVoltage(Dynamixel dyna, uint8_t* voltage);
uint8_t DynamixelGetTemperature(Dynamixel dyna, uint8_t* temp);

// Instructions
#define DYNAMIXEL_PING                     1
#define DYNAMIXEL_READ_DATA                2
#define DYNAMIXEL_WRITE_DATA               3
#define DYNAMIXEL_REG_WRITE                4
#define DYNAMIXEL_ACTION                   5
#define DYNAMIXEL_RESET                    6

// Sets poll for response timeout
#define TXDELAY 2000

// DYNAMIXEL EEPROM AREA
#define DYNAMIXEL_MODEL_NUMBER_L           0
#define DYNAMIXEL_MODEL_NUMBER_H           1
#define DYNAMIXEL_VERSION                  2
#define DYNAMIXEL_ID                       3
#define DYNAMIXEL_BAUD_RATE                4
#define DYNAMIXEL_RETURN_DELAY_TIME        5
#define DYNAMIXEL_CW_ANGLE_LIMIT_L         6
#define DYNAMIXEL_CW_ANGLE_LIMIT_H         7
#define DYNAMIXEL_CCW_ANGLE_LIMIT_L        8
#define DYNAMIXEL_CCW_ANGLE_LIMIT_H        9
#define DYNAMIXEL_LIMIT_TEMPERATURE        11
#define DYNAMIXEL_DOWN_LIMIT_VOLTAGE       12
#define DYNAMIXEL_UP_LIMIT_VOLTAGE         13
#define DYNAMIXEL_MAX_TORQUE_L             14
#define DYNAMIXEL_MAX_TORQUE_H             15
#define DYNAMIXEL_RETURN_LEVEL             16
#define DYNAMIXEL_ALARM_LED                17
#define DYNAMIXEL_ALARM_SHUTDOWN           18
//Todo: ////////////////////////////////////////////19&23?
// MX SERIES EEPROM
#define MX_MULTI_TURN_OFFSET_L             20
#define MX_MULTI_TURN_OFFSET_H             21
#define MX_RESOLUTION_DIVIDER              22
//////////////////////////////////////////////////////////
// DYNAMIXEL RAM AREA
#define DYNAMIXEL_TORQUE_ENABLE            24
#define DYNAMIXEL_LED                      25

// AX SERIES RAM
#define AX_CW_COMPLIANCE_MARGIN            26
#define AX_CCW_COMPLIANCE_MARGIN           27
#define AX_CW_COMPLIANCE_SLOPE             28
#define AX_CCW_COMPLIANCE_SLOPE            29
//Todo: ////////////////////////////////////////////29?
// MX SERIES RAM
#define MX_D_GAIN                          26
#define MX_I_GAIN                          27
#define MX_P_GAIN                          28

#define DYNAMIXEL_GOAL_POSITION_L          30
#define DYNAMIXEL_GOAL_POSITION_H          31
#define DYNAMIXEL_MOVING_SPEED_L           32
#define DYNAMIXEL_MOVING_SPEED_H           33
#define DYNAMIXEL_TORQUE_LIMIT_L           34
#define DYNAMIXEL_TORQUE_LIMIT_H           35
#define DYNAMIXEL_PRESENT_POSITION_L       36
#define DYNAMIXEL_PRESENT_POSITION_H       37
#define DYNAMIXEL_PRESENT_SPEED_L          38
#define DYNAMIXEL_PRESENT_SPEED_H          39
#define DYNAMIXEL_PRESENT_LOAD_L           40
#define DYNAMIXEL_PRESENT_LOAD_H           41
#define DYNAMIXEL_PRESENT_VOLTAGE          42
#define DYNAMIXEL_PRESENT_TEMPERATURE      43
#define DYNAMIXEL_REGISTERED_INSTRUCTION   44
#define DYNAMIXEL_MOVING                   46
#define DYNAMIXEL_LOCK                     47
#define DYNAMIXEL_PUNCH_L                  48
#define DYNAMIXEL_PUNCH_H                  49
//Todo: ////////////////////////////////////////////WHAT IS THIS//MX ONLY Mode!!
#define MX_GOAL_ACCELERATION               73

#define MX_HIGH_BYTE_MASK                  0x0F
#define AX_HIGH_BYTE_MASK                  0x03


#ifdef __cplusplus
}
#endif

#endif // ROVECONTROL_H_



// roveWare Upgrades Version 2 Release



//Standard C lib
//#include <stdint.h>
//Rover Wrappers for hardware specific microcontroller pin protocol drivers
//#include "../RoveBoard/RoveBoardPins.h"


//TODO Judah Factor Out Dev Shorthand
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




/*Todo Test Suite
int testWheelMode(int min_speed, int max_speed, int speed_increment, int pause_microseconds);
int testJointMode(int min_angle, int max_angle, int angle_increment, int speed, int pause_microseconds);

int RoveControl::testWheelMode(int min_speed, int max_speed, int speed_increment, int pause_microseconds)
{
    //TODO
    test_metrics test;
    return roveDynmxAx_TestWheelMode(&_rove_dynamxl, &test);
}// end method
int RoveControl::testJointMode(int min_angle, int max_angle, int angle_increment, int speed, int pause_microseconds)
{
    //TODO
    test_metrics test;
    return roveDynmxAx_TestJointMode(&_rove_dynamxl, &test);
}// end method



int32_t roveDynmxAx_TestWheelMode(rove_dyna_serial* dynmxl, test_metrics* test);
int32_t roveDynmxAx_TestJointMode(rove_dyna_serial* dynmxl, test_metrics* test);

int32_t roveDynmxAx_TestWheelMode(rove_dyna_serial* dynmxl, test_metrics* test)
{
    if( roveDynmxAx_SetWheelModeCFG(dynmxl) )
    {
        printf("Dev16 Error roveDynmxAx_SetWheelModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    if( roveDynmxAx_SetWheelModeCFG(dynmxl) )
    {
        printf("Dev16 Error roveDynmxAx_SetWheelModeCFG ldynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    int16_t speed = 0;

    //ramp up from zero to max forward
    for (speed = 0; speed < test->max_speed; speed += test->speed_increment)
    {
        //TODO arg2 could be negative??
        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        //roveBoard_DelayMilliSec(test->pause_microseconds);
    } //end for

    //ramp back from max forward through zero to max reverse
    for (speed = test->max_speed; speed > test->min_speed; speed -= test->speed_increment)
    {
        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        //roveBoard_DelayMilliSec(test->pause_microseconds);
    } //end for

    //ramp back from max reverse landing on zero
    for (speed = test->min_speed; speed < 0; speed += test->speed_increment)
    {
        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        }//endif

        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        //roveBoard_DelayMilliSec(test->pause_microseconds);
    } //end for

    //roveBoard_DelayMilliSec(4*test->pause_microseconds);
    return AX_ERROR_FREE;
};//end fnctn*/


/*
int32_t roveDynmxAx_TestJointMode(rove_dyna_serial* dynmxl, test_metrics* test)
{
    if( roveDynmxAx_SetJointModeCFG(dynmxl))
    {
        printf("Dev16 Error roveDynmxAx_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    if(roveDynmxAx_SetJointModeCFG(dynmxl))
    {
        printf("Dev16 Error roveDynmxAx_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    //catch dynamixel joint api confusion
    if(test->min_speed > test->max_speed)
    {
        printf("test->min_speed > test->max_speed Dev16 Error roveDynmxAx_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//end if

    //joint mode only takes positive speeds
    if(test->min_speed < 0)
    {
        test->min_speed = 0;
    }//end if

    //joint mode only takes positive speeds
    if(test->max_speed > AX_12_MAX_JOINT_SPEED)
    {
       test->max_speed = AX_12_MAX_JOINT_SPEED;
    }//end if

    uint16_t speed = 0;

    for (speed = test->min_speed; speed < test->max_speed; speed += test->speed_increment)
    {
        uint16_t angle = 0;

        for (angle = test->min_angle; angle < test->max_angle; angle += test->angle_increment)
        {
            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
                return AX_ERROR;
            }//endif

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
                return AX_ERROR;
            }//endif

            //roveBoard_DelayMilliSec(test->pause_microseconds);
        } //end for

        for (angle = test->max_angle; angle > test->min_angle; angle -= test->angle_increment)
        {

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            //roveBoard_DelayMilliSec(test->pause_microseconds);
        } //end for

        for (angle = test->min_angle; angle < test->max_angle; angle += test->angle_increment) {

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed)){
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed)){
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            //roveBoard_DelayMilliSec(test->pause_microseconds);
        } //end for

    } //end for

    //oveBoard_DelayMilliSec(4*test->pause_microseconds);
    return AX_ERROR_FREE;
};//end fnctn
*/
