/*********************************************************************
*
*   MODULE NAME:
*       UTL_str.c - String Utilities
*
*   DESCRIPTION:
*       Routines to support strings.
*
*   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "UTL_pub.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/
#define      TENTHS_MULT (6554)
#define  HUNDREDTHS_MULT  (655)
#define THOUSANDTHS_MULT   (66)

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
*       UTL_bld_int_str_fixed - Build Integer String Fixed
*
*   DESCRIPTION:
*       Build a string of fixed length from an integer.  Asserts if
*       the number of digits allocated for the string is not large
*       enough to hold the number. A NULL terminator will
*       be placed at str[num_digits].
*
*********************************************************************/
void UTL_bld_int_str_fixed
    (
    uint32  nmbr,       /* Integer from which string is to be built */
    uint8   num_digits, /* Number of digits allocated for the string */
    tchr*   str         /* String where integer is written */
    )
{
/*----------------------------------------------------------
Variables
----------------------------------------------------------*/
uint32 tmp;        /* Temporary value */
tchr* str_num_ptr; /* String pointer, writing to memory starting from the last digit */

/*----------------------------------------------------------
Null terminate the string.
----------------------------------------------------------*/
str_num_ptr = str + num_digits;
*str_num_ptr-- = NULL;

/*----------------------------------------------------------
Build the numeric string of integers.
----------------------------------------------------------*/
while(num_digits > 0)
    {
    num_digits--;
    tmp = nmbr / 10;
    *str_num_ptr-- = (char)(nmbr - tmp * 10 + '0');
    nmbr = tmp;
    }

/*----------------------------------------------------------
Make certain all digits were printed.  If this assert fails,
the num_digits parameter was not large enough for the
number given.
----------------------------------------------------------*/
UTL_assert(nmbr == 0, UTL_FILE_UTL_STR);
}   /* UTL_bld_int_str_fixed() */



