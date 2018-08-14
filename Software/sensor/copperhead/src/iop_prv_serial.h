/*********************************************************************
*
*   HEADER NAME:
*       IOP_prv_serial.h - Serial Private Declarations
*
*   Copyright 2007 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _IOP_PRV_SERIAL_H
#define      _IOP_PRV_SERIAL_H

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "SYC_pub_prj_s.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/
typedef uint8 serial_protocol_type; enum
    {
    SERIAL_PROTOCOL_GARMIN,
    SERIAL_PROTOCOL_NMEA0183
    }; /* serial_protocol_type */

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

/*----------------------------------------------------------
This confusing compiler switch is done to put the correct
code where it needs to be, and not compile in things that
don't need to be there.

If we are compiling a system that can be either NMEA0183
or Garmin Serial, then we need to choose a protocol based
on the serial_protocol variable.

However, if we are only building a NMEA 0183 system (ie, no
Garmin Serial support at all), there's really no reason to
check that variable because if it says the protocol is
Garmin Serial, we really can't do anything. So, just macro
this function to SERIAL_PROTOCOL_NMEA0183. Because the
preprocessor does text substitution, that causes the
compiler to see things like:

   if(SERIAL_PROTOCOL_NMEA0183 == SERIAL_PROTOCOL_NMEA0183)

The compiler then optimizes the if statement out, creating
a clean system.
----------------------------------------------------------*/
#if ( (SYC_NMEA0183_SUPPORT == TRUE) && (SYC_GRM_SERIAL_SUPPORT == TRUE) )
serial_protocol_type IOP_get_serial_protocol
    (
    void
    );

#elif ( (SYC_NMEA0183_SUPPORT == FALSE) && (SYC_GRM_SERIAL_SUPPORT == TRUE) )
    #define IOP_get_serial_protocol() (SERIAL_PROTOCOL_GARMIN)

#elif ( (SYC_NMEA0183_SUPPORT == TRUE) && (SYC_GRM_SERIAL_SUPPORT == FALSE) )
    #define IOP_get_serial_protocol() (SERIAL_PROTOCOL_NMEA0183)

#endif

/*----------------------------------------------------------
The only time we need to set the serial protocol is if we
have built a system that uses both NMEA 0183 and Garmin
Serial. If we just use one or the other, we can't switch
protocols anyway, so just macro it to nothing.
----------------------------------------------------------*/
#if ( (SYC_NMEA0183_SUPPORT == TRUE) && (SYC_GRM_SERIAL_SUPPORT == TRUE) )
void IOP_set_serial_protocol
    (
    serial_protocol_type new_type
    );

#else
    #define IOP_set_serial_protocol(_new_type)
#endif



void iop_init_serial
    (
    void
    );


#endif  /* _IOP_PUB_H */
