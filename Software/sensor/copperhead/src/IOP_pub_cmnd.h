/*********************************************************************
*
*   HEADER NAME:
*       IOP_pub_cmnd.h - Input/Output Processing Public Declarations
*
* Copyright 2001-2015 by Garmin Ltd. or its subsidiaries.
*
*********************************************************************/

#ifndef _IOP_PUB_CMND_H
#define _IOP_PUB_CMND_H

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/
typedef uint16 IOP_cmnd_id_type; enum
    {
    /*------------------------------------------------------
    Do not change values, these are marine/handheld product
    standard values.
    ------------------------------------------------------*/

    IOP_ABORT_DOWN_LOAD                 =  0,   /* abort current down load                  */
    IOP_DOWN_LOAD_ALM                   =  1,   /* down load almanac                        */
    IOP_DOWN_LOAD_POSN                  =  2,   /* down load position                       */
    IOP_DOWN_LOAD_PRX                   =  3,   /* down load proximity waypoints            */
    IOP_DOWN_LOAD_RTE                   =  4,   /* down load routes                         */
    IOP_DOWN_LOAD_TIME                  =  5,   /* down load date/time                      */
    IOP_DOWN_LOAD_TRK                   =  6,   /* down load track log                      */
    IOP_DOWN_LOAD_WPT                   =  7,   /* down load waypoints                      */
    IOP_POWER_OFF                       =  8,   /* turn off the power                       */
    IOP_RECEIVER_OFF                    =  9,   /* turn off the receiver                    */
    IOP_RECEIVER_ON                     = 10,   /* turn off the receiver                    */
    IOP_RESET_CDP                       = 11,   /* reset CDP static variables               */

    /*------------------------------------------------------
    the following identifiers were added after initial GPS95
    production and are not in alphabetical order
    ------------------------------------------------------*/

    IOP_DL_JEPP_FLASH                   = 12,   /* down load jepp DB flash                  */
    IOP_ERASE_JEPP_FLASH                = 13,   /* erase jepp DB flash memory               */
    IOP_DOWN_LOAD_ID                    = 14,   /* down load unit identification            */
    IOP_DOWN_LOAD_CLK                   = 15,   /* down load clock drift                    */
    IOP_REINIT_RCV                      = 16,   /* reinitialize RCV module                  */
    IOP_DOWN_LOAD_VOLTAGE               = 17,   /* down load voltage data                   */
    IOP_TEST_FLASH                      = 18,   /* perform flash card test                  */
    IOP_EXT_VPP_ON                      = 19,   /* turn on external VPP voltage             */
    IOP_EXT_VPP_OFF                     = 20,   /* turn off external VPP                    */
    IOP_BB_VPP_ON                       = 21,   /* turn on boot block VPP                   */
    IOP_BB_VPP_OFF                      = 22,   /* turn off boot block VPP                  */
    IOP_STORE_COM_CFG                   = 23,   /* store COM configuration data             */
    IOP_DSBL_COM_XMTR                   = 24,   /* disable COM transmitter                  */
    IOP_ENBL_COM_XMTR                   = 25,   /* enable COM transmitter                   */
    IOP_WX_ALRT_TEST                    = 26,   /* weather alert tone test                  */
    IOP_DOWN_LOAD_COM_CFG               = 27,   /* down load COM config data                */
    IOP_DOWN_LOAD_NVOL                  = 28,   /* down load nonvol data                    */
    IOP_DOWN_LOAD_FNVOL                 = 29,   /* down load far nonvol data                */
    IOP_COM_RCVR_OFF                    = 30,   /* turn off the com receiver                */
    IOP_COM_RCVR_ON                     = 31,   /* turn on  the com receiver                */
    IOP_DOWN_LOAD_SCREEN                = 32,   /* screen dump                              */
    IOP_DL_BMAP_FLASH                   = 33,   /* down load basemap flash                  */
    IOP_ERASE_BMAP_FLASH                = 34,   /* erase basemap flash                      */
    IOP_DB_VPP_ON                       = 35,   /* turn on database VPP                     */
    IOP_DB_VPP_OFF                      = 36,   /* turn off database VPP                    */
    IOP_COM_FRMT_GENIE                  = 37,   /* Switch COM format to GENIE               */
    IOP_COM_FRMT_NMEA                   = 38,   /* Switch COM format to NMEA                */
    IOP_CLR_NONVOL_UNPROTECTED_ONLY     = 39,   /* clear unprotected nonvol                 */
    IOP_ENUM_AVAILABLE_1                = 40,   /* available to be re-assigned              */
    IOP_CLEAR_STACK_INFO                = 41,   /* clear stack usage info                   */
    IOP_DOWN_LOAD_SHUTDOWN_INFO         = 42,   /* down load shutdown info                  */
    IOP_DOWN_LOAD_STACKS_INFO           = 43,   /* down load stack usage info               */
    IOP_ERASE_RAM                       = 44,   /* clear all ram memory & reset             */
    IOP_DOWN_LOAD_SWPT                  = 45,   /* down load symbol waypoints               */
    IOP_DOWN_LOAD_CEL_TUNE              = 46,   /* down load cell tuning data               */
    IOP_CLONE_ALL                       = 47,   /* down load all data                       */
    IOP_CLONE_CFG                       = 48,   /* down load configuration                  */
    IOP_PVT_DATA_ON                     = 49,   /* turn on PVT CPO data                     */
    IOP_PVT_DATA_OFF                    = 50,   /* turn off PVT CPO data                    */
    IOP_CEL_INT_MIC                     = 51,   /* enable internal microphone               */
    IOP_CEL_EXT_MIC                     = 52,   /* enable external microphone               */
    IOP_CLR_ALL_NONVOL_INCL_PROTECTED   = 53,   /* clear all nonvol including protected     */
    IOP_DL_POSN_PHONE_NMBR              = 54,   /* down load position/phone nmbr            */
    IOP_ERASE_SHUTDOWN_TBL              = 55,   /* erase shutdown table                     */
    IOP_DOWN_LOAD_PH_NMBR               = 56,   /* down load phone number                   */
    IOP_DL_BAUD_CAPS                    = 57,   /* down load baud capabilities              */
    IOP_ACK_PING                        = 58,   /* acknowledge ping                         */
    IOP_ENBL_FIRST_ASSIST               = 59,   /* enable prot. 1 emerg. feature            */
    IOP_DSBL_FIRST_ASSIST               = 60,   /* disable prot. 1 emerg feature            */
    IOP_UNLOCK_IO                       = 61,   /* unlock for next iop command              */
    IOP_DOWN_LOAD_FFM                   = 62,   /* down load flash file mngr mem            */
    IOP_DL_GMAP_RGN_INFO                = 63,   /* down load Gmap region info               */
    IOP_START_CMPS_CAL                  = 64,   /* start compass calibration                */
    IOP_STOP_CMPS_CAL                   = 65,   /* start compass calibration                */
    IOP_DOWN_LOAD_CMPS_CAL              = 66,   /* down load compass cal data               */
    IOP_DOWN_LOAD_BARO_CAL              = 67,   /* down load compass cal data               */
    IOP_USER_CNTRST_ON                  = 68,   /* user contrast mode                       */
    IOP_HW_CNTRST_ON                    = 69,   /* hardware contrast on                     */
    IOP_DOWN_LOAD_DTMGRD                = 70,   /* down load detum and grid data            */
    IOP_NV_PRG_TIME_TST                 = 71,   /* NV prg time test                         */
    IOP_DL_FLASH_ID                     = 72,   /* down load flash ID                       */
    IOP_DL_GOLFLOGIX_ID                 = 73,   /* down load GolfLogix data                 */
    IOP_TEST_CAN                        = 74,   /* send CAN test message                    */
    IOP_PRTL_DSPL_MODE                  = 75,   /* enter partial display mode               */
    IOP_PDA_TRNSFR_CONFIG               = 76,   /* copy data section list to host           */
    IOP_PDA_END_SYNC                    = 77,   /* end sync of the current section          */
    IOP_PDA_BEGIN_SYNC_SESSION          = 78,   /* tell the PC to begin sync session        */
    IOP_PDA_END_SYNC_SESSION            = 79,   /* end the sync session                     */
    IOP_ABORT_T001                      = 80,   /* abort transport layer                    */
    IOP_RQST_COMM_STATS                 = 81,   /* request comm stats                       */
    IOP_RESET_COMM_STATS                = 82,   /* reset comm stats                         */
    IOP_PREP_POWER_OFF                  = 83,   /* prepare to power down                    */
    IOP_NAV_MNTR_DATA_ON                = 84,   /* NAV monitor data on                      */
    IOP_NAV_MNTR_DATA_OFF               = 85,   /* NAV monitor data off                     */
    IOP_TRANSFER_TO_BB                  = 86,   /* Transfer to boot block                   */
    IOP_COM_VOICE_TX                    = 87,   /* RFC voice transmit                       */
    IOP_COM_TONE_TX                     = 88,   /* RFC tone transmit                        */
    IOP_COM_DATA_TX                     = 89,   /* RFC data transmit                        */
    IOP_COM_STOP_TX                     = 90,   /* RFC stop transmit                        */
    IOP_DL_RGN_SUPPORT                  = 91,   /* Download Region Support Info             */
    IOP_DOWN_LOAD_FLIGHT                = 92,   /* Download flight log                      */
    IOP_DOWN_LOAD_EPH                   = 93,   /* Download Ephemeris Data                  */
    IOP_TEST_EEPROM                     = 94,   /* test EEPROM                              */
    IOP_ENABLE_TIS                      = 95,   /* Enable TIS on transponder                */
    IOP_DISABLE_TIS                     = 96,   /* Disable TIS on transponder               */
    IOP_REQUEST_VIDEO                   = 97,   /* Request Video Display Resource           */
    IOP_RELEASE_VIDEO                   = 98,   /* Done Using Video Resource                */
    IOP_REQUEST_AUDIO                   = 99,   /* Request Audio (out) Resource             */
    IOP_RELEASE_AUDIO                   = 100,  /* Done Using Audio (out) Resource          */
    IOP_COM_FRMT_QCOM_DIAG              = 101,  /* Switch COM format to QCOM_DIAG           */
    IOP_RFASIC_RQST_PARMS               = 102,  /* Request RFASIC information               */
    IOP_BEGIN_GYRO_TEST                 = 103,  /* Begin the gyro test                      */
    IOP_BEGIN_TCHSCRN_CAL               = 104,  /* Begin touch screen calibration           */
    IOP_GYRO_OUTPUT_ON                  = 105,  /* Gyro output on                           */
    IOP_GYRO_OUTPUT_OFF                 = 106,  /* Gyro output off                          */
    IOP_WAAS_ON                         = 107,  /* Turn on WAAS                             */
    IOP_WAAS_OFF                        = 108,  /* Turn off WAAS                            */
    IOP_WAAS_RQST_STAT                  = 109,  /* Request WAAS status                      */
    IOP_RCV_DATA_ON                     = 110,  /* turn on RCV CPO data                     */
    IOP_RCV_DATA_OFF                    = 111,  /* turn off RCV CPO data                    */
    IOP_DOWN_LOAD_UNLOCK                = 112,  /* Down Load Map Unlock Codes               */
    IOP_DL_CRADLE_ID                    = 113,  /* Down Load Cradle ID                      */
    IOP_DL_CRADLE_ID_VOLT               = 114,  /* Down Load Cradle ID voltage              */
    IOP_DL_GPS_ANT_STATUS               = 115,  /* Down Load GPS Antenna Status             */
    IOP_DEL_TEMP_TBL                    = 116,  /* Delete Clock Drift Temp Table from NonVol*/
    IOP_DL_LAP                          = 117,  /* Download lap (Forerunner)                */
    IOP_REQ_SYC_MODE                    = 118,  /* Request SYC Mode                         */
    IOP_PAVG_ON                         = 119,  /* turn on position averaging               */
    IOP_PAVG_OFF                        = 120,  /* turn off position averaging              */
    IOP_DOWN_LOAD_WPT_CAT               = 121,  /* Down Load waypoint category names        */
    IOP_CHANGE_PRIMARY_PORT             = 122,  /* Change primary port to port that rx cmnd */
    IOP_RELEASE_PORT                    = 123,  /* Kill IOP & release serial port resource  */
    IOP_DISK_HTR_ON                     = 124,  /* turn on disk drive heater                */
    IOP_DISK_HTR_OFF                    = 125,  /* turn off disk drive heater               */
    IOP_PVT_REMOTE_ON                   = 126,  /* turn on remote PVT data reporting        */
    IOP_PVT_REMOTE_OFF                  = 127,  /* turn off remote PVT data reporting       */
    IOP_TEST_GLSI                       = 128,  /* Specific command to test GLSI            */
    IOP_TEST_RAM                        = 129,  /* Specific command to test RAM             */
    IOP_TEST_ROM                        = 130,  /* Specific command to test ROM             */
    IOP_DOWN_LOAD_BIAS                  = 131,  /* Down load gyro bias data                 */
    IOP_DEMO_ENABLE                     = 132,  /* Enables the demo                         */
    IOP_DEMO_DISABLE                    = 133,  /* Disables the demo                        */
    IOP_BATT_CHRGR_ENABLE               = 134,  /* Enables the battery charger              */
    IOP_BATT_CHRGR_DISABLE              = 135,  /* Disables the battery charger             */
    IOP_DOWN_LOAD_REG_CODE              = 136,  /* Download Registration Code               */
    IOP_ADAPTIVE_TX_ON                  = 137,  /* Turn on adaptive transmit                */
    IOP_ADAPTIVE_TX_OFF                 = 138,  /* Turn off adaptive transmit               */
    IOP_AUTO_SHUTOFF_ON                 = 139,  /* Turn on automatic shutoff                */
    IOP_AUTO_SHUTOFF_OFF                = 140,  /* Turn off automatic shutoff               */
    IOP_ADAPTIVE_TX_RQST_STATE          = 141,  /* State of adaptive transmit               */
    IOP_AUTO_SHUTOFF_RQST_STATE         = 142,  /* State of auto shutoff                    */
    IOP_EXT_PWR_UP_ON                   = 143,  /* Turn on external power-up                */
    IOP_EXT_PWR_UP_OFF                  = 144,  /* Turn off external power-up               */
    IOP_EXT_PWR_UP_RQST_STATE           = 145,  /* Request state of external power-up       */
    IOP_PPS_AUTO_OFF_ON                 = 146,  /* Turn on PPS Auto Off mode                */
    IOP_PPS_AUTO_OFF_OFF                = 147,  /* Turn off PPS Auto Off mode               */
    IOP_PPS_AUTO_OFF_RQST_STATE         = 148,  /* Request state of PPS Auto Off mode       */
    IOP_TRANSFER_TO_SYS                 = 149,  /* Transfer to system                       */
    IOP_NAND_BLOCK_MAP_INFO_RQST        = 150,  /* Request NAND block map information       */
    IOP_REQ_PRODUCT_INVENTORY           = 151,  /* Request Product Inventory                */
    IOP_GPS_RESET_NO_FIRST_FIX          = 152,  /* Reset the gps no first fix flag          */
    IOP_ENBL_GPS_BUDDY_PROTOCOL         = 153,
    IOP_IRDA_AUX_TOGGLE                 = 154,  /* Toggles IRDA/AUX Select GPIO             */
    IOP_GARMIN_LOCK_SCR_LCTN_GARMIN     = 155,  /* Garmin Lock Set Secure Locations to Garmin */
    IOP_CLR_EPH                         = 156,  /* erase all ephemeris data                 */
    IOP_CLR_ALM                         = 157,  /* erase all almanac data                   */
    IOP_TRANSFER_TO_FLASH               = 158,  /* MSN Direct Band Specific                 */
    IOP_GET_MSN_DIRECT_REG_KEY          = 159,  /* Get MSN Direct Registration Key          */
    IOP_TEST_GRAPHICS_RAM               = 160,  /* Start Graphics RAM Test                  */
    IOP_ENABLE_PRODUCT_INVENTORY_TEST   = 161,  /* Enable Product Inventory Test            */
    IOP_DISABLE_GARMIN_LOCK             = 162,  /* Disable Garmin Lock until reset by user  */
    IOP_REQ_PRODUCT_INFO                = 163,  /* Request GRM_product_info_type            */
    IOP_REQ_PRODUCT_INFO_SUMMARY        = 164,  /* Request GRM_product_info_summary_type    */
    IOP_REQ_ASSERT_DATA                 = 165,  /* Request the assert data from EEPROM      */
    IOP_CLEAR_UNLOCK_CODES              = 166,  /* Clears all unlock codes in the unit      */
    IOP_REQ_TAIWAN_DATA                 = 167,  /* Request data that Taiwan has stored      */
    IOP_DOWN_LOAD_PACKED_EPH            = 168,  /* Download Packed Ephemeris Data           */
    IOP_DOWN_LOAD_SW_UNLOCK             = 169,  /* Down Load Software Unlock Codes          */
    IOP_AUTO_BACKLIGHT_OFF              = 170,  /* Turn off automatic backlight             */
    IOP_AUTO_BACKLIGHT_ON               = 171,  /* Turn on automatic backlight              */
    IOP_REQ_PRODUCT_INVENTORY_V2        = 172,  /* Request Product Inventory                */
    IOP_RESET_SNSR                      = 173,  /* Reset all sensors (cmps, baro). Use for
                                                   testing sensor borads in Taiwan          */
    IOP_REBOOT                          = 174,  /* Reboots the unit                         */
    IOP_TEST_FAN                        = 175,  /* Start Fan Test                           */

    /*------------------------------------------------------
    IOP commands to turn on/off the satellite data request
    (IOP_RCV_MNTR_BIT)
    ------------------------------------------------------*/
    IOP_RCV_MNTR_ON                     = 176,
    IOP_RCV_MNTR_OFF                    = 177,
    IOP_PING                            = 178,  /* Generic PING command                     */

    /*------------------------------------------------------
    Request Unit Type
    ------------------------------------------------------*/
    IOP_UNIT_TYPE_RQST                  = 179,

    /*------------------------------------------------------
    Get accessory's current limit value ( mA )
    ------------------------------------------------------*/
    IOP_GET_ILIMIT_DATA                 =193,

    /*------------------------------------------------------
    Sonar Command ID's
    ------------------------------------------------------*/
    IOP_SONAR_CMND_START                = 200,

    IOP_SONAR_RQST_RCVR_PARMS           = 201,  /* request sonar receiver parameters        */
    IOP_SONAR_TEST_REMOTE_SONAR         = 202,  /* enter remote sonar test mode             */

    IOP_SONAR_CMND_END                  = 299,

    /*------------------------------------------------------
    XM Radio Command IDs
    ------------------------------------------------------*/
    IOP_XM_CMND_START                   = 300,

    IOP_XM_CMND_CBM_LOG_ON              = 300,
    IOP_XM_CMND_CBM_LOG_OFF             = 301,
    IOP_XM_CMND_CBM_REQ_DIAG_INFO       = 302,
    IOP_XM_CMND_REQ_START_TEST          = 303,
    IOP_XM_CMND_REQ_STOP_TEST           = 304,
    IOP_XM_CMND_REQ_CONTACT_MADE        = 305,
    IOP_XM_CMND_REQ_SGNL_QLTY           = 306,
    IOP_XM_CMND_REQ_ANTENNA_STATUS      = 307,
    IOP_XM_CMND_REQ_EXTERNAL_ID_ADC     = 308,

    IOP_XM_CMND_AUDIO_MUTE              = 310,
    IOP_XM_CMND_AUDIO_PLAY              = 311,
    IOP_XM_CMND_AUDIO_DEL_ALL_FAVS      = 312,
    IOP_XM_CMND_REQ_CHANNEL_LIST        = 313,
    IOP_XM_CMND_REQ_RADIO_ID            = 314,
    IOP_XM_CMND_REQ_FAVORITE_BANDS      = 315,
    IOP_XM_CMND_REQ_CHANNEL_LABEL_LIST  = 316,

    IOP_XM_CMND_MODULE_CONFIG_CHECK     = 320,
    IOP_XM_CMND_VERSION_CHECK           = 321,
    IOP_XM_CMND_RCVR_RESTORE_DEFAULTS   = 322,

    IOP_XM_CMND_END                     = 349,

    /*------------------------------------------------------
    XM/Wx Weather Command IDs
    ------------------------------------------------------*/
    IOP_WX_CMND_START                   = 350,

    IOP_WX_CMND_REQ_STATS               = 350,
    IOP_WX_LOG_ON                       = 351,
    IOP_WX_LOG_OFF                      = 352,
    IOP_WX_GSM_STANDBY                  = 353,
    IOP_WX_CMND_REQ_PRDCT_LIST          = 354,

    IOP_WX_CMND_END                     = 374,

    /*------------------------------------------------------
    RDS Command IDs
    ------------------------------------------------------*/
    IOP_RDS_CMND_START                  = 375,

    IOP_RDS_CMND_LOG_ON                 = 376,
    IOP_RDS_CMND_LOG_OFF                = 377,
    IOP_RDS_CLEAR_FM_TBL                = 378,
    IOP_RDS_INST_CONTACT_MADE_REQ       = 379,
    IOP_RDS_CMND_RST_CONTACT_MADE       = 380,

    IOP_RDS_CMND_READ_GTM_ESN           = 398,
    IOP_RDS_CMND_PROGRAM_GTM_ESN        = 399,
    IOP_RDS_CMND_END                    = 399,

    /*------------------------------------------------------
    Bluetooth Command IDs (More BT commands at 707)
    ------------------------------------------------------*/
    IOP_BT_CMND_START                   = 430,

    IOP_BT_GET_BDADDR                   = 430,  /* Get the Bluetooth device address         */
    IOP_BT_POWER_ON                     = 431,  /* Power on Bluetooth hardware              */
    IOP_BT_POWER_OFF                    = 432,  /* Power off Bluetooth hardware             */
    IOP_BT_SET_TEST_MODE                = 433,  /* Sets the Bluetooth device into test mode.*/
    IOP_BT_SET_TEST_DEVICE              = 434,  /* Sets the unit as a test device, see Parrot.rme 1.112.*/
    IOP_BT_SET_REMOTE_DEVICE            = 435,  /* Sets the unit as a remote device, see Parrot.rme 1.112.*/
    IOP_BT_NORMAL_DEVICE                = 436,  /* Sets the unit as a normal device, see Parrot.rme 1.112.   */
    IOP_BT_RESET_DEVICE                 = 437,  /* Resets the unit, see Parrot.rme 1.112.   */
    IOP_BT_START_LOOPBACK_TEST          = 438,  /* Starts a BT loopback test, see Parrot.rme 1.113.*/
    IOP_BT_STOP_LOOPBACK_TEST           = 439,  /* Stops a BT loopback test, see Parrot.rme 1.113.*/
    IOP_BT_START_MIC_LOOPBACK_TEST      = 440,  /* Starts a microphone loopback test, see Parrot.rme 1.112.*/
    IOP_BT_STOP_MIC_LOOPBACK_TEST       = 441,  /* Stops a microphone loopback test, see Parrot.rme 1.112.*/
    IOP_BT_ANSWER_INCOMING_CALL         = 442,  /* Answers an incoming call.                */
    IOP_BT_AUDIO_ON                     = 443,  /* Enables audio management in Bluetooth.   */
    IOP_BT_AUDIO_OFF                    = 444,  /* Disables audio management in Bluetooth.  */
    IOP_BT_SET_REMOTE_DEVICE_ADDR_TEST  = 445,  /* Sets the unit as a remote device w/o changing the BT addr. */
    IOP_BT_GET_TEST_MODE                = 446,  /* Gets the state of Bluetooth test mode    */
    IOP_BT_DSBL_AUTHENTICATION          = 447,  /* Disables authentication on the BT device */
    IOP_BT_SWITCH_SERVER                = 448,  /* Switch Open Server on unit               */

    IOP_BT_CMND_END                     = 449,

    /*------------------------------------------------------
    Fitness Product Command IDs
    ------------------------------------------------------*/
    IOP_DOWN_LOAD_RUN                   = 450,
    IOP_DOWN_LOAD_WRKT                  = 451,
    IOP_DOWN_LOAD_WRKT_DATE             = 452,
    IOP_DOWN_LOAD_PRFL                  = 453,
    IOP_DOWN_LOAD_WRKT_LMT              = 454,

    /*------------------------------------------------------
    Remote Sensor Command IDs
    ------------------------------------------------------*/
    IOP_SYC_RPT_NEED_INIT               = 455,  /* Report Needed Init                       */
    IOP_RESET_SENSOR                    = 456,  /* reset search id on ANT sensors           */

    /*------------------------------------------------------
    ActiveSync Command IDs
    ------------------------------------------------------*/
    IOP_AS_CMND_START                   = 475,

    IOP_AS_REQ_USER_CNFG                = 477,
    IOP_AS_USER_CNFG_END                = 478,

    IOP_AS_CMND_END                     = 499,

    /*------------------------------------------------------
    Read hard drive temperature sensor
    ------------------------------------------------------*/
    IOP_READ_HD_TEMP                    = 500,

    /*------------------------------------------------------
    Set the state of the GPS PPS line
    ------------------------------------------------------*/
    IOP_PPS_NORMAL                      = 501,  /* Set PPS line to normal operation         */
    IOP_PPS_FORCE_HI                    = 502,  /* Force PPS line high                      */
    IOP_PPS_FORCE_LO                    = 503,  /* Force PPS line high                      */

    /*------------------------------------------------------
    Remote GPS Command IDs
    ------------------------------------------------------*/
    IOP_RMT_GPS_CMND_START              = 510,

    IOP_RMT_GPS_INST_ON                 = 510,  /* turn on SiRF inst out Garmin port        */
    IOP_RMT_GPS_INST_OFF                = 511,  /* turn off SiRF inst out Garmin port       */
    IOP_RMT_GPS_NRML_MODE               = 512,  /* set remote gps to normal operating mode  */
    IOP_RMT_GPS_TEST_MODE               = 513,  /* set remote gps to test operating mode    */
    IOP_RMT_GPS_COLD_START              = 514,  /* clear ephemeris and almanac data         */
    IOP_RMT_GPS_FCTRY_RESET             = 515,  /* do a factory reset on remote GPS device  */
    IOP_RMT_GPS_WARM_START              = 516,  /* do a warm start on the remote GPS device */
    IOP_RMT_GPS_ENBL_OUTPUT             = 517,  /* enable output of remote gps messages     */
    IOP_RMT_GPS_DSBL_OUTPUT             = 518,  /* disable output of remote gps messages    */
    IOP_RMT_GPS_INVALID_POSN            = 519,  /* invalidate position of remote GPS        */
    IOP_RMT_GPS_HOT_START               = 520,  /* do a hot start on remote GPS device      */
    IOP_RMT_GPS_ST_RSVD1                = 521,  /*  */
    IOP_RMT_GPS_BRDCST_UPDT_ON          = 522,  /* turn real ephemeris update on            */
    IOP_RMT_GPS_BRDCST_UPDT_OFF         = 523,  /* turn real ephemeris update off           */
    IOP_RMT_GPS_PRED_EPH_ON             = 524,  /* turn predicted ephemeris on              */
    IOP_RMT_GPS_PRED_EPH_OFF            = 525,  /* turn predicted ephemeris off             */
    IOP_RMT_GPS_ST_RSVD6                = 526,  /*  */
    IOP_RMT_GPS_ST_RSVD7                = 527,  /*  */
    IOP_RMT_GPS_ST_RSVD8                = 528,  /*  */
    IOP_RMT_GPS_ST_RSVD9                = 529,  /*  */
    IOP_RMT_GPS_ST_RSVD10               = 530,  /*  */
    IOP_RMT_GPS_ST_RSVD11               = 531,  /*  */
    IOP_RMT_GPS_ST_RSVD12               = 532,  /*  */
    IOP_RMT_GPS_ST_RSVD13               = 533,  /*  */
    IOP_RMT_GPS_ST_RSVD14               = 534,  /*  */
    IOP_RMT_GPS_ST_RSVD15               = 535,  /*  */
    IOP_RMT_GPS_ST_RSVD16               = 536,  /*  */

    IOP_RMT_GPS_ST_JAMMING_TEST_ON      = 537,  /*  */
    IOP_RMT_GPS_ST_JAMMING_TEST_OFF     = 538,  /*  */

    IOP_RMT_GPS_PRDC_WARM_START_TEST_ON = 539,  /*  */
    IOP_RMT_GPS_PRDC_WARM_START_TEST_OFF= 540,  /*  */

    IOP_RMT_GPS_PGPS_HOT_PGPS_ONLY      = 541,  /*  */
    IOP_RMT_GPS_ST_RSVD22               = 542,  /*  */
    IOP_RMT_GPS_ST_RSVD23               = 543,  /*  */
    IOP_RMT_GPS_ST_RSVD24               = 544,  /*  */
    IOP_RMT_GPS_ST_RSVD25               = 545,  /*  */

    IOP_RMT_GPS_ST_RSVD26               = 546,  /*  */
    IOP_RMT_GPS_ST_RSVD27               = 547,  /*  */
    IOP_RMT_GPS_ST_RSVD28               = 548,  /*  */
    IOP_RMT_GPS_ST_RSVD29               = 549,  /*  */

    IOP_RMT_GPS_CMND_END                = 549,

    /*------------------------------------------------------
    Read Bravo 2.0 Die ID
    ------------------------------------------------------*/
    IOP_READ_DIE_ID                     = 550,

    /*------------------------------------------------------
    Additional commands related to batteries
    ------------------------------------------------------*/
    IOP_BATT_CMND_START                 = 551,

    IOP_BATT_RSVD1                      = 551,  /*  */
    IOP_BATT_RSVD2                      = 552,  /*  */
    IOP_BATT_FG_LOG_START               = 553,  /* battery fuel gauge - start logging       */
    IOP_BATT_FG_LOG_STOP                = 554,  /* battery fuel gauge - stop logging        */

    IOP_DOWN_LOAD_BATT_MEM              = 555,  /* down load memory of a battery pack       */
    IOP_BATT_CHRG_STATUS                = 556,
    IOP_BATT_GET_DATA                   = 557,
    IOP_BATT_GET_DOOR_OPEN              = 558,
    IOP_BATT_AUTH_STATUS                = 559,
    IOP_BATT_RSVD3                      = 560,  /*  */

    IOP_BATT_CMND_END                   = 560,

    /*------------------------------------------------------
    Course data for fitness products.
    ------------------------------------------------------*/
    IOP_DOWN_LOAD_COURSE                = 561,
    IOP_DOWN_LOAD_COURSE_LAP            = 562,
    IOP_DOWN_LOAD_COURSE_PNT            = 563,
    IOP_DOWN_LOAD_COURSE_TRK            = 564,
    IOP_DOWN_LOAD_COURSE_LMT            = 565,

    /*------------------------------------------------------
    Flush NVM command
    ------------------------------------------------------*/
    IOP_FLUSH_NV                        = 570,

    /*------------------------------------------------------
    Set aviation database initial feature unlock
    ------------------------------------------------------*/
    IOP_AVTN_DB_INIT_FEATURE_UNLOCK     = 571,

    /*------------------------------------------------------
    Checksum commands
    ------------------------------------------------------*/
    IOP_DEL_AUD_CHECKSUM                = 574,

    /*------------------------------------------------------
    Composite video related commands
    ------------------------------------------------------*/
    IOP_REQ_VID_SWITCH_STATE            = 575,

    /*------------------------------------------------------
    Request sensor capability command
    ------------------------------------------------------*/
    IOP_RQST_SNSR_CAPABILITY            = 580,

    /*------------------------------------------------------
    Microphone detect request command
    ------------------------------------------------------*/
    IOP_MIC_DETECT_STATUS               = 581,

    /*------------------------------------------------------
    Power Supply related commands
    ------------------------------------------------------*/
    IOP_PSRC_CMND_START                 = 582,
    IOP_PSRC_USB_DETECT_STATUS          = 583,
    IOP_PSRC_TYPE                       = 584,

    IOP_PSRC_CMND_STOP                  = 590,

    /*------------------------------------------------------
    Calorie Burn Rate command
    ------------------------------------------------------*/
    IOP_DOWN_LOAD_CAL_TBL               = 591,

    /*------------------------------------------------------
    GCD force update command
    ------------------------------------------------------*/
    IOP_FORCE_GCD_UPDATE                = 592,

    /*------------------------------------------------------
    DC series data
    ------------------------------------------------------*/
    IOP_RQST_KEY_SCAN_DATA              = 593,
    IOP_DC_RQST_REF_TRK_PT              = 594,
    IOP_DC_WUSB_CHNL_SWEEP              = 596,
    IOP_DC_RQST_MODEL_INFO              = 597,

    /*------------------------------------------------------
    VLRP-protocol config related commands
    ------------------------------------------------------*/
    IOP_STORE_VLRP_CFG                  = 600,
    IOP_DOWN_LOAD_VLRP_CFG              = 601,
    IOP_DOWN_LOAD_VLRP_TIMING           = 602,
    IOP_VLRP_STOP_TX                    = 603,
    IOP_VLRP_START_TX                   = 604,
    IOP_VLRP_RQST_TEST_PKT              = 605,

    /*------------------------------------------------------
    TouchScreen Linearization Data
    ------------------------------------------------------*/
    IOP_TS_LIN_DATA_RQST                = 610,

    IOP_TS_CAL_CLEAR                    = 611,

    /*------------------------------------------------------
    Mount Detection command
    ------------------------------------------------------*/
    IOP_MOUNT_DETECT_STATUS             = 614,

    /*------------------------------------------------------
    ADC commands
    ------------------------------------------------------*/
    IOP_DOWN_LOAD_ADC_CAL               = 615,

    /*------------------------------------------------------
    Test the RTC Alarm
    ------------------------------------------------------*/
    IOP_TEST_ALARM                      = 616,

    /*------------------------------------------------------
    Product number request
    ------------------------------------------------------*/
    IOP_PRD_NUM_RQST                    = 617,

    /*------------------------------------------------------
    External Ethernet Port Status
    ------------------------------------------------------*/
    IOP_EXT_ETHR_PRT_STAT               = 620,

    /*------------------------------------------------------
    PCB commands
    ------------------------------------------------------*/
    IOP_DL_PCB_GPN                      = 630,
    IOP_DL_PCB_VERSION                  = 631,
    IOP_DL_PCB_DISPLAY_TYPE             = 632,
    IOP_DL_PCB_INVENTORY                = 633,
    IOP_PRINT_PCB_INVENTORY             = 634,

    /*------------------------------------------------------
    One-Time Programmable Memory
    ------------------------------------------------------*/
    IOP_LCK_OTP                         = 640,

    /*------------------------------------------------------
    Board revision request
    ------------------------------------------------------*/
    IOP_BRD_REV_RQST                    = 643,

    /*------------------------------------------------------
    Initial fix date request and reset
    ------------------------------------------------------*/
    IOP_REQ_IFIX_DATE                   = 644,
    IOP_RESET_IFIX_DATE                 = 645,
    IOP_REQ_NOH_IFIX_FLAG               = 646,
    IOP_SET_SIM_IFIX                    = 647,

    /*------------------------------------------------------
    Efield testing
    ------------------------------------------------------*/
    IOP_TEST_EFIELD                     = 650,
    IOP_TEST_EFIELD_CUR_VALS            = 651,
    IOP_TEST_EFIELD_COND_VALS           = 652,
    IOP_EFIELD_POWER_DOWN               = 653,
    IOP_EFIELD_POWER_UP                 = 654,
    IOP_EFIELD_DEBUG_ON                 = 655,
    IOP_EFIELD_DEBUG_OFF                = 656,
    IOP_EFIELD_CAL_OFFSETS              = 657,
    IOP_EFIELD_CAL_STATE                = 658,
    IOP_EFIELD_CAL_VALUES               = 659,

    /*------------------------------------------------------
    Bezel lock and unlock
    ------------------------------------------------------*/
    IOP_LOCK_BEZEL                      = 660,
    IOP_UNLOCK_BEZEL                    = 661,

    /*------------------------------------------------------
    Ethernet Diagnostics
    ------------------------------------------------------*/
    IOP_DUMP_STACKS                     = 670,
    IOP_SET_HUB_MODE                    = 671,

    /*------------------------------------------------------
    Request Nag Date for Map Updates
    ------------------------------------------------------*/
    IOP_MAPDATE_RQST                    = 675,

    /*------------------------------------------------------
    Request GPS velocity filter time constant
    ------------------------------------------------------*/
    IOP_RQST_GPS_VEL_FLTR               = 676,

    /*------------------------------------------------------
    Delete all GDB run data
    ------------------------------------------------------*/
    IOP_DEL_GDB_RUN_DATA                = 677,

    /*------------------------------------------------------
    Download flash serial number
    ------------------------------------------------------*/
    IOP_DL_FLASH_SNUM                   = 678,

    /*------------------------------------------------------
    Download flash info stored in SD/MMC CID register
    ------------------------------------------------------*/
    IOP_DL_FLASH_MID                    = 679,  /* Flash Manufacturer ID        */
    IOP_DL_FLASH_OID                    = 680,  /* Flash OEM/Application ID     */
    IOP_DL_FLASH_PNM                    = 681,  /* Flash Product Name           */
    IOP_DL_FLASH_PRV                    = 682,  /* Flash Product Revision       */
    IOP_DL_FLASH_MDT                    = 683,  /* Flash Manufacturing Date     */

    /*------------------------------------------------------
    ANTLink Commands
    ------------------------------------------------------*/
    IOP_ALINK_KEEP_ALIVE                = 684,
    IOP_ALINK_RQST_TIMEOUT              = 685,

    /*------------------------------------------------------
    Start of next command ID group.
    ------------------------------------------------------*/
    IOP_DL_RTC_ACC                      = 686,

    /*------------------------------------------------------
    Transfer to low-power mode
    ------------------------------------------------------*/
    IOP_TRANSFER_TO_LOWPWR              = 687,

    /*------------------------------------------------------
    Reset Wizards
    ------------------------------------------------------*/
    IOP_RESET_WIZARDS                   = 688,

    /*------------------------------------------------------
    MTK BEE ID group
    ------------------------------------------------------*/
    IOP_MTK_BEE_HSHAKE_ACK              = 689,
    IOP_MTK_BEE_UPLD_DONE               = 690,
    IOP_MTK_BEE_UPLD_DONE_ACK           = 691,

    /*------------------------------------------------------
    ANT Testing
    ------------------------------------------------------*/
    IOP_TEST_ANT_TXRX                   = 695,

    /*------------------------------------------------------
    Compass Cal
    ------------------------------------------------------*/
    IOP_CLR_CMPS_CAL                    = 696,

    /*------------------------------------------------------
    Clear Settings
    ------------------------------------------------------*/
    IOP_CLR_USER_SETTINGS               = 697,
    IOP_CLR_DEALER_SETTINGS             = 698,

    /*------------------------------------------------------
    ANT Remote Control Testing
    ------------------------------------------------------*/
    IOP_TEST_ANT_RMT                    = 699,

    /*------------------------------------------------------
    Sensor Calibration
    ------------------------------------------------------*/
    IOP_START_ACCEL_CAL                 = 700,
    IOP_STOP_ACCEL_CAL                  = 701,
    IOP_START_MAG_CAL                   = 702,
    IOP_STOP_MAG_CAL                    = 703,

    /*------------------------------------------------------
    Error Log
    ------------------------------------------------------*/
    IOP_RQST_ERROR_LOG                  = 704,

    /*------------------------------------------------------
    Request system info string.
    ------------------------------------------------------*/
    IOP_RQST_SYS_INFO_STR               = 705,

    /*------------------------------------------------------
    Clear Error Log
    ------------------------------------------------------*/
    IOP_CLR_ERROR_LOG                   = 706,

    /*------------------------------------------------------
    Bluetooth Commands Extented
    ------------------------------------------------------*/
    IOP_BT_CMND_EXT_START               = 707,

    IOP_BT_CLEAR_PAIRINGS               = 708,
    IOP_BT_SET_PASS_THROUGH_MODE        = 709,
    IOP_BT_SET_SSP_DEBUG_MODE           = 710,
    IOP_BT_PRINT_LINK_KEYS              = 711,
    IOP_BT_HDSET_TEST_ON                = 712,
    IOP_BT_HDSET_TEST_OFF               = 713,
    IOP_BT_HDSET_AUDIO_ON               = 714,
    IOP_BT_HDSET_AUDIO_OFF              = 715,
    IOP_BT_GET_PWR_MODE                 = 716,

    IOP_BT_CMND_EXT_STOP                = 717,

    /*------------------------------------------------------
    Delete Checksum commands
    ------------------------------------------------------*/
    IOP_DEL_ALL_CHECKSUMS               = 718,

    /*------------------------------------------------------
    Managed NAND refresh group.
    ------------------------------------------------------*/
    IOP_MNAND_REFRESH_FACTORY_START     = 719,
    IOP_MNAND_REFRESH_LAST              = 721,

    /*------------------------------------------------------
    Phone Commmand IDs
    ------------------------------------------------------*/
    IOP_DOWN_LOAD_IMEI                  = 722,
    IOP_DOWN_LOAD_WIFI_ADDR             = 723,

    /*------------------------------------------------------
    Prepare for power on  command
    ------------------------------------------------------*/
    IOP_PREP_POWER_ON                   = 724, /* prepare to power on system */

    /*------------------------------------------------------
    Master Clear Request
    ------------------------------------------------------*/
    IOP_FLSH_MSTR_CLR                   = 725, /* tool requesting the device to master clear */
    IOP_FLSH_MSTR_CLR_STATUS            = 726, /* was master clear successful? */
    IOP_WHOAMI              = 727, /* for clients who wants to know this server */

    /*------------------------------------------------------
    Test config modules command
    ------------------------------------------------------*/
    IOP_CONFIG_MOD_TEST                 = 728,

    /*------------------------------------------------------
    Camera commands
    ------------------------------------------------------*/
    IOP_DL_CAMERA_REG                   = 729, /* Download camera registers */
    IOP_TEST_IMG_PROC                   = 730, /* Initiate Image Processor Test (No sensor) */
    IOP_CAMERA_DETECT                   = 731,
    IOP_CAMERA_UPDATE_FIRMWARE          = 732,
    IOP_CAMERA_RSRVD4                   = 733,
    IOP_CAMERA_RSRVD5                   = 734,

    /*------------------------------------------------------
    GPS RF section commands
    ------------------------------------------------------*/
    IOP_GPS_RF_DL_NOISE_CANCEL_SETTINGS     = 735, /* Download RF noise cancellation settings */
    IOP_GPS_RF_RSRVD1                       = 736,
    IOP_GPS_RF_RSRVD2                       = 737,

    /*------------------------------------------------------
    Extended Remote GPS Command IDs
    ------------------------------------------------------*/
    IOP_RMT_GPS_CMND_EXT_START             = 738,

    IOP_RMT_GPS_PRDC_COLD_START_TEST_ON    = 739,
    IOP_RMT_GPS_PRDC_COLD_START_TEST_OFF   = 740,
    IOP_RMT_GPS_DSBL_INT_LNA               = 741,
    IOP_RMT_GPS_ENBL_INT_LNA               = 742,

    IOP_RMT_GPS_CMND_EXT_END               = 760,

    /*------------------------------------------------------
    WiFi Commands
    ------------------------------------------------------*/
    IOP_WIFI_START_TESTMODE             = 761,
    IOP_WIFI_RXTEST_CALC                = 762,
    IOP_WIFI_TXTEST_START               = 763,
    IOP_WIFI_TXTEST_STOP                = 764,
    IOP_WIFI_TEST_GET_STATUS            = 765,
    IOP_WIFI_RXTEST_STOP                = 766,
    IOP_WIFI_STOP_TESTMODE              = 767,
    IOP_WIFI_GET_CONNECTION_INFO        = 768,
    IOP_WIFI_GET_COUNTRY_CODE           = 769,

    IOP_WIFI_CMND_END                   = 770,

    /*------------------------------------------------------
    Download IIC Error Data Command
    ------------------------------------------------------*/
    IOP_DL_IIC_ERROR_DATA               = 771,

    /*------------------------------------------------------
    Mount SW version
    ------------------------------------------------------*/
    IOP_MOUNT_GET_SW_VER                = 772,

    /*------------------------------------------------------
    Build GarminDevice.xml file.
    ------------------------------------------------------*/
    IOP_BLD_GRMN_DEV_XML                = 773,

    /*------------------------------------------------------
    Report whether or not the zip update is complete
    ------------------------------------------------------*/
    IOP_ZIP_UPDT_CMPLT_CMND             = 774,

    /*------------------------------------------------------
    Test Page information over IOP
    ------------------------------------------------------*/
    IOP_TEST_PAGE_INFO                  = 775,  /* Display information from test page over IOP */

    /*------------------------------------------------------
    Begin the zip update extraction
    ------------------------------------------------------*/
    IOP_ZIP_UPDT_STRT_CMND              = 776,

    /*------------------------------------------------------
    Clear VIN data (related to BMW LIN mount)
    ------------------------------------------------------*/
    IOP_MOUNT_CLEAR_VIN_TABLE           = 778,

    /*------------------------------------------------------
    Switch LIN mount to Master LIN mode (for testing)
    ------------------------------------------------------*/
    IOP_MOUNT_SET_MASTER_LIN_NODE       = 779,

    /*------------------------------------------------------
    IOP for map
    ------------------------------------------------------*/
    IOP_GET_MAP_PART_NUM                = 780,

    /*------------------------------------------------------
    Enable/Disable test page access
    ------------------------------------------------------*/
    IOP_ENABLE_TEST_PAGES               = 781,
    IOP_DISABLE_TEST_PAGES              = 782,

    /*------------------------------------------------------
    Wifi commands
    ------------------------------------------------------*/
    IOP_WIFI_GET_MAC_ADDR               = 783,

    /*------------------------------------------------------
    Get status of MNAND refresh
    ------------------------------------------------------*/
    IOP_MNAND_GET_REFRESH_STATUS        = 784,

    /*------------------------------------------------------
    Disable/Enable Display sub system
    ------------------------------------------------------*/
    IOP_DSBL_DSPL                       = 785,
    IOP_ENBL_DSPL                       = 786,

    /*------------------------------------------------------
    Verify/rename map authentication file if present
    ------------------------------------------------------*/
    IOP_GMA_VERIFY_RENAME               = 787,

    /*------------------------------------------------------
    Atmel AVR MCU commands
    ------------------------------------------------------*/
    IOP_AVR_UPDATE                      = 788,

    /*------------------------------------------------------
    Diagnostic Mode
    ------------------------------------------------------*/
    IOP_SYC_DIAG_MODE_ENABLE            = 789,
    IOP_SYC_DIAG_MODE_DISABLE           = 790,

    /*------------------------------------------------------
    ANT download Sensor ID Commands.
    -----------------------------------------------------*/
    IOP_DL_ANT_HR_ID                    = 791, /* Heart Rate               */
    IOP_DL_ANT_CAD_ID                   = 792, /* Cadence Sensor           */
    IOP_DL_ANT_SPD_ID                   = 793, /* Speed Sensor             */
    IOP_DL_ANT_SPDCAD_ID                = 794, /* Speed and Cadence Sensor */
    IOP_DL_ANT_PWR_ID                   = 795, /* Power Meter              */
    IOP_DL_ANT_POD_ID                   = 796, /* Foot Pod                 */
    IOP_DL_ANT_LEV_ID                   = 797, /* Light Electric Vehicle   */
    IOP_DL_ANT_BR_ID                    = 798, /* Bike Radar               */

    /*------------------------------------------------------
    Load test traffic data command.
    ------------------------------------------------------*/
    IOP_LOAD_TEST_TRF_DATA_ID           = 805,

    /*------------------------------------------------------
    OEM Audio Commands
    ------------------------------------------------------*/
    IOP_OEM_SET_MUTE_LINE_HIGH          = 810,
    IOP_OEM_SET_MUTE_LINE_LOW           = 811,

    /*------------------------------------------------------
    Managed nand field refresh commands
    ------------------------------------------------------*/
    IOP_GET_MNAND_FLD_RFRSH_STATUS      = 815,

    /*------------------------------------------------------
    Autopilot Drive Unit Commands
    ------------------------------------------------------*/
    IOP_AUP_DRIVE_UNIT_RUDDER_RAIL_STAR_SET     = 818,
    IOP_AUP_DRIVE_UNIT_RUDDER_CENTER_SET        = 819,
    IOP_AUP_DRIVE_UNIT_RUDDER_RAIL_PORT_SET     = 820,
    IOP_AUP_DRIVE_UNIT_RUDDER_CENTER_CLEAR      = 821,

    IOP_AUP_DRIVE_UNIT_RUDDER_ANGLE_STAR_ACK    = 822,
    IOP_AUP_DRIVE_UNIT_RUDDER_ANGLE_PORT_ACK    = 823,

    IOP_AUP_DRIVE_UNIT_RUDDER_DIR_CAL_BEGIN     = 824,
    IOP_AUP_DRIVE_UNIT_RUDDER_DIR_CAL_CANCEL    = 825,

    IOP_AUP_DRIVE_UNIT_DISABLE_MOTOR                    = 826,

    IOP_AUP_DRIVE_UNIT_RUDDER_ANGULAR_RATE_CALC_BEGIN   = 827,

    IOP_AUP_DRIVE_UNIT_CLR_SETTINGS             = 828,

    IOP_AUP_DRIVE_UNIT_GEAR_RATIO_TEST_OVERRIDE = 829,

    IOP_AUP_DRIVE_UNIT_PLACE_HOLDER             = 830,

    /*------------------------------------------------------
    More Sensor Calibration
    ------------------------------------------------------*/
    IOP_STOP_FIXED_ACCEL_CAL            = 831,

    /*------------------------------------------------------
    CSM get cient type ID command
    ------------------------------------------------------*/
    IOP_CSM_GET_CLIENT_TYPE_ID          = 833,

    /*------------------------------------------------------
    Enable/Disable NREC debug output
    ------------------------------------------------------*/
    IOP_ECR_OUTPUT_EN                   = 835,
    IOP_ECR_OUTPUT_DA                   = 836,

    /*------------------------------------------------------
    Erase region command
    ------------------------------------------------------*/
    IOP_ERASE_XLDR                      = 837,
    IOP_ERASE_SYS                       = 838,

    /*------------------------------------------------------
    Touchscreen Controller Commands
    ------------------------------------------------------*/
    IOP_TSC_READ_SENSORS_DATA           = 840,
    IOP_TSC_READ_RAWDIFF_DATA           = 841,
    IOP_TSC_CLR_BOOTLOADER_FLAG         = 842,
    IOP_TSC_GET_BOOTLOADER_FLAG         = 843,
    IOP_TSC_BLOCK_FIRMWARE_UPDATE       = 844,

    /*------------------------------------------------------
    Print Power-up/Reset info out IOP
    ------------------------------------------------------*/
    IOP_GET_RST_PWRP_INFO               = 845,

    /*------------------------------------------------------
    Read  PRNP checksum from the metadata
    ------------------------------------------------------*/
    IOP_GET_PRNP_CHECKSUM               = 846,

    /*------------------------------------------------------
    Microphone data logging
    ------------------------------------------------------*/
    IOP_MIC_LOG_START                   = 847,
    IOP_MIC_LOG_STOP                    = 848,

    /*------------------------------------------------------
    HCache profiling
    ------------------------------------------------------*/
    IOP_GFS_HCACHE_PROF_ENBL            = 849,
    IOP_GFS_HCACHE_PROF_DSBL            = 850,
    IOP_GFS_HCACHE_PROF_DUMP            = 851,

    /*------------------------------------------------------
    IOP instr ID to get saved sw version number list
    -----------------------------------------------------*/
    IOP_GET_SW_VER_LIST                 = 852,

    /*------------------------------------------------------
    Touchscreen Controller Commands (cont.)
    ------------------------------------------------------*/
    IOP_TSC_ALLOW_FIRMWARE_UPDATE       = 853,

    /*------------------------------------------------------
    IOP instr ID to get LOC8 lock status
    -----------------------------------------------------*/
    IOP_GET_LOC8_LOCK_STATUS            = 854,

    /*------------------------------------------------------
    IOP instr to output all PMIC register contents
    -----------------------------------------------------*/
    IOP_GET_PMIC_REG_DATA               = 855,

    /*------------------------------------------------------
    IOP command to reset RTC accuracy test
    -----------------------------------------------------*/
    IOP_RESET_RTC_ACC                   = 856,

    /*------------------------------------------------------
    IOP command to get PRNP Image Programming speed
    -----------------------------------------------------*/
    IOP_GET_IMAGE_PROGRAMMING_SPEED    = 857,

    /*------------------------------------------------------
    Touchscreen Controller Commands (cont.)
    ------------------------------------------------------*/
    IOP_TSC_READ_VERSION                = 858,

    IOP_TSC_CMND_END                    = 859,

    /*------------------------------------------------------
    IOP command to get 006-J Garmin part number
    -----------------------------------------------------*/
    IOP_GET_IMAGE_BOM_GPN               = 860,

    /*------------------------------------------------------
    File system commands.
    -----------------------------------------------------*/
    IOP_FS_CMD_CHKDSK_EMB_VOL           = 870,
    IOP_FS_CMD_CHKDSK_EVL_RSLT          = 871,

    /*------------------------------------------------------
    Dead reckoning commands
    ------------------------------------------------------*/
    IOP_DR_GYRO_DISABLE_CAL             = 880,
    IOP_DR_GYRO_ENABLE_CAL              = 881,
    IOP_DR_CLR_GYRO_BIAS_LOW_TEMP       = 882,
    IOP_DR_CLR_GYRO_BIAS_MED_TEMP       = 883,
    IOP_DR_CLR_GYRO_BIAS_HIGH_TEMP      = 884,

    /*------------------------------------------------------
    IOP command to enter suspend state
    -----------------------------------------------------*/
    IOP_SUSPEND                         = 900,

    /*------------------------------------------------------
    Commands to turn GSM off and on
    ------------------------------------------------------*/
    IOP_GSM_ON                          = 901,
    IOP_GSM_OFF_NORMAL                  = 902,
    IOP_GSM_OFF_IMMEDIATE               = 903,

    /*------------------------------------------------------
    iPod authentication chip test
    ------------------------------------------------------*/
    IOP_TEST_IPOD_AUTH                  = 904,

    /*------------------------------------------------------
    Commands to turn on hopper
    ------------------------------------------------------*/
    IOP_HOPPER_SETUP                     = 905,
    IOP_HOPPER_SETUP_WHILE_ONE           = 906,

    /*------------------------------------------------------
    Commands to enable/disable RTC clock out
    ------------------------------------------------------*/
    IOP_RTC_OUT_PAD_ENABLE              = 907,
    IOP_RTC_OUT_PAD_DISABLE             = 908,
    IOP_RTC_OUT_PAD_RESERVED_1          = 909,
    IOP_RTC_OUT_PAD_RESERVED_2          = 910,

    /*------------------------------------------------------
    Remote GPS Command IDs for TI-Specific Commands
    (More TI-Specific commands at 1350)
    ------------------------------------------------------*/
    IOP_RMT2_GPS_CMND_START             = 911,  /*  */
    IOP_RMT_GPS_TI_RSVD01               = 911,  /*  */
    IOP_RMT_GPS_TI_RSVD02               = 912,  /*  */
    IOP_RMT_GPS_TI_RSVD03               = 913,  /*  */
    IOP_RMT_GPS_TI_RSVD04               = 914,  /*  */
    IOP_RMT_GPS_TI_RSVD05               = 915,  /*  */
    IOP_RMT_GPS_TI_RSVD06               = 916,  /*  */
    IOP_RMT_GPS_TI_RSVD07               = 917,  /*  */
    IOP_RMT_GPS_TI_RSVD08               = 918,  /*  */
    IOP_RMT_GPS_TI_RSVD09               = 919,  /*  */
    IOP_RMT_GPS_TI_RSVD10               = 920,  /*  */
    IOP_RMT2_GPS_CMND_END               = 920,  /*  */

    /*------------------------------------------------------
    Commands to turn off hopper
    ------------------------------------------------------*/
    IOP_HOPPER_DISABLE                  = 921,

    /*------------------------------------------------------
    Media Transfer Protocol commands
    ------------------------------------------------------*/
    IOP_MTP_AUTODETECT_ENABLE           = 922,
    IOP_MTP_AUTODETECT_ENABLE_PERS      = 923,
    IOP_MTP_AUTODETECT_DISABLE          = 924,
    IOP_MTP_AUTODETECT_DISABLE_PERS     = 925,
    IOP_MTP_RESERVED1                   = 926,
    IOP_MTP_RESERVED2                   = 927,
    IOP_MTP_RESERVED3                   = 928,
    IOP_MTP_RESERVED4                   = 929,
    IOP_MTP_RESERVED5                   = 930,

    /*------------------------------------------------------
    IOP command to turn on and off the Play wav in Test Mode
    -----------------------------------------------------*/
    IOP_TEST_PLAY_WAV_OFF               = 931,
    IOP_TEST_PLAY_WAV_ON                = 932,

    /*------------------------------------------------------
    Check whether an SD card is present
    -----------------------------------------------------*/
    IOP_SD_CARD_PRESENT                 = 933,

    /*------------------------------------------------------
    IOP command to display the sound test page.
    ------------------------------------------------------*/
    IOP_SOUND_TEST                      = 934,

    /*------------------------------------------------------
    IOP command to test the functionality of the accelerometer.
    ------------------------------------------------------*/
    IOP_ACCEL_SELF_TEST                 = 935,

    /*------------------------------------------------------
    Set PRNP flag in non-vol if mass storage has to be
    programmed.
    ------------------------------------------------------*/
    IOP_SET_PRNP_NV_FLAG                = 936,
    IOP_GET_PRNP_NV_FLAG                = 937,
    IOP_DEL_PRNP_NV_FLAG                = 938,

    /*------------------------------------------------------
    Automatic Volume Control (AVC) IOP commands
    ------------------------------------------------------*/
    IOP_AVC_ENABLE                      = 939,
    IOP_AVC_DISABLE                     = 940,
    IOP_AVC_START_TUNING                = 941,
    IOP_AVC_STOP_TUNING                 = 942,
    IOP_AVC_OUTPUT_GAIN_TBL             = 943,
    IOP_AVC_GET_AVC_CALC_GAIN           = 944,
    IOP_AVC_GET_CRNT_HW_GAIN            = 945,
    IOP_AVC_LOG_MIC_DATA                = 946,

    /*------------------------------------------------------
    Command to get the amplifier faults
    ------------------------------------------------------*/
    IOP_GET_NV_AMP_FAULTS               = 947,
    IOP_CLEAR_NV_AMP_FAULTS             = 948,

    /*------------------------------------------------------
    Command to get USB faults
    ------------------------------------------------------*/
    IOP_GET_NV_USB_FAULTS               = 949,
    IOP_CLEAR_NV_USB_FAULTS             = 950,

    /*------------------------------------------------------
    IOP instr ID to get MLG ecoroute lock status
    -----------------------------------------------------*/
    IOP_GET_MLG_ECOROUTE_LOCK_STATUS    = 951,

    /*------------------------------------------------------
    IOP command to get VCOM value
    -----------------------------------------------------*/
    IOP_GET_VCOM_VALUE                  = 952,

    /*------------------------------------------------------
    High Temperature Display control
    ------------------------------------------------------*/
    IOP_HIGH_TEMP_CTRL_DISABLE          = 953,
    IOP_HIGH_TEMP_CTRL_ENABLE           = 954,

    /*------------------------------------------------------
    Commands to enable and disable ASR voice hopper
    ------------------------------------------------------*/
    IOP_ASR_HOPPER_ENABLE               = 955,
    IOP_ASR_HOPPER_DISABLE              = 956,

    /*------------------------------------------------------
    Command to get the GNSS data source(s) being used
    ------------------------------------------------------*/
    IOP_GNSS_RQST_DATA_SRC              = 957,

    /*------------------------------------------------------
    Commands to enable and disable infinite loop on shutdown
    ------------------------------------------------------*/
    IOP_LOOP_ON_SHUTDWN_ENABLE          = 958,
    IOP_LOOP_ON_SHUTDWN_DISABLE         = 959,

    IOP_RPT_MAP_UNLOCK_CHNG             = 960,

    /*------------------------------------------------------
    AMX device factory test commands
    ------------------------------------------------------*/
    IOP_AMX_LED_GREEN_ON                = 961,
    IOP_AMX_LED_RED_ON                  = 962,
    IOP_AMX_LED_OFF                     = 963,
    IOP_AMX_RESERVED_0                  = 964,
    IOP_AMX_RESERVED_1                  = 965,
    IOP_AMX_RESERVED_2                  = 966,

    /*------------------------------------------------------
    IOP command to get the state of the I/O expander
    ------------------------------------------------------*/
    IOP_GET_IO_EXP_STATUS               = 967,

    /*------------------------------------------------------
    IOP command to get the state of steering wheel keys
    ------------------------------------------------------*/
    IOP_GET_VIM_KEYS                    = 968,

    /*------------------------------------------------------
    IOP command to get the state of BT steering wheel keys
    ------------------------------------------------------*/
    IOP_GET_BT_STW_KEYS                 = 969,

    /*------------------------------------------------------
    IOP command to get the speed of the vehicle
    ------------------------------------------------------*/
    IOP_GET_SPEED                       = 970,

    /*------------------------------------------------------
    Play media from USB drive upon next power cycle
    ------------------------------------------------------*/
    IOP_PLAY_USB_NEXT_BOOT              = 971,

    /*------------------------------------------------------
    IOP commands for storage of critical data during PRNP
    ------------------------------------------------------*/
    IOP_SET_PRNP_CRITICAL_DATA_FLAG     = 972,
    IOP_GET_PRNP_CRITICAL_DATA_FLAG     = 973,
    IOP_RESET_PRNP_CRITICAL_DATA_FLAG   = 974,

    /*------------------------------------------------------
    Enter test mode at boot
    ------------------------------------------------------*/
    IOP_SET_STARTUP_IN_TESTMODE         = 975,

    /*------------------------------------------------------
    Get ADC counts for AUD and BT key presses from VIM
    ------------------------------------------------------*/
    IOP_GET_STW_AUD_ADC_COUNT           = 976,
    IOP_GET_STW_BT_ADC_COUNT            = 977,

    /*------------------------------------------------------
    Commands for turning on/off audio when running hopper
    ------------------------------------------------------*/
    IOP_AUDIO_HOPPER_ENABLE             = 978,
    IOP_AUDIO_HOPPER_DISABLE            = 979,

    /*------------------------------------------------------
    Commands for putting demo mode in undecided state
    ------------------------------------------------------*/
    IOP_DEMO_UNDECIDED                  = 980,

    /*------------------------------------------------------
    PWR Framework debug info
    ------------------------------------------------------*/
    IOP_PWR_DBG_LOG                     = 981,
    IOP_PWR_DBG_SUSPEND                 = 982,
    IOP_PWR_DBG_STANDBY                 = 983,
    IOP_PWR_DBG_LOWBATT                 = 984,
    IOP_PWR_DBG_BATTERY                 = 985,
    IOP_PWR_DBG_EXTERNAL                = 986,
    IOP_PWR_DBG_UNLOCKED                = 987,
    IOP_PWR_DBG_LP_MP3                  = 988,

    IOP_GET_OEM_MODEL                   = 989,
    IOP_GET_OEM_MARKET                  = 990,

    IOP_CHECK_FOR_BB                    = 991,

    /*------------------------------------------------------
    Reserved for GPS MULTI
    ------------------------------------------------------*/
    IOP_GPS_MULTI_RSVD_START            = 992,
    IOP_GPS_MULTI_RSVD_1                = 992,
    IOP_GPS_MULTI_RSVD_2                = 993,
    IOP_GPS_MULTI_RSVD_3                = 994,
    IOP_GPS_MULTI_RSVD_4                = 995,
    IOP_GPS_MULTI_RSVD_5                = 996,
    IOP_GPS_MULTI_RSVD_6                = 997,
    IOP_GPS_MULTI_RSVD_7                = 998,
    IOP_GPS_MULTI_RSVD_8                = 999,
    IOP_GPS_MULTI_RSVD_9                = 1000,
    IOP_GPS_MULTI_RSVD_10               = 1001,
    IOP_GPS_MULTI_RSVD_11               = 1002,
    IOP_GPS_MULTI_RSVD_12               = 1003,
    IOP_GPS_MULTI_RSVD_13               = 1004,
    IOP_GPS_MULTI_RSVD_14               = 1005,
    IOP_GPS_MULTI_RSVD_15               = 1006,
    IOP_GPS_MULTI_RSVD_16               = 1007,
    IOP_GPS_MULTI_RSVD_17               = 1008,
    IOP_GPS_MULTI_RSVD_18               = 1009,
    IOP_GPS_MULTI_RSVD_19               = 1010,
    IOP_GPS_MULTI_RSVD_20               = 1011,
    IOP_GPS_MULTI_RSVD_21               = 1012,
    IOP_GPS_MULTI_RSVD_22               = 1013,
    IOP_GPS_MULTI_RSVD_23               = 1014,
    IOP_GPS_MULTI_RSVD_24               = 1015,
    IOP_GPS_MULTI_RSVD_25               = 1016,
    IOP_GPS_MULTI_RSVD_26               = 1017,
    IOP_GPS_MULTI_RSVD_27               = 1018,
    IOP_GPS_MULTI_RSVD_28               = 1019,
    IOP_GPS_MULTI_RSVD_29               = 1020,
    IOP_GPS_MULTI_RSVD_30               = 1021,
    IOP_GPS_MULTI_RSVD_31               = 1022,
    IOP_GPS_MULTI_RSVD_32               = 1023,
    IOP_GPS_MULTI_RSVD_33               = 1024,
    IOP_GPS_MULTI_RSVD_34               = 1025,
    IOP_GPS_MULTI_RSVD_35               = 1026,
    IOP_GPS_MULTI_RSVD_36               = 1027,
    IOP_GPS_MULTI_RSVD_37               = 1028,
    IOP_GPS_MULTI_RSVD_38               = 1029,
    IOP_GPS_MULTI_RSVD_39               = 1030,
    IOP_GPS_MULTI_RSVD_40               = 1031,
    IOP_GPS_MULTI_RSVD_41               = 1032,
    IOP_GPS_MULTI_RSVD_42               = 1033,
    IOP_GPS_MULTI_RSVD_43               = 1034,
    IOP_GPS_MULTI_RSVD_44               = 1035,
    IOP_GPS_MULTI_RSVD_45               = 1036,
    IOP_GPS_MULTI_RSVD_46               = 1037,
    IOP_GPS_MULTI_RSVD_47               = 1038,
    IOP_GPS_MULTI_RSVD_48               = 1039,
    IOP_GPS_MULTI_RSVD_49               = 1040,
    IOP_GPS_MULTI_RSVD_50               = 1041,
    IOP_GPS_MULTI_RSVD_END              = 1041,

    /*------------------------------------------------------
    Extended Bluetooth Audio Command IDs
    ------------------------------------------------------*/
    IOP_BT_AUDIO_CMND_EXT_START         = 1042,

    IOP_BT_AUD_EXTD_SHOW_INQUIRY_RESULT = 1042,
    IOP_BT_AUD_EXTD_INQUIRY_STR         = 1043,
    IOP_BT_AUD_EXTD_INQUIRY_STP         = 1044,
    IOP_BT_AUD_EXTD_SHOW_PAIRED         = 1045,
    IOP_BT_AUD_EXTD_DEL_PAIRED          = 1046,
    IOP_BT_AUD_EXTD_CONN_STAT           = 1047,
    IOP_BT_AUD_EXTD_RING                = 1048,
    IOP_BT_AUD_EXTD_PAIR_DUT            = 1049,
    IOP_BT_AUD_EXTD_DEV_CONN            = 1050,
    IOP_BT_AUD_EXTD_DEV_SCO             = 1051,
    IOP_RFC_NOTE_TEST                   = 1052,
    IOP_RFC_LOAD_CONFIG                 = 1053,
    IOP_BT_AUDIO_CMND_EXT_END           = 1054,

    /*------------------------------------------------------
    Start of Marine specific command section #1.

    This section may be modified by marine projects using
    the MARINE technology/iop Git repository.
    ------------------------------------------------------*/
    IOP_CMND_MARINE_SECTION_1_START     = 1055,

    /*------------------------------------------------------
    Test mode remote control
    ------------------------------------------------------*/
    IOP_TST_RMT_SEL_NEXT                = 1055,  /* select next test mode button */
    IOP_TST_RMT_EXE                     = 1056,  /* execute selected button      */
    IOP_TST_RMT_MENU                    = 1057,  /* return to menu               */

    /*------------------------------------------------------
    Quick RAM test
    ------------------------------------------------------*/
    IOP_TEST_RAM_QUICK                  = 1058,  /* perform quick ram test       */

    IOP_AIS_RESET_TARGETS               = 1059,  /* Reset AIS targets            */

    /*------------------------------------------------------
    WiFi Router Commands
    ------------------------------------------------------*/
    IOP_WIFI_ROUTER_CMND_BEGIN          = 1060,  /* Marker Only                     */
    IOP_WIFI_ROUTER_REBOOT              = 1061,  /* Reboot Wi-Fi Router             */
    IOP_WIFI_ROUTER_FACTORY_RESET       = 1062,  /* Reset Wi-Fi Router              */
    IOP_WIFI_ROUTER_SW_UPDATE_CHECK     = 1063,  /* Start SW update check process   */
    IOP_WIFI_ROUTER_RQST_UPDATE_DL      = 1064,  /* Start SW download process       */
    IOP_WIFI_ROUTER_SLEEP               = 1065,  /* Put Wi-Fi Router to sleep       */
    IOP_WIFI_ROUTER_WAKE                = 1066,  /* Wake up Wi-Fi Router            */
    IOP_WIFI_ROUTER_CMND_END            = 1079,  /* Marker Only                     */

    IOP_TEST_BMAP                       = 1080,  /* Start BMAP Test              */

    /*---------------------------------------------------------
    GMM Commands
    ---------------------------------------------------------*/
    IOP_GMM_CMND_BEGIN                  = 1081,

    IOP_GMM_CMND_END                    = 1099,

    /*------------------------------------------------------
    End of Marine specific command section #1.
    ------------------------------------------------------*/
    IOP_CMND_MARINE_SECTION_1_END       = 1100,

    /*------------------------------------------------------
    Trigger Region and Checksum tests in Test Mode
    ------------------------------------------------------*/
    IOP_TEST_MODE_CHECKSUM              = 1101,
    IOP_TEST_MODE_RGN_CHK               = 1102,

    /*------------------------------------------------------
    Enable/disable voltage to mount
    ------------------------------------------------------*/
    IOP_MOUNT_VOLTAGE_ENABLE            = 1103,
    IOP_MOUNT_VOLTAGE_DISABLE           = 1104,

    /*------------------------------------------------------
    Enable/disable flashlight
    ------------------------------------------------------*/
    IOP_FLASHLIGHT_ENABLE               = 1105,
    IOP_FLASHLIGHT_DISABLE              = 1106,
    IOP_FLASHLIGHT_RESERVED             = 1107,

    /*------------------------------------------------------
    Hardware configuration handling command ID
    ------------------------------------------------------*/
    IOP_READ_HW_CONFIG                  = 1108,

    /*------------------------------------------------------
    Barometer related command IDs
    ------------------------------------------------------*/
    IOP_BARO_CMND_START                 = 1109,

    IOP_BARO_GET_LOCAL_PRESS_OFST       = 1109,
    IOP_BARO_RESET_LOCAL_PRESS_OFST     = 1110,
    IOP_BARO_CMND_END                   = 1114,

    /*------------------------------------------------------
    Bluetooth file xfer related command IDs
    ------------------------------------------------------*/
    IOP_BT_FILE_XFER_INQUIRY            = 1115,
    IOP_BT_FILE_XFER_BT_MODE            = 1116,

    /*------------------------------------------------------
    ANT related command IDs
    ------------------------------------------------------*/
    IOP_ANT_CMND_START                  = 1120,
    IOP_ANT_OPEN_PAIRED_SENSORS         = 1120,
    IOP_ANT_CLOSE_ALL_SENSORS           = 1121,
    IOP_ANT_STOP_SENSOR_SEARCH          = 1122,
    IOP_ANT_CMND_END                    = 1134,

    /*------------------------------------------------------
    Video related command IDs (action cam / virb)
    ------------------------------------------------------*/
    IOP_VIDEO_CMND_START                = 1135,
    IOP_VIDEO_GET_SNS_UNIT_ID           = 1135,
    IOP_VIDEO_DIVE_CASE_STATUS          = 1136,
    IOP_VIDEO_HDMI_CABLE_STATUS         = 1137,
    IOP_VIDEO_GET_ICB_UNIT_ID           = 1138,
    IOP_VIDEO_GET_NV_MAC_ADDR           = 1139,
    IOP_VIDEO_GET_ICB_HW_VER            = 1140,
    IOP_VIDEO_GET_IOB_HW_VER            = 1141,
    IOP_VIDEO_GET_WB_UNIT_ID            = 1142,
    IOP_VIDEO_GET_PB_UNIT_ID            = 1143,
    IOP_VIDEO_CMND_END                  = 1144,

    /*------------------------------------------------------
    Locked block test command ID
    ------------------------------------------------------*/
    IOP_LOCK_BLK_TST_CMD                = 1145,

    /*------------------------------------------------------
    Test mode startup commands

    IOP_SET_STARTUP_IN_TESTMODE is earlier in the file
    ------------------------------------------------------*/
    IOP_CLR_STARTUP_IN_TESTMODE         = 1146,
    IOP_GET_STARTUP_IN_TESTMODE         = 1147,

    /*------------------------------------------------------
    Touchscreen Low Power Mode Commands
    ------------------------------------------------------*/
    IOP_TSC_LOW_PWR_ON                  = 1148,
    IOP_TSC_LOW_PWR_OFF                 = 1149,

    /*------------------------------------------------------
    PMU Performance Profiling Control
    ------------------------------------------------------*/
    IOP_PMU_PERF_INIT_I                 = 1150,
    IOP_PMU_PERF_INIT_C                 = 1151,
    IOP_PMU_PERF_INIT_C2                = 1152,
    IOP_PMU_PERF_INIT_W                 = 1153,
    IOP_PMU_PERF_INIT_R                 = 1154,
    IOP_PMU_PERF_INIT_N                 = 1155,
    IOP_PMU_PERF_START                  = 1156,
    IOP_PMU_PERF_STOP                   = 1157,
    IOP_PMU_PERF_REPORT                 = 1158,

    /*------------------------------------------------------
    Remote GPS Command IDs for the 3 major GPS chipsets:
    MTK, ST and TI
    ------------------------------------------------------*/
    IOP_RMT3_GPS_CMND_START             = 1159,  /*  */
    IOP_RMT_GPS_MTK_RSVD01              = 1159,  /*  */
    IOP_RMT_GPS_MTK_RSVD02              = 1160,  /*  */
    IOP_RMT_GPS_MTK_RSVD03              = 1161,  /*  */
    IOP_RMT_GPS_MTK_RSVD04              = 1162,  /*  */
    IOP_RMT_GPS_MTK_RSVD05              = 1163,  /*  */
    IOP_RMT_GPS_MTK_RSVD06              = 1164,  /*  */
    IOP_RMT_GPS_MTK_RSVD07              = 1165,  /*  */
    IOP_RMT_GPS_MTK_RSVD08              = 1166,  /*  */
    IOP_RMT_GPS_MTK_RSVD09              = 1167,  /*  */
    IOP_RMT_GPS_MTK_RSVD10              = 1168,  /*  */
    IOP_RMT_GPS_MTK_RSVD11              = 1169,  /*  */
    IOP_RMT_GPS_MTK_RSVD12              = 1170,  /*  */
    IOP_RMT_GPS_MTK_RSVD13              = 1171,  /*  */
    IOP_RMT_GPS_MTK_RSVD14              = 1172,  /*  */
    IOP_RMT_GPS_MTK_RSVD15              = 1173,  /*  */
    IOP_RMT_GPS_MTK_RSVD16              = 1174,  /*  */
    IOP_RMT_GPS_MTK_RSVD17              = 1175,  /*  */
    IOP_RMT_GPS_MTK_RSVD18              = 1176,  /*  */
    IOP_RMT_GPS_MTK_RSVD19              = 1177,  /*  */
    IOP_RMT_GPS_MTK_RSVD20              = 1178,  /*  */
    IOP_RMT_GPS_MTK_RSVD21              = 1179,  /*  */
    IOP_RMT_GPS_MTK_RSVD22              = 1180,  /*  */
    IOP_RMT_GPS_MTK_RSVD23              = 1181,  /*  */
    IOP_RMT_GPS_MTK_RSVD24              = 1182,  /*  */
    IOP_RMT_GPS_MTK_RSVD25              = 1183,  /*  */
    IOP_RMT_GPS_MTK_RSVD26              = 1184,  /*  */
    IOP_RMT_GPS_MTK_RSVD27              = 1185,  /*  */
    IOP_RMT_GPS_MTK_RSVD28              = 1186,  /*  */
    IOP_RMT_GPS_MTK_RSVD29              = 1187,  /*  */
    IOP_RMT_GPS_MTK_RSVD30              = 1188,  /*  */
    IOP_RMT_GPS_MTK_RSVD31              = 1189,  /*  */
    IOP_RMT_GPS_MTK_RSVD32              = 1190,  /*  */
    IOP_RMT_GPS_MTK_RSVD33              = 1191,  /*  */
    IOP_RMT_GPS_MTK_RSVD34              = 1192,  /*  */
    IOP_RMT_GPS_MTK_RSVD35              = 1193,  /*  */
    IOP_RMT_GPS_MTK_RSVD36              = 1194,  /*  */
    IOP_RMT_GPS_MTK_RSVD37              = 1195,  /*  */
    IOP_RMT_GPS_MTK_RSVD38              = 1196,  /*  */
    IOP_RMT_GPS_MTK_RSVD39              = 1197,  /*  */
    IOP_RMT_GPS_MTK_RSVD40              = 1198,  /*  */
    IOP_RMT_GPS_MTK_RSVD41              = 1199,  /*  */
    IOP_RMT_GPS_MTK_RSVD42              = 1200,  /*  */
    IOP_RMT_GPS_MTK_RSVD43              = 1201,  /*  */
    IOP_RMT_GPS_MTK_RSVD44              = 1202,  /*  */
    IOP_RMT_GPS_MTK_RSVD45              = 1203,  /*  */
    IOP_RMT_GPS_MTK_RSVD46              = 1204,  /*  */
    IOP_RMT_GPS_MTK_RSVD47              = 1205,  /*  */
    IOP_RMT_GPS_MTK_RSVD48              = 1206,  /*  */
    IOP_RMT_GPS_MTK_RSVD49              = 1207,  /*  */
    IOP_RMT_GPS_MTK_RSVD50              = 1208,  /*  */
    IOP_RMT_GPS_MTK_RSVD51              = 1209,  /*  */
    IOP_RMT_GPS_MTK_RSVD52              = 1210,  /*  */
    IOP_RMT_GPS_MTK_RSVD53              = 1211,  /*  */
    IOP_RMT_GPS_MTK_RSVD54              = 1212,  /*  */
    IOP_RMT_GPS_MTK_RSVD55              = 1213,  /*  */
    IOP_RMT_GPS_MTK_RSVD56              = 1214,  /*  */
    IOP_RMT_GPS_MTK_RSVD57              = 1215,  /*  */
    IOP_RMT_GPS_MTK_RSVD58              = 1216,  /*  */
    IOP_RMT_GPS_MTK_RSVD59              = 1217,  /*  */
    IOP_RMT_GPS_MTK_RSVD60              = 1218,  /*  */
    IOP_RMT_GPS_MTK_RSVD61              = 1219,  /*  */
    IOP_RMT_GPS_MTK_RSVD62              = 1220,  /*  */
    IOP_RMT_GPS_MTK_RSVD63              = 1221,  /*  */
    IOP_RMT_GPS_MTK_RSVD64              = 1222,  /*  */
    IOP_RMT_GPS_MTK_RSVD65              = 1223,  /*  */
    IOP_RMT_GPS_MTK_RSVD66              = 1224,  /*  */
    IOP_RMT_GPS_MTK_RSVD67              = 1225,  /*  */
    IOP_RMT_GPS_MTK_RSVD68              = 1226,  /*  */
    IOP_RMT_GPS_MTK_RSVD69              = 1227,  /*  */
    IOP_RMT_GPS_MTK_RSVD70              = 1228,  /*  */
    IOP_RMT_GPS_MTK_RSVD71              = 1229,  /*  */
    IOP_RMT_GPS_MTK_RSVD72              = 1230,  /*  */
    IOP_RMT_GPS_MTK_RSVD73              = 1231,  /*  */
    IOP_RMT_GPS_MTK_RSVD74              = 1232,  /*  */
    IOP_RMT_GPS_MTK_RSVD75              = 1233,  /*  */
    IOP_RMT_GPS_MTK_RSVD76              = 1234,  /*  */
    IOP_RMT_GPS_MTK_RSVD77              = 1235,  /*  */
    IOP_RMT_GPS_MTK_RSVD78              = 1236,  /*  */
    IOP_RMT_GPS_MTK_RSVD79              = 1237,  /*  */
    IOP_RMT_GPS_MTK_RSVD80              = 1238,  /*  */
    IOP_RMT_GPS_MTK_RSVD81              = 1239,  /*  */
    IOP_RMT_GPS_MTK_RSVD82              = 1240,  /*  */
    IOP_RMT_GPS_MTK_RSVD83              = 1241,  /*  */
    IOP_RMT_GPS_MTK_RSVD84              = 1242,  /*  */
    IOP_RMT_GPS_MTK_RSVD85              = 1243,  /*  */
    IOP_RMT_GPS_MTK_RSVD86              = 1244,  /*  */
    IOP_RMT_GPS_MTK_RSVD87              = 1245,  /*  */
    IOP_RMT_GPS_MTK_RSVD88              = 1246,  /*  */
    IOP_RMT_GPS_MTK_RSVD89              = 1247,  /*  */
    IOP_RMT_GPS_MTK_RSVD90              = 1248,  /*  */
    IOP_RMT_GPS_MTK_RSVD91              = 1249,  /*  */
    IOP_RMT_GPS_MTK_RSVD92              = 1250,  /*  */
    IOP_RMT_GPS_MTK_RSVD93              = 1251,  /*  */
    IOP_RMT_GPS_MTK_RSVD94              = 1252,  /*  */
    IOP_RMT_GPS_MTK_RSVD95              = 1253,  /*  */
    IOP_RMT_GPS_MTK_RSVD96              = 1254,  /*  */
    IOP_RMT_GPS_MTK_RSVD97              = 1255,  /*  */
    IOP_RMT_GPS_MTK_RSVD98              = 1256,  /*  */
    IOP_RMT_GPS_MTK_RSVD99              = 1257,  /*  */
    IOP_RMT_GPS_MTK_RSVD100             = 1258,  /*  */

    IOP_RMT_GPS_ST_RSVD30               = 1259,  /*  */
    IOP_RMT_GPS_ST_RSVD31               = 1260,  /*  */
    IOP_RMT_GPS_ST_RSVD32               = 1261,  /*  */
    IOP_RMT_GPS_ST_RSVD33               = 1262,  /*  */
    IOP_RMT_GPS_ST_RSVD34               = 1263,  /*  */
    IOP_RMT_GPS_ST_RSVD35               = 1264,  /*  */
    IOP_RMT_GPS_ST_RSVD36               = 1265,  /*  */
    IOP_RMT_GPS_ST_RSVD37               = 1266,  /*  */
    IOP_RMT_GPS_ST_RSVD38               = 1267,  /*  */
    IOP_RMT_GPS_ST_RSVD39               = 1268,  /*  */
    IOP_RMT_GPS_ST_RSVD40               = 1269,  /*  */
    IOP_RMT_GPS_ST_RSVD41               = 1270,  /*  */
    IOP_RMT_GPS_ST_RSVD42               = 1271,  /*  */
    IOP_RMT_GPS_ST_RSVD43               = 1272,  /*  */
    IOP_RMT_GPS_ST_RSVD44               = 1273,  /*  */
    IOP_RMT_GPS_ST_RSVD45               = 1274,  /*  */
    IOP_RMT_GPS_ST_RSVD46               = 1275,  /*  */
    IOP_RMT_GPS_ST_RSVD47               = 1276,  /*  */
    IOP_RMT_GPS_ST_RSVD48               = 1277,  /*  */
    IOP_RMT_GPS_ST_RSVD49               = 1278,  /*  */
    IOP_RMT_GPS_ST_RSVD50               = 1279,  /*  */
    IOP_RMT_GPS_ST_RSVD51               = 1280,  /*  */
    IOP_RMT_GPS_ST_RSVD52               = 1281,  /*  */
    IOP_RMT_GPS_ST_RSVD53               = 1282,  /*  */
    IOP_RMT_GPS_ST_RSVD54               = 1283,  /*  */
    IOP_RMT_GPS_ST_RSVD55               = 1284,  /*  */
    IOP_RMT_GPS_ST_RSVD56               = 1285,  /*  */
    IOP_RMT_GPS_ST_RSVD57               = 1286,  /*  */
    IOP_RMT_GPS_ST_RSVD58               = 1287,  /*  */
    IOP_RMT_GPS_ST_RSVD59               = 1288,  /*  */
    IOP_RMT_GPS_ST_RSVD60               = 1289,  /*  */
    IOP_RMT_GPS_ST_RSVD61               = 1290,  /*  */
    IOP_RMT_GPS_ST_RSVD62               = 1291,  /*  */
    IOP_RMT_GPS_ST_RSVD63               = 1292,  /*  */
    IOP_RMT_GPS_ST_RSVD64               = 1293,  /*  */
    IOP_RMT_GPS_ST_RSVD65               = 1294,  /*  */
    IOP_RMT_GPS_ST_RSVD66               = 1295,  /*  */
    IOP_RMT_GPS_ST_RSVD67               = 1296,  /*  */
    IOP_RMT_GPS_ST_RSVD68               = 1297,  /*  */
    IOP_RMT_GPS_ST_RSVD69               = 1298,  /*  */
    IOP_RMT_GPS_ST_RSVD70               = 1299,  /*  */
    IOP_RMT_GPS_ST_RSVD71               = 1300,  /*  */
    IOP_RMT_GPS_ST_RSVD72               = 1301,  /*  */
    IOP_RMT_GPS_ST_RSVD73               = 1302,  /*  */
    IOP_RMT_GPS_ST_RSVD74               = 1303,  /*  */
    IOP_RMT_GPS_ST_RSVD75               = 1304,  /*  */
    IOP_RMT_GPS_ST_RSVD76               = 1305,  /*  */
    IOP_RMT_GPS_ST_RSVD77               = 1306,  /*  */
    IOP_RMT_GPS_ST_RSVD78               = 1307,  /*  */
    IOP_RMT_GPS_ST_RSVD79               = 1308,  /*  */
    IOP_RMT_GPS_ST_RSVD80               = 1309,  /*  */
    IOP_RMT_GPS_ST_RSVD81               = 1310,  /*  */
    IOP_RMT_GPS_ST_RSVD82               = 1311,  /*  */
    IOP_RMT_GPS_ST_RSVD83               = 1312,  /*  */
    IOP_RMT_GPS_ST_RSVD84               = 1313,  /*  */
    IOP_RMT_GPS_ST_RSVD85               = 1314,  /*  */
    IOP_RMT_GPS_ST_RSVD86               = 1315,  /*  */
    IOP_RMT_GPS_ST_RSVD87               = 1316,  /*  */
    IOP_RMT_GPS_ST_RSVD88               = 1317,  /*  */
    IOP_RMT_GPS_ST_RSVD89               = 1318,  /*  */
    IOP_RMT_GPS_ST_RSVD90               = 1319,  /*  */
    IOP_RMT_GPS_ST_RSVD91               = 1320,  /*  */
    IOP_RMT_GPS_ST_RSVD92               = 1321,  /*  */
    IOP_RMT_GPS_ST_RSVD93               = 1322,  /*  */
    IOP_RMT_GPS_ST_RSVD94               = 1323,  /*  */
    IOP_RMT_GPS_ST_RSVD95               = 1324,  /*  */
    IOP_RMT_GPS_ST_RSVD96               = 1325,  /*  */
    IOP_RMT_GPS_ST_RSVD97               = 1326,  /*  */
    IOP_RMT_GPS_ST_RSVD98               = 1327,  /*  */
    IOP_RMT_GPS_ST_RSVD99               = 1328,  /*  */
    IOP_RMT_GPS_ST_RSVD100              = 1329,  /*  */
    IOP_RMT_GPS_ST_RSVD101              = 1330,  /*  */
    IOP_RMT_GPS_ST_RSVD102              = 1331,  /*  */
    IOP_RMT_GPS_ST_RSVD103              = 1332,  /*  */
    IOP_RMT_GPS_ST_RSVD104              = 1333,  /*  */
    IOP_RMT_GPS_ST_RSVD105              = 1334,  /*  */
    IOP_RMT_GPS_ST_RSVD106              = 1335,  /*  */
    IOP_RMT_GPS_ST_RSVD107              = 1336,  /*  */
    IOP_RMT_GPS_ST_RSVD108              = 1337,  /*  */
    IOP_RMT_GPS_ST_RSVD109              = 1338,  /*  */
    IOP_RMT_GPS_ST_RSVD110              = 1339,  /*  */
    IOP_RMT_GPS_ST_RSVD111              = 1340,  /*  */
    IOP_RMT_GPS_ST_RSVD112              = 1341,  /*  */
    IOP_RMT_GPS_ST_RSVD113              = 1342,  /*  */
    IOP_RMT_GPS_ST_RSVD114              = 1343,  /*  */
    IOP_RMT_GPS_ST_RSVD115              = 1344,  /*  */
    IOP_RMT_GPS_ST_RSVD116              = 1345,  /*  */
    IOP_RMT_GPS_ST_RSVD117              = 1346,  /*  */
    IOP_RMT_GPS_ST_RSVD118              = 1347,  /*  */
    IOP_RMT_GPS_ST_RSVD119              = 1348,  /*  */
    IOP_RMT_GPS_ST_RSVD120              = 1349,  /*  */
    IOP_RMT_GPS_ST_RSVD121              = 1350,  /*  */
    IOP_RMT_GPS_ST_RSVD122              = 1351,  /*  */
    IOP_RMT_GPS_ST_RSVD123              = 1352,  /*  */
    IOP_RMT_GPS_ST_RSVD124              = 1353,  /*  */
    IOP_RMT_GPS_ST_RSVD125              = 1354,  /*  */
    IOP_RMT_GPS_ST_RSVD126              = 1355,  /*  */
    IOP_RMT_GPS_ST_RSVD127              = 1356,  /*  */
    IOP_RMT_GPS_ST_RSVD128              = 1357,  /*  */
    IOP_RMT_GPS_ST_RSVD129              = 1358,  /*  */

    IOP_RMT_GPS_TI_RSVD11               = 1359,  /*  */
    IOP_RMT_GPS_TI_RSVD12               = 1360,  /*  */
    IOP_RMT_GPS_TI_RSVD13               = 1361,  /*  */
    IOP_RMT_GPS_TI_RSVD14               = 1362,  /*  */
    IOP_RMT_GPS_TI_RSVD15               = 1363,  /*  */
    IOP_RMT_GPS_TI_RSVD16               = 1364,  /*  */
    IOP_RMT_GPS_TI_RSVD17               = 1365,  /*  */
    IOP_RMT_GPS_TI_RSVD18               = 1366,  /*  */
    IOP_RMT_GPS_TI_RSVD19               = 1367,  /*  */
    IOP_RMT_GPS_TI_RSVD20               = 1368,  /*  */
    IOP_RMT_GPS_TI_RSVD21               = 1369,  /*  */
    IOP_RMT_GPS_TI_RSVD22               = 1370,  /*  */
    IOP_RMT_GPS_TI_RSVD23               = 1371,  /*  */
    IOP_RMT_GPS_TI_RSVD24               = 1372,  /*  */
    IOP_RMT_GPS_TI_RSVD25               = 1373,  /*  */
    IOP_RMT_GPS_TI_RSVD26               = 1374,  /*  */
    IOP_RMT_GPS_TI_RSVD27               = 1375,  /*  */
    IOP_RMT_GPS_TI_RSVD28               = 1376,  /*  */
    IOP_RMT_GPS_TI_RSVD29               = 1377,  /*  */
    IOP_RMT_GPS_TI_RSVD30               = 1378,  /*  */
    IOP_RMT_GPS_TI_RSVD31               = 1379,  /*  */
    IOP_RMT_GPS_TI_RSVD32               = 1380,  /*  */
    IOP_RMT_GPS_TI_RSVD33               = 1381,  /*  */
    IOP_RMT_GPS_TI_RSVD34               = 1382,  /*  */
    IOP_RMT_GPS_TI_RSVD35               = 1383,  /*  */
    IOP_RMT_GPS_TI_RSVD36               = 1384,  /*  */
    IOP_RMT_GPS_TI_RSVD37               = 1385,  /*  */
    IOP_RMT_GPS_TI_RSVD38               = 1386,  /*  */
    IOP_RMT_GPS_TI_RSVD39               = 1387,  /*  */
    IOP_RMT_GPS_TI_RSVD40               = 1388,  /*  */
    IOP_RMT_GPS_TI_RSVD41               = 1389,  /*  */
    IOP_RMT_GPS_TI_RSVD42               = 1390,  /*  */
    IOP_RMT_GPS_TI_RSVD43               = 1391,  /*  */
    IOP_RMT_GPS_TI_RSVD44               = 1392,  /*  */
    IOP_RMT_GPS_TI_RSVD45               = 1393,  /*  */
    IOP_RMT_GPS_TI_RSVD46               = 1394,  /*  */
    IOP_RMT_GPS_TI_RSVD47               = 1395,  /*  */
    IOP_RMT_GPS_TI_RSVD48               = 1396,  /*  */
    IOP_RMT_GPS_TI_RSVD49               = 1397,  /*  */
    IOP_RMT_GPS_TI_RSVD50               = 1398,  /*  */
    IOP_RMT_GPS_TI_RSVD51               = 1399,  /*  */
    IOP_RMT_GPS_TI_RSVD52               = 1400,  /*  */
    IOP_RMT_GPS_TI_RSVD53               = 1401,  /*  */
    IOP_RMT_GPS_TI_RSVD54               = 1402,  /*  */
    IOP_RMT_GPS_TI_RSVD55               = 1403,  /*  */
    IOP_RMT_GPS_TI_RSVD56               = 1404,  /*  */
    IOP_RMT_GPS_TI_RSVD57               = 1405,  /*  */
    IOP_RMT_GPS_TI_RSVD58               = 1406,  /*  */
    IOP_RMT_GPS_TI_RSVD59               = 1407,  /*  */
    IOP_RMT_GPS_TI_RSVD60               = 1408,  /*  */
    IOP_RMT_GPS_TI_RSVD61               = 1409,  /*  */
    IOP_RMT_GPS_TI_RSVD62               = 1410,  /*  */
    IOP_RMT_GPS_TI_RSVD63               = 1411,  /*  */
    IOP_RMT_GPS_TI_RSVD64               = 1412,  /*  */
    IOP_RMT_GPS_TI_RSVD65               = 1413,  /*  */
    IOP_RMT_GPS_TI_RSVD66               = 1414,  /*  */
    IOP_RMT_GPS_TI_RSVD67               = 1415,  /*  */
    IOP_RMT_GPS_TI_RSVD68               = 1416,  /*  */
    IOP_RMT_GPS_TI_RSVD69               = 1417,  /*  */
    IOP_RMT_GPS_TI_RSVD70               = 1418,  /*  */
    IOP_RMT_GPS_TI_RSVD71               = 1419,  /*  */
    IOP_RMT_GPS_TI_RSVD72               = 1420,  /*  */
    IOP_RMT_GPS_TI_RSVD73               = 1421,  /*  */
    IOP_RMT_GPS_TI_RSVD74               = 1422,  /*  */
    IOP_RMT_GPS_TI_RSVD75               = 1423,  /*  */
    IOP_RMT_GPS_TI_RSVD76               = 1424,  /*  */
    IOP_RMT_GPS_TI_RSVD77               = 1425,  /*  */
    IOP_RMT_GPS_TI_RSVD78               = 1426,  /*  */
    IOP_RMT_GPS_TI_RSVD79               = 1427,  /*  */
    IOP_RMT_GPS_TI_RSVD80               = 1428,  /*  */
    IOP_RMT_GPS_TI_RSVD81               = 1429,  /*  */
    IOP_RMT_GPS_TI_RSVD82               = 1430,  /*  */
    IOP_RMT_GPS_TI_RSVD83               = 1431,  /*  */
    IOP_RMT_GPS_TI_RSVD84               = 1432,  /*  */
    IOP_RMT_GPS_TI_RSVD85               = 1433,  /*  */
    IOP_RMT_GPS_TI_RSVD86               = 1434,  /*  */
    IOP_RMT_GPS_TI_RSVD87               = 1435,  /*  */
    IOP_RMT_GPS_TI_RSVD88               = 1436,  /*  */
    IOP_RMT_GPS_TI_RSVD89               = 1437,  /*  */
    IOP_RMT_GPS_TI_RSVD90               = 1438,  /*  */
    IOP_RMT_GPS_TI_RSVD91               = 1439,  /*  */
    IOP_RMT_GPS_TI_RSVD92               = 1440,  /*  */
    IOP_RMT_GPS_TI_RSVD93               = 1441,  /*  */
    IOP_RMT_GPS_TI_RSVD94               = 1442,  /*  */
    IOP_RMT_GPS_TI_RSVD95               = 1443,  /*  */
    IOP_RMT_GPS_TI_RSVD96               = 1444,  /*  */
    IOP_RMT_GPS_TI_RSVD97               = 1445,  /*  */
    IOP_RMT_GPS_TI_RSVD98               = 1446,  /*  */
    IOP_RMT_GPS_TI_RSVD99               = 1447,  /*  */
    IOP_RMT_GPS_TI_RSVD100              = 1448,  /*  */
    IOP_RMT_GPS_TI_RSVD101              = 1449,  /*  */
    IOP_RMT_GPS_TI_RSVD102              = 1450,  /*  */
    IOP_RMT_GPS_TI_RSVD103              = 1451,  /*  */
    IOP_RMT_GPS_TI_RSVD104              = 1452,  /*  */
    IOP_RMT_GPS_TI_RSVD105              = 1453,  /*  */
    IOP_RMT_GPS_TI_RSVD106              = 1454,  /*  */
    IOP_RMT_GPS_TI_RSVD107              = 1455,  /*  */
    IOP_RMT_GPS_TI_RSVD108              = 1456,  /*  */
    IOP_RMT_GPS_TI_RSVD109              = 1457,  /*  */
    IOP_RMT_GPS_TI_RSVD110              = 1458,  /*  */
    IOP_RMT3_GPS_CMND_END               = 1458,  /*  */

    /*------------------------------------------------------
    Bus Test Command IDs.
    ------------------------------------------------------*/
    IOP_TEST_USB                        = 1459,  /* Start USB Test          */
    IOP_TEST_NXS                        = 1460,  /* Start Nexus Bus Test    */

    /*------------------------------------------------------
    STREAM Memory Benchmark Command IDs.
    ------------------------------------------------------*/
    IOP_TEST_STREAM_MEM                 = 1461,  /* Start STREAM Test       */

    /*------------------------------------------------------
    IOP command to test the functionality of the serial flash.
    ------------------------------------------------------*/
    IOP_SERIAL_FLASH_SELF_TEST          = 1462,

    /*------------------------------------------------------
    IOP command to test the functionality of the rtc.
    ------------------------------------------------------*/
    IOP_RTC_SELF_TEST                   = 1463,

    /*------------------------------------------------------
    IOP command to trigger a Rotation Sensor Test
    ------------------------------------------------------*/
    IOP_ROT_SEN_TEST                    = 1464,

    /*------------------------------------------------------
    IOP command to trigger an IVA Stress Test
    ------------------------------------------------------*/
    IOP_TEST_IVA                        = 1465,

    /*------------------------------------------------------
    IOP command to get barometer local pressure offest
    ------------------------------------------------------*/
    IOP_DOWN_LOAD_BARO_LOCAL_PRESSURE   = 1466,

    /*------------------------------------------------------
    Retrieves the gain factor used to correct the reported
    ambient light value. This should return the current
    gain factor used and whether or not it is valid
    ------------------------------------------------------*/
    IOP_GET_AMB_LGHT_GAIN_FACTOR        = 1467,

    /*------------------------------------------------------
    activity-monitoring submodule
    ------------------------------------------------------*/
    IOP_ACT_MON_CMND_START              = 1468,
    IOP_ACT_MON_CMND_END                = 1479,

    /*------------------------------------------------------
    IOP command to run RGB Video In Test
    ------------------------------------------------------*/
    IOP_VID_IN_RGB_TEST                 = 1480,

    /*------------------------------------------------------
    IOP command to start in-circuit programming.
    ------------------------------------------------------*/
    IOP_ICP_START                       = 1481,

    /*------------------------------------------------------
    Factory Remanufacture Re-Population command
    ------------------------------------------------------*/
    IOP_START_REMANUFACTURE             = 1482,

    /*------------------------------------------------------
    Synchronize Autopilot Dockside Wizard closed notification
    ------------------------------------------------------*/
    IOP_AUP_DOCKSIDE_WIZARD_CLOSE       = 1483,

    /*------------------------------------------------------
    Touchpanel Self Test
    ------------------------------------------------------*/
    IOP_TS_SELF_TEST                    = 1484,

    /*------------------------------------------------------
    IOP command to get power cycle test mode
    ------------------------------------------------------*/
    IOP_PWR_CYCLE_TEST_GET_MODE         = 1485,

    /*------------------------------------------------------
    Command to delete a file that keeps the unit in
    test mode and a command to download the status
    of the file to see if it is deleted.
    ------------------------------------------------------*/
    IOP_TEST_MODE_FILE_DELETE           = 1486,
    IOP_DL_TEST_MODE_FILE_STATUS        = 1487,

    IOP_CLR_NONVOL_UNPROTECTED_ONLY_NO_REBOOT   = 1488,

    /*------------------------------------------------------
    IOP command to get gyro cal status
    ------------------------------------------------------*/
    IOP_DL_GYRO_CAL_STATUS              = 1489,

    /*------------------------------------------------------
    IOP command to disable mag for gyro calibration
    ------------------------------------------------------*/
    IOP_AHRS_DISABLE_MAG                = 1490,

    /*------------------------------------------------------
    IOP command to start in-circuit programming and force
    all updates.
    ------------------------------------------------------*/
    IOP_ICP_FORCE_UPDATES_START         = 1491,

    /*------------------------------------------------------
    IOP command group for 3-axis gyro cal
    ------------------------------------------------------*/
    IOP_3AXIS_GYRO_START_CAL            = 1492,
    IOP_3AXIS_GYRO_CLEAR_CAL            = 1493,
    IOP_3AXIS_GYRO_DL_CAL               = 1494,

    /*------------------------------------------------------
    IOP command to query state of USB mux.
    ------------------------------------------------------*/
    IOP_USB_MUX_GET_STATUS              = 1495,

    /*------------------------------------------------------
    vivosmart touch panel sorting
    ------------------------------------------------------*/
    IOP_PANEL_SORTING_START             = 1496,
    IOP_PANEL_SORTING_STOP              = 1497,
    IOP_PANEL_SORTING_DL_RESULT         = 1498,
    IOP_PANEL_SORTING_DELETE_RESULT     = 1499,

    /*----------------------------------------------------------
    Touch Screen false touch Count request
    ----------------------------------------------------------*/
    IOP_CMND_RQST_TS_FALSE_TCH_CNT      = 1500,

    /*----------------------------------------------------------
    Remote Ambarella A7L Processor Commands
    ------------------------------------------------------*/
    IOP_A7L_REMOTE_AUDIO_LOOPBACK_START = 1501,
    IOP_A7L_REMOTE_AUDIO_LOOPBACK_STOP  = 1502,

    IOP_A7L_REMOTE_LAST_CMND            = 1512,

    /*------------------------------------------------------
    Optical Heart Rate commands
    ------------------------------------------------------*/
    IOP_OHR_CMD_START                   = 1513,

    IOP_OHR_TURN_ON                     = 1513,
    IOP_OHR_TURN_OFF                    = 1514,
    IOP_OHR_GET_VER                     = 1515,
    IOP_OHR_GET_HR                      = 1516,
    IOP_OHR_GET_RESTRICTION             = 1517,

    IOP_OHR_CMD_END                     = 1522,

    /*------------------------------------------------------
    Clear accel/mag cal from nonvol
    ------------------------------------------------------*/
    IOP_CLEAR_ACCEL_CAL                 = 1523,
    IOP_CLEAR_MAG_CAL                   = 1524,

    /*------------------------------------------------------
    Accelerometer temperature calibration
    ------------------------------------------------------*/
    IOP_ACCEL_TEMP_CAL_START            = 1525,
    IOP_ACCEL_TEMP_CAL_STOP             = 1526,
    IOP_ACCEL_TEMP_CAL_CLEAR            = 1527,
    IOP_ACCEL_TEMP_GET_CAL_DATA         = 1528,

    /*------------------------------------------------------
    Check for mag cross axis correction coeff
    ------------------------------------------------------*/
    IOP_CHECK_MAG_CROSS_AXIS_COEFF      = 1529,

    /*------------------------------------------------------
    Heart rate monitor analog front end verification
    ------------------------------------------------------*/
    IOP_HRM_AFE_CMD_START               = 1530,

    IOP_HRM_AFE_TURN_ON                 = 1530,
    IOP_HRM_AFE_TURN_OFF                = 1531,
    IOP_HRM_AFE_GET_PART_NUM            = 1532,
    IOP_HRM_AFE_TEST                    = 1533,

    IOP_HRM_AFE_CMD_END                 = 1539,

    /*------------------------------------------------------
    Temperature Bias Commands
    ------------------------------------------------------*/
    IOP_GET_TEMP_BIAS                   = 1540,

    /*------------------------------------------------------
    Bike Radar Command IDs
    ------------------------------------------------------*/
    IOP_BR_CMD_START                    = 1541,
    IOP_BR_CMD_END                      = 1640,

    /*------------------------------------------------------
    Dynastream Command IDs
    ------------------------------------------------------*/
    IOP_DYNASTREAM_CMD_START            = 1641,

    IOP_BSL_MODE                        = 1641,
    IOP_DUMP_CONFIG_BLOCK               = 1642,
    IOP_GET_BIST_STATUS                 = 1643,

    IOP_DYNASTREAM_CMD_END              = 1650,

    /*------------------------------------------------------
    IOP command group for 3-axis accel cal
    ------------------------------------------------------*/
    IOP_3AXIS_ACCEL_START_CAL           = 1651,
    IOP_3AXIS_ACCEL_CLEAR_CAL           = 1652,
    IOP_3AXIS_ACCEL_DL_CAL              = 1653,

    /*------------------------------------------------------
    Start of next command ID group.
    ------------------------------------------------------*/
    IOP_START_OF_NEXT_CMND              = 1654,

    IOP_LAST_CMND_ID                /* placeholder/no trailing comma*/

    };


typedef uint16 IOP_test_cmnd_id_type; enum
    {
    IOP_TEST_CMND_DONE                  = 0,

    IOP_TEST_CMND_TURN_LEDS_OFF         = 1,
    IOP_TEST_CMND_TURN_LED_1_ON         = 2,
    IOP_TEST_CMND_TURN_LED_2_ON         = 3,

    IOP_LAST_TEST_CMND_ID
    };  /* end IOP_test_cmnd_id_type */


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

#ifdef __cplusplus
}
#endif

#endif  /* _IOP_PUB_CMND_H */
