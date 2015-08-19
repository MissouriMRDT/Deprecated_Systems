/*********************************************************************
*
*   MODULE NAME:
*
*       hwm_can.c - Hardware Manager Can Interface
*
*   DESCRIPTION:
*       Defines interface for the CAN hardware to set up and TX/RX can
*       messages.
*
* Copyright 2006-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "UTL_pub.h"
#include "SYC_pub_prj_s.h"
#include "string.h"

/*----------------------------------------------------------
Compile out this file if no CAN support.
----------------------------------------------------------*/

#include "hwm_prv_can.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

#define RX_MOB 2

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

static CCAN_MSG_OBJ_T         rx_queue[hwm_CAN_RX_QUEUE_SZ]; /* asm import */

static hwm_can_tx_t           tx_queue[hwm_CAN_TX_QUEUE_SZ];


static uint8                  rx_head;
static uint8                  rx_tail;                         /* asm import */

static HWM_can_rx_clbk_type   rx_funcs[ hwm_CAN_NMBR_RX_MOBS ];

static uint8                  tx_head;
static uint8                  tx_tail;

static hwm_can_mob_id_t       next_xmit_mob_id;

hwm_can_bus_status_t8   hwm_can_tx_status;

uint8   mob_free[NUM_MOB];

unsigned int tx_count = 0;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

static hwm_can_mob_id_t can_find_free_mob
    (
    hwm_can_mob_id_t    start_mob_num
    );

static boolean can_all_mob_tx_finished
    (
    void
    );

static boolean can_MOb_transmit
    (
    hwm_can_mob_t * mob
    );

static void proc_can_rx
    (
    void
    );

static void proc_can_tx
    (
    void
    );

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_can_tx_error - Get Transmit Error Status
*
*   DESCRIPTION:
*       Passes back if there was an error or not with the last
*       transmission. Returns False until the status of the first
*       transmitted packet is known.
*
*   NOTE: The application should not assume that the error occurred
*       with any specific frame. If it needs that information, the
*       driver needs to be rewritten to have individual statuses or
*       callbacks for each transmitted frame.
*
*********************************************************************/
boolean HWM_can_tx_error
    (
    boolean * error         /* True if last tx resulted in error */
    )
{
*error = ( hwm_can_tx_status != hwm_CAN_BUS_TX_OK );

return( hwm_can_tx_status != hwm_CAN_BUS_PWRP );

} /* HWM_can_tx_error() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_can_listen_for_ext - Listen for CAN Extended Frame
*
*   DESCRIPTION:
*       This routine sets up a MOb to listen for messages that
*       match the given filter in an extended frame. The callback
*       function will be called with the data on a match.
*
*       If mask is 0 and callback is NULL, this function will
*       set the last MOb to receive and discard any packets it hears.
*
*********************************************************************/
void HWM_can_listen_for_ext
    (
    uint32          const * identifier, /* CAN Extended ID field */
    uint32          const * mask,       /* CAN Extended ID Mask */
    HWM_can_rx_clbk_type    clbk        /* Callback function on match */
    )
{
/*----------------------------------------------------------
Local Variables
----------------------------------------------------------*/
CCAN_MSG_OBJ_T      msg_obj;
hwm_can_mob_id_t    mob_id;

if( (*mask == 0) && (clbk == NULL) )
    {
    /*------------------------------------------------------
    Special case. Use the last MOb.
    ------------------------------------------------------*/
    mob_id = NUM_MOB - 1;
    }

else
    {
    /*------------------------------------------------------
    Try to find a free MOb
    ------------------------------------------------------*/
    mob_id = can_find_free_mob( MOB_0 );
    }

if( mob_id != MOB_INV )
    {
    /*------------------------------------------------------
    Set up the MOb for RX
    ------------------------------------------------------*/
    mob_free[mob_id] = RX_MOB;

    #if(hwm_CAN_EXT_DATA_FRAME_ONLY != TRUE)
        switch(CFG_USE_EXTENDED | CFG_RTR_DATA)
            {
            case (CFG_USE_STANDARD | CFG_RTR_DATA):
                msg_obj.msgobj = mob_id;
                msg_obj.mode_id = (*identifier | CAN_MSGOBJ_STD | CAN_MSGOBJ_DAT);
                msg_obj.mask = *mask;
                break;

            case (CFG_USE_EXTENDED | CFG_RTR_DATA):
    #endif
                msg_obj.msgobj = mob_id;
                msg_obj.mode_id = (*identifier | CAN_MSGOBJ_EXT | CAN_MSGOBJ_DAT);
                msg_obj.mask = *mask;
    #if(hwm_CAN_EXT_DATA_FRAME_ONLY != TRUE)
                break;

            case (CFG_USE_STANDARD | CFG_RTR_REMOTE_FRAME):
                msg_obj.msgobj = mob_id;
                msg_obj.mode_id = (*identifier | CAN_MSGOBJ_STD | CAN_MSGOBJ_RTR);
                msg_obj.mask = *mask;
                break;

            case (CFG_USE_EXTENDED | CFG_RTR_REMOTE_FRAME):
                msg_obj.msgobj = mob_id;
                msg_obj.mode_id = (*identifier | CAN_MSGOBJ_EXT | CAN_MSGOBJ_RTR);
                msg_obj.mask = *mask;
                break;
            }
    #endif

    if( clbk != NULL )
        {
        /*--------------------------------------------------
        Register the callback for this MOb
        --------------------------------------------------*/
        UTL_assert( mob_id < hwm_CAN_NMBR_RX_MOBS, UTL_FILE_HWM_CAN );
        rx_funcs[ mob_id ] = clbk;
        }

    LPC_CCAN_API->config_rxmsgobj(&msg_obj);
    }

} /* HWM_can_listen_for_ext() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_can_tsk - CAN Main Task
*
*   DESCRIPTION:
*       Processes CAN messages the CAN ISR has placed in the queue,
*       and also processes messages that need to be sent.
*
*********************************************************************/
void HWM_can_tsk
    (
    void
    )
{
proc_can_rx();
proc_can_tx();

} /* HWM_can_tsk() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_rx_can - Receive CAN Frame
*
*   DESCRIPTION:
*       This routine takes the data received over CAN and pushes
*       them onto the RX queue.
*
*********************************************************************/
void HWM_rx_can
    (
    CCAN_MSG_OBJ_T    * msg_obj /* CAN Message Object */
    )
{

/*----------------------------------------------------------
Add message to receive queue.
----------------------------------------------------------*/
rx_queue[ rx_tail ] = *msg_obj;

rx_tail++;
rx_tail %= hwm_CAN_RX_QUEUE_SZ;
} /* HWM_rx_can() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_tx_can_ext - Transmit CAN Extended Frame
*
*   DESCRIPTION:
*       This routine sets up the given message in an extended frame
*       for transmit over CAN.
*
*********************************************************************/
void HWM_tx_can_ext
    (
    HWM_can_id_t    const * identifier, /* CAN Extended ID field */
    uint8           const * data,       /* Payload */
    uint8           const   size        /* Size of data */
    )
{
/*----------------------------------------------------------
Add message to transmit queue.
----------------------------------------------------------*/
tx_queue[ tx_tail ].ident = *identifier;
tx_queue[ tx_tail ].dlc   = size;
memcpy( &tx_queue[ tx_tail ].data, data, size );

tx_tail++;
tx_tail %= hwm_CAN_TX_QUEUE_SZ;

/*----------------------------------------------------------
Make sure the queue hasn't wrapped.
----------------------------------------------------------*/
UTL_assert( tx_tail != tx_head, UTL_FILE_HWM_CAN );
} /* HWM_tx_can_ext() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       hwm_can_init - Hardware Level CAN Init
*
*   DESCRIPTION:
*       Initializes CAN hardware and driver.
*
*********************************************************************/
void hwm_can_init
    (
    void
    )
{

ccan_rom_init();

} /* hwm_can_init() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       hwm_can_pwrdwn - Hardware Level CAN Powerdown
*
*   DESCRIPTION:
*       Handles power down of CAN controller.
*
*   NOTES:
*       1. This function will block until the flush is complete.
*       2. Calling this will not guarantee that the packets are
*          all sent out, only that they are queued in the hardware
*          CAN controller.
*
*********************************************************************/
void hwm_can_pwrdwn
    (
    void
    )
{
/*----------------------------------------------------------
Flush CAN transmit buffer.
----------------------------------------------------------*/
while( tx_head != tx_tail )
    {
    proc_can_tx();
    }

/* wait here until all MOb's have been transmitted. */
while(can_all_mob_tx_finished() == FALSE);

} /* hwm_can_pwrdwn() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       hwm_can_pwrp - Hardware Level CAN powerup
*
*   DESCRIPTION:
*       Handles powerup of CAN hardware.
*
*********************************************************************/
void hwm_can_pwrp
    (
    void
    )
{
/*----------------------------------------------------------
Perform any project-specific powerup.
----------------------------------------------------------*/
memset( &rx_queue, 0, sizeof( rx_queue ) );
memset( &tx_queue, 0, sizeof( tx_queue ) );
rx_head = 0;
rx_tail = 0;
tx_head = 0;
tx_tail = 0;

next_xmit_mob_id = 0;

memset( &mob_free, TRUE, sizeof( mob_free ) );

hwm_can_tx_status  = hwm_CAN_BUS_PWRP;

} /* hwm_can_pwrp() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       can_find_free_mob - CAN Find Free MOb
*
*   DESCRIPTION:
*       This function returns the number of the first MOb available or
*       MOB_INV if no MOb is available.
*
*********************************************************************/
static hwm_can_mob_id_t can_find_free_mob
    (
    hwm_can_mob_id_t    start_mob_num
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
hwm_can_mob_id_t    mob_number;

//for( mob_number = start_mob_num; mob_number < NUM_MOB; mob_number++ )
//    {
//        if( mob_free[mob_number] == TRUE )
//            {
//            /*--------------------------------------------------
//            Unused (disabled) MOb found.
//            --------------------------------------------------*/
//            return( mob_number );
//            }
//    }
uint32 mob_tx_reg1 = LPC_CAN->TXREQ1;
uint32 mob_tx_reg2 = LPC_CAN->TXREQ2;

for( mob_number = start_mob_num; mob_number < NUM_MOB; mob_number++ )
    {
    if( mob_free[mob_number] != RX_MOB )
        {
        if(mob_number < 16)
            {
            if( 0 == ( ( ( mob_tx_reg1 ) >> mob_number ) & 1 ) )
                {
                /*--------------------------------------------------
                Free MOb found.
                --------------------------------------------------*/
                return( mob_number );
                }
            }
        else
            {
            if( 0 == ( ( ( mob_tx_reg2 ) >> ( mob_number - 16 ) ) & 1 ) )
                {
                /*--------------------------------------------------
                Free pending MOb found.
                --------------------------------------------------*/
                return( mob_number );
                }
            }
        }
    }

return( MOB_INV );
}  /*can_find_free_mob()*/

/*********************************************************************
*
*   PROCEDURE NAME:
*       can_all_mob_tx_finished - CAN determine if all MOb tx are done
*
*   DESCRIPTION:
*       This function returns true if all MOb's that have been set
*        to transmit are done, otherwise it returns false
*
*********************************************************************/
static boolean can_all_mob_tx_finished
    (
    void
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
hwm_can_mob_id_t    mob_number;

for( mob_number = MOB_0; mob_number < NUM_MOB; mob_number++ )
    {
    if(mob_number < 16)
        {
        if( 0 != ( ( ( LPC_CAN->TXREQ1 ) >> mob_number ) & 1 ) )
            {
            /*--------------------------------------------------
            Transmission pending MOb found.
            --------------------------------------------------*/
            return( FALSE );
            }
        }
    else
        {
        if( 0 != ( ( ( LPC_CAN->TXREQ2 ) >> ( mob_number - 16 ) ) & 1 ) )
            {
            /*--------------------------------------------------
            Transmission pending MOb found.
            --------------------------------------------------*/
            return( FALSE );
            }
        }
    }


return( TRUE );
} /* can_all_mob_tx_finished() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       can_MOb_transmit - MOb Transmit
*
*   DESCRIPTION:
*       This routine finds a free MOb slot and sets it up to transmit
*       the message as described by the 'mob' parameter. Returns FALSE
*       if there was not a free MOb.
*
*********************************************************************/
static boolean can_MOb_transmit
    (
    hwm_can_mob_t * mob
    )
{
/*----------------------------------------------------------
Local Variables
----------------------------------------------------------*/
CCAN_MSG_OBJ_T      msg_obj;
hwm_can_mob_id_t    mob_id;
uint8               i;

/*----------------------------------------------------------
Try to find a free MOb starting the with next xmit index.
----------------------------------------------------------*/
mob_id = can_find_free_mob( next_xmit_mob_id );

if( mob_id == MOB_INV )
    {
    /*------------------------------------------------------
    No free MOb found.
    ------------------------------------------------------*/
    return( FALSE );
    }

/*----------------------------------------------------------
Determine if all msg objs above the current msg obj selected
are finished transmitting.

Without doing this, frames from the queue can be sent out
of order. See the following situation:
[Time 1] TX Queue: ABCDEF    MOB's: xxxx     Sent:
[Time 2] TX Queue: EF        MOB's: ABCD     Sent:
[Time 3] TX Queue: EF        MOB's: xxCD     Sent: AB
[Time 4] TX Queue:           MOB's: EFCD     Sent: AB
[Time 5] TX Queue:           MOB's: xxxx     Sent: ABEFCD
----------------------------------------------------------*/

if( mob_id >= 16 )
    {
    if( ( LPC_CAN->TXREQ2 & ( 0xFFFF << ( mob_id - 16 ) ) ) > ( 1 << ( mob_id - 16 ) ) )
        {
        /*------------------------------------------------------
        transmit pending MOb found.
        ------------------------------------------------------*/
        return( FALSE );
        }
    }
else
    {
    if( ( LPC_CAN->TXREQ1 & ( 0xFFFF << mob_id ) ) > ( 1 << mob_id ) )
        {
        /*------------------------------------------------------
        transmit pending MOb found.
        ------------------------------------------------------*/
        return( FALSE );
        }
    else if( LPC_CAN->TXREQ2 != 0 )
        {
        /*------------------------------------------------------
        transmit pending MOb found.
        ------------------------------------------------------*/
        return( FALSE );
        }
    }

mob_free[mob_id] = FALSE;
tx_count++;

/*----------------------------------------------------------
Save the ID.
----------------------------------------------------------*/
next_xmit_mob_id = mob_id + 1;
next_xmit_mob_id %= NUM_MOB;

/*----------------------------------------------------------
Set up the MOb for transmit
----------------------------------------------------------*/
#if(hwm_CAN_EXT_DATA_FRAME_ONLY != TRUE)
    switch( mob->cfg )
        {
        case (CFG_USE_STANDARD | CFG_RTR_DATA):
            msg_obj.msgobj = mob_id;
            msg_obj.mode_id = ( mob->ident.std | CAN_MSGOBJ_STD | CAN_MSGOBJ_DAT );
            msg_obj.mask = mob->ident_msk.std;
            msg_obj.dlc =  mob->dlc;
            for( i = 0; i < mob->dlc; i++ )
                {
                msg_obj.data[i] = mob->data[i];
                }
            break;

        case (CFG_USE_EXTENDED | CFG_RTR_DATA):
#endif
            msg_obj.msgobj = mob_id;
            msg_obj.mode_id = ( mob->ident.ext | CAN_MSGOBJ_EXT | CAN_MSGOBJ_DAT );
            msg_obj.mask = mob->ident_msk.ext;
            msg_obj.dlc =  mob->dlc;
            for( i = 0; i < mob->dlc; i++ )
                {
                msg_obj.data[i] = mob->data[i];
                }

#if(hwm_CAN_EXT_DATA_FRAME_ONLY != TRUE)
            break;

        case (CFG_USE_STANDARD | CFG_RTR_REMOTE_FRAME):
            msg_obj.msgobj = mob_id;
            msg_obj.mode_id = ( mob->ident.std | CAN_MSGOBJ_STD | CAN_MSGOBJ_RTR );
            msg_obj.mask = mob->ident_msk.std;
            msg_obj.dlc =  mob->dlc;
            for( i = 0; i < mob->dlc; i++ )
                {
                msg_obj.data[i] = mob->data[i];
                }
            break;

        case (CFG_USE_EXTENDED | CFG_RTR_REMOTE_FRAME):
            msg_obj.msgobj = mob_id;
            msg_obj.mode_id = ( mob->ident.ext | CAN_MSGOBJ_EXT | CAN_MSGOBJ_RTR );
            msg_obj.mask = mob->ident_msk.ext;
            msg_obj.dlc =  mob->dlc;
            for( i = 0; i < mob->dlc; i++ )
                {
                msg_obj.data[i] = mob->data[i];
                }
            break;
        }
#endif

LPC_CCAN_API->can_transmit(&msg_obj);

return( TRUE );
} /* can_MOb_transmit() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       proc_can_rx - Process CAN Rx
*
*   DESCRIPTION:
*       This handler is responsible for taking the relevant data from
*       the RX queue and passing it along to the proper registered callback
*       for handling.
*
*********************************************************************/
static void proc_can_rx
    (
    void
    )
{
/*----------------------------------------------------------
Local Variables
----------------------------------------------------------*/
hwm_can_mob_id_t    mob_id;
HWM_can_id_t      	ident;
CCAN_MSG_OBJ_T      * rx_head_ptr;
uint8               data_len;
uint8               data_buf[ 8 ];

/*----------------------------------------------------------
Process one message at a time, because each one might
require a response to be sent out.
----------------------------------------------------------*/
if( rx_head != rx_tail )
    {
    rx_head_ptr = &rx_queue[rx_head];

    mob_id   = rx_head_ptr->msgobj;
    data_len = rx_head_ptr->dlc;
    memcpy( &data_buf, rx_head_ptr->data, data_len );

    #if(hwm_CAN_EXT_DATA_FRAME_ONLY == TRUE)
        {
        //UTL_assert( rx_head_ptr->extended == TRUE, UTL_FILE_HWM_CAN );
        ident.ext = rx_head_ptr->mode_id;
        }
    #else
        {
        ident.std = rx_head_ptr->mode_id;
        }
    #endif


    /*------------------------------------------------------
    Move to the next rx msg
    ------------------------------------------------------*/
    rx_head++;
    rx_head %= hwm_CAN_RX_QUEUE_SZ;


    /*------------------------------------------------------
    Use the registered callback to handle the data
    ------------------------------------------------------*/
    UTL_assert( mob_id < hwm_CAN_NMBR_RX_MOBS, UTL_FILE_HWM_CAN );
    (*rx_funcs[mob_id])( &ident, data_buf, data_len );
    }

} /* proc_can_rx() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       proc_can_tx - Process CAN Tx
*
*   DESCRIPTION:
*       This routine takes messages ready for transmit from the TX queue
*       and sets them up for transmit.
*
*********************************************************************/
static void proc_can_tx
    (
    void
    )
{
/*----------------------------------------------------------
Local Variables
----------------------------------------------------------*/
hwm_can_mob_t   mob_setup;

/*----------------------------------------------------------
Process all messages now because this only involves copying
to the CAN registers.
----------------------------------------------------------*/
while( tx_head != tx_tail )
    {
    /*------------------------------------------------------
    Set up the message
    ------------------------------------------------------*/
    memset( &mob_setup, 0, sizeof( hwm_can_mob_t ) );
    mob_setup.cfg   = (CFG_USE_EXTENDED | CFG_RTR_DATA);
    mob_setup.ident = tx_queue[tx_head].ident;
    mob_setup.dlc   = tx_queue[tx_head].dlc;
    mob_setup.data  = tx_queue[tx_head].data;

    if( can_MOb_transmit( &mob_setup ) == FALSE )
        {
        /*--------------------------------------------------
        Hardware buffers are full. Stop trying for now.
        --------------------------------------------------*/
        break;
        }

    /*------------------------------------------------------
    Increment the head if sending was successful.
    ------------------------------------------------------*/
    tx_head++;
    tx_head %= hwm_CAN_TX_QUEUE_SZ;
    }

} /* proc_can_tx() */
