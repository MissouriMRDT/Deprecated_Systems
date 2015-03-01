//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)

// roveStructXfer.h
//
// first created:
//
// 04_20_2014_Keenan Johnson
//
// last edited:
//
//02_25_2015_Judah Schad_jrs6w7@mst.edu


#pragma once

#ifndef ROVESTRUCTXFER_H_
#define ROVESTRUCTXFER_H_

//globally scoped Texas Instruments (TI) header files

#include "RoverMotherboardMain.h"

//MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "mrdtRoveWare.h"

//TODO

enum peripheral_devices{motor_controller, bms, robotic_arm, tcp_cmd, drill, gripper, science_payload, gps, lighting_board, camera, power_board, test};

//TODO

void send_struct(UART_Handle uart, void* my_struct, enum peripheral_devices device);

//TODO

bool recv_struct( UART_Handle uart, void* my_struct, enum peripheral_devices device );

#endif // ROVESTRUCTXFER_H_
