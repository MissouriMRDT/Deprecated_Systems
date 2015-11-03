// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style sockets
//
// mrdt::rovWare

// BEGIN TCP HORIZON RECIEVE

// DEVICE TEAM : YOU MAY START THIS CHALLENG BY SKIPPING PAST THIS TCP LOGIC ON DOWN TO LINE 50ish : "BEGIN HORIZON COMMANDS"

#include "roveDeviceTemplate_Thread.h"

void roveDeviceTemplateThread(UArg arg0, UArg arg1) {

    printf("Init roveDevice_TemplateThread\n\n\n");

    //access the global pwm handles
    extern PWM_Handle pwm_1;
    extern PWM_Handle pwm_2;
    extern PWM_Handle pwm_3;
    extern PWM_Handle pwm_4;
    extern PWM_Handle pwm_5;
    extern PWM_Handle pwm_6;

    //open a tiva ndk socket session in this task stack
    fdOpenSession(  TaskSelf() );

    //init Horizon protocol for command_msg_buffer
    rove_tcp_socket command_msg;

    //handle tcp connection state
    command_msg.connected_flag = DISCONNECTED;
    command_msg.error_code = ERROR_FREE;

    //HORIZON command protocol
    command_msg.message_id = 0;
    command_msg.struct_id = 0;

    //TODO debug
    int16_t motor_speed = 0;

//BEGIN NEW EXPERT MEMBER CHALLENGE:

    //Horizon is a forever Client and she calls RED Base Station server forever repeatedly on disconnects
    while (FOREVER) {

        printf("Attempting to connect\n\n");

        command_msg.connected_flag = roveTCP_Connect(&command_msg);

        // loop to recieve cmds and send telem from and to the base station: if socket breaks, loop breaks and we attempt to reconnect
       while (command_msg.connected_flag == CONNECTED) {

            printf("Connected\n");

            //TODO debug
            if( (roveTCP_HorizonProtocol_Recv(&command_msg)) < SINGLE_BYTE ) {

                printf("ZERO bytes from roveTCP_HorizonProtocol_Recv\n");

            }//endwhile


///////////////END HORIZON RECIEVE/////////////////

            rovePrintf_TCPCmdMsg(&command_msg);

///////////////BEGIN HORIZON SEND COMMANDS/////////


            switch (command_msg.struct_id) {

                case motor_drive_right_id:

                    //the right motors must be negative the left motors. Their phase is backwards, but we also wired one of THOSE backwards
                    motor_speed = -(*((int16_t*)command_msg.command_value));

                    roveDriveMotor_ByPWM(pwm_1, motor_speed);
                    roveDriveMotor_ByPWM(pwm_2, motor_speed);
                    roveDriveMotor_ByPWM(pwm_3, -motor_speed);

                    break;

                case motor_drive_left_id:

                    //the right motors must be opposite the right motors. Their phase is backwards, but we also wired one of THOSE backwards
                    motor_speed = (*((int16_t*)command_msg.command_value));

                    roveDriveMotor_ByPWM(pwm_4, -motor_speed);
                    roveDriveMotor_ByPWM(pwm_5, motor_speed);
                    roveDriveMotor_ByPWM(pwm_6, -motor_speed);

                    break;

        }//endwhile

        printf("Connection Lost\n");

        close(command_msg.socket_fd);

        command_msg.message_id = 0;

        command_msg.struct_id = 0;

    }//endwhile FOREVER

}//endfnctnTask roveDeviceTemplateThread
