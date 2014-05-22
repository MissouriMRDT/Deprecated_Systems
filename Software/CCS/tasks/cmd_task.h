/*
 * simple_drive.h
 *
 *  Created on: May 6, 2014
 *      Author: Keenan Johnson
 */

#ifndef CMD_TASK_H_
#define CMD_TASK_H_

#include <string.h>
#include <stdbool.h>
#include "../include/struct_xfer.h"
#include "../include/structs.h"
#include "../Commands/drive_commands.h"

extern Void process_cmds(UArg arg0, UArg arg1)
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

	drill_cmd.direction = 0;
	drill_cmd.goalSpeed = 0;
	drill_cmd.heaterPower = 0;
	drill_cmd.thermoReadings = 0;
	drill_cmd.sensorPower = 0;
	drill_cmd.gasReadings = 0;

	// Gripper struct
	struct gripper_control_struct gripper_cmd;

	while(1)
	{
		// Read cmd from TCP
		cmd_valid = recv_struct( uart7, &cmd_struct, tcp_cmd );

		if ( cmd_valid == true )
		{
			//*************
			// Drive Left
			//*************
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

			//*************
			// Drive Right
			//*************
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
				mux_1( 9 );
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
				mux_1( 9 );
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Left belt
			//*************
			if ( cmd_struct.id == 2004 )
			{
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
				mux_1( 9 );
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//****************
			// Linear Actuator
			//****************
			if ( cmd_struct.id == 2005 )
			{
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
				mux_1( 9 );
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Left Wrist
			//*************
			if ( cmd_struct.id == 2006 )
			{
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
				mux_1( 9 );
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Forearm Group
			//*************
			if ( cmd_struct.id == 2007 )
			{
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
				mux_1( 9 );
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//*************
			// Wrist Group
			//*************
			if ( cmd_struct.id == 2008 )
			{
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
				mux_1( 9 );
				send_struct(uart1, &arm_control, robotic_arm);
			}

			//////////////////////////////
			// Drill Commands
			//////////////////////////////

			//*************
			// Drill Speed
			//**************
			if( cmd_struct.id == 6001 )
			{
				drill_cmd.goalSpeed = cmd_struct.value;

				mux_2(10);
				send_struct(uart2, &drill_cmd, drill);
			}

			//*************
			// Drill Direction
			//**************
			if( cmd_struct.id == 6002 )
			{
				drill_cmd.direction = cmd_struct.value;

				mux_2(10);
				send_struct(uart4, &drill_cmd, drill);
			}

			//*************
			// Heater Power
			//**************
			if( cmd_struct.id == 6003 )
			{
				drill_cmd.heaterPower = cmd_struct.value;

				mux_2(10);
				send_struct(uart4, &drill_cmd, drill);
			}

			//*************
			// Thermo Readings
			//**************
			if( cmd_struct.id == 6004 )
			{
				drill_cmd.thermoReadings = cmd_struct.value;

				mux_2(10);
				send_struct(uart4, &drill_cmd, drill);
			}

			//*************
			// Sensor Power
			//**************
			if( cmd_struct.id == 6005 )
			{
				drill_cmd.sensorPower = cmd_struct.value;

				mux_2(10);
				send_struct(uart4, &drill_cmd, drill);
			}

			//*************
			// Gas Readings
			//**************
			if( cmd_struct.id == 6006 )
			{
				drill_cmd.gasReadings = cmd_struct.value;

				mux_2(10);
				send_struct(uart4, &drill_cmd, drill);
			}

			//////////////////////////////
			// Gripper
			/////////////////////////////

			if ( cmd_struct.id == 6007 )
			{
				gripper_cmd.grip_cmd = cmd_struct.value;

				// Send Command
				mux_3( 11 );
				send_struct(uart3, &gripper_cmd, gripper);
			}
		}
	}
}

#endif /* CMD_TASK_H_ */
