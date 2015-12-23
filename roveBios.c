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



    #include <xdc/std.h>
    #include <xdc/runtime/System.h>

    #include <ti/sysbios/BIOS.h>
    #include <ti/sysbios/knl/Swi.h>
    #include <ti/sysbios/knl/Task.h>
    #include <ti/sysbios/knl/Clock.h>
    #include <ti/sysbios/knl/Semaphore.h>

    #include <xdc/cfg/global.h>

    Swi_Handle swi0, swi1;
    Semaphore_Handle sem0;

    /*
     *  ======== swi0Fxn =======
     */
    Void swi0Fxn(UArg arg0, UArg arg1)
    {
        System_printf("Enter swi0Fxn, a0 = %d, a1 = %d\n", (Int)arg0, (Int)arg1);
        System_printf("swi0 trigger = %d\n", Swi_getTrigger());
        System_printf("swi0 pri = %d\n", Swi_getPri(swi0));
        System_printf("Exit swi0Fxn\n");
    }

    /*
     *  ======== swi1Fxn =======
     */
    Void swi1Fxn(UArg arg0, UArg arg1)
    {
        System_printf("Enter swi1Fxn, a0 = %d, a1 = %d\n", (Int)arg0, (Int)arg1);
        System_printf("swi1 trigger = %d\n", Swi_getTrigger());
        System_printf("swi1 pri = %d\n", Swi_getPri(swi1));
        System_printf("Exit swi1Fxn\n");
    }

    /*
     *  ======== clk0Fxn =======
     */
    Void clk0Fxn(UArg arg0)
    {
        Swi_post(swi0);
        Swi_post(swi1);

        Semaphore_post(sem0);
    }

    /*
     *  ======== tsk0Fxn =======
     */
    Void tsk0Fxn(UArg arg0, UArg arg1)
    {
        UInt key;

        /* wait for swis to be posted from Clock function */
        Semaphore_pend(sem0, BIOS_WAIT_FOREVER);

        System_printf("Running tsk0Fxn\n");

        key = Swi_disable();        /* swis are disabled */
        Swi_inc(swi0);              /* swi0 trigger = 1 */
        Swi_inc(swi0);              /* swi0 trigger = 2 */
        Swi_restore(key);           /* swi0 runs */

        Swi_or(swi1, 0x100);        /* swi1 runs with trigger = 0x103 */

        Swi_andn(swi1, 0x1);        /* swi1 trigger = 0x10 */
        Swi_andn(swi1, 0x2);        /* swi1 runs with trigger = 0x00 */

        Swi_dec(swi1);              /* swi1 trigger = 2 */
        Swi_dec(swi1);              /* swi1 trigger = 1 */
        Swi_dec(swi1);              /* swi1 runs with trigger = 0 */

        System_printf("Calling BIOS_exit\n");
        BIOS_exit(0);
    }

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

    //TODO watchdog = rove_init_watchdog(Board_WATCHDOG0);
    //TODO Tiva ADC module
    //roveADC_Handle adc_1 = roveAdc_Init(1, ?);
    //roveADC_Handle adc_2 = roveAdc_Init(2, ?);
    //roveADC_Handle adc_3 = roveAdc_Init(3, ?);
    //roveADC_Handle adc_4 = roveAdc_Init(4, ?);
    //roveADC_Handle adc_5 = roveAdc_Init(5, ?);
    //roveADC_Handle adc_6 = roveAdc_Init(6, ?);
    //printf("Init ADC\n\n");



        Swi_Params swiParams;
        Task_Params taskParams;
        Clock_Params clkParams;



        Swi_Params_init(&swiParams);
        swiParams.arg0 = 1;
        swiParams.arg1 = 0;
        swiParams.priority = 2;
        swiParams.trigger = 0;

        swi0 = Swi_create(swi0Fxn, &swiParams, NULL);

        swiParams.arg0 = 2;
        swiParams.arg1 = 0;
        swiParams.priority = 1;
        swiParams.trigger = 3;


        swi1 = Swi_create(swi1Fxn, &swiParams, NULL);



        Task_Params_init(&taskParams);
        taskParams.priority = 1;



        Task_create (tsk0Fxn, &taskParams, NULL);

        Clock_Params_init(&clkParams);
        clkParams.startFlag = TRUE;



        Clock_create(clk0Fxn, 2, &clkParams, NULL);

        sem0 = Semaphore_create(0, NULL, NULL);



    printf("Init BIOS\n\n");

    //begin real time scheduler
    BIOS_start();

    return (0);
}//end main
