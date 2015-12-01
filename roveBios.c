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
#include "roveBios.h"

//init main
int main(void) {

/////////////////////////////////////////////BEGIN PRE BIOS STARTUP CONFIG/////////

    //init TI board driver routines
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();

    //TODO Board_initWatchdog();
    printf("\n\nInit TIVA EK_1294_XL\n\n");

    //REED?? but there is no GPIO.c like there is PWM.c PWM_Open()and UART.c UART_open()
    //so we need to own the instantion ourselves? roveGPIO_open??
    //or we can rip apart roveBoard1294/EK_TM4C1294XL.C for actual config here
    //These are all need to be configured as OUTPUTS in EK_TM4C1294XL.C
  /*  roveGpio_Handle PE_0 = roveGpio_Init(PE_0, PORT_E, PIN_2);
    roveGpio_Handle PE_1 = roveGpio_Init(PE_1, PORT_E, PIN_2);
    roveGpio_Handle PH_0 = roveGpio_Init(PH_0, PORT_H, PIN_0);
    roveGpio_Handle PH_1 = roveGpio_Init(PH_1, PORT_H, PIN_1);
    roveGpio_Handle PK_2 = roveGpio_Init(PK_2, PORT_K, PIN_2);
    roveGpio_Handle PK_3 = roveGpio_Init(PK_3, PORT_K, PIN_3);
    roveGpio_Handle PL_0 = roveGpio_Init(PL_0, PORT_L, PIN_0);
    roveGpio_Handle PL_1 = roveGpio_Init(PL_1, PORT_L, PIN_1);
    roveGpio_Handle PM_6 = roveGpio_Init(PM_6, PORT_M, PIN_6);
    roveGpio_Handle PM_7 = roveGpio_Init(PM_7, PORT_M, PIN_7);*/

//DO NOT INIT UART_0 or UART_1-> hardware support conflict: HardwareResourecs/EK_TM4C1294XL.h

    //hardcoding a 57600 Baud Rate in Tiva UART module for dynamixel
    roveUart_Handle UART_2 = roveUart_Init(2, 57600);
    roveUart_Handle UART_3 = roveUart_Init(3, 57600);
    roveUart_Handle UART_4 = roveUart_Init(4, 57600);
    roveUart_Handle UART_5 = roveUart_Init(5, 57600);
    roveUart_Handle UART_6 = roveUart_Init(6, 57600);
    roveUart_Handle UART_7 = roveUart_Init(7, 57600);
    printf("Init UARTS\n\n");

//DO NOT INIT PWM_0 -> ethernet support conflict: HardwareResourecs/EK_TM4C1294XL.h

    //hardcoding 20,000 Period for Tiva PWM module
    rovePwm_Handle PWM_1 = rovePwm_Init(1, 20000);
    rovePwm_Handle PWM_2 = rovePwm_Init(2, 20000);
    rovePwm_Handle PWM_3 = rovePwm_Init(3, 20000);
    rovePwm_Handle PWM_4 = rovePwm_Init(4, 20000);
    rovePwm_Handle PWM_5 = rovePwm_Init(5, 20000);
    rovePwm_Handle PWM_6 = rovePwm_Init(6, 20000);
    printf("Init PWM\n\n");

    //TODO watchdog = rove_init_watchdog(Board_WATCHDOG0);

    //TODO Tiva ADC module
    //adc_1 = roveAdc_Init(1, ?);
    //adc_2 = roveAdc_Init(2, ?);
    //adc_3 = roveAdc_Init(3, ?);
    //adc_4 = roveAdc_Init(4, ?);
    //adc_5 = roveAdc_Init(5, ?);
    //adc_6 = roveAdc_Init(6, ?);
    //printf("Init ADC\n\n");
    printf("Init BIOS\n\n");

    //begin real time scheduler
    BIOS_start();

    return (0);
}//end main
