/*********************************************************************
*
*   MODULE NAME:
*       IOP_nmea2k_inst.c - NMEA 2000 Adapter Instance Manager
*
*   DESCRIPTION:
*       Handles automatic setting of NMEA 2000 Adapter instance.
*
*   PUBLIC PROCEDURES:
*       Name                        Title
*       --------------------------- --------------------------------------
*
*   PRIVATE PROCEDURES:
*       Name                        Title
*       --------------------------- --------------------------------------
*       iop_nmea2k_inst_init        Adapter Instance Initialization
*       iop_nmea2k_inst_rcvd        Adapter Instance was Received
*       iop_nmea2k_inst_tsk         Adapter Instance Task
*
*   LOCAL PROCEDURES:
*       Name                        Title
*       --------------------------- --------------------------------------
*
*   Copyright 2007-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log[5]$
* $NoKeywords$
*********************************************************************/

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "HWM_pub.h"
#include "NVM_pub.h"
#include "SYC_pub.h"
#include "UTL_pub.h"

#include "iop_prv_nmea2k_inst.h"

/*----------------------------------------------------------
Compile out this file if no nmea2k support.
----------------------------------------------------------*/
#if ( SYC_NMEA2K_SUPPORT == TRUE )

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Maximum number of sensors allowed. We will only try
to claim one of the first n adapter instances.
----------------------------------------------------------*/
#define MAX_RUDDER_SENSORS      1
#define MAX_ENGINE_SENSORS      8
#define MAX_FLUID_SENSORS       2   /* 2 Instances PER Fluid Type allowed. */
#define MAX_TEMPERATURE_SENSORS 2   /* 2 Instances PER Temperature Source allowed. */
#define LARGEST_NUM_SENSORS     8   /* Must update this value based on largest Max value. */

/*----------------------------------------------------------
On a conflict, wait between 3 and 15 seconds before
switching. Gather data for the 3 seconds prior to switching
to determine which instances are free.
----------------------------------------------------------*/
#define TASK_PERIOD_INST_CONFLICT_TIMER  1000 /* ms */
#define MIN_SWITCH_TIME                  3000 /* ms */
#define MAX_SWITCH_TIME                 15000 /* ms */
#define LISTEN_PERIOD                    3000 /* ms */

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

/*----------------------------------------------------------
Bitfield indicating if an adapter instance has been heard.
----------------------------------------------------------*/
static __no_init uint8          my_adapter_insts_used[ (LARGEST_NUM_SENSORS + 7) / 8 ];

static __no_init uint8          my_conflict_timer;

static __no_init boolean        my_search_again;

/*--------------------------------------------------------------------
                                 MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

uint8 max_instances
    (
    void
    );

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_inst_init - Adapter Instance Initialization
*
*   DESCRIPTION:
*       Initializes module.
*
*********************************************************************/
void iop_nmea2k_inst_init
    (
    void
    )
{
/*----------------------------------------------------------
Set globals.
----------------------------------------------------------*/
my_conflict_timer = 0;
my_search_again   = TRUE;

/*----------------------------------------------------------
Start task timer.
----------------------------------------------------------*/
SYC_set_timer_expired( SYC_TIMER_IOP_NMEA2K_INST );
} /* iop_nmea2k_inst_init() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_inst_rcvd - Adapter Instance was Received
*
*   DESCRIPTION:
*       Periodic task for automatically changing instance.
*
*********************************************************************/
void iop_nmea2k_inst_rcvd
    (
    uint8   inst                    /* instance heard */
    )
{
/*----------------------------------------------------------
Don't autoswitch if not enabled.
----------------------------------------------------------*/
if( NVM_read_nonvol( iop_nmea2k_adapter_inst_auto ) == FALSE )
    {
    return;
    }

if( my_conflict_timer != 0 )
    {
    /*------------------------------------------------------
    We have already detected a conflict. Mark this instance
    if it is within the listen period.
    ------------------------------------------------------*/
    if( ( my_conflict_timer <= (LISTEN_PERIOD / TASK_PERIOD_INST_CONFLICT_TIMER) )
     && ( inst < max_instances() ) )
        {
        my_adapter_insts_used[inst / 8] |= 1 << (inst % 8);
        }
    }
else if( inst == NVM_read_nonvol( iop_nmea2k_adapter_inst ) )
    {
    /*------------------------------------------------------
    New conflict detected. Start timer. Reset table.
    ------------------------------------------------------*/
    my_conflict_timer = ( HWM_get_random_nmbr()
                          % (((MAX_SWITCH_TIME - MIN_SWITCH_TIME) / TASK_PERIOD_INST_CONFLICT_TIMER) + 1) )
                        + (MIN_SWITCH_TIME / TASK_PERIOD_INST_CONFLICT_TIMER);

    UTL_memset( my_adapter_insts_used, 0, sizeof( my_adapter_insts_used ) );
    }
} /* iop_nmea2k_inst_rcvd() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_inst_tsk - Adapter Instance Task
*
*   DESCRIPTION:
*       Adapter instance main task.
*
*********************************************************************/
void iop_nmea2k_inst_tsk
    (
    void
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8   inst;
boolean higher_inst_found;

if( SYC_is_timer_expired( SYC_TIMER_IOP_NMEA2K_INST ) == FALSE )
    {
    /*------------------------------------------------------
    Don't execute until the timer expires.
    ------------------------------------------------------*/
    return;
    }

/*----------------------------------------------------------
Restart the timer.
----------------------------------------------------------*/
SYC_set_timer( SYC_TIMER_IOP_NMEA2K_INST, TASK_PERIOD_INST_CONFLICT_TIMER );

/*----------------------------------------------------------
Don't autoswitch if not enabled.
----------------------------------------------------------*/
if( NVM_read_nonvol( iop_nmea2k_adapter_inst_auto ) == FALSE )
    {
    return;
    }

/*----------------------------------------------------------
Check if a conflict was detected.
----------------------------------------------------------*/
if( my_conflict_timer != 0 )
    {
    /*------------------------------------------------------
    Decrement the conflict timer.
    ------------------------------------------------------*/
    if( --my_conflict_timer == 0 )
        {
        /*--------------------------------------------------
        Timer expired. Switch now to the lowest available
        instance.
        --------------------------------------------------*/
        for( inst = 0; inst < max_instances(); inst++ )
            {
            if( (my_adapter_insts_used[inst / 8] & 1 << (inst % 8)) == 0 )
                {
                /*------------------------------------------
                Found a valid instance.
                ------------------------------------------*/
                NVM_write_nonvol( iop_nmea2k_adapter_inst, inst );
                break;
                }
            }

        if(my_search_again == TRUE)
            {
            /*--------------------------------------------------
            Check if any instances were heard higher than ours.
            --------------------------------------------------*/
            higher_inst_found = FALSE;
            for( ; inst < max_instances(); inst++ )
                {
                if( (my_adapter_insts_used[inst / 8] & 1 << (inst % 8)) != 0 )
                    {
                    higher_inst_found = TRUE;
                    break;
                    }
                }

            /*--------------------------------------------------
            Initiate a conflict with our own instance if we just
            picked the highest one, since everyone could have
            moved off of the lowest instance.
            --------------------------------------------------*/
            if( higher_inst_found == FALSE )
                {
                iop_nmea2k_inst_rcvd( NVM_read_nonvol( iop_nmea2k_adapter_inst ) );
                my_search_again = FALSE;
                }
            }
        else
            {
            my_search_again = TRUE;
            }
        }
    }
} /* iop_nmea2k_inst_tsk() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       max_instances - Returns the maximum number of instances.
*
*   DESCRIPTION:
*       Returns maximum number of instances for the current Adapter.
*
*********************************************************************/
uint8 max_instances
    (
    void
    )
{
uint8   max;

/*----------------------------------------------------------
Determine the Adapter Type
----------------------------------------------------------*/
switch( HWM_get_adapter_type() )
    {

    case HWM_ADAPTER_RUDDER_ANGLE:
        max = MAX_RUDDER_SENSORS;
        break;

    case HWM_ADAPTER_ENGINE_TILT:
        max = MAX_ENGINE_SENSORS;
        break;

    case HWM_ADAPTER_FLUID_LEVEL:
        max = MAX_FLUID_SENSORS;
        break;

    case HWM_ADAPTER_BENNETT_TRIM:
        /*----------------------------------------------------------
        Bennett Trim Tab Adapter does support multiple instances
        ----------------------------------------------------------*/
        break;

    case HWM_ADAPTER_WATERSPEED_AND_TEMP:
        max = MAX_TEMPERATURE_SENSORS;
        break;

    default:
        UTL_assert_always( UTL_FILE_ADC_CONVERT );
        break;

    }

return( max );
} /* max_instances() */

#endif /* SYC_NMEA2K_SUPPORT */
