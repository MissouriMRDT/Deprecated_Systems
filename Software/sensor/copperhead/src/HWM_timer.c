/*********************************************************************
*
*   MODULE NAME:
*       HWM_timer.c - System Tick Timer functions
*
*   DESCRIPTION:
*       This file includes the pwrp and init functions for the
*       sys tick timer.  The timer ticks every 10ms.
*
* Copyright 2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "HWM_pub.h"
#include "core_cm0.h"
#include "SYC_pub_s.h"
#include "syc_prv_timer.h"
#include "SYC_pub_timer_prj.h"
#include <String.h>

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

#define TICKS   12000   /*1ms interrupts*/
#define TICK_TIME  ( ( TICKS / SYSCTL_IRC_FREQ ) * 1000 ) // System tick timer in ms
#define SysTick_enable 0

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

volatile uint16 syc_timer_array[SYC_TIMER_CNT];
static uint32 time_count;
static uint32 old_time_ms;
static uint32 old_time_us;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*********************************************************************
*
*   PROCEDURE NAME:
*       hwm_timer_pwrp
*
*   DESCRIPTION:
*       This procedure defaults the timer values to off.
*
*********************************************************************/

void hwm_timer_pwrp
    (
    void
    )
{

    memset(&syc_timer_array, SYC_TIMER_OFF, sizeof( syc_timer_array ) );

}   /* hwm_timer_pwrp() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       hwm_timer_init
*
*   DESCRIPTION:
*       This procedure initializes the sys tick timer.
*
*********************************************************************/

void hwm_timer_init
    (
    void
    )
{

    SysTick_Config(TICKS);
    time_count = 0;
    old_time_ms = 0;
    old_time_us = 0;

}   /* hwm_timer_init() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       SysTick_Handler
*
*   DESCRIPTION:
*       This is the interrupt handler for the sys tick timer.
*       It decrements the values of the syc_timer_array every 10ms.
*
*********************************************************************/

void SysTick_Handler
    (
    void
    )
{

    int i;
    for(i = 0; i < SYC_TIMER_CNT; i++ )
        {
        if( ( syc_timer_array[i] > 0 ) && ( syc_timer_array[i] != SYC_TIMER_OFF ) )
            {
            syc_timer_array[i] -= 1;
            }
        }
    time_count++;

}   /* SysTick_Handler() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_get_time_diff_ms
*
*   DESCRIPTION:
*		Procedure finds the time difference in ms from the last
*		time it was called.  It must be called once first to
*		establish the old_time_ms.  It must also be called less
*		than once a minute to get a valid time difference.
*
*********************************************************************/

uint32 HWM_get_time_diff_ms
    (
    void
    )
{
	uint32 new_time_ms;
	uint32 time_diff_ms;

	new_time_ms = time_count;
	if(new_time_ms > old_time_ms)
	{
		time_diff_ms = new_time_ms - old_time_ms;
	}
	else
	{
		time_diff_ms = new_time_ms + (4294967296 - old_time_ms);
	}
	old_time_ms = new_time_ms;

    return time_diff_ms;
}   /* HWM_get_time_diff_ms() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_get_time_diff_us
*
*   DESCRIPTION:
*		Procedure finds the time difference in us from the last
*		time it was called.  It must be called once first to
*		establish the old_time_us.  It must also be called less
*		than once a minute to get a valid time difference.
*
*********************************************************************/

uint32 HWM_get_time_diff_us
    (
    void
    )
{
    uint32 new_time_ms;
    uint32 time_diff;
    uint32 new_time_us;

    new_time_ms = time_count;
    if(new_time_ms >= old_time_ms)
    {
        time_diff = new_time_ms - old_time_ms;
    }
    else
    {
        time_diff = new_time_ms + (4294967296 - old_time_ms);
    }
    old_time_ms = new_time_ms;

    new_time_us = SysTick->VAL;
    if(new_time_us < old_time_us)
    {
        time_diff = ( ( old_time_us - new_time_us ) / ( SYSCTL_IRC_FREQ / 1000000 ) ) + ( time_diff * 1000 ) ;
    }
    else
    {
        time_diff = ( ( old_time_us + (TICKS - new_time_us) ) / ( SYSCTL_IRC_FREQ / 1000000 ) ) + ( ( time_diff - 1 ) * 1000 );
    }
    old_time_us = new_time_us;

    return time_diff;
}   /* HWM_get_time_diff() */


/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_get_random_nmbr
*
*   DESCRIPTION:
*       This procedure grabs the value from the sys tick timer
*       register for the random number.
*
*********************************************************************/

uint8 HWM_get_random_nmbr
    (
    void
    )
{

    return ( SysTick->VAL );

}   /* HWM_get_random_nmbr() */

