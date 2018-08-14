/*********************************************************************
*
*   HEADER NAME:
*       HWM_pub_rgn_defn.h - Hardware Manager Public Region Definition
*                            Declarations
*
* Copyright 2001-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

#if !defined _HWM_PUB_RGN_DEFN_H
#define _HWM_PUB_RGN_DEFN_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "GRM_pub.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/
typedef uint8 HWM_data_rgn_type; enum    /* data region type         */
    {
    /*-----------------------------------------------------------
    Do not change order, these are company standard values.
    -----------------------------------------------------------*/
    HWM_RGN_AVTN_DB             = 0,    /* aviation database (jepp)         */
    HWM_RGN_GCHART_BASE_MAP     = 1,    /* GChart basemap (marine)          */
    HWM_RGN_RESERVED_0          = 2,    /* reserved 0                       */
    HWM_RGN_BASE_MAP            = 3,    /* basemap (GMap)                   */
    HWM_RGN_SYS_CODE_SYS_OFST   = 4,    /* system code (offset from sys rom)*/
    HWM_RGN_BB_CODE             = 5,    /* boot block code                  */
    HWM_RGN_BB_CODE_SYS_OFST    = 6,    /* boot block (offset from sys rom) */
    HWM_RGN_AVTN_DB_SYS_OFST    = 7,    /* aviation db (offset from sys rom)*/
    HWM_RGN_BASE_MAP_SYS_OFST   = 8,    /* basemap (offset from sys rom)    */
    HWM_RGN_FLASH_FILE          = 9,    /* Flash File Manager               */
    HWM_RGN_SUPP_MAP            = 10,   /* supplemental map (GMap)          */
    HWM_RGN_SUPP_MAP_SYS_OFST   = 11,   /* sup map (offset from sys rom)    */
    HWM_RGN_RAM_CODE            = 12,   /* code to run from ram             */
    HWM_RGN_NONVOL              = 13,   /* non-volatile data                */
    HWM_RGN_SYS_CODE            = 14,   /* system code                      */
    HWM_RGN_UNUSED              = 15,   /* unused (placeholder) region      */
    HWM_RGN_LOGO                = 16,   /* Logo image data                  */
    HWM_RGN_AUDIO               = 17,   /* Audio data region                */
    HWM_RGN_AUDIO_SYS_OFST      = 18,   /* Audio data offset from sys rom   */
    HWM_RGN_AUDIO2              = 19,   /* 2nd Audio data region            */
    HWM_RGN_AUDIO2_SYS_OFST     = 20,   /* Audio data offset from sys rom   */
    HWM_RGN_SUPP_MAP_1          = 21,   /* 2nd supplemental map rgn (GMap)  */
    HWM_RGN_SUPP_MAP_2          = 22,   /* 3rd supplemental map rgn (GMap)  */
    HWM_RGN_SUPP_MAP_3          = 23,   /* 4th supplemental map rgn (GMap)  */
    HWM_RGN_RESERVED_1          = 24,   /* reserved 1                       */
    HWM_RGN_RESERVED_2          = 25,   /* reserved 2                       */
    HWM_RGN_RESERVED_3          = 26,   /* reserved 3                       */
    HWM_RGN_EXTERNAL            = 27,   /* External Region (requires header)*/
    HWM_RGN_GRMN_DATA           = 28,   /* Garmin data/sw                   */
    HWM_RGN_CELL_ALIGN_DATA     = 29,   /* Cell phone alignment data        */
    HWM_RGN_SPEECH_DATA         = 30,   /* encoded speech                   */
    HWM_RGN_AVTN_DB_2           = 31,   /* 2nd aviation database (jepp)     */
    HWM_RGN_TRK_LOG             = 32,   /* Track log                        */
    HWM_RGN_TERRAIN_DB          = 33,   /* Terrain database                 */
    HWM_RGN_BIOS                = 34,   /* BIOS settings                    */
    HWM_RGN_UNUSED_35           = 35,   /* unused                           */
    HWM_RGN_CHART_DB            = 36,   /* Aviation chart database          */
    HWM_RGN_CHART_ARCHIVE       = 37,   /* Aviation chart archive           */
    HWM_RGN_CHRG_CODE           = 38,   /* charger code                     */
    HWM_RGN_OBSTACLE_DB         = 39,   /* Obstacle database                */
    HWM_RGN_AIRPORT_TERRAIN_DB  = 40,   /* Airport terrain database         */
    HWM_RGN_NVNAND              = 41,   /* NVM in NAND region               */
    HWM_RGN_STRK                = 42,   /* Saved Tracks                     */
    HWM_RGN_XLDR_CODE           = 43,   /* X-Loader (Bravo 2 NAND boot code)*/
    HWM_RGN_GFS_XFER            = 44,   /* Region for file transfer via rgn */
    HWM_RGN_ERROR_SHUTDOWN      = 45,   /* Store error shutdown reports     */
    HWM_RGN_CUSTOM_POI          = 46,   /* Custom POIs                      */
    HWM_RGN_LEXICAL             = 47,   /* Lexical package files            */
    HWM_RGN_FTL                 = 48,   /* Flash translation layer          */
    HWM_RGN_GMAP_PROM           = 49,   /* Pre-programmed Read Only Memory GMap (i.e. full coverage hard drive image) */
    HWM_RGN_GMAP_OEM            = 50,   /* OEM GMap                         */
    HWM_RGN_DEMO                = 51,   /* Demo Data                        */
    HWM_RGN_AUDIO3              = 52,   /* 3rd audio data region            */
    HWM_RGN_AUDIO4              = 53,   /* 4th audio data region            */
    HWM_RGN_AUDIO5              = 54,   /* 5th audio data region            */
    HWM_RGN_AUDIO6              = 55,   /* 6th audio data region            */
    HWM_RGN_AUDIO7              = 56,   /* 7th audio data region            */
    HWM_RGN_AUDIO8              = 57,   /* 8th audio data region            */
    HWM_RGN_AUDIO9              = 58,   /* 9th audio data region            */
    HWM_RGN_AUDIO10             = 59,   /* 10th audio data region           */
    HWM_RGN_AUDIO11             = 60,   /* 11th audio data region           */
    HWM_RGN_AUDIO12             = 61,   /* 12th audio data region           */
    HWM_RGN_AUDIO13             = 62,   /* 13th audio data region           */
    HWM_RGN_AUDIO14             = 63,   /* 14th audio data region           */
    HWM_RGN_AUDIO15             = 64,   /* 15th audio data region           */
    HWM_RGN_AUDIO16             = 65,   /* 16th audio data region           */
    HWM_RGN_AUDIO17             = 66,   /* 17th audio data region           */
    HWM_RGN_AUDIO18             = 67,   /* 18th audio data region           */
    HWM_RGN_BASE_MAP_ATL        = 68,   /* Atlantic Basemap region          */
    HWM_RGN_BASE_MAP_AMR        = 69,   /* Americas Basemap region          */
    HWM_RGN_BASE_MAP_PAC        = 70,   /* Pacific Basemap region           */
    HWM_RGN_DEMO_MAP            = 71,   /* Demonstration cartography region */
    HWM_RGN_FTL2                = 72,   /* 2nd Flash translation layer rgn  */
    HWM_RGN_SONAR_DRIVER        = 73,   /* Region for sonar driver code     */
    HWM_RGN_SW_UPDATE_1         = 74,   /* 1st Region for software updates  */
    HWM_RGN_SW_UPDATE_2         = 75,   /* 2nd Region for software updates  */
    HWM_RGN_GPI_OEM             = 76,   /* Custom POI OEM data region       */
    HWM_RGN_GMAP_PROM_1         = 77,   /* 2nd Pre-programmed Read Only Memory GMap */
    HWM_RGN_VEHICLE             = 78,   /* custom vehicle region            */
    HWM_RGN_AVTN_SUPP_DB        = 79,   /* Aviation supplemental database   */
    HWM_RGN_VIRTUAL             = 80,   /* Virtual region used for misc. data transfers */
    HWM_RGN_REMOTE_SW_SIRF_STARTER
                                = 81,   /* SiRF starter                     */
    HWM_RGN_REMOTE_SW_SIRF_BURNER
                                = 82,   /* SiRF burner                      */
    HWM_RGN_FS                  = 83,   /* Internal filesystem              */
    HWM_RGN_MBR                 = 84,   /* Master boot record               */
    HWM_RGN_SYS2_CODE           = 85,   /* system code part 2               */
    HWM_RGN_TEXT_LANG           = 86,   /* Current Text Language            */
    HWM_RGN_LOWPWR_CODE         = 87,   /* Low Power Mode Code              */
    HWM_RGN_DEMO_CARD           = 88,   /* Demo Card region                 */
    HWM_RGN_USER_CARD           = 89,   /* User Data on Card region         */
    HWM_RGN_SCM                 = 90,   /* Chinese security module          */
    HWM_RGN_NVNAND2             = 91,   /* Second NVM backing store region  */
    HWM_RGN_EE_SIRF_1DAY_DB     = 92,   /* SiRF one day extended ephemeris database */
    HWM_RGN_GMAP_TZ             = 93,   /* Timezone preprogrammed map       */

    HWM_RGN_NVBACKUP_PRIMARY    = 94,   /* Primary NVBACKUP region          */
    HWM_RGN_NVBACKUP_BACKUP     = 95,   /* Backup NVBACKUP region           */

    HWM_RGN_NONVOL2             = 96,   /* Second NVM region                */

    HWM_RGN_ASR                 = 97,   /* ASR data region                  */
    HWM_RGN_ASR_MAP             = 98,   /* ASR Map data region              */
    HWM_RGN_GMAP_3D             = 99,   /* 3d Building map image            */
    HWM_RGN_GMAP_3D_1           = 100,  /* Secondary 3d Building map image  */
    HWM_RGN_OEM_CONFIG          = 101,  /* OEM configuration                */
    HWM_RGN_ZIP_UPDT            = 102,  /* Zip Update Region                */

    HWM_RGN_DYNAMIC_MAPS        = 103,  /* Dynamic map content              */
    HWM_RGN_DYN_MAP_0           = 103,  /* Dynamic map name region 0        */
    HWM_RGN_DYN_MAP_1           = 104,  /* Dynamic map name region 1        */
    HWM_RGN_DYN_MAP_2           = 105,  /* Dynamic map name region 2        */
    HWM_RGN_DYN_MAP_3           = 106,  /* Dynamic map name region 3        */
    HWM_RGN_DYN_MAP_4           = 107,  /* Dynamic map name region 4        */
    HWM_RGN_DYN_MAP_5           = 108,  /* Dynamic map name region 5        */
    HWM_RGN_DYN_MAP_6           = 109,  /* Dynamic map name region 6        */
    HWM_RGN_DYN_MAP_7           = 110,  /* Dynamic map name region 7        */
    HWM_RGN_DYN_MAP_8           = 111,  /* Dynamic map name region 8        */
    HWM_RGN_DYN_MAP_9           = 112,  /* Dynamic map name region 9        */
    HWM_RGN_DYN_MAP_10          = 113,  /* Dynamic map name region 10       */
    HWM_RGN_DYN_MAP_11          = 114,  /* Dynamic map name region 11       */
    HWM_RGN_DYN_MAP_12          = 115,  /* Dynamic map name region 12       */
    HWM_RGN_DYN_MAP_13          = 116,  /* Dynamic map name region 13       */
    HWM_RGN_DYN_MAP_14          = 117,  /* Dynamic map name region 14       */
    HWM_RGN_DYN_MAP_15          = 118,  /* Dynamic map name region 15       */
    HWM_RGN_DYN_MAP_16          = 119,  /* Dynamic map name region 16       */
    HWM_RGN_DYN_MAP_17          = 120,  /* Dynamic map name region 17       */
    HWM_RGN_DYN_MAP_18          = 121,  /* Dynamic map name region 18       */
    HWM_RGN_DYN_MAP_19          = 122,  /* Dynamic map name region 19       */

    HWM_RGN_TEST_IMG            = 123,  /* Test Image region                */
    HWM_RGN_JCV                 = 124,  /* JCV region                       */

    HWM_RGN_AOPA_DB             = 125,  /* AOPA airport directory           */
    HWM_RGN_SAFETAXI_DB         = 126,  /* SafeTaxi airport diagram db      */

    HWM_RGN_IMAGE_RESOURCE      = 127,  /* System image resources           */
    HWM_RGN_GMAP_3D_1_2         = 128,  /* Second supplemental 3D map region*/

    HWM_RGN_ASR_MAP_DIR         = 129,  /* ASR Map data directory           */

    HWM_RGN_GSM_CONFIG          = 130,  /* GSM configuration                */

    HWM_NUM_RGN_DEFS,                   /* Count of regions in enumeration  */
    HWM_RGN_REMOTE_SW           = 245,  /* remote software region           */
    HWM_RGN_REMOTE_SW_SIRF      = 246,  /* remote software region for SIRF  */
    HWM_RGN_REMOTE_SW_GXM30     = 247,  /* remote software region for GXM30 */
    HWM_RGN_REMOTE_SW_GTM10     = 248,  /* remote software region for GTM10 */
    HWM_RGN_REMOTE_1            = 249,  /* remote region                    */
    HWM_RGN_REMOTE_2            = 250,  /* remote region                    */
    HWM_RGN_REMOTE_3            = 251,  /* remote region                    */
    HWM_RGN_REMOTE_4            = 252,  /* remote region                    */
    HWM_RGN_REMOTE_5            = 253,  /* remote region                    */
    HWM_RGN_REMOTE_6            = 254,  /* remote region                    */

    HWM_INVALID_RGN             = 255   /* invalid region specifier         */
    } /* HWM_data_rgn_type */;

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

#endif /* HWM_PUB_RGN_DEFN_H */

