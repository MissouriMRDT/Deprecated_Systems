// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// New Members Practice Utilities on URC 2015 Horizon Protocol
//
// mrdt::rovWare

#ifndef ROVEWARE_NEWMEMBERUTILS_H_
#define ROVEWARE_NEWMEMBERUTILS_H_

#include "roveWare_tivaWrappers.h"

#define LIN_ACT_FORWARD 0xE1
#define LIN_ACT_REVERSE 0xE0

#define actuator_increment 207

typedef struct linear_actuator_struct {

    uint8_t command_byte;
    uint8_t speed;

}__attribute__((packed)) linear_actuator_struct, *linear_actuator_struct_ptr;

//roveWare Control Routines
void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed);

void roveDrivePolulu_LinActCmd(int tiva_pin, int16_t speed);

//TODO Add New Member Functions (Dynamixel and Polulo Wrappers)

#endif // ROVEWARE_NEWMEMBERUTILS_H_
