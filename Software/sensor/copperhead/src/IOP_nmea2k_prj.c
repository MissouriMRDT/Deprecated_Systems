/*********************************************************************
*
*   MODULE NAME:
*       IOP_nmea2k_prj.c - Project-Specific Input/Output Processing
*                          for NMEA 2000 Data
*
*   DESCRIPTION:
*       Input/Output Processing Module for NMEA 2000 Data (over a CAN bus).
*
*   Copyright 2007-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "NVM_pub.h"
#include "GRM_pub.h"
#include "HWM_pub.h"
#include "IOP_pub.h"
#include "SYC_pub.h"
#include "iop_pub_snsr.h"
#include "iop_prv.h"
#include "iop_prv_nmea2k.h"
#include "heading.h"

/*----------------------------------------------------------
Compile out this file if no nmea2k support.
----------------------------------------------------------*/
#if ( SYC_NMEA2K_SUPPORT == TRUE )

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            PROJECT INCLUDES
--------------------------------------------------------------------*/

#include "iop_prv_nmea2k_prj.h"

/*--------------------------------------------------------------------
                            MEMORY CONSTANTS
--------------------------------------------------------------------*/

#if( _SYSBLD == _ON )

    static const iop_nmea2k_temperature_t TEMPERATURE_DEFAULTS[] =
        {
        /* Field    Description                 Value */
        /* 1        Sequence ID             */  IOP_NMEA2K_UINT08_UNAVAIL,
        /* 2        Temperature Instance    */  IOP_NMEA2K_UINT08_UNAVAIL,
        /* 3        Temperature Source      */  IOP_NMEA2K_UINT08_UNAVAIL,
        /* 4        Actual Temperature      */  IOP_NMEA2K_UINT16_UNAVAIL,
        /* 5        Set Temperature         */  IOP_NMEA2K_UINT16_UNAVAIL,
        /* 6        Reserved                */  IOP_NMEA2K_UINT08_UNAVAIL
        };
    UTL_compiler_assert( sizeof(TEMPERATURE_DEFAULTS) == 8, IOP_NMEA2K_PRJ );

    static const iop_nmea2k_temperature_ext_t TEMPERATURE_EXT_DEFAULTS[] =
        {
        /* Field    Description                 Value */
        /* 1        Sequence ID             */  IOP_NMEA2K_UINT08_UNAVAIL,
        /* 2        Temperature Instance    */  IOP_NMEA2K_UINT08_UNAVAIL,
        /* 3        Temperature Source      */  IOP_NMEA2K_UINT08_UNAVAIL,
        /* 4        Actual Temperature      */  IOP_NMEA2K_UINT24_UNAVAIL,
        /* 5        Set Temperature         */  IOP_NMEA2K_UINT16_UNAVAIL
        };
    UTL_compiler_assert( sizeof(TEMPERATURE_EXT_DEFAULTS) == 8, IOP_NMEA2K_PRJ );

    static const iop_nmea2k_heading_t HEADING_DEFAULTS[] =
        {
        /* Field    Description                 Value */
        /* 1        Sequence ID             */  IOP_NMEA2K_UINT08_UNAVAIL,
        /* 2        Heading Sensor Reading  */  IOP_NMEA2K_UINT16_UNAVAIL,
        /* 3        Deviation               */  IOP_NMEA2K_SINT16_UNAVAIL,
        /* 4        Variation               */  IOP_NMEA2K_SINT16_UNAVAIL,
        /* 5        Heading Sensor Reference*/  0x03,		/* XXXXXX11 */
        /* 6        Reserved                */  0x3F        /* 111111XX */
        };
    UTL_compiler_assert( sizeof(HEADING_DEFAULTS) == 8, IOP_NMEA2K_PRJ );

#endif /* ( _SYSBLD == _ON ) */

static const iop_nmea2k_pgn_info_t invalid_pgn =
    {
    0xFFFFFFFF, { TRUE,     FALSE,   FALSE,  FALSE,  }
    };

iop_nmea2k_pgn_info_t PGN_INFO_TBL[ MAX_PGN_CNT ];

#if ( _BBBLD == _ON )

    /*----------------------------------------------------------
    PGN Info Table - Generic Table
    ----------------------------------------------------------*/
    const iop_nmea2k_pgn_info_t PGN_INFO_TBL_GENERIC[] =
        {
       /* PGN                           Single?     TX?     RX?     RX First Only? (only valid if Single=FALSE && RX=TRUE) */
        { iop_NMEA_ISO_ACK_PGN,         { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_ISO_REQ_PGN,         { TRUE,     FALSE,  TRUE,   TRUE,  } },
        { iop_NMEA_ISO_ADD_CLAIM,       { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_PROPR_SF_AD_PGN,     { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_REQ_CMD_ACK_PGN,     { FALSE,    TRUE,   TRUE,   FALSE, } },
        { iop_NMEA_PGN_LIST_PGN,        { FALSE,    TRUE,   FALSE,  FALSE, } },
        { iop_NMEA_PROPR_FP_AD_PGN,     { FALSE,    TRUE,   TRUE,   FALSE, } },
        { iop_NMEA_PROD_INFO_PGN,       { FALSE,    TRUE,   FALSE,  FALSE, } }
        };
    compiler_assert( cnt_of_array( PGN_INFO_TBL_GENERIC ) <= MAX_PGN_CNT );

#endif /* ( _BBBLD == _ON ) */

#if( _SYSBLD == _ON )

    /*----------------------------------------------------------
    PGN Info Table - Temperature Sensor
    ----------------------------------------------------------*/
    const iop_nmea2k_pgn_info_t PGN_INFO_TBL_TEMP[] =
        {
       /* PGN                           Single?     TX?     RX?     RX First Only? (only valid if Single=FALSE && RX=TRUE) */
        { iop_NMEA_ISO_ACK_PGN,         { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_ISO_REQ_PGN,         { TRUE,     FALSE,  TRUE,   TRUE,  } },
        { iop_NMEA_ISO_ADD_CLAIM,       { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_PROPR_SF_AD_PGN,     { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_REQ_CMD_ACK_PGN,     { FALSE,    TRUE,   TRUE,   FALSE, } },
        { iop_NMEA_PGN_LIST_PGN,        { FALSE,    TRUE,   FALSE,  FALSE, } },
        { iop_NMEA_PROPR_FP_AD_PGN,     { FALSE,    TRUE,   TRUE,   FALSE, } },
        { iop_NMEA_PROD_INFO_PGN,       { FALSE,    TRUE,   FALSE,  FALSE, } },
        { iop_NMEA_TEMPERATURE_PGN,     { TRUE,     TRUE,   FALSE,  TRUE,  } },
        { iop_NMEA_TEMPERATURE_EXT_PGN, { TRUE,     TRUE,   FALSE,  TRUE,  } },
        };
    compiler_assert( cnt_of_array( PGN_INFO_TBL_TEMP ) == PGN_INFO_TBL_TEMP_CNT );
    compiler_assert( cnt_of_array( PGN_INFO_TBL_TEMP ) <= MAX_PGN_CNT );

    /*----------------------------------------------------------
    PGN Info Table - Heading Sensor
    ----------------------------------------------------------*/
    const iop_nmea2k_pgn_info_t PGN_INFO_TBL_HEADING[] =
        {
       /* PGN                           Single?     TX?     RX?     RX First Only? (only valid if Single=FALSE && RX=TRUE) */
        { iop_NMEA_ISO_ACK_PGN,         { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_ISO_REQ_PGN,         { TRUE,     FALSE,  TRUE,   TRUE,  } },
        { iop_NMEA_ISO_ADD_CLAIM,       { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_PROPR_SF_AD_PGN,     { TRUE,     TRUE,   TRUE,   TRUE,  } },
        { iop_NMEA_REQ_CMD_ACK_PGN,     { FALSE,    TRUE,   TRUE,   FALSE, } },
        { iop_NMEA_PGN_LIST_PGN,        { FALSE,    TRUE,   FALSE,  FALSE, } },
        { iop_NMEA_PROPR_FP_AD_PGN,     { FALSE,    TRUE,   TRUE,   FALSE, } },
        { iop_NMEA_PROD_INFO_PGN,       { FALSE,    TRUE,   FALSE,  FALSE, } },
        { iop_NMEA_HEADING_PGN,         { TRUE,     TRUE,   FALSE,  TRUE,  } },
        };
    compiler_assert( cnt_of_array( PGN_INFO_TBL_HEADING ) == PGN_INFO_TBL_HEADING_CNT );
    compiler_assert( cnt_of_array( PGN_INFO_TBL_HEADING ) <= MAX_PGN_CNT );

#endif /* ( _SYSBLD == _ON ) */

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/

static uint8  seq_id;


/*--------------------------------------------------------------------
                                 MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

static void pwrp_pgn_info_tbl
    (
    void
    );

/*********************************************************************
*
*   PROCEDURE NAME:
*       IOP_nmea2k_init_prj - Project-Specific Initialization
*
*   DESCRIPTION:
*       Initializes project-specific NMEA2k values
*
*********************************************************************/
void IOP_nmea2k_init_prj
    (
    void
    )
{
/*------------------------------------------------------
If in the boot block, we don't need any of this.
------------------------------------------------------*/

seq_id = iop_NMEA2K_DD056_FIRST_SID;


/*-----------------------------------------------------
Power-up the PGN_INFO_TBL array.
-----------------------------------------------------*/
pwrp_pgn_info_tbl();

} /* IOP_nmea2k_init_prj() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_process_complete_packet_prj - Project-Specific
*           Handling of a Complete Packet
*
*   DESCRIPTION:
*       Called when the main file doesn't recognize a PGN being
*       processed. Returns true if the PGN was handled and false if
*       not.
*
*********************************************************************/
boolean iop_nmea2k_process_complete_packet_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data_ptr
    )
{

#if(FALSE) /*Later work*/
#if( _SYSBLD == _ON )

    /*------------------------------------------------------
    Mark instance as received based upon Adapter type.
    ------------------------------------------------------*/
    switch( HWM_get_adaptor_type() )
        {
        case HWM_ADAPTER_RUDDER_ANGLE:
            if( pgn->full == iop_NMEA_RUDDER_PGN )
                {
                iop_nmea2k_inst_rcvd( *data_ptr ); /* Mark instance as received. Instance is the 1st byte. */
                return( TRUE );
                }
            break;

        case HWM_ADAPTER_ENGINE_TILT:
            if( pgn->full == iop_NMEA_ENG_RAP_PGN )
                {
                if( *(data_ptr + 5) != IOP_NMEA2K_UINT08_UNAVAIL ) /* Only Auto Instance if Engine Tilt/Trim data is available. */
                    {
                    iop_nmea2k_inst_rcvd( *data_ptr ); /* Mark instance as received. Instance is the 1st byte. */
                    }
                return( TRUE );
                }
            break;

        case HWM_ADAPTER_FLUID_LEVEL:
            if( pgn->full == iop_NMEA_FLUID_LVL_PGN )
                {
                uint8 inst;
                uint8 type;

                inst = GRM_nibble_lower( *data_ptr ); /* Fluid Instance is lower 4 bits of 1st byte. */
                type = GRM_nibble_upper( *data_ptr ); /* Fluid Type     is upper 4 bits of 1st byte. */

                if( type == NVM_read_nonvol( HWM_fluid_type ) ) /* Only Auto Instance if same fluid type found. */
                    {
                    iop_nmea2k_inst_rcvd( inst ); /* Mark instance as received. Instance is 1st 4 bits of 1st byte. */
                    }
                return( TRUE );
                }
            break;

        case HWM_ADAPTER_BENNETT_TRIM:
            /*----------------------------------------------
            No Instance Support. Do nothing.
            ----------------------------------------------*/
            break;

        case HWM_ADAPTER_WATERSPEED_AND_TEMP: /* Used only for Temperature */
            if( pgn->full == iop_NMEA_TEMPERATURE_PGN )
                {
                uint8 source;

                source = *(data_ptr + 2);

                if( source == NVM_read_nonvol( HWM_temperature_source ) ) /* Only Auto Instance if same temperature source found. */
                    {
                    iop_nmea2k_inst_rcvd( *(data_ptr + 1) ); /* Mark instance as received. Instance is the 2nd byte. */
                    }
                return( TRUE );
                }
            break;

        default:
            UTL_assert_always( UTL_FILE_HWM_GENERIC_ADAPTER );
            break;
        }
#endif
#endif

return( FALSE ); /* Indicate that packet was not handled. */
} /* iop_nmea2k_process_complete_packet_prj() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_process_complex_cmd_prj - Project-Specific Handling of
*                                            the Complex Command PGN
*
*   DESCRIPTION:
*       Called when the main file doesn't recognize a PGN being
*       requested. Returns true if the PGN was handled and false if
*       not, to allow the caller to generate a nack. See where this
*       is called and follow the format of the main switch statement.
*
*********************************************************************/
boolean iop_nmea2k_process_complex_cmd_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data_ptr,
    uint8                       num_params,
    iop_nmea2k_dd139_t8         priority_err,
    iop_nmea2k_dd037_t8       * pgn_err,
    iop_nmea2k_dd141_t8       * param_err_list
    )
{
/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
#if( _SYSBLD == _ON )

    uint8   i;

#endif /* ( _SYSBLD == _ON ) */

switch( pgn->full )
    {
    #if( _SYSBLD == _ON )

#if(FALSE) /*later work*/
        case iop_NMEA_RUDDER_PGN:
            /*-----------------------------------------------
            Prevent other adapters from processing this code.
            -----------------------------------------------*/
            if( HWM_get_sensor_type() != HWM_ADAPTER_RUDDER_ANGLE )
                {
                break;
                }

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 1:
                        /*-----------------------------------------
                        Field 1: Rudder Instance
                        -----------------------------------------*/
                        if( *data_ptr <= iop_NMEA2K_DD128_LAST_INST )
                            {
                            iop_nmea2k_inst_user_set( *data_ptr );
                            }
                        else
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                            }

                        data_ptr++;         /* Field 1 size is 1 byte */
                        break;

                    case 5:
                        /*-----------------------------------------
                        Field 5: Rudder Position
                        Store calibration data in nonvol.
                        ----------------------------------*/
                        if( HWM_sensor_lvl_man_cal_request( *(sint16*)data_ptr ) == FALSE )
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_OUT_OF_RANGE;
                            }
                        data_ptr += 2;      /* Field 5 size is 2 bytes */
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        break;
                    }
                }
            return ( TRUE );

        case iop_NMEA_ENG_RAP_PGN:
            /*-----------------------------------------------
            Prevent other adapters from processing this code.
            -----------------------------------------------*/
            if( HWM_get_adapter_type() != HWM_ADAPTER_ENGINE_TILT )
                {
                break;
                }

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 1:
                        /*-----------------------------------------
                        Field 1: Engine Instance
                        -----------------------------------------*/
                        if( *data_ptr <= iop_NMEA2K_DD128_LAST_INST )
                            {
                            iop_nmea2k_inst_user_set( *data_ptr );
                            }
                        else
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                            }

                        data_ptr++;         /* Field 1 size is 1 byte */
                        break;

                    case 4:
                        /*-----------------------------------------
                        Field 4: Engine Tilt
                        Store calibration data in nonvol.
                        ----------------------------------*/
                        if( HWM_sensor_lvl_man_cal_request( *(sint8*)data_ptr ) == FALSE )
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_OUT_OF_RANGE;
                            }
                        data_ptr++;      /* Field 4 size is 1 byte */
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        break;
                    }
                }
            return ( TRUE );

        case iop_NMEA_FLUID_LVL_PGN:
            /*-----------------------------------------------
            Prevent other adapters from processing this code.
            -----------------------------------------------*/
            if( HWM_get_adapter_type() != HWM_ADAPTER_FLUID_LEVEL )
                {
                break;
                }

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 1:
                        /*----------------------------------
                        Field 1: Fluid Instance
                        ----------------------------------*/
                        iop_nmea2k_inst_user_set( GRM_nibble_lower( *data_ptr ) );
                        data_ptr++;         /* Field 1 size is 4 bits */
                        break;

                    case 2:
                        /*----------------------------------
                        Field 2: Fluid Type
                        ----------------------------------*/
                        if( GRM_nibble_lower( *data_ptr ) <= 0x0F )
                            {
                            NVM_write_nonvol( HWM_fluid_type, GRM_nibble_lower( *data_ptr ) );
                            }
                        else
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_OUT_OF_RANGE;
                            }
                        data_ptr++;         /* Field 2 size is 4 bits */
                        break;

                    case 3:
                        /*----------------------------------
                        Field 3: Fluid Level
                        Store calibration data in nonvol.
                        ----------------------------------*/
                        if( HWM_sensor_lvl_man_cal_request( *(sint16*)data_ptr ) == FALSE )
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_OUT_OF_RANGE;
                            }
                        data_ptr += 2;      /* Field 3 size is 2 bytes */
                        break;

                    case 4:
                        /*----------------------------------
                        Field 4: Tank Capacity
                        ----------------------------------*/
                        NVM_write_nonvol( HWM_fluid_tank_capacity, *(uint32*)data_ptr );
                        data_ptr += 4;      /* Field 4 size is 4 bytes */
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        break;
                    }
                }
            return ( TRUE );

        case iop_NMEA_SPEED_WATER_REF:

            /*-----------------------------------------------
            Prevent other adapters from processing this code.
            -----------------------------------------------*/
            if( HWM_get_sensor_type() != HWM_ADAPTER_WATERSPEED_AND_TEMP )
                {
                break;
                }

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {

                    case 3:
                        /*-----------------------------------------
                        Field 4: Water Speed Referenced Type
                        -----------------------------------------*/
                        NVM_write_nonvol( HWM_speed_water_ref_type, *data_ptr );

                        data_ptr++;         /* Field 3 size is 1 byte */
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        break;
                    }
                }
#endif
        case iop_NMEA_TEMPERATURE_PGN:

            /*-----------------------------------------------
            Prevent other adapters from processing this code.
            -----------------------------------------------*/
            if( HWM_get_sensor_type() != TEMPERATURE_SENSOR )
                {
                break;
                }

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 2:
                        /*-----------------------------------------
                        Field 2: Temperature Instance
                        -----------------------------------------*/
                        if( *data_ptr <= iop_NMEA2K_DD128_LAST_INST )
                            {
                            NVM_write_nonvol( HWM_temperature_inst, *data_ptr );
                            }
                        else
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                            }

                        data_ptr++;         /* Field 2 size is 1 byte */
                        break;

                    case 3:
                        /*-----------------------------------------
                        Field 3: Temperature Source
                        -----------------------------------------*/
                        NVM_write_nonvol( HWM_temperature_source, *data_ptr );

                        data_ptr++;         /* Field 3 size is 1 byte */
                        break;

                    case 4:
                        {
                        /*--------------------------------------
                        Field 4: Actual Temperature - Save the
                        difference as the Offset in nonvol
                        --------------------------------------*/
                        NVM_write_nonvol( HWM_temperature_offset, ( (sint16) ( *data_ptr - HWM_get_temperature() ) ) );
                        data_ptr += 2;      /* Field 4 size is 2 bytes */

                        /*----------------------------------
                        Report new value back.
                        ----------------------------------*/
                        IOP_route_type   route;      /* Route info for sending response */
                        uint8            buf[5];     /* Packet for sending response */

                        route.source_addr = IOP_NMEA2K_GLOBAL_ADDRESS;
                        route.source_port = IOP_GRMN_NMEA2K_SENSOR_PORT;
                        route.dest_port   = IOP_GRMN_NMEA2K_SENSOR_PORT;

                        buf[0] = IOP_SNSR_TEMP_OFFSET_DATA;
                        *((uint16 *)&buf[1]) = NVM_read_nonvol( HWM_temperature_offset );
                        IOP_inst_route( IOP_MRN_SNSR_USER_CAL, ( uint8 * )&buf, 1 + sizeof( sint16 ), &route );
                        }
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        break;
                    }
                }
            return ( TRUE );

        case iop_NMEA_TEMPERATURE_EXT_PGN:

            /*-----------------------------------------------
            Prevent other adapters from processing this code.
            -----------------------------------------------*/
            if( HWM_get_sensor_type() != TEMPERATURE_SENSOR )
                {
                break;
                }

            for( i = 0; i < num_params; i++ )
                {
                switch( *data_ptr++ )
                    {
                    case 2:
                        /*-----------------------------------------
                        Field 2: Temperature Instance
                        -----------------------------------------*/
                        if( *data_ptr <= iop_NMEA2K_DD128_LAST_INST )
                            {
                            NVM_write_nonvol( HWM_temperature_inst, *data_ptr );
                            }
                        else
                            {
                            param_err_list[i] = iop_NMEA2K_DD141_NO_MATCH;
                            }

                        data_ptr++;         /* Field 2 size is 1 byte */
                        break;

                    case 3:
                        /*-----------------------------------------
                        Field 3: Temperature Source
                        -----------------------------------------*/
                        NVM_write_nonvol( HWM_temperature_source, *data_ptr );

                        data_ptr++;         /* Field 3 size is 1 byte */
                        break;

                    case 4:
                        {
                        /*--------------------------------------
                        Field 4: Actual Temperature - Save the
                        difference as the Offset in nonvol
                        --------------------------------------*/
                        NVM_write_nonvol( HWM_temperature_offset, ( (sint16) ( *data_ptr - HWM_get_temperature_ext() ) ) );
                        data_ptr += 2;      /* Field 4 size is 2 bytes */

                        /*----------------------------------
                        Report new value back.
                        ----------------------------------*/
                        IOP_route_type   route;      /* Route info for sending response */
                        uint8            buf[5];     /* Packet for sending response */

                        route.source_addr = IOP_NMEA2K_GLOBAL_ADDRESS;
                        route.source_port = IOP_GRMN_NMEA2K_SENSOR_PORT;
                        route.dest_port   = IOP_GRMN_NMEA2K_SENSOR_PORT;

                        buf[0] = IOP_SNSR_TEMP_OFFSET_DATA;
                        *((uint16 *)&buf[1]) = NVM_read_nonvol( HWM_temperature_offset );
                        IOP_inst_route( IOP_MRN_SNSR_USER_CAL, ( uint8 * )&buf, 1 + sizeof( sint16 ), &route );
                        }
                        break;

                    default:
                        param_err_list[i] = iop_NMEA2K_DD141_BAD_DATA;
                        break;
                    }
                }
            return ( TRUE );

    #else /* ( _SYSBLD != _ON ) */

        case iop_NMEA_HEADING_PGN:
        case iop_NMEA_TEMPERATURE_EXT_PGN:
        case iop_NMEA_TEMPERATURE_PGN:
            /*--------------------------------------------------
            We handle this PGN, but only in system code. Return
            true because we handle the pgn, but set error.
            --------------------------------------------------*/
            *pgn_err = iop_NMEA2K_DD037_UNAVAIL;
            return( TRUE );

    #endif /* ( _SYSBLD == _ON ) */

    default:
        break;
    }


/*----------------------------------------------------------
Return FALSE if not handled above.
----------------------------------------------------------*/
return( FALSE );
} /* iop_nmea2k_process_complex_cmd_prj() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_process_complex_req_prj - Project-Specific Handling of
*                                            the Complex Request PGN
*
*   DESCRIPTION:
*       Called when the main file doesn't recognize a PGN being
*       requested. Returns true if the PGN was handled and false if
*       not, to allow the caller to generate a nack. See where this
*       is called and follow the format of the main switch statement.
*
*********************************************************************/

boolean iop_nmea2k_process_complex_req_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8               const * data_ptr,
    uint8                       num_params,
    iop_nmea2k_dd139_t8         interval_err,
    iop_nmea2k_dd037_t8       * pgn_err,
    boolean                   * param_err,
    iop_nmea2k_dd141_t8       * param_err_list
    )
{
return( FALSE );
} /* iop_nmea2k_process_complex_req_prj() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_process_reqest_prj - Project-Specific Handling of
*                                       the Request PGN
*
*   DESCRIPTION:
*       Called when the main file doesn't recognize a PGN being
*       requested. Returns true if the PGN was handled and false if
*       not, to allow the caller to generate a nack.
*
*********************************************************************/
boolean iop_nmea2k_process_reqest_prj
    (
    iop_nmea2k_pgn_t    const * pgn,
    uint8                       source_addr
    )
{
switch( pgn->full )
    {
#if( _SYSBLD == _ON )

    case iop_NMEA_TEMPERATURE_PGN:
        iop_nmea2k_tx_temperature_pgn();
        return( TRUE );

    case iop_NMEA_TEMPERATURE_EXT_PGN:
        iop_nmea2k_tx_temperature_ext_pgn();
        return( TRUE );

    case iop_NMEA_HEADING_PGN:
        iop_nmea2k_tx_heading_pgn();
        return( TRUE );

#endif /* ( _SYSBLD == _ON ) */

    default:
        return( FALSE );
    }
} /* iop_nmea2k_process_reqest_prj() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_update_tx_vals - Update values to be transmitted.
*
*   DESCRIPTION:
*       Updates the file scope variables that hold the values
*        transmitted by each of the iop_nmea2k_tx_* functions.
*
*********************************************************************/
#if(FALSE) /*May need to include later*/
#if( _SYSBLD == _ON )
void iop_nmea2k_update_tx_vals
    (
    void
    )
{
/*----------------------------------------------------------
Update the sequence ID

An upward counting number used to tie related information
together between different PGNs . For example, the SID would
be used to tie together the COG, SOG and RAIM values to a
given position. 255=no valid position fix to tie it to.
Range 0 to 250 for valid position fixes.
----------------------------------------------------------*/
if(seq_id == iop_NMEA2K_DD056_LAST_SID)
    {
    seq_id = iop_NMEA2K_DD056_FIRST_SID;
    }
else if(seq_id < iop_NMEA2K_DD056_LAST_SID)
    {
    seq_id++;
    }

} /* iop_nmea2k_update_tx_vals() */
#endif /* ( _SYSBLD == _ON ) */
#endif

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_tx_temperature_pgn - Transmit Temperature message.
*
*   DESCRIPTION:
*       Transmits a Temperature message.
*
*********************************************************************/
#if( _SYSBLD == _ON )
void iop_nmea2k_tx_temperature_pgn
    (
    void
    )
{

/*----------------------------------------------------------
Transmit the Temperature PGN only if we're configured as a
Temperature Sensor
----------------------------------------------------------*/
if( HWM_get_sensor_type() != TEMPERATURE_SENSOR  )
    {
    return;
    }

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t                id;
iop_nmea2k_temperature_t    temperature_data;

/*----------------------------------------------------------
Copy the defaults from flash.
----------------------------------------------------------*/
memcpy( (uint8 *)&temperature_data, (uint8*)TEMPERATURE_DEFAULTS, sizeof( iop_nmea2k_temperature_t )  );

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( 5 )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_TEMPERATURE_PGN )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

/*----------------------------------------------------------
Update the fields we care about.
----------------------------------------------------------*/
#if ( SYC_NVM_SUPPORT == TRUE )
    temperature_data.temp_inst   = NVM_read_nonvol( HWM_temperature_inst );
    temperature_data.temp_source = NVM_read_nonvol(HWM_temperature_source);
    temperature_data.actual_temp = HWM_get_temperature();  /* Degrees Kelvin with resolution of 1x10E-2 */
#else
    temperature_data.temp_inst   = 0;
    temperature_data.temp_source = 0;
    temperature_data.actual_temp = HWM_get_temperature();  /* Degrees Kelvin with resolution of 1x10E-2 */
#endif

/*----------------------------------------------------------
Send the frames.
----------------------------------------------------------*/
iop_nmea2k_single_frame_tx( &id, (uint8*)&temperature_data, sizeof( iop_nmea2k_temperature_t ), TRUE );

} /* iop_nmea2k_tx_temperature_pgn() */
#endif /* ( _SYSBLD == _ON ) */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_tx_temperature_ext_pgn - Transmit an Extended Temperature message.
*
*   DESCRIPTION:
*       Transmits an Extended Temperature message.
*
*********************************************************************/
#if( _SYSBLD == _ON )
void iop_nmea2k_tx_temperature_ext_pgn
    (
    void
    )
{

/*----------------------------------------------------------
Transmit the Temperature PGN only if we're configured as a
Temperature sensor
----------------------------------------------------------*/
if( HWM_get_sensor_type() != TEMPERATURE_SENSOR  )
    {
    return;
    }

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t                id;
iop_nmea2k_temperature_ext_t    temperature_ext_data;

/*----------------------------------------------------------
Copy the defaults from flash.
----------------------------------------------------------*/
memcpy( (uint8 *)&temperature_ext_data, (uint8*)TEMPERATURE_EXT_DEFAULTS, (uint16)sizeof(iop_nmea2k_temperature_ext_t) );

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( 5 )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_TEMPERATURE_EXT_PGN )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

/*----------------------------------------------------------
Update the fields we care about.
----------------------------------------------------------*/
#if ( SYC_NVM_SUPPORT == TRUE )
    temperature_ext_data.temp_inst   = NVM_read_nonvol( HWM_temperature_inst );
    temperature_ext_data.temp_source = NVM_read_nonvol(HWM_temperature_source);
    temperature_ext_data.actual_temp = HWM_get_temperature_ext();  /* Degrees Kelvin with resolution of 1x10E-2 */
#else
    temperature_ext_data.temp_inst   = 0;
    temperature_ext_data.temp_source = 0;
    temperature_ext_data.actual_temp = HWM_get_temperature_ext();  /* Degrees Kelvin with resolution of 1x10E-2 */
#endif

/*----------------------------------------------------------
Send the frames.
----------------------------------------------------------*/
iop_nmea2k_single_frame_tx( &id, (uint8*)&temperature_ext_data, sizeof(iop_nmea2k_temperature_ext_t), TRUE );

} /* iop_nmea2k_tx_temperature_ext_pgn() */
#endif /* ( _SYSBLD == _ON ) */

/*********************************************************************
*
*   PROCEDURE NAME:
*       iop_nmea2k_tx_heading_pgn - Transmit Heading message.
*
*   DESCRIPTION:
*       Transmits a Heading message.
*
*********************************************************************/
#if( _SYSBLD == _ON )
void iop_nmea2k_tx_heading_pgn
    (
    void
    )
{

/*----------------------------------------------------------
Transmit the Temperature PGN only if we're configured as a
Heading Sensor
----------------------------------------------------------*/
if( HWM_get_sensor_type() != HEADING_SENSOR  )
    {
    return;
    }

/*----------------------------------------------------------
Don't transmit this unless our address is valid.
----------------------------------------------------------*/
if( !iop_nmea2k_address_valid )
    {
    return;
    }

/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
HWM_can_id_t                id;
iop_nmea2k_heading_t        heading_data;

/*----------------------------------------------------------
Copy the defaults from flash.
----------------------------------------------------------*/
memcpy( (uint8 *)&heading_data, (uint8*)HEADING_DEFAULTS, (uint16)sizeof(iop_nmea2k_heading_t) );

/*----------------------------------------------------------
Fill in the ID field.
----------------------------------------------------------*/
id.ext = IOP_NMEA2K_IDENTIFIER_PRIO( 2 )
       | IOP_NMEA2K_IDENTIFIER_RSVD( 0 )
       | IOP_NMEA2K_IDENTIFIER_PGN( iop_NMEA_HEADING_PGN )
       | IOP_NMEA2K_IDENTIFIER_SOURCE( iop_nmea2k_address );

/*----------------------------------------------------------
Update the fields we care about.
----------------------------------------------------------*/
#if ( SYC_NVM_SUPPORT == TRUE )
    heading_data.heading_sensor_reading = get_vessel_heading();
    heading_data.deviation = 0;
    heading_data.variation = 0;
    heading_data.heading_sensor_ref = 1;
#else
    heading_data.heading_sensor_reading = get_vessel_heading();
    heading_data.deviation = 0;
    heading_data.variation = 0;
    heading_data.heading_sensor_ref = 1;
#endif


/*----------------------------------------------------------
Send the frames.
----------------------------------------------------------*/
iop_nmea2k_single_frame_tx( &id, (uint8*)&heading_data, sizeof(iop_nmea2k_heading_t), TRUE );

} /* iop_nmea2k_tx_heading_pgn() */
#endif /* ( _SYSBLD == _ON ) */

/*********************************************************************
*
*   PROCEDURE NAME:
*       pwrp_pgn_info_tbl - Powers up the PGN table
*
*   DESCRIPTION:
*       Returns pointer to the appropriate  PGN_INFO_TBL for the
*       current Adapter Type.
*
*********************************************************************/

static void pwrp_pgn_info_tbl
    (
    void
    )
{
/*---------------------------------------------------------
Macros
---------------------------------------------------------*/
#define copy_table( _a ) \
    memcpy( &PGN_INFO_TBL, &(_a), sizeof( _a ) );

/*----------------------------------------------------------
Local Variables
----------------------------------------------------------*/
uint8   i;

/*----------------------------------------------------------
Fill table with invalid entries
----------------------------------------------------------*/
for( i = 0; i < MAX_PGN_CNT; i++ )
    {
    copy_table( invalid_pgn );
    }

/*------------------------------------------------
Copy the appropriate table into the PGN_INFO_TBL.
------------------------------------------------*/
//#if ( _BBBLD == _ON )
//
//    copy_table( PGN_INFO_TBL_GENERIC );
//
//#endif /* ( _BBBLD == _ON ) */


#if( _SYSBLD == _ON )

    switch( HWM_get_sensor_type() )
        {

        case TEMPERATURE_SENSOR:
            copy_table( PGN_INFO_TBL_TEMP );
            break;

        case HEADING_SENSOR:
            copy_table( PGN_INFO_TBL_HEADING );
            break;

        default:
            UTL_assert_always( UTL_FILE_IOP_PRV_NMEA2K_PRJ );
            break;
        }

#endif /* ( _SYSBLD == _ON ) */

} /* pwrp_pgn_info_tbl() */

#endif /* SYC_NMEA2K_SUPPORT */
