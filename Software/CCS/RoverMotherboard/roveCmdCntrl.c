// roveCmdCtrl.c
//
// first created:
//
// 01_22_2015_Owen_Chiaventone omc8db@mst.edu
//
// last edited:
//
// 03_08_2015 Connor Walsh cwd8d@mst.edu
//
// 04_07_2015_Judah Schad_jrs6w7@mst.edu
//
// this implements a single function BIOS thread that acts as the RoverMotherboard.cfg roveCmdCtrlTask handle
//
// recieves commands from roveTCPHandler in roveCom protocol using TI.Mailbox.from object
//
// sends pwm commands to motors, and uart commands to robot arm
//
// BIOS_start in main inits this as the roveCmdCntrlTask Thread
//
// this is a RoverMotherboard.cfg object::roveCmdCntrlTask::		priority 3, vital_flag = t, 2048 persistent private stack

#include "roveIncludes/roveWareHeaders/roveCmdCntrl.h"

Void roveCmdCntrl(UArg arg0, UArg arg1){

	//const FOREVER hack to kill the 'unreachable statement' compiler warning

	extern const uint8_t FOREVER;

	//initialized in main

	extern PWM_Handle motor_0;
	extern PWM_Handle motor_1;
	extern PWM_Handle motor_2;
	extern PWM_Handle motor_3;
	extern PWM_Handle motor_4;
	extern PWM_Handle motor_5;

	base_station_msg_struct fromBaseMsg;

	char commandBuffer[MAX_COMMAND_SIZE + 4];

	int messageSize;

	int speed = 0;

	int i = 0;

					System_printf("roveCmdCntrlr		init! \n");
					System_flush();

	while (FOREVER){

		System_printf("Cmd Cntrl Is PENDING FOR MAIL!");
		System_flush();

		Mailbox_pend(fromBaseStationMailbox, &fromBaseMsg, BIOS_WAIT_FOREVER);

					//System_printf("2:	 Cmd Cntrl Just RECIEVED PENDED MAIL! ID: %d \n", fromBaseMsg.id);
					//System_flush();

		switch(fromBaseMsg.id){

			// case 0 hack to make a happy switch
			case 0:
			break;

/* This is for ASCII control only
 *
			case motor_left_id:

				// TODO implement correct Jack for Motor Comm Board

				//the left motors must be the negative of the right motors. Their phase is backwards

				speed = -((struct motor_control_struct*)(&fromBaseMsg))->speed;

				//protect from the max and min for the motorcontroller

				if (speed > 999){

					speed = 999;
				}//endif

				if (speed < -999){

						speed = -999;
				}//endif

				messageSize = generateMotorCommand(speed, commandBuffer);
				deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize-1));

							System_printf("commandBuffer holds %s \n", commandBuffer);
							System_flush();

							System_printf("messageSize holds %d \n", messageSize);
							System_flush();

							System_printf("speed holds %d \n", speed);
							System_flush();

			break;

			//end drive motor_left_id with ASCII strings

			//case motor_right_id:

				speed = ((struct motor_control_struct*)(&fromBaseMsg))->speed;

				//protect from the max and min for the motorcontroller

				if (speed > 999){

					speed = 999;
				}//endif

				if (speed < -999){

						speed = -999;
				}//endif

				messageSize = generateMotorCommand(speed, commandBuffer);
				deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize-1));

							System_printf("commandBuffer holds %s \n", commandBuffer);
							System_flush();

							System_printf("messageSize holds %d \n", messageSize);
							System_flush();

							System_printf("speed holds %d \n", speed);
							System_flush();

			break;

			// end drive motor_right_id with ASCII strings
*/

			case motor_left_id:

				//the left motors must be the negative of the right motors. Their phase is backwards

				speed = -( ((struct motor_control_struct*)(&fromBaseMsg))->speed );

							//System_printf("left speed before conversion holds %d \n", speed);

				//protect from the max and min for the motorcontroller

				if(speed > 999){

					speed = 999;
				}//endif

				if(speed < -999){

						speed = -999;
				}//endif

				pwmWrite(motor_0, speed);
				pwmWrite(motor_1, speed);
				pwmWrite(motor_2, speed);

			break;

			// end drive motor_left_id

			case motor_right_id:

				speed = ((struct motor_control_struct*)(&fromBaseMsg))->speed;

								//System_printf("right speed before conversion holds %d \n", speed);

				//protect from the max and min for the motorcontroller

				if(speed > 999){

					speed = 999;
				}//endif

				if(speed < -999){

						speed = -999;
				}//endif

				pwmWrite(motor_0, speed);
				pwmWrite(motor_1, speed);
				pwmWrite(motor_2, speed);

			break;

			//end drive motor_right_id

			//robotic arm commands defined 201 to 207
			case wrist_clock_wise...e_stop_arm:

				speed = fromBaseMsg.value[0];

				if(speed < 0){

						roboArmNegativeWrite(fromBaseMsg.id,-speed, &fromBaseMsg);

				}else{

						roboArmPositiveWrite(fromBaseMsg.id,speed, &fromBaseMsg);

				}//endif

			break;

			case gripper_open:

					//TODO ((struct gripper_command*)(&fromBaseMsg))->grip_cmd = 0;

			break;

			default:

				System_printf("\nDefault case reached in CmdCnt\n");
				System_printf("Error: StructID cannot be handled");
				System_flush();

			break;

			}//endswitch

			//case drill_id

			// adds the start bytes, size byte, and checksum based on what struct id

			System_printf("First Char: %d\n", fromBaseMsg.value[0]);
			System_printf("When I cast: %d\n", ((struct robot_arm_command*)(&fromBaseMsg))->reset);
			System_flush();

			messageSize = buildSerialStructMessage((void *)&fromBaseMsg, commandBuffer);

			System_printf("Message Size: %d\n", messageSize);
			System_flush();

			// TODO change deviceJack = getDeviceJack(fromBaseMsg.id);

			// getDeviceJack(fromBaseMsg.id);

			int deviceJack = ONBOARD_ROVECOMM;

			deviceWrite(deviceJack, commandBuffer, messageSize);

			//debugging only:

			i = 0;

			while( i <( messageSize ) ){


			System_printf("Cmd Cntrl Just Sent!: %d\n", commandBuffer[i]);
			System_flush();

			i++;

			}//end for

	}//endwhile(FOREVER)

	// postcondition: execution will not reach this state unless a serious error occurs

	System_printf("Rove Cmd Cntrl Task Error: Forced Exit\n");
	System_flush();

	// exit Task

	Task_exit();

}//endfnct:		roveCmdCntrl() Task Thread

void roboArmPositiveWrite(int struct_id, int speed, char* output_buffer){

				//zero out the struct

				((struct robot_arm_command*)(output_buffer))->wristCounterClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->wristClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->wristDown = 0;
				((struct robot_arm_command*)(output_buffer))->wristUp = 0;
				((struct robot_arm_command*)(output_buffer))->elbowDown = 0;
				((struct robot_arm_command*)(output_buffer))->elbowUp = 0;
				((struct robot_arm_command*)(output_buffer))->elbowCounterClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->elbowClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->actuatorReverse = 0;
				((struct robot_arm_command*)(output_buffer))->actuatorForward = 0;
				((struct robot_arm_command*)(output_buffer))->baseCounterClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->baseClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->reset = 0;

				switch( struct_id ){

					//
					case wrist_clock_wise:

						((struct robot_arm_command*)(output_buffer))->wristClockWise = 1;
					break;

					//
					case wrist_up:

						((struct robot_arm_command*)(output_buffer))->wristUp = 1;
					break;

					//
					case elbow_clock_wise:

						((struct robot_arm_command*)(output_buffer))->elbowClockWise = 1;
					break;

					//
					case elbow_up:

						((struct robot_arm_command*)(output_buffer))->elbowUp = 1;
					break;

					//
					case actuator_forward:

						((struct robot_arm_command*)(output_buffer))->actuatorForward = 1;
					break;

					//
					case base_clock_wise:

						((struct robot_arm_command*)(output_buffer))->baseClockWise = 1;
					break;

					//
					case e_stop_arm:

						((struct robot_arm_command*)(output_buffer))->reset = 1;
					break;

					// end robot arm

				}//endswitch(struct_id)

				( (struct robot_arm_command*)(output_buffer) )->speed = speed;

			return;

}//endfnctn

void roboArmNegativeWrite(int struct_id, int speed, char* output_buffer){

				//zero out the struct

				((struct robot_arm_command*)(output_buffer))->wristCounterClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->wristClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->wristDown = 0;
				((struct robot_arm_command*)(output_buffer))->wristUp = 0;
				((struct robot_arm_command*)(output_buffer))->elbowDown = 0;
				((struct robot_arm_command*)(output_buffer))->elbowUp = 0;
				((struct robot_arm_command*)(output_buffer))->elbowCounterClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->elbowClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->actuatorReverse = 0;
				((struct robot_arm_command*)(output_buffer))->actuatorForward = 0;
				((struct robot_arm_command*)(output_buffer))->baseCounterClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->baseClockWise = 0;
				((struct robot_arm_command*)(output_buffer))->reset = 0;

				switch( struct_id ){

					// negative clockwise speed = positive clockwise speed

					case wrist_clock_wise:

						((struct robot_arm_command*)(output_buffer))->wristCounterClockWise = 1;
					break;

					//
					case wrist_up:

						((struct robot_arm_command*)(output_buffer))->wristDown = 1;
					break;

					//
					case elbow_clock_wise:

						((struct robot_arm_command*)(output_buffer))->elbowCounterClockWise = 1;
					break;

					//
					case elbow_up:

						((struct robot_arm_command*)(output_buffer))->elbowDown = 1;
					break;

					//
					case actuator_forward:

						((struct robot_arm_command*)(output_buffer))->actuatorReverse = 1;
					break;

					case base_clock_wise:

						((struct robot_arm_command*)(output_buffer))->baseCounterClockWise = 1;
					break;

				}//endswitch(struct_id)

				( (struct robot_arm_command*)(output_buffer) )->speed = speed;

			return;

}//endfnctn roboArmNegativeWrite
