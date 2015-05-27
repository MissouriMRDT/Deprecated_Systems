/*
 * roveWatchdog.h
 *
 *  Created on: May 27, 2015
 *      Author: mrdtdev
 */

#ifndef ROVEWATCHDOG_H_
#define ROVEWATCHDOG_H_
#include "../RoverMotherboardMain.h"

Watchdog_Handle rove_init_watchdog(int index);

void watchdog_callback();

#endif /* ROVEWATCHDOG_H_ */
