// Missouri Science and Technology Mars Rover Design Team 2015
//
// roveBIOS_Init.c
//
// Using Texas Instruments Code Composer Studio RTOS stack
//
// TODO FALL_2015
//
// TODO V1 - for URC 2016 IP Server -> (PWM / UART) Device Controller Template
//
// Judah Schad jrs6w7@mst.edu
//
// get global handles
// initializes Texas Instruments drivers
// configs hardware interface
// begins the scheduler
//
// Texas Instruments:
//
// SYS/BIOS Kernel
// RTOS operating system
// TIVA RTSC config
//
// mrdt::roveWare

#include "roveBIOS_Init.h"

//init main
int main(void) {


///////////////BEGIN 2016//////PRE BIOS STARTUP CONFIG/////////

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
    uart_2 = (UART_Handle) roveUART_Init(2, 9600);
    uart_3 = (UART_Handle) roveUART_Init(3, 9600);
    uart_4 = (UART_Handle) roveUART_Init(4, 9600);
    uart_5 = (UART_Handle) roveUART_Init(5, 9600);
    uart_6 = (UART_Handle) roveUART_Init(6, 9600);
    uart_7 = (UART_Handle) roveUART_Init(7, 9600);

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


///////////////END   2016//////MAIN/////////////////////////



///////////////BEGIN 2016//////PRE BIOS STARTUP CONFIG//////

//Tiva HW IO Module Initialization Wrapper
PWM_Handle rovePWM_Init(UInt pwm_index, UInt period_in_microseconds) {

    PWM_Handle pwm_handle;

    PWM_Params pwmParams;

    PWM_Params_init(&pwmParams);

    pwmParams.period = period_in_microseconds;
    pwm_handle = PWM_open(pwm_index, &pwmParams);

    if (pwm_handle == NULL) {

        System_abort("Error opening the PWM\n");

    }   //endif

    return pwm_handle;

}   //endfnctn rovePWMInit


//Tiva HW IO Module Initialization Wrapper
UART_Handle roveUART_Init(UInt uart_index, UInt baud_rate) {

    UART_Handle uart_handle;
    UART_Params uartParams;

    UART_Params_init(&uartParams);

    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = baud_rate;

    uart_handle = (UART_Handle)UART_open(uart_index, &uartParams);

    if (uart_handle == NULL) {

        System_abort("Error opening the UART\n");

    } //endif

    return uart_handle;

} //endfnct init_uart(UInt uart_index, UInt baud_rate)


///////////////END 2016//////PRE BIOS CONFIG//////
