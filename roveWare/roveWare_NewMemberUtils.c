// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// New Members Practice Utilities on URC 2015 Horizon Protocol
//
// mrdt::rovWare

#include "roveWare_NewMemberUtils.h"

void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed){

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

    rovePWM_Write(motor, microseconds);

    return;

} //endfnct roveDriveMotor_ByPWM
