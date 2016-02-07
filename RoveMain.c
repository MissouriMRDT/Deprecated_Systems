// Missouri Science and Technology Mars Rover Design Team 2015
// Judah Schad jrs6w7@mst.edu
//
// Texas Inst Rtos Module / TM4 Pin Access Runtime Instances
// Using Texas Instruments Code Composer Studio SYS/BIOS Kernel
//
// RTOS::real time operating system
//
// RoveSetupCCS/CCSJs.cfg
//
// initializes Texas Instruments drivers
// configs hardware interface
// get global handles
// begins the scheduler
//
// mrdt::rovWareCCS

// == RoveBoardCCS ========
//
// Rtos Pin Access MCU Interface Assets
#include "RoveBoard/RoveBoard.h"

// == RoveWareCCS ========
//
#include "RoveBoard/RoveLoops.h"
#include "../RoveWare/RoveComm.h"
#include "../RoveWare/RoveControl.h"

//HORIZON command CONFIG protocol
#define DRIVE_RIGHT_MOTORS 100
#define DRIVE_LEFT_MOTORS 101

rovePWM_Handle MOTOR_1;
rovePWM_Handle MOTOR_2;
rovePWM_Handle MOTOR_3;
rovePWM_Handle MOTOR_4;
rovePWM_Handle MOTOR_5;
rovePWM_Handle MOTOR_6;

Void roveLOOP(UArg arg0, UArg arg1);

// == RoveSetupCCS ==============
//
int main(void) {

    // TI board driver routines
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();

    //Todo EK_TM4C1294XL_initWatchdog();
    printf("\n\nInit TIVA EK_1294_XL\n\n");

//DO NOT INIT PWM_0 -> ethernet support conflict: roveBoard/EK_TM4C1294XL.h
    //These are hardcode configured as OUTPUTS in the roveBoard/EK_TM4C1294XL.C file

    //hardcoding 20,000 Period for Tiva PWM module (i.e. hardware_rcServo() pins
    MOTOR_1 = roveBoard_PWM_open(1, 20000);
    MOTOR_2 = roveBoard_PWM_open(2, 20000);
    MOTOR_3 = roveBoard_PWM_open(3, 20000);
    MOTOR_4 = roveBoard_PWM_open(4, 20000);
    MOTOR_5 = roveBoard_PWM_open(5, 20000);
    MOTOR_6 = roveBoard_PWM_open(6, 20000);
    printf("Init PWM\n\n");

    //See RoveLoop.h and RoveMoreLoops.h for RoveRtosTask threads scheduled by TexasInstRtos
    roveBoard_LOOP_open(&roveLOOP, 1);

    //begin real time scheduler
    //Todo roveWATCHDOG_Handle = roveBoard_WATCHDOG_open(Board_WATCHDOG0);
    printf("Init BIOS\n\n");

    BIOS_start();
    return (0);
}//end main



// == RoveLoopCCS_HiPri ========
//
// loops spin forever, but sleep and wake states are scheduled by the rtos
//
Void roveLOOP(UArg arg0, UArg arg1)
{
    printf("Init roveLoop\n\n");

    uint16_t data_id = 0;
    size_t   data_size = 0;
    uint16_t motor_speed = 0;

    RoveCommBegin(192, 168, 1, 51);

    printf("RoveCommBegin\n\n");

    while(FOREVER)
    {
        RoveCommGetMsg(&data_id, &data_size, &motor_speed);

        switch (data_id) {

            //case 0 means there was no message
            case 0:
                break;

            //the right motors must be opposite the left motors. Their phase is backwards, but we also wired one of THOSE backwards
            case DRIVE_LEFT_MOTORS:

                motor_speed = -motor_speed;
                roveDriveMotor_ByPWM(MOTOR_1, motor_speed);
                roveDriveMotor_ByPWM(MOTOR_2, motor_speed);
                roveDriveMotor_ByPWM(MOTOR_3, -motor_speed);
                break;

            //the left motors must be opposite the right motors. Their phase is backwards, but we also wired TWO of THOSE backwards
            case DRIVE_RIGHT_MOTORS:

                roveDriveMotor_ByPWM(MOTOR_4, -motor_speed);
                roveDriveMotor_ByPWM(MOTOR_5, motor_speed);
                roveDriveMotor_ByPWM(MOTOR_6, -motor_speed);
                break;

            default:

                printf("Unrecognized data_id : %d\n\n", data_id);
                break;
        }//endswitch

    }// end while

}//end loop
