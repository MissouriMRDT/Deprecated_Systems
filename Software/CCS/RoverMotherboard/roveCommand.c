/*
 * roveCommandParser.c
 *
 *  Created on: Jan 24, 2015
 *      Author: owen
 */

#include <string.h>
#include <stdbool.h>
#include "struct_xfer.h"
#include "structs.h"
#include "json.h"
#include "timing.h"


// Driver Files
#include "uarts.h"

#include "roveCommand.h"
#include "muxes.h"
///HACKS
//#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

Void roveCommand(UArg arg0, UArg arg1)
{

	// Base Station Struct
	base_station_msg_struct fromBaseMsg;

	// Motor Controller Struct
	struct motor_control_struct motor_control_struct;

	// define extern UARTs
	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;

	System_printf("roveCommandParser has started\n");
	System_flush();
	while(1)
	{
		System_printf("roveCommandParser is waiting for a message\n");
		System_flush();

				// Read cmd from TCPHandler
				Mailbox_pend(fromBaseStationMailbox, &fromBaseMsg, BIOS_WAIT_FOREVER);

				switch ( fromBaseMsg.id )
					{
						//*************
						// Drive Left
						//*************
						case 4001:
							motor_control_struct.value = fromBaseMsg.value;

							mux_1( 8 );
							mux_2( 7 );
							mux_3( 6 );

							send_struct(uart1, &motor_control_struct, motor_controller);
							send_struct(uart2, &motor_control_struct, motor_controller);
							send_struct(uart3, &motor_control_struct, motor_controller);

						break;

						//*************
						// Drive Right
						//*************
						case 4002:
							motor_control_struct.value = fromBaseMsg.value;

							mux_1( 1 );
							mux_2( 2 );
							mux_3( 3 );

							send_struct(uart1, &motor_control_struct, motor_controller);
							send_struct(uart2, &motor_control_struct, motor_controller);
							send_struct(uart3, &motor_control_struct, motor_controller);

						break;
					}//endswitch
				//}//endif
		System_printf("\nCommand Parser Thread has received a command!:");
		System_printf("id - %d, value - %d\n", fromBaseMsg.id, fromBaseMsg.value);
		System_flush();
		//Wait to get data from base station

		//Dump data back to base station
	}

}


