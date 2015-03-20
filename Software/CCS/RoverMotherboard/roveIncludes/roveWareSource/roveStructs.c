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
	case (char)robot_arm:
			return sizeof(struct arm_control_struct);
	default:
		return 1;
	}
	return -1;
}


