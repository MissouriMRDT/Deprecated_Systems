// Missouri Science and Technology Mars Rover Design Team 2015
//
// roveDeviceTemplate.c
//
// Using Texas Instruments Code Composer Studio RTOS stack
//
// first created:
//
// 09_01_2015       V1 - URC Horizon IP TCP Client / UART/ PWM Controller Template
//
// Judah Schad jrs6w7@mst.edu
//
// mrdt::roveWare

#include "roveBIOS_Init.h"

#include "roveDeviceTemplate_Thread.h"

#include "roveWare/roveWare_tivaWrappers.h"

//init main
int main(void) {

    //init TI board driver routines
    Board_initGeneral();
    Board_initGPIO();
    Board_initEMAC();
    Board_initUART();
    Board_initPWM();

    //Board_initWatchdog();

    printf("\n\nInit TIVA EK_1294_XL\n\n");

//DO NOT INIT UART_0 or UART_1-> hardware support conflict: HardwareResourecs/EK_TM4C1294XL.h

    //hardcoding a 115,200 Baud Rate in Tiva UART module
    uart_2 = (UART_Handle) roveUART_Init(2, 115200);
    uart_3 = (UART_Handle) roveUART_Init(3, 115200);
    uart_4 = (UART_Handle) roveUART_Init(4, 115200);
    uart_5 = (UART_Handle) roveUART_Init(5, 115200);
    uart_6 = (UART_Handle) roveUART_Init(6, 115200);
    uart_7 = (UART_Handle) roveUART_Init(7, 115200);

    printf("Init UARTS\n\n");

//DO NOT INIT PWM_0 -> ethernet support conflict: HardwareResourecs/EK_TM4C1294XL.h

    //hardcoding 20,000 Period for Tiva PWM module
    pwm_1 = (PWM_Handle) rovePWM_Init(1, 20000);
    pwm_2 = (PWM_Handle) rovePWM_Init(2, 20000);
    pwm_3 = (PWM_Handle) rovePWM_Init(3, 20000);
    pwm_4 = (PWM_Handle) rovePWM_Init(4, 20000);
    pwm_5 = (PWM_Handle) rovePWM_Init(5, 20000);
    pwm_6 = (PWM_Handle) rovePWM_Init(6, 20000);

    printf("Init PWM\n\n");

    //watchdog = rove_init_watchdog(Board_WATCHDOG0);

    printf("Init BIOS\n\n");

    //begin real time scheduler
    BIOS_start();

    return (0);

}//endmain RoverMotherboardMain
