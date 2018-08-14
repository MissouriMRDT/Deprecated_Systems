/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

#include <stdint.h>

#include <adc14.h>

#include <msp_pin.h>

#include "status_monitoring.h"

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

static c_msp_pin        msp_estop_1 = { PIN_5, MSP_PORT_1, PIN_MODE_INPUT_GPIO };
                                    /* estop 1 pin gpio             */
static c_msp_pin        msp_estop_2 = { PIN_6, MSP_PORT_1, PIN_MODE_INPUT_GPIO };
                                    /* estop 2 pin gpio             */
static c_msp_pin        msp_pack_arr_voltage = { PIN_3, MSP_PORT_5, PIN_MODE_INPUT_TERNINARY };
                                    /* voltage from the bms lead pin*/
static c_msp_pin        msp_pack_current = { PIN_5, MSP_PORT_5, PIN_MODE_INPUT_TERNINARY };
                                    /* voltage out of bms pin       */
static c_msp_pin        msp_pack_out_voltage = { PIN_4, MSP_PORT_5, PIN_MODE_INPUT_TERNINARY };
                                    /* current ouf of bms pin       */
static c_msp_pin        msp_rover_power = { PIN_0, MSP_PORT_6, PIN_MODE_OUTPUT_GPIO };
                                    /* power toggle pin for power   */

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/


/*******************************************************************
*
*	PROCEDURE NAME:
*		status_is_estop_1_active
*
*	DESCRIPTION:
*		Returns true if the estop is engaged (should not be moving)
*
*******************************************************************/

inline bool status_is_estop_1_active
	(
		void
	)
{
	return( msp_432_get_pin_input_state( &msp_estop_1 ) );

}	/* status_is_estop_1_active() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		status_is_estop_2_active
*
*	DESCRIPTION:
*		Returns true if the estop is engaged (should not be moving)
*
*******************************************************************/

inline bool status_is_estop_2_active
	(
		void
	)
{
	return( msp_432_get_pin_input_state( &msp_estop_2 ) );

}	/* status_is_estop_2_active() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		status_powerup
*
*	DESCRIPTION:
*		Initializes all status monitoring pins
*
*******************************************************************/

e_error_states status_powerup
	(
		void
	)
{
	msp_432_update_pin_mode( &msp_estop_1 );
	msp_432_update_pin_mode( &msp_estop_2 );
	msp_432_update_pin_mode( &msp_pack_arr_voltage );
	msp_432_update_pin_mode( &msp_pack_current );
	msp_432_update_pin_mode( &msp_pack_out_voltage );

	return( ERROR_NO_ERROR );

}	/* status_powerup() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		status_read_pack_volt_current
*
*	DESCRIPTION:
*		Reads pack voltage and current via ADC
*
*******************************************************************/

e_error_states status_read_pack_volt_current
	(
		void
	)
{
	//Excluded due to not fully completed

}	/* status_read_pack_volt_current() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		status_turn_rover_off()
*
*	DESCRIPTION:
*		Turns main power off to the rover
*
*******************************************************************/

inline e_error_states status_turn_rover_off
	(
		void
	)
{
	return( msp_432_set_output_pin_low( &msp_rover_power ) );

}	/* status_turn_rover_off() */



/*******************************************************************
*
*	PROCEDURE NAME:
*		status_turn_rover_on()
*
*	DESCRIPTION:
*		Turns main power on to the rover
*
*******************************************************************/

inline e_error_states status_turn_rover_on
	(
		void
	)
{
	return( msp_432_set_output_pin_high( &msp_rover_power ) );

}	/* status_turn_rover_on() */

