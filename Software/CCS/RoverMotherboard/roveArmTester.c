// roveComTest.c
//
//  Created on: Mar 23, 2015
//      Author: Connor Walsh
//

#include "roveIncludes/roveWareHeaders/roveArmTester.h"

#define STRUCT_ID_MIN wrist_clock_wise
#define STRUCT_ID_MAX actuator_forward
#define STRUCT_INCREMENT 1

#define MIN_SPEED -1000
#define MAX_SPEED 1000
#define SPEED_INCREMENT 350

#define FOREVER 1

#define MS_DELAY 120

void roveArmTester(UArg arg0, UArg arg1) {
	base_station_msg_struct test_command_msg;
	struct robot_arm_command robot_arm;

	robot_arm.struct_id = STRUCT_ID_MIN;
	robot_arm.speed = MIN_SPEED;
	while (FOREVER) {
		robot_arm.speed = MIN_SPEED;
		robot_arm.struct_id = STRUCT_ID_MIN;
		while (robot_arm.struct_id <= STRUCT_ID_MAX) {
			while (robot_arm.speed < MAX_SPEED) {
				robot_arm.speed = robot_arm.speed + SPEED_INCREMENT;
				robot_arm.struct_id = robot_arm.struct_id + STRUCT_INCREMENT;

				System_printf("Tester Posted struct_id %d, speed, %d\n",
						robot_arm.struct_id, robot_arm.speed);
				System_flush();

				memcpy(&test_command_msg, &robot_arm, sizeof(robot_arm));
				Mailbox_post(fromBaseStationMailbox, &test_command_msg,
						BIOS_WAIT_FOREVER);

				ms_delay(MS_DELAY);

			} //end while

			while (robot_arm.speed > MIN_SPEED) {
				robot_arm.speed = robot_arm.speed - SPEED_INCREMENT;
				robot_arm.struct_id = robot_arm.struct_id - STRUCT_INCREMENT;

				System_printf("Tester Posted struct_id %d, speed, %d\n",
						robot_arm.struct_id, robot_arm.speed);
				System_flush();

				memcpy(&test_command_msg, &robot_arm, sizeof(robot_arm));
				Mailbox_post(fromBaseStationMailbox, &test_command_msg,
						BIOS_WAIT_FOREVER);

				ms_delay(MS_DELAY);

			} //end while

		} //end while

	} //end while

} //end fnctn
