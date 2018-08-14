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

    //TODO base_station.local_ip_addr = rovecommInit(LISTEN_PORT, LOCAL_IP_ADDRESS, &base_station);
    rovecommInit(LISTEN_PORT, &base_station);


///////////////BEGIN 2016//////COMMAND////////////////////


    //command work variable
    int16_t speed = 0;

    //only write one way device to the dynamixel forever globally
    digitalWrite(TRI_STATE_BUFFER, HIGH);

    //make sure and stop all arm motors when powering up, set command all speeds zero
    rovePolulu_DriveLinAct(LIN_ACT_ID, speed);
    roveDynamixel_Rotate(WRIST_A_ID, WRIST_UART, ENDLESS_ROTATION, speed);
    roveDynamixel_Rotate(WRIST_B_ID, WRIST_UART, ENDLESS_ROTATION, speed);
    roveDynamixel_Rotate(ELBOW_A_ID, ELBOW_UART, ENDLESS_ROTATION, speed);
    roveDynamixel_Rotate(ELBOW_B_ID, ELBOW_UART, ENDLESS_ROTATION, speed);
    roveDynamixel_Rotate(BASE_ID, BASE_UART, ENDLESS_ROTATION, speed);
    roveDynamixel_Rotate(GRIPPER_ID, GRIPPER_UART, ENDLESS_ROTATION, speed);


///////////////END   2016//////COMMAND/////////////////////


///////////////BEGIN 2016//////RECIEVE/////////////////////


    //2016 is a forever UDP server and she listens for RED Base Station Datagrams
    while (FOREVER) {

            //TODO
            if( getUdpMsg(&base_station.data_id, &base_station.data_byte_cnt, &base_station) < SINGLE_BYTE ) {

                printf("ZERO bytes from getUdpMsg\n");

            } else {


///////////////END   2016//////RECIEVE/////////////////

                rovePrintf_IPMessage(&base_station);

///////////////BEGIN 2016//////COMMAND//////////////////


                speed = (*((int16_t*)base_station.data_buffer));

                switch (base_station.data_id) {

                    case DRIVE_RIGHT_MOTORS:

                        //the right motors must be opposite the left motors. Their phase is backwards, but we also wired one of THOSE backwards
                        speed = -speed;

                        roveDriveMotor_ByPWM(pwm_1, speed);
                        roveDriveMotor_ByPWM(pwm_2, speed);
                        roveDriveMotor_ByPWM(pwm_3, -speed);

                        break;

                    case DRIVE_LEFT_MOTORS:

                        //the left motors must be opposite the right motors. Their phase is backwards, but we also wired TWO of THOSE backwards
                        roveDriveMotor_ByPWM(pwm_4, -speed);
                        roveDriveMotor_ByPWM(pwm_5, speed);
                        roveDriveMotor_ByPWM(pwm_6, -speed);

                        break;

                    //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                    case WRIST_ROTATE:

                        speed = roveDynamixel_ConvertSpeed(speed);
                        roveDynamixel_Rotate(WRIST_A_ID, WRIST_UART, ENDLESS_ROTATION, speed);
                        roveDynamixel_Rotate(WRIST_B_ID, WRIST_UART, ENDLESS_ROTATION, speed);
                        break;

                    //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                    case WRIST_VERTICAL:

                        speed = roveDynamixel_ConvertSpeed(speed);
                        roveDynamixel_Rotate(WRIST_A_ID, WRIST_UART, ENDLESS_ROTATION, speed);

                        speed = roveDynamixel_ReverseSpeed(speed);
                        roveDynamixel_Rotate(WRIST_B_ID, WRIST_UART, ENDLESS_ROTATION, speed);
                        break;

                    //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                    case ELBOW_ROTATE:

                        speed = roveDynamixel_ConvertSpeed(speed);
                        roveDynamixel_Rotate(ELBOW_A_ID, ELBOW_UART, ENDLESS_ROTATION, speed);
                        roveDynamixel_Rotate(ELBOW_B_ID, ELBOW_UART, ENDLESS_ROTATION, speed);
                        break;

                    //differential gears, motors would move opposite, except we have them wired backwards, so opposite in hardware is together in software
                    case ELBOW_VERTICAL:

                        speed = roveDynamixel_ConvertSpeed(speed);
                        roveDynamixel_Rotate(ELBOW_A_ID, ELBOW_UART, ENDLESS_ROTATION, speed);

                        speed = roveDynamixel_ReverseSpeed(speed);
                        roveDynamixel_Rotate(ELBOW_B_ID, ELBOW_UART, ENDLESS_ROTATION, speed);
                        break;

                    //single dynamixel at base, gear ratio rotates incredibly fast
                    case BASE_ROTATE:

                        speed = roveDynamixel_ConvertSpeed(speed);
                        roveDynamixel_Rotate(BASE_ID, BASE_UART, ENDLESS_ROTATION, speed);
                        break;

                    //stop all arm motors, set all speeds zero
                    case E_STOP_ARM:

                        speed = 0;

                        rovePolulu_DriveLinAct(LIN_ACT_ID, speed);
                        roveDynamixel_Rotate(WRIST_A_ID, WRIST_UART, ENDLESS_ROTATION, speed);
                        roveDynamixel_Rotate(WRIST_B_ID, WRIST_UART, ENDLESS_ROTATION, speed);
                        roveDynamixel_Rotate(ELBOW_A_ID, ELBOW_UART, ENDLESS_ROTATION, speed);
                        roveDynamixel_Rotate(ELBOW_B_ID, ELBOW_UART, ENDLESS_ROTATION, speed);
                        roveDynamixel_Rotate(BASE_ID, BASE_UART, ENDLESS_ROTATION, speed);
                        roveDynamixel_Rotate(GRIPPER_ID, GRIPPER_UART, ENDLESS_ROTATION, speed);
                        break;

                    //positive is forward, negative is reverse, only 8 bit low_byte is speed
                    case ACTUATOR_INCREMENT:

                        rovePolulu_DriveLinAct(LIN_ACT_ID, speed);
                        break;

                    //single dynamixel at gripper, gear ratio rotates incredibly slow
                    case GRIPPER_OPEN:

                        speed = roveDynamixel_ConvertSpeed(speed);
                        roveDynamixel_Rotate(GRIPPER_ID, GRIPPER_UART, ENDLESS_ROTATION, speed);
                        break;

                    default:

                        printf("Unrecognized Data_id : %d\n", base_station.data_id);
                        break;

                }//endswitch

            }//endif

///////////////END   2016//////COMMAND/////////////////


    }//endwhile FOREVER


///////////////END   2016//////RECIEVE/////////////////


}//endfnctnTask roveDeviceTemplateThread
