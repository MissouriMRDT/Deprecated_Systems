// RoverMotherboardMain.c
//
// Using Texas Instruments Code Composer Studio RTOS stack. See read me include for copyright
//
// first created:
//
// 01_22_2015_Owen_Chiaventone omc8db
//
// last edited:
//
// 02_24_2015_Judah Schad_jrs6w7@mst.edu
//
// this instatiates global handles, initializes TI modules and then calls the TI BIOS operating system
//
// TI BIOS operating system instatiates the roveTCPHandler, roveCmdCntrl, and roveTelemCntrl threads
//
// includes globally scoped Texas Instruments (TI) header files

#include "roveIncludes/RoverMotherboardMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "roveIncludes/mrdtRoveWare.h"

// globally create UART handles

UART_Handle uart0;
UART_Handle uart1;
UART_Handle uart2;
UART_Handle uart3;
UART_Handle uart4;
UART_Handle uart5;
UART_Handle uart6;
UART_Handle uart7;

// globally create PWM handles

PWM_Handle motor_0;
PWM_Handle motor_1;
PWM_Handle motor_2;
PWM_Handle motor_3;
PWM_Handle motor_4;
PWM_Handle motor_5;

// hack to kill 'unreachable statement' for task error clause in CCS

const uint8_t FOREVER = 1;

// init main

int main(void) {

// init TI board driver routines

	Board_initGeneral();
	Board_initGPIO();
	Board_initEMAC();

	System_printf("Init uarts\n");
	System_flush();
	Board_initUART();

	System_printf("Init PWM\n");
	System_flush();
	Board_initPWM();

//init UARTS

	System_printf("Assign UARTS\n");
	System_flush();

	// not utilizing uart0 or uart1 (no mob to pins)

	uart0 = (UART_Handle) init_uart(0, 115200);
	uart1 = (UART_Handle) init_uart(1, 115200);
	uart2 = (UART_Handle) init_uart(2, 115200);
	uart3 = (UART_Handle) init_uart(3, 115200);
	uart4 = (UART_Handle) init_uart(4, 115200);
	uart5 = (UART_Handle) init_uart(5, 115200);
	uart6 = (UART_Handle) init_uart(6, 115200);
	uart7 = (UART_Handle) init_uart(7, 115200);

// init PWMs

//System_printf("Assign PWM 1\n");
//System_flush();

	motor_0 = (PWM_Handle) rovePWMInit(1, 20000);

	//System_printf("Assign PWM 2\n");
	//System_flush();

	motor_1 = (PWM_Handle) rovePWMInit(2, 20000);

	//System_printf("Assign PWM 3\n");
	//System_flush();

	motor_2 = (PWM_Handle) rovePWMInit(3, 20000);

	//System_printf("Assign PWM 4\n");
	//System_flush();

	motor_3 = (PWM_Handle) rovePWMInit(4, 20000);

	//System_printf("Assign PWM 5\n");
	//System_flush();

	motor_4 = (PWM_Handle) rovePWMInit(5, 20000);

	//System_printf("Assign PWM 6\n");
	//System_flush();

	motor_5 = (PWM_Handle) rovePWMInit(6, 20000);

// start TI BIOS

	ms_delay(1);

	System_printf("roveMotherboardMain init \n");
	System_printf("\n");
	System_printf("\n");
	System_flush();

	ms_delay(1);

	BIOS_start();

// exit TI BIOS

	return (0);

}				//endmain RoverMotherboardMain
