// The rover
//
// Keenan Johnson 2014

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Queue.h>

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
#include <ti/drivers/SPI.h>

/* Board Header file */
#include "Board.h"

// Keenan Include File
#include "muxes.h"
#include "lcd.h"
#include "tcp.h"
#include "UARTS.h"

Void uart1(UArg arg0, UArg arg1)
{
    UART_Handle uart1;
    UART_Params uartParams1;

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

    /* Loop forever echoing */
    while (TRUE) {
    	UART_write(uart1, "UART1", 5);
		//UART_read(uart1, &input, 1);
		//System_printf("Uart1: %x\n",input);
		//System_flush();
    }
}

Void uart2(UArg arg0, UArg arg1)
{
    UART_Handle uart2;
    UART_Params uartParams2;

    char input;

    //rec.data = "a";

	// Start UART1
	UART_Params_init(&uartParams2);
	uartParams2.readReturnMode = UART_RETURN_FULL;
	uartParams2.readEcho = UART_ECHO_OFF;
	uartParams2.baudRate = 9600;
	uart2 = UART_open(2, &uartParams2);

	if (uart2 == NULL) {
		System_abort("Error opening the UART7");
	}

	while (TRUE) {
			UART_write(uart2, "UART2", 5);
			//UART_read(uart5, &input, 1);
			//System_printf("Uart5: %x\n",input);
			//System_flush();
		}
}

Int main(Void)
{
	// TI RTOS Inits
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();
    //Board_initSPI();

    // Custom Inits
    init_mux_pins();
    init_LCD();
    open_UARTs();

    uint32_t read;

    //read = SPI_Read(0x0000);

    //System_printf("MR: %d", read);

    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Rover booting");
    System_flush();

    typedef struct Rec {
     Queue_Elem elem;
     Char data;
    } Rec;

    //Queue_Handle myQ;

    BIOS_start();

    return (0);
}
