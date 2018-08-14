/*********************************************************************
*
*   HEADER NAME:
*       HWM_pub.h - Hardware Manager Public Declarations
*
*   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

#ifndef HWM_PUB_H_
#define HWM_PUB_H_

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "ccan_rom.h"


/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
CAN Identifier - Rev A uses 'standard', Rev B uses 'extended'
----------------------------------------------------------*/
typedef union
    {
    uint32              ext;            /* Extended identifier */
    uint16              std;            /* Standard identifier */
    uint8               tab[4];         /* Table to access each byte */
    } HWM_can_id_t;

/*----------------------------------------------------------
CAN Callback Function
----------------------------------------------------------*/
typedef void (*HWM_can_rx_clbk_type)
    (
    HWM_can_id_t    const * id,
    uint8                 * data,
    uint8                   data_len
    );

/*--------------------------------------------------------------------
                            PROJECT INCLUDES
--------------------------------------------------------------------*/

#include "SYC_pub_prj_s.h"

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
HWM_can.c procedures
----------------------------------------------------------*/

boolean HWM_can_tx_error
    (
    boolean * error
    );

void HWM_can_listen_for_ext
    (
    uint32          const * identifier, /* CAN Extended ID field */
    uint32          const * mask,       /* CAN Extended ID Mask */
    HWM_can_rx_clbk_type    clbk        /* Callback function on match */
    );

void HWM_can_tsk
    (
    void
    );

void HWM_rx_can
    (
    CCAN_MSG_OBJ_T    * msg_obj
    );

void HWM_tx_can_ext
    (
    HWM_can_id_t    const * identifier, /* CAN Extended ID field */
    uint8           const * data,       /* Payload */
    uint8           const   size        /* Size of data */
    );

uint8 HWM_get_random_nmbr
    (
    void
    );

void hwm_timer_pwrp
    (
    void
    );

void hwm_timer_init
    (
    void
    );

#endif /* HWM_PUB_H_ */
