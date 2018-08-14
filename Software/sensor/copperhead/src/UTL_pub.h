/*********************************************************************
*
*   HEADER NAME:
*       UTL_pub.h - Utility Public Declarations
*
*   Copyright 2002-2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

#if !defined _UTL_PUB
#define      _UTL_PUB

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "GRM_pub.h"
#include "UTL_pub_assert_prj.h"
#include "UTL_pub_fixed_pnt.h"

/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*----------------------------------------------------------
The max enumeration value constant is used to generate a
compiler assert.
----------------------------------------------------------*/
#define MAX_ENUM_VALUE (32767)

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

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_assert - Assert
*
*   DESCRIPTION:
*       Runtime macro that asserts when _e is 0 and
*       _GRM_ASSERT == _ON.  Otherwise do nothing.
*
*       A file id is used to identify the file, as opposed
*       to a file name string since the file id consumes
*       much less flash space.
*
*       void UTL_assert
*               (
*               _e,                  //Assert if this value is 0
*               UTL_file_id _file_id //File ID where assert is called
*               )
*
----------------------------------------------------------*/
#if(_GRM_ASSERT == _ON)

    #define UTL_assert(_e, _file_id)                   \
        {                                              \
        if((_e) == FALSE)                              \
            {                                          \
            UTL_rpt_failed_assert(_file_id, __LINE__, __DATE__,__TIME__); \
            }                                          \
        }

#else

    #define UTL_assert(_e, _file_id)

#endif /* _GRM_ASSERT */

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_assert_always - Always assert
*
*   DESCRIPTION:
*       Runtime macro that always asserts if _GRM_ASSERT == _ON.
*       Otherwise do nothing.
*
*       void UTL_assert_always
*               (
*               UTL_file_id _file_id //File ID where assert is called
*               )
*
----------------------------------------------------------*/
#define UTL_assert_always(_file_id) UTL_assert(FALSE, _file_id)

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_calc_mask_bit_uint8 - Calculate Mask Bit uint8
*
*   DESCRIPTION:
*       Calculates the bit in a uint8 mask that is set.  For
*       example, (1 << 0) returns 0 and (1 << 7) returns 7.
*
*       uint8 UTL_calc_mask_bit_uint8
*               (
*               uint8 _mask //Mask to examine
*               )
*
----------------------------------------------------------*/
#define UTL_calc_mask_bit_uint8(_mask) (UTL_log2_uint8(_mask))

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_compiler_assert - Compiler Assert
*
*   DESCRIPTION:
*       Compile time macro that asserts when _e is 0.  The
*       _file parameter should be the filename where the assert
*       occurs and is used simply to create a unique enumeration
*       name so naming conflicts do not occur.
*
*       Note that the maximum valid enumeration value must be
*       explicitly defined: max_sint_val(signed int) cannot be
*       used since, though the compiler generates the correct
*       value, the compiler does not detect an overflow when
*       the macro is used.
*
*       UTL_compiler_assert
*               (
*               _e,   //Assert if this value is 0
*               _file //Filename where assert is called
*               )
*
----------------------------------------------------------*/
#define UTL_compiler_assert(_e, _file)                                \
    enum  tokcat(___compiler_assert_test_, tokcat(_file, __LINE__))   \
        {                                                             \
        tokcat(___, tokcat(_file, __LINE__)) = MAX_ENUM_VALUE + !(_e) \
        }

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_get_indx - Get Index
*
*   DESCRIPTION:
*       Searches a table in flash for a value and returns
*       the index where the value was found.
*
*       UTL_get_indx
*               (
*               int _value,         //Value for which to search
*               flash_uint8* _table //Table where value is stored
*               )
*
----------------------------------------------------------*/
#define UTL_get_indx(_value, _table )  \
    UTL_get_indx_fcn                   \
        (                              \
        (uint8 const*)&(_value),       \
        sizeof(_value),                \
        ((flash_uint8*)_table),        \
        sizeof((_table)[0]),           \
        cnt_of_array(_table)           \
        )

/*----------------------------------------------------------
*
*   MACRO NAME:
*       UTL_get_indx_dflt - Get Index with Default
*
*   DESCRIPTION:
*       Searches a table in flash for a value and returns
*       the index where the value was found. If no match is
*       found, dflt will be returned.
*
*       UTL_get_indx
*               (
*               int _value,             //Value for which to search
*               flash_uint8* _table,    //Table where value is stored
*               int _dflt
*               )
*
----------------------------------------------------------*/
#define UTL_get_indx_dflt(_value, _table, _dflt )   \
    UTL_get_indx_fcn_dflt                           \
        (                                           \
        (uint8 const*)&(_value),                    \
        sizeof(_value),                             \
        ((flash_uint8*)_table),                     \
        sizeof((_table)[0]),                        \
        cnt_of_array(_table),                       \
        (_dflt)                                     \
        )

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*----------------------------------------------------------
UTL_assert.c procedures
----------------------------------------------------------*/

void UTL_rpt_failed_assert
    (
    UTL_file_id file_id,
    uint16 line,
    char date[11],
    char time[8]
    );

/*----------------------------------------------------------
UTL_mem.s procedures
----------------------------------------------------------*/

/*boolean UTL_cmp_flash_to_ram
    (
    flash_uint8* flash_ptr,
    uint8 const* ram_ptr,
    uint8 size
    );

void UTL_copy_flash_to_ram
    (
    uint8* ram_ptr,
    flash_uint8* flash_ptr,
    uint16 size
    );*/

void UTL_copy_ram_to_ram
    (
    uint8* ram_dest_ptr,
    uint8 const* ram_src_ptr,
    uint8 size
    );

sint8 UTL_memcmp
    (
    uint8* ram_ptr1,
    uint8* ram_ptr2,
    uint8  size
    );

void UTL_memset
    (
    uint8* ram_ptr,
    uint8 value,
    uint16 size
    );

/*----------------------------------------------------------
UTL_get_index.c procedures
----------------------------------------------------------*/

/*uint8 UTL_get_indx_fcn
    (
    void const* val_ptr,
    uint8 val_sz,
    flash_uint8* tbl,
    uint8 tbl_entry_sz,
    uint8 tbl_cnt
    );

uint8 UTL_get_indx_fcn_dflt
    (
    void const* val_ptr,
    uint8 val_sz,
    flash_uint8* tbl,
    uint8 tbl_entry_sz,
    uint8 tbl_cnt,
    uint8 dflt
    );*/

/*----------------------------------------------------------
UTL_nmbr.c procedures
----------------------------------------------------------*/

uint8 UTL_cnt_digits_uint8
    (
    uint8 nmbr
    );

uint8 UTL_cnt_digits_uint16
    (
    uint16 nmbr
    );

uint8 UTL_log2_uint8
    (
    uint8 nmbr
    );

/*----------------------------------------------------------
UTL_str.c procedures
----------------------------------------------------------*/

uint8 UTL_bld_frac_str
    (
    uint8 numerator,
    tchr* str
    );

uint8 UTL_bld_float_str_auto
    (
    UTL_fixed_pnt_type fixed_pnt_nmbr,
    tchr* str,
    uint8 max_int_digits_with_decimal
    );

uint8 UTL_bld_int_str_auto
    (
    uint16 nmbr,
    tchr* str
    );

void UTL_bld_int_str_fixed
    (
    uint32  nmbr,
    uint8   num_digits,
    tchr*   str
    );

void UTL_bld_byte_str_fixed
    (
    uint8   nmbr,       /* Byte from which string is to be built */
    tchr*   str         /* String where byte hex is written */
    );

/*void UTL_copy_str_flash
    (
    tchr* str_ram,
    flash_tchr * str_flash
    );*/

boolean UTL_float_str_to_fixed
    (
    uint8        const * str_p,
    uint8                str_len,
    UTL_fixed_pnt_type * fp_num_out
    );

uint8 UTL_strlen
    (
    tchr const* str
    );

/*uint8 UTL_strlen_flash
    (
    flash_tchr * str
    );*/


#endif  /* _UTL_PUB */
