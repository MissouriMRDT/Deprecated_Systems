// The rover
//
// Keenan Johnson 2014

/*
 *  ======== empty.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <inc/hw_ssi.h>
#include <driverlib/ssi.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include "driverlib/sysctl.h"
#include <ti/drivers/Watchdog.h>

/* Board Header file */
#include "Board.h"

Void echoFxn(UArg arg0, UArg arg1)
{
    UART_Handle uart1;
    UART_Handle uart2;
    UART_Params uartParams1;
    UART_Params uartParams2;

    char input;


    // Start UART1
    UART_Params_init(&uartParams1);
    uartParams1.readReturnMode = UART_RETURN_FULL;
    uartParams1.readEcho = UART_ECHO_OFF;
    uartParams1.baudRate = 9600;
    uart1 = UART_open(1, &uartParams1);

    if (uart1 == NULL) {
        System_abort("Error opening the UART1");
    }

    // Start UART1
	UART_Params_init(&uartParams2);
	uartParams2.readReturnMode = UART_RETURN_FULL;
	uartParams2.readEcho = UART_ECHO_OFF;
	uartParams2.baudRate = 9600;
	uart2 = UART_open(2, &uartParams2);

	if (uart2 == NULL) {
		System_abort("Error opening the UART2");
	}

    /* Loop forever echoing */
    while (TRUE) {
		UART_read(uart1, &input, 1);
		System_printf("Rec: %x\n",input);
		System_flush();
		UART_write(uart2, &input, 1);
    }

}

/*
 *  ======== main ========
 */
Int main(Void)
{
    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Rover booting");
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
