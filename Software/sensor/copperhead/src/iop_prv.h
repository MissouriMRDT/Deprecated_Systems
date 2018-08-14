/*********************************************************************
*
*   HEADER NAME:
*       IOP_prv.h - IOP Private Declarations
*
*   Copyright 2007 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _IOP_PRV_H
#define      _IOP_PRV_H

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "IOP_pub_prj_s.h"
#include "IOP_pub.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/
typedef uint8 rx_state_type; enum
    {
    RX_STATE_PARSER_START   = 0x00,
    RX_STATE_PARSER_MASK    = 0x0F,


    RX_STATE_START_DLE      = 0x00,
    RX_STATE_ID             = 0x01,
    RX_STATE_SIZE           = 0x02,
    RX_STATE_DATA           = 0x03,
    RX_STATE_CHECKSUM       = 0x04,
    RX_STATE_END_DLE        = 0x05,
    RX_STATE_ETX            = 0x06,


    RX_STATE_PACKET_START   = 0x10,
    RX_STATE_PACKET_MASK    = 0xF0,

    RX_STATE_PACKET_NONE    = 0x10,
    RX_STATE_PACKET_GOOD    = 0x20,
    RX_STATE_PACKET_BAD     = 0x30,


    RX_STATE_INVALID        = 0xFF
    }; /* iop_rx_state_type */

typedef struct
    {
    IOP_inst_id_type    id;
    uint8               size;
    uint8               checksum;

    rx_state_type       state;
    uint8               dle_count;
    uint8               data_idx;

    uint8               data[ IOP_PACKET_DATA_SZ ];
    } packet_type;

typedef uint8 baud_change_state_type; enum
    {
    BAUD_RQST_DATA,
    ACK_PING,
    BAUD_CHANGED,

    BAUD_CHANGE_STATE_CNT
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

/*----------------------------------------------------------
iop_main.c procedure prototypes.
----------------------------------------------------------*/
boolean iop_grmn_proc_input
    (
    IOP_inst_id_type    const id,
    uint8       const * const data,
    uint8               const size,
    IOP_route_type    * const route,
    boolean             const just_test
    );

void iop_grmn_tx
    (
    IOP_inst_id_type            const id,
    uint8 const* const          data,
    uint8                       const data_size,
    IOP_route_type            * const route
    );

/*----------------------------------------------------------
IOP_serial.c procedure prototypes.
----------------------------------------------------------*/
#if ( SYC_SERIAL_SUPPORT == TRUE )

    #if ( SYC_SERIAL_RX_SUPPORT == TRUE )

        void iop_grmn_serial_proc_command
            (
            uint8       const * const data,
            uint8               const data_size
            );

        boolean iop_grmn_serial_proc_input
            (
            IOP_inst_id_type    const id,
            uint8       const * const data,
            boolean             const just_test
            );

        void iop_pwrp_serial
            (
            void
            );

        void iop_serial_rx_tsk
            (
            void
            );

    #endif /* SYC_SERIAL_RX_SUPPORT */

    void iop_serial_tx
        (
        IOP_inst_id_type const      id,
        uint8 const* const          data,
        uint8 const                 size
        );

#endif /* SYC_SERIAL_SUPPORT */

#endif  /* _IOP_PUB_H */
