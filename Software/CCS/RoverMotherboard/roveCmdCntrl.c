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

Void roveCmdCntrl(UArg arg0, UArg arg1) {

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
	int deviceJack;
	int motor_speed = 0;

	int16_t arm_speed = 0;

	int i = 0;

	System_printf("roveCmdCntrlr		init! \n\n");

	System_flush();

	while (FOREVER) {

//		System_printf("CmdCntrl Is PENDING FOR MAIL!\n\n");
//		System_flush();

		Mailbox_pend(fromBaseStationMailbox, &fromBaseMsg, BIOS_WAIT_FOREVER);

		switch (fromBaseMsg.id) {

		// case 0 hack to make a happy switch
		case 0:
			break;

		case motor_left_id:
			//the left motors must be the negative of the right motors. Their phase is backwards

			motor_speed = -( ( (struct motor_control_struct*)(&fromBaseMsg))->speed );

			DriveMotor(motor_0, motor_speed);
			DriveMotor(motor_1, motor_speed);
			DriveMotor(motor_2, -motor_speed);

			break;

			// end drive motor_left_id

		case motor_right_id:

			motor_speed = ( ( (struct motor_control_struct*)(&fromBaseMsg))->speed );

			DriveMotor(motor_3, -motor_speed);
			DriveMotor(motor_4, motor_speed);
			DriveMotor(motor_5, -motor_speed);

			break;

			//end drive motor_right_id

		default:
			deviceJack = getDeviceJack(fromBaseMsg.id);
			if(getStructSize(fromBaseMsg.id) !=  -1) // Invalid
			{
				messageSize = buildSerialStructMessage((void *) &fromBaseMsg,
						commandBuffer);

				System_printf("Message Size: %d\n", messageSize);
				deviceWrite(deviceJack, commandBuffer, messageSize);
			}
			break;

		} //endswitch

		//debugging only:

//		i = 0;
//
//		System_printf("Cmd Cntrl Just Sent!: ");
//
//		while (i < (messageSize)) {
//
//			System_printf("%d, ", commandBuffer[i]);
//			i++;
//
//		} //end while
	}
	System_flush();

	System_printf("Rove Cmd Cntrl Task Error: Forced Exit\n");
	System_flush();

	Task_exit();

} //endfnct:		roveCmdCntrl() Task Thread
/* This is the case for ASCII control only

 case motor_left_id:

 //the left motors must be the negative of the right motors. Their phase is backwards

 speed = -((struct motor_control_struct*)(&fromBaseMsg))->speed;

 messageSize = generateMotorCommand(speed, commandBuffer);
 deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize-1));

 break;


 //case motor_right_id:

 speed = ((struct motor_control_struct*)(&fromBaseMsg))->speed;

 messageSize = generateMotorCommand(speed, commandBuffer);
 deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize-1));

 break;

 // end drive motor_right_id with ASCII strings
 */

/*This is
 for ASCII control only
 *
 case motor_left_id:

 // TODO implement correct Jack for Motor Comm Board

 //the left motors must be the negative of the right motors. Their phase is backwards

 speed = -((struct motor_control_struct*)(&fromBaseMsg))->speed;

 //protect from the max and min for the motorcontroller

 if (speed > 999) {

 speed = 999;
 } //endif

 if (speed < -999) {

 speed = -999;
 } //endif

 messageSize = generateMotorCommand(speed, commandBuffer);
 deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize - 1));

 System_printf("commandBuffer holds %s \n", commandBuffer);
 System_flush();

 System_printf("messageSize holds %d \n", messageSize);
 System_flush();

 System_printf("speed holds %d \n", speed);
 System_flush();

 break;

 //end drive motor_left_id with ASCII strings

 //case motor_right_id:

 speed = ((struct motor_control_struct*) (&fromBaseMsg))->speed;

 //protect from the max and min for the motorcontroller

 if (speed > 999) {

 speed = 999;
 } //endif

 if (speed < -999) {

 speed = -999;
 } //endif

 messageSize = generateMotorCommand(speed, commandBuffer);
 deviceWrite(ONBOARD_ROVECOMM, commandBuffer, (messageSize - 1));

 System_printf("commandBuffer holds %s \n", commandBuffer);
 System_flush();

 System_printf("messageSize holds %d \n", messageSize);
 System_flush();

 System_printf("speed holds %d \n", speed);
 System_flush();

 break;

 // end drive motor_right_id with ASCII strings
 */
