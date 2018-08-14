/*********************************************************************
*
*   HEADER NAME:
*       UTL_pub_fixed_pnt - Utility Public Fixed Point Declarations
*
*   Copyright 2002-2004 by Garmin Ltd. or its subsidiaries.
*---------------------------------------------------------------------
* $Log$
* $NoKeywords$
*********************************************************************/

#if !defined _UTL_PUB_FIXED_PNT
#define      _UTL_PUB_FIXED_PNT

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
UTL fixed point number fractional portion constants.
----------------------------------------------------------*/
enum
    {
    /* The lower byte is the fractional portion */
    UTL_FIXED_PNT_FRAC_SHIFT   = 8,   /* Shift size to remove fraction */
    UTL_FIXED_PNT_DIVISOR      = 256, /* The fixed point number has this assumed denominator */

    /* Exact fixed point value for .1 */
    UTL_FIXED_PNT_TENTHS_VALUE = (uint8)((256 + 10/2)/10),

    /* The most significant byte used used for number attributes.  They should be OR'd in after the number is generated. */
    UTL_FIXED_PNT_ATTR_MASK    = 0xFF000000,
    UTL_FIXED_PNT_NEGATIVE     = 0x80000000
    };

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*---------------------------------------------------------------
Floating point numbers can be communicated in integer numbers
using this type.  This fixed point number divided by
UTL_FIXED_PNT_DIVISOR is the actual value of the float.
---------------------------------------------------------------*/
typedef uint32 UTL_fixed_pnt_type;      /* The number in fixed point */
typedef uint16 UTL_fixed_pnt_int_type;  /* The middle two bytes are the integer portion */
typedef sint16 UTL_fixed_pnt_sint_type; /* The middle two bytes are the integer portion */
typedef uint8  UTL_fixed_pnt_frac_type; /* The lower byte is the fractional portion */

/*----------------------------------------------------------
Value returned when comparing two fixed point values.
----------------------------------------------------------*/
typedef enum
    {
    UTL_FIXED_PNT_GREATER_THAN,
    UTL_FIXED_PNT_LESS_THAN,
    UTL_FIXED_PNT_EQUAL
    } UTL_fixed_pnt_compare_type;

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

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_cnvrt_int_to_fixed_pnt - Convert Integer to Fixed Point
*
*   DESCRIPTION:
*       Converts an integer to fixed point.
*
*       UTL_fixed_pnt_type UTL_cnvrt_int_to_fixed_pnt
*               (
*               UTL_fixed_pnt_int_type _int
*               )
*
----------------------------------------------------------*/
#define UTL_cnvrt_int_to_fixed_pnt(_int) (((UTL_fixed_pnt_type)(_int) << UTL_FIXED_PNT_FRAC_SHIFT))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_cnvrt_fixed_pnt_to_frac - Convert Fixed Point to Fraction
*
*   DESCRIPTION:
*       Converts a fixed point number to just its fractional
*       component.  The returned value is a numerator with
*       an assumed division by UTL_FIXED_PNT_DIVISOR.
*
*       UTL_fixed_pnt_frac_type UTL_cnvrt_fixed_to_frac
*               (
*               UTL_fixed_pnt_type _fixed_pnt
*               )
*
----------------------------------------------------------*/
#define UTL_cnvrt_fixed_pnt_to_frac(_fixed_pnt) ((UTL_fixed_pnt_frac_type)(_fixed_pnt))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_cnvrt_fixed_pnt_to_int - Convert Fixed Point to Integer
*
*   DESCRIPTION:
*       Converts a fixed point number to just its integer
*       component, abandoning its fractional part.
*
*       UTL_fixed_pnt_int_type UTL_cnvrt_fixed_pnt_to_int
*               (
*               UTL_fixed_pnt_type _fixed_pnt
*               )
*
----------------------------------------------------------*/
#define UTL_cnvrt_fixed_pnt_to_int(_fixed_pnt) ((UTL_fixed_pnt_int_type)(_fixed_pnt >> UTL_FIXED_PNT_FRAC_SHIFT))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_cnvrt_fixed_pnt_to_sint - Convert Fixed Point to Signed Integer
*
*   DESCRIPTION:
*       Converts a fixed point number to just its signed
*       integer component, abandoning its fractional part.
*
*       UTL_fixed_pnt_int_type UTL_cnvrt_fixed_pnt_to_int
*               (
*               UTL_fixed_pnt_type _fixed_pnt
*               )
*
----------------------------------------------------------*/
#define UTL_cnvrt_fixed_pnt_to_sint(_fixed_pnt) ((UTL_fixed_pnt_sint_type)(_fixed_pnt >> UTL_FIXED_PNT_FRAC_SHIFT) * (UTL_is_fixed_pnt_negative(_fixed_pnt) ? -1 : 1))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_cnvrt_fixed_pnt_to_int_round - Convert Fixed Point to Integer Round
*
*   DESCRIPTION:
*       Converts a fixed point number to an integer,
*       rounding up when the fraction value is >= .5.
*
*       UTL_fixed_pnt_int_type UTL_cnvrt_fixed_pnt_to_int
*               (
*               UTL_fixed_pnt_type _fixed_pnt
*               )
*
----------------------------------------------------------*/
#define UTL_cnvrt_fixed_pnt_to_int_round(_fixed_pnt) ((UTL_fixed_pnt_int_type)((_fixed_pnt + UTL_FIXED_PNT_DIVISOR/2) >> UTL_FIXED_PNT_FRAC_SHIFT))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_cnvrt_frac_to_fixed_pnt - Convert Fraction to Fixed Point
*
*   DESCRIPTION:
*       Converts a fraction to fixed point.
*
*       UTL_fixed_pnt_type UTL_cnvrt_frac_to_fixed_pnt
*               (
*               int _numerator,
*               int _denominator
*               )
*
----------------------------------------------------------*/
#define UTL_cnvrt_frac_to_fixed_pnt(_numerator, _denominator) ((_numerator) * UTL_FIXED_PNT_DIVISOR / (_denominator))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_is_fixed_pnt_negative - Is Fixed Point Negative
*
*   DESCRIPTION:
*       Returns true if the fixed point number is negative.
*
*       boolean UTL_is_fixed_pnt_negative
*               (
*               UTL_fixed_pnt_type _fixed_pnt
*               )
*
----------------------------------------------------------*/
#define UTL_is_fixed_pnt_negative(_fixed_pnt) (((_fixed_pnt) & UTL_FIXED_PNT_NEGATIVE) == UTL_FIXED_PNT_NEGATIVE)

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_set_fixed_pnt_negative - Set Fixed Point Negative
*
*   DESCRIPTION:
*       Sets the fixed point value as a negative number.
*
*       void UTL_is_fixed_pnt_negative
*               (
*               UTL_fixed_pnt_type _fixed_pnt
*               )
*
----------------------------------------------------------*/
#define UTL_set_fixed_pnt_negative(_fixed_pnt) ((_fixed_pnt) != 0 ? (_fixed_pnt) | UTL_FIXED_PNT_NEGATIVE : (_fixed_pnt))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_set_fixed_pnt_positive - Set Fixed Point Positive
*
*   DESCRIPTION:
*       Sets the fixed point value as a positive number.
*       Note that -0 is not generated.
*
*       void UTL_is_fixed_pnt_positive
*               (
*               UTL_fixed_pnt_type _fixed_pnt
*               )
*
----------------------------------------------------------*/
#define UTL_set_fixed_pnt_positive(_fixed_pnt) ((_fixed_pnt) & ~UTL_FIXED_PNT_NEGATIVE)

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
UTL_nmbr.c procedures
----------------------------------------------------------*/

UTL_fixed_pnt_type UTL_cnvrt_int_to_fixed_tenths
    (
    uint16 nmbr
    );

UTL_fixed_pnt_type UTL_fixed_pnt_signed_add
    (
    UTL_fixed_pnt_type fixed_pnt_nmbr_1,
    UTL_fixed_pnt_type fixed_pnt_nmbr_2
    );

UTL_fixed_pnt_compare_type UTL_fixed_pnt_signed_compare
    (
    UTL_fixed_pnt_type fixed_pnt_nmbr_1,
    UTL_fixed_pnt_type fixed_pnt_nmbr_2
    );

UTL_fixed_pnt_type UTL_fixed_pnt_signed_subtract
    (
    UTL_fixed_pnt_type fixed_pnt_nmbr_1,
    UTL_fixed_pnt_type fixed_pnt_nmbr_2
    );

#endif  /* _UTL_PUB_FIXED_PNT */