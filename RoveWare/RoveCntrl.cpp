// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
// speed used in BOTH wheel AND joint mode AX12:(WHEEL GoalSpeed :0~2047/0X7FF unit:0.1%):(JOINT GoalSpeed: 0~1023/0X3FF unit: 0.111rpm)
//
// angle ONLY used in joint mode AX12:(JOINT GoalPosition:0~1023/0x3FF) at 0.29 degree
//
// mrdt::rovWare
#include "RoveCntrl.h"

//Standard C lib
#include <string.h>

///////////////::BEGIN//////Horizon Assets ////////////////////////

//standard rcservo : 1000uS full reverse : 1500uS stop : 2000uS full forward
void roveCntrl_RcServo_SpinMotor(rovePWM_Handle motor, int16_t speed){

    int16_t microseconds;

    //scale down to the final range to be between 1000 and 2000
    microseconds = speed / 2;

    //offset so that 1500 is neutral
    microseconds += 1500;

    //protect the upper bound on motor pulse width
    if (microseconds > 2000) {

        microseconds = 2000;
    }//endif

    //protect the lower bound on motor pulse width
    if (microseconds < 1000) {

        microseconds = 1000;
    }//endif

    roveBoard_PWM_write(motor, microseconds);
    return;
} //endfnctn



//todo David : Ascii Roboteq
void roveCntrl_RoboteqMlb_ConfigRead(UART_Handle motor, void* config_data)
{
    //todo David : integrate with Judah/ Reed/ Miles
}//endfnctn

//todo David : Ascii Roboteq
void roveCntrl_RoboteqMlb_ConfigWrite(UART_Handle motor, void* config_data)
{
    //todo David : integrate with Judah/ Reed/ Miles
}//endfnctn
