/*********************************************************************
*
*   HEADER NAME:
*       IOP_pub_evnt.h - Input/Output Processing Public Declarations
*
* Copyright 2001-2015 by Garmin Ltd. or its subsidiaries.
*
*********************************************************************/

#ifndef _IOP_PUB_EVNT_H
#define _IOP_PUB_EVNT_H

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

/*----------------------------------------------------------
Do not change order, these are standard values, which are
shared with Taiwan, MapSource, and other 3rd party users.
----------------------------------------------------------*/
typedef uint16 IOP_evnt_id_type; enum
    {

    IOP_ALM_COLLECT                         =  0,       /* almanac data collected               */
    IOP_BAD_SV                              =  1,       /* bad space vehicle                    */
    IOP_CONVERGED                           =  2,       /* convergence declared                 */
    IOP_DYNMCS_DTCTD                        =  3,       /* dynamics detected                    */
    IOP_ELEV_FAIL                           =  4,       /* convergence fail due to elev check   */
    IOP_EPH_COLLECT                         =  5,       /* ephemeris data collected             */
    IOP_ERROR                               =  6,       /* error: (see IOP_error_id_type)       */
    IOP_FIX_TRANS                           =  7,       /* pvt fix type transition              */
    IOP_GEOM_POOR                           =  8,       /* ECEF geometry poor                   */
    IOP_HLTH_BAD                            =  9,       /* health decoded as bad                */
    IOP_HLTH_WEAK                           = 10,       /* health decoded as weak               */
    IOP_IMAG_ROOTS                          = 11,       /* imaginary roots                      */
    IOP_KEY_PRESS                           = 12,       /* key press detected                   */
    IOP_LOW_BATT_CHNG                       = 13,       /* low battery power discrete change    */
    IOP_LOWVBACK_CHNG                       = 14,       /* low memory battery discrete change   */
    IOP_MSG_CLRD                            = 15,       /* message cleared                      */
    IOP_MSG_SET                             = 16,       /* message set                          */
    IOP_PARITY_FAIL                         = 17,       /* satellite data parity fail           */
    IOP_PVT_OVFL                            = 18,       /* pvt throughput overflow              */
    IOP_START_AUTO_SRCH                     = 19,       /* auto-search process started          */
    IOP_STATE_TRANS                         = 20,       /* system controller state transition   */
    IOP_STOP_AUTO_SRCH                      = 21,       /* auto-search process stopped          */
    IOP_TIME_SET                            = 22,       /* time set                             */
    IOP_URA_WARNING                         = 23,       /* use at your own risk warning         */
    IOP_UTC_COLLECT                         = 24,       /* UTC leap seconds collected           */
    IOP_VISB_FAILED                         = 25,       /* failed visibility test               */
    IOP_WORD_SYNCD                          = 26,       /* word-sync performed                  */
    IOP_RTCM_BYTE_FMT                       = 27,       /* RTCM byte format detected            */
    IOP_RTCM_RX_DATA                        = 28,       /* RTCM transition to receive data mode */
    IOP_RTCM_DTCT_FMT                       = 29,       /* RTCM transition to detect format mode*/
    IOP_RTCM_FIRST_WRD                      = 30,       /* RTCM first word collected            */
    IOP_RTCM_FRAME_SYNC                     = 31,       /* RTCM frame synchronization           */
    IOP_RTCM_PARITY_FAIL                    = 32,       /* RTCM word parity failure             */
    IOP_RTCM_IOD_MISMTCH                    = 33,       /* RTCM IOD mismatch                    */
    IOP_EPH_BUFFERED                        = 34,       /* Ephemeris buffered                   */
    IOP_EPH_SWITCHED                        = 35,       /* Ephemeris switch from buffer         */
    IOP_RTCM_SYNC_LOST                      = 36,       /* RTCM word sync lost                  */
    IOP_ABORT_DWELL                         = 37,       /* RCV message indicating dwell aborted */
    IOP_FRAME_MISMATCH                      = 38,       /* eph frame not equal to rcv_frm       */
    IOP_FRME_INTRPT                         = 39,       /* Data collection frame interrupted    */
    IOP_CHNLS_OK                            = 40,       /* All available channels are OK        */
    IOP_CARD_CHNG                           = 41,       /* data card detect line change         */
    IOP_RAM_TEST                            = 42,       /* ram test result                      */
    IOP_ROM_TEST                            = 43,       /* !HWM_rom_fail flag                   */
    IOP_BMAP_TEST                           = 44,       /* !HWM_bmap_fail flag                  */
    IOP_FLSH_TEST_RSLT                      = 45,       /* data card flash test results         */
    IOP_SW_EVNT                             = 46,       /* software analysis event (debugging)  */
    IOP_EVNT_OVFL                           = 47,       /* CDP event buffer overflowed          */
    IOP_DPTH_SNDR_TIMEOUT                   = 48,       /* Depth sounder data collect time-out  */
    IOP_MAP_DRAW                            = 49,       /* Map draw state                       */
    IOP_EVNT_UNUSED                         = 50,       /* CDP event was unused by the system   */
    IOP_WX_ALERT_TONE                       = 51,       /* NOAA weather alert tone detected     */
    IOP_JEPP_TEST                           = 52,       /* DBM_pdb_stat != DBM_db_err           */
    IOP_SYC_INIT_DONE                       = 53,       /* Init process complete                */
    IOP_SYN_LOCK                            = 54,       /* Synthesizer lock state               */
    IOP_ANT_BIAS_CHNG                       = 55,       /* Antenna bias change; 0=OK, !0=shorted*/
    IOP_GPROM_TEST                          = 56,       /* !HWM_gp_rom_fail flag                */
    IOP_DTMF_RCVD                           = 57,       /* DTMF tone decoded; data = tone enum  */
    IOP_PROT_ONE_ENBL                       = 58,       /* Protection One (enable=1, disable=0) */
    IOP_GPS_LSI_TEST                        = 59,       /* GPS LSI test                         */
    IOP_BRVO_ROM_TEST                       = 60,       /* Bravo checksum test (0=fail;1=pass)  */
    IOP_EEPRM_TEST                          = 61,       /* EEPROM test result                   */
    IOP_CMPS_CAL_CMPLT                      = 62,       /* Compass calibration complete         */
    IOP_SONR_CAL_CMPLT                      = 63,       /* Sonar calibration complete           */
    IOP_SMAP_TEST                           = 64,       /* Supplemental map region test         */
    IOP_CAN_TEST_RSLT                       = 65,       /* CAN bus test result (0=fail;1=pass)  */
    IOP_AUDIO_TEST                          = 66,       /* Audio region test result             */
    IOP_AUDIO_TEST2                         = 67,       /* Second Audio region test result      */
    IOP_COM_SQUELCH                         = 68,       /* COM squelch state change             */
    IOP_COM_SQTONE                          = 69,       /* COM squelch tone detected            */
    IOP_COM_VOX                             = 70,       /* COM VOX state change                 */
    IOP_EXT_VOLT                            = 71,       /* External voltage change              */
    IOP_COM_EXT_HEADSET                     = 72,       /* External headset change              */
    IOP_SPLSH_SCRN_TEST                     = 73,       /* Splash screen test result            */
    IOP_PEN_PRESS                           = 74,       /* PEN press detected                   */
    IOP_GYRO_CLKW_TEST                      = 75,       /* Clockwise Gyro test result           */
    IOP_GYRO_CCLKW_TEST                     = 76,       /* Counter Clockwise Gyro test result   */
    IOP_RDR_ROT_SLIP                        = 77,       /* Radar rotational slip                */
    IOP_RDR_ROT_CORR                        = 78,       /* Radar rotational speed correction    */
    IOP_RDR_DATA_MISSED                     = 79,       /* Some Radar pulses have been skipped  */
    IOP_ETHERNET_STATUS                     = 80,       /* Ethernet Status                      */
    IOP_FIX_REJECTED                        = 81,       /* Fix failed reasonability test        */
    IOP_HEATER_STATUS                       = 82,       /* Heater on/off status                 */
    IOP_TERRAIN_TEST                        = 83,       /* Terrain database tests               */
    IOP_RDR_AFC_FAIL                        = 84,       /* Marine Radar AFC failure             */
    IOP_XM_DATA_LINK_GOOD_PACKETS           = 85,       /* XM Data Link Good Packets            */
    IOP_XM_DATA_LINK_BAD_PACKETS            = 86,       /* XM Data Link Bad Packets             */
    IOP_USB_SENSE_MEAS                      = 87,       /* External ID reading                  */
    IOP_XM_CBM_TEST_RESULT                  = 88,       /* XM CBM Test Result                   */
    IOP_XM_SPI_TEST_RESULT                  = 89,       /* XM SPI Test Result                   */
    IOP_XM_ANTENNA_UPDATE                   = 90,       /* XM Antenna Update                    */
    IOP_BT_INCOMING_CALL                    = 91,       /* Bluetooth has an incoming call       */
    IOP_SIRF_UPDT_START                     = 92,       /* SIRF update has started              */
    IOP_BT_UPDT_START                       = 93,       /* Bluetooth update has started         */
    IOP_PLD_UPDT_START                      = 94,       /* PLD update has started               */
    IOP_NV_FLUSH_CMPLT                      = 95,       /* NVM has completed a flush            */
    IOP_DEL_AUD_SUM_CMPLT                   = 96,       /* Deleting audio checksum files cmplt  */
    IOP_POI_DB_TEST                         = 97,       /* Pre-loaded POI Database Test Result  */
    IOP_MIC_CNG                             = 98,       /* Microphone change                    */
    IOP_FAN_TEST                            = 99,       /* fan test result                      */
    IOP_TOUCH_SCREEN_TEST                   = 100,      /* touch screen test result             */
    IOP_EXT_ETHR_PRT_0_STATUS               = 101,      /* External Ethernet Port 0 Status      */
    IOP_EXT_ETHR_PRT_1_STATUS               = 102,      /* External Ethernet Port 1 Status      */
    IOP_EXT_ETHR_PRT_2_STATUS               = 103,      /* External Ethernet Port 2 Status      */
    IOP_EXT_ETHR_PRT_3_STATUS               = 104,      /* External Ethernet Port 3 Status      */
    IOP_EXT_ETHR_PRT_4_STATUS               = 105,      /* External Ethernet Port 4 Status      */
    IOP_TS_LIN_PRSNT                        = 106,      /* Touch Screen linearization present   */
    IOP_GRAPHICS_RAM_TEST                   = 107,      /* Graphics RAM Test Result             */
    IOP_LPBK_PORT_0_RX_STATUS               = 108,      /* Loopback RX test result for port 0   */
    IOP_LPBK_PORT_1_RX_STATUS               = 109,      /* Loopback RX test result for port 1   */
    IOP_LPBK_PORT_2_RX_STATUS               = 110,      /* Loopback RX test result for port 2   */
    IOP_LPBK_PORT_3_RX_STATUS               = 111,      /* Loopback RX test result for port 3   */
    IOP_LPBK_PORT_4_RX_STATUS               = 112,      /* Loopback RX test result for port 4   */
    IOP_LPBK_PORT_0_TX_STATUS               = 113,      /* Loopback TX test result for port 0   */
    IOP_LPBK_PORT_1_TX_STATUS               = 114,      /* Loopback TX test result for port 1   */
    IOP_LPBK_PORT_2_TX_STATUS               = 115,      /* Loopback TX test result for port 2   */
    IOP_LPBK_PORT_3_TX_STATUS               = 116,      /* Loopback TX test result for port 3   */
    IOP_LPBK_PORT_4_TX_STATUS               = 117,      /* Loopback TX test result for port 4   */
    IOP_DEMO_RGN_TEST                       = 118,      /* Demo RGN test result                 */
    IOP_COLOR_CYCLE_CMPLT                   = 119,      /* Test Mode color page cycle complete  */
    IOP_ANT_HR_UPDATE                       = 120,      /* New ANT HR reading                   */
    IOP_ANT_CADENCE_UPDATE                  = 121,      /* New ANT cadence reading              */
    IOP_ANT_SPEED_UPDATE                    = 122,      /* new ANT speed reading                */
    IOP_ANT_POWER_UPDATE                    = 123,      /* new ANT power reading                */
    IOP_ANT_DISTANCE_UPDATE                 = 124,      /* new ANT distance reading             */
    IOP_ANT_ALWAYSON_CONNECT                = 125,      /* ANT Always-On Connection status      */
    IOP_ANT_RSRV2                           = 126,      /* ANT IOP event for factory testing    */
    IOP_ANT_RSRV3                           = 127,      /* ANT IOP event for factory testing    */
    IOP_ANT_RSRV4                           = 128,      /* ANT IOP event for factory testing    */
    IOP_ANT_RSRV5                           = 129,      /* ANT IOP event for factory testing    */
    IOP_ROLLER_POSN_UPDATE                  = 130,      /* New roller position update           */
    IOP_NMEA2K_POWER_DETECT                 = 131,      /* NMEA2000 poweron detected            */
    IOP_EFIELD_TEST_START                   = 132,      /* EFIELD IOP event for factory testing */
    IOP_EFIELD_TEST_RESULT                  = 133,      /* EFIELD IOP event for factory testing */
    IOP_EFIELD_TEST_RSRV1                   = 134,      /* EFIELD IOP event for factory testing */
    IOP_EFIELD_TEST_RSRV2                   = 135,      /* EFIELDRSRV IOP event for factory testing */
    IOP_FAN2_TEST                           = 136,      /* second fan test result               */
    IOP_PORT_0_RX_STATUS                    = 137,      /* RX line state for port 0             */
    IOP_ANT_TXRX_RESULT                     = 138,      /* result of ANT TX/RX test             */
    IOP_ANT_PAIR_CMPLT                      = 139,      /* notification of pairing complete     */
    IOP_BT_MODE_CHNG                        = 140,      /* BT mode change event                 */
    IOP_DEL_ALL_XSUM_CMPLT                  = 141,      /* Deleting all checksum files cmplt    */
    IOP_AVTN_FLGHT_CHART_TEST               = 142,      /* Aviation FlightChart test result     */
    IOP_PFD_MODE_CHNG                       = 143,      /* Aviation PFD Mode Change event       */
    IOP_SHTDWN_CMPLT                        = 144,      /* Unit has safely shutdown             */
    IOP_RFRSH_CMPLT                         = 145,      /* MLC NAND refresh is complete         */
    IOP_OBSTACLE_TEST                       = 146,      /* Obstacle database test status        */
    IOP_PLD_UPDT_CMPLT                      = 147,      /* PLD update is complete               */
    IOP_CNFG_MOD_TEST                       = 148,      /* Config Module Test status            */
    IOP_CAMERA_FOCUS_CMPLT                  = 149,      /* Camera Focus Complete                */
    IOP_IMG_PROC_TEST_RSLT                  = 150,      /* Image Processor Test Result          */
    IOP_RFRSH_START                         = 151,      /* MLC NAND refresh started             */
    IOP_SCRN_CAL_CMPLT                      = 152,      /* Screen Calibration complete          */
    IOP_ZIP_UPDT_CMPLT                      = 153,      /* Zip Update Process complete          */
    IOP_BB_HOLD_STATUS                      = 154,      /* Status of Hold in BB pin (hi or low) */
    IOP_MANIFEST_STATUS                     = 155,      /* Status of manifest generation        */
    IOP_BACKUP_CAMERA_PRESENT               = 156,      /* Is backup camera present             */
    IOP_FRONT_AUX_DET                       = 157,      /* Is front aux jack in use             */
    IOP_REAR_AUX_DET                        = 158,      /* Is rear aux jack in use              */
    IOP_SHUTDOWN_STATUS                     = 159,      /* Status of shutdown log generation    */
    IOP_KEY_TEST_CMPLT                      = 160,      /* Key Test is complete                 */
    IOP_AVTN_IFR_VFR_CHART_TEST             = 161,      /* Aviation IFR/VFR Chart test result   */
    IOP_VOLUME_CHANGE                       = 161,      /* Audio volume change event            */
    IOP_ILLUM_CHANGE                        = 162,      /* Illumination signal state changed    */
    IOP_EVNT_VIM                            = 163,      /* VIM Generated Event                  */
    IOP_NV_MOVE_EVNT                        = 164,      /* Nonvol move/defrag                   */
    IOP_ENCODER_ROTATE                      = 165,      /* Rotary encoder rotattion detected    */
    IOP_JOYSTICK_MOVE                       = 166,      /* Joystick movement detected           */
    IOP_EXT_ETHR_PRT_5_STATUS               = 167,      /* External Ethernet Port 5 Status      */
    IOP_BATT_PACK_CHNG                      = 168,      /* Battery Pack Present Status Changed  */
    IOP_CAMERA_FLASH_FAULT                  = 169,      /* Fault recieved from Flash Driver     */
    IOP_CARD_CHNG_2                         = 170,      /* data card 2 detect line change       */
    IOP_BMAP_TEST_STATUS                    = 171,      /* BaseMap Test Status. TRUE = Testing  */
    IOP_RAM_TEST_STATUS                     = 172,      /* RAM Test Status.     TRUE = Testing  */
    IOP_RAM_TEST_QUICK                      = 173,      /* Quick ram test result                */
    IOP_CAMERA_FLASH_STATUS                 = 174,      /* Flash status for image capture       */
    IOP_BIOS_OP_RESULT_EVNT                 = 175,      /* Handle BIOS related operation event  */
    IOP_BT_PWR_CHNG                         = 176,      /* BT power change event                */
    IOP_USB_TEST                            = 177,      /* USB bus pass/fail test result        */
    IOP_NXS_BUS_TEST                        = 178,      /* Nexus bus pass/fail test result      */
    IOP_LED_LVL_TEST                        = 179,      /* LED Level pass/fail test result      */
    IOP_ROT_SEN_TEST_RSLT                   = 180,      /* Rotation Sensor test result          */
    IOP_IVA_TEST_RSLT                       = 181,      /* IVA stress test result               */
    IOP_TSC_UPDT_START                      = 182,      /* Touch Screen Update Starting         */
    IOP_TSC_UPDT_RSLT                       = 183,      /* Touch Screen Update Result           */
    IOP_TSC_GRID_TEST_RSLT                  = 184,      /* Touch Screen Grid Test Result        */

    IOP_LAST_EVNT_ID
    }; /* IOP_evnt_id_type */


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

#endif  /* _IOP_PUB_EVNT_H */
