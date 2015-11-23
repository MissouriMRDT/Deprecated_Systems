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

    printf("Init roveDevice_TemplateThread\n\n\n");

///////////////BEGIN 2016//////NETWORKING/////////////////

    //open a tiva ndk socket session in this task stack
    fdOpenSession( TaskSelf() );

    //TODO eliminate struct patterns in favor of local variables?
    //init roveComm
    rove_udp_socket base_station;
    //TODO base_station.local_ip_addr = rovecommInit(LOCAL_IP_ADDRESS, &base_station);
    roveComm_Init(&base_station);

///////////////BEGIN 2016//////COMMAND Args//////////////////

    //BOTH wheel AND joint mode AX12:(WHEEL GoalSpeed :0~2047/0X7FF unit:0.1%):(JOINT GoalSpeed: 0~1023/0X3FF unit: 0.111rpm)
    int16_t speed = 0;

    //ONLY joint mode AX12:(JOINT GoalPosition:0~1023/0x3FF) at 0.29 degree
    int16_t angle = 0;

///////////////END   2016//////COMMAND Args///////////////////

///////////////BEGIN 2016//////MOTOR TEST ROUTINE/////////////

    //2016 is a forever UDP server and she listens for RED Base Station Datagrams
    while (FOREVER) {

//ERROR_STATE: Angle Limit Error Bit (Bit1) staus response set 1 = "Destination Out of Range" and triggers "Alarm LED/Shutdown"

//TEST WHEEL mode

        //WARNING!! in Wheel Mode, the savage_electronics::Dynamixel.move() function has no effect only Dynamixel.turn() works
        //joint_position goal angle in "wheel mode" is always seen as zero = infinite and ONLY the goal speed matters

//////////speed schema -> rpm

        //range: 0~2047( 0X7FF)
        //unit:  0.1%.

        //speed = 0 Full Reverse
        //speed = 1023 = 1024 Full Stop
        //speed = 1025~2047 Full forward

        //angle schema = undefined -> has no affect

        //i.e. speed = 512 means 50% of max motor output in reverse
        roveDynamixel_SetWheelModeCFG(LEFT_WRIST);
        roveDynamixel_SetWheelModeCFG(RIGHT_WRIST);

        //roveDynamixel_SpinWheelCMD::->if(spin_wheel_direction == CLOCKWISE) wheel_speed += (1 >> 10);

        //ramp up from zero to max forward
        for (speed = 0; speed < 1000; speed += 50) {

            //TODO remove 'spin_wheel_direction' arg1??   ->...arg2 could be negative??
            roveDynamixel_SpinWheelCMD(LEFT_WRIST, CLOCKWISE, speed);
            roveDynamixel_SpinWheelCMD(RIGHT_WRIST, CLOCKWISE, speed);
            roveDelay_MilliSec(500);
        } //end for

        //ramp back from max forward through zero to max reverse
        for (speed = 1000; speed > -1000; speed -= 50) {

            //TODO remove 'spin_wheel_direction' arg1??   ->...arg2 could be negative??
            roveDynamixel_SpinWheelCMD(LEFT_WRIST, CLOCKWISE, speed);
            roveDynamixel_SpinWheelCMD(RIGHT_WRIST, CLOCKWISE, speed);
            roveDelay_MilliSec(500);
        } //end for

        //ramp back from max reverse landing on zero
        for (speed = -1000; speed < 0; speed += 50) {

            //TODO remove 'spin_wheel_direction' arg1??   ->...arg2 could be negative??
            roveDynamixel_SpinWheelCMD(LEFT_WRIST, CLOCKWISE, speed);
            roveDynamixel_SpinWheelCMD(RIGHT_WRIST, CLOCKWISE, speed);
            roveDelay_MilliSec(500);
        } //end for

//TODO:  #define and scale speed < 1000; speed += 50

//END TEST WHEEL mode
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
        roveDynamixel_SetJointModeCFG(LEFT_WRIST);
        roveDynamixel_SetJointModeCFG(RIGHT_WRIST);

        //very slowly now
        speed = 10;

        for (angle = 0; angle < 1000; angle += 50) {

            roveDynamixel_RotateJointCMD(LEFT_WRIST, angle, speed);
            roveDynamixel_RotateJointCMD(RIGHT_WRIST, angle, speed);
            roveDelay_MilliSec(500);
        } //end for

        for (angle = 1000; angle > 0; speed -= 50) {

            roveDynamixel_RotateJointCMD(LEFT_WRIST, angle, speed);
            roveDynamixel_RotateJointCMD(RIGHT_WRIST, angle, speed);
            roveDelay_MilliSec(500);
        } //end for

        for (speed = 0; speed < 500; speed += 50) {

            roveDynamixel_RotateJointCMD(LEFT_WRIST, angle, speed);
            roveDynamixel_RotateJointCMD(RIGHT_WRIST, angle, speed);
            roveDelay_MilliSec(500);
        } //end for

        //END TEST JOINT mode
        roveDelay_MilliSec(20000);

/////////////////END 2016//////MOTOR TEST ROUTINE/////////////

//////////////REPEAT 2016//////MOTOR TEST FOREVER/////////////

    }//endwhile FOREVER
}//endfnctnTask roveDeviceTemplateThread

///////////////////////////////END THREAD/////////////////////

///////////////////////////////ADDENDUM///////// NOTES :TODO??
//access the global pwm handles
//extern PWM_Handle pwm_1;
//extern PWM_Handle pwm_2;
//extern PWM_Handle pwm_3;
//extern PWM_Handle pwm_4;
//extern PWM_Handle pwm_5;
//extern PWM_Handle pwm_6;
