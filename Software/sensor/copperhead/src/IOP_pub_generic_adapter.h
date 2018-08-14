/*********************************************************************
*
*   HEADER NAME:
*       IOP_pub_generic_adapter.h - Public IOP definitions for
*                                   each Adapter.
*
* Copyright 2007-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/


#if !defined _IOP_PUB_GENERIC_ADAPTER_H
#define _IOP_PUB_GENERIC_ADAPTER_H

#include "HWM_pub_generic_adapter.h"

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
OUTPUT TYPES - (Heartbeat message from Adapter)
----------------------------------------------------------*/
typedef union /* iop_heartbeat */
    {
    struct
        {
        HWM_cal_t8              calibration_status;
        HWM_hookup_t8           hookup_status;
        HWM_gauge_t8            gauge_type;
        HWM_sensor_t8           sensor_type;
        uint16                  sender_voltage;
        uint16                  gauge_voltage;
        } rudder_angle;

    struct
        {
        HWM_cal_t8              calibration_status;
        HWM_hookup_t8           hookup_status;
        HWM_gauge_t8            gauge_type;
        HWM_sensor_t8           sensor_type;
        uint16                  sender_voltage;
        uint16                  gauge_voltage;
        } engine_tilt;

    struct
        {
        HWM_cal_t8              calibration_status;
        HWM_hookup_t8           hookup_status;
        HWM_gauge_t8            gauge_type;
        HWM_sensor_t8           sensor_type;
        uint16                  sender_voltage;
        uint16                  gauge_voltage;
        } fluid_level;

    struct
        {
        HWM_cal_t8              calibration_status;
        HWM_hookup_t8           hookup_status;
        uint16                  stbd;
        uint16                  port;
        } bennett_trim;

    struct
        {
        HWM_cal_t8              calibration_status;     /* Based on Water speed only */
        sint16                  temperature_offset;
        UTL_fixed_pnt_type      temperature_multiplier;
        sint16                  waterspeed_offset;
        } waterspeed_and_temp;

    } iop_heartbeat;

/*----------------------------------------------------------
INPUT TYPES - Multi_Cal message to Rudder Angle Adapter
                                   Engine Tilt  Adapter &
                                   Fluid  Level Adapter.

    -1st byte = # of Calibration Points to follow.
    -Remaining bytes = Calibration Points (Set of 3 16-bit
        numbers). Everything is tightly packed.
----------------------------------------------------------*/

    typedef struct  /* IOP_MRN_SNSR_RUDDER_MULTI_CAL        */
                    /* IOP_MNR_SNSR_ENGINE_TILT_MULTI_CAL   */
                    /* IOP_MRN_SNSR_FUEL_LVL_MULTI_CAL      */
        {
        uint8                   num_cal_points;
        HWM_xfrm_tbl_entry_t    cal_points[1];
        } IOP_generic_adapter_multi_cal_pkt_t;

/*----------------------------------------------------------
INPUT TYPES - (to Bennett Trim Tab Adapter)

    -1st byte = Formula Revision #.
        Compare to BENNETT_TRIM_TAB_FORMULA_VERSION
    -2nd byte = # of Calibration Points to follow.
    -Remaining bytes = Calibration Points (Set of 3 16-bit
        numbers). Everything is tightly packed.
----------------------------------------------------------*/

    typedef struct /* IOP_MRN_SNSR_TRIM_TAB_MULTI_CAL */
           /* IOP_MRN_SNSR_TRIM_TAB_CAL_PNT_TBL - Note: Re-used as an output type. */
        {
        uint8                   rev_num;
        uint8                   num_cal_points;
        HWM_xfrm_tbl_entry_t    cal_points[1];
        } IOP_bennett_trim_multi_cal_pkt_t;

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

#endif /* _IOP_PUB_GENERIC_ADAPTER_H */
