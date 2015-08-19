/*********************************************************************
*
*   HEADER NAME:
*       NVM_pub_prj.h
*
* Copyright 2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

#ifndef NVM_PUB_PRJ_H_
#define NVM_PUB_PRJ_H_

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "HWM_pwr_prj.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

#define NVM_VALID   'T'

/*--------------------------------------------------------------------
FLASH_SECTOR_SIZE is 0 for 1 sector, 1 for 2 sectors, etc.
sector size is 4K
--------------------------------------------------------------------*/
#define FLASH_SECTOR_SIZE       0

/*--------------------------------------------------------------------
FLASH_SIZE should be just above the number of bytes in NVM_nonvol_type
FLASH_SIZE can only be 256, 512, 1024, and 4096
--------------------------------------------------------------------*/
#define FLASH_SIZE              256

typedef uint8 HWM_cal_t8; enum
    {
    HWM_STATE_DISABLED,         /* Disabled sensor (not detected)*/
    HWM_STATE_UNCAL,            /* Uncalibrated */
    HWM_STATE_CAL_PARTIAL,      /* Partially calibrated: not ready for use */
    HWM_STATE_CAL,              /* Calibrated: ready for use */
    HWM_STATE_CAL_FULL,         /* Calibration table full: ready for use */

    HWM_DEFAULT_STATE = HWM_STATE_UNCAL
    }; /* HWM_cal_t8 */

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

typedef struct
    {
    uint8                       NVM_valid;

    uint32                      syc_unit_id;

    uint8                       iop_nmea2k_addr;

    uint8                       iop_nmea2k_sys_inst;
    uint8                       iop_nmea2k_dev_inst;

    HWM_sensor_peripheral_t     HWM_sensor_type;
    HWM_cal_t8                  HWM_cal_state;

    uint8                       HWM_temperature_inst;
    uint8                       HWM_temperature_source;
    sint16                      HWM_temperature_offset;     /* Stored in 10E-2 Kelvins */

    } NVM_nonvol_type;

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Store nonvol defaults in flash so that they can be
efficiently copied to RAM.  Every time a new nonvol value is
added, its default should be placed in this structure.
----------------------------------------------------------*/
static NVM_nonvol_type const my_nonvol_defaults =
    {
    /* nvm_valid                    =  */ NVM_VALID,

    /* syc_unit_id                  =  */ 0,

    /* iop_nmea2k_addr              =  */ 0,

    /* iop_nmea2k_sys_inst          =  */ 0,
    /* iop_nmea2k_dev_inst          =  */ 0,

    /* HWM_sensor_type              =  */ TEMPERATURE_SENSOR,
    /* HWM_cal_state                =  */ HWM_DEFAULT_STATE,

    /* HWM_temperature_inst         =  */ 0,
    /* HWM_temperature_source       =  */ 0,
    /* HWM_temperature_offset       =  */ 0,

    };

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

void NVM_pwrp
    (
    void
    );

#endif /* NVM_PUB_PRJ_H_ */
