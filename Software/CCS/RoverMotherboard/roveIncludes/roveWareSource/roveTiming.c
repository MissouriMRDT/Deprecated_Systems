// roveTiming.c MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveTiming.h"

//encapsulates the system control call to delay a given number of milliseconds

void ms_delay(int milliseconds) {

    SysCtlDelay(milliseconds * (SysCtlClockGet() / 100));

} //endfnctn ms_delay( int milliseconds )
