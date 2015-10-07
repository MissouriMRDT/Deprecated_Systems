// roveBiosStart.h MST MRDT 2015
//
// Judah Schad jrs6w7@mst.edu
//
// module for init and config hardware periph access routines at start up

#ifndef ROVEBIOSINIT_H_
#define ROVEBIOSINIT_H_

//EK_1294XL dev shield target device
#include "../roveTargetConfigs/Board.h"
#include "inc/hw_memmap.h"

//C lib
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//CCS TI config
#include <xdc/std.h>

#include <xdc/cfg/global.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

//CCS TI operating system
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

//TI hardware access routines
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/Watchdog.h>

//TI BIOS hardware drivers
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"

//CCS TI TIVA NDK BSD support
//#include <sys/socket.h>

//TI TIVA Mailbox() BIOS software routine support
//#include <ti/sysbios/knl/Mailbox.h>

//global Watchdog
//Watchdog_Handle watchdog;

//Tiva HW IO Module Initialization Wrappers
PWM_Handle rovePWM_Init(PWM_Handle pwm_index, uint16_t period_in_microseconds);

UART_Handle roveUART_Init(UInt uart_index, UInt baud_rate);//TODO

//global UARTs

//DO NOT INIT UART_0 or UART_1-> hardware support conflict: HardwareResourecs/EK_TM4C1294XL.h

UART_Handle uart_2;
UART_Handle uart_3;
UART_Handle uart_4;
UART_Handle uart_5;
UART_Handle uart_6;
UART_Handle uart_7;

//global PWMs

//DO NOT INIT PWM_0 -> ethernet support conflict: HardwareResourecs/EK_TM4C1294XL.h

PWM_Handle pwm_1;
PWM_Handle pwm_2;
PWM_Handle pwm_3;
PWM_Handle pwm_4;
PWM_Handle pwm_5;
PWM_Handle pwm_6;


//Tiva HW IO Module Initialization Wrappers
PWM_Handle rovePWM_Init(PWM_Handle pwm_index, uint16_t period_in_microseconds) {

    PWM_Handle pwm_handle;

    PWM_Params pwmParams;

    PWM_Params_init(&pwmParams);

    pwmParams.period = period_in_microseconds;
    pwm_handle = (PWM_Handle)PWM_open(pwm_index, &pwmParams);

    if (pwm_handle == NULL) {

        System_abort("Error opening the PWM\n");

    }   //endif

    return pwm_handle;

}   //endfnctn rovePWMInit



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

#endif // ROVEBIOSINIT_H_
