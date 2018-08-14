/*********************************************************************
*
*   HEADER NAME:
*       IOP_pub - IOP Public Declarations
*
*   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

#if !defined _IOP_PUB_H
#define      _IOP_PUB_H

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
//#include "HWM_pub_adc.h"
#include "IOP_pub_cmnd.h"
#include "IOP_pub_evnt.h"
#include "IOP_pub_grmn.h"
#include "IOP_pub_inst.h"
#include "HWM_pub_adc.h"
#include "hwm_temperature.h"
#include "heading.h"
#include "hwm_prv_can.h"
#include "IOP_pub_grmn_nmea2k_trans.h"
#include "SYC_pub_prj_s.h"
#include "UTL_pub_assert_prj.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/
#ifndef SYC_NMEA2K_SUPPORT
    #define SYC_NMEA2K_SUPPORT FALSE
#endif

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/
typedef struct
    {
    uint16          id;
    uint16          data;
    uint32          time;
    } IOP_evnt_data_type;

typedef struct  /* voltage data type    */
    {
    sint16  bat;
    sint16  ext;
    } IOP_volt_data_type;

typedef struct
    {
    uint16          start_of_stack;
    uint16          cstack_remaining;
    uint16          rstack_remaining;
    } IOP_stack_data_type;

typedef struct
    {
    UTL_file_id         file_id;
    uint16              line_number;
    } IOP_assert_data_type;


typedef struct
    {
    float           motor_current;
    sint16          motor_rpm;
    uint16          encoder_angle;
    } IOP_motor_info_data_type;



/*----------------------------------------------------------
Define the data that is computed by the sonar hardware and
sent to the Comm Monitor.  Note that the fields are sized
from largest to smallest to avoid alignment issues with 32
bit compilers.
----------------------------------------------------------*/
#if (SYC_SONAR_SUPPORT == TRUE)
    typedef struct
        {
        uint16 variance;
        uint8  mean;
        uint8  min;
        uint8  max;
        } IOP_dps_driver_data_type;
#endif

/*----------------------------------------------------------
Define the data that is sent by DPS in test mode.
----------------------------------------------------------*/
#if (SYC_SONAR_SUPPORT == TRUE)
    typedef struct
        {
        uint8 bias;
        uint8 dynamic_range;
        uint8 peak;
        uint8 noise;
        } IOP_dps_test_data_type;
#endif

/*--------------------------------------------------------------------
                            PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            MEMORY CONSTANTS
--------------------------------------------------------------------*/
#define IOP_NMEA2K_DFLT_ADDRESS    0

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 MACROS
--------------------------------------------------------------------*/

#if ( SYC_NMEA2K_SUPPORT == TRUE )
    #define IOP_ready()     IOP_nmea2k_ready()
#elif ( SYC_SERIAL_RX_SUPPORT == TRUE )
    #define IOP_ready()     TRUE
#endif

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
iop_main.c procedure prototypes.
----------------------------------------------------------*/
void IOP_evnt
    (
    IOP_evnt_id_type    const event_id,
    uint16              const event_data
    );

boolean IOP_hold_in_bb
    (
    void
    );

void IOP_init
    (
    void
    );

void IOP_inst
    (
    IOP_inst_id_type            const id,
    uint8               const * const data,
    uint8                       const size
    );

void IOP_inst_route
    (
    IOP_inst_id_type            const id,
    uint8               const * const data,
    uint8                       const size,
    IOP_route_type            * const route
    );

void IOP_main_tsk
    (
    void
    );

void IOP_printf
    (
    tchr                const * const string_data
    );

void IOP_pwrp
    (
    void
    );

void IOP_send_capabilities
    (
    void
    );

/*----------------------------------------------------------
IOP_nmea2k.c prototypes
----------------------------------------------------------*/
boolean IOP_nmea2k_ready
    (
    void
    );

/*----------------------------------------------------------
IOP_util.c procedure prototypes.
----------------------------------------------------------*/
void IOP_tx_assert_data
    (
    void
    );

void IOP_tx_screen
    (
    void
    );

void IOP_tx_stack_data
    (
    void
    );

#endif  /* _IOP_PUB_H */
