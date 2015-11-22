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


///////////////BEGIN 2016//////DEVICE THREAD//////////////


#include "roveDevice_Thread.h"

void roveDeviceThread(UArg arg0, UArg arg1) {

    printf("Init roveDevice_TemplateThread\n\n\n");

    //access the global pwm handles
    extern PWM_Handle pwm_1;
    extern PWM_Handle pwm_2;
    extern PWM_Handle pwm_3;
    extern PWM_Handle pwm_4;
    extern PWM_Handle pwm_5;
    extern PWM_Handle pwm_6;


///////////////BEGIN 2016//////NETWORKING/////////////////


    //open a tiva ndk socket session in this task stack
    fdOpenSession(  TaskSelf() );

    //init roveComm
    rove_udp_socket base_station;

    //TODO base_station.local_ip_addr = rovecommInit(LOCAL_IP_ADDRESS, &base_station);
    roveComm_Init(&base_station);

///////////////BEGIN 2016//////COMMAND////////////////////

    //command work variable
    int16_t speed = 0;

///////////////END   2016//////COMMAND/////////////////////


///////////////BEGIN 2016//////RECIEVE/////////////////////


    //2016 is a forever UDP server and she listens for RED Base Station Datagrams
    while (FOREVER) {

///////////////BEGIN 2016//////MOTOR TEST//////////////////

    for (speed = 0; speed < 1000; speed += 50) {

        roveDriveMotor_ByPWM(pwm_1, speed);
        roveDriveMotor_ByPWM(pwm_2, speed);
        roveDriveMotor_ByPWM(pwm_3, -speed);
        roveDriveMotor_ByPWM(pwm_4, -speed);
        roveDriveMotor_ByPWM(pwm_5, speed);
        roveDriveMotor_ByPWM(pwm_6, -speed);

        roveDelay_MilliSec(500);

    } //end for

    for (speed = 1000; speed > -1000; speed -= 50) {

        roveDriveMotor_ByPWM(pwm_1, speed);
        roveDriveMotor_ByPWM(pwm_2, speed);
        roveDriveMotor_ByPWM(pwm_3, -speed);
        roveDriveMotor_ByPWM(pwm_4, -speed);
        roveDriveMotor_ByPWM(pwm_5, speed);
        roveDriveMotor_ByPWM(pwm_6, -speed);

        roveDelay_MilliSec(500);

    } //end for


    for (speed = -1000; speed < 0; speed += 50) {

        roveDriveMotor_ByPWM(pwm_1, speed);
        roveDriveMotor_ByPWM(pwm_2, speed);
        roveDriveMotor_ByPWM(pwm_3, -speed);
        roveDriveMotor_ByPWM(pwm_4, -speed);
        roveDriveMotor_ByPWM(pwm_5, speed);
        roveDriveMotor_ByPWM(pwm_6, -speed);

        roveDelay_MilliSec(500);

    } //end for

    roveDelay_MilliSec(20000);

///////////////END   2016//////MOTOR TEST/////////////////

    }//endwhile FOREVER

}//endfnctnTask roveDeviceTemplateThread
