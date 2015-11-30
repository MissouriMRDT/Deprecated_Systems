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
    //Board_initWatchdog();
    printf("\n\nInit TIVA EK_1294_XL\n\n");

//DO NOT INIT UART_0 or UART_1-> hardware support conflict: HardwareResourecs/EK_TM4C1294XL.h
    //hardcoding a 57600 Baud Rate in Tiva UART module for dynamixel
    uart_2 = roveUart_Init(2, 57600);
    uart_3 = roveUart_Init(3, 57600);
    uart_4 = roveUart_Init(4, 57600);
    uart_5 = roveUart_Init(5, 57600);
    uart_6 = roveUart_Init(6, 57600);
    uart_7 = roveUart_Init(7, 57600);
    printf("Init UARTS\n\n");

//DO NOT INIT PWM_0 -> ethernet support conflict: HardwareResourecs/EK_TM4C1294XL.h
    //hardcoding 20,000 Period for Tiva PWM module
    pwm_1 = rovePwm_Init(1, 20000);
    pwm_2 = rovePwm_Init(2, 20000);
    pwm_3 = rovePwm_Init(3, 20000);
    pwm_4 = rovePwm_Init(4, 20000);
    pwm_5 = rovePwm_Init(5, 20000);
    pwm_6 = rovePwm_Init(6, 20000);
    printf("Init PWM\n\n");

//TODO watchdog = rove_init_watchdog(Board_WATCHDOG0);
    //hardcoding ? Tiva ADC module
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
//END::PRE BIOS CFG

/////////////////////////////////////////////////////Tiva HW IO Module Initialization Wrappers
PWM_Handle rovePwm_Init(UInt pwm_index, UInt period_in_microseconds) {

    PWM_Handle pwmHandle;
    PWM_Params pwmParams;
    PWM_Params_init(&pwmParams);
    //TODO Phase Align params
    pwmParams.period = period_in_microseconds;

    pwmHandle = PWM_open(pwm_index, &pwmParams);
    if (pwmHandle == NULL) {
        System_abort("Error opening the PWM\n");
    }//endif

    return pwmHandle;
}//endfnctn rovePwm_Init

UART_Handle roveUart_Init(UInt uart_index, UInt baud_rate) {

    UART_Handle uartHandle;
    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = baud_rate;

    uartHandle = (UART_Handle)UART_open(uart_index, &uartParams);
    if (uartHandle == NULL) {
        System_abort("Error opening the UART\n");
    }//endif

    return uartHandle;
}//endfnct roveUart_Init
/*TODO
UInt roveAdc_Init(UInt adc_index, UInt adc_cfg) {

    //TODO
    UInt adcHandle = NULL;

    //UInt adcParams;
    if (adcHandle == NULL) {
        System_abort("Error opening the ADC\n");
    } //endif

    return adcHandle;
}//endfnct roveAdc_Init*/
//END::Tiva Hw IO Init Wrappres
