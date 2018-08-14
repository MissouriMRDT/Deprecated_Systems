/*********************************************************************
*
*   HEADER NAME:
*       GRM_pub.h - Public Declarations
*
*   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

#if !defined _GRM_PUB
#define      _GRM_PUB

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "GRM_pub_s.h"
#include "GRM_pub_prj.h"


/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
Define the ASSERT conditional that enables/disables run time
condition testing.
----------------------------------------------------------*/
#if(_RELBLD == _ON)
    #define _GRM_ASSERT _OFF /* Release code disables asserts */
#else
    #define _GRM_ASSERT _ON
#endif


/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
RAM variable types
----------------------------------------------------------*/
    typedef signed char             sint8;
    typedef unsigned char           uint8;
    typedef char                    tchr;
    typedef signed short            sint16;
    typedef unsigned short          uint16;
    typedef signed int              sint32;
    typedef unsigned int            uint32;

#define uint64 uint32 /* Not supported */

/*----------------------------------------------------------
Boolean type
----------------------------------------------------------*/
typedef uint8 boolean;

typedef uint16                      GRM_product_nmbr_u16;
typedef uint16                      GRM_sw_vrsn_nmbr_u16;

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
*       max_sint_val - Maximum Signed Integer Value
*
*   DESCRIPTION:
*       Returns the maximum signed integral value for the
*       given type.
*
*       int max_sint_val
*               (
*               _t //Must be a valid argument for sizeof.
*               )
*
----------------------------------------------------------*/
#define max_sint_val(_t)    (setbits(0, (sizeof(_t) * 8) - 1))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       min_sint_val - Minimum Signed Integer Value
*
*   DESCRIPTION:
*       Returns the minimum signed integral value for the
*       given type.
*
*       int min_sint_val
*               (
*               _t //Must be a valid argument for sizeof.
*               )
*
----------------------------------------------------------*/
#define min_sint_val(_t)    (sint32)(~max_sint_val(_t))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       max_uint_val - Maximum Unigned Integer Value
*
*   DESCRIPTION:
*       Returns the maximum unsigned integral value for the
*       given type.
*
*       int max_uint_val
*               (
*               _t //Must be a valid argument for sizeof.
*               )
----------------------------------------------------------*/
#define max_uint_val(_t)    (setbits(0, (sizeof(_t) * 8)))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       offsetof - Offset Of
*
*   DESCRIPTION:
*       Returns the byte offset of a field within a
*       structure.
*
*       uint32 offsetof
*               (
*               _type, //Structure type
*               _mem   //Structure member
*               )
*
----------------------------------------------------------*/
#define offsetof(_type, _mem) (((uint8*)&((_type*)0)->_mem - (uint8*)(_type*)0))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       tokcat - Token Concatenation
*
*   DESCRIPTION:
*       Returns a single C token that is the result of
*       concatenating two tokens.  For example, if
*       "tokcat( _, __LINE__)" appears at line 123, it will be
*       replaced with "_123" by the preprocessor.
*
*       Note that _tokcat() only exists to allow tokcat() to
*       get around preprocessor substitution rules.
*
*       string tokcat
*               (
*               _token1, //Left token to concatenate
*               _token2  //Right token to concatenate
*               )
*
----------------------------------------------------------*/
#define _tokcat(_token1, _token2)   _token1 ## _token2
#define tokcat(_token1, _token2)    _tokcat(_token1, _token2)

/*----------------------------------------------------------
*
*   MACRO NAME:
*       stringize - Stringize
*
*   DESCRIPTION:
*       Places string quote characters around the specified
*       argument.
*
*       Note that _stringize() only exists to allow stringize()
*       to get around preprocessor substitution rules.
*
*       string stringize
*               (
*               _token  //Token to place quotes around
*               )
*
----------------------------------------------------------*/
#define _stringize(_token)       #_token
#define stringize(_token)        _stringize(_token)

/*----------------------------------------------------------
*
*   MACRO NAME:
*       cnt_of_array - Count of Array
*
*   DESCRIPTION:
*       Returns the number of elements in the array.
*
*       int cnt_of_array
*               (
*               _array  //Variable name of array to count
*               )
*
----------------------------------------------------------*/
#define cnt_of_array(_array)    (sizeof(_array) / sizeof((_array)[0]))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       setbits - Set Bits
*
*   DESCRIPTION:
*       Sets a variable number of bits: setbits(2, 3)
*       returns 00011100.
*
*       int setbits
*               (
*               _bit, //Least significant bit to set
*               _len  //Number of bits to set
*               )
*
----------------------------------------------------------*/
#define setbits(_bit, _len)     ((((uint32)1 << ((_len) - 1)) - (uint32)1 + ((uint32)1 << ((_len) - 1))) << (_bit))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       setbit - Set Bit
*
*   DESCRIPTION:
*       Sets a single bit: setbit(2) returns 00000100.
*
*       int setbit
*               (
*               _bit //Bit location to set
*               )
*
----------------------------------------------------------*/
#define setbit(_bit)            ((uint32)1 << (_bit))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       clrbits - Clear Bits
*
*   DESCRIPTION:
*       Clears a variable number of bits: clrbits(2, 3)
*       returns 11100011.
*
*       int clrbits
*               (
*               _bit, //Least significant bit to clear
*               _len  //Number of bits to clear
*               )
*
----------------------------------------------------------*/
#define clrbits(_bit, _len)      (~setbits((_bit), (_len)))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       clrbit - Clear Bit
*
*   DESCRIPTION:
*       Clears a single bit: clrbit(2) returns 11111011.
*
*       int clrbit
*               (
*               _bit //Bit location to clear
*               )
*
----------------------------------------------------------*/
#define clrbit(_bit)            (~setbit(_bit))


/*----------------------------------------------------------
*
*   MACRO NAME:
*       putbits - Put Bits
*
*   DESCRIPTION:
*       Returns the result of copying a variable number over
*       a value.
*
*       int putbits
*               (
*               _bits,      //Value of bits to put
*               _val,       //Value over which bits should be copied
*               _first_bit, //First (low) bit to be copied ver
*               _num_bits,  //Number of bits to transfer
*               )
*
----------------------------------------------------------*/
#define putbits(_bits, _val, _first_bit, _num_bits) \
    (((_val) & clrbits((_first_bit), (_num_bits))) | (((unsigned)(_bits) & setbits(0, (_num_bits))) << (_first_bit)))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       absval - Absolute Value
*
*   DESCRIPTION:
*       Returns the absolute value.
*
*       minval
*           (
*           _x //Value to retrieve maximum value
*           )
*
----------------------------------------------------------*/
#define absval(_x) ((_x) >= 0 ? (_x) : (-_x))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       maxval32 - Maximum Value
*
*   DESCRIPTION:
*       Returns the maximum between two uint32 values.
*
*       minval
*           (
*           uint32 _x, //First value to compare
*           uint _y  //Second value to compare
*           )
*
----------------------------------------------------------*/
#define maxval32(_x, _y)          ((uint32)(_x) > (uint32)(_y) ? (_x) : (_y))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       maxval16 - Maximum Value
*
*   DESCRIPTION:
*       Returns the maximum between two uint16 values.
*
*       minval
*           (
*           uint16 _x, //First value to compare
*           uint16 _y  //Second value to compare
*           )
*
----------------------------------------------------------*/
#define maxval16(_x, _y)          ((uint16)(_x) > (uint16)(_y) ? (_x) : (_y))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       maxval8 - Maximum Value
*
*   DESCRIPTION:
*       Returns the maximum between two uint8 values.
*
*       minval
*           (
*           uint8 _x, //First value to compare
*           uint8 _y  //Second value to compare
*           )
*
----------------------------------------------------------*/
#define maxval8(_x, _y)          ((uint8)(_x) > (uint8)(_y) ? (_x) : (_y))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       minval32 - Minimum Value
*
*   DESCRIPTION:
*       Returns the minimum between two uint32 values.
*
*       minval
*           (
*           uint32 _x, //First value to compare
*           uint32 _y  //Second value to compare
*           )
*
----------------------------------------------------------*/
#define minval32(_x, _y)          ((uint32)(_x) < (uint32)(_y) ? (_x) : (_y))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       minval16 - Minimum Value
*
*   DESCRIPTION:
*       Returns the minimum between two uint16 values.
*
*       minval
*           (
*           uint16 _x, //First value to compare
*           uint16 _y  //Second value to compare
*           )
*
----------------------------------------------------------*/
#define minval16(_x, _y)          ((uint16)(_x) < (uint16)(_y) ? (_x) : (_y))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       minval8 - Minimum Value
*
*   DESCRIPTION:
*       Returns the minimum between two uint8 values.
*
*       minval
*           (
*           uint8 _x, //First value to compare
*           uint8 _y  //Second value to compare
*           )
*
----------------------------------------------------------*/
#define minval8(_x, _y)          ((uint8)(_x) < (uint8)(_y) ? (_x) : (_y))

#define compiler_assert(_x) UTL_compiler_assert(_x, 0)

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

void GRM_get_build_description
    (
    tchr        * const string_ptr
    );

void GRM_get_product_string
    (
    tchr        * const string_ptr
    );

void GRM_get_version_string
    (
    tchr        * const string_ptr
    );

void GRM_get_model_version_string
    (
    tchr        * const string_ptr
    );

#endif  /* _GRM_PUB */
