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

    case motor_left_id:
        return sizeof(struct motor_control_struct);

    case motor_right_id:
        return sizeof(struct motor_control_struct);

    case PTZ_Cam_id_0...PTZ_Cam_id_10:
    		return sizeof(struct PTZ_Cam_Ctrl);

    case bms_emergency_command_id:
        return sizeof(struct bms_emergency_command);
/*
    case bms_cell1_voltage_telem_id ... bms_total_amperage_telem_id:
        return sizeof(struct power_board_bms_telem);

    case power_board_command_id:
        return sizeof(struct power_board_command);

    case power_board_telem_motor1_current_id
            ... power_board_telem_main_battery_voltage_id:
        return sizeof(struct power_board_bms_telem);
*/
    case wrist_clock_wise ... drill_forward:
        return sizeof(struct base_station_robot_arm_command);
/*
    case (char) robot_arm_constant_speed_id:
        return sizeof(struct robot_arm_command);
*/
    case gps_telem_reply:
            return sizeof(struct gps_telem);

    case science_telem_request_id:
    				return sizeof(struct science_telem_request);

    case PH_telem_id:
    				return sizeof(struct PH_telem);

    case moisture_telem_id:
    				return sizeof(struct moisture_telem);

    case CCD_telem_packet_id:
    				return sizeof(struct CCD_telem_packet);

    } //endswitch:		(structId)

    return -1;

} //endfnctn getStructSize(char structId)

