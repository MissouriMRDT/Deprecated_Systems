/*
 * roveWatchdog.c
 *
 *  Created on: May 27, 2015
 *      Author: mrdtdev
 */
#include "../roveWareHeaders/roveWatchdog.h"

Watchdog_Handle rove_init_watchdog(int index)
{
  Watchdog_Handle watchdog;
  Watchdog_Params params;

  /* Create and enable a Watchdog with resets enabled */
  Watchdog_Params_init(&params);
  params.callbackFxn = watchdog_callback;
  params.resetMode = Watchdog_RESET_ON;

  watchdog = Watchdog_open(index, &params);
  if (watchdog == NULL) {
      System_abort("Error opening Watchdog!\n");
  }
  Watchdog_clear(watchdog);

	return watchdog;
}

void watchdog_callback()
{
	printf("A critical error occurred. Watchdog is activating.\n");
	return;
}

