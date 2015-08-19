/*********************************************************************
*
*   HEADER NAME:
*       IOP_pub_nmea2k.h - NMEA 2000 Public Declarations
*
* Copyright 2007-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/
#if !defined _IOP_PUB_NMEA2K_H
#define _IOP_PUB_NMEA2K_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

#define IOP_NMEA2K_GLOBAL_ADDRESS       255 /* Global (broadcast) address */

/*----------------------------------------------------------
NMEA 2000 Data Type Reserved Values
----------------------------------------------------------*/
#define IOP_NMEA2K_UINT08_UNAVAIL   ( 0xFF )
#define IOP_NMEA2K_UINT08_RSVD      ( 0xFD )
#define IOP_NMEA2K_UINT08_INVALID   ( 0xFE )

#define IOP_NMEA2K_SINT08_UNAVAIL   ( 0x7F )
#define IOP_NMEA2K_SINT08_RSVD      ( 0x7D )
#define IOP_NMEA2K_SINT08_INVALID   ( 0x7E )

#define IOP_NMEA2K_UINT16_UNAVAIL   ( 0xFFFF )
#define IOP_NMEA2K_UINT16_RSVD      ( 0xFFFD )
#define IOP_NMEA2K_UINT16_INVALID   ( 0xFFFE )

#define IOP_NMEA2K_SINT16_UNAVAIL   ( 0x7FFF )
#define IOP_NMEA2K_SINT16_RSVD      ( 0x7FFD )
#define IOP_NMEA2K_SINT16_INVALID   ( 0x7FFE )

#define IOP_NMEA2K_UINT24_UNAVAIL   ( 0xFFFFFF )
#define IOP_NMEA2K_UINT24_RSVD      ( 0xFFFFFD )
#define IOP_NMEA2K_UINT24_INVALID   ( 0xFFFFFE )

#define IOP_NMEA2K_SINT24_UNAVAIL   ( 0x7FFFFF )
#define IOP_NMEA2K_SINT24_RSVD      ( 0x7FFFFD )
#define IOP_NMEA2K_SINT24_INVALID   ( 0x7FFFFE )

#define IOP_NMEA2K_UINT32_UNAVAIL   ( 0xFFFFFFFF )
#define IOP_NMEA2K_UINT32_RSVD      ( 0xFFFFFFFD )
#define IOP_NMEA2K_UINT32_INVALID   ( 0xFFFFFFFE )

#define IOP_NMEA2K_SINT32_UNAVAIL   ( 0x7FFFFFFF )
#define IOP_NMEA2K_SINT32_RSVD      ( 0x7FFFFFFD )
#define IOP_NMEA2K_SINT32_INVALID   ( 0x7FFFFFFE )

#define IOP_NMEA2K_FLOAT32_UNAVAIL  ( 0x7FFFFFFF )
#define IOP_NMEA2K_FLOAT32_RSVD     ( 0x7FFFFFFD )
#define IOP_NMEA2K_FLOAT32_INVALID  ( 0x7FFFFFFE )

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

#endif /* IOP_PUB_NMEA2K_H */
