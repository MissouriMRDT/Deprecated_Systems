/*********************************************************************
*
*   HEADER NAME:
*       SNS_pub_n2k_capabilities.h - Sensors Public NMEA 2000
*                                    Capabilities Declarations
*
*   Copyright 2007-2015 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _SNS_PUB_N2K_CAPABILITIES
#define      _SNS_PUB_N2K_CAPABILITIES

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
NMEA 2000 Sensor Capabilities Bitfield

This is sent as the payload of IOP_MRN_SNSR_CAPABILITIES.
Each bit indicates support for some type of configuration.
Only add new entries to the end of the list.
----------------------------------------------------------*/
typedef uint32 SNS_n2k_capabilities_type; enum
    {
                                                /* If set, the sensor...                                                        */
    SNS_N2K_NEEDS_CALIBRATION_BIT       = 0,    /* is not fully calibrated                                                      */
    SNS_N2K_GENERIC_SUPPORT_BIT         = 1,    /* supports Generic Configuration Strings                                       */
    SNS_N2K_FUEL_FLOW_SUPPORT_BIT       = 2,    /* supports Fuel Flow (Eng Inst, Flow Direction)                                */
    SNS_N2K_FLUID_LVL_SUPPORT_BIT       = 3,    /* supports Fluid Level (Fluid Inst, Tank Size, Level Calibration)              */
    SNS_N2K_AUTOPILOT_SUPPORT_BIT       = 4,    /* supports Autopilot Configuration                                             */
    SNS_N2K_TEMP_SUPPORT_BIT            = 5,    /* supports Temperature (Temp Inst, Temp Offset, Temp Multiplier)               */
    SNS_N2K_DEPTH_SUPPORT_BIT           = 6,    /* supports Water Depth (Keel Offset)                                           */
    SNS_N2K_GPS_SUPPORT_BIT             = 7,    /* supports GPS (WAAS On/Off, Init Position)                                    */
    SNS_N2K_WIND_SUPPORT_BIT            = 8,    /* supports Wind (Angle Offset, Angle Filter, Speed Filter)                     */
    SNS_N2K_PRES_SUPPORT_BIT            = 9,    /* supports Pressure (Pressure Inst, Pressure Adj)                              */
    SNS_N2K_TEMP_ADJ_SUPPORT_BIT        = 10,   /* DNU - Used to be used in Intelliducer and GWS10                              */
    SNS_N2K_AUP_IPS_SUPPORT_BIT         = 11,   /* supports IPS Autopilot Configuration                                         */
    SNS_N2K_TRIM_TAB_SUPPORT_BIT        = 12,   /* supports Trim Tab Configuration                                              */
    SNS_N2K_ENGN_TILT_SUPPORT_BIT       = 13,   /* supports Enginge tilt sensor configuration (Engine instance, Calibration)    */
    SNS_N2K_RUDDER_ANG_SUPPORT_BIT      = 14,   /* supports Rudder Angle sensor configuration (Rudder instance, Calibration)    */
    SNS_N2K_WTRSPD_SUPPORT_BIT          = 15,   /* supports Water Speed sensor configuration (Refrence type, calibration)       */
    SNS_N2K_FLUID_TYPE_SUPPORT_BIT      = 16,   /* supports Fluid Type                                                          */
    SNS_N2K_XM_SUPPORT_BIT              = 17,   /* supports XM (audio and/or weather)                                           */
    SNS_N2K_TEMP_SRC_SUPPORT_BIT        = 18,   /* supports Temperature Source configuration                                    */
    sns_N2K_AIS_ONLY_BIT                = 19,   /* supports AIS but not DSC/VHF capabilities */
    sns_N2K_AIS_TRANCEIVER_BIT          = 20,   /* supports ais transceiver configuration items */
    sns_N2K_WIRELESS_SUPPORT_BIT        = 21,   /* supports Wireless sensor configuration items */
    sns_N2K_WTRSPD_ADV_CAL_SUPPORT_BIT  = 22,   /* supports advance water speed calibration */

    SNS_N2K_CAPABILITIES_CNT,             /* Must be after all sensor bits */

    SNS_N2K_NEEDS_CALIBRATION       = setbit( SNS_N2K_NEEDS_CALIBRATION_BIT ),
    SNS_N2K_GENERIC_SUPPORT         = setbit( SNS_N2K_GENERIC_SUPPORT_BIT ),
    SNS_N2K_FUEL_FLOW_SUPPORT       = setbit( SNS_N2K_FUEL_FLOW_SUPPORT_BIT ),
    SNS_N2K_FLUID_LVL_SUPPORT       = setbit( SNS_N2K_FLUID_LVL_SUPPORT_BIT ),
    SNS_N2K_AUTOPILOT_SUPPORT       = setbit( SNS_N2K_AUTOPILOT_SUPPORT_BIT ),
    SNS_N2K_TEMP_SUPPORT            = setbit( SNS_N2K_TEMP_SUPPORT_BIT ),
    SNS_N2K_DEPTH_SUPPORT           = setbit( SNS_N2K_DEPTH_SUPPORT_BIT ),
    SNS_N2K_GPS_SUPPORT             = setbit( SNS_N2K_GPS_SUPPORT_BIT ),
    SNS_N2K_WIND_SUPPORT            = setbit( SNS_N2K_WIND_SUPPORT_BIT ),
    SNS_N2K_PRES_SUPPORT            = setbit( SNS_N2K_PRES_SUPPORT_BIT ),
    SNS_N2K_TEMP_ADJ_SUPPORT        = setbit( SNS_N2K_TEMP_ADJ_SUPPORT_BIT ),
    SNS_N2K_AUP_IPS_SUPPORT         = setbit( SNS_N2K_AUP_IPS_SUPPORT_BIT ),
    SNS_N2K_TRIM_TAB_SUPPORT        = setbit( SNS_N2K_TRIM_TAB_SUPPORT_BIT ),
    SNS_N2K_ENGN_TILT_SUPPORT       = setbit( SNS_N2K_ENGN_TILT_SUPPORT_BIT ),
    SNS_N2K_RUDDER_ANG_SUPPORT      = setbit( SNS_N2K_RUDDER_ANG_SUPPORT_BIT ),
    SNS_N2K_WTRSPD_SUPPORT          = setbit( SNS_N2K_WTRSPD_SUPPORT_BIT ),
    SNS_N2K_FLUID_TYPE_SUPPORT      = setbit( SNS_N2K_FLUID_TYPE_SUPPORT_BIT ),
    SNS_N2K_XM_SUPPORT              = setbit( SNS_N2K_XM_SUPPORT_BIT ),
    SNS_N2K_TEMP_SRC_SUPPORT        = setbit( SNS_N2K_TEMP_SRC_SUPPORT_BIT ),
    SNS_N2K_AIS_ONLY_SUPPORT        = setbit( sns_N2K_AIS_ONLY_BIT ),               /* sensor supports AIS               */
    SNS_N2K_AIS_TRANCEIVER_SUPPORT  = setbit( sns_N2K_AIS_TRANCEIVER_BIT ),         /* sensor support AIS transceiver    */
    SNS_N2K_WIRELESS_SUPPORT        = setbit( sns_N2K_WIRELESS_SUPPORT_BIT ),       /* sensor supports wireless          */
    SNS_N2K_WTRSPD_ADV_CAL_SUPPORT  = setbit( sns_N2K_WTRSPD_ADV_CAL_SUPPORT_BIT ), /* sensor supports Advance water speed calibration */

    /*------------------------------------------------------
    Mask for all know capabilities bits. If any bits are set
    outside of this mask, and the sensor supports generic
    config, then we should show the generic config page.
    ------------------------------------------------------*/
    SNS_N2K_KNOWN_CAPABILITIES_MASK = setbits( 0, SNS_N2K_CAPABILITIES_CNT )
    }; /* SNS_n2k_capabilities_type */

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

#endif  /* _SNS_PUB_N2K_CAPABILITIES */
