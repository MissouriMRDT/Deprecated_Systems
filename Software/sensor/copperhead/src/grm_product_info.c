/*********************************************************************
*
*   MODULE NAME:
*
*       GRM_product_info.c - Product Information File
*
*   DESCRIPTION:
*       [module description]
*
* Copyright 2004-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#if(FALSE) /*Headers may need to be included later*/
#include "HWM_pub_rgn.h"
#include "NVM_pub.h"
#endif

#include "GRM_pub_prj.h"
#include "GRM_pub_product_info.h"
#include "SYC_pub_prj_s.h"
#include "IOP_pub.h"
#include "UTL_pub.h"
#include "grm_prv_product_info.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Bootblock has a fixed product information size since dynamic
memory is not available.
----------------------------------------------------------*/
enum
    {
    BB_PRODUCT_INFO_SIZE = GRM_calc_product_info_size( GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT )
    };

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
/*********************************************************************
*
*   PROCEDURE NAME:
*       GRM_send_product_info - send Product Information
*
*   DESCRIPTION:
*       This function sends the various regions supported by
*       the device and their relevant information.
*
*********************************************************************/
void GRM_send_product_info
    (
    IOP_route_type    * const route
    )
{
/*----------------------------------------------------------
Note this only works as-is because there is only 1 region
----------------------------------------------------------*/

/*----------------------------------------------------------
Variables
----------------------------------------------------------*/
GRM_product_info_summary_type   product_info;

#if ((GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT) > 1)
    uint8                   count;
#endif

/*-------------------------------------------------------------------
Ensure our product string size does not exceed the allocated memory
-------------------------------------------------------------------*/
UTL_compiler_assert(PRODUCT_STR_SIZE <= GRM_PRODUCT_INFO_SUMMARY_STR_LEN, UTL_FILE_GRM_PRODUCT_INFO);

/*----------------------------------------------------------
Need to have more than 0 record counts
----------------------------------------------------------*/
UTL_compiler_assert(GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT > 0, UTL_FILE_GRM_PRODUCT_INFO);

/*----------------------------------------------------------
Clear the product info memory
----------------------------------------------------------*/
memset( (uint8 *)(&product_info), (uint8)0x00, (uint16)sizeof(product_info) );

/*----------------------------------------------------------
Setup the non-region product info
----------------------------------------------------------*/
product_info.rgn_rcrd_count = GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT;
product_info.product_nmbr   = PRODUCT_NUM_DEC;

/*----------------------------------------------------------
Copy the product name
----------------------------------------------------------*/
GRM_get_product_string(product_info.product_name);

/*----------------------------------------------------------
System region is count #0.

Further regions count up from there.

Don't compile in count if there isn't more than 1 region.
System will be 0, and there won't be any other regions.
----------------------------------------------------------*/
#if ((GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT) > 1)
    count = (uint8)(GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT - 1);
#endif

#if (SYC_CYPRESS_SONAR_SUPPORT == TRUE)
    {
    /*------------------------------------------------------
    Check that we have at least 2 regions, one for this, one
    for the boot block.
    ------------------------------------------------------*/
    UTL_compiler_assert(GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT >= 2, UTL_FILE_GRM_PRODUCT_INFO);

    boolean         sonar_driver_present;
    uint16          sonar_vrsn;

    /*------------------------------------------------------
    Get the sonar driver info
    ------------------------------------------------------*/
    #if (_BBBLD == _ON)
        sonar_driver_present = HWM_sonar_driver_get_vrsn_bb(&sonar_vrsn);
    #else
        /* dummy vars */
        uint16 code_integrity;
        uint16 product_id;
        uint8  dash_nmbr;

        sonar_driver_present = HWM_sonar_driver_get_vrsn(&sonar_vrsn, &code_integrity, &product_id, &dash_nmbr);
    #endif

    /*------------------------------------------------------
    Fill in the sonar driver version.
    ------------------------------------------------------*/
    if( sonar_driver_present == TRUE )
        {
        product_info.rgns[ count ].vrsn_nmbr = sonar_vrsn;
        }
    else
        {
        /*--------------------------------------------------
        No sonar driver, so send 0 for the version.
        --------------------------------------------------*/
        product_info.rgns[ count ].vrsn_nmbr = 0;
        }

    product_info.rgns[ count ].rgn_id = HWM_RGN_SONAR_DRIVER;

    --count;

    /*------------------------------------------------------
    Check for array out of bounds.
    ------------------------------------------------------*/
    UTL_assert(count < GRM_PRODUCT_INFO_BB_RGN_RCRD_COUNT, UTL_FILE_GRM_PRODUCT_INFO);
    }
#endif

#if (FALSE /*_BBBLD == _ON*/)

    if( ( HWM_sys_present_chk() == FALSE ) || ( HWM_sys_chksum_test() == FALSE ) )
        {
        /*--------------------------------------------------
        If there is no system code present, or it is
        corrupt, our version number is effectively 0.
        --------------------------------------------------*/
        product_info.rgns[0].vrsn_nmbr = 0;
        }
    else
        {
        uint16 dummy_present;
        uint16 dummy_checksum;

        /*--------------------------------------------------
        Read the version number.
        --------------------------------------------------*/
        HWM_sys_info( &dummy_present, &(product_info.rgns[0].vrsn_nmbr), &dummy_checksum );
        }

#else /* _SYSBLD == _ON */

    /*------------------------------------------------------
    System build, we know the product info directly, and
    the system is already present, as we're running from it!
    ------------------------------------------------------*/
    product_info.rgns[0].vrsn_nmbr = VERSION_NUM;

#endif

/*----------------------------------------------------------
System code
----------------------------------------------------------*/
product_info.rgns[0].rgn_id = HWM_RGN_SYS_CODE;

/*----------------------------------------------------------
Send product information
----------------------------------------------------------*/
IOP_inst_route(IOP_PRODUCT_INFO_SUMMARY, (uint8 *)&product_info, sizeof(product_info), route);

} /* GRM_send_product_info() */
