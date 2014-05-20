/*
 * simple_drive.h
 *
 *  Created on: May 6, 2014
 *      Author: Keenan Johnson
 */

#ifndef SIMPLE_DRIVE_H_
#define SIMPLE_DRIVE_H_

#include <string.h>
#include <stdbool.h>
#include "../include/struct_xfer.h"
#include "../include/structs.h"


// This is temporary and should be removed
// once the base station is updated
float fix_drive_cmds( char cmd_value )
{
	return ((((float) cmd_value/255)*32) - 16) ;
}


extern Void tcp_connection(UArg arg0, UArg arg1)
{

	// Init UARTs
	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart7;

	bool cmd_valid = false;

	// Read buffer
	struct base_station_cmd_struct cmd_struct;

	// Motor Controller Struct
	struct motor_struct _struct;

	// Drill struct
	struct drill_Controls drill_cmd;

	while(1)
	{
		///////////////////////////////////////////////////
		// DRIVE COMMANDS
		///////////////////////////////////////////////////

		// Read cmd from TCP
		cmd_valid = recv_struct( uart7, &cmd_struct, tcp_cmd );

		if ( cmd_valid == true )
		{
			//////////////////////////
			// Left Command
			//////////////////////////
			if( cmd_struct.id == 4009 )
			{
				_struct.value = cmd_struct.value;

				mux_1( 8 );
				mux_2( 7 );
				mux_3( 6 );

				send_struct(uart1, &_struct, motor_controller);
				send_struct(uart2, &_struct, motor_controller);
				send_struct(uart3, &_struct, motor_controller);
			}

			//////////////////////////
			// Right Command
			//////////////////////////
			if( cmd_struct.id == 4010 )
			{
				_struct.value = cmd_struct.value;

				mux_1( 1 );
				mux_2( 2 );
				mux_3( 3 );

				send_struct(uart1, &_struct, motor_controller);
				send_struct(uart2, &_struct, motor_controller);
				send_struct(uart3, &_struct, motor_controller);
			}

			//////////////////////////////
			// Drill Command
			///////////////////////////////
			if( cmd_struct.id == 5000 )
			{
				drill_cmd.direction = 1;
				drill_cmd.goalSpeed = cmd_struct.value;

				mux_4(4);

				send_struct(uart4, &drill_cmd, drill);

				System_printf("Drill command: %i\n", cmd_struct.value);
				System_flush();
			}
		}
	}
}

#endif /* SIMPLE_DRIVE_H_ */
