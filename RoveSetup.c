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

// == RoveLoopCCS ========
//
#include "RoveLoop.h"

// == RoveSetupCCS ==============
//
int main(void) {

/////////////////////////////////////////////BEGIN Tiva SETUP/////////
    // TI board driver routines
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();
    //Todo EK_TM4C1294XL_initWatchdog();

    // RoveDev custom board driver routines
    //Todo roveEK_TM4C1294XL_initCCP();
    //Todo roveEK_TM4C1294XL_initADC();
    printf("\n\nInit TIVA EK_1294_XL\n\n");

/////////////////////////////////////////////BEGIN HARDWARE Abstraction SETUP
    //Todo still need to be hard code configured as OUTPUTS in the roveBoard/EK_TM4C1294XL.C file?
    /*roveGPIO_Handle PE_0 = roveBoard_GPIO_open(PE_0, PORT_E, PIN_2);
    roveGPIO_Handle PE_1 = roveBoard_GPIO_open(PE_1, PORT_E, PIN_2);
    roveGPIO_Handle PH_0 = roveBoard_GPIO_open(PH_0, PORT_H, PIN_0);
    roveGPIO_Handle PH_1 = roveBoard_GPIO_open(PH_1, PORT_H, PIN_1);
    roveGPIO_Handle PK_2 = roveBoard_GPIO_open(PK_2, PORT_K, PIN_2);
    roveGPIO_Handle PK_3 = roveBoard_GPIO_open(PK_3, PORT_K, PIN_3);
    roveGPIO_Handle PL_0 = roveBoard_GPIO_open(PL_0, PORT_L, PIN_0);
    roveGPIO_Handle PL_1 = roveBoard_GPIO_open(PL_1, PORT_L, PIN_1);
    roveGPIO_Handle PM_6 = roveBoard_GPIO_open(PM_6, PORT_M, PIN_6);
    roveGpio_Handle PM_7 = roveBoard_GPIO_open(PM_7, PORT_M, PIN_7);*/

//DO NOT INIT UART_0 or UART_1-> hardware support conflict: roveBoard/EK_TM4C1294XL.h
    //hardcode configured as INPUT/OUTPUT pairs in the roveBoard/EK_TM4C1294XL.C file

    //hardcoding a 57600 Baud Rate in Tiva UART module for dynamixel (i.e. hardware_serial pins)
    roveUART_Handle UART_2 = roveBoard_UART_open(2, 57600);
    roveUART_Handle UART_3 = roveBoard_UART_open(3, 57600);
    roveUART_Handle UART_4 = roveBoard_UART_open(4, 57600);
    roveUART_Handle UART_5 = roveBoard_UART_open(5, 57600);
    roveUART_Handle UART_6 = roveBoard_UART_open(6, 57600);
    roveUART_Handle UART_7 = roveBoard_UART_open(7, 57600);
    printf("Init UARTS\n\n");

//DO NOT INIT PWM_0 -> ethernet support conflict: roveBoard/EK_TM4C1294XL.h
    //These are hardcode configured as OUTPUTS in the roveBoard/EK_TM4C1294XL.C file

    //hardcoding 20,000 Period for Tiva PWM module (i.e. hardware_rcServo() pins
    rovePWM_Handle PWM_1 = roveBoard_PWM_open(1, 20000);
    rovePWM_Handle PWM_2 = roveBoard_PWM_open(2, 20000);
    rovePWM_Handle PWM_3 = roveBoard_PWM_open(3, 20000);
    rovePWM_Handle PWM_4 = roveBoard_PWM_open(4, 20000);
    rovePWM_Handle PWM_5 = roveBoard_PWM_open(5, 20000);
    rovePWM_Handle PWM_6 = roveBoard_PWM_open(6, 20000);
    printf("Init PWM\n\n");

    //These are hardcoded configured to TIMER INTERRUPTS and Capture Compare Registers in the roveBoard/roveEK_TM4C1294XL.c

    //Todo Rove Tiva Read PWM Capture and Compare Timers (i.e. hardware_pulseIn() pins
    //roveCCP_Handle CCP_1 = roveBoard_CCP_open(1, ?);
    //roveCCP_Handle CCP_2 = roveBoard_CCP_open(1, ?);
    //roveCCP_Handle CCP_3 = roveBoard_CCP_open(1, ?);
    //roveCCP_Handle CCP_4 = roveBoard_CCP_open(1, ?);
    //roveCCP_Handle CCP_5 = roveBoard_CCP_open(1, ?);
    //roveCCP_Handle CCP_6 = roveBoard_CCP_open(1, ?);
    printf("Init CCP\n\n");

    //These are hardcoded configured to TIMER INTERRUPTS and Capture Compare Registers in the roveBoard/roveEK_TM4C1294XL.c

    //Todo Rove Tiva read ADC module (i.e. hardware_analogRead() pins
    //roveADC_Handle ADC_1 = roveBoard_ADC_open(1, ?);
    //roveADC_Handle ADC_2 = roveBoard_ADC_open(2, ?);
    //roveADC_Handle ADC_3 = roveBoard_ADC_open(3, ?);
    //roveADC_Handle ADC_4 = roveBoard_ADC_open(4, ?);
    //roveADC_Handle ADC_5 = roveBoard_ADC_open(5, ?);
    //roveADC_Handle ADC_6 = roveBoard_ADC_open(6, ?);
    //printf("Init ADC\n\n");

/////////////////////////////////////////////BEGIN MEMORY AND SCHEDULING SETUP
    //Todo Rtos Malloc Hook?s

/////////////////////////////////////////////BEGIN THREAD INSTANCE SETUP

    //See RoveLoop.h and RoveMoreLoops.h for RoveRtosTask threads scheduled by TexasInstRtos
    roveBoard_LOOP_open(&roveLOOP, 1);

    //begin real time scheduler
    //Todo roveWATCHDOG_Handle = roveBoard_WATCHDOG_open(Board_WATCHDOG0);
    printf("Init BIOS\n\n");

    BIOS_start();
    return (0);
}//end main
