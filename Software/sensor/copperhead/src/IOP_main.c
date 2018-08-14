/*********************************************************************
 *
 *   MODULE NAME:
 *       IOP_main.c - Input/Output Processing
 *
 *   DESCRIPTION:
 *       Input/Output Processing Module
 *
 *   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
 *********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub_product_info.h"
#include "HWM_pub.h"
//#include "HWM_pub_generic_adapter.h"
#include "HWM_pub_xfer.h"
//#include "HWM_pub_rgn.h"
#include "IOP_pub.h"
#include "IOP_pub_snsr.h"
#if ( SYC_NVM_SUPPORT == TRUE )
#include "NVM_pub.h"
#endif
#include "SNS_pub_n2k_capabilities.h"
#include "SYC_pub.h"
#include "UTL_pub.h"
#include "iop_prv.h"
#include "iop_prv_nmea2k.h"
#include "iop_prv_nmea2k_inst.h"
#include "IOP_prv_nmea2k_prj.h"
#include <stdlib.h>

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

static void process_command
    (
    uint8 const * const data,
    uint8 const data_size,
    IOP_route_type * const route
    );

static void process_gnrc_cnfg
    (
    char   const * const data,
    uint8   const size
    );

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_evnt - Transmit Event Data
 *
 *   DESCRIPTION:
 *       This procedure transmits event data using the GARMIN protocol.
 *
 *********************************************************************/
void IOP_evnt
    (
    IOP_evnt_id_type const event_id,
    uint16 const event_data
    )
{

/*----------------------------------------------------------
 Local Variables
 ----------------------------------------------------------*/
IOP_evnt_data_type event;

/*----------------------------------------------------------
 Transmit the event.
 ----------------------------------------------------------*/
event.id = event_id;
event.data = event_data;
event.time = 0;

IOP_inst( IOP_EVNT_DATA, ( uint8 const * )&event, sizeof( event ) );

} /* IOP_evnt() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_init - Init for IOP Module
 *
 *   DESCRIPTION:
 *       This procedure initializes the IOP module.
 *
 *********************************************************************/

void IOP_init
    (
    void
    )
{

#if ( _SYSBLD == _ON )

//    iop_nmea2k_inst_init();

#endif

    iop_nmea2k_rx_init();
    IOP_nmea2k_init_prj();

} /* IOP_init() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_inst - Transmit Instrumentation Data
 *
 *   DESCRIPTION:
 *       This procedure transmits instrumentation data using the
 *       GARMIN protocol to/from the default Garmin port.
 *
 *********************************************************************/

void IOP_inst
(
    IOP_inst_id_type const id,
    uint8 const * const data,
    uint8 const size
)
{
/*----------------------------------------------------------
 Local variables
 ----------------------------------------------------------*/
IOP_route_type route;

#if( SYC_NMEA2K_SUPPORT == TRUE )

route.source_addr = IOP_NMEA2K_GLOBAL_ADDRESS;

#endif

route.source_port = IOP_GRMN_NMEA2K_GARMIN_APP_PORT;
route.dest_port = IOP_GRMN_NMEA2K_GARMIN_APP_PORT;

/*----------------------------------------------------------
 Transmit the garmin packet.
 ----------------------------------------------------------*/
iop_grmn_tx( id, data, size, &route );
} /* IOP_inst() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_inst_route - Transmit Instrumentation Data w/Route
 *
 *   DESCRIPTION:
 *       This procedure transmits instrumentation data using the
 *       GARMIN protocol to/from the specified ports and address.
 *
 *********************************************************************/

void IOP_inst_route
    (
    IOP_inst_id_type const id,
    uint8 const * const data,
    uint8 const size,
    IOP_route_type * const route
    )
{
/*----------------------------------------------------------
 Transmit the garmin packet.
 ----------------------------------------------------------*/
iop_grmn_tx( id, data, size, route );
} /* IOP_inst() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_main_tsk - IOP Main Thread
 *
 *   DESCRIPTION:
 *       This procedure is the main thread for IOP task.
 *
 *********************************************************************/

void IOP_main_tsk
    (
    void
    )
{
    iop_nmea2k_tsk();

} /* IOP_main_tsk() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_printf - Standard Output
 *
 *   DESCRIPTION:
 *       This procedure transmits a given string.  This procedure
 *       differs from the shared IOP_printf in that it does not do
 *       string formatting.  It simply takes a string and transmits it.
 *
 *********************************************************************/
#if(FALSE) /*Future work*/
#if ( _RELBLD == _OFF )
void IOP_printf
    (
    tchr const * const string_data
    )
{
IOP_inst( IOP_CONSOLE_DATA, ( uint8 const * )string_data, UTL_strlen( string_data ) + 1 );
} /* IOP_printf() */
#endif  /* _RELBLD */
#endif
/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_pwrp - Powerup for IOP Module
 *
 *   DESCRIPTION:
 *       This procedure initializes the IOP module.
 *
 *********************************************************************/

void IOP_pwrp
    (
    void
    )
{

    iop_pwrp_nmea2k();

} /* IOP_pwrp() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       IOP_send_capabilities - IOP Send Capabilities
 *
 *   DESCRIPTION:
 *       Sends out the sensor capabilities packet. Called when
 *       requested or if capabilities change.
 *
 *********************************************************************/
#if ( _SYSBLD == _ON )
void IOP_send_capabilities
    (
    void
    )
{
/*----------------------------------------------------------
 Local variables
 ----------------------------------------------------------*/
SNS_n2k_capabilities_type cap;
IOP_route_type route;

/*----------------------------------------------------------
 Enable Generic Support.
 ----------------------------------------------------------*/
cap = SNS_N2K_GENERIC_SUPPORT;

/*----------------------------------------------------------
 Set capabilities dependant upon Adapter type.
 ----------------------------------------------------------*/
switch ( HWM_get_sensor_type() )
    {
    /*------------------------------------------------------
     Adapters dedicated to a single task: Always output
     capabilites.
     ------------------------------------------------------*/
    case TEMPERATURE_SENSOR:
        cap |= SNS_N2K_TEMP_SRC_SUPPORT;
        break;

    case HEADING_SENSOR:
//        cap |= SNS_N2K_ENGN_TILT_SUPPORT;
        break;

    default:
        UTL_assert_always(UTL_FILE_IOP_MAIN);
        break;
    }

    /*------------------------------------------------------
     Output the Needs Calibration bit whenever adapter not
     calibrated.
     NOTE: Used to also require that the sensor was detected,
     but can no longer detect if sensor detected because
     resistive type sensors default to generic voltage line
     (0V-5V) whenever resistive sensor not detected.
     ------------------------------------------------------*/

    if( NVM_read_nonvol( HWM_cal_state ) <= HWM_STATE_CAL_PARTIAL )
        {
        switch( HWM_get_sensor_type() )
            {
            /*------------------------------------------------------
             Adapters dedicated to a single task: Output bit whenever
             the device is not calibrated.
             ------------------------------------------------------*/
            case TEMPERATURE_SENSOR:
                break;
            case HEADING_SENSOR:
                cap |= SNS_N2K_NEEDS_CALIBRATION;
                break;

            default:
                UTL_assert_always( UTL_FILE_IOP_MAIN );
                break;
            }
        }

/*----------------------------------------------------------
 Always send this packet out as broadcast to avoid duplicate
 requests.
 ----------------------------------------------------------*/
route.source_addr = IOP_NMEA2K_GLOBAL_ADDRESS;
route.source_port = IOP_GRMN_NMEA2K_SENSOR_PORT;
route.dest_port = IOP_GRMN_NMEA2K_SENSOR_PORT;

/*----------------------------------------------------------
 Send capabilities packet.
 ----------------------------------------------------------*/
IOP_inst_route( IOP_MRN_SNSR_CAPABILITIES, (uint8 *) &cap,
        sizeof(SNS_n2k_capabilities_type), &route );
} /* IOP_send_capabilities() */
#endif /* ( _SYSBLD == _ON ) */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       iop_grmn_proc_input - Process Received Packet
 *
 *   DESCRIPTION:
 *       This procedure handles received packets. Returns if the
 *       id was used or not. If just_test is true, only the id is
 *       used and no action will be taken.
 *
 *********************************************************************/

boolean iop_grmn_proc_input
   (
    IOP_inst_id_type const id,
    uint8 const * const data,
    uint8 const size,
    IOP_route_type * const route,
    boolean const just_test /* If TRUE, no action will be taken */
    )
{
/*----------------------------------------------------------
 Local variables
 ----------------------------------------------------------*/
boolean ret; /* return value */

/*----------------------------------------------------------
 Initialize
 ----------------------------------------------------------*/
ret = FALSE;

/*----------------------------------------------------------
 Handle general packet ID's.
 ----------------------------------------------------------*/
if ( id == IOP_CMND_DATA )
    {
    if ( !just_test )
        {
        process_command( data, size, route );
        }
    ret = TRUE;
    }

else if ( id == IOP_RQST_DATA )
    {
    if ( !just_test )
        {
        /*----------------------------------------------
         Taiwan requested sending an ACK to this.
         ----------------------------------------------*/
        IOP_inst_route( IOP_ACK_BYTE, (uint8 *) &id, sizeof(id), route );
        }
    ret = TRUE;
    }

else if ( (id == IOP_PRODUCT_RQST) || (id == IOP_PRODUCT_RQST_EXTEND) )
    {
    if ( !just_test )
        {
        tchr sw_build_desc[GRM_BUILD_DESCRIPTION_SIZE];

        GRM_get_build_description( sw_build_desc );
        IOP_inst_route( IOP_PRODUCT_DATA, (uint8 const *) sw_build_desc,
        GRM_BUILD_DESCRIPTION_SIZE, route );
        }
    ret = TRUE;
    }

#if(FALSE) /*Future Garmin proprietary packet work*/
else if( id == IOP_SYC_MODE_DATA )
    {
    if( !just_test )
        {
        SYC_init( *( SYC_mode_t8 * )data ); /* Set Operating Modes: Normal Mode=1, Test Mode=3 */
        }
    ret = TRUE;
    }
#endif

#if ( SYC_NVM_SUPPORT == TRUE )
else if( id == IOP_UNIT_ID_DATA )
    {
    if( !just_test )
        {
        NVM_write_nonvol( syc_unit_id, *( uint32 * )data );

        /*--------------------------------------------------
        Restart the unit
        --------------------------------------------------*/
        //SYC_pwrdwn();
        iop_pwrp_nmea2k();
        }
    ret = TRUE;
    }
#endif

#if(FALSE) /*Future Garmin proprietary packet work*/
#if ( _SYSBLD == _ON )
else if(
         (id == IOP_MRN_SNSR_RUDDER_ANGLE_TEST_START)
      || (id == IOP_MRN_SNSR_RUDDER_ANGLE_GAUGE_TYPE_SET)
      || (id == IOP_MRN_SNSR_RUDDER_ANGLE_SENSOR_TYPE_SET)
      || (id == IOP_MRN_SNSR_RUDDER_MULTI_CAL)

      || (id == IOP_MRN_SNSR_ENGINE_TILT_TEST_START)
      || (id == IOP_MRN_SNSR_ENGINE_TILT_GAUGE_TYPE_SET)
      || (id == IOP_MRN_SNSR_ENGINE_TILT_SENSOR_TYPE_SET)
      || (id == IOP_MNR_SNSR_ENGINE_TILT_MULTI_CAL)

      || (id == IOP_MRN_SNSR_FUEL_LVL_TEST_START)
      || (id == IOP_MRN_SNSR_FUEL_LVL_CAL_INIT)
      || (id == IOP_MRN_SNSR_FUEL_LVL_MULTI_CAL)
      || (id == IOP_MRN_SNSR_FUEL_SNSR_GAUGE_TYPE_SET)
      || (id == IOP_MRN_SNSR_FLUID_LEVEL_SENSOR_TYPE_SET)
       )
    {
    if( !just_test )
        {
        HWM_sensor_lvl_io_hndlr( id, data, size );
        }
    ret = TRUE;
    }

else if( id == IOP_MRN_SNSR_TRIM_TAB_CAL_INIT )
    {
    if( !just_test )
        {
        /*----------------------------------------------------------
        Clear data from nonvol. Also updates the calibration status.
        ----------------------------------------------------------*/
        HWM_calibration_reset();

        /*----------------------------------------------------------
        Initialize Calibration by setting up the appropriate timers:

            SYC_TIMER_HWM_TRIM_TAB_CAL:
                -1st used to ensure operator begins the procedure
                 within a specified amount of time.
                -2nd used to ensure frequency has increased
                 within a specified amount of time.
        ----------------------------------------------------------*/
        SYC_set_timer_runtime(SYC_TIMER_HWM_TRIM_TAB_CAL,  HWM_CAL_MAX_TIME_MS);

        }
    ret = TRUE;
    }

else if( id == IOP_MRN_SNSR_TRIM_TAB_MULTI_CAL )
    {
    if( !just_test )
        {
        HWM_update_calibration_tbl( id, data, size );
        }
    ret = TRUE;
    }

    else if( id == IOP_MRN_SNSR_SET_TRIM_TAB_OSCILLATION )
        {
        if( !just_test )
            {
            #if ( _TSTBLD == _ON )

            if( SYC_in_test_mode() )
                {
                /*----------------------------------
                Check if oscillation should be
                turned on or off.
                ----------------------------------*/
                if( *( uint8 * )data == 1 )
                    {
                    HWM_set_oscillation_state( TRUE );
                    }
                else
                    {
                    HWM_set_oscillation_state( FALSE );
                    }
                }

            #endif
            }
        ret = TRUE;
        }

else if( id == IOP_MRN_SNSR_WTRSPD_CAL_START )
    {
    if( !just_test )
        {
        HWM_reset_water_speed_calibration();
        }
    ret = TRUE;
    }

else if( id == IOP_MRN_SNSR_WTRSPD_CAL_PNT )
    {
    if( !just_test )
        {
        HWM_water_speed_calibration( *(uint16 *)data );
        }
    ret = TRUE;
    }

else if( id == IOP_MRN_SNSR_WTRSPD_CAL_TBL_REQ )
    {
    if( !just_test )
        {
        HWM_water_speed_cal_table_request();
        }
    ret = TRUE;
    }

else if( id == IOP_MRN_SNSR_WTRSPD_CAL_TBL_SET )
    {
    if(!just_test)
        {
        HWM_water_speed_cal_table_set( (HWM_wtr_speed_cal_entry *)data, size );
        }
    ret = TRUE;
    }
#endif

#endif


#if(FALSE) /*Future Garmin proprietary packet work*/
else if( id == IOP_MRN_SNSR_USER_CAL )
    {
    if( !just_test )
        {
        uint8   buf[5];     /* Packet for sending response */
        uint8 * payload;    /* Start of packet, after the calibration type */
        route->source_addr = IOP_NMEA2K_GLOBAL_ADDRESS;
        payload = (uint8 *)data + sizeof(IOP_mrn_snsr_user_cal_type);

        switch( *(IOP_mrn_snsr_user_cal_type *)data )
            {
            case IOP_SNSR_TEMP_OFFSET_SET:
                NVM_write_nonvol( HWM_temperature_offset, *(sint16 *)payload );
                /* break intentionally omitted */
            case IOP_SNSR_TEMP_OFFSET_RQST:
                {
                buf[0] = IOP_SNSR_TEMP_OFFSET_DATA;
                *((sint16 *)&buf[1]) = NVM_read_nonvol( HWM_temperature_offset );
                IOP_inst_route( IOP_MRN_SNSR_USER_CAL, ( uint8 * )&buf, 1 + sizeof( sint16 ), route );
                }
                break;

            case IOP_SNSR_TEMP_MULT_SET:
                NVM_write_nonvol( HWM_temperature_multiplier, *(uint16 *)payload );
                /* break intentionally omitted */
            case IOP_SNSR_TEMP_MULT_RQST:
                {
                buf[0] = IOP_SNSR_TEMP_MULT_DATA;
                *((uint16 *)&buf[1]) = NVM_read_nonvol( HWM_temperature_multiplier );
                IOP_inst_route( IOP_MRN_SNSR_USER_CAL, ( uint8 * )&buf, 1 + sizeof( uint16 ), route );
                }
                break;

            default:
                break;
            }

        }
    ret = TRUE;
    }
#endif


else if( id == IOP_MRN_SNSR_RQST_CAPABILITIES )
    {
    if ( !just_test )
        {
        IOP_send_capabilities();
        }
    ret = TRUE;
    }

else if( id == IOP_MRN_SNSR_GNRC_CNFG )
    {
    if( !just_test )
        {
        process_gnrc_cnfg( data, size );
        }
    ret = TRUE;
    }

#if(FALSE) /*Future Garmin proprietary packet work*/
#if ( _BBBLD == _ON )

else if(id == IOP_NET_UPDATE_BEGIN)
    {
    if(!just_test)
        {
        /*----------------------------------------------
        Save that we are in net update mode.
        ----------------------------------------------*/
        HWM_xfer_mode = HWM_XFER_NET_UPDATE;
        }
    ret = TRUE;
    }

else if(id == IOP_NET_UPDATE_DONE)
    {
    if(!just_test)
        {
        if( HWM_xfer_mode == HWM_XFER_NET_UPDATE )
            {
            /*------------------------------------------
            End of a net update. Check if the system
            code is present and has a valid checksum,
            then transfer to system code if it is.
            ------------------------------------------*/
            HWM_rgn_system_check(); /* Does not return if successful! */
            }
        }
    ret = TRUE;
    }

else if(id == IOP_RGN_CMPLT)
    {
    if(!just_test)
        {
        /*----------------------------------------------
        Send ack.
        ----------------------------------------------*/
        IOP_inst_route( IOP_ACK_BYTE, ( uint8 * )&id, sizeof( id ), route );

        /*----------------------------------------------
        End of a region transfer.
        ----------------------------------------------*/
        HWM_rgn_xfer_cmplt();   /* Does not return if successful! */
        }
    ret = TRUE;
    }

else if(id == IOP_RGN_DATA)
    {
    if(!just_test)
        {
        uint16      address;
        sint16      data_size;
        uint8     * byptr;

        address     = (uint16) *(uint32 *)data;
        data_size   = (sint16)(size - sizeof(uint32));
        byptr       = (uint8 *)data + (sizeof(uint32));

        /*----------------------------------------------
        Pass the data down to the region code.
        ----------------------------------------------*/
        HWM_rgn_xfer_data( address, byptr, data_size );

        /*----------------------------------------------
        Send ack.
        ----------------------------------------------*/
        IOP_inst_route( IOP_ACK_BYTE, ( uint8 * )&id, sizeof( id ), route );
        }
    ret = TRUE;
    }

else if(id == IOP_RGN_STRT_RX)
    {
    if(!just_test)
        {
        boolean rst;
        HWM_rgn_stat_type rgn_status;

        /*----------------------------------------------
        Send ack.
        ----------------------------------------------*/
        IOP_inst_route( IOP_ACK_BYTE, ( uint8 * )&id, sizeof( id ), route );

        /*----------------------------------------------
        Start receiving a region.
        ----------------------------------------------*/
        rst = HWM_rgn_xfer_start( *(HWM_data_rgn_type *)data );

        /*----------------------------------------------
        If packet was valid for xfer, send success.
        ----------------------------------------------*/
        if( rst == TRUE )
            {
            rgn_status = HWM_RS_SUCCESS;
            IOP_inst_route( IOP_RGN_STATUS, (uint8*) &rgn_status, sizeof(rgn_status), route );
            }
        }
    ret = TRUE;
    }

else if(id == IOP_HOLD_IN_BB)
    {
    /*--------------------------------------------------
    This handler absolutely should check to see if the
    value of just_test is FALSE before actually doing
    its processing. However, we need to listen to the
    IOP_HOLD_IN_BB inst when we don't have a valid
    nmea2k address. The way in which this is
    accomplished is to call the Garmin IOP data handler
    with a just_test value of TRUE when the nmea2k
    address is invalid, and false when it is valid.
    Then, right here, we just ignore the just_test
    value and go ahead and hold in BB regardless. That
    way, no other insts get handled when the nmea2k
    address is invalid, but this particular one does.
    --------------------------------------------------*/
    /*if(!just_test)*/
    /*  {           */
        SYC_hold_in_bb();
    /*  }           */
    ret = TRUE;
    }

#else /* _BBBLD != _ON */

else if(id == IOP_NET_UPDATE_BEGIN)
    {
    if(!just_test)
        {
        SYC_pwrdwn();
        HWM_xfer_bb( HWM_XFER_NET_UPDATE,
                     HWM_INVALID_RGN,
                     0xFF,
                     IOP_GRMN_NMEA2K_RESERVED_LAST_PORT,
                     IOP_GRMN_NMEA2K_RESERVED_LAST_PORT,
                     NVM_read_nonvol( iop_nmea2k_addr )
                   );
        }
    ret = TRUE;
    }

else if(id == IOP_RGN_STRT_RX)
    {
    if(!just_test)
        {
        /*----------------------------------------------
        Send ack.
        ----------------------------------------------*/
        IOP_inst_route( IOP_ACK_BYTE, ( uint8 * )&id, sizeof( id ), route );

        /*----------------------------------------------
        We need to transfer to bootblock code to update
        sw.
        ----------------------------------------------*/
        SYC_pwrdwn();
        HWM_xfer_bb( HWM_XFER_RGN_VIA_BB,
                     *(HWM_data_rgn_type *)data,
                     route->source_addr,
                     route->source_port,
                     route->dest_port,
                     NVM_read_nonvol( iop_nmea2k_addr )
                   );
        }
    ret = TRUE;
    }
#endif
#endif

	return (ret);
} /* iop_grmn_proc_input() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       iop_grmn_tx - Transmit Garmin Packet
 *
 *   DESCRIPTION:
 *       This procedure transmits a Garmin formatted packet.
 *
 *********************************************************************/

void iop_grmn_tx
    (
    IOP_inst_id_type const id,
    uint8 const* const data,
    uint8 const data_size, IOP_route_type * const route
    )
{

iop_nmea2k_tx_grmn(id, route, data, data_size);

} /* iop_grmn_tx() */

/*********************************************************************
 *
 *   PROCEDURE NAME:
 *       process_command - Process Received Command
 *
 *   DESCRIPTION:
 *       This procedure handles processing of received commands.
 *
 *********************************************************************/
static void process_command
    (
    uint8 const * const data,
    uint8 const data_size,
    IOP_route_type * const route
    )
{
/*----------------------------------------------------------
 Local Variables
 ----------------------------------------------------------*/
#if ( SYC_NVM_SUPPORT == TRUE )
uint32 unit_id;
#endif

#if ( _TSTBLD == _ON )

union
    {
    boolean test_result;
    } cmd_data;

#endif

/*----------------------------------------------------------
 Process other garmin service features.
 ----------------------------------------------------------*/

/*----------------------------------------------------------
 Handle the command.
 ----------------------------------------------------------*/
switch( *(IOP_cmnd_id_type*) data )
    {
#if(FALSE) /*Future Garmin proprietary packet work*/
    case IOP_POWER_OFF:
        SYC_pwr_off();
        break;

    case IOP_REQ_SYC_MODE:
        IOP_inst_route( IOP_DI AG_SYC_MODE, &SYC_mode, sizeof( SYC_mode ), route );
        break;
#endif

#if ( SYC_NVM_SUPPORT == TRUE )
    case IOP_DOWN_LOAD_ID:
        unit_id = NVM_read_nonvol( syc_unit_id );
        IOP_inst_route( IOP_UNIT_ID_DATA, (uint8 *)&unit_id, sizeof( unit_id ), route );
        break;
#endif

    case IOP_REQ_PRODUCT_INFO_SUMMARY:
        GRM_send_product_info(route);
        break;

#if(FALSE) /*Future Garmin proprietary packet work*/
    case IOP_REQ_ASSERT_DATA:
        IOP_tx_assert_data();
        break;

#if ( _TSTBLD == _ON )
    case IOP_TEST_EEPROM:
        cmd_data.test_result = HWM_eeprom_test();
        IOP_evnt( IOP_EEPRM_TEST, cmd_data.test_result );
        break;

    case IOP_TEST_RAM:
        cmd_data.test_result = HWM_ram_test();
        IOP_evnt( IOP_RAM_TEST, cmd_data.test_result );
        break;

    case IOP_TEST_ROM:
        cmd_data.test_result = HWM_rom_test();
        IOP_evnt( IOP_ROM_TEST, cmd_data.test_result );
        break;
#endif

#if ( _BBBLD != _ON ) && ( SYC_STACK_CHECK_SUPPORT == TRUE )
    case IOP_DOWN_LOAD_STACKS_INFO:
        IOP_tx_stack_data();
        break;
#endif

    case IOP_CLR_NONVOL_UNPROTECTED_ONLY:
        NVM_user_clear();

        /*--------------------------------------------------
        Nonvol clear is complete, restart the unit
        --------------------------------------------------*/
        SYC_pwrdwn();
        HWM_xfer_sys();
        break;
#endif

    case IOP_DOWN_LOAD_NVOL:
        NVM_inst_nonvol();
        break;

    default:
        break;
    } /* switch( cmnd_id ) */

} /* process_command() */

/****************************************************************************
*
*   PROCEDURE NAME:
*		process_gnrc_cnfg
*
*   DESCRIPTION:
*
*   NOTES:
*
****************************************************************************/
static void process_gnrc_cnfg
    (
    char    const * const data,
    uint8   const size
    )
{
const char gnrc_cmnd_temp_source[] = "TMPSRC=";        /* 8 bit Temperature Source index. */
const char gnrc_cmnd_temp_inst[] = "TMPINST=";
const char gnrc_cmnd_temp_offset[] = "TMPOFFSET=";

const char *value;
int stoi_value;

switch( HWM_get_sensor_type() )
    {
    case TEMPERATURE_SENSOR:
        /*----------------------------------------------------------
        Temperature Source
        ----------------------------------------------------------*/
        if( 0 == strncmp( data, gnrc_cmnd_temp_source, ( sizeof(gnrc_cmnd_temp_source) - 1 ) ) )
            {
            value = ( data + sizeof(gnrc_cmnd_temp_source) - 1 );

            stoi_value = atoi( value );

            if( stoi_value <= 14 ) /* Enforce Limits (Based on allowed PGN values). */
                {
                NVM_write_nonvol( HWM_temperature_source, ( (uint8)stoi_value ) );
                }
            return;
            }

        /*----------------------------------------------------------
        Temperature Instance
        ----------------------------------------------------------*/
        if( 0 == strncmp( data, gnrc_cmnd_temp_inst, ( sizeof(gnrc_cmnd_temp_inst) - 1 ) ) )
            {
            value = ( data + sizeof(gnrc_cmnd_temp_inst) - 1 );

            stoi_value = atoi( value );

            if( stoi_value <= 253 ) /* Enforce Limits (Based on allowed PGN values). */
                {
                NVM_write_nonvol( HWM_temperature_inst, ( (uint8)stoi_value ) );
                }
            return;
            }

        /*----------------------------------------------------------
        Temperature Offset
        ----------------------------------------------------------*/
        if( 0 == strncmp( data, gnrc_cmnd_temp_offset, ( sizeof(gnrc_cmnd_temp_offset) - 1 ) ) )
            {
            value = ( data + sizeof(gnrc_cmnd_temp_offset) - 1 );

            stoi_value = atoi( value );

            NVM_write_nonvol( HWM_temperature_offset, ( (sint16)stoi_value ) );
            return;
            }

        break;

    case HEADING_SENSOR:

        break;

    default:
        break;
    }
}	/* process_gnrc_cnfg() */
