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

	int motor_speed = 0;

	int16_t arm_speed = 0;

	int i = 0;

		System_printf("roveCmdCntrlr		init! \n");
		System_flush();

	while (FOREVER){

		System_printf("Cmd Cntrl Is PENDING FOR MAIL!");
		System_flush();

		Mailbox_pend(fromBaseStationMailbox, &fromBaseMsg, BIOS_WAIT_FOREVER);

		switch(fromBaseMsg.id){

			// case 0 hack to make a happy switch
			case 0:
			break;

			case motor_left_id:

				//the left motors must be the negative of the right motors. Their phase is backwards

				motor_speed = -( ((struct motor_control_struct*)(&fromBaseMsg))->speed );

				pwmWrite(motor_0, motor_speed);
				pwmWrite(motor_1, motor_speed);
				pwmWrite(motor_2, motor_speed);

			break;

			// end drive motor_left_id

			case motor_right_id:

				motor_speed = ((struct motor_control_struct*)(&fromBaseMsg))->speed;

				pwmWrite(motor_0, motor_speed);
				pwmWrite(motor_1, motor_speed);
				pwmWrite(motor_2, motor_speed);

			break;

			//end drive motor_right_id

			//robotic arm commands defined 201 to 207

			case wrist_clock_wise...e_stop_arm:


			arm_speed = (int16_t)(fromBaseMsg.value[0]);

			System_printf("Struct id: %d\n", ((struct robot_arm_command*)(&fromBaseMsg))->struct_id);
			System_printf("Arm Speed: %d\n", (int16_t)(fromBaseMsg.value[0]) );
			System_flush();

				if(arm_speed < 0){

						roboArmNegativeWrite(fromBaseMsg.id,-(arm_speed), (char*)&fromBaseMsg);

				}else{

						roboArmPositiveWrite(fromBaseMsg.id,(arm_speed), (char*)&fromBaseMsg);

				}//endif

				//defined as 200 on Arm board

				((struct robot_arm_command*)(&fromBaseMsg))->struct_id = robot_arm_id;

			break;

			case gripper_open:

					//TODO ((struct gripper_command*)(&fromBaseMsg))->grip_cmd = 0;

			break;

			default:

				System_printf("\nDefault case reached in CmdCntrl\n");
				System_printf("Error: StructID cannot be handled");
				System_flush();

			break;

			}//endswitch

			//case drill_id

			// adds the start bytes, size byte, and checksum based on what struct id

			System_printf("Struct id: %d\n", ((struct robot_arm_command*)(&fromBaseMsg))->struct_id);
			System_printf("Arm Speed: %d\n", ((struct robot_arm_command*)(&fromBaseMsg))->speed);
			System_flush();

			messageSize = buildSerialStructMessage((void *)&fromBaseMsg, commandBuffer);

			System_printf("Message Size: %d\n", messageSize);

			// TODO change deviceJack = getDeviceJack(fromBaseMsg.id);

			// getDeviceJack(fromBaseMsg.id);

			int deviceJack = ONBOARD_ROVECOMM;

			deviceWrite(deviceJack, commandBuffer, messageSize);

			//debugging only:

			i = 0;

			System_printf("Cmd Cntrl Just Sent!: ");

			while( i <( messageSize ) ){

				System_printf("%d, ", commandBuffer[i]);
				i++;

			}//end while

			System_flush();


	}//endwhile(FOREVER)

	// postcondition: execution will not reach this state unless a serious error occurs

	System_printf("Rove Cmd Cntrl Task Error: Forced Exit\n");
	System_flush();

	// exit Task

	Task_exit();

}//endfnct:		roveCmdCntrl() Task Thread

/* This is the case for ASCII control only

			case motor_left_id:

				//the left motors must be the negative of the right motors. Their phase is backwards

				speed = -((struct motor_control_struct*)(&fromBaseMsg))->speed;

				messageSize = generateMotorCommand(speed, commandBuffer);
				deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize-1));

			break;

			//end drive motor_left_id with ASCII strings

			//case motor_right_id:

				speed = ((struct motor_control_struct*)(&fromBaseMsg))->speed;

				messageSize = generateMotorCommand(speed, commandBuffer);
				deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize-1));

			break;

			// end drive motor_right_id with ASCII strings
*/

void roboArmPositiveWrite(int struct_id, int16_t speed, char* output_buffer){

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
				//((struct robot_arm_command*)(output_buffer))->reset = 0;

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
					//case e_stop_arm:

						//((struct robot_arm_command*)(output_buffer))->reset = 1;
					//break;

					// end robot arm

				}//endswitch(struct_id)

				( (struct robot_arm_command*)(output_buffer) )->speed = speed;

			return;

}//endfnctn

void roboArmNegativeWrite(int struct_id, int16_t speed, char* output_buffer){

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
				//((struct robot_arm_command*)(output_buffer))->reset = 0;

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
