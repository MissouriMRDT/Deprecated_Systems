/*********************************************************************
*
*   MODULE NAME:
*       IOP_nmea2k.c - Input/Output Processing for NMEA 2000 Data
*
*   DESCRIPTION:
*       Input/Output Processing Module for NMEA 2000 Data (over a CAN bus).
*
*   Copyright 2007-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "HWM_pub.h"
#include "IOP_pub.h"
#include "SYC_pub.h"

#include "iop_prv.h"
#if (SYC_CANET_SUPPORT == TRUE)
    #include "iop_prv_canet.h"
#endif

#if ( SYC_NVM_SUPPORT == TRUE )
    #include "NVM_pub.h"
#else
    #include "hwm_pub_xfer.h"
    #include "HWM_pub.h"
#endif

/*----------------------------------------------------------
Compile out this file if no nmea2k support.
----------------------------------------------------------*/
#if ( SYC_NMEA2K_SUPPORT == TRUE )

#include "iop_prv_nmea2k.h"
#include "iop_prv_nmea2k_prj.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
These states match Figure B-1: Address Claim State Diagram
in the NMEA 2000 Documentation, Appendix D.
----------------------------------------------------------*/
typedef uint8 addr_claim_state_t; enum
    {
    STATE_0_IDLE,
    STATE_1_DELAY,
    STATE_2A_TX,
    STATE_2B_TX,
    STATE_3_PROC_RX,
    STATE_4_NEW_ADDR,
    STATE_5_SUCCESS,
    STATE_6_DELAY,
    STATE_7_NO_ADDR,
    STATE_8_WAIT_REQ,
    STATE_9_TX
    };

/*----------------------------------------------------------
General NMEA 2000 constants
----------------------------------------------------------*/
#define DATABASE_VRSN               1300 /* 1.300 */
#define SINGLE_FRAME_MAX_SIZE       8   /* 1 can frame */
#define FAST_PACKET_MAX_SIZE        223 /* 32 can frames plus overhead = 6 + 31*7 */
#define FAST_PACKET_MAX_SEQ         8   /* Maximum sequence counter value */
#define GROUP_ADDR_LIMIT            240 /* PGN's above this are sent to everyone */
#define DEFAULT_PRIO                6   /* Default message priority */
#define DEFAULT_PROPR_PRIO          7   /* Default proprietary message priority */

/*----------------------------------------------------------
Address claim constants
----------------------------------------------------------*/
#define NMBR_ADDRESSES              252 /* 0 to 251 are valid addresses */
#define CANT_CLAIM_ADDRESS          254

/*----------------------------------------------------------
Delay times (specified in ISO 11783-5:2001(E) 6.4.6.1.2)
----------------------------------------------------------*/
/* Random delay */
#define MAX_INTERVAL_DELAY          153 /* ms */
#define MIN_INTERVAL_DELAY          0   /* ms */

/* Address claim response delay */
#define DELAY_250MS                 300 /* at least 250 ms */

/* Fast-packet frame maximum spacing */
#define FAST_PACKET_TIMEOUT         750 /* ms */

/* define default values if there is no NVM support */
#if ( SYC_NVM_SUPPORT != TRUE )
    #define SYSTEM_INSTANCE_NO_NVM 0
    #define DEVICE_INSTANCE_NO_NVM 0
#endif

/* Size of the unit ID */
#define UNIT_ID_STR_SIZE    10

/*----------------------------------------------------------
Proprietary Header (2 bytes total):
1. Manufacturer Code (11 bits)
2. Reserved (2 bits)
3. Industry Group (3 bits)
----------------------------------------------------------*/
#define PROPR_HEADER    (uint16)((iop_NMEA2K_MARINE_INDUSTRY_GRP << 13) | (0x3 << 11) | iop_NMEA2K_GARMIN_MFG_CODE)

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

typedef struct
    {
    HWM_can_id_t    id;                             /* CAN identifier                   */
    boolean         is_grmn;                        /* is this a Garmin packet?         */
    uint8           timeout;                        /* ticks left until data expires    */
    uint8           seq;                            /* last sequence counter received   */
    uint8           length;                         /* expected total length            */
    uint8           data_size;                      /* current size of data             */
    uint8           data[ FAST_PACKET_MAX_SIZE ];   /* data buffer                      */
    } fast_packet_info_t;

/*--------------------------------------------------------------------
                            PROJECT INCLUDES
--------------------------------------------------------------------*/

#include "IOP_prv_nmea2k_prj.h"

/*--------------------------------------------------------------------
                            MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Address claim constants.
----------------------------------------------------------*/
static addr_claim_state_t         addr_claim_state;
uint8                             iop_nmea2k_address;
boolean                           iop_nmea2k_address_valid;
uint8                             HWM_xfer_my_nmea2k_address;

/*----------------------------------------------------------
Sequence counters for transmitted fast-packet messages.
----------------------------------------------------------*/
static uint8                      seq_cnt_tbl[ cnt_of_array(PGN_INFO_TBL) ];

/*----------------------------------------------------------
Buffer for received fast messages.
----------------------------------------------------------*/
static fast_packet_info_t         fast_packets[ SIMUL_FAST_PACKETS ];

/*----------------------------------------------------------
Timer counters for periodic tasks.
----------------------------------------------------------*/
#if( _SYSBLD == _ON )
    static uint8      periodic_task_timeouts[ cnt_of_array(PERIODIC_TASKS) ];
#endif /* ( _SYSBLD == _ON ) */

/* temp var for storing random unit ID number */
#if ( SYC_NVM_SUPPORT != TRUE )
    uint32 my_random_unit_ID;
#endif

/*----------------------------------------------------------
Unit ID string as ascii.
----------------------------------------------------------*/
static tchr unit_id_str[UNIT_ID_STR_SIZE + 1];

/*--------------------------------------------------------------------
                                 MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

static void addr_claim
    (
    void
    );

static void addr_conflict
    (
    uint8  *remote_name
    );

static void addr_request
    (
    void
    );

static uint8 fast_packet_rx
    (
    HWM_can_id_t        const * identifier, /* CAN Extended ID field */
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data,       /* Payload */
    uint8                   * * data_ptr    /* Pointer to packet to process */
    );

static void get_name
    (
    uint8 * data
    );

static void process_complete_packet
    (
    iop_nmea2k_pgn_t  * pgn,
    uint8             * data_ptr,
    uint8               data_len,
    uint8               source_addr,
    uint8               dest_addr
    );

static void process_complex_cmd
    (
    uint8 const * const data_ptr,
    uint8         const source_addr,
    uint8         const dest_addr
    );

static void process_complex_req
    (
    uint8 const * const data_ptr,
    uint8         const source_addr,
    uint8         const dest_addr
    );

static void process_grmn_data
    (
    uint8       source_addr,
    uint8     * data,
    uint8       data_len
    );

static void tx_addr_claim
    (
    void
    );

static void tx_complex_ack
    (
    iop_nmea2k_pgn_t      * pgn,
    uint8                   source_addr,
    uint8                   num_params,
    iop_nmea2k_dd139_t8     interval_err,
    iop_nmea2k_dd037_t8     pgn_err,
    iop_nmea2k_dd141_t8   * param_err_list
    );

static void tx_grmn_invalid
    (
    iop_nmea2k_pgn_t  * rqstd_pgn,
    uint8               dest_addr
    );

static void tx_nack
    (
    iop_nmea2k_pgn_t  * rqstd_pgn,
    uint8               dest_addr
    );

static void tx_product_info
    (
    void
    );

static void tx_pgn_list
    (
    uint8               dest_addr,   /* address to send to */
    iop_nmea2k_dd145_t8 trans_or_recieve_pgn_list
    );

#if ( _SYSBLD == _ON )

    static void set_dev_inst_lower
        (
        uint8 const new_inst
        );

    static void set_dev_inst_upper
        (
        uint8 const new_inst
        );

    static void set_sys_inst
        (
        uint8 const new_inst
        );

#endif /* ( _SYSBLD == _ON ) */


/*********************************************************************
*
*   PROCEDURE NAME:
*       IOP_nmea2k_ready - Check if NMEA2k is ready
*
*   DESCRIPTION:
*       Returns true if NMEA2k is ready.
*
*********************************************************************/
boolean IOP_nmea2k_ready
    (
    void
    )
{

return( iop_nmea2k_address_valid );

} /* IOP_nmea2k_ready() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_fast_packet_tx - Send a NMEA2K Fast-Packet Message
*
*   DESCRIPTION:
*       This procedure handles sending of a fast-packet of NMEA2K data.
*       Maximum size is 223 bytes, which will be split up into 32
*       frames. PGN's that are not listed as single-frame must be
*       sent with either the fast-packet or multi-packet transport
*       protocol.
*
*********************************************************************/
void iop_nmea2k_fast_packet_tx
    (
    HWM_can_id_t    const * identifier, /* CAN Extended ID field */
    uint8           const * data,       /* Payload */
    uint8                   size        /* Size of data */
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
iop_nmea2k_pgn_t pgn;
uint8   tx_buf[8];
uint8   seq_count;
uint8   frame_count;
uint8   i;

/*----------------------------------------------------------
Make sure size fits into a fast-packet message.
----------------------------------------------------------*/
UTL_assert( size <= FAST_PACKET_MAX_SIZE, UTL_FILE_IOP_NMEA2K );

/*----------------------------------------------------------
Initialize
----------------------------------------------------------*/
frame_count = 0;

/*----------------------------------------------------------
Determine the sequence counter based on the PGN.
----------------------------------------------------------*/
pgn.full = ( identifier->ext >> 8 ) & 0x1FFFF;

if( pgn.pdu.format < GROUP_ADDR_LIMIT )
    {
    pgn.pdu.specific = 0;
    }

/*----------------------------------------------------------
Find the PGN in the PGN into table.
----------------------------------------------------------*/
for( i = 0; i < cnt_of_array( PGN_INFO_TBL ); i++ )
    {
    if( PGN_INFO_TBL[i].pgn.full == pgn.full )
        {
        break;
        }
    }

/*----------------------------------------------------------
Make sure the PGN was found.
----------------------------------------------------------*/
UTL_assert( i != cnt_of_array( PGN_INFO_TBL ), UTL_FILE_IOP_NMEA2K );

seq_count = seq_cnt_tbl[i]++ % FAST_PACKET_MAX_SEQ;

/*----------------------------------------------------------
Prepare the first frame. It contains the sequence counter
and total size (not including filler bytes).
----------------------------------------------------------*/
tx_buf[0] = ( seq_count << 5 ) | frame_count++;
tx_buf[1] = size;

for( i = 2; i < SINGLE_FRAME_MAX_SIZE; i++ )
    {
    if( size > 0 )
        {
        tx_buf[i] = *data++;
        size--;
        }
    else
        {
        /*--------------------------------------------------
        Set unused bytes to 0xFF.
        --------------------------------------------------*/
        tx_buf[i] = 0xFF;
        }
    }

/*----------------------------------------------------------
Send the rest of the frames.
----------------------------------------------------------*/
while( size > 0 )
    {
    iop_nmea2k_single_frame_tx( identifier, tx_buf, SINGLE_FRAME_MAX_SIZE, FALSE );

    tx_buf[0] = ( seq_count << 5 ) | frame_count++;

    for( i = 1; i < SINGLE_FRAME_MAX_SIZE; i++ )
        {
        if( size > 0 )
            {
            tx_buf[i] = *data++;
            size--;
            }
        else
            {
            /*----------------------------------------------
            Set unused bytes to 0xFF.
            ----------------------------------------------*/
            tx_buf[i] = 0xFF;
            }
        }
    }

/*----------------------------------------------------------
Send out the final frame.
----------------------------------------------------------*/
iop_nmea2k_single_frame_tx( identifier, tx_buf, SINGLE_FRAME_MAX_SIZE, TRUE );

} /* iop_nmea2k_fast_packet_tx() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_process_rx_frame - Process Received Data
*
*   DESCRIPTION:
*       This procedure receives data from the CAN bus driver and
*       handles it.
*
*********************************************************************/
void iop_nmea2k_process_rx_frame
    (
    HWM_can_id_t    const * id,
    uint8                 * data,
    uint8                   data_len
    )
{
/*----------------------------------------------------------
Local variables.
----------------------------------------------------------*/
iop_nmea2k_pgn_t    pgn;
uint8 * data_ptr;
uint8   dest_addr;
uint8   i;

/*----------------------------------------------------------
Initialize
----------------------------------------------------------*/
dest_addr = 0xFF;

/*----------------------------------------------------------
Extract the PGN fields from the ID.
----------------------------------------------------------*/
pgn.full = ( id->ext >> 8 ) & 0x1FFFF;

/*----------------------------------------------------------
Check if the PGN was meant for us.
----------------------------------------------------------*/
if( pgn.pdu.format < GROUP_ADDR_LIMIT )
    {
    /*------------------------------------------------------
    This PGN has a destination in the specific field.
    Zero the destination field of the PGN so that the
    PGN without destination can be compared later.
    ------------------------------------------------------*/
    dest_addr = pgn.pdu.specific;
    pgn.pdu.specific = 0;
    if( ( dest_addr != IOP_NMEA2K_GLOBAL_ADDRESS )
     && ( dest_addr != iop_nmea2k_address ) )
        {
        /*--------------------------------------------------
        This frame was meant for someone else. Ignore it.
        --------------------------------------------------*/
        return;
        }
    }

for( i = 0; i < cnt_of_array( PGN_INFO_TBL ); i++ )
    {
    if( PGN_INFO_TBL[i].pgn.full == pgn.full )
        {
        break;
        }
    }

if( ( i == cnt_of_array( PGN_INFO_TBL ) ) || ( PGN_INFO_TBL[i].pgn_transmission_info.rx == FALSE ) )
    {
    /*------------------------------------------------------
    This PGN is not in our table as receivable. Ignore it.
    ------------------------------------------------------*/
    return;
    }

/*----------------------------------------------------------
Check if this was a fast-packet message.
----------------------------------------------------------*/
if( !PGN_INFO_TBL[i].pgn_transmission_info.single )
    {
    if( PGN_INFO_TBL[i].pgn_transmission_info.rx_first_only )
        {
        /*--------------------------------------------------
        We only care about the data in the first frame of
        this PGN. Remove the sequence ID and size.
        --------------------------------------------------*/
        data_ptr = &data[2];
        data_len -= 2;
        }
    else
        {
        data_len = fast_packet_rx( id, &pgn, data, &data_ptr );

        if( data_len == 0 )
            {
            /*----------------------------------------------
            No packet to process. This was either not the
            last frame in a packet or was filtered out.
            ----------------------------------------------*/
            return;
            }
        }
    }
else
    {
    data_ptr = data;
    }

process_complete_packet( &pgn, data_ptr, data_len, id->tab[0], dest_addr );
} /* iop_nmea2k_process_rx_frame() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_rx_init - Set Up Receiving of CAN Bus Frames
*
*   DESCRIPTION:
*       Creates a listen message object to receive data from the CAN
*       bus. This function should only be called if the data coming
*       in on the bus is NMEA 2000 data.
*
*********************************************************************/
void iop_nmea2k_rx_init
    (
    void
    )
{
/*----------------------------------------------------------
Local Variables
----------------------------------------------------------*/
uint32 zero;

/*----------------------------------------------------------
Initialize
----------------------------------------------------------*/
zero = 0;

/*------------------------------------------------------
Set up CAN receive callback. No hardware filtering is
being done because of a hardware bug: CAN transmits too
late if no MOb is set up to receive any incoming message
(see the AT90CAN32 datasheet, 33.1.2 Errata).
------------------------------------------------------*/
HWM_can_listen_for_ext( &zero, &zero, (HWM_can_rx_clbk_type)iop_nmea2k_process_rx_frame );
} /* iop_nmea2k_rx_init() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_single_frame_tx - Send a NMEA2K Single-Frame Message
*
*   DESCRIPTION:
*       This procedure handles sending of ONE frame of NMEA2K data.
*
*********************************************************************/
void iop_nmea2k_single_frame_tx
    (
    HWM_can_id_t  const *   identifier, /* CAN Extended ID field */
    uint8         const *   data,       /* Payload */
    uint8         const     size,       /* Size of data */
    boolean       const     last_frame  /* Is this the last frame of a message? */
    )
{
/*----------------------------------------------------------
Make sure the data fits into 1 frame.
----------------------------------------------------------*/
UTL_assert( size <= 8, UTL_FILE_IOP_NMEA2K );

#if( SYC_CANET_SUPPORT )

    if( HWM_get_can_protocol() == HWM_CAN_CANET )
        {
        iop_nmea2k_pgn_t    pgn;
        boolean             broadcast;

        /*--------------------------------------------------
        Extract the PGN fields from the ID.
        --------------------------------------------------*/
        pgn.full = identifier->ext >> 8;

        if( ( pgn.pdu.format >= GROUP_ADDR_LIMIT )
         || ( pgn.pdu.specific == IOP_NMEA2K_GLOBAL_ADDRESS ) )
            {
            broadcast = TRUE;
            }
        else
            {
            broadcast = FALSE;
            }

        /*--------------------------------------------------
        Pass frame to CANet handler.
        --------------------------------------------------*/
        iop_tx_nmea2k_over_canet( identifier, data, size, broadcast, last_frame );
        }
    else /* HWM_get_can_protocol() == HWM_CAN_NMEA2K */
        {
        /*--------------------------------------------------
        Check assumption.
        --------------------------------------------------*/
        UTL_assert( HWM_get_can_protocol() == HWM_CAN_NMEA2K, UTL_FILE_IOP_NMEA2K );

        /*--------------------------------------------------
        Send directly to CAN driver.
        --------------------------------------------------*/
        HWM_tx_can_ext( identifier, data, size );
        }

#else

    /*------------------------------------------------------
    Send directly to CAN driver.
    ------------------------------------------------------*/
    HWM_tx_can_ext( identifier, data, size );

#endif
} /* single_frame_tx() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_tsk - NMEA 2000 Main Task
*
*   DESCRIPTION:
*       Processes nmea2k data.
*
*********************************************************************/
void iop_nmea2k_tsk
    (
    void
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8 i;

if( ( SYC_is_timer_expired(SYC_TIMER_IOP_NMEA2K_ADDR) == TRUE )
//#if( _BBBLD == _ON )
// && ( SYC_is_timer_expired(SYC_TIMER_SYC_BB_LISTEN)   == TRUE )
//#endif
  )
    {
    /*------------------------------------------------------
    Handle address claim state machine.
    ------------------------------------------------------*/
    addr_claim();
    }

if( SYC_is_timer_expired(SYC_TIMER_IOP_NMEA2K) == TRUE )
    {
    /*------------------------------------------------------
    Decrement fast timeout values.
    ------------------------------------------------------*/
    for( i = 0; i < SIMUL_FAST_PACKETS; i++ )
        {
        if( fast_packets[i].timeout > 0 )
            {
            fast_packets[i].timeout--;
            }
        }

    #if( _SYSBLD == _ON )
        /*--------------------------------------------------
        Send any periodic PGN's
        --------------------------------------------------*/
        for( i = 0; i < cnt_of_array( PERIODIC_TASKS ); i++ )
            {
            periodic_task_timeouts[i]--;
            if( periodic_task_timeouts[i] == 0 )
                {
                periodic_task_timeouts[i] = PERIODIC_TASKS[i].time / iop_NMEA2K_TASK_PERIOD;

                PERIODIC_TASKS[i].function();
                }
            }
    #endif /* ( _SYSBLD == _ON ) */

    /*------------------------------------------------------
    Reset the timer.
    ------------------------------------------------------*/
    SYC_set_timer(SYC_TIMER_IOP_NMEA2K, iop_NMEA2K_TASK_PERIOD);
    }

} /* iop_nmea2k_tsk() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_tx_grmn - Transmit Garmin Data over NMEA 2000
*
*   DESCRIPTION:
*       This procedure sends a proprietary Garmin packet over NMEA
*       2000.
*
*********************************************************************/
void iop_nmea2k_tx_grmn
    (
    IOP_inst_id_type    inst_id,
    IOP_route_type    * route,
    uint8 const       * data_buf,
    uint8               data_size
    )
{
/*----------------------------------------------------------
Local constants
----------------------------------------------------------*/
#define PROPR_GRMN_HDR_SIZE 6   /* Proprietary & Garmin overhead */

/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t    id;
uint8           data[ IOP_NMEA2K_TX_GRMN_MAX_DATA_SZ + PROPR_GRMN_HDR_SIZE ];

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Data Fields:
1. Manufacturer Code (11 bits) - Proprietary Requirement
2. Reserved (2 bits) - Proprietary Requirement
3. Industry Group (3 bits) - Proprietary Requirement
4. Garmin Instrumentation ID (2 bytes)
5. Source Port (1 byte)
6. Destination Port (1 byte)
7. Data (n bytes)
----------------------------------------------------------*/
data[0] = PROPR_HEADER & 0xFF;
data[1] = PROPR_HEADER >> 8;
data[2] = inst_id & 0xFF;
data[3] = inst_id >> 8;
data[4] = route->dest_port;         /* Switch source and destination */
data[5] = route->source_port;       /* ...ports for reply message    */

/*----------------------------------------------------------
Make sure the data fits in the rest of the packet.
----------------------------------------------------------*/
UTL_assert( data_size <= IOP_NMEA2K_TX_GRMN_MAX_DATA_SZ, UTL_FILE_IOP_NMEA2K );

/*----------------------------------------------------------
Copy the data buffer.
----------------------------------------------------------*/
memcpy( &data[PROPR_GRMN_HDR_SIZE], data_buf, data_size );

id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( DEFAULT_PROPR_PRIO )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

#if (SINGLE_FRAME_MAX_SIZE >= PROPR_GRMN_HDR_SIZE)
if( data_size <= (SINGLE_FRAME_MAX_SIZE - PROPR_GRMN_HDR_SIZE) )
#else
if( (data_size + PROPR_GRMN_HDR_SIZE) <= SINGLE_FRAME_MAX_SIZE)
#endif
    {
    /*------------------------------------------------------
    Fill in the ID field.
    ------------------------------------------------------*/
    id.ext |= IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_PROPR_SF_AD_PGN | route->source_addr );

    /*------------------------------------------------------
    Send the frame using the single-frame method.
    ------------------------------------------------------*/
    iop_nmea2k_single_frame_tx( &id, data, ( data_size + PROPR_GRMN_HDR_SIZE ), TRUE );
    }
else
    {
    /*------------------------------------------------------
    Fill in the ID field.
    ------------------------------------------------------*/
    id.ext |= IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_PROPR_FP_AD_PGN | route->source_addr );

    /*------------------------------------------------------
    Send the message using the fast-packet method.
    ------------------------------------------------------*/
    iop_nmea2k_fast_packet_tx( &id, data, ( data_size + PROPR_GRMN_HDR_SIZE ) );
    }
} /* iop_nmea2k_tx_grmn() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_pwrp_nmea2k - Powerup NMEA 2000
*
*   DESCRIPTION:
*       This procedure powers up the NMEA 2000 module.
*
*********************************************************************/
void iop_pwrp_nmea2k
    (
    void
    )
{
/*----------------------------------------------------------
Local variables.
----------------------------------------------------------*/
uint32 unit_id;

/*----------------------------------------------------------
Initialize globals
----------------------------------------------------------*/
addr_claim_state = STATE_0_IDLE;
iop_nmea2k_address_valid = FALSE;
memset( &seq_cnt_tbl, 0, sizeof( seq_cnt_tbl ) );
memset( &fast_packets, 0, sizeof( fast_packets ) );

#if( _SYSBLD == _ON )
    {
    /*----------------------------------------------------------
    Local scoped variables
    ----------------------------------------------------------*/
    uint8 i;

    for( i = 0; i < cnt_of_array( PERIODIC_TASKS ); i++ )
        {
        periodic_task_timeouts[i] = PERIODIC_TASKS[i].time / iop_NMEA2K_TASK_PERIOD;
        }
    }
#endif /* ( _SYSBLD == _ON ) */

SYC_set_timer_expired(SYC_TIMER_IOP_NMEA2K);
SYC_set_timer_expired(SYC_TIMER_IOP_NMEA2K_ADDR);

#if ( SYC_NVM_SUPPORT == TRUE )
    unit_id = NVM_read_nonvol( syc_unit_id );
#else
    /*------------------------------------------------------
    Populate the random unit ID if there is no NVM support.
    ------------------------------------------------------*/
    my_random_unit_ID = 0;
    my_random_unit_ID += HWM_get_random_nmbr();
    my_random_unit_ID += (uint32)HWM_get_random_nmbr() << 8;
    my_random_unit_ID += (uint32)HWM_get_random_nmbr() << 16;
    my_random_unit_ID += (uint32)HWM_get_random_nmbr() << 24;
    unit_id = my_random_unit_ID;
#endif

/*----------------------------------------------------------
Build the unit ID string on powerup because building a
string from an int is time consuming (5000+ clock cycles).
----------------------------------------------------------*/
UTL_bld_int_str_fixed( unit_id, UNIT_ID_STR_SIZE, unit_id_str );

/*----------------------------------------------------------
Initialize the address.
----------------------------------------------------------*/
#if ( SYC_NVM_SUPPORT == TRUE )
    iop_nmea2k_address = NVM_read_nonvol( iop_nmea2k_addr );
#else
    iop_nmea2k_address = 0;
#endif

} /* iop_pwrp_nmea2k() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       addr_claim - Address Claim
*
*   DESCRIPTION:
*       Handles address claim state machine. See Figure B-1: Address
*       Claim State Diagram in the NMEA 2000 Documentation, Appendix D.
*
*********************************************************************/
static void addr_claim
    (
    void
    )
{
/*----------------------------------------------------------
Local Variables
----------------------------------------------------------*/
uint8 delay_time;

/*----------------------------------------------------------
Note: At this point the address timer is expired, so this
function will be called the next time the main loop is run
unless the timer is set or turned off.
----------------------------------------------------------*/

if(addr_claim_state == STATE_0_IDLE)
    {
    #if( SYC_CANET_SUPPORT == TRUE )
        if( HWM_get_can_protocol() == HWM_CAN_CANET )
            {
            /*------------------------------------------
            Don't try to claim an address until unless
            CANet is ready.
            ------------------------------------------*/
            if( iop_canet_ready() == FALSE )
                {
                return;
                }
            }
    #endif

    /*--------------------------------------------------
    Delay a random time.
    --------------------------------------------------*/
    delay_time = ( HWM_get_random_nmbr() % (MAX_INTERVAL_DELAY + 1 - MIN_INTERVAL_DELAY) ) + MIN_INTERVAL_DELAY;
    SYC_set_timer_runtime( SYC_TIMER_IOP_NMEA2K_ADDR, delay_time );

    addr_claim_state = STATE_1_DELAY;
    }
else if(addr_claim_state == STATE_1_DELAY)
    {
    /*--------------------------------------------------
    This state just waits for a delay to complete, which
    we do with timers, so skip to state 2 now.
    --------------------------------------------------*/
    addr_claim_state = STATE_2A_TX;
    }
else if(addr_claim_state == STATE_2A_TX)
    {
    /*--------------------------------------------------
    Transmit address claim.
    --------------------------------------------------*/
    tx_addr_claim();

    addr_claim_state = STATE_2B_TX;
    }
else if(addr_claim_state == STATE_2B_TX)
    {
    /*--------------------------------------------------
    Wait on address claim transmit status.
    --------------------------------------------------*/
    boolean tx_error;

    /*--------------------------------------------------
    Wait until we have transmitted something.
    --------------------------------------------------*/
    if( HWM_can_tx_error( &tx_error ) )
        {
        /*----------------------------------------------
        Check the transmit status.
        ----------------------------------------------*/
        if( tx_error )
            {
            /*----------------------------------------------
            There has been a problem sending the address
            claim. Go back to state 0 to start delay.
            ----------------------------------------------*/
            addr_claim_state = STATE_0_IDLE;
            }
        else
            {
            /*------------------------------------------
            Address claim sent ok.
            Wait 250ms in state 3 for a response.
            ------------------------------------------*/
            SYC_set_timer( SYC_TIMER_IOP_NMEA2K_ADDR, DELAY_250MS );

            addr_claim_state = STATE_3_PROC_RX;
            }
        }
    }
else if(addr_claim_state == STATE_3_PROC_RX)
    {
    /*--------------------------------------------------
    This state is handled by process_rx_frame, which
    will transition to states 2 or 4. If it gets
    here, the timer has expired with no response
    received, so skip to state 5.
    --------------------------------------------------*/
    addr_claim_state = STATE_5_SUCCESS;

    /*--------------------------------------------------
    We now have a valid address.
    --------------------------------------------------*/
    #if ( SYC_NVM_SUPPORT == TRUE )
        NVM_write_nonvol( iop_nmea2k_addr, iop_nmea2k_address );
    #else
        HWM_xfer_my_nmea2k_address = iop_nmea2k_address;
    #endif

    iop_nmea2k_address_valid = TRUE;
    }
else if(addr_claim_state == STATE_4_NEW_ADDR)
    {
    /*--------------------------------------------------
    Choose a new address.
    --------------------------------------------------*/
    iop_nmea2k_address_valid = FALSE;

    iop_nmea2k_address++;
    iop_nmea2k_address %= NMBR_ADDRESSES;

    #if ( SYC_NVM_SUPPORT == TRUE )
    if( iop_nmea2k_address == NVM_read_nonvol( iop_nmea2k_addr ) )
    #else
    if( iop_nmea2k_address == HWM_xfer_my_nmea2k_address )
    #endif
        {
        /*----------------------------------------------
        Error. We have checked all addresses, and didn't
        find an unused one.
        ----------------------------------------------*/
        iop_nmea2k_address = CANT_CLAIM_ADDRESS;

        /*----------------------------------------------
        Delay a random time.
        ----------------------------------------------*/
        delay_time = ( HWM_get_random_nmbr() % (MAX_INTERVAL_DELAY + 1 - MIN_INTERVAL_DELAY) ) + MIN_INTERVAL_DELAY;
        SYC_set_timer_runtime( SYC_TIMER_IOP_NMEA2K_ADDR, delay_time );

        addr_claim_state = STATE_6_DELAY;
        }
    else
        {
        addr_claim_state = STATE_2A_TX;
        }
    }
else if(addr_claim_state == STATE_5_SUCCESS)
    {
    /*--------------------------------------------------
    This is the normal run state. Any transitions are
    handled by process_rx_frame. Turn off the timer so
    we don't come back to the address claim until we
    need to switch states.
    --------------------------------------------------*/
    SYC_set_timer_off( SYC_TIMER_IOP_NMEA2K_ADDR );
    }
else if(addr_claim_state == STATE_6_DELAY)
    {
    /*--------------------------------------------------
    This state just waits for a delay to complete, which
    we do with timers, so skip to state 7 now.
    --------------------------------------------------*/
    addr_claim_state = STATE_7_NO_ADDR;
    }
else if(addr_claim_state == STATE_7_NO_ADDR)
    {
    /*--------------------------------------------------
    Send our address (should be CANT_CLAIM_ADDRESS).
    --------------------------------------------------*/
    UTL_assert( (iop_nmea2k_address == CANT_CLAIM_ADDRESS), UTL_FILE_IOP_NMEA2K );
    tx_addr_claim();

    addr_claim_state = STATE_8_WAIT_REQ;
    }
else if(addr_claim_state == STATE_8_WAIT_REQ)
    {
    /*--------------------------------------------------
    Nothing to do. We are waiting on an address request.
    Any transitions are handled by process_rx_frame.
    Turn off the timer so we don't come back to the
    address claim until we need to switch states.
    --------------------------------------------------*/
    SYC_set_timer_off( SYC_TIMER_IOP_NMEA2K_ADDR );
    }
else if(addr_claim_state == STATE_9_TX)
    {
    tx_addr_claim();

    addr_claim_state = STATE_5_SUCCESS;
    }
else
    {
    /*--------------------------------------------------
    Invalid state.
    --------------------------------------------------*/
    UTL_assert_always( UTL_FILE_IOP_NMEA2K );
    }
} /* addr_claim() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       addr_conflict - Address Conflict
*
*   DESCRIPTION:
*       When this function has called, we have received an address
*       claim message from another unit that matches our address.
*       See Figure B-1: Address Claim State Diagram in the NMEA 2000
*       Documentation, Appendix D.
*
*********************************************************************/
static void addr_conflict
    (
    uint8  *remote_name         /* name of remote (conflicting) unit */
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8   name[8];
sint8   i;
boolean iwin;

/*----------------------------------------------------------
Get my name.
----------------------------------------------------------*/
get_name( name );

/*----------------------------------------------------------
Compare the names as uint64's. Lower one wins.
----------------------------------------------------------*/
iwin = FALSE;
for( i = 7; i >= 0; i-- )
    {
    if( name[i] < remote_name[i] )
        {
        iwin = TRUE;
        break;
        }
    else if( name[i] > remote_name[i] )
        {
        break;
        }
    }

/*----------------------------------------------------------
Only respond if we are in states 2B, 3 or 5.
----------------------------------------------------------*/
switch( addr_claim_state )
    {
    case STATE_2B_TX:
    case STATE_3_PROC_RX:
        if( iwin )
            {
            addr_claim_state = STATE_2A_TX;
            }
        else
            {
            addr_claim_state = STATE_4_NEW_ADDR;
            }
        SYC_set_timer_expired(SYC_TIMER_IOP_NMEA2K_ADDR);
        break;

    case STATE_5_SUCCESS:
        if( iwin )
            {
            addr_claim_state = STATE_9_TX;
            }
        else
            {
            addr_claim_state = STATE_4_NEW_ADDR;
            }
        SYC_set_timer_expired(SYC_TIMER_IOP_NMEA2K_ADDR);
        break;

    default:
        break;
    }
} /* addr_conflict() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       addr_request - Address Request
*
*   DESCRIPTION:
*       When this function has called, we have received a request for
*       the address claim message. For handling, see Figure B-1:
*       Address Claim State Diagram in the NMEA 2000 Documentation,
*       Appendix D.
*
*********************************************************************/
static void addr_request
    (
    void
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8 delay_time;

/*----------------------------------------------------------
Only respond if we are in states 5 or 8.
----------------------------------------------------------*/
switch( addr_claim_state )
    {
    case STATE_5_SUCCESS:
        addr_claim_state = STATE_9_TX;
        SYC_set_timer_expired(SYC_TIMER_IOP_NMEA2K_ADDR);
        break;

    case STATE_8_WAIT_REQ:
        /*--------------------------------------------------
        Delay a random time.
        --------------------------------------------------*/
        delay_time = ( HWM_get_random_nmbr() % (MAX_INTERVAL_DELAY + 1 - MIN_INTERVAL_DELAY) ) + MIN_INTERVAL_DELAY;
        SYC_set_timer_runtime( SYC_TIMER_IOP_NMEA2K_ADDR, delay_time );

        addr_claim_state = STATE_6_DELAY;
        break;

    default:
        break;
    }
} /* addr_request() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       fast_packet_rx - Handle Reception of a NMEA2K Fast-Packet
*                        Message
*
*   DESCRIPTION:
*       Stores the frame in the fast-packet buffers, if applicable.
*       Passes back an index into the fast-packet array if this was the
*       final frame of a message. Otherwise, passes back -1.
*
*********************************************************************/
static uint8 fast_packet_rx
    (
    HWM_can_id_t        const * identifier, /* CAN Extended ID field */
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data,       /* Payload */
    uint8                   * * data_ptr    /* Pointer to packet to process */
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8 i;
uint8 free_space;
uint8 lower_prio;
boolean is_new_grmn;

/*----------------------------------------------------------
Initialize
----------------------------------------------------------*/
free_space = SIMUL_FAST_PACKETS;
lower_prio = SIMUL_FAST_PACKETS;
is_new_grmn = FALSE;

if( (data[0] & 0x1F) == 0 )
    {
    /*------------------------------------------------------
    This is the first packet in a new series.
    ------------------------------------------------------*/

    /*------------------------------------------------------
    If the packet fits in 1 frame, process now instead of
    taking up buffer space.
    ------------------------------------------------------*/
    if( data[1] <= 6 )
        {
        *data_ptr = (uint8 *)&data[2];
        return( data[1] );
        }

    /*------------------------------------------------------
    For proprietary fast-packet frames, make sure the
    manufacturer code is Garmin and the destination port is
    one that we handle.
    ------------------------------------------------------*/
    if( pgn->full == iop_NMEA_PROPR_FP_AD_PGN )
        {
        if(   ( data[2] == (PROPR_HEADER & 0xFF) )
           && ( data[3] == (PROPR_HEADER >> 8  ) )
           && (   ( data[7] == IOP_GRMN_NMEA2K_GARMIN_APP_PORT )
               || ( data[7] == IOP_GRMN_NMEA2K_SENSOR_PORT     ) ) )
            {
            /*----------------------------------------------
            Manufacturer code and port are ok. Check the
            Inst ID to see if we process it.
            ----------------------------------------------*/
            IOP_inst_id_type id;

            id = ( data[5] << 8 ) | data[4];

            if( iop_grmn_proc_input(id, NULL, 0, NULL, TRUE) == FALSE )
                {
                /*------------------------------------------
                IOP does not process this Inst ID. Drop
                frame.
                ------------------------------------------*/
                return( 0 );
                }

            is_new_grmn = TRUE;
            }
        else
            {
            /*----------------------------------------------
            Invalid manufacturer code or port. Drop frame.
            ----------------------------------------------*/
            return( 0 );
            }
        }
    }

/*----------------------------------------------------------
See if this packet matches an ID in our current buffers.
Also, search for lower priority or free space entries to
replace.
----------------------------------------------------------*/
for( i = 0; i < SIMUL_FAST_PACKETS; i++ )
    {
    if( ( fast_packets[i].timeout > 0 )
     && ( fast_packets[i].id.ext == identifier->ext ) )
        {
        /*--------------------------------------------------
        We are saving this message. Save the new frame.
        --------------------------------------------------*/
        if( data[0] == (fast_packets[i].seq + 1) )
            {
            /*----------------------------------------------
            Sequency number matches expected value.
            ----------------------------------------------*/
            memcpy( &fast_packets[i].data[ fast_packets[i].data_size ], &data[1], 7 );
            fast_packets[i].data_size += 7;
            fast_packets[i].seq = data[0];

            if( fast_packets[i].data_size >= fast_packets[i].length )
                {
                /*------------------------------------------
                This was the final frame of the packet.
                ------------------------------------------*/
                fast_packets[i].timeout = 0;

                *data_ptr = fast_packets[i].data;
                return( fast_packets[i].length );
                }
            else
                {
                fast_packets[i].timeout = FAST_PACKET_TIMEOUT / iop_NMEA2K_TASK_PERIOD;
                }
            }
        else
            {
            /*----------------------------------------------
            Sequence number is unexpected. Remove existing
            entry.
            ----------------------------------------------*/
            fast_packets[i].timeout = 0;
            free_space = i;
            }
        }
    else if( fast_packets[i].timeout == 0 )
        {
        free_space = i;
        }

    /*-------------------------------------------------------
    lower_prio will contain the index of the last fast packet
    buffer that:
    a) is lower priority based on CAN ID.
    OR
    b) contains a packet that is not Garmin proprietary and
    the current frame is Garmin proprietary.

    This isn't too bad of a problem with only one buffer.
    -------------------------------------------------------*/
    else if( ( fast_packets[i].id.ext > identifier->ext )
          || ( (is_new_grmn == TRUE) && (fast_packets[i].is_grmn == FALSE) ) )
        {
        lower_prio = i;
        }
    }

if( (data[0] & 0x1F) == 0 )
    {
    /*------------------------------------------------------
    This is the first packet in a new series. Save it if
    there is free space or a lower priority space.
    ------------------------------------------------------*/
    i = ( free_space < SIMUL_FAST_PACKETS ) ? free_space : lower_prio;

    if( i < SIMUL_FAST_PACKETS )
        {
        /*--------------------------------------------------
        Check if new frame will overwrite existing buffer.
        --------------------------------------------------*/
        UTL_assert( fast_packets[i].timeout == 0, UTL_FILE_IOP_NMEA2K );

        /*--------------------------------------------------
        Space found. Save the new frame.
        --------------------------------------------------*/
        memcpy( &fast_packets[i].data, &data[2], 6 );
        fast_packets[i].id.ext = identifier->ext;
        fast_packets[i].is_grmn = is_new_grmn;
        fast_packets[i].data_size = 6;
        fast_packets[i].seq = data[0];
        fast_packets[i].length = data[1];
        fast_packets[i].timeout = FAST_PACKET_TIMEOUT / iop_NMEA2K_TASK_PERIOD;
        }
    else
        {
        /*--------------------------------------------------
        Frame dropped.
        --------------------------------------------------*/
        UTL_assert_always( UTL_FILE_IOP_NMEA2K );
        }
    }

return( 0 );
} /* fast_packet_rx() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       get_name - Get NMEA 2000 NAME
*
*   DESCRIPTION:
*       Fills data with the 8-byte NAME field.
*
*********************************************************************/
static void get_name
    (
    uint8 * data        /* will be filled with name (must be at least 8 bytes!) */
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint32 unit_id;
uint8 system_instance;
uint8 device_instance;

#if ( SYC_NVM_SUPPORT == TRUE )
    system_instance = NVM_read_nonvol( iop_nmea2k_sys_inst );
    device_instance = NVM_read_nonvol( iop_nmea2k_dev_inst );
#else
    system_instance = SYSTEM_INSTANCE_NO_NVM;
    device_instance = DEVICE_INSTANCE_NO_NVM;
#endif

/*----------------------------------------------------------
Copy the constant name fields from flash.
----------------------------------------------------------*/
iop_get_name_prj( data );

/*----------------------------------------------------------
Fill in the instances.
----------------------------------------------------------*/
((iop_nmea2k_name_field_t *)data)->systemInst           = system_instance;
*((uint8*)&((iop_nmea2k_name_field_t *)data)->dev_inst) = device_instance;

/*----------------------------------------------------------
Fill in the id field.
----------------------------------------------------------*/
#if ( SYC_NVM_SUPPORT == TRUE )
    unit_id = NVM_read_nonvol( syc_unit_id );
#else
    unit_id = my_random_unit_ID;
#endif

((iop_nmea2k_name_field_t *)data)->identity =
        ( unit_id & iop_NMEA2K_IDENTITY_UNIT_ID_MASK )
      | ( (uint32)( PRODUCT_NUM_DEC & iop_NMEA2K_IDENTITY_PROD_NUM_MASK ) << iop_NMEA2K_IDENTITY_PROD_NUM_LSB );

} /* get_name() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       process_complete_packet - Process Complete Packet
*
*   DESCRIPTION:
*       Data_ptr points to a packet that has been received in its
*       entirity that has been sent to us directly or to global. This
*       function decides how to handle the packet.
*
*********************************************************************/
static void process_complete_packet
    (
    iop_nmea2k_pgn_t  * pgn,
    uint8             * data_ptr,
    uint8               data_len,
    uint8               source_addr,
    uint8               dest_addr
    )
{
/*----------------------------------------------------------
The only PGNs that we handle when we don't have a valid
nmea2k address are:
iop_NMEA_ISO_ADD_CLAIM
iop_NMEA_ISO_REQ_PGN for the iop_NMEA_ISO_ADD_CLAIM
iop_NMEA_PROPR_xx_AD_PGN with an inst of IOP_HOLD_IN_BB (bbbld only)

In order to facilitate handling the IOP_HOLD_IN_BB before
we have a valid address, we process all garmin IOP packets
yet pass in a just_test value of TRUE when the nmea2k
address is invalid and a just_test value of FALSE when the
nmea2k address is valid. Then in the iop handler, we
actually set the hold_in_bb flag even when just_test is
TRUE.

If you're worried about the hackish nature of this
implementation, consider that the very nature of the hold in
BB command requires a hack. We have to listen for the
command before we claim an address because the BB won't
claim an address until it is determined that we need to
hold in BB. It was decided that this implementation is as
good as any and requires very little extra code space.
----------------------------------------------------------*/
if( pgn->full == iop_NMEA_ISO_ADD_CLAIM )
    {
    if( iop_nmea2k_address == source_addr )
        {
        /*--------------------------------------------------
        Address conflict!
        --------------------------------------------------*/
        addr_conflict( data_ptr );
        }
    }
else if( pgn->full == iop_NMEA_ISO_REQ_PGN)
    {
    /*------------------------------------------------------
    Set PGN to the requested PGN.
    ------------------------------------------------------*/
    memcpy( (uint8 *)pgn, data_ptr, 3 );

    if( pgn->full == iop_NMEA_ISO_ADD_CLAIM )
        {
        addr_request();
        }
    else if( iop_nmea2k_address_valid == FALSE )
        {
        /*--------------------------------------------------
        Only handle address claim and address claim request
        messages until our address is valid.
        --------------------------------------------------*/
        return;
        }
    else if( pgn->full == iop_NMEA_PROD_INFO_PGN )
        {
        tx_product_info();
        }
    else if( pgn->full == iop_NMEA_PGN_LIST_PGN )
        {
        tx_pgn_list( source_addr, iop_NMEA2K_DD145_TRANSMIT );
        tx_pgn_list( source_addr, iop_NMEA2K_DD145_RECEIVE );
        }
    else if( (pgn->full == iop_NMEA_PROPR_FP_AD_PGN )
          || (pgn->full == iop_NMEA_PROPR_SF_AD_PGN ) )
        {
        /*--------------------------------------------------
        The certification tool requires a response to all
        non-mandatory and fast-packet PGNs.
        --------------------------------------------------*/
        tx_grmn_invalid( pgn, source_addr );
        }
    else if( ( iop_nmea2k_process_reqest_prj( pgn, source_addr ) == FALSE )
          && ( dest_addr == iop_nmea2k_address ) )
        {
        /*--------------------------------------------------
        Unhandled request. If sent directly to us, send a
        NACK back.
        --------------------------------------------------*/
        tx_nack( pgn, source_addr );
        }
    }
/*----------------------------------------------------------
Go ahead and handle Garmin proprietary packets even before
we know if we have a valid nmea2k address. This is done so
that the hold in BB command gets handled even before the BB
acquires an address. Making this call is ok because the iop
handler gets passed a value of just_test = TRUE when the
nmea2k address is invalid.
----------------------------------------------------------*/
else if( (pgn->full == iop_NMEA_PROPR_SF_AD_PGN)
      || (pgn->full == iop_NMEA_PROPR_FP_AD_PGN) )
    {
    /*------------------------------------------------------
    This is a proprietary packet. Only handle if a Garmin
    device sent it.
    ------------------------------------------------------*/
    if( ( data_ptr[0] == (PROPR_HEADER & 0xFF) )
     && ( data_ptr[1] == (PROPR_HEADER >> 8  ) )
      )
        {
        process_grmn_data( source_addr, &data_ptr[2], (data_len - 2) );
        }
    }
else if( iop_nmea2k_address_valid == FALSE )
    {
    /*------------------------------------------------------
    Only handle the following messages until our address is
    valid:
    address claim
    address claim request
    IOP hold in BB command
    ------------------------------------------------------*/
    return;
    }
else if( pgn->full == iop_NMEA_REQ_CMD_ACK_PGN)
    {
    switch( data_ptr[0] )
        {
        case iop_NMEA2K_DD144_REQUEST:
            process_complex_req( data_ptr, source_addr, dest_addr );
            break;

        case iop_NMEA2K_DD144_COMMAND:
            process_complex_cmd( data_ptr, source_addr, dest_addr );
            break;

        default:
            /*----------------------------------------------
            Unknown/unhandled group function. No reply.
            ----------------------------------------------*/
            break;
        }
    }
else if( pgn->full == iop_NMEA_ISO_ACK_PGN )
    {
    /*------------------------------------------------------
    NMEA Certification requires that we list this PGN as
    receivable. We don't do anything with it, though.
    ------------------------------------------------------*/
    }
else if( !iop_nmea2k_process_complete_packet_prj( pgn, data_ptr ) )
    {
    /*------------------------------------------------------
    Unknown PGN. It should have been filtered out before
    calling this function.
    ------------------------------------------------------*/
    UTL_assert_always( UTL_FILE_IOP_NMEA2K );
    }
} /* process_complete_packet() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       process_complex_cmd - Process Complex Command
*
*   DESCRIPTION:
*       Handles command group function of PGN 126208.
*
*********************************************************************/
static void process_complex_cmd
    (
    uint8       const * data_ptr,
    uint8       const   source_addr,
    uint8       const   dest_addr
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
iop_nmea2k_pgn_t    requested_pgn;
iop_nmea2k_dd139_t8 priority_err;
iop_nmea2k_dd037_t8 pgn_err;
iop_nmea2k_dd141_t8 param_err_list[ MAX_NMBR_RQST_PARAMS + 2 ];
uint8               num_params;
uint8               i;

/*----------------------------------------------------------
Commands cannot be sent to the global address.
----------------------------------------------------------*/
if( dest_addr != iop_nmea2k_address )
    {
    return;
    }

/*----------------------------------------------------------
Initialize
----------------------------------------------------------*/
priority_err = iop_NMEA2K_DD139_NO_ERR;
pgn_err      = iop_NMEA2K_DD037_NO_ERR;
memset( &param_err_list, iop_NMEA2K_DD141_NO_ERR, sizeof( param_err_list ) );

data_ptr++;     /* Skip first byte, we know this is a command already */

/*----------------------------------------------------------
Read the PGN.
----------------------------------------------------------*/
memcpy( (uint8 *)&requested_pgn.full, data_ptr, 3 );
data_ptr += 3;
requested_pgn.pdu.sbz = 0;

/*----------------------------------------------------------
Read the priority setting.
----------------------------------------------------------*/
if( (*data_ptr & 0x0F) < 0x08 )
    {
    /*------------------------------------------------------
    Error if trying to change it.
    ------------------------------------------------------*/
    priority_err = iop_NMEA2K_DD139_DENIED;
    }
data_ptr += 1;

/*----------------------------------------------------------
Read the number of requested parameters.
----------------------------------------------------------*/
num_params = *data_ptr++;

/*----------------------------------------------------------
Make sure our buffers are large enough to handle the
request. Otherwise, send that access is denied.
----------------------------------------------------------*/
if( num_params > MAX_NMBR_RQST_PARAMS )
    {
    pgn_err = iop_NMEA2K_DD037_DENIED;
    }
else
    {
    if( requested_pgn.full == iop_NMEA_ISO_ADD_CLAIM )
        {
        #if( _SYSBLD == _ON )
            {
            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 3:
                        /*---------------------------------------------------
                        Field 3: Device Instance Lower (ISO ECU Instance)
                        ---------------------------------------------------*/
                        set_dev_inst_lower( *data_ptr );
                        data_ptr += 1;      /* Field 3 size is 3 bits */
                        break;

                    case 4:
                        /*-------------------------------------------------------
                        Field 4: Device Instance Upper (ISO Function Instance)
                        -------------------------------------------------------*/
                        set_dev_inst_upper( (*data_ptr) << 3 );
                        data_ptr += 1;      /* Field 4 size is 5 bits */
                        break;

                    case 8:
                        /*---------------------------------------------------
                        Field 8: System Instance (ISO Device Class Instance)
                        ---------------------------------------------------*/
                        set_sys_inst( *data_ptr );
                        data_ptr += 1;      /* Field 8 size is 4 bits */
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        break;
                    }
                }
            }
        #else /* ( _SYSBLD != _ON ) */
            /*------------------------------------------
            Return PGN temporarily not unavailable.
            ------------------------------------------*/
            pgn_err = iop_NMEA2K_DD037_UNAVAIL;
        #endif /* ( _SYSBLD == _ON ) */
        }
    /*--------------------------------------------------
    Give the project-specific function a chance.
    --------------------------------------------------*/
    else if( !iop_nmea2k_process_complex_cmd_prj( &requested_pgn, data_ptr, num_params,
                                                  priority_err, &pgn_err, param_err_list ) )
        {
        /*----------------------------------------------
        Check PGN_INFO_TBL to see if we support the PGN.
        ----------------------------------------------*/
        for( i = 0; i < cnt_of_array( PGN_INFO_TBL ); i++ )
            {
            if( PGN_INFO_TBL[i].pgn.full == requested_pgn.full )
                {
                break;
                }
            }

        if( i == cnt_of_array( PGN_INFO_TBL ) )
            {
            /*------------------------------------------
            We do not support support the PGN.
            ------------------------------------------*/
            pgn_err = iop_NMEA2K_DD037_BAD_PGN;
            }
        else
            {
            /*----------------------------------------------
            We support this PGN, but we don't support the
            complex request for it.
            ----------------------------------------------*/
            pgn_err = iop_NMEA2K_DD037_BAD_REQ;
            }
        }
    }

/*----------------------------------------------------------
At this point, we have processed the data. We now have to
send out an acknowledgement with any errors.
----------------------------------------------------------*/
tx_complex_ack( &requested_pgn, source_addr, num_params,
                priority_err, pgn_err, param_err_list );
} /* process_complex_cmd() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       process_complex_req - Process Complex Request
*
*   DESCRIPTION:
*       Handles request group function of PGN 126208. This will
*       reply with a PGN if the given fields match the given values.
*       Otherwise, it generates a NACK.
*
*********************************************************************/
static void process_complex_req
    (
    uint8       const * data_ptr,
    uint8       const   source_addr,
    uint8       const   dest_addr
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
iop_nmea2k_pgn_t    requested_pgn;
iop_nmea2k_dd139_t8 interval_err;
iop_nmea2k_dd037_t8 pgn_err;
iop_nmea2k_dd141_t8 param_err_list[ MAX_NMBR_RQST_PARAMS + 2 ];
boolean             param_err;
uint8               num_params;
uint8               i;

/*----------------------------------------------------------
Initialize
----------------------------------------------------------*/
interval_err = iop_NMEA2K_DD139_NO_ERR;
pgn_err      = iop_NMEA2K_DD037_NO_ERR;
param_err    = FALSE;
memset( &param_err_list, iop_NMEA2K_DD141_NO_ERR, sizeof( param_err_list ) );

data_ptr++;     /* Skip first byte, we know this is a request already */

/*----------------------------------------------------------
Read the PGN.
----------------------------------------------------------*/
memcpy( (uint8 *)&requested_pgn.full, data_ptr, 3 );
data_ptr += 3;
requested_pgn.pdu.sbz = 0;

/*----------------------------------------------------------
Read the transmission interval.
----------------------------------------------------------*/
if( *(uint32 *)data_ptr < 0xFFFFFFFE )
    {
    /*------------------------------------------------------
    Error if trying to change it.
    ------------------------------------------------------*/
    interval_err = iop_NMEA2K_DD139_DENIED;
    }
data_ptr += 4;

/*----------------------------------------------------------
Read the transmission interval offset.
----------------------------------------------------------*/
if( ( *(uint16 *)data_ptr != 0x0000 )
 && ( *(uint16 *)data_ptr != 0xFFFF ) )
    {
    /*------------------------------------------------------
    Error if trying to change it.
    ------------------------------------------------------*/
    interval_err = iop_NMEA2K_DD139_DENIED;
    }
data_ptr += 2;

/*----------------------------------------------------------
Read the number of requested parameters.
----------------------------------------------------------*/
num_params = *data_ptr++;

/*----------------------------------------------------------
Make sure our buffers are large enough to handle the
request. Otherwise, send that access is denied.
----------------------------------------------------------*/
if( num_params > MAX_NMBR_RQST_PARAMS )
    {
    pgn_err = iop_NMEA2K_DD037_DENIED;
    }
else
    {
    if( requested_pgn.full == iop_NMEA_PROD_INFO_PGN )
        {
        #if( _SYSBLD == _ON )
            {
            boolean send_prod_info;

            /*--------------------------------------------------
            Send by default if no parameters are specified.
            --------------------------------------------------*/
            send_prod_info = TRUE;

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 2:
                        /*--------------------------------------
                        Field 2: Manufacturer Product Code
                        --------------------------------------*/
                        {
                        uint16 prod_code;

                        /*----------------------------------------------------------
                        Determine Product Code based on the Adapter Type.
                        ----------------------------------------------------------*/
                        switch( HWM_get_sensor_type() )
                            {
                            case TEMPERATURE_SENSOR:
                                prod_code = PROD_INFO_PROD_CODE_GRA10;
                                break;

                            case HEADING_SENSOR:
                                prod_code = PROD_INFO_PROD_CODE_GET10;
                                break;

                            default:
                                prod_code = PROD_INFO_PROD_CODE_GRA10;
                                UTL_assert_always( UTL_FILE_IOP_NMEA2K );
                                break;
                            }

                        if( *(uint16 *)data_ptr != prod_code )
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                            param_err = TRUE;
                            }

                        data_ptr += 2;      /* Field 2 size is 2 bytes */
                        break;
                        }

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        param_err = TRUE;

                        /*--------------------------------------
                        Once we receive an invalid parameter,
                        stop checking the rest of the packet.
                        --------------------------------------*/
                        num_params = i + 1;
                        break;
                    }
                }

            /*--------------------------------------------------
            The packet has been processed. Now decide the reply.
            --------------------------------------------------*/
            if( ( interval_err == iop_NMEA2K_DD139_NO_ERR )
             && ( param_err == FALSE )
             && ( send_prod_info == TRUE ) )
                {
                tx_product_info();
                }
            }
        #else /* ( _SYSBLD != _ON ) */
            /*------------------------------------------
            Return PGN temporarily not unavailable.
            ------------------------------------------*/
            pgn_err = iop_NMEA2K_DD037_UNAVAIL;
        #endif /* ( _SYSBLD == _ON ) */
        }
    else if( requested_pgn.full == iop_NMEA_PGN_LIST_PGN )
        {
        #if( _SYSBLD == _ON )
            {
            boolean send_xmit_list;
            boolean send_recv_list;

            /*--------------------------------------------------
            Send by default if no parameters are specified.
            --------------------------------------------------*/
            send_xmit_list = TRUE;
            send_recv_list = TRUE;

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 1:
                        /*--------------------------------------
                        Field 1: Group Function Code
                        --------------------------------------*/
                        if( *data_ptr == iop_NMEA2K_DD145_TRANSMIT )
                            {
                            send_recv_list = FALSE; /* Transmit list requested. Don't send receive list. */
                            }
                        else if( *data_ptr == iop_NMEA2K_DD145_RECEIVE )
                            {
                            send_xmit_list = FALSE; /* Receive list requested. Don't send transmit list. */
                            }
                        else
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                            param_err = TRUE;
                            }

                        data_ptr++;     /* Field 1 size is 1 byte */
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        param_err = TRUE;

                        /*--------------------------------------
                        Once we receive an invalid parameter,
                        stop checking the rest of the packet.
                        --------------------------------------*/
                        num_params = i + 1;
                        break;
                    }
                }

            /*--------------------------------------------------
            The packet has been processed. Now decide the reply.
            --------------------------------------------------*/
            if( ( interval_err == iop_NMEA2K_DD139_NO_ERR )
             && ( param_err == FALSE ) )
                {
                if( send_xmit_list == TRUE )
                    {
                    tx_pgn_list( source_addr, iop_NMEA2K_DD145_TRANSMIT );
                    }
                if( send_recv_list == TRUE )
                    {
                    tx_pgn_list( source_addr, iop_NMEA2K_DD145_RECEIVE );
                    }
                }
            }
        #else /* ( _SYSBLD != _ON ) */
            /*------------------------------------------
            Return PGN temporarily not unavailable.
            ------------------------------------------*/
            pgn_err = iop_NMEA2K_DD037_UNAVAIL;
        #endif /* ( _SYSBLD == _ON ) */
        }
    else if( requested_pgn.full == iop_NMEA_ISO_ADD_CLAIM )
        {
        boolean send_add_claim;
        iop_nmea2k_name_field_t name;

        /*--------------------------------------------------
        Send by default if no parameters are specified.
        --------------------------------------------------*/
        send_add_claim = TRUE;
        get_name( (uint8 *)&name );

        for( i = 0; i < num_params; i++ )
            {
            switch( *data_ptr++ )
                {
                case 2:
                    /*--------------------------------------
                    Field 2: Manufacturer Code
                    --------------------------------------*/
                    if( ( *(uint16 *)data_ptr & 0x03FF ) != (uint16)name.manufacturer )
                        {
                        param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                        param_err = TRUE;
                        }
                    data_ptr += 2;      /* Field 2 size is 11 bits */
                    break;

                case 3:
                    /*---------------------------------------------------
                    Field 3: Device Instance Lower (ISO ECU Instance)
                    ---------------------------------------------------*/
                    if( ( *data_ptr & 0x07 ) != (uint8)name.dev_inst.ecuInst )
                        {
                        param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                        param_err = TRUE;
                        }
                    data_ptr += 1;      /* Field 3 size is 3 bits */
                    break;

                case 4:
                    /*-------------------------------------------------------
                    Field 4: Device Instance Upper (ISO Function Instance)
                    -------------------------------------------------------*/
                    if( ( *data_ptr & 0x1F ) != (uint8)name.dev_inst.functionInst )
                        {
                        param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                        param_err = TRUE;
                        }
                    data_ptr += 1;      /* Field 4 size is 5 bits */
                    break;

                case 5:
                    /*--------------------------------------
                    Field 5: Device Function (ISO Function)
                    --------------------------------------*/
                    if( *data_ptr != (uint8)name.function )
                        {
                        param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                        param_err = TRUE;
                        }
                    data_ptr += 1;      /* Field 5 size is 8 bits */
                    break;

                case 7:
                    /*--------------------------------------
                    Field 7: Device Class
                    --------------------------------------*/
                    if( ( *data_ptr & 0x7F ) != (uint8)name.deviceClass )
                        {
                        param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                        param_err = TRUE;
                        }
                    data_ptr += 1;      /* Field 7 size is 7 bits */
                    break;

                case 8:
                    /*---------------------------------------------------
                    Field 8: System Instance (ISO Device Class Instance)
                    ---------------------------------------------------*/
                    if( ( *data_ptr & 0x0F ) != (uint8)name.systemInst )
                        {
                        param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                        param_err = TRUE;
                        }
                    data_ptr += 1;      /* Field 8 size is 4 bits */
                    break;

                case 9:
                    /*---------------------------------------------------
                    Field 9: Industry Group
                    ---------------------------------------------------*/
                    if( ( *data_ptr & 0x07 ) != (uint8)name.industryGrp )
                        {
                        param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                        param_err = TRUE;
                        }
                    data_ptr += 1;      /* Field 9 size is 3 bits */
                    break;

                default:
                    param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                    param_err = TRUE;

                    /*--------------------------------------
                    Once we receive an invalid parameter,
                    stop checking the rest of the packet.
                    --------------------------------------*/
                    num_params = i + 1;
                    break;
                }
            }

        /*--------------------------------------------------
        The packet has been processed. Now decide the reply.
        --------------------------------------------------*/
        if( ( interval_err == iop_NMEA2K_DD139_NO_ERR )
         && ( param_err == FALSE )
         && ( send_add_claim == TRUE ) )
            {
            tx_addr_claim();
            }
        }

    /*------------------------------------------------------
    Give the project-specific function a chance.
    ------------------------------------------------------*/
    else if( !iop_nmea2k_process_complex_req_prj( &requested_pgn, data_ptr, num_params,
                                                  interval_err, &pgn_err, &param_err,
                                                  param_err_list ) )
        {
        /*----------------------------------------------
        Check PGN_INFO_TBL to see if we support the PGN.
        ----------------------------------------------*/
        for( i = 0; i < cnt_of_array( PGN_INFO_TBL ); i++ )
            {
            if( PGN_INFO_TBL[i].pgn.full == requested_pgn.full )
                {
                break;
                }
            }

        if( i == cnt_of_array( PGN_INFO_TBL ) )
            {
            /*------------------------------------------
            We do not support support the PGN.
            ------------------------------------------*/
            pgn_err = iop_NMEA2K_DD037_BAD_PGN;
            }
        else
            {
            /*----------------------------------------------
            We support this PGN, but we don't support the
            complex request for it.
            ----------------------------------------------*/
            pgn_err = iop_NMEA2K_DD037_BAD_REQ;
            }
        }
    }

/*----------------------------------------------------------
At this point, we have processed the data and sent out any
requested packet or set error flags. Check the error flags
to see if we should send an acknowledgement.
----------------------------------------------------------*/
if( ( dest_addr == iop_nmea2k_address )
 && ( ( interval_err != iop_NMEA2K_DD139_NO_ERR )
   || ( pgn_err != iop_NMEA2K_DD037_NO_ERR )
   || ( param_err != FALSE )
    )
  )
    {
    /*------------------------------------------------------
    There was an error and the packet was send directly to
    us. Send back an acknowledgement.
    ------------------------------------------------------*/
    tx_complex_ack( &requested_pgn, source_addr, num_params,
                    interval_err, pgn_err, param_err_list );
    }
} /* process_complex_req() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       process_grmn_data - Process Received Garmin Data
*
*   DESCRIPTION:
*       This procedure receives Garmin data.
*
*********************************************************************/
static void process_grmn_data
    (
    uint8       source_addr,
    uint8     * data,
    uint8       data_len
    )
{
/*----------------------------------------------------------
Local variables.
----------------------------------------------------------*/
IOP_inst_id_type id;
IOP_route_type   route;

/*----------------------------------------------------------
data[0] = Inst ID (LSB)
data[1] = Inst ID (MSB)
data[2] = Source Port
data[3] = Destination Port
----------------------------------------------------------*/
if( ( data[3] == IOP_GRMN_NMEA2K_GARMIN_APP_PORT )
 || ( data[3] == IOP_GRMN_NMEA2K_SENSOR_PORT ) )
    {
    id = data[0] | ( data[1] << 8 );
    route.source_addr = source_addr;
    route.source_port = data[2];
    route.dest_port   = data[3];

    /*------------------------------------------------------
    We want to process almost all garmin data if and only if
    the nmea2k address is valid. The only IOP inst we want
    to process when the nmea2k address is invalid is
    IOP_HOLD_IN_BB. Therefore, go ahead and call the IOP
    handler even if the nmea2k address is invalid, but pass
    a value of just_test = TRUE. This allows us to ensure
    that no garmin IOP data will be processed when the
    nmea2k address is invalid, yet still handle the hold in
    BB command by ignoring just_test for that particular
    IOP inst.
    ------------------------------------------------------*/
    iop_grmn_proc_input( id, &data[4], (data_len - 4), &route, !iop_nmea2k_address_valid );
    }
} /* process_grmn_data() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       set_dev_inst_lower - Set Lower Part of Device Instance
*
*   DESCRIPTION:
*       Sets the device instance.
*
*********************************************************************/
#if( _SYSBLD == _ON )

static void set_dev_inst_lower
    (
    uint8 const new_inst
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8 cur_inst;

/*----------------------------------------------------------
Read current value.
----------------------------------------------------------*/
cur_inst = NVM_read_nonvol( iop_nmea2k_dev_inst );

/*----------------------------------------------------------
Store back, replacing the lower 3 bits.
----------------------------------------------------------*/
NVM_write_nonvol( iop_nmea2k_dev_inst, ((cur_inst & 0xF8) | (new_inst & 0x07)) );

/*----------------------------------------------------------
Send out the address claim again.
----------------------------------------------------------*/
addr_request();
} /* set_dev_inst_lower() */

#endif /* ( _SYSBLD == _ON ) */

/*********************************************************************
*
*   PROCEDURE NAME:
*       set_dev_inst_upper - Set Upper Part of Device Instance
*
*   DESCRIPTION:
*       Sets the device instance.
*
*********************************************************************/
#if( _SYSBLD == _ON )

static void set_dev_inst_upper
    (
    uint8 const new_inst
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8 cur_inst;

/*----------------------------------------------------------
Read current value.
----------------------------------------------------------*/
cur_inst = NVM_read_nonvol( iop_nmea2k_dev_inst );

/*----------------------------------------------------------
Store back, replacing the upper 5 bits.
----------------------------------------------------------*/
NVM_write_nonvol( iop_nmea2k_dev_inst, ((cur_inst & 0x07) | (new_inst & 0xF8)) );

/*----------------------------------------------------------
Send out the address claim again.
----------------------------------------------------------*/
addr_request();
} /* set_dev_inst_upper() */

#endif /* ( _SYSBLD == _ON ) */

/*********************************************************************
*
*   PROCEDURE NAME:
*       set_sys_inst - Set System Instance.
*
*   DESCRIPTION:
*       Sets the device instance.
*
*********************************************************************/
#if( _SYSBLD == _ON )

static void set_sys_inst
    (
    uint8 const new_inst
    )
{
/*----------------------------------------------------------
Save to nonvol
----------------------------------------------------------*/
NVM_write_nonvol( iop_nmea2k_sys_inst, new_inst );

/*----------------------------------------------------------
Send out the address claim again.
----------------------------------------------------------*/
addr_request();
} /* set_sys_inst() */

#endif /* ( _SYSBLD == _ON ) */

/*********************************************************************
*
*   PROCEDURE NAME:
*       tx_addr_claim - Transmit Address Claim Message
*
*   DESCRIPTION:
*       Transmits an address claim message with the current address.
*
*********************************************************************/
static void tx_addr_claim
    (
    void
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t    id;
uint8           data[8];

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( DEFAULT_PRIO )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_ISO_ADD_CLAIM | IOP_NMEA2K_GLOBAL_ADDRESS )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

/*----------------------------------------------------------
The name field goes into data.
----------------------------------------------------------*/
get_name( data );

/*----------------------------------------------------------
Send the frame.
----------------------------------------------------------*/
iop_nmea2k_single_frame_tx( &id, data, SINGLE_FRAME_MAX_SIZE, TRUE );
} /* tx_addr_claim() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       tx_complex_ack - Transmit Complex Acknowledgement
*
*   DESCRIPTION:
*       Transmits an acknowledgement for PGN 126208.
*
*********************************************************************/
static void tx_complex_ack
    (
    iop_nmea2k_pgn_t      * pgn,
    uint8                   source_addr,
    uint8                   num_params,
    iop_nmea2k_dd139_t8     interval_err,
    iop_nmea2k_dd037_t8     pgn_err,
    iop_nmea2k_dd141_t8   * param_err_list
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t    id;
uint8           data[ 6 + ( ( MAX_NMBR_RQST_PARAMS + 1 ) / 2 ) ]; /* Maximum size */
uint8           size;
uint8           i;

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
If there was a PGN error, mark transmission as not
supported and number of parameters as 0xFF, per NMEA
2000 Acknowledge PGN information.
----------------------------------------------------------*/
if( pgn_err != iop_NMEA2K_DD037_NO_ERR )
    {
    if( pgn_err == iop_NMEA2K_DD037_BAD_PGN )
        {
        num_params = 0;
        }
    else
        {
        num_params = 0xFF;
        interval_err = iop_NMEA2K_DD139_BAD_REQ;
        }
    }

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( 3 ) /* High Priority */
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_REQ_CMD_ACK_PGN | source_addr )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

/*----------------------------------------------------------
Data Fields:
1. Function Code (1 byte)
2. Requested PGN (3 bytes)
3. PGN Error Code (4 bits)
4. Transmission Error/Priority Code (4 bits)
5. Number of Parameters (1 byte)
6. First error code (4 bits)
7. Field 6 repeated.
----------------------------------------------------------*/
data[0] = iop_NMEA2K_DD144_ACK;
memcpy( &data[1], (uint8 *)&pgn->full, 3 );
data[4] = (interval_err << 4) | (pgn_err);
data[5] = num_params;

/*----------------------------------------------------------
0xFF is a special value that means the same as 0.
----------------------------------------------------------*/
if( num_params == 0xFF )
    {
    num_params = 0;
    }

/*----------------------------------------------------------
The errors are 4 bits each, starting with the LSB.
Unused bits should be filled with all 1s.
----------------------------------------------------------*/
param_err_list[num_params] = 0xF;
{
uint8 * d = &data[6];
for( i = 0; i < num_params; i += 2 )
    {
    *d++ = (param_err_list[i+1] << 4) | param_err_list[i];
    }
}
size = 6 + ((num_params + 1) >> 1);

/*----------------------------------------------------------
Send the message.
----------------------------------------------------------*/
iop_nmea2k_fast_packet_tx( &id, data, size );
} /* tx_complex_ack() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       tx_grmn_invalid - Transmit Invalid Garmin Packet
*
*   DESCRIPTION:
*       Transmits an invalid Garmin packet. This is required to pass
*       NMEA2000 certification, otherwise we wouldn't do it.
*
*********************************************************************/
static void tx_grmn_invalid
    (
    iop_nmea2k_pgn_t  * pgn,
    uint8               dest_addr   /* address to send to */
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t    id;
uint8           data[6];

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Data Fields:
1. Manufacturer Code (11 bits) - Proprietary Requirement
2. Reserved (2 bits) - Proprietary Requirement
3. Industry Group (3 bits) - Proprietary Requirement
4. Garmin Instrumentation ID (2 bytes)
5. Source Port (1 byte)
6. Destination Port (1 byte)
7. Data (n bytes)
----------------------------------------------------------*/
data[0] = PROPR_HEADER & 0xFF;
data[1] = PROPR_HEADER >> 8;
data[2] = IOP_INV_INST_ID & 0xFF;
data[3] = IOP_INV_INST_ID >> 8;
data[4] = IOP_GRMN_NMEA2K_RESERVED_LAST_PORT;
data[5] = IOP_GRMN_NMEA2K_RESERVED_LAST_PORT;

id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( DEFAULT_PROPR_PRIO )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( pgn->full )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

if( ( pgn->full == iop_NMEA_PROPR_SF_AD_PGN )
 || ( pgn->full == iop_NMEA_PROPR_FP_AD_PGN ) )
    {
    /*------------------------------------------------------
    Add destination to the ID field.
    ------------------------------------------------------*/
    id.ext |= IOP_NMEA2K_IDENTIFIER_PGN( (uint32)dest_addr );
    }

if( pgn->full == iop_NMEA_PROPR_SF_AD_PGN )
    {
    /*------------------------------------------------------
    Send the frame using the single-frame method.
    ------------------------------------------------------*/
    iop_nmea2k_single_frame_tx( &id, data, 6, TRUE );
    }
else
    {
    /*------------------------------------------------------
    Send the message using the fast-packet method.
    ------------------------------------------------------*/
    iop_nmea2k_fast_packet_tx( &id, data, 6 );
    }
} /* tx_grmn_invalid() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       tx_nack - Transmit Negative Acknowledgement
*
*   DESCRIPTION:
*       Transmits a NACK for a PGN that we don't support.
*
*********************************************************************/
static void tx_nack
    (
    iop_nmea2k_pgn_t  * rqstd_pgn,
    uint8               dest_addr   /* address to send the NACK to */
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t    id;
uint8           data[8];

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( DEFAULT_PRIO )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_ISO_ACK_PGN | dest_addr )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

/*----------------------------------------------------------
Data Fields:
1. Control Byte (1 byte)
2. Group Function Value (1 byte)
3. Reserved = 0xFF (3 bytes)
4. PGN of Requested Information (3 bytes)
----------------------------------------------------------*/
data[0] = iop_NMEA2K_DD177_NEG_ACK;
memset( &data[1], 0xFF, 4 );
memcpy( &data[5], (uint8 *)&rqstd_pgn->full, 3 );

/*----------------------------------------------------------
Send the frame.
----------------------------------------------------------*/
iop_nmea2k_single_frame_tx( &id, data, SINGLE_FRAME_MAX_SIZE, TRUE );
} /* tx_nack() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       tx_product_info - Transmit Product Information
*
*   DESCRIPTION:
*       Transmits the Product Information PGN.
*
*********************************************************************/
static void tx_product_info
    (
    void
    )
{
/*----------------------------------------------------------
Literal Constants
----------------------------------------------------------*/
#define PROD_INFO_MSG_SIZE          134     /* 134 bytes = 2+2+32+32+32+32+1+1 */

/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t    id;
uint8           data[PROD_INFO_MSG_SIZE];

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( DEFAULT_PRIO )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_PROD_INFO_PGN )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

/*----------------------------------------------------------
Data Fields:
1. NMEA 2000 Database Version (2 bytes)
2. NMEA Manufacturer's Product Code (2 bytes)
3. Manufacturer's Model ID (32 bytes)
4. Manufacturer's Software Version Code (32 bytes)
5. Manufacturer's Model Version (32 bytes)
6. Manufacturer's Model Serial Code (32 bytes)
7. NMEA 2000 Certification Level (1 byte)
8. Load Equivalency (1 byte)
----------------------------------------------------------*/

/*----------------------------------------------------------
Assign Product Code & Load Equivalency based on the
Adapter Type.
----------------------------------------------------------*/
uint16  prod_code;
uint8   load_eq;
switch( HWM_get_sensor_type() )
    {
    case TEMPERATURE_SENSOR:
        prod_code   = PROD_INFO_PROD_CODE_GRA10;
        load_eq     = PROD_INFO_LOAD_EQ_GRA10;
        break;

    case HEADING_SENSOR:
        prod_code   = PROD_INFO_PROD_CODE_GET10;
        load_eq     = PROD_INFO_LOAD_EQ_GET10;
        break;

    default:
        prod_code   = PROD_INFO_PROD_CODE_GRA10;
        load_eq     = PROD_INFO_LOAD_EQ_GRA10;
        UTL_assert_always( UTL_FILE_IOP_NMEA2K );
        break;
    }

data[0] = DATABASE_VRSN & 0xFF;
data[1] = DATABASE_VRSN >> 8;

data[2] = prod_code & 0xFF;
data[3] = prod_code >> 8;

memset( &data[4], 0, 128 );
GRM_get_product_string( (tchr *)&data[4] );

GRM_get_version_string( (tchr *)&data[36] );

GRM_get_model_version_string( (tchr *)&data[68] );

memcpy( &data[100], &unit_id_str, UNIT_ID_STR_SIZE );

data[132] = PROD_INFO_CERT;

data[133] = load_eq;

/*----------------------------------------------------------
Send the message using the fast-packet method.
----------------------------------------------------------*/
iop_nmea2k_fast_packet_tx( &id, data, PROD_INFO_MSG_SIZE );
} /* tx_product_info() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       tx_pgn_list - Transmit List of Recieved or Transmitted PGN's
*
*   DESCRIPTION:
*       Transmits the PGN List PGN with all PGN's that we transmit.
*
*********************************************************************/
static void tx_pgn_list
    (
    uint8               dest_addr,   /* address to send to */
    iop_nmea2k_dd145_t8 trans_or_recieve_pgn_list
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t    id;
uint8           data[ 3 * cnt_of_array(PGN_INFO_TBL) + 1 ]; /* Maximum size */
uint8           size;
uint8           i;
uint8           max_tbl_size;
iop_pgn_transmission_info_t8 pgn_info;

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( DEFAULT_PRIO )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_PGN_LIST_PGN | dest_addr )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );


/*----------------------------------------------------------
Determine maximum table size.
----------------------------------------------------------*/
max_tbl_size = PGN_INFO_TBL_TEMP_CNT;

/*----------------------------------------------------------
Data Fields:
1. Function Code (1 byte)
2. Supported PGN (3 bytes)
3. Field 2 repeated
----------------------------------------------------------*/
data[0] = (uint8)trans_or_recieve_pgn_list;

for( i = 0, size = 1; i < max_tbl_size; i++ )
    {
    pgn_info = PGN_INFO_TBL[i].pgn_transmission_info;

    if ( ((trans_or_recieve_pgn_list == iop_NMEA2K_DD145_RECEIVE) && pgn_info.rx) || ((trans_or_recieve_pgn_list == iop_NMEA2K_DD145_TRANSMIT) && pgn_info.tx))
        {
        memcpy( &(data[size]), (uint8 const *) &(PGN_INFO_TBL[i].pgn.full), 3 );
        size += 3;
        }
    }

/*----------------------------------------------------------
Send the message.
----------------------------------------------------------*/
iop_nmea2k_fast_packet_tx( &id, data, size );
} /* tx_pgn_list() */

#endif /* SYC_NMEA2K_SUPPORT */
