// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveDevice_Thread.c
//
// jrs6w7@mst.edu
//
// TODO FALL_2015 V1 - for URC 2016 IP Server -> PWM / UART / Device Controller Template
//
// C interface for a TexInst TIVA RTOS TASK Thread with private stack / signal
//
// Using Texas Instruments Code Composer Studio RTOS stack instatiates the roveDevice_Thread.c
//
// This is found in the tivaRtscJS.cfg[TI-RTOS] Javascript Gui/Script tab at the bottom of Projece Explorer Folders
//
// recieves base station messages using ip bsd style sockets and issues logic commands to hardware
//
// mrdt::rovWare
#include "roveDevice_Thread.h"
///////////////BEGIN 2016//////DEVICE THREAD//////////////
void roveDeviceThread(UArg arg0, UArg arg1) {

    //developement notes:
    //TODO eliminate struct patterns in favor of local variables?
    //Or just go other way and add C++ Wrappers Inside of CCS?
    //straight embedded static function jump table lookups?

    //device notes:
    //WARNING!! in Wheel Mode, the savage_electronics::Dynamixel.move() function has no effect only Dynamixel.turn() works
    //joint_position goal angle in "wheel mode" is always seen as zero = infinite and ONLY the goal speed matters
    printf("Init roveDevice_TemplateThread Arm Dyna Tester\n\n\n");

///////////////BEGIN 2016//////NETWORKING///////////////////
    //open a tiva ndk socket session in this task stack
    fdOpenSession( TaskSelf() );

/////////////////TODO base_station.local_ip_addr.port.subscribers[ip_addrs++] = rovecommInit(LOCAL_IP_ADDRESS, PORT, &base_station, state);
    //init roveComm
    rove_udp_socket base_station;
    roveComm_Init(&base_station);

///////////////BEGIN 2016//////Dynamixel Serial//////////////
    rove_dyna_serial_port left_wrist;
    rove_dyna_serial_port right_wrist;

    left_wrist.error_flag = NO_ERRORS;
    left_wrist.dynamixel_id = 0x00;
    left_wrist.tiva_pin = roveGetPinNum_ByDeviceId(0x00);
    left_wrist.listen_for_reply_flag = DONT_LISTEN_FOR_REPLY;

    right_wrist.error_flag = NO_ERRORS;
    right_wrist.dynamixel_id = 0x01;
    right_wrist.tiva_pin = roveGetPinNum_ByDeviceId(0x01);
    right_wrist.listen_for_reply_flag = DONT_LISTEN_FOR_REPLY;

    //BOTH wheel AND joint mode AX12:(WHEEL GoalSpeed :0~2047/0X7FF unit:0.1%):(JOINT GoalSpeed: 0~1023/0X3FF unit: 0.111rpm)
    int16_t speed = 0;

    //ONLY joint mode AX12:(JOINT GoalPosition:0~1023/0x3FF) at 0.29 degree
    int16_t angle = 0;

///////////////BEGIN 2016//////MOTOR TEST ROUTINE/////////////
    while (FOREVER) {

//TODO Base Station define Data Id's Cmd Proto Integration
        if( roveGet_UdpMsg(&base_station.data_id, &base_station.data_byte_cnt, &base_station) < SINGLE_BYTE ) {
            printf("ZERO bytes from getUdpMsg\n");
        } else {

//TEST WHEEL mode
//////////speed schema -> rpm
        //range: 0~2047( 0X7FF)
        //unit:  0.1%.
        //speed = 0 Full Reverse
        //speed = 1023 = 1024 Full Stop
        //speed = 1025~2047 Full forward

///////////angle schema = undefined -> has no affect
        //i.e. speed = 512 means 50% of max motor output in reverse
        roveDynamixel_SetWheelModeCFG(&left_wrist);
        roveDynamixel_SetWheelModeCFG(&right_wrist);

        //roveDynamixel_SpinWheelCMD::->if(spin_wheel_direction > 0) wheel_speed += (1 >> 10);
        //ramp up from zero to max forward
        for (speed = 0; speed < 1000; speed += 50) {

            //TODO arg2 could be negative??
            roveDynamixel_SpinWheelCMD(&left_wrist, speed);
            roveDynamixel_SpinWheelCMD(&right_wrist, speed);
            roveDelay_MilliSec(500);
        } //end for

        //ramp back from max forward through zero to max reverse
        for (speed = 1000; speed > -1000; speed -= 50) {

            //TODO arg2 could be negative
            roveDynamixel_SpinWheelCMD(&left_wrist, speed);
            roveDynamixel_SpinWheelCMD(&right_wrist, speed);
            roveDelay_MilliSec(500);
        } //end for

        //ramp back from max reverse landing on zero
        for (speed = -1000; speed < 0; speed += 50) {

            //TODO arg2 could be negative
            roveDynamixel_SpinWheelCMD(&left_wrist, speed);
            roveDynamixel_SpinWheelCMD(&right_wrist, speed);
            roveDelay_MilliSec(500);
        } //end for

//TODO:  #define and scale speed < 1000; speed += 50

//::END TEST WHEEL mode
        roveDelay_MilliSec(20000);
//TEST JOINT mode
//////////speed schema-> rpm
        //range:  0~1023 (0X3FF)
        //unit:   0.111rpm
        //speed =  0 = 1024 is max rpm of the motor (114rpm)
        //speed =  1~1023 (up to 114rpm)
        //ie: speed = 300 is about 33.3 rpm

//////////angle schema -> 10 bit absolute joint position (Goal Position): dead band at 300-360 degrees
        //range:   0~1023 (0x3FF)
        //unit:    0.29 degree
        //ie: angle = 1024 is 300 degree
        roveDynamixel_SetJointModeCFG(&left_wrist);
        roveDynamixel_SetJointModeCFG(&right_wrist);

        //very slowly now
        speed = 10;
        for (angle = 0; angle < 1000; angle += 50) {

            roveDynamixel_RotateJointCMD(&left_wrist, angle, speed);
            roveDynamixel_RotateJointCMD(&right_wrist, angle, speed);
            roveDelay_MilliSec(500);
        } //end for

        for (angle = 1000; angle > 0; speed -= 50) {

            roveDynamixel_RotateJointCMD(&left_wrist, angle, speed);
            roveDynamixel_RotateJointCMD(&right_wrist, angle, speed);
            roveDelay_MilliSec(500);
        } //end for

        for (speed = 0; speed < 500; speed += 50) {

            roveDynamixel_RotateJointCMD(&left_wrist, angle, speed);
            roveDynamixel_RotateJointCMD(&right_wrist, angle, speed);
            roveDelay_MilliSec(500);
        } //end for

        //END TEST JOINT mode
        roveDelay_MilliSec(20000);
//::END2016 MOTOR TEST ROUTINE

//////////////REPEAT 2016//////MOTOR TEST FOREVER/////////////
    }//endwhile FOREVER
}//endfnctnTask roveDeviceTemplateThread
//::END THREAD

///////////////////////////////ADDENDUM///////// NOTES :TODO??
//access the global pwm handles
//extern PWM_Handle pwm_1;
//extern PWM_Handle pwm_2;
//extern PWM_Handle pwm_3;
//extern PWM_Handle pwm_4;
//extern PWM_Handle pwm_5;
//extern PWM_Handle pwm_6;
