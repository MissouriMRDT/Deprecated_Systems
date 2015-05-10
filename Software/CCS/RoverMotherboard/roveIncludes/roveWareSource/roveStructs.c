// roveStructs.c MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveStructs.h"

int getStructSize(char structId) {

    switch (structId) {

    case (char) motor_left_id:
        return sizeof(struct motor_control_struct);

    case (char) motor_right_id:
        return sizeof(struct motor_control_struct);

    case bms_emergency_stop_command_id:
        return sizeof(struct bms_emergency_stop_command);

    case bms_cell1_voltage_telem_id ... bms_total_amperage_telem_id:
        return sizeof(struct power_board_bms_telem);

    case power_board_command_id:
        return sizeof(struct power_board_command);

    case power_board_telem_motor1_current_id
            ... power_board_telem_main_battery_voltage_id:
        return sizeof(struct power_board_bms_telem);

    case (char) wrist_clock_wise ... gripper_open:
        return sizeof(struct base_station_robot_arm_command);

    case (char) robot_arm_constant_speed_id:
        return sizeof(struct robot_arm_command);

    case (char) gps_telem_reply:
            return sizeof(struct gps_telem);

    } //endswitch:		(structId)

    return -1;

} //endfnctn getStructSize(char structId)

