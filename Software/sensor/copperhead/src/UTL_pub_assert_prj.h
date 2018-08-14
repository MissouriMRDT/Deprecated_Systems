/*********************************************************************
*
*   HEADER NAME:
*       UTL_pub_assert_prj.h - Utility Public, Project Specific Assert Declarations
*
*   Copyright 2002-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _UTL_PUB_ASSERT_PRJ
#define      _UTL_PUB_ASSERT_PRJ

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
The following enumeration uniquely defines each source file
so they may be identified in asserts.  Using file strings
to identify files consumes too much flash space.  Files should
be appended to the end of the list so that ID's will remain
unchanged.

This information can be used while J-Tagging by viewing
the first three bytes of EEPROM.
1st byte: File ID
2nd & 3rd bytes: Line number of the assert (little-endian)
----------------------------------------------------------*/
typedef uint8 UTL_file_id; enum
    {
    UTL_FILE_GRM_PRODUCT_INFO               = 0,
    UTL_FILE_HWM_CAN                        = 1,
    UTL_FILE_HWM_COMM                       = 2,
    UTL_FILE_HWM_FUEL_LVL                   = 3,
    UTL_FILE_HWM_PWR_PRJ                    = 4,
    UTL_FILE_HWM_TRIM_TAB                   = 5,
    UTL_FILE_IOP_MAIN                       = 6,
    UTL_FILE_IOP_NMEA2K                     = 7,
    UTL_FILE_NVM_MAIN                       = 8,
    UTL_FILE_SYC_MAIN                       = 9,
    UTL_FILE_SYC_MAIN_BB                    = 10,
    UTL_FILE_UTL_FILTER                     = 11,
    UTL_FILE_UTL_STR                        = 12,
    UTL_FILE_HWM_GENERIC_ADAPTER            = 13,
    UTL_FILE_HWM_WATER_SPEED                = 14,
    UTL_FILE_ADC_CONVERT                    = 15,
    UTL_FILE_GRM_INIT                       = 16,
    UTL_FILE_HWM_GENERIC_ADAPTER_SYS        = 17,
    UTL_FILE_IOP_PRV_NMEA2K_PRJ             = 18,
    UTL_FILE_UTL_MATH                       = 19,
    UTL_FILE_IAP                            = 20,
    UTL_FILE_HEADING                        = 21,

    }; /* UTL_file_id */

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

#endif  /* _UTL_PUB_ASSERT_PRJ */
