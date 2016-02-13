// Missouri Science and Technology Mars Rover Design Team 2015
// Judah Schad jrs6w7@mst.edu
//
// Using Texas Instruments Code Composer Studio SYS/BIOS Kernel
// RTOS::real time operating system
//
#ifdef __cplusplus
extern "C" {
#endif

// == RoveWare2016 UNDER DEVELOPEMENT =========
//
#include "roveDrive.h"

//////////////////////////////////////////////////
// == DAVID Todo : RoveLoop_DriveCntrl : DEVELOPEMENT: New 2016 Drive Protocol ========
//
//  2016 double bonus challenge: "What file do the following 3 variables belong in?
//
//  Hint: IP RoveComm-> RoveWare_TivaDriveDevice_CntrlLoop -> PIN_OUTPUT RoveCntrl
//
//  BaseEthernetProtocols/BoardPinmapProtocols -> RoveDevice Integration Interface
//
//
//
//  "Josh Reed 2016 data_id manifest ::vs::  Horizon RoveStructs.h struct_id list?"
//
//                  needs to integrate 2016 drive with:
//
//  "Mike Miles : RcServo Protocol ::vs:: Roboteq Ascii Protocol?"
//
//
//
//  example: what file(s) / message(s) /code change ... should handle changes between the base data_id and the motor pwm period?

#define RCSERVO_PERIOD_MICROSECONDS 20000 //miles
// vs?
#define DRIVE_LEFT_MOTORS_BY_IP 100 //reed
#define DRIVE_RIGHT_MOTORS_BY_IP 101 //reed
//end_todo



///////////////////////////////////
// == RoveCCS_Setup ==============
//
// Rtos Hooks to the PWm Pins ========
rovePWM_Handle MOTOR_1;
rovePWM_Handle MOTOR_2;
rovePWM_Handle MOTOR_3;
rovePWM_Handle MOTOR_4;
rovePWM_Handle MOTOR_5;
rovePWM_Handle MOTOR_6;

Void roveLoop_DRIVE_RcServoByIp(UArg arg0, UArg arg1);

int main(void)
{
    // Call Texas Instruments Tiva 1294 board hardware driver routines
    // Todo roveBoard_EK_TM4C1294XL_Open();
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();
    EK_TM4C1294XL_initWatchdog();

    printf("Texas Instruments Tiva C Connected Code Composer EK_1294_XL Begin\n\n");

    //hardcoding 20,000 uSec Period for Tiva PWM module (i.e. hardware_rcServo() pins)
    MOTOR_1 = roveBoard_PWM_open(1, RCSERVO_PERIOD_MICROSECONDS);
    MOTOR_2 = roveBoard_PWM_open(2, RCSERVO_PERIOD_MICROSECONDS);
    MOTOR_3 = roveBoard_PWM_open(3, RCSERVO_PERIOD_MICROSECONDS);
    MOTOR_4 = roveBoard_PWM_open(4, RCSERVO_PERIOD_MICROSECONDS);
    MOTOR_5 = roveBoard_PWM_open(5, RCSERVO_PERIOD_MICROSECONDS);
    MOTOR_6 = roveBoard_PWM_open(6, RCSERVO_PERIOD_MICROSECONDS);
    printf("PWM Open\n\n");

    //See RoveMoreLoops.c to add lower pri forever threads to the Texas Inst Bios Rtos schedule
    roveBoard_LOOP_open(&roveLoop_DRIVE_RcServoByIp, 1);

    //Dead mans trigger, will call estop if a successfull Watchdog_clear(estop_drive_motors) hasn't posted within timeout
    //roveWATCHDOG_Handle estop_drive_motors = roveBoard_WATCHDOG_open(rovePost_WATCHDOG_DriveEstop);

    //begin real time scheduler
    printf("BIOS Scheduler Begin\n\n");

    BIOS_start();
    return (0);
}//end main



///////////////////////////////////
// == RoveCCS_HiPri_Loop ========
//
// This highest Priority loop spins forever, but sleep/wake states scheduled by BIOS on the Rtos Post/Pend Schedule
Void roveLoop_DRIVE_RcServoByIp(UArg arg0, UArg arg1)
{
    printf("RoveDriveDevice Begin\n\n");

    //Todo? Gbenga, should we bind data_id TO data_size under the hood in a struct?
    //roveComm_GetMsg(roveData data_struct, uint16_t motor_speed);
    uint16_t data_id = 0;
    size_t   data_size = 0;
    roveComm_Begin(192, 168, 1, 51);

    printf("Rovecomm Begin\n\n");

    //Left/Right Real Time IP To RcServo Skid Steering Controller for Roboteq Brushless MotorCntrlrs
    uint16_t motor_speed = 0;
    uint8_t LoopForever = 1;
    while(LoopForever)
    {
        roveComm_GetMsg(&data_id, &data_size, &motor_speed);

        switch (data_id) {

            //case 0 means there was no message
            case 0:
                //printf("RoveLOOP go to sleep on roveComm pend -> no IP message available at : %d\n\n", roveBoard_GetTimeStamp() );
                break;

            //the right motors must be opposite the left motors. Their phase is backwards, but we also wired one of THOSE backwards
            case DRIVE_LEFT_MOTORS_BY_IP:

                motor_speed = -motor_speed;
                roveCntrl_RcServo_Spin(MOTOR_1, motor_speed);
                roveCntrl_RcServo_Spin(MOTOR_2, motor_speed);
                roveCntrl_RcServo_Spin(MOTOR_3, -motor_speed);
                break;

            //the left motors must be opposite the right motors. Their phase is backwards, but we also wired TWO of THOSE backwards
            case DRIVE_RIGHT_MOTORS_BY_IP:

                roveCntrl_RcServo_Spin(MOTOR_4, -motor_speed);
                roveCntrl_RcServo_Spin(MOTOR_5, motor_speed);
                roveCntrl_RcServo_Spin(MOTOR_6, -motor_speed);
                break;

            default:

                printf("RoveLOOP unrecognized data_id : %d\n\n", data_id);
                break;
        }//endswitch

    }// end while

}//end loop

#ifdef __cplusplus
}
#endif
