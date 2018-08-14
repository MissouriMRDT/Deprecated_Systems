// Missouri Science and Technology Mars Rover Design Team 2015
// Judah Schad jrs6w7@mst.edu
//
// Using Texas Instruments Code Composer Studio RTOS stack
// SYS/BIOS Kernel
// RTOS operating system
// tivaRTSC_JS.cfg
//
// initializes Texas Instruments drivers
// configs hardware interface
// get global handles
// begins the scheduler
//
// mrdt::roveWare
#include "roveSetup.h"

//init main
int main(void) {

/////////////////////////////////////////////BEGIN SETUP/////////

    //init TI board driver routines
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();

    //TODO Board_initWatchdog();

/////////////////////////////////////////////BEGIN HARDWARE SETUP

    printf("\n\nInit TIVA EK_1294_XL\n\n");

    //TODO Reed/Connor/Owen Hardware Abstraction Advice?
    //There is no GPIO.c like there is PWM.c and UART.c which contain PWM_Open() and UART_open()
    //Should we write roveGPIO.c with a roveGPIO_Params_init() and roveGPIO_open()?
    //right now I just have stubbed roveGPIO_Handle as small typedef struct in roveBOARD_TIVA1294.h

    //still need to be hard code configured as OUTPUTS in the roveBoard/EK_TM4C1294XL.C file
    /*roveGPIO_Handle PE_0 = roveBoard_InitGpioCFG(PE_0, PORT_E, PIN_2);
    roveGPIO_Handle PE_1 = roveBoard_InitGpioCFG(PE_1, PORT_E, PIN_2);
    roveGPIO_Handle PH_0 = roveBoard_InitGpioCFG(PH_0, PORT_H, PIN_0);
    roveGPIO_Handle PH_1 = roveBoard_InitGpioCFG(PH_1, PORT_H, PIN_1);
    roveGPIO_Handle PK_2 = roveBoard_InitGpioCFG(PK_2, PORT_K, PIN_2);
    roveGPIO_Handle PK_3 = roveBoard_InitGpioCFG(PK_3, PORT_K, PIN_3);
    roveGPIO_Handle PL_0 = roveBoard_InitGpioCFG(PL_0, PORT_L, PIN_0);
    roveGPIO_Handle PL_1 = roveBoard_InitGpioCFG(PL_1, PORT_L, PIN_1);
    roveGPIO_Handle PM_6 = roveBoard_InitGpioCFG(PM_6, PORT_M, PIN_6);
    roveGpio_Handle PM_7 = roveBoard_InitGpioCFG(PM_7, PORT_M, PIN_7);*/

//DO NOT INIT UART_0 or UART_1-> hardware support conflict: HardwareResourecs/EK_TM4C1294XL.h

    //hardcode configured as INPUT/OUTPUT pairs in the roveBoard/EK_TM4C1294XL.C file
    //hardcoding a 57600 Baud Rate in Tiva UART module for dynamixel
    roveUART_Handle UART_2 = roveBoard_InitUartCFG(2, 57600);
    roveUART_Handle UART_3 = roveBoard_InitUartCFG(3, 57600);
    roveUART_Handle UART_4 = roveBoard_InitUartCFG(4, 57600);
    roveUART_Handle UART_5 = roveBoard_InitUartCFG(5, 57600);
    roveUART_Handle UART_6 = roveBoard_InitUartCFG(6, 57600);
    roveUART_Handle UART_7 = roveBoard_InitUartCFG(7, 57600);
    printf("Init UARTS\n\n");

//DO NOT INIT PWM_0 -> ethernet support conflict: HardwareResourecs/EK_TM4C1294XL.h

    //These are hardcode configured as OUTPUTS in the roveBoard/EK_TM4C1294XL.C file
    //hardcoding 20,000 Period for Tiva PWM module
    rovePWM_Handle PWM_1 = roveBoard_InitPwmCFG(1, 20000);
    rovePWM_Handle PWM_2 = roveBoard_InitPwmCFG(2, 20000);
    rovePWM_Handle PWM_3 = roveBoard_InitPwmCFG(3, 20000);
    rovePWM_Handle PWM_4 = roveBoard_InitPwmCFG(4, 20000);
    rovePWM_Handle PWM_5 = roveBoard_InitPwmCFG(5, 20000);
    rovePWM_Handle PWM_6 = roveBoard_InitPwmCFG(6, 20000);
    printf("Init PWM\n\n");

    //TODO Tiva ADC module
    //roveADC_Handle adc_1 = roveAdc_Init(1, ?);
    //roveADC_Handle adc_2 = roveAdc_Init(2, ?);
    //roveADC_Handle adc_3 = roveAdc_Init(3, ?);
    //roveADC_Handle adc_4 = roveAdc_Init(4, ?);
    //roveADC_Handle adc_5 = roveAdc_Init(5, ?);
    //roveADC_Handle adc_6 = roveAdc_Init(6, ?);
    //printf("Init ADC\n\n");

    //TODO Tiva Capture and Compare Timers
    //roveCapCompare_Handle = cap_1 = roveCapture_Init(1, ?);
    //roveCapCompare_Handle = cap_1 = roveCapture_Init(1, ?);
    //roveCapCompare_Handle = cap_1 = roveCapture_Init(1, ?);
    //roveCapCompare_Handle = cap_1 = roveCapture_Init(1, ?);
    //roveCapCompare_Handle = cap_1 = roveCapture_Init(1, ?);
    //roveCapCompare_Handle = cap_1 = roveCapture_Init(1, ?);
    //printf("Init CAP CMPR\n\n");


/////////////////////////////////////////////BEGIN MEMORY AND SCHEDULING SETUP

    //TODO Rtos Malloc Hooks

    //TODO watchdog = rove_init_watchdog(Board_WATCHDOG0);
    //printf("Init BIOS\n\n");

/////////////////////////////////////////////BEGIN LOOPS

   //begin real time scheduler
    BIOS_start();
    return (0);
}//end main
