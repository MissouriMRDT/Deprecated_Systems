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

	// Robotic Arm Struct
	struct arm_control_struct arm_control;

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
			// Robotic ARM Stuff
			/////////////////////////////

			//*************
			// Right Wrist
			//*************
			if ( cmd_struct.id == 2001 )
			{
				// Set Mux
				mux_1( 9 );

				// Forward
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 1;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Backward
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 1;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Left Wrist
			//*************
			if ( cmd_struct.id == 2002 )
			{
				// Set Mux
				mux_1( 9 );

				// Forward
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 1;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Backward
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 1;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Right Belt
			//*************
			if ( cmd_struct.id == 2003 )
			{
				// Set Mux
				mux_1( 9 );

				// Forward
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 1;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Backward
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 1;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Left belt
			//*************
			if ( cmd_struct.id == 2004 )
			{
				// Set Mux
				mux_1( 9 );

				// Forward
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 1;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Backward
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 1;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//****************
			// Linear Actuator
			//****************
			if ( cmd_struct.id == 2005 )
			{
				// Set Mux
				mux_1( 9 );

				// Forward
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 1;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Backward
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 1;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Left Wrist
			//*************
			if ( cmd_struct.id == 2006 )
			{
				// Set Mux
				mux_1( 9 );

				// Forward
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 1;
					arm_control.joint6Backward = 0;
				}

				// Backward
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 1;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Forearm Group
			//*************
			if ( cmd_struct.id == 2007 )
			{
				// Set Mux
				mux_1( 9 );

				// Counterclockwise
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 1;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 1;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Clockwise
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 1;
					arm_control.joint4Forward = 1;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Up
				if ( cmd_struct.value == 2 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 1;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 1;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Down
				if ( cmd_struct.value == 3 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 1;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 1;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Wrist Group
			//*************
			if ( cmd_struct.id == 2008 )
			{
				// Set Mux
				mux_1( 9 );

				// Left
				if ( cmd_struct.value == 0 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 1;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 1;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Right
				if ( cmd_struct.value == 1 )
				{
					arm_control.joint1Forward = 1;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 1;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Up
				if ( cmd_struct.value == 2 )
				{
					arm_control.joint1Forward = 0;
					arm_control.joint1Backward = 1;
					arm_control.joint2Forward = 1;
					arm_control.joint2Backward = 0;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Down
				if ( cmd_struct.value == 3 )
				{
					arm_control.joint1Forward = 1;
					arm_control.joint1Backward = 0;
					arm_control.joint2Forward = 0;
					arm_control.joint2Backward = 1;
					arm_control.joint3Forward = 0;
					arm_control.joint3Backward = 0;
					arm_control.joint4Forward = 0;
					arm_control.joint4Backward = 0;
					arm_control.joint5Forward = 0;
					arm_control.joint5Backward = 0;
					arm_control.joint6Forward = 0;
					arm_control.joint6Backward = 0;
				}

				// Send Command
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//////////////////////////////
			// Drill Command
			//////////////////////////////

			if( cmd_struct.id == 5000 )
			{
				drill_cmd.direction = 1;
				drill_cmd.goalSpeed = cmd_struct.value;

				mux_4(4);

				send_struct(uart4, &drill_cmd, drill);

				System_printf("Got data");
				System_flush();

				bool drill_cmd_echo = recv_struct( uart4, &drill_cmd, drill );

				if( drill_cmd_echo )
				{
					System_printf("Got data");
					System_flush();
				}
			}
		}
	}
}

#endif /* SIMPLE_DRIVE_H_ */
