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

<<<<<<< HEAD
<<<<<<< HEAD
    int16_t dynamixel_rotate_at_speed = 0;

    dynamixel_rotate_at_speed = 0;

    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
    roveDynamixel_SendCommand(BASE_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, BASE_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
    roveDynamixel_SendCommand(GRIPPER_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, GRIPPER_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

    roveDrivePolulu_LinActCmd(LIN_ACT_ID, ZERO_SPEED);

=======
    //TODO debug
    int16_t motor_speed = 0;
>>>>>>> origin/driveMotorsByIp_HorizonProtocol

//BEGIN NEW EXPERT MEMBER CHALLENGE:

    //Horizon is a forever Client and she calls RED Base Station server forever repeatedly on disconnects
=======
    //2016 is a forever UDP server and she listens for RED Base Station Datagrams
>>>>>>> origin/feature/roveCommUDP2016
    while (FOREVER) {

            //TODO
            if( getUdpMsg(&base_station.data_id, &base_station.data_byte_cnt, &base_station) < SINGLE_BYTE ) {

                printf("ZERO bytes from getUdpMsg\n");

            }//endif

///////////////END HORIZON RECIEVE/////////////////

            rovePrintf_IPMessage(&base_station);

///////////////BEGIN HORIZON SEND COMMANDS/////////

            dynamixel_rotate_at_speed = (*((int16_t*)command_msg.command_value));

            dynamixel_rotate_at_speed = roveConverRedProtocol_toDynamixelSpeed(dynamixel_rotate_at_speed);

            switch(command_msg.struct_id) {

                //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                case wrist_rotate:

                    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    break;

                //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                case wrist_vertical:

                    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    dynamixel_rotate_at_speed = roveReverseDynamixelSpeed(dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    break;

                //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                case elbow_rotate:

                    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    break;

                //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                case elbow_vertical:

                    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    dynamixel_rotate_at_speed = roveReverseDynamixelSpeed(dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    break;

                case base_rotate:

                    roveDynamixel_SendCommand(BASE_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, BASE_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    break;

                case e_stop_arm:

                    dynamixel_rotate_at_speed = 0;

                    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(WRIST_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, WRIST_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_A_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(ELBOW_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, ELBOW_B_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(BASE_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, BASE_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);
                    roveDynamixel_SendCommand(GRIPPER_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, GRIPPER_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    roveDrivePolulu_LinActCmd(LIN_ACT_ID, ZERO_SPEED);

                    break;

                case actuator_increment:

                    roveDrivePolulu_LinActCmd(LIN_ACT_ID, dynamixel_rotate_at_speed);

                    break;

                case gripper_open:

                    roveDynamixel_SendCommand(GRIPPER_UART, DYNAMIXEL_ROTATE_TO_POSITION_COMMAND, GRIPPER_ID, ENDLESS_ROTATION, dynamixel_rotate_at_speed);

                    break;

                default:

                    printf("Unrecognized Struct_id : %d\n", command_msg.struct_id);

                    break;

///////////////END HORIZON SEND COMMANDS/////////////////

<<<<<<< HEAD
<<<<<<< HEAD
=======
            switch (command_msg.struct_id) {
=======
            switch (base_station.data_id) {
>>>>>>> origin/feature/roveCommUDP2016

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
>>>>>>> origin/driveMotorsByIp_HorizonProtocol

                default:

                    printf("Not a drive command\n");

                    break;

            }//endswitch



    }//endwhile FOREVER

}//endfnctnTask roveDeviceTemplateThread
