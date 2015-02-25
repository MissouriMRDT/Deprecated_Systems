/*
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <string.h>

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* NDK BSD support */
#include <sys/socket.h>

/* Example/Board Header file */
#include "Board.h"

//added keenans includes to project for toubleshooting Stellaris to Tiva defines
//Todo add the includes to main here:

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

//Task Files
//#include "roveCommand.h"
//#include "telemHwiUart1.h"

    //init UART handles

	UART_Handle uart0;
    UART_Handle uart1;
    UART_Handle uart2;
    UART_Handle uart3;
    UART_Handle uart4;
    UART_Handle uart5;
    UART_Handle uart6;
    UART_Handle uart7;

//
//  ======== init main  ========
//
int main(void)
{
    // init board drivers

    Board_initGeneral();
    Board_initGPIO();
    Board_initEMAC();
    Board_initUART();

    //init UARTS

	uart0 = init_uart( 0, 115200 );
    uart1 = init_uart( 1, 115200 );
	uart2 = init_uart( 2, 115200 );
	uart3 = init_uart( 3, 115200 );
	uart4 = init_uart( 4, 115200 );
	uart5 = init_uart( 5, 115200 );
	uart7 = init_uart( 7, 115200 );

    System_printf("Starting Main nSystem provider is set to "
                  "SysMin. Halt the target to view any SysMin contents in"
                  " ROV.\n");

    //SysMin will only print to the console when you call flush or exit

    System_flush();

    //start BIOS

    BIOS_start();

    //exit

    return (0);

}//endmain program RoverMotherboardMain
