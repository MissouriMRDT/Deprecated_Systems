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
#include "tcp_task.h"
#include "uarts.h"
#include "uart_0.h"
#include "struct_test.h"

Int main(Void)
{
	// TI RTOS Inits
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();

    // Custom Inits
    init_mux_pins();
    init_spi();

    //Establish TCP connection
    set_up_tcp();

    // Turn on LED for fun
    GPIO_write(Board_LED0, Board_LED_ON);

    // Start BIOS (RTOS)
    BIOS_start();

    //System_printf("%c", input);
	//System_flush()

    return (0);
}
