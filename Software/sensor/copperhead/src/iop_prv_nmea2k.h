/*********************************************************************
*
*   HEADER NAME:
*       iop_prv_nmea2k.h - NMEA 2000 Private Declarations
*
* Copyright 2007-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/
#if !defined _IOP_PRV_NMEA2K_H
#define _IOP_PRV_NMEA2K_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "HWM_pub.h"
#include "IOP_pub_grmn.h"
#include "IOP_pub_inst.h"
#include "IOP_pub_nmea2k.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
NMEA 2000 PGN LIST
----------------------------------------------------------*/
#define iop_NMEA_ISO_ACK_PGN                     59392 /*  0xE800, Single */
#define iop_NMEA_ISO_REQ_PGN                     59904 /*  0xEA00, Single */
#define iop_NMEA_ISO_ADD_CLAIM                   60928 /*  0xEE00, Single */
#define iop_NMEA_PROPR_SF_AD_PGN                 61184 /*  0xEF00, Single (Proprietary Single-Frame to Specific Address) */
#define IOP_NMEA_PROP_SNGL_FRM_CPAC_RUD_ANG_PGN  65280 /* 0x0FF00, Single */
#define iop_NMEA_REQ_CMD_ACK_PGN                126208 /* 0x1ED00, Fast   */
#define iop_NMEA_PGN_LIST_PGN                   126464 /* 0x1EE00, Fast   */
#define iop_NMEA_PROPR_FP_AD_PGN                126720 /* 0x1EF00, Fast   (Proprietary Fast-Packet to Specific Address) */
#define iop_NMEA_PROD_INFO_PGN                  126996 /* 0x1F014, Fast   */
#define IOP_NMEA_HDG_TRK_CTRL_PGN               127237 /* 0x1F105, Fast   */
#define iop_NMEA_RUDDER_PGN                     127245 /* 0x1F10D, Single */
#define iop_NMEA_HEADING_PGN                    127250 /* 0x1F112, Single */
#define iop_NMEA_ENG_RAP_PGN                    127488 /* 0x1F200, Single */
#define iop_NMEA_ENG_DYN_PGN                    127489 /* 0x1F201, Fast   */
#define iop_NMEA_TRIP_ENG_PGN                   127497 /* 0x1F209, Fast   */
#define iop_NMEA_FLUID_LVL_PGN                  127505 /* 0x1F211, Single */
#define iop_NMEA_BATTERY_PGN                    127508 /* 0x1F214, Single */
#define iop_NMEA_SPEED_WATER_REF                128259 /* 0x1F503, Single */
#define iop_NMEA_WATER_DEPTH                    128267 /* 0x1F50B, Single */
#define iop_NMEA_WIND_DATA_PGN                  130306 /* 0x1FD02, Single */
#define iop_NMEA_TEMPERATURE_PGN                130312 /* 0x1FD08, Single */
#define iop_NMEA_PRESSURE_PGN                   130314 /* 0x1FD0A, Single */
#define iop_NMEA_TEMPERATURE_EXT_PGN            130316 /* 0x1FD0C, Single */
#define iop_NMEA_SMALL_CRAFT_PGN                130576 /* 0x1FE10, Single */
/* If you add to this list, be sure to update PGN_INFO_TBL */

/*----------------------------------------------------------
Name Constants
----------------------------------------------------------*/
#define iop_NMEA2K_GARMIN_MFG_CODE      229 /* NMEA 2000 Manufacturer Code */
#define iop_NMEA2K_MARINE_INDUSTRY_GRP  4   /* NMEA 2000 Industry Group */

/* We split the identity field into 4 bits Product Number and 17 bits Unit ID */
#define iop_NMEA2K_IDENTITY_UNIT_ID_MASK    0x1FFFF
#define iop_NMEA2K_IDENTITY_PROD_NUM_LSB    17
#define iop_NMEA2K_IDENTITY_PROD_NUM_MASK   0x0F

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
NMEA 2000 PGN
----------------------------------------------------------*/
typedef union
    {
    uint32      full;           /* Needed for comparisons */
    struct
        {
        uint8   specific;       /* PDU Specific Field */
        uint8   format;         /* PDU Format Field */
        uint8   data_pg;        /* PDU Data Page Field */
        uint8   sbz;            /* Set Bit to Zero (so 32-bit can be used) */
        } pdu;
    } iop_nmea2k_pgn_t;

typedef struct
    {
    uint32  identity     : 21;      /* unique number                                    */
    uint32  manufacturer : 11;      /* manufacturer's code                              */
    struct
        {
        uint8 ecuInst      : 3;     /* Device Instance Lower (ISO ECU Instance)         */
        uint8 functionInst : 5;     /* Device Instance Upper (ISO Function Instance)    */
        } dev_inst;
    uint8   function     : 8;       /* function code based on device class              */
    uint8   reserved     : 1;       /* should be set to 0                               */
    uint8   deviceClass  : 7;       /* device class                                     */
    uint8   systemInst   : 4;       /* System Instance (ISO Device Class Instance)      */
    uint8   industryGrp  : 3;       /* Industry Group 4 for Marine                      */
    uint8   selfConfig   : 1;       /* 1 if unit's address self-configurable            */
    } iop_nmea2k_name_field_t;

/*----------------------------------------------------------
NMEA 2000 Data Dictionary Constants:
(See NMEA 2000 Documentation, Appendix B2 for more info.)
----------------------------------------------------------*/
/*----------------------------------------------------------
DD037: Error Codes, Acknowledgement
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd037_t8; enum
    {
    iop_NMEA2K_DD037_NO_ERR         = 0,
    iop_NMEA2K_DD037_BAD_PGN        = 1,
    iop_NMEA2K_DD037_UNAVAIL        = 2,
    iop_NMEA2K_DD037_DENIED         = 3,
    iop_NMEA2K_DD037_BAD_REQ        = 4
    };

/*----------------------------------------------------------
DD056: Sequence ID
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd056_t8; enum
    {
    iop_NMEA2K_DD056_FIRST_SID      = 0,
    /*------------------------------------------------------
    ID's 0 to 250 are valid.
    ------------------------------------------------------*/
    iop_NMEA2K_DD056_LAST_SID       = 250,

    iop_NMEA2K_DD056_NOT_AVAIL      = 255
    };

/*----------------------------------------------------------
DD128: Generic Instance
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd128_t8; enum
    {
    iop_NMEA2K_DD128_FIRST_INST     = 0,
    /*------------------------------------------------------
    Instances 0 to 252 are valid.
    ------------------------------------------------------*/
    iop_NMEA2K_DD128_LAST_INST      = 252,

    iop_NMEA2K_DD128_RESERVED       = 253,
    iop_NMEA2K_DD128_ERROR          = 254,
    iop_NMEA2K_DD128_NOT_AVAIL      = 255
    };

/*----------------------------------------------------------
DD139: Error Codes, Transmit Interval Acknowledgement
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd139_t8; enum
    {
    iop_NMEA2K_DD139_NO_ERR         = 0,
    iop_NMEA2K_DD139_BAD_DATA       = 1,
    iop_NMEA2K_DD139_TOO_SMALL      = 2,
    iop_NMEA2K_DD139_DENIED         = 3,
    iop_NMEA2K_DD139_BAD_REQ        = 4
    };

/*----------------------------------------------------------
DD141: Error Codes, Command Acknowledgement
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd141_t8; enum
    {
    iop_NMEA2K_DD141_NO_ERR         = 0,
    iop_NMEA2K_DD141_BAD_DATA       = 1,
    iop_NMEA2K_DD141_UNAVAIL        = 2,
    iop_NMEA2K_DD141_NO_MATCH       = 3, // 3 could be a lack of match to a request
    iop_NMEA2K_DD141_OUT_OF_RANGE   = 3, // or a command out of range
    iop_NMEA2K_DD141_DENIED         = 4,
    iop_NMEA2K_DD141_BAD_REQ        = 5
    };

/*----------------------------------------------------------
DD144: Group Function, Request/Command/Acknowledge
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd144_t8; enum
    {
    iop_NMEA2K_DD144_REQUEST        = 0,
    iop_NMEA2K_DD144_COMMAND        = 1,
    iop_NMEA2K_DD144_ACK            = 2,
    iop_NMEA2K_DD144_READ           = 3,
    iop_NMEA2K_DD144_READ_REPLY     = 4,
    iop_NMEA2K_DD144_WRITE          = 5,
    iop_NMEA2K_DD144_WRITE_REPLY    = 6
    };

/*----------------------------------------------------------
DD145: Group Function, Transmit and Receive PGN List
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd145_t8; enum
    {
    iop_NMEA2K_DD145_TRANSMIT       = 0,
    iop_NMEA2K_DD145_RECEIVE        = 1
    };

/*----------------------------------------------------------
DD169: Generic Instance (4-bit)
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd169_t8; enum
    {
    iop_NMEA2K_DD169_FIRST_INST     = 0,
    /*------------------------------------------------------
    Instances 0 to 15 are all valid.
    ------------------------------------------------------*/
    iop_NMEA2K_DD169_LAST_INST      = 15,

    /*------------------------------------------------------
    Mask because field is <8 bits
    ------------------------------------------------------*/
    iop_NMEA2K_DD169_MASK           = 0x0F
    };

/*----------------------------------------------------------
DD177: ISO 11783 ACK Status
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd177_t8; enum
    {
    iop_NMEA2K_DD177_POS_ACK        = 0,
    iop_NMEA2K_DD177_NEG_ACK        = 1,
    iop_NMEA2K_DD177_DENIED         = 2
    };

/*----------------------------------------------------------
DD179: Group Function, Connection Management
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd179_t8; enum
    {
    iop_NMEA2K_DD179_RTS            = 0x10,
    iop_NMEA2K_DD179_CTS            = 0x11,
    iop_NMEA2K_DD179_EOM            = 0x13,
    iop_NMEA2K_DD179_BAM            = 0x20,
    iop_NMEA2K_DD179_ABORT          = 0xFF
    };

/*----------------------------------------------------------
DD205: Wind Reference (3-bit)
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd205_t8; enum
    {
    iop_NMEA2K_DD205_THEO_GND_TRUE  = 0,
    iop_NMEA2K_DD205_THEO_GND_MAG   = 1,
    iop_NMEA2K_DD205_APPARENT       = 2,
    iop_NMEA2K_DD205_THEO_GND_BOAT  = 3,
    iop_NMEA2K_DD205_THEO_GND_WTR   = 4,

    /*------------------------------------------------------
    Mask because field is <8 bits
    ------------------------------------------------------*/
    iop_NMEA2K_DD205_MASK           = 0x07
    };

/*----------------------------------------------------------
DD289: Pressure Source
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd289_t8; enum
    {
    iop_NMEA2K_DD289_ATMOS          = 0,
    iop_NMEA2K_DD289_WATER          = 1,
    iop_NMEA2K_DD289_STEAM          = 2,
    iop_NMEA2K_DD289_COMP_AIR       = 3,
    iop_NMEA2K_DD289_HYDRAULIC      = 4,

    iop_NMEA2K_DD289_RESERVED       = 253,
    iop_NMEA2K_DD289_ERROR          = 254,
    iop_NMEA2K_DD289_NOT_AVAIL      = 255
    };

/*----------------------------------------------------------
DD291: Temperature Source
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd291_t8; enum
    {
    iop_NMEA2K_DD291_SEA            = 0,
    iop_NMEA2K_DD291_OUTSIDE        = 1,
    iop_NMEA2K_DD291_INSIDE         = 2,
    iop_NMEA2K_DD291_ENG_ROOM       = 3,
    iop_NMEA2K_DD291_MAIN_CABIN     = 4,
    iop_NMEA2K_DD291_LIVE_WELL      = 5,
    iop_NMEA2K_DD291_BAIT_WELL      = 6,
    iop_NMEA2K_DD291_REFRIDGE       = 7,
    iop_NMEA2K_DD291_HEATING        = 8,
    iop_NMEA2K_DD291_DEW_POINT      = 9,
    iop_NMEA2K_DD291_WIND_CHILL_A   = 10,
    iop_NMEA2K_DD291_WIND_CHILL_T   = 11,
    iop_NMEA2K_DD291_HEAT_IDX       = 12,
    iop_NMEA2K_DD291_FREEZER        = 13,

    iop_NMEA2K_DD291_NOT_SUPPORTED  = 253,
    iop_NMEA2K_DD291_ERROR          = 254,
    iop_NMEA2K_DD291_NOT_AVAIL      = 255
    };

/*----------------------------------------------------------
DD226: NMEA 2000 Certification Level
----------------------------------------------------------*/
typedef uint8 iop_nmea2k_dd226_t8; enum
    {
    iop_NMEA2K_DD226_LVL_A          = 0,
    iop_NMEA2K_DD226_LVL_B          = 1
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

extern uint8                      iop_nmea2k_address;
extern boolean                    iop_nmea2k_address_valid;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

#define IOP_NMEA2K_IDENTIFIER_PRIO(_x)      ( (uint32)(_x) << 26 )  /* Priority */
#define IOP_NMEA2K_IDENTIFIER_RSVD(_x)      ( (uint32)(_x) << 25 )  /* Reserved bit */
#define IOP_NMEA2K_IDENTIFIER_PGN(_x)       (         (_x) <<  8 )  /* PGN | Destination Address ( fills DP/PDUF/PDUS fields) */
#define IOP_NMEA2K_IDENTIFIER_SOURCE(_x)    (         (_x) <<  0 )  /* Source Address */

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

void iop_nmea2k_fast_packet_tx
    (
    HWM_can_id_t    const * identifier,
    uint8           const * data,
    uint8                   size
    );

boolean iop_nmea2k_process_complete_packet_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data_ptr
    );

boolean iop_nmea2k_process_complex_cmd_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data_ptr,
    uint8                       num_params,
    iop_nmea2k_dd139_t8         priority_err,
    iop_nmea2k_dd037_t8       * pgn_err,
    iop_nmea2k_dd141_t8       * param_err_list
    );

boolean iop_nmea2k_process_complex_req_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data_ptr,
    uint8                       num_params,
    iop_nmea2k_dd139_t8         interval_err,
    iop_nmea2k_dd037_t8       * pgn_err,
    boolean                   * param_err,
    iop_nmea2k_dd141_t8       * param_err_list
    );

boolean iop_nmea2k_process_reqest_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8                       source_addr
    );

void iop_nmea2k_process_rx_frame
    (
    HWM_can_id_t    const * id,
    uint8                 * data,
    uint8                   data_len
    );

void iop_nmea2k_rx_init
    (
    void
    );

void iop_nmea2k_single_frame_tx
    (
    HWM_can_id_t  const *   identifier,
    uint8         const *   data,
    uint8         const     size,
    boolean       const     last_frame
    );

void iop_nmea2k_tsk
    (
    void
    );

void iop_nmea2k_tx_grmn
    (
    IOP_inst_id_type    inst_id,
    IOP_route_type    * route,
    uint8       const * data_buf,
    uint8               data_size
    );

void iop_pwrp_nmea2k
    (
    void
    );

#endif /* IOP_PRV_NMEA2K_H */
