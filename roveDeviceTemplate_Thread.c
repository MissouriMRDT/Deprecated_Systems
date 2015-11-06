// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style sockets
//
// mrdt::rovWare

// BEGIN 2016 DEVICE RECIEVE

// DEVICE TEAM : YOU MAY START THIS CHALLENG BY SKIPPING PAST THIS TCP LOGIC ON DOWN TO LINE 50ish : "BEGIN HORIZON COMMANDS"

#include "roveDeviceTemplate_Thread.h"

void roveDeviceTemplateThread(UArg arg0, UArg arg1) {

    printf("Init roveDevice_TemplateThread\n\n\n");

    //access the global pwm handles
    //TODO pwm_1 motor_1
    extern PWM_Handle motor_1;
    extern PWM_Handle motor_2;
    extern PWM_Handle motor_3;
    extern PWM_Handle motor_4;
    extern PWM_Handle motor_5;
    extern PWM_Handle motor_6;

    //open a tiva ndk socket session in this task stack
    fdOpenSession(  TaskSelf() );

    //init roveComm
    rove_udp_socket base_station;

    //TODO base_station.socket_fd = rovecommInit(LISTEN_PORT, LOCAL_IP_ADDRESS, &base_station);
    base_station.socket_fd = rovecommInit(LISTEN_PORT, &base_station);

    //commands
    int16_t speed;

    //2016 is a forever UDP server and she listens for RED Base Station Datagrams
    while (FOREVER) {

            //TODO
            if( getUdpMsg(&base_station.data_id, &base_station.data_byte_cnt, &base_station) < SINGLE_BYTE ) {

                printf("ZERO bytes from getUdpMsg\n");

            }//endif

///////////////END HORIZON RECIEVE/////////////////

            rovePrintf_IPMessage(&base_station);

///////////////BEGIN HORIZON SEND COMMANDS/////////


            switch (base_station.data_id) {

                case motor_drive_right_id:

                    //the right motors must be negative the left motors. Their phase is backwards, but we also wired one of THOSE backwards
                    speed = -(*((int16_t*)base_station.data_buffer));

                    roveDriveMotor_ByPWM(motor_1, speed);
                    roveDriveMotor_ByPWM(motor_2, speed);
                    roveDriveMotor_ByPWM(motor_3, -speed);

                    break;

                case motor_drive_left_id:

                    //the right motors must be opposite the right motors. Their phase is backwards, but we also wired two of THOSE backwards
                    speed = (*((int16_t*)base_station.data_buffer));

                    roveDriveMotor_ByPWM(motor_4, -speed);
                    roveDriveMotor_ByPWM(motor_5, speed);
                    roveDriveMotor_ByPWM(motor_6, -speed);

                    break;

                default:

                    printf("Not a drive command\n");

                    break;

            }//endswitch



    }//endwhile FOREVER

}//endfnctnTask roveDeviceTemplateThread
