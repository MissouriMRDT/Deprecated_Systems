/*********************************************************************
*
*   MODULE NAME:
*       iap.c
*
*   DESCRIPTION:
*       Contains functions that erase and write flash using
*       NXP iap drivers.
*
* Copyright 2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "GRM_pub.h"
#include "UTL_pub.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

#include "iap_driver.h"
#include "NVM_pub_prj.h"
#include "iap.h"

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

#define FLASH_SECTOR(_v_)       ((_v_) >> 12)

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*********************************************************************
*
*   PROCEDURE NAME:
*       nvm_prv_erase
*
*   DESCRIPTION:
*       This procedure erases a sector of flash
*
*********************************************************************/
void iap_nvm_erase
    (
    uint16 flash_offset
    )
{

__e_iap_status iap_status;

/* Prepare the sector for erase */
iap_status = (__e_iap_status) iap_prepare_sector(FLASH_SECTOR(flash_offset),
        (FLASH_SECTOR(flash_offset) + FLASH_SECTOR_SIZE));
UTL_assert( iap_status == CMD_SUCCESS, UTL_FILE_IAP );

/* Erase the sector */
iap_status = (__e_iap_status) iap_erase_sector(FLASH_SECTOR(flash_offset),
        (FLASH_SECTOR(flash_offset) + FLASH_SECTOR_SIZE));
UTL_assert( iap_status == CMD_SUCCESS, UTL_FILE_IAP );

} /* nvm_prv_erase() */

/****************************************************************************
*
*   PROCEDURE NAME:
*       nvm_prv_write
*
*   DESCRIPTION:
*       Writes 256 bytes or less to flash of type NVM_nonvol_type
*
****************************************************************************/
void iap_nvm_write
    (
    NVM_nonvol_type *data,
    uint32  flash_offset
    )
{

__e_iap_status iap_status;

/* Prepare the sector for writing */
iap_status = (__e_iap_status) iap_prepare_sector(FLASH_SECTOR(flash_offset),
      (FLASH_SECTOR(flash_offset) + FLASH_SECTOR_SIZE));
UTL_assert( iap_status == CMD_SUCCESS, UTL_FILE_IAP );

/* write data to flash */
iap_status = (__e_iap_status) iap_copy_ram_to_flash(data,
      (void *)flash_offset, FLASH_SIZE);
UTL_assert( iap_status == CMD_SUCCESS, UTL_FILE_IAP );

}   /* nvm_prv_write() */
