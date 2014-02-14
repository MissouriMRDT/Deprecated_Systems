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
    UART_Handle uart;
    UART_Params uartParams;

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uart = UART_open(7, &uartParams);

    if (uart == NULL) {
        System_abort("Error opening the UART");
    }

    /* Loop forever echoing */
    while (TRUE) {
        UART_write(uart, "hello\n", 6);
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
    Board_initSPI();
    Board_initUART();
    // Board_initWatchdog();

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target and use ROV to view output.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
        unsigned char ip_addr[] = {192,168,2,10};
        unsigned char sub_mask[] = {255,255,255,0};
        unsigned char gtw_addr[] = {192,168,2,1};

        SPI_Send(MR,0x80);    //Reset
        SysCtlDelay(500);

        //Gateway Address config
        SPI_Send(GAR+0,gtw_addr[0]);
        SPI_Send(GAR+1,gtw_addr[1]);
        SPI_Send(GAR+2,gtw_addr[2]);
        SPI_Send(GAR+3,gtw_addr[3]);

        //MAC Address config
        SPI_Send(SAR+0,mac_addr[0]);
        SPI_Send(SAR+1,mac_addr[1]);
        SPI_Send(SAR+2,mac_addr[2]);
        SPI_Send(SAR+3,mac_addr[3]);
        SPI_Send(SAR+4,mac_addr[4]);
        SPI_Send(SAR+5,mac_addr[5]);

        //Sub Mask config
        SPI_Send(SUBR+0,sub_mask[0]);
        SPI_Send(SUBR+1,sub_mask[1]);
        SPI_Send(SUBR+2,sub_mask[2]);
        SPI_Send(SUBR+3,sub_mask[3]);


        //Ip config
        SPI_Send(SIPR+0,ip_addr[0]);
        SPI_Send(SIPR+1,ip_addr[1]);
        SPI_Send(SIPR+2,ip_addr[2]);
        SPI_Send(SIPR+3,ip_addr[3]);

        // Setting the Wiznet W5100 RX and TX Memory Size, we use 2KB for Rx/Tx 4 channels
        SPI_Send(RMSR,0x55);
        SPI_Send(TMSR,0x55);

       //Testing the read value by writing it on the LCD Screen
        uint32_t *n;

        while(1) //this is the loop in question
        {
        //SPI_Read(SIPR);
        }

    /* Start BIOS */
    //BIOS_start();

    return (0);
}
