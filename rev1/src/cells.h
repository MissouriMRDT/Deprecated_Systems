#if !defined( CELLS_H )
#define CELLS_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

#include <stdint.h>

#include <macros.h>

/***************************************************************************
*                             LITERAL CONSTANTS                            *
***************************************************************************/

#define CELL_MAX_VOLTAGE            4.2
#define CELL_MINIMAL_VOLTAGE        3.3
#define CELL_NOMINAL_VOLTAGE        3.7

#define NUM_PACK_CELLS              8

#define PACK_MAX_VOLTAGE            NUM_PACK_CELLS * CELL_MAX_VOLTAGE
#define PACK_MINIMAL_VOLTAGE        NUM_PACK_CELLS * CELL_MINIMAL_VOLTAGE
#define PACK_NOMINAL_VOLTAGE        NUM_PACK_CELLS * CELL_NOMINAL_VOLTAGE

/***************************************************************************
*                                   MACROS                                 *
***************************************************************************/

/***************************************************************************
*                                    TYPES                                 *
***************************************************************************/

typedef uint16_t        t_u16_cell_voltage;

/***************************************************************************
*                              MEMORY CONSTANTS                            *
***************************************************************************/

enum _e_bms_error_states
{
	BMS_STATES_ERROR_NO_ERR         = 0,
	BMS_STATES_ERROR_OVER_VOLTAGE   = bitmsk( 1 ),
	BMS_STATES_ERROR_UNDER_VOLTAGE  = bitmsk( 2 ),
	BMS_STATES_ERROR_OVER_TEMP      = bitmsk( 3 ),
	BMS_STATES_ERROR_UNDER_TEMP     = bitmsk( 4 ),
	BMS_STATES_UNUSED2              = bitmsk( 5 ),
	BMS_STATES_UNUSED1              = bitmsk( 6 ),
	BMS_STATE_ERROR_GENERIC         = bitmsk( 7 ),
};
typedef uint8_t e_bms_error_states;

/***************************************************************************
*                                   CLASSES                                *
***************************************************************************/


/*******************************************************************
*
*   CLASS:
*		c_bms_cell
*
*   DESCRIPTION:
*		Current single cell state
*
*******************************************************************/

typedef struct _c_bms_cell
{
	e_bms_error_states  m_error_state;/* current cell error state   */
	t_u16_cell_voltage  m_current_voltage;
	                                  /* current cell voltage       */
} c_bms_cell;


/*******************************************************************
*
*   CLASS:
*		c_bms_pack
*
*   DESCRIPTION:
*		Current pack state
*
*******************************************************************/

typedef struct _c_bms_pack
{
	c_bms_cell          m_cells[ NUM_PACK_CELLS ];
	                                /* cells in the battery pack    */
	t_u16_cell_voltage  m_max_cell_voltage;
	                                /* maximum cell voltage         */
	t_u16_cell_voltage  m_min_cell_voltage;
	                                /* minimum cell voltage         */
} c_bms_pack;

/***************************************************************************
*                                  VARIABLES                               *
***************************************************************************/

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
