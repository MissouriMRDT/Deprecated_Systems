/*********************************************************************
*
*   HEADER NAME:
*       hwm_pub_xfer.h - Hardware manager transfer header
*
* Copyright 2007 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/


#if !defined _HWM_PUB_XFER_H
#define _HWM_PUB_XFER_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "HWM_pub_rgn_defn.h"
#include "IOP_pub_grmn.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/
typedef enum
    {
    HWM_XFER_NONE,                  /* no upload (default power up)                   */
    HWM_XFER_RGN_VIA_BB,            /* xfer to bb which then xfers to sys_code region */
    HWM_XFER_NET_UPDATE             /* xfer to bb which then waits until transferred out of net update. */
    }  HWM_xfer_mode_type;

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/
//#include "hwm_prv_rgn_prj.h"

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/
#if(FALSE) /*might need later*/
extern HWM_xfer_mode_type   HWM_xfer_mode;
extern HWM_data_rgn_type    HWM_xfer_data;
extern uint8                HWM_xfer_route_address;
extern IOP_grmn_port_type   HWM_xfer_route_source_port;
extern IOP_grmn_port_type   HWM_xfer_route_dest_port;
#endif
extern uint8                HWM_xfer_my_nmea2k_address;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
HWM_xfer.s procedures
----------------------------------------------------------*/
#if(FALSE) /*might need later*/
void HWM_xfer_bb
    (
    HWM_xfer_mode_type mode,
    HWM_data_rgn_type  rgn,
    uint8              src_addr,
    IOP_grmn_port_type source_port,
    IOP_grmn_port_type dest_port,
    uint8              nmea2k_address
    );

void HWM_xfer_sys
    (
    void
    );
#endif

#endif /* HWM_PUB_XFER_H */
