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
#include "../include/json.h"
#include "../include/timing.h"

extern Void process_cmds(UArg arg0, UArg arg1)
{

	// Init UARTs
	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart7;

	extern bool drill_telem_active;
	extern bool gps_telem_active;
	extern bool power_telem_active;

	bool cmd_valid = false;

	// Read buffer
	struct base_station_cmd_struct cmd_struct;

	// Motor Controller Struct
	struct motor_struct _struct;

	// Robotic Arm Struct
	struct arm_control_struct arm_control;

	// Drill struct
	struct drill_Controls drill_cmd;

	// Science Payload
	struct science_payload_control_struct science_cmd;

	// Lighting board
	struct lighting_board_struct light_cmd;

	// Camera Control
	struct camera_control_struct camera_cmd;

	science_cmd.lb395 = 0;
	science_cmd.lb440 = 0;
	science_cmd.doorserv = 0;

	drill_cmd.direction = 0;
	drill_cmd.goalSpeed = 0;
	drill_cmd.heaterPower = 0;
	drill_cmd.thermoReadings = 0;
	drill_cmd.sensorPower = 0;
	drill_cmd.gasReadings = 0;

	light_cmd.red = 0;
	light_cmd.green = 0;
	light_cmd.blue = 0;
	light_cmd.pwm1 = 0;
	light_cmd.pwm2 = 0;
	light_cmd.pwm3 = 0;
	light_cmd.d1 = 0;
	light_cmd.d2 = 0;

	// Gripper struct
	struct gripper_control_struct gripper_cmd;

	while(1)
	{
		// Read cmd from TCP
		cmd_valid = recv_struct( uart7, &cmd_struct, tcp_cmd );

		if ( cmd_valid == true )
		{
			switch ( cmd_struct.id )
			{
				//*************
				// Drive Left
				//*************
				case 4001:
					_struct.value = cmd_struct.value;

					mux_1( 8 );
					mux_2( 7 );
					mux_3( 6 );

					send_struct(uart1, &_struct, motor_controller);
					send_struct(uart2, &_struct, motor_controller);
					send_struct(uart3, &_struct, motor_controller);
					break;

				//*************
				// Drive Right
				//*************
				case 4002:
					_struct.value = cmd_struct.value;

					mux_1( 1 );
					mux_2( 2 );
					mux_3( 3 );

					send_struct(uart1, &_struct, motor_controller);
					send_struct(uart2, &_struct, motor_controller);
					send_struct(uart3, &_struct, motor_controller);
					break;

				//////////////////////////////
				// Robotic ARM Stuff
				/////////////////////////////

				//*************
				// Wrist Commands
				//*************
				case 2001:

					switch( cmd_struct.value )
					{
						case 0: // Counterclockwise
							arm_control.reset =					0;
							arm_control.wristUp = 				0;
							arm_control.wristDown = 			0;
							arm_control.wristClockWise = 		0;
							arm_control.wristCounterClockWise = 1;
							arm_control.elbowUp =				0;
							arm_control.elbowDown = 			0;
							arm_control.elbowClockWise = 		0;
							arm_control.elbowCounterClockWise = 0;
							arm_control.actuatorReverse = 		0;
							arm_control.actuatorForward = 		0;
							arm_control.baseCounterClockWise = 	0;
							arm_control.baseClockWise = 		0;
							break;

						case 1: // Clockwise
							arm_control.reset =					0;
							arm_control.wristUp = 				0;
							arm_control.wristDown = 			0;
							arm_control.wristClockWise = 		1;
							arm_control.wristCounterClockWise = 0;
							arm_control.elbowUp =				0;
							arm_control.elbowDown = 			0;
							arm_control.elbowClockWise = 		0;
							arm_control.elbowCounterClockWise = 0;
							arm_control.actuatorReverse = 		0;
							arm_control.actuatorForward = 		0;
							arm_control.baseCounterClockWise = 	0;
							arm_control.baseClockWise = 		0;
							break;

						case 2: // Down
							arm_control.reset =					0;
							arm_control.wristUp = 				0;
							arm_control.wristDown = 			1;
							arm_control.wristClockWise = 		0;
							arm_control.wristCounterClockWise = 0;
							arm_control.elbowUp =				0;
							arm_control.elbowDown = 			0;
							arm_control.elbowClockWise = 		0;
							arm_control.elbowCounterClockWise = 0;
							arm_control.actuatorReverse = 		0;
							arm_control.actuatorForward = 		0;
							arm_control.baseCounterClockWise = 	0;
							arm_control.baseClockWise = 		0;
							break;

						case 3: // Up
							arm_control.reset =					0;
							arm_control.wristUp = 				1;
							arm_control.wristDown = 			0;
							arm_control.wristClockWise = 		0;
							arm_control.wristCounterClockWise = 0;
							arm_control.elbowUp =				0;
							arm_control.elbowDown = 			0;
							arm_control.elbowClockWise = 		0;
							arm_control.elbowCounterClockWise = 0;
							arm_control.actuatorReverse = 		0;
							arm_control.actuatorForward = 		0;
							arm_control.baseCounterClockWise = 	0;
							arm_control.baseClockWise = 		0;
							break;
					}

					// Send Command
					mux_1( 9 );
					send_struct(uart1, &arm_control, robotic_arm);
					break;

					//*************
					// Elbow Commands
					//*************
					case 2002:

						switch( cmd_struct.value )
						{
							case 0: // Counterclockwise
								arm_control.reset =					0;
								arm_control.wristUp = 				0;
								arm_control.wristDown = 			0;
								arm_control.wristClockWise = 		0;
								arm_control.wristCounterClockWise = 0;
								arm_control.elbowUp =				0;
								arm_control.elbowDown = 			0;
								arm_control.elbowClockWise = 		0;
								arm_control.elbowCounterClockWise = 1;
								arm_control.actuatorReverse = 		0;
								arm_control.actuatorForward = 		0;
								arm_control.baseCounterClockWise = 	0;
								arm_control.baseClockWise = 		0;
								break;

							case 1: // Clockwise
								arm_control.reset =					0;
								arm_control.wristUp = 				0;
								arm_control.wristDown = 			0;
								arm_control.wristClockWise = 		0;
								arm_control.wristCounterClockWise = 0;
								arm_control.elbowUp =				0;
								arm_control.elbowDown = 			0;
								arm_control.elbowClockWise = 		1;
								arm_control.elbowCounterClockWise = 0;
								arm_control.actuatorReverse = 		0;
								arm_control.actuatorForward = 		0;
								arm_control.baseCounterClockWise = 	0;
								arm_control.baseClockWise = 		0;
								break;

							case 2: // Down
								arm_control.reset =					0;
								arm_control.wristUp = 				0;
								arm_control.wristDown = 			0;
								arm_control.wristClockWise = 		0;
								arm_control.wristCounterClockWise = 0;
								arm_control.elbowUp =				0;
								arm_control.elbowDown = 			1;
								arm_control.elbowClockWise = 		0;
								arm_control.elbowCounterClockWise = 0;
								arm_control.actuatorReverse = 		0;
								arm_control.actuatorForward = 		0;
								arm_control.baseCounterClockWise = 	0;
								arm_control.baseClockWise = 		0;
								break;

							case 3: // Up
								arm_control.reset =					0;
								arm_control.wristUp = 				0;
								arm_control.wristDown = 			0;
								arm_control.wristClockWise = 		0;
								arm_control.wristCounterClockWise = 0;
								arm_control.elbowUp =				1;
								arm_control.elbowDown = 			0;
								arm_control.elbowClockWise = 		0;
								arm_control.elbowCounterClockWise = 0;
								arm_control.actuatorReverse = 		0;
								arm_control.actuatorForward = 		0;
								arm_control.baseCounterClockWise = 	0;
								arm_control.baseClockWise = 		0;
								break;
						}

						// Send Command
						mux_1( 9 );
						send_struct(uart1, &arm_control, robotic_arm);
						break;

						//*************
						// Linear Actuator Commands
						//*************
						case 2003:

							switch( cmd_struct.value )
							{
								case 0: //Backward
									arm_control.reset =					0;
									arm_control.wristUp = 				0;
									arm_control.wristDown = 			0;
									arm_control.wristClockWise = 		0;
									arm_control.wristCounterClockWise = 0;
									arm_control.elbowUp =				0;
									arm_control.elbowDown = 			0;
									arm_control.elbowClockWise = 		0;
									arm_control.elbowCounterClockWise = 0;
									arm_control.actuatorReverse = 		1;
									arm_control.actuatorForward = 		0;
									arm_control.baseCounterClockWise = 	0;
									arm_control.baseClockWise = 		0;
									break;

								case 1: // Forward
									arm_control.reset =					0;
									arm_control.wristUp = 				0;
									arm_control.wristDown = 			0;
									arm_control.wristClockWise = 		0;
									arm_control.wristCounterClockWise = 0;
									arm_control.elbowUp =				0;
									arm_control.elbowDown = 			0;
									arm_control.elbowClockWise = 		0;
									arm_control.elbowCounterClockWise = 0;
									arm_control.actuatorReverse = 		0;
									arm_control.actuatorForward = 		1;
									arm_control.baseCounterClockWise = 	0;
									arm_control.baseClockWise = 		0;
									break;
							}

						// Send Command
						mux_1( 9 );
						send_struct(uart1, &arm_control, robotic_arm);
						break;

						//*************
						// Base Servo Commands
						//*************
						case 2004:

							switch( cmd_struct.value )
							{
								case 0: // Counterclockwise
									arm_control.reset =					0;
									arm_control.wristUp = 				0;
									arm_control.wristDown = 			0;
									arm_control.wristClockWise = 		0;
									arm_control.wristCounterClockWise = 0;
									arm_control.elbowUp =				0;
									arm_control.elbowDown = 			0;
									arm_control.elbowClockWise = 		0;
									arm_control.elbowCounterClockWise = 0;
									arm_control.actuatorReverse = 		0;
									arm_control.actuatorForward = 		0;
									arm_control.baseCounterClockWise = 	1;
									arm_control.baseClockWise = 		0;
									break;

								case 1: // Clockwise
									arm_control.reset =					0;
									arm_control.wristUp = 				0;
									arm_control.wristDown = 			0;
									arm_control.wristClockWise = 		0;
									arm_control.wristCounterClockWise = 0;
									arm_control.elbowUp =				0;
									arm_control.elbowDown = 			0;
									arm_control.elbowClockWise = 		0;
									arm_control.elbowCounterClockWise = 0;
									arm_control.actuatorReverse = 		0;
									arm_control.actuatorForward = 		0;
									arm_control.baseCounterClockWise = 	0;
									arm_control.baseClockWise = 		1;
									break;
							}

						// Send Command
						mux_1( 9 );
						send_struct(uart1, &arm_control, robotic_arm);
						break;

						//*************
						// Reset
						//*************
						case 2005:
							arm_control.reset =					1;
							arm_control.wristUp = 				0;
							arm_control.wristDown = 			0;
							arm_control.wristClockWise = 		0;
							arm_control.wristCounterClockWise = 0;
							arm_control.elbowUp =				0;
							arm_control.elbowDown = 			0;
							arm_control.elbowClockWise = 		0;
							arm_control.elbowCounterClockWise = 0;
							arm_control.actuatorReverse = 		0;
							arm_control.actuatorForward = 		0;
							arm_control.baseCounterClockWise = 	0;
							arm_control.baseClockWise = 		0;

							// Send Command
							mux_1( 9 );
							send_struct(uart1, &arm_control, robotic_arm);
							break;

				//////////////////////////////
				// Drill Commands
				//////////////////////////////

				//*************
				// Drill Speed
				//**************
				case 6001:
					drill_cmd.goalSpeed = cmd_struct.value;

					mux_2(10);
					send_struct(uart2, &drill_cmd, drill);

					break;

				//*************
				// Drill Direction
				//**************
				case 6002:
					drill_cmd.direction = cmd_struct.value;

					mux_2(10);
					send_struct(uart4, &drill_cmd, drill);

					break;

				//*************
				// Heater Power
				//**************
				case 6003:
					drill_cmd.heaterPower = cmd_struct.value;

					mux_2(10);
					send_struct(uart4, &drill_cmd, drill);

					break;

				//*************
				// Thermo Readings
				//**************
				case 6004:

					drill_cmd.thermoReadings = cmd_struct.value;

					mux_2(10);
					send_struct(uart4, &drill_cmd, drill);

					break;

				//*************
				// Sensor Power
				//**************
				case 6005:

					drill_cmd.sensorPower = cmd_struct.value;

					mux_2(10);
					send_struct(uart4, &drill_cmd, drill);

					break;

				//*************
				// Gas Readings
				//**************
				case 6006:

					drill_cmd.gasReadings = cmd_struct.value;

					mux_2(10);
					send_struct(uart4, &drill_cmd, drill);

					break;

				//////////////////////////////
				// Gripper
				/////////////////////////////

				case 6007:

					gripper_cmd.grip_cmd = cmd_struct.value;

					// Send Command
					mux_3( 11 );
					send_struct(uart3, &gripper_cmd, gripper);

					break;

				//////////////////////////////
				// Science Payload
				/////////////////////////////

				//*************
				// 395 nm Light
				//**************
				case 6008:

					science_cmd.lb395 = cmd_struct.value;

					// Send command
					mux_4( 12 );
					send_struct(uart4, &science_cmd, science_payload);

					break;

				//*************
				// 440 nm Light
				//**************
				case 6009:

					science_cmd.lb440 = cmd_struct.value;

					// Send command
					mux_4( 12 );
					send_struct(uart4, &science_cmd, science_payload);

					break;

				//*************
				// Door Servo
				//**************
				case 6010:

					science_cmd.doorserv = cmd_struct.value;

					// Send command
					mux_4( 12 );
					send_struct(uart4, &science_cmd, science_payload);

					break;

				// Turn Drill telem on or off
				case 6011:
					if ( cmd_struct.value == 1 )
					{
						drill_telem_active = true;
					}
					else if ( cmd_struct.value == 0 )
					{
						drill_telem_active = false;
					}
					break;

				///////////////////
				// Lighting Board
				///////////////////

				// Red light
				case 6012:
					light_cmd.red = cmd_struct.value;
					mux_4( 12 );
					send_struct(uart4, &light_cmd, lighting_board);
					break;

				// Green light
				case 6013:
					light_cmd.green = cmd_struct.value;
					mux_4( 12 );
					send_struct(uart4, &light_cmd, lighting_board);
					break;

				// Blue light
				case 6014:
					light_cmd.blue = cmd_struct.value;
					mux_4( 12 );
					send_struct(uart4, &light_cmd, lighting_board);
					break;

				// GPS Telem
				case 1006:
					if ( cmd_struct.value == 1 )
					{
						gps_telem_active = true;
					}
					else if ( cmd_struct.value == 0 )
					{
						gps_telem_active = false;
					}
					break;

					/////////////////
					// Camera Control
					/////////////////

					// Camera Pitch
					case 6022:
						camera_cmd.pitch = cmd_struct.value;
						mux_4( 1 );
						send_struct(uart4, &camera_cmd, camera);
						break;

					// Camera Yaw
					case 6023:
						camera_cmd.yaw = cmd_struct.value;
						mux_4( 1 );
						send_struct(uart4, &camera_cmd, camera);
						break;

					// Camera Roll
					case 6024:
						camera_cmd.roll = cmd_struct.value;
						mux_4( 1 );
						send_struct(uart4, &camera_cmd, camera);
						break;

					// Camera Mode
					case 6025:
						camera_cmd.mode = cmd_struct.value;
						mux_4( 1 );
						send_struct(uart4, &camera_cmd, camera);
						break;

					//////////////
					// Power Board
					//////////////
					case 5007:
						if ( cmd_struct.value == 1 )
						{
							power_telem_active = true;
						}
						else if ( cmd_struct.value == 0 )
						{
							power_telem_active = false;
						}
						break;
			}
		}
	}
}

#endif /* CMD_TASK_H_ */
