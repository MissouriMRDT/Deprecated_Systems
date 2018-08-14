#if !defined( STATUS_MONOTORING_H )
#define STATUS_MONOTORING_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

#include <stdint.h>

#include <msp_pin.h>
#include <error_states.h>

/***************************************************************************
*                             LITERAL CONSTANTS                            *
***************************************************************************/

/***************************************************************************
*                                   MACROS                                 *
***************************************************************************/

/***************************************************************************
*                                    TYPES                                 *
***************************************************************************/

/***************************************************************************
*                              MEMORY CONSTANTS                            *
***************************************************************************/

/***************************************************************************
*                                   CLASSES                                *
***************************************************************************/

/***************************************************************************
*                                  VARIABLES                               *
***************************************************************************/

extern uint16_t         pack_voltage_array;
                                    /* pack voltage from bms leads  */
extern uint16_t         pack_discarge_current;
                                    /* current pack discharge       */
extern uint16_t         pack_voltage_out;
                                    /* pack voltage out of bms      */

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/

extern inline bool status_is_estop_1_active
	(
		void
	);

extern inline bool status_is_estop_2_active
	(
		void
	);

e_error_states status_powerup
	(
		void
	);

e_error_states status_read_pack_volt_current
	(
		void
	);

extern inline e_error_states status_turn_rover_off
	(
		void
	);

extern inline e_error_states status_turn_rover_on
	(
		void
	);

#ifdef __cplusplus
}
#endif

#endif
