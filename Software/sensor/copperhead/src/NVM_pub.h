/*********************************************************************
*
*   MODULE NAME:
*       NVM_pub.h
*
*   DESCRIPTION:
*       Header for NVM_main.c and
*       contains macros to read and write to NVM
*
* Copyright 2004-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/
#ifndef NVM_PUB_H_
#define NVM_PUB_H_
/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

#define FLASH_OFFSET    0x7F00

/*--------------------------------------------------------------------
                                TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

#include "NVM_pub_prj.h"
#include "iap.h"
#include "iap_driver.h"

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/

extern NVM_nonvol_type NVM_nonvol_ram;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
*
*   MACRO NAME:
*       NVM_read_nonvol - Read Nonvol
*
*   DESCRIPTION:
*       Retrieve a value from nonvol (actually retrieve the
*       value from the nonvol structure mirrored in RAM).
*       The return value is the parameter's type.  For
*       example, if one of the structure members in the
*       nonvol structure is a boolean named "backlight", the
*       following call returns that boolean's value.
*
*       NVM_read_nonvol(backlight)
*
*       This macro is used to retrieve nonvol values, instead
*       of just using the nonvol structure directly, to provide
*       a similar interface to what is used to write nonvol.
*
*       ? NVM_read_nonvol
*               (
*               _nv_member //Structure member name (nonvol variable)
*               )
*
----------------------------------------------------------*/
#define NVM_read_nonvol(_nv_member) (NVM_nonvol_ram._nv_member)

/*----------------------------------------------------------
*
*   MACRO NAME:
*       NVM_write_nonvol - Write Nonvol
*
*   DESCRIPTION:
*       Write a new value to flash if it differs from the
*       current value in the RAM copy.
*
*       void NVM_write_nonvol
*               (
*               _nv_member, //Structure member name (nonvol variable)
*               _nv_value   //New value for nonvol variable
*               )
*
----------------------------------------------------------*/
#define NVM_write_nonvol(_nv_member, _nv_value)                                         \
    {                                                                                   \
    if (NVM_nonvol_ram._nv_member != _nv_value)                                         \
        {                                                                               \
        NVM_nonvol_ram._nv_member = _nv_value; /* Write value to nonvol variable */     \
        NVM_write();                                                                    \
        }                                                                               \
    }

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

void NVM_pwrp
    (
    void
    );

void NVM_inst_nonvol
    (
    void
    );

void NVM_write
    (
    void
    );

#endif /* NVM_PUB_H_ */
