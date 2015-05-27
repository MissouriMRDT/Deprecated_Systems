/*
 * roveAutonomy.h
 *
 *  Created on: May 13, 2015
 *      Author: Owen
 *
 *  Anything that the rover decides to do on its own
 */

#ifndef ROVEAUTONOMY_H_
#define ROVEAUTONOMY_H_

#include "../RoverMotherboardMain.h"
#include "roveStructs.h"

//-------------------------------------
// Predefined commands
//-------------------------------------

static const struct motor_control_struct E_STOP_MOTORS[] = {
		{motor_left_id, 0},
		{motor_right_id, 0}
};


static const struct robot_arm_command E_STOP_ARM[] = {
		{e_stop_arm, 0},
		{e_stop_arm, 0},
		{e_stop_arm, 0},
		{e_stop_arm, 0},
		{e_stop_arm, 0},
		{e_stop_arm, 0},
		{e_stop_arm, 0},
		{e_stop_arm, 0}
};

//-----------------------------------
// Autonomy assistance functions
//
// Most of these produce commands post messages to
// roveCommandCntrl
//-----------------------------------

void emergencyStop();

#endif /* ROVEAUTONOMY_H_ */
