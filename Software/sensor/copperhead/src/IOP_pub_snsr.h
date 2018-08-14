/*********************************************************************
*
*   HEADER NAME:
*       IOP_pub_snsr.h - Sensor Public Declarations
*
* Copyright 2008-2015 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/
#if !defined _IOP_PUB_SNSR_H
#define _IOP_PUB_SNSR_H

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
First byte of IOP_MRN_SNSR_USER_CAL inst id.

If an item in generic config is going to have UI to
configure it then it should handle these three instructions
and have a unique capabilities flag.
----------------------------------------------------------*/
typedef uint8 IOP_mrn_snsr_user_cal_type; enum
    {
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_ANG_OFFSET_SET    = 0,    /* Set Wind Sensor Installation Offset */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_ANG_OFFSET_RQST   = 1,    /* Wind Sensor Installation Offset Request */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_ANG_OFFSET_DATA   = 2,    /* Wind Sensor Installation Offset Response */
/* SNS_N2K_TEMP_ADJ_SUPPORT */          IOP_SNSR_TEMP_OFFSET_SET        = 3,    /* Set Temperature Offset */
/* SNS_N2K_TEMP_ADJ_SUPPORT */          IOP_SNSR_TEMP_OFFSET_RQST       = 4,    /* Temperature Offset Request */
/* SNS_N2K_TEMP_ADJ_SUPPORT */          IOP_SNSR_TEMP_OFFSET_DATA       = 5,    /* Temperature Offset Response */
/* SNS_N2K_TEMP_ADJ_SUPPORT */          IOP_SNSR_TEMP_MULT_SET          = 6,    /* Set Temperature Multiplier */
/* SNS_N2K_TEMP_ADJ_SUPPORT */          IOP_SNSR_TEMP_MULT_RQST         = 7,    /* Temperature Multiplier Request */
/* SNS_N2K_TEMP_ADJ_SUPPORT */          IOP_SNSR_TEMP_MULT_DATA         = 8,    /* Temperature Multiplier Response */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_PRESSURE_OFFSET_SET    = 9,    /* Set Pressure Offset */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_PRESSURE_OFFSET_RQST   = 10,   /* Pressure Offset Request */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_PRESSURE_OFFSET_DATA   = 11,   /* Pressure Offset Response */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_PRESSURE_MULT_SET      = 12,   /* Set Pressure Multiplier */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_PRESSURE_MULT_RQST     = 13,   /* Pressure Multiplier Request */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_PRESSURE_MULT_DATA     = 14,   /* Pressure Multiplier Response */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_ANG_FILTER_SET    = 15,   /* Set Wind Angle Filter Value */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_ANG_FILTER_RQST   = 16,   /* Wind Angle Filter Value Request */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_ANG_FILTER_DATA   = 17,   /* Wind Angle Filter Value Response */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_SPD_FILTER_SET    = 18,   /* Set Wind Speed Filter Value */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_SPD_FILTER_RQST   = 19,   /* Wind Speed Filter Value Request */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_SPD_FILTER_DATA   = 20,   /* Wind Speed Filter Value Response */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_SPD_MULT_SET      = 21,   /* Set Wind Speed Multiplier */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_SPD_MULT_RQST     = 22,   /* Wind Speed Multiplier Request */
/* SNS_N2K_WIND_SUPPORT */              IOP_SNSR_WIND_SPD_MULT_DATA     = 23,   /* Wind Speed Multiplier Response */
/* SNS_N2K_WTRSPD_SUPPORT */            IOP_SNSR_WTRSPD_OFFSET_SET      = 24,   /* Set Water Speed Offset */
/* SNS_N2K_WTRSPD_SUPPORT */            IOP_SNSR_WTRSPD_OFFSET_RQST     = 25,   /* Water Speed Offset Request */
/* SNS_N2K_WTRSPD_SUPPORT */            IOP_SNSR_WTRSPD_OFFSET_DATA     = 26,   /* Water Speed Offset Response */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_MMSI_SET               = 27,   /* Set MMSI */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_MMSI_RQST              = 28,   /* MMSI Request */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_MMSI_DATA              = 29,   /* MMSI Response */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_CALL_SIGN_SET          = 30,   /* Set Call Sign */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_CALL_SIGN_RQST         = 31,   /* Call Sign Request */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_CALL_SIGN_DATA         = 32,   /* Call Sign Response */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_SHIP_NAME_SET          = 33,   /* Set Ship Name */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_SHIP_NAME_RQST         = 34,   /* Ship Name Request */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_SHIP_NAME_DATA         = 35,   /* Ship Name Response */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_DIM_SET                = 36,   /* Set Dimension */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_DIM_RQST               = 37,   /* Dimension Request */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_DIM_DATA               = 38,   /* Dimension Response */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_VESSEL_TYPE_SET        = 39,   /* Set Vessel Type */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_VESSEL_TYPE_RQST       = 40,   /* Vessel Type Request */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_VESSEL_TYPE_DATA       = 41,   /* Vessel Type Response */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_GPS_BRIDGING_SET       = 42,   /* Set GPS Bridging Support */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_GPS_BRIDGING_RQST      = 43,   /* GPS Bridging Request */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_GPS_BRIDGING_DATA      = 44,   /* GPS Bridging Response */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_SILENT_MODE_SET        = 45,   /* Set Silent Mode */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_SILENT_MODE_RQST       = 46,   /* Silent Mode Request */
/* SNS_N2K_AIS_TRANCEIVER_SUPPORT */    IOP_SNSR_SILENT_MODE_DATA       = 47,   /* Silent Mode Response */
/* SNS_N2K_WIRELESS_SUPPORT */          IOP_SNSR_PAIR_STATUS_SET        = 48,   /* Set Pair Status */
/* SNS_N2K_WIRELESS_SUPPORT */          IOP_SNSR_PAIR_STATUS_RQST       = 49,   /* Pair Status Request */
/* SNS_N2K_WIRELESS_SUPPORT */          IOP_SNSR_PAIR_STATUS_DATA       = 50,   /* Pair Status Response */

    /*------------------------------------------------------
    WARNING: Do not adjust order! These are sent across
    the network.
    ------------------------------------------------------*/
    };

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

#endif /* IOP_PUB_SNSR_H */
