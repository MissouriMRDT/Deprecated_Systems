/*
 * roveStructs.c
 *
 *  Created on: Mar 20, 2015
 *      Author: mrdtdev
 */


#include "../roveWareHeaders/roveStructs.h"

int getStructSize(char structId)
{
	switch(structId)
	{
	case (char)motor_left:
			return sizeof(struct motor_control_struct);
	case (char)motor_right:
			return sizeof(struct motor_control_struct);
	case (char)robot_arm:
			return sizeof(struct mobo_robo_arm_command);
	case (char)gripper:
			return sizeof(struct mobo_gripper_command);
	case (char)drill:
			return sizeof(struct drill_control_struct);

	}//endswitch:		(structId)

	return -1;

}//endfnctn:	gtetStructSize(char structId)


