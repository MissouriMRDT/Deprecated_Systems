/*********************************************************************
*
*   HEADER NAME:
*       IOP_prv_nmea2k_prj.h - NMEA 2000 Private Project-Specific File
*
* Copyright 2007-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/
#if !defined _IOP_PRV_NMEA2K_PRJ_H
#define _IOP_PRV_NMEA2K_PRJ_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "HWM_pwr_prj.h"
#include <string.h>

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Project-specific constants
----------------------------------------------------------*/
#define PROD_INFO_PROD_CODE_GRA10   24927   /* NMEA2000-assigned value */
#define PROD_INFO_PROD_CODE_GET10   22056   /* NMEA2000-assigned value */
#define PROD_INFO_PROD_CODE_GFL10   6230    /* NMEA2000-assigned value */
#define PROD_INFO_PROD_CODE_GBT10   6608    /* NMEA2000-assigned value */
#define PROD_INFO_PROD_CODE_GST10   26202   /* NMEA2000-assigned value */

#define PROD_INFO_CERT              iop_NMEA2K_DD226_LVL_B /* Certification level */
#define PROD_INFO_LOAD_EQ_GRA10   2   /* Load equivalency */
#define PROD_INFO_LOAD_EQ_GET10   2   /* Load equivalency */
#define PROD_INFO_LOAD_EQ_GFL10   2   /* Load equivalency */
#define PROD_INFO_LOAD_EQ_GBT10   1   /* Load equivalency */
#define PROD_INFO_LOAD_EQ_GST10   1   /* Load equivalency */

/*----------------------------------------------------------
Number of fast messages that can be received simulatenously.
----------------------------------------------------------*/
#define SIMUL_FAST_PACKETS          1

/*----------------------------------------------------------
Maximum number of requestable/commandable parameters in all
PGN's supported by the Request Group Function.
----------------------------------------------------------*/
#define MAX_NMBR_RQST_PARAMS        7

/*----------------------------------------------------------
This is the maximum size of all Garmin packets over
NMEA2000. Currently the biggest packet is:

IOP_PRODUCT_INFO_SUMMARY: which can be up to 40 bytes
IOP_NVOL_DATA: currently it's 147 bytes

If you're not sure what to use, then use
FAST_PACKET_MAX_SIZE defined in IOP_nmea2k.c
----------------------------------------------------------*/
#define IOP_NMEA2K_TX_GRMN_MAX_DATA_SZ        223

#define MAX_PGN_CNT                           10

/*----------------------------------------------------------
Make sure that we can at least instrument nonvol
----------------------------------------------------------*/
/*
#if( _SYSBLD == _ON )
    UTL_compiler_assert(sizeof(NVM_nonvol_type) <= IOP_NMEA2K_TX_GRMN_MAX_DATA_SZ, UTL_FILE_IOP_NMEA2K);
#endif
*/

enum
    {
    /*------------------------------------------------------
    Should divide evenly into 750 (Fast-Packet timeout) and
    all entries in PERIODIC_TASKS[]. Using a lower value
    increases the accuracy of the timeouts, but increases
    time spent checking them. Suggested value is 50 because
    NMEA 2000 Appendix E Section 3.12.3 says "The margin for
    time-outs is 50 ms."
    ------------------------------------------------------*/
    iop_NMEA2K_TASK_PERIOD          = 50 /* ms */
    };

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/
typedef struct
    {
    boolean     single        : 1;
    boolean     tx            : 1;
    boolean     rx            : 1;
    boolean     rx_first_only : 1;  /* Receive first frame only? (only applies to fast packets) */
    } iop_pgn_transmission_info_t8;

typedef struct
    {
    iop_nmea2k_pgn_t    pgn;
    iop_pgn_transmission_info_t8 pgn_transmission_info;
    } iop_nmea2k_pgn_info_t;

typedef struct
    {
    uint16              time;
    void                (*function)(void);
    } iop_nmea2k_periodic_task_t;

/*----------------------------------------------------------
Data Format Types
----------------------------------------------------------*/
typedef uint16  iop_nmea2k_DF39_t16; /* DF39: Degrees Kelvin. 1E-2 */
typedef uint16  iop_nmea2k_DF02_t16; /* DF02: 0 to 2Pi, 1E-4 radians per unit. */
typedef sint16  iop_nmea2k_DF04_t16; /* DF04: +/-Pi 1E-4 radians per unit. */
typedef uint32  iop_nmea2k_DF105_t32;/* DF105: +/-Pi 1E-4 radians per unit. */
typedef uint16  iop_nmea2k_DF38_t16; /* DF38: Degrees Kelvin. 1E-1 */


/*--------------------------------------------------------------------
Payload of the Temperature PGN (130312)
--------------------------------------------------------------------*/
#pragma pack(1)
typedef struct
    {
    uint8                   sequence_id;
    uint8                   temp_inst;
    uint8                   temp_source;
    iop_nmea2k_DF39_t16     actual_temp;
    iop_nmea2k_DF39_t16     set_temp;
    uint8                   reserved;
    } iop_nmea2k_temperature_t;

/*--------------------------------------------------------------------
Payload of the Temperature Extended PGN (130316)
--------------------------------------------------------------------*/
#pragma pack(1)
typedef struct
    {
    uint8                   sequence_id;
    uint8                   temp_inst;
    uint8                   temp_source;
    iop_nmea2k_DF105_t32    actual_temp : 24;
    iop_nmea2k_DF38_t16     set_temp;
    } iop_nmea2k_temperature_ext_t;

/*--------------------------------------------------------------------
Payload of the Vessel Heading PGN (127250)
--------------------------------------------------------------------*/
#pragma pack(1)
typedef struct
    {
    uint8                   sequence_id;
    iop_nmea2k_DF02_t16     heading_sensor_reading;
    iop_nmea2k_DF04_t16     deviation;
    iop_nmea2k_DF04_t16     variation;
    unsigned     			heading_sensor_ref : 2;
    unsigned                reserved : 6;
    } iop_nmea2k_heading_t;

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/


#define iop_get_name_prj(_data)                                                                                         \
    {                                                                                                                   \
    switch( HWM_get_sensor_type() )                                                                                     \
        {                                                                                                               \
        case TEMPERATURE_SENSOR:                                                                                        \
            memcpy(_data, &NAME_CONSTANTS_TEMP, sizeof( iop_nmea2k_name_field_t ) );                                    \
            break;                                                                                                      \
        case HEADING_SENSOR:                                                                                            \
            memcpy(_data, &NAME_CONSTANTS_HEADING, sizeof( iop_nmea2k_name_field_t ) );                                 \
            break;                                                                                                      \
        default:                                                                                                        \
        memcpy(_data, &NAME_CONSTANTS, sizeof( iop_nmea2k_name_field_t ) );                                         \
            break;                                                                                                      \
        }                                                                                                               \
    }

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

void iop_nmea2k_tx_temperature_pgn
    (
    void
    );

void iop_nmea2k_tx_temperature_ext_pgn
    (
    void
    );

void iop_nmea2k_tx_heading_pgn
    (
    void
    );

void iop_nmea2k_update_tx_vals
    (
    void
    );

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/



/*----------------------------------------------------------
PGN Info Table.
----------------------------------------------------------*/
extern iop_nmea2k_pgn_info_t PGN_INFO_TBL[ MAX_PGN_CNT ];

#if ( _BBBLD == _ON )

    /*----------------------------------------------------------
    PGN Info Table - Generic Table
    ----------------------------------------------------------*/
    extern const iop_nmea2k_pgn_info_t PGN_INFO_TBL_GENERIC[];

#endif /* ( _BBBLD == _ON ) */

#define PGN_INFO_TBL_TEMP_CNT           10
#define PGN_INFO_TBL_HEADING_CNT        9

#if( _SYSBLD == _ON )

    /*----------------------------------------------------------
    PGN Info Table - Temperature Sensor
    ----------------------------------------------------------*/
    extern const iop_nmea2k_pgn_info_t PGN_INFO_TBL_TEMP[];

    /*----------------------------------------------------------
    PGN Info Table - Heading Sensor
    ----------------------------------------------------------*/
    extern const iop_nmea2k_pgn_info_t PGN_INFO_TBL_HEADING[];

#endif /* ( _SYSBLD == _ON ) */

/*----------------------------------------------------------
Periodically Sent PGNs. <Function> will be called every
<Time> milliseconds.
----------------------------------------------------------*/
#if( _SYSBLD == _ON )
    static const iop_nmea2k_periodic_task_t PERIODIC_TASKS[] =
        {
        /* Time(ms)     Function   */
        {   100,       iop_nmea2k_tx_heading_pgn           	},
        {   1000,       iop_nmea2k_tx_temperature_pgn           },
        {   1000,       iop_nmea2k_tx_temperature_ext_pgn       }
//        {   1000,       iop_nmea2k_update_tx_vals               } /* Should be equal to smallest value above which requires this function */
        };
#endif /* ( _SYSBLD == _ON ) */

/*----------------------------------------------------------
NAME field for Address Claim message. Fields that are not
constant will be replaced after this is copied into the
message.
----------------------------------------------------------*/
static const iop_nmea2k_name_field_t NAME_CONSTANTS =
    {
    0,                              /* identity     (NOT constant)          */
    iop_NMEA2K_GARMIN_MFG_CODE,     /* manufacturer (229 = GARMIN)          */
    {0,                             /* ecuInst      (NOT constant)          */
    0},                             /* functionInst (NOT constant)          */
    170,                            /* function     (170 = General Sensor)  */
    0,                              /* reserved     (must be 0)             */
    80,                             /* deviceClass  (80 = Instrumentation)  */
    0,                              /* systemInst   (NOT constant)          */
    iop_NMEA2K_MARINE_INDUSTRY_GRP, /* industryGrp  (4 = Marine)            */
    1,                              /* selfConfig   (must be 1)             */
    };

static const iop_nmea2k_name_field_t NAME_CONSTANTS_TEMP =
    {
    0,                              /* identity     (NOT constant)          */
    iop_NMEA2K_GARMIN_MFG_CODE,     /* manufacturer (229 = GARMIN)          */
    {0,                             /* ecuInst      (NOT constant)          */
    0},                             /* functionInst (NOT constant)          */
    130,                            /* function     (130 = Temperature)  */
    0,                              /* reserved     (must be 0)             */
    75,                             /* deviceClass  (75 = Sensor Communication Interface)  */
    0,                              /* systemInst   (NOT constant)          */
    iop_NMEA2K_MARINE_INDUSTRY_GRP, /* industryGrp  (4 = Marine)            */
    1,                              /* selfConfig   (must be 1)             */
    };

static const iop_nmea2k_name_field_t NAME_CONSTANTS_HEADING =
    {
    0,                              /* identity     (NOT constant)          */
    iop_NMEA2K_GARMIN_MFG_CODE,     /* manufacturer (229 = GARMIN)          */
    {0,                             /* ecuInst      (NOT constant)          */
    0},                             /* functionInst (NOT constant)          */
    140,                            /* function     (170 = General Sensor)  */
    0,                              /* reserved     (must be 0)             */
    60,                             /* deviceClass  (80 = Instrumentation)  */
    0,                              /* systemInst   (NOT constant)          */
    iop_NMEA2K_MARINE_INDUSTRY_GRP, /* industryGrp  (4 = Marine)            */
    1,                              /* selfConfig   (must be 1)             */
    };

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

void IOP_nmea2k_init_prj
    (
    void
    );

#endif /* IOP_PRV_NMEA2K_PRJ_H */




