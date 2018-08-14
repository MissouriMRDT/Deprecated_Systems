/*********************************************************************
*
*   MODULE NAME:
*       GRM_init - System Constants
*
*   DESCRIPTION:
*       GRM_init provides the space allocation for commonly used
*       constants within the system.
*
*   PUBLIC PROCEDURES:
*       Name                        Title
*       -----------------------     --------------------------------------
*       GRM_get_build_description   Get Software Build Description
*       GRM_get_product_string      Get Product Description
*       GRM_get_version_string      Get Version Description
*       GRM_get_model_version_stringGet Model Version Description
*
*   PRIVATE PROCEDURES:
*       Name                        Title
*       -----------------------     --------------------------------------
*
*   LOCAL PROCEDURES:
*       Name                        Title
*       -----------------------     --------------------------------------
*
*
*   Copyright 2000-2009 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*
*********************************************************************/

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "UTL_pub.h"
#include "HWM_pwr_prj.h"
#include <String.h>

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/
static uint8 product_str_temp[]   = PRODUCT_STR_RUDDER_ANGLE;
static uint8 product_str_heading[]    = PRODUCT_STR_ENGINE_TILT;

static uint8 build_desc_temp[]    = GRM_BUILD_DESCRIPTION_RUDDER_ANGLE;
static uint8 build_desc_heading[]     = GRM_BUILD_DESCRIPTION_ENGINE_TILT;

static uint8  version_str[]               = VERSION_STR;
static uint8  model_version_str[]         = MODEL_VERSION_STR;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/


/*********************************************************************
*
*   PROCEDURE NAME:
*       GRM_get_build_description - Get Software Build Description
*
*   DESCRIPTION:
*       Fills a string with the build description.
*
*********************************************************************/

void GRM_get_build_description
    (
    tchr        * const string_ptr
    )
{
/*----------------------------------------------------------
Assign an adapter specific string based on the Adapter Type.
----------------------------------------------------------*/
switch( HWM_get_sensor_type() )
    {
    case TEMPERATURE_SENSOR:
        memcpy( ( uint8 * )string_ptr, ( uint8 * )build_desc_temp, GRM_BUILD_DESCRIPTION_SIZE );
        break;

    case HEADING_SENSOR:
    	memcpy( ( uint8 * )string_ptr, ( uint8 * )build_desc_heading, GRM_BUILD_DESCRIPTION_SIZE );
        break;

    default:
        UTL_assert_always( UTL_FILE_GRM_INIT );
        break;
    }

}   /* GRM_get_build_description() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       GRM_get_product_string - Get Product Description
*
*   DESCRIPTION:
*       Fills a string with the build description.
*
*********************************************************************/

void GRM_get_product_string
    (
    tchr        * const string_ptr
    )
{

/*----------------------------------------------------------
Assign an adapter specific string based on the Adapter Type.
----------------------------------------------------------*/
switch( HWM_get_sensor_type() )
    {
    case TEMPERATURE_SENSOR:
        memcpy( ( uint8 * )string_ptr, ( uint8 * )product_str_temp, PRODUCT_STR_SIZE );
        break;

    case HEADING_SENSOR:
    	memcpy( ( uint8 * )string_ptr, ( uint8 * )product_str_heading, PRODUCT_STR_SIZE );
        break;

    default:
        UTL_assert_always( UTL_FILE_GRM_INIT );
        break;
    }
}   /* GRM_get_product_string() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       GRM_get_version_string - Get Version Description
*
*   DESCRIPTION:
*       Fills a string with the version number.
*
*********************************************************************/

void GRM_get_version_string
    (
    tchr        * const string_ptr
    )
{

memcpy( ( uint8 * )string_ptr, ( uint8 * )version_str, VERSION_STR_SIZE );

}   /* GRM_get_version_string() */

/*********************************************************************
*
*   PROCEDURE NAME:
*       GRM_get_model_version_string - Get Hardware Model Version
*
*   DESCRIPTION:
*       Fills a string with the model version number.
*
*********************************************************************/

void GRM_get_model_version_string
    (
    tchr        * const string_ptr
    )
{

memcpy( ( uint8 * )string_ptr, ( uint8 * )model_version_str, MODEL_VERSION_STR_SIZE );

}   /* GRM_get_model_version_string() */
