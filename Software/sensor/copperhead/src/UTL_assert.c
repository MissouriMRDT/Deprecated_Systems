/*********************************************************************
*
*   MODULE NAME:
*       UTL_assert.c - Assert Support Routines
*
*   DESCRIPTION:
*       Routines to support asserts.
*
*   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "HWM_pub.h"
#include "IOP_pub.h"
#include "SYC_pub.h"
#include "NVM_pub.h"
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
*       UTL_rpt_failed_assert - Report Failed Assert
*
*   DESCRIPTION:
*       Store the assert information in EEPROM and power down the
*       unit.  The assert information is a file id that uniquely
*       identifies the file (as opposed to a flash-consuming string)
*       and a line number.
*
*       The following shows the EEPROM memory locations where the
*       assert information is stored.
*
*       0x0000 file_id
*       0x0001 least significant byte of the line number
*       0x0002 most significant byte of the line number
*
*********************************************************************/
void UTL_rpt_failed_assert
    (
    UTL_file_id file_id, /* File ID where assert is called */
    uint16 line,          /* Line where assert occurred */
    char date[11],
    char time[8]
    )
{
/*----------------------------------------------------------
Variables
----------------------------------------------------------*/

uint8 i;
uint8 thousands;
uint8 hundreds;
uint8 tens;
uint8 ones;

Chip_GPIO_SetPinDIROutput(LPC_GPIO, 3, 0);
Chip_GPIO_SetPinOutLow(LPC_GPIO, 3, 0);
while(1)
    {
    i = file_id;
    thousands = ( line / 1000 );
    hundreds = ( ( line % 1000 ) / 100 );
    tens = ( ( line % 100 ) / 10 );
    ones = ( line % 10);

    while( i > 0 )
        {
        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);

        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);
        i--;
        }

    SYC_set_timer(UTL_ASSERT_TIMER, 3000);
    while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

    while( thousands > 0 )
        {
        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);

        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);
        thousands--;
        }

    SYC_set_timer(UTL_ASSERT_TIMER, 1000);
    while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

    while( hundreds > 0 )
        {
        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);

        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);
        hundreds--;
        }

    SYC_set_timer(UTL_ASSERT_TIMER, 1000);
    while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

    while( tens > 0 )
        {
        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);

        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);
        tens--;
        }

    SYC_set_timer(UTL_ASSERT_TIMER, 1000);
    while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

    while( ones > 0 )
        {
        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);

        SYC_set_timer(UTL_ASSERT_TIMER, 500);
        while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

        Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 0);
        ones--;
        }

    SYC_set_timer(UTL_ASSERT_TIMER, 5000);
    while ( SYC_is_timer_expired(UTL_ASSERT_TIMER) == FALSE );

    }

}   /* UTL_rpt_failed_assert() */
