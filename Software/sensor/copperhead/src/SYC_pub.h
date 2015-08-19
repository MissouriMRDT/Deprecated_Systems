/*********************************************************************
*
*   HEADER NAME:
*       SYC_pub.h - System Controller Public Declarations
*
*   Copyright 2002-2008 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _SYC_PUB
#define      _SYC_PUB

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "SYC_pub_s.h"
#include "SYC_pub_prj_s.h"
#include "SYC_pub_timer_prj.h"

#include "syc_prv_timer.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
System mode type.  The actual enumerated values are defined
in SYC_pub_s.h.
----------------------------------------------------------*/
typedef uint8 SYC_mode_t8;

/*--------------------------------------------------------------------
                            PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
SYC_main.c variables
----------------------------------------------------------*/
extern boolean          SYC_show_version_flag;
extern SYC_mode_t8      SYC_mode;

/*--------------------------------------------------------------------
                                 MACROS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_in_test_mode - In Test Mode
*
*   DESCRIPTION:
*       Returns true if the system is in test mode.
*
*       boolean SYC_in_test_mode
*               (
*               void
*               )
*
----------------------------------------------------------*/
#if (_TSTBLD == _ON)

    #define SYC_in_test_mode() (SYC_mode == SYC_TEST)

#else

    /* Cannot be in test mode if not a test build. */
    #define SYC_in_test_mode() (FALSE)

#endif /* _TSTBLD */

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_is_timer_expired - Is Timer Expired
*
*   DESCRIPTION:
*       Returns true if timer is expired.  Note that the
*       validity of the SYC_timer_type parameter cannot be
*       checked since this is a macro.
*
*       boolean SYC_get_timer
*               (
*               SYC_timer_type _timer //System timer to query
*               )
*
----------------------------------------------------------*/
#define SYC_is_timer_expired(_timer) (syc_timer_array[(_timer)] == SYC_TIMER_EXPIRED)

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_get_time - Get System Time
*
*   DESCRIPTION:
*       Returns the current system time count value.  The
*       time counts from 0 to syc_CLOCK_MAX_COUNT_VAL at a
*       rate of SYC_timer_ticks_per_second.
*
*       SYC_timer_count_type SYC_get_time
*               (
*               void
*               )
*
----------------------------------------------------------*/
#define SYC_get_time() SYC_get_tick_count()

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_set_timer - Set Timer
*
*   DESCRIPTION:
*       Set the expiration time for a system timer.  The
*       maximum length of time that a timer can measure is
*       SYC_TIMER_TICKS_PER_SECOND.  The timer should
*       be polled (by calling SYC_is_timer_expired()) to
*       determine when it expires.
*
*       An assert triggers if the timer is set to 0.  This
*       prevents instances where the timer is unwittingly
*       set to 0 due to incorrect mathematics.  Use
*       SYC_set_timer_expired() to set a timer to be
*       immediately expired.
*
*       void SYC_set_timer
*               (
*               SYC_timer_type _timer //System timer to configure
*               uint16 _time          //Number of milliseconds from the current time
*               )
*
----------------------------------------------------------*/
//#define calc_tick(_time) ((uint16)((uint32)(_time) * SYC_TIMER_TICKS_PER_SECOND / 1000))

#define SYC_set_timer(_timer, _time)	syc_timer_array[(_timer)] = (_time);
//    {
//    /* Check validity _n for > 1 compiler asserts in the same macro */
//    UTL_compiler_assert((_timer)         <= SYC_TIMER_CNT, SYC_PUB);
//    UTL_compiler_assert((uint32)(_time)  <= SYC_TIMER_MAX_TIME, SYC_PUB_2);
//    UTL_compiler_assert((_time)          != 0, SYC_PUB_3);
//    UTL_compiler_assert(calc_tick(_time) != SYC_TIMER_OFF, SYC_PUB_4);
//    syc_timer_array[(_timer)] = calc_tick(_time);
//    }

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_set_timer_runtime - Set Timer Runtim
*
*   DESCRIPTION:
*       This function is the runtime version of
*       SYC_set_timer() without the compiler assert checks.
*
*       void SYC_set_timer_runtime
*               (
*               SYC_timer_type _timer //System timer to configure
*               uint16 _time          //Number of milliseconds from the current time
*               )
*
----------------------------------------------------------*/

#define SYC_set_timer_runtime(_timer, _time)                                \
    {                                                                       \
    syc_timer_array[(_timer)] = (_time);                           \
    }

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_set_timer_expired - Set Timer Expired
*
*   DESCRIPTION:
*       Sets a system timer to expired.
*
*       void SYC_set_timer
*               (
*               SYC_timer_type _timer //System timer to configure
*               )
*
----------------------------------------------------------*/
#define SYC_set_timer_expired(_timer)                        \
    {                                                        \
    UTL_compiler_assert((_timer) <= SYC_TIMER_CNT, SYC_PUB); \
    syc_timer_array[(_timer)] = (uint16)(SYC_TIMER_EXPIRED);  \
    }

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_set_timer_off - Set Timer Off
*
*   DESCRIPTION:
*       Sets a system timer to off.
*
*       void SYC_set_timer_off
*               (
*               SYC_timer_type _timer //System timer to configure
*               )
*
----------------------------------------------------------*/
#define SYC_set_timer_off(_timer)                        \
    {                                                    \
    syc_timer_array[(_timer)] = (uint16)(SYC_TIMER_OFF); \
    }

/*----------------------------------------------------------
*
*   MACRO NAME:
*       SYC_ms_to_ticks - Convert milliseconds to ticks
*
*   DESCRIPTION:
*       Converts milliseconds to system ticks.  Dependent
*           on SYC_TIMER_TICKS_PER_SECOND
*
*       void ms_to_ticks
*               (
*               uint32 _mstime //Input in milliseconds
*               )
*
----------------------------------------------------------*/
#define SYC_ms_to_ticks(_mstime) ((SYC_timer_tick_type)((uint32)(_mstime) * SYC_TIMER_TICKS_PER_SECOND / 1000))

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
SYC_main.c procedures
----------------------------------------------------------*/

void SYC_hold_in_bb
    (
    void
    );

void SYC_init
    (
    SYC_mode_t8     const new_mode
    );

void SYC_main
    (
    void
    );

void SYC_pwr_off
    (
    void
    );

void SYC_pwrdwn
    (
    void
    );

/*----------------------------------------------------------
SYC_simulator.c procedures
----------------------------------------------------------*/

void SYC_sim_reset_dflts_timer
    (
    void
    );

#endif  /* _SYC_PUB */
