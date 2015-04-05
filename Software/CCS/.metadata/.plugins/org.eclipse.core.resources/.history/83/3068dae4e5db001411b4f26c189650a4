//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)

// RoverMotherboardMain.c
//
// first created:
//
// 01_22_2015_Owen_Chiaventone
//
// last edited:
//
//02_24_2015_Judah Schad_jrs6w7@mst.edu
//
//	this instatiates global handles, initializes TI modules and then calls the TI BIOS operating system
//
//	TI BIOS operating system instatiates the roveTCPHandler, roveCmdCntrl, and roveTelemCntrl threads

//includes globally scoped Texas Instruments (TI) header files

#include "roveIncludes/RoverMotherboardMain.h"

#include "roveIncludes/roveWareHeaders/roveUarts.h"

const uint8_t FOREVER = 1;

//globally init UART handles

	UART_Handle uart0;
    UART_Handle uart1;
    UART_Handle uart2;
    UART_Handle uart3;
    UART_Handle uart4;
    UART_Handle uart5;
    UART_Handle uart6;
    UART_Handle uart7;

//globally create PWM handles
    PWM_Handle motor_0;
    PWM_Handle motor_1;
    PWM_Handle motor_2;
    PWM_Handle motor_3;
    PWM_Handle motor_4;
    PWM_Handle motor_5;

//TODO Mailbox Init

//
//  ======== init main  ========
//
int main(void)
{

//init TI board driver routines
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
	uart0 = (UART_Handle)init_uart( 0, 115200 );
    uart1 = (UART_Handle)init_uart( 1, 115200 );
	uart2 = (UART_Handle)init_uart( 2, 115200 );
	uart3 = (UART_Handle)init_uart( 3, 115200 );
	uart4 = (UART_Handle)init_uart( 4, 115200 );
	uart5 = (UART_Handle)init_uart( 5, 115200 );
	uart6 = (UART_Handle)init_uart( 6, 115200 );
	uart7 = (UART_Handle)init_uart( 7, 115200 );

//Init PWMs
    System_printf("Assign PWM 1\n");
    System_flush();
	motor_0 = (PWM_Handle)rovePWMInit( 1, 20000 );
/*
	System_printf("Assign PWM 2\n");
    System_flush();
	motor_1 = (PWM_Handle)rovePWMInit( EK_TM4C1294XL_PWM2, 20000);
    System_printf("Assign PWM 3\n");
    System_flush();

	motor_2 = (PWM_Handle)rovePWMInit( EK_TM4C1294XL_PWM3, 20000);
    System_printf("Assign PWM 4\n");
    System_flush();

	motor_3 = (PWM_Handle)rovePWMInit( EK_TM4C1294XL_PWM4, 20000);
    System_printf("Assign PWM 5\n");
    System_flush();

	motor_4 = (PWM_Handle)rovePWMInit( EK_TM4C1294XL_PWM5, 20000);
    System_printf("Assign PWM 6\n");
    System_flush();

	motor_5 = (PWM_Handle)rovePWMInit( 6, 20000);
*/
//start TI BIOS

	ms_delay( 1 );

	System_printf("roveMotherboardMain init \n");
	System_printf("\n");
	System_printf("\n");
	System_flush();

	ms_delay( 1 );

    BIOS_start();

//exit BIOS

    return (0);

}//endmain: 		RoverMotherboardMain
