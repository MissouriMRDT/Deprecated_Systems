/*********************************************************************
*
*   HEADER NAME:
*       GRM_pub_prj.h - Project Specific Public Declarations
*
*   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _GRM_PUB_PRJ
#define      _GRM_PUB_PRJ

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

#define PRODUCT_NUM_DEC         (1015)
#define PRODUCT_NUM             "\xF7\x03"

#if (_BBBLD == _ON)

    #define PRODUCT_STR_RUDDER_ANGLE        "GRA10-BB"
    #define PRODUCT_STR_ENGINE_TILT         "GET10-BB"
    #define PRODUCT_STR_FLUID_LEVEL         "GFL10-BB"
    #define PRODUCT_STR_BENNETT_TRIM        "GBT10-BB"
    #define PRODUCT_STR_SPEED_TEMP          "GST10-BB"

    #define PRODUCT_STR_SIZE                (8)

#else

    #define PRODUCT_STR_RUDDER_ANGLE        "GRA10"
    #define PRODUCT_STR_ENGINE_TILT         "GET10"
    #define PRODUCT_STR_FLUID_LEVEL         "GFL10"
    #define PRODUCT_STR_BENNETT_TRIM        "GBT10"
    #define PRODUCT_STR_SPEED_TEMP          "GST10"

    #define PRODUCT_STR_SIZE                (5)

#endif

/*----------------------------------------------------------
Set the REL_VERSION_NUM number to a value greater than or
equal to The VERSION_NUM number to signify a beta build.
Set the REL_VERSION_NUM number to a value less than then
VERSION_NUM number to signify a release build.
----------------------------------------------------------*/
#define REL_VERSION_NUM         (210)
#define VERSION_NUM             (210)    /* Do not include leading zero or it will be interpreted as an Octal. */
#define VERSION_NUM_CODE        "\xD2"  /* Hexidecimal = 210 */

#define VERSION_STR             "2.10"
#define VERSION_STR_SIZE        (4)

#define MODEL_VERSION_STR       "1.0"
#define MODEL_VERSION_STR_SIZE  (3)
#define DASH_NMBR               (0)     /* Dash part of product number (006-B0774-xx) */

/*----------------------------------------------------------
If a username is defined, then this is a development build.
----------------------------------------------------------*/
#if defined( _UN )

    #define DESCRIPTION_STR             stringize(_UN) " " __DATE__ " "
    #define DESCRIPTION_STR_SIZE        (16)

/*----------------------------------------------------------
If the software version number is less than the release
version number, then this is a beta build.
----------------------------------------------------------*/
#elif (VERSION_NUM < REL_VERSION_NUM)

    #define DESCRIPTION_STR             "Beta "
    #define DESCRIPTION_STR_SIZE        (5)

/*----------------------------------------------------------
If the software version number is greater than or equal to
the release version number, then this is a release build.
----------------------------------------------------------*/
#else

    #define DESCRIPTION_STR             "Ver "
    #define DESCRIPTION_STR_SIZE        (4)

#endif

#define GRM_BUILD_DESCRIPTION_RUDDER_ANGLE      PRODUCT_NUM VERSION_NUM_CODE "\x00" PRODUCT_STR_RUDDER_ANGLE    " " DESCRIPTION_STR VERSION_STR "\x00"
#define GRM_BUILD_DESCRIPTION_ENGINE_TILT       PRODUCT_NUM VERSION_NUM_CODE "\x00" PRODUCT_STR_ENGINE_TILT     " " DESCRIPTION_STR VERSION_STR "\x00"
#define GRM_BUILD_DESCRIPTION_FLUID_LEVEL       PRODUCT_NUM VERSION_NUM_CODE "\x00" PRODUCT_STR_FLUID_LEVEL     " " DESCRIPTION_STR VERSION_STR "\x00"
#define GRM_BUILD_DESCRIPTION_BENNETT_TRIM      PRODUCT_NUM VERSION_NUM_CODE "\x00" PRODUCT_STR_BENNETT_TRIM    " " DESCRIPTION_STR VERSION_STR "\x00"
#define GRM_BUILD_DESCRIPTION_SPEED_TEMP        PRODUCT_NUM VERSION_NUM_CODE "\x00" PRODUCT_STR_SPEED_TEMP      " " DESCRIPTION_STR VERSION_STR "\x00"

#define GRM_BUILD_DESCRIPTION_SIZE              (2 +                             /* PRODUCT_NUM     */ \
                                                1 +                             /* VERSION_NUM      */ \
                                                1 +                             /* "\x00"           */ \
                                                PRODUCT_STR_SIZE +              /* PRODUCT_STR      */ \
                                                1 +                             /* SPACE            */ \
                                                DESCRIPTION_STR_SIZE +          /* DESCRIPTION_STR  */ \
                                                VERSION_STR_SIZE +              /* VERSION_STR      */ \
                                                1)                              /* NULL termination */

#define GRM_BUILD_VERSION_NUM                   VERSION_NUM


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

#endif  /* _GRM_PUB_PRJ */
