/*********************************************************************
*
*   HEADER NAME:
*       SYC_pub_prj_s - System Controller Public Project Declarations
*
*       Note: This file is included by both the compiler and assembler.
*
*   Copyright 1998-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log[5]$
* $NoKeywords$
*
*********************************************************************/

#if !defined _SYC_PUB_PRJ_S
#define      _SYC_PUB_PRJ_S

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "GRM_pub_s.h"


/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Technology Switches
----------------------------------------------------------*/

/*----------------------------------------------------------
System Build
----------------------------------------------------------*/

    /*------------------------------------------------------
    Non-Vol Memory Support Switch
    Non-Vol Memory Write Support Switch
    ------------------------------------------------------*/
    #define SYC_NVM_SUPPORT                 TRUE
    #define SYC_NVM_WRITE_SUPPORT           TRUE

/*----------------------------------------------------------
NMEA 2000 Support Switch
This switch turns on/off all NMEA 2000 support.
----------------------------------------------------------*/
#define SYC_NMEA2K_SUPPORT              TRUE

/*----------------------------------------------------------
CANNET Support Switch
This switch turns on/off all CANNET support.
----------------------------------------------------------*/
#define SYC_CANET_SUPPORT               FALSE

/*----------------------------------------------------------
CAN Support Switch
If we are using any CAN protocol, then CAN support
is turned on.
----------------------------------------------------------*/
#if (SYC_CANET_SUPPORT == TRUE) || (SYC_NMEA2K_SUPPORT == TRUE)
    #define SYC_CAN_SUPPORT             TRUE
#else
    #define SYC_CAN_SUPPORT             FALSE
#endif

/*----------------------------------------------------------
Serial Support Switch
----------------------------------------------------------*/
#define SYC_SERIAL_SUPPORT              FALSE

/*----------------------------------------------------------
IOP Support Switch
If we have any method of transmitting, then IOP support
is turned on.
----------------------------------------------------------*/
#if (SYC_SERIAL_SUPPORT == TRUE) || (SYC_CAN_SUPPORT == TRUE)
    #define SYC_IOP_SUPPORT             TRUE
#else
    #define SYC_IOP_SUPPORT             FALSE
#endif

/*----------------------------------------------------------
If serial is turned off, then serial receive should be off
as well.
----------------------------------------------------------*/
#if (SYC_SERIAL_SUPPORT == FALSE)

    /*------------------------------------------------------
    Serial Receive Switch
    This switch turns on/off the ability to receive data.
    If set to FALSE, the unit may still have the ability to
    transmit data.
    ------------------------------------------------------*/
    #undef  SYC_SERIAL_RX_SUPPORT
    #define SYC_SERIAL_RX_SUPPORT       FALSE
#endif

/*----------------------------------------------------------
Hardware Verification Switch
This switch turn on/off code that was built for the purpose
of testing hardware.
----------------------------------------------------------*/
#define SYC_STACK_CHECK_SUPPORT         FALSE

/*----------------------------------------------------------
LED Support Switch
----------------------------------------------------------*/
#define SYC_LED_SUPPORT                 FALSE

/*----------------------------------------------------------
Cypress Sonar Switch
----------------------------------------------------------*/
#define SYC_CYPRESS_SONAR_SUPPORT       FALSE

/*----------------------------------------------------------
Water Speed Support Switch
----------------------------------------------------------*/
#define SYC_WATER_SPEED_SUPPORT         FALSE

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

#endif  /* _SYC_PUB_PRJ_S */
