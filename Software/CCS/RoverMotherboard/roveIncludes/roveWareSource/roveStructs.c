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
	case (char)motor_left_id:
			return sizeof(struct motor_control_struct);
	case (char)motor_right_id:
			return sizeof(struct motor_control_struct);
	case (char)robot_arm_id:
			return sizeof(struct robot_arm_command);
	case (char)gripper_id:
			return sizeof(struct gripper_command);
	case (char)drill_id:
			return sizeof(struct drill_command);

	}//endswitch:		(structId)

	return -1;

}//endfnctn:	gtetStructSize(char structId)


