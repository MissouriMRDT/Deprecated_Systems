/*********************************************************************
*
*   HEADER NAME:
*       GRM_pub_product_info.h - Product Information Header File
*
* Copyright 2004-2007 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _GRM_PUB_PRODUCT_INFO_H
#define _GRM_PUB_PRODUCT_INFO_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "GRM_pub.h"
#include "IOP_pub.h"

#if !defined( _WIN32 )

    #include "HWM_pub_rgn_defn.h"

#else

    #include "HWM_pub_rgn.h"

#endif


/*---------------------------------------------------------------
So you want to add another region?

add 1 to GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT via compiler flags
ensure that grm_send_product_info does not let count go below 0
---------------------------------------------------------------*/

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/
#define GRM_PRODUCT_NUMBER_STR_LEN          (13)
#define GRM_PRODUCT_INFO_SUMMARY_STR_LEN    (31)

/*------------------------------------------------------
Since dynamic memory is not available,
declare the number of region records used in the
product information structure.
------------------------------------------------------*/
#define GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT                                                                  \
              1 /* system region */                                                                         \
            /* sonar/cypress chip */                                                                        \
            + ((SYC_CYPRESS_SONAR_SUPPORT == TRUE)?1:0)    \
            + 0 /* NOTE: ADD 1 for each additional region */

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/
typedef uint32 GRM_inventory_attr_type; enum
    {
    /*------------------------------------------------------
    Bit set if the region has been erased.
    ------------------------------------------------------*/
    GRM_INVENTORY_ATTR_ERASED               = setbit( 0 ),

    /*------------------------------------------------------
    Bit set if the region can be removed (e.g. a data card).
    ------------------------------------------------------*/
    GRM_INVENTORY_ATTR_REMOVABLE            = setbit( 1 ),

    /*------------------------------------------------------
    Bit set if the region, if removable, has been removed
    from the device.
    ------------------------------------------------------*/
    GRM_INVENTORY_ATTR_REMOVED              = setbit( 2 ),

    /*------------------------------------------------------
    Bit set if the region is updateable by the user,
    (e.g. a software region).  This is different from a
    programmable region such as a map region programmable
    by Map Source.
    ------------------------------------------------------*/
    GRM_INVENTORY_ATTR_USER_UPDATEABLE      = setbit( 3 ),

    /*------------------------------------------------------
    Bit set if the region is not ready to report its
    information.  This could happen with a media that
    requires extra time to boot up (e.g. hard drives).
    ------------------------------------------------------*/
    GRM_INVENTORY_ATTR_IN_PROGRESS          = setbit( 4 ),

    GRM_INVENTORY_ATTR_DEFAULT              = 0
    };  /* GRM_inventory_attr_type */

typedef struct
    {
    uint16              vrsn_nmbr;
    HWM_data_rgn_type   rgn_id;
    uint8               reserved;
    } GRM_rgn_rcrd_summary_type;

typedef struct
    {
    tchr                        product_name[GRM_PRODUCT_INFO_SUMMARY_STR_LEN + 1];
    GRM_product_nmbr_u16        product_nmbr;
    uint16                      rgn_rcrd_count;
    GRM_rgn_rcrd_summary_type   rgns[GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT];
    } GRM_product_info_summary_type;

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
#define GRM_calc_product_info_size(_rgn_rcrd_count) (sizeof(GRM_product_info_summary_type) + (maxval32(1, (_rgn_rcrd_count)) - 1) * sizeof(GRM_rgn_rcrd_summary_type))

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

void GRM_send_product_info
    (
    IOP_route_type    * const route
    );

#endif /* GRM_PUB_PRODUCT_INFO_H */

