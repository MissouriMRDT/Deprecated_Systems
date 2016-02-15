// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::roveWare
#ifndef ROVECNTRL_H_
#define ROVECNTRL_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "RoveBoard.h"

//=== RoveCCSTiva_RCServo ========
//
//standard rcservo 20000uS period : 1000uS full reverse : 1500uS stop : 2000uS full forward
void roveCntrl_RcServo_SpinMotor(PWM_Handle motor, int16_t speed);



//=== RoveCCSTiva_Roboteq_Ascii_Serial ========
//
//todo David : Ascii Roboteq
void roveCntrl_RoboteqMlb_ConfigRead(UART_Handle motor, void* config_data);
void roveCntrl_RoboteqMlb_ConfigWrite(UART_Handle motor, void* config_data);



#ifdef __cplusplus
}
#endif

#endif // ROVECNTRL_H_
