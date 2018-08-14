/*********************************************************************
*
*   HEADER NAME:
*       SYC_pub_timer_prj.h - System Controller Timer Public, Project Specific Declarations
*
*   NOTES:
*       This file is where system timers are be configured.
*
*   Copyright 2002-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _SYC_PUB_TIMER_PRJ
#define      _SYC_PUB_TIMER_PRJ

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

//#include "SYC_pub_timer_prj_s.h"
#include "UTL_pub.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
The following timers count down at a rate of
SYC_TIMER_TICKS_PER_SECOND to zero.  The count value of the
timers should be monitored, and when the timer reaches a
a count of zero, then event should be considered triggered
and the timer count may be reset.  The maximum amount of
measurable time is SYC_TIMER_MAX_TIME.

Note: The assembler timer count value,
syc_TIMER_CNT_FOR_ASSEMBLER, should also be modified to
reflect changes to the enumeration.
----------------------------------------------------------*/
typedef uint8 SYC_timer_type; enum
{
//    SYC_TIMER_IOP_CANET_ADDR,
    SYC_TIMER_IOP_NMEA2K,
    SYC_TIMER_IOP_NMEA2K_ADDR,
//    SYC_TIMER_ADC_INST,
//    SYC_TIMER_ADC_TEST,
    SYC_TIMER_ADC_READ,
	UTL_ASSERT_TIMER,
//    SYC_TIMER_ADC_TRANSITION_DELAY,
//    SYC_TIMER_HWM_ADAPTER,
//    SYC_TIMER_HWM_GAUGE_TST,
//    SYC_TIMER_HWM_HOOKUP_TST,
//    SYC_TIMER_HWM_TRIM_TAB_L,
//    SYC_TIMER_HWM_TRIM_TAB_R,
//    SYC_TIMER_HWM_TRIM_TAB_CAL,
//    SYC_TIMER_HWM_WATER_SPEED,
//    SYC_TIMER_NVM_MAIN,
//    SYC_TIMER_HWM_GENERIC_ADAPTER_SYS,
//    SYC_TIMER_IOP_NMEA2K_INST_ENG,
//    SYC_TIMER_IOP_NMEA2K_INST,
	SYC_TIMER_HWM_LSM9DS1_MAG_CAL,

    SYC_TIMER_CNT
}; /* SYC_timer_type */


/*------------------------------------------------------
Make certain the assembler timer count value is correct.
------------------------------------------------------*/
//UTL_compiler_assert(syc_TIMER_CNT_FOR_ASSEMBLER == SYC_TIMER_CNT, SYC_PUB_TIMER_PRJ);

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
This type defines how timer count values are stored.
----------------------------------------------------------*/
typedef uint8 SYC_timer_count_type;

/*--------------------------------------------------------------------
                            PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

#endif  /* _SYC_PUB_TIMER_PRJ */
