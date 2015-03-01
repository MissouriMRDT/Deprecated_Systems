//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)
//
// roveTiming.c
//
// first created:
//
// 04_20_2014_Keenan_Johnson
//
// last edited:
//
//02_25_2015_Judah Schad_jrs6w7@mst.edu

//MRDesign Team:: 	roveWare::		encapsulates the system control call to delay a given number of milliseconds

#include "../roveWareHeaders/roveTiming.h"

//encapsulates the system control call to delay a given number of milliseconds

void ms_delay(int milliseconds){

	SysCtlDelay(milliseconds*(SysCtlClockGet() / 100) );

}//endfnct:		ms_delay( int milliseconds )
