//
// roveStructs.c
//
// first created:
//
// 03_22_2015_Owen_Chiaventone omc8db@mst.edu
//
// last edited:
//
// 04_07_2015_Judah Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveStructs.h"

int getStructSize(char structId){

	switch(structId){

	case (char)motor_left_id:

			return sizeof(struct motor_control_struct);

	case (char)motor_right_id:

			return sizeof(struct motor_control_struct);

	case bms_emergency_stop_command_id:

		return sizeof(struct bms_emergency_stop_command);

	case bms_cell1_voltage_telem_id ... bms_total_amperage_telem_id:

		return sizeof(struct power_board_bms_telem);

	case power_board_command_id:

		return sizeof(struct power_board_command);

	case power_board_telem_motor1_current_id ... power_board_telem_main_battery_voltage_id:

		return sizeof(struct power_board_bms_telem);

	case (char)wrist_clock_wise...actuator_forward:

				return sizeof(struct robot_arm_command);

		case (char)gripper_open:

				return sizeof(struct gripper_command);

	}//endswitch:		(structId)

	return -1;

}//endfnctn getStructSize(char structId)


