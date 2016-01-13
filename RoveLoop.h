// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#pragma once
#ifndef ROVELOOP_H_
#define ROVELOOP_H_

#ifdef __cplusplus
extern "C" {
#endif

// ======== USING roveComm ========
//Cplus Public in roveWiresCplus.h
//roveComm::beginUdp(local_ip_addr, port);
//roveComm::readUdp(remote_ip_addr, "char_message");

//C Public as Cplus Private in roveComm.h
//int32_t roveComm_InitUdpCFG(&_udp_socket, (uint8_t*)my_ip_addr, (int32_t)port);
//int32_t roveComm_GetUdpMSG(&_udp_socket, &_udp_data);
// ========  =======  ========

// ======== USING roveControl ========
//Cplus Public in roveWiresCplus.h
//roveControl::BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin);

//C Public as Cplus Private in roveControl.h
//int32_t roveDynmxAx_InitCFG(&_rove_dynamxl, (uint8_t)dyna_id, serial_pin, tri_state_pin);
// ========  =======  ========

//Rtos Kernel Module Instance Api
#include <ti/sysbios/knl/Task.h>
//#include <ti/sysbios/knl/Swi.h>
//#include <ti/sysbios/knl/Clock.h>
//#include <ti/sysbios/knl/Semaphore.h>

Void roveLoop(UArg arg0, UArg arg1);

#ifdef __cplusplus
}
#endif

#endif // ROVELOOP





























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
