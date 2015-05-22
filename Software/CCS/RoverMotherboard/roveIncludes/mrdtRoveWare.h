//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)

// mrdtRoveWare.h
//
// first created:
//
// 02_24_2015_Judah Schad_jrs6w7@mst.edu
//
// last edited:
//
// 04_07_2015_Judah Schad_jrs6w7@mst.edu

#pragma once

#ifndef MRDTROVEWARE_H_
#define MRDTROVEWARE_H_

// jump table needs sequential integers for compiler to optimize switch statements run in O(1)
// any non consecutive integer #defines will revert to if-else-else that runs in O(n)

// hardware parameters

// mux select line pins

// U3_MUX_S0 PH0
// U3_MUX_S1 PH1
// U4_MUX_S0 PM6
// U4_MUX_S1 PM7
// U5_MUX_S0 PL0
// U5_MUX_S1 PL1
// U6_MUX_S0 PK2
// U6_MUX_S1 PK3
// U7_MUX_S0 PE0
// U7_MUX_S1 PE1

#define U3_MUX_S0 0
#define U3_MUX_S1 1
#define U4_MUX_S0 2
#define U4_MUX_S1 3
#define U5_MUX_S0 4
#define U5_MUX_S1 5
#define U6_MUX_S0 6
#define U6_MUX_S1 7
#define U7_MUX_S0 8
#define U7_MUX_S1 9

// uarts

// Uart pins:
// U2RX PA6
// U2TX PA7
// U3RX PA4
// U3TX PA5
// U4RX PK0
// U4TX PK1
// U5RX PC6
// U5TX PC7
// U6RX PP0
// U6TX PP1
// U7RX PC4
// U7TX PC5

#define U2RX uart2
#define U2TX uart2
#define U3RX uart3
#define U3TX uart3
#define U4RX uart4
#define U4TX uart4
#define U5RX uart5
#define U5TX uart5
#define U6RX uart6
#define U6TX uart6
#define U7RX uart7
#define U7TX uart7

// special devices
#define ARM_JACK 7

#define POWER_BOARD_ON_MOB 18
#define GPS_ON_MOB 19

// PWM Lines init as handles

// MOTOR_0 PF1
// MOTOR_1 PF2
// MOTOR_2 PF3
// MOTOR_3 PG0
// MOTOR_4 PG1
// MOTOR_5 PK4
//
// Extra unused pwm capable pins
// PK5
// PM0
// PM6

// Network Parameters

// tcp ip socket flags

#define NOT_CONNECTED -1
#define CONNECTED 1

// sending timeout in seconds

#define NETWORK_TIMEOUT 6

// hardcodes the IP of the base station
#define RED_IP "192.168.1.2"

// hardcodes the TCP port

#define TCPPORT 11000

// TCPHandler switch handles

#define CONSOLE_COMMAND		0x00
#define SYNCHRONIZE_STATUS	0x01
#define COMMAND_METADATA	0x02
#define TELEM_METADATA		0x03
#define ERROR_METADATA		0x04
#define ROVER_COMMAND		0x05
#define ROVER_TELEM			0x06
#define ROVER_ERROR			0x07
#define JSON_START_BYTE 	'{'

// TCP Sending Parameters

#define SEND_TCP_TASK_PRIORITY 2

#define RECV_UART_NONBLOCK_TASK_PRIORITY 2

#define SEND_KEEPALIVE_DELAY_TICKS 50 //Can also be set to BIOS_WAIT_FOREVER or BIOS_NO_WAIT

// hardware

#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

// size in bytes of longest command that can be recieved from the base station

#define MAX_COMMAND_SIZE 30
#define MAX_TELEM_SIZE 30

// struct id

#define	test_device_id 									99
#define	motor_left_id 									100
#define	motor_right_id 									101

#define gps_telem_reply                                 140

#define	bms_emergency_stop_command_id					150

/*
#define bms_cell1_voltage_telem_id						151
#define bms_cell2_voltage_telem_id						152
#define bms_cell3_voltage_telem_id						153
#define bms_cell4_voltage_telem_id						154
#define bms_cell5_voltage_telem_id						155
#define bms_cell6_voltage_telem_id						156
#define bms_cell7_voltage_telem_id						157
#define bms_cell8_voltage_telem_id						158
#define bms_pack_voltage_telem_id						159
#define bms_total_amperage_telem_id						160

#define	power_board_command_id 							170
#define power_board_telem_motor1_current_id 			180
#define power_board_telem_motor2_current_id 			181
#define power_board_telem_motor3_current_id 			182
#define power_board_telem_motor4_current_id 			183
#define power_board_telem_motor5_current_id 			184
#define power_board_telem_motor6_current_id 			185
#define power_board_telem_aux_current_id				186
#define power_board_telem_5V_bus_current_id				187
#define power_board_telem_12v_critical_bus_current_id	188
#define power_board_telem_12v_highpower_bus_current_id	189
#define power_board_telem_robotarm_bus_current_id		190
#define power_board_telem_main_battery_voltage_id		191

// robot arm values

//deprecated in favor of variable speed
#define	robot_arm_constant_speed_id 200
*/
// clockwise is positive, counter clockwise is negative

#define wrist_clock_wise 201
#define wrist_up 202
#define elbow_clock_wise 203
#define elbow_up 204
#define base_clock_wise 205
#define e_stop_arm 206
#define actuator_forward 207

// gripper value

#define gripper_open 208

#define drill_forward 209

// telem_device_id
/*
#define	telem_req_id 254

#define	robot_arm_telem_req_id 0
#define	gripper_telem_req_id 1
#define	drill_telem_req_id 2
#define	bms_telem_req_id 3
#define	power_board_telem_req_id 4
*/
// Custom Drivers

//MRDesign Team:: 	roveWare::		roveCom cmnd || telem :: data structures

#include "roveWareHeaders/roveStructs.h"

//MRDesign Team:: 	roveWare::		roveCom uart :: constructs and instatiates uarts

#include "roveWareHeaders/roveUarts.h"

//MRDesign Team:: 	roveWare::		roveCom timing :: encapsulate system delay

#include "roveWareHeaders/roveTiming.h"

//MRDesign Team:: 	roveWare::		roveCom transfer :: creates message protocol for easyTransfer

#include "roveWareHeaders/roveStructTransfer.h"

//MRDesign Team:: 	roveWare::		roveCom pinMap :: contains the wrappers for the TI hardware resources

#include "roveWareHeaders/roveHardwareAbstraction.h"

//MRDesign Team:: 	roveWare::		roveNet convert json to and from roveCom formatting

#include "roveWareHeaders/roveJson.h"

//DON'T INCLUDE SYS BIOS THREADS in ROVEWARE:

//MRDesign Team:: 	roveWare::		roveNet tcp ip bsd socket BIOS thread service

//#include "roveTcpHandler.h"

//MRDesign Team::roveWare::		    roveCom command and control BIOS thread service

//#include "roveCmdCntrl.h"

//MRDesign Team::roveWare::		    roveCom command and control BIOS thread service

//#include "roveTelemCntrl.h"

//MRDesign Team::roveWare::		    roveCom hardware tester BIOS thread service

//#include "roveHardwareTester.h"

//MRDesign Team::roveWare::		    roveCom structTransfer Tester BIOS thread service

//#include "roveComTest.h"

//MRDesign Team::roveWare::		    roveCom ASCII string MC Tester BIOS thread service

//#include "rovMotorControlTester.h"

#endif // MRDTROVEWARE_H_
