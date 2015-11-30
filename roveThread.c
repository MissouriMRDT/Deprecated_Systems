// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// C interface for a TexInst TIVA RTOS TASK Thread with private stack / signal
// Using Texas Instruments Code Composer Studio RTOS stack instatiates the roveDevice_Thread.c
// This is found in the tivaRtscJS.cfg[TI-RTOS] Javascript Gui/Script tab at the bottom of Projece Explorer Folders
// recieves base station messages using ip bsd style sockets and issues logic commands to hardware
//
// mrdt::rovWare
#include "roveThread.h"
///////////////BEGIN 2016//////DEVICE THREAD//////////////
void roveThread(UArg arg0, UArg arg1) {

    //developement notes:
    //TODO eliminate struct patterns in favor of local variables?
    //Or just go other way and add C++ Wrappers Inside of CCS?
    //straight embedded static function jump table lookups?


//TEST WHEEL mode
    //////////speed schema -> rpm
            //range: 0~2047( 0X7FF)
            //unit:  0.1%.
            //speed = 0 Full Reverse
            //speed = 1023 = 1024 Full Stop
            //speed = 1025~2047 Full forward
            //i.e. speed = 512 means 50% of max motor output in reverse
    //angle schema = undefined -> has no affect

//TEST JOINT mode
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


//DEV16 notes
    //WARNING!! in Wheel Mode, the savage_electronics::Dynamixel.move() function has no effect only Dynamixel.turn() works
    //joint_position goal angle in "wheel mode" is always seen as zero = infinite and ONLY the goal speed matters
    printf("Init roveThread Arm Dyna Tester\n\n\n");

///////////////BEGIN 2016//////NETWORKING///////////////////
    //open a tiva ndk socket session in this task stack
    fdOpenSession( TaskSelf() );

/////////////////TODO base_station.local_ip_addr.port.subscribers[ip_addrs++] = rovecommInit(LOCAL_IP_ADDRESS, PORT, &base_station, state);

//Judah Dev16 Shorthand
#define LOCAL_DEVICE_IP_ADDRESS "192.168.1.2"
#define LEFT_WRIST_ID 0x00
#define LWRST_TIVA_PIN 0x00
#define RIGHT_WRIST_ID 0x01
#define RWRST_TIVA_PIN 0x01
#define DYNA_WRITE_ONLY 0

    //TODO args :: init roveComm
    rove_udp_socket roveCommDev16;
    roveComm_Init(&roveCommDev16);

///////////////BEGIN 2016//////Dynamixel Serial//////////////
    //init device protocol
    rove_protocol roboWristDev16;

    rove_dyna_serial left_wrist;
    left_wrist.error_flag = roveDynamixel_Init(&left_wrist, LEFT_WRIST_ID, LWRST_TIVA_PIN, DYNA_WRITE_ONLY);
    if(left_wrist.error_flag){
        //system abort
    }//end if

    rove_dyna_serial right_wrist;
    left_wrist.error_flag = roveDynamixel_Init(&left_wrist, RIGHT_WRIST_ID, RWRST_TIVA_PIN, DYNA_WRITE_ONLY);
    if(left_wrist.error_flag){
       //system abort
    }//end if

    //BOTH wheel AND joint mode AX12:(WHEEL GoalSpeed :0~2047/0X7FF unit:0.1%):(JOINT GoalSpeed: 0~1023/0X3FF unit: 0.111rpm)
    int16_t speed = 0;

    //ONLY joint mode AX12:(JOINT GoalPosition:0~1023/0x3FF) at 0.29 degree
    int16_t angle = 0;

///////////////BEGIN 2016//////MOTOR TEST ROUTINE/////////////
    while (FOREVER) {

//TODO Base Station define Data Id's Cmd Proto Integration
        if( roveGet_UdpMsg(&roboWristDev16, &roveCommDev16) < COMMS_SINGLE_BYTE ) {
            printf("ZERO bytes from getUdpMsg\n");
        }//end if

//TEST WHEEL mode
        if( roveDynamixel_SetWheelModeCFG(&left_wrist)) {
            printf("Dev16 Error roveDynamixel_SetWheelModeCFG left_wrist!");
        }//endif

        if(roveDynamixel_SetWheelModeCFG(&right_wrist)) {
            printf("Dev16 Error roveDynamixel_SetWheelModeCFG left_wrist!");
        }//endif

        //roveDynamixel_SpinWheelCMD::->if(spin_wheel_direction > 0) wheel_speed += (1 >> 10);
        //ramp up from zero to max forward
        for (speed = 0; speed < 1000; speed += 50) {

            //TODO arg2 could be negative??
            if(roveDynamixel_SpinWheelCMD(&left_wrist, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD left_wrist!");
            }//endif

            if(roveDynamixel_SpinWheelCMD(&right_wrist, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD right_wrist!");
            }//endif

            roveDelay_MilliSec(500);
        } //end for

        //ramp back from max forward through zero to max reverse
        for (speed = 1000; speed > -1000; speed -= 50) {

            if(roveDynamixel_SpinWheelCMD(&left_wrist, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD left_wrist!");
            }//endif

            if(roveDynamixel_SpinWheelCMD(&right_wrist, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD right_wrist!");
            }//endif

            roveDelay_MilliSec(500);
        } //end for

        //ramp back from max reverse landing on zero
        for (speed = -1000; speed < 0; speed += 50) {

            if(roveDynamixel_SpinWheelCMD(&left_wrist, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD left_wrist!");
            }//endif

            if(roveDynamixel_SpinWheelCMD(&right_wrist, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD right_wrist!");
            }//endif

            roveDelay_MilliSec(500);
        } //end for
//TODO:  #define and scale speed < 1000; speed += 50
//::END TEST WHEEL mode
        roveDelay_MilliSec(20000);

//TEST JOINT mode
        if( roveDynamixel_SetJointModeCFG(&left_wrist)) {
            printf("Dev16 Error roveDynamixel_SetJointModeCFG left_wrist!");
        }//endif

        if(roveDynamixel_SetJointModeCFG(&right_wrist)) {
            printf("Dev16 Error roveDynamixel_SetJointModeCFG left_wrist!");
        }//endif
        //very slowly now
        speed = 10;
        for (angle = 0; angle < 1000; angle += 50) {

            //TODO arg2 could be negative??
            if(roveDynamixel_RotateJointCMD(&left_wrist, angle, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD left_wrist!");
            }//endif

            if(roveDynamixel_RotateJointCMD(&right_wrist, angle, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD right_wrist!");
            }//endif

            roveDelay_MilliSec(500);
        } //end for

        for (angle = 1000; angle > 0; speed -= 50) {

            if(roveDynamixel_RotateJointCMD(&left_wrist, angle, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD left_wrist!");
            }//endif

            if(roveDynamixel_RotateJointCMD(&right_wrist, angle, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD right_wrist!");
            }//endif

            roveDelay_MilliSec(500);
        } //end for

        for (speed = 0; speed < 500; speed += 50) {

            if(roveDynamixel_RotateJointCMD(&left_wrist, angle, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD left_wrist!");
            }//endif

            if(roveDynamixel_RotateJointCMD(&right_wrist, angle, speed)){
                printf("Dev16 Error roveDynamixel_SpinWheelCMD right_wrist!");
            }//endif

            roveDelay_MilliSec(500);
        } //end for
//END TEST JOINT mode

        roveDelay_MilliSec(20000);
//::END2016 MOTOR TEST ROUTINE

//////////////REPEAT 2016//////MOTOR TEST FOREVER/////////////
    }//endwhile FOREVER

}//endfnctnTask
//::END THREAD

///////////////////////////////ADDENDUM///////// NOTES :TODO??
//access the global pwm handles
//extern PWM_Handle pwm_1;
//extern PWM_Handle pwm_2;
//extern PWM_Handle pwm_3;
//extern PWM_Handle pwm_4;
//extern PWM_Handle pwm_5;
//extern PWM_Handle pwm_6;
