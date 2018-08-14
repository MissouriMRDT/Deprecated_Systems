/*********************************************************************
*
*   HEADER NAME:
*       hwm_prv_can_prj.h - Project-specific Private declarations for
*                           AT90CANxxx CAN driver
*
* Copyright 2006-2007 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/
#if !defined _HWM_PRV_CAN_PRJ_H
#define _HWM_PRV_CAN_PRJ_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "HWM_pub.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
NMEA 2000 Bit Timings
Baud Rate = 250 Kbps (required value)
TQ = 250 ns
Sample Point = 1 - ( PHS2 / ( 1 + PRS + PHS1 + PHS2 ) )
             = 1 - ( 2 / ( 1 + 7 + 6 + 2 ) )
             = 87.5% (between 85% and 90% required)
----------------------------------------------------------*/
#define CONF_CANBT1_NMEA2K      ( hwm_CANBT1_BRP(3) )
#define CONF_CANBT2_NMEA2K      ( hwm_CANBT2_SJW(1) | \
                                  hwm_CANBT2_PRS(7) )
#define CONF_CANBT3_NMEA2K      ( hwm_CANBT3_PHS1(6) | \
                                  hwm_CANBT3_PHS2(2) | \
                                  hwm_CANBT3_SMP_THRICE )

/*----------------------------------------------------------
The above clock values are based on Fclkio = 12 MHz.
----------------------------------------------------------*/
//UTL_compiler_assert( hwm_CLK_SPEED == 12000000L, HWM_PRV_CAN_PRJ );


/*----------------------------------------------------------
Set this to true if this project only sends using Extended
Data CAN frames to compile out support for Standard and
Remote frames.
----------------------------------------------------------*/
#define hwm_CAN_EXT_DATA_FRAME_ONLY     TRUE

#define hwm_CAN_NMBR_RX_MOBS            1

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

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
CANet needs to turn on power supplied to the tranciever.
NMEA2k supplies power from the bus.
----------------------------------------------------------*/
#define hwm_can_pwrp_prj()

/*----------------------------------------------------------
CAN Bit Timing Registers - CANBT1, CANBT2, CANBT3
----------------------------------------------------------*/
#define hwm_can_set_bit_timing_nmea2k() { hwm_io_canbt1 = CONF_CANBT1_NMEA2K; hwm_io_canbt2 = CONF_CANBT2_NMEA2K; hwm_io_canbt3 = CONF_CANBT3_NMEA2K; }

#define hwm_can_set_bit_timing_prj()    hwm_can_set_bit_timing_nmea2k()

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

#endif /* HWM_PRV_CAN_PRJ_H */
