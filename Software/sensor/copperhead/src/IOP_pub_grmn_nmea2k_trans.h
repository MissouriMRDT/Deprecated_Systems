/*********************************************************************
*
*   HEADER NAME:
*       IOP_pub_grmn_nmea2k_trans - IOP Public Garmin NMEA 2000 Transport Declarations
*
*   Copyright 2005-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _IOP_PUB_GRMN_NMEA2K_TRANS
#define      _IOP_PUB_GRMN_NMEA2K_TRANS

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "GRM_pub.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Garmin over NMEA 2000 ports
----------------------------------------------------------*/
enum
    {
    IOP_GRMN_NMEA2K_RESERVED_FIRST_PORT,  /* Reserved for future use */
    IOP_GRMN_NMEA2K_DFLT_PRIMARY_PORT  ,  /* Default primary port */
    IOP_GRMN_NMEA2K_GARMIN_APP_PORT    ,  /* Standard Garmin application port */
    IOP_GRMN_NMEA2K_CCS_PORT           ,  /* CCS communication */
    IOP_GRMN_NMEA2K_SENSOR_PORT        ,  /* Sensor state data */
    IOP_GRMN_NMEA2K_SHARE_PORT         ,  /* Shared data port  */
    IOP_GRMN_NMEA2K_MOB_PORT           ,  /* System-wide MOB port */
    IOP_GRMN_NMEA2K_OEM_PORT           ,  /* OEM data port                      */
    IOP_GRMN_NMEA2K_AS_PORT            ,  /* Activesync port */

    IOP_GRMN_NMEA2K_TOTAL_PORTS        ,  /* Total number of ports */

    IOP_GRMN_NMEA2K_RESERVED_LAST_PORT  =   255, /* Reserved for future use */
    IOP_GRMN_NMEA2K_INV_PORT            =  IOP_GRMN_NMEA2K_RESERVED_LAST_PORT
    };

/*----------------------------------------------------------
** NOTE: SEE A TEAM LEADER BEFORE ALLOCATING A NEW PORT**
----------------------------------------------------------*/
//compiler_assert( IOP_GRMN_NMEA2K_TOTAL_PORTS == 9 );

/*----------------------------------------------------------
The maximum safe data payload size for garmin over NMEA2K.
----------------------------------------------------------*/
#define IOP_GRMN_NMEA2K_MAX_DATA_SZ ( 192 )

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


#endif  /* _IOP_PUB_GRMN_NMEA2K_TRANS */
