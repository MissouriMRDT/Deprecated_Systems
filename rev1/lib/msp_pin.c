/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

#include <stdint.h>

#include <gpio.h>
#include <msp432.h>

#include "error_states.h"
#include "msp_pin.h"

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

static volatile uint8_t
	            * const PnDIR[ 10 ] = { &P1DIR, &P2DIR, &P3DIR, &P4DIR, &P5DIR, &P6DIR, &P7DIR, &P8DIR, &P9DIR, &P10DIR };
	                                /* port input / output settings */
static volatile uint8_t
	            * const PnIN[ 10 ] = { &P1IN, &P2IN, &P3IN, &P4IN, &P5IN, &P6IN, &P7IN, &P8IN, &P9IN, &P10IN };
	                                /* port input state             */
static volatile uint8_t
	            * const PnOUT[ 10 ] = { &P1OUT, &P2OUT, &P3OUT, &P4OUT, &P5OUT, &P6OUT, &P7OUT, &P8OUT, &P9OUT, &P10OUT };
	                                /* port output state            */
static volatile uint8_t
	            * const PnREN[ 10 ] = { &P1REN, &P2REN, &P3REN, &P4REN, &P5REN, &P6REN, &P7REN, &P8REN, &P9REN, &P10REN };
	                                /*  port register enable setting*/
static volatile uint8_t
	            * const PnSEL0[ 10 ] = { &P1SEL0, &P2SEL0, &P3SEL0, &P4SEL0, &P5SEL0, &P6SEL0, &P7SEL0, &P8SEL0, &P9SEL0, &P10SEL0 };
	                                /*  port select 0 setting       */
static volatile uint8_t
	            * const PnSEL1[ 10 ] = { &P1SEL1, &P2SEL1, &P3SEL1, &P4SEL1, &P5SEL1, &P6SEL1, &P7SEL1, &P8SEL1, &P9SEL1, &P10SEL1 };
	                                /*  port select 1 setting       */

/***************************************************************************
*                                   CLASSES                                *
***************************************************************************/

/***************************************************************************
*                                  VARIABLES                               *
***************************************************************************/

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/


/*******************************************************************
*
*	PROCEDURE NAME:
*		msp_432_get_pin_input_state
*
*	DESCRIPTION:
*		Gets an input state from a selected pin
*
*******************************************************************/

inline uint8_t msp_432_get_pin_input_state
	(
		const c_msp_pin
				* const msp_pin     /* pin to update                */
	)
{
#if defined( VERBOSE_CHECKING )
	if( msp_pin == NULL )
	{
		return( ERROR_NULL_PARAMETER );
	}
#endif

	if( MSP_NUM_PORTS > msp_pin->m_port )
	{
		return ( *PnIN[ msp_pin->m_port ] & msp_pin->m_pin != 0 );
	}

	return( 0 );

}	/* get_pin_input_state() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		msp_432_set_output_pin_high
*
*	DESCRIPTION:
*		Sets the output of a pin high
*
*******************************************************************/

e_error_states msp_432_set_output_pin_high
	(
		const c_msp_pin
		        * const msp_pin     /* pin to update                */
	)
{
#if defined( VERBOSE_CHECKING )
	if( msp_pin == NULL )
	{
		return( ERROR_NULL_PARAMETER );
	}
#endif

	if( MSP_NUM_PORTS > msp_pin->m_port )
	{
#if defined( TRACE_DEBUGGING )
		if( getbit( *PnDIR[ msp_pin.m_port ], msp_pin.m_pin ) != PIN_MODE_OUTPUT_GPIO )
		{
			return( ERROR_INVALID_CONFIGURATION );
		}
#endif

		*PnOUT[ msp_pin->m_port ] |= msp_pin->m_pin;

		return( ERROR_NO_ERROR );
	}

	return( ERROR_INVALID_PARAMETER );

}	/* msp_432_set_output_pin_high() */


/*******************************************************************
*
*	PROCEDURE NAME:
*		msp_432_set_output_pin_low
*
*	DESCRIPTION:
*		Gets an input state from a selected pin
*
*******************************************************************/

e_error_states msp_432_set_output_pin_low
	(
		const c_msp_pin
		        * const msp_pin     /* pin to update                */
	)
{
#if defined( VERBOSE_CHECKING )
	if( msp_pin == NULL )
	{
		return( ERROR_NULL_PARAMETER );
	}
#endif

	if( MSP_NUM_PORTS > msp_pin->m_port )
	{
#if defined( TRACE_DEBUGGING )
		if( getbit( *PnDIR[ msp_pin.m_port ], msp_pin.m_pin ) != PIN_MODE_OUTPUT_GPIOT )
		{
			return( ERROR_INVALID_CONFIGURATION );
		}
#endif

		*PnOUT[ msp_pin->m_port ] &= ~msp_pin->m_pin;

		return( ERROR_NO_ERROR );
	}

	return( ERROR_INVALID_PARAMETER );

}	/* msp_432_set_output_pin_low() */



/*******************************************************************
*
*	PROCEDURE NAME:
*		msp_432_update_pin_mode
*
*	DESCRIPTION:
*		Updates a pin mode according to it's specified pin mode
*
*******************************************************************/

e_error_states msp_432_update_pin_mode
	(
		const c_msp_pin
		        * const msp_pin     /* pin to update                */
	)
{
#if defined( VERBOSE_CHECKING )
	if( msp_pin == NULL )
	{
		return( ERROR_NULL_PARAMETER );
	}
#endif

	if( MSP_NUM_PORTS > msp_pin->m_port )
	{

		if( msp_pin->m_mode & 0x01 )
		{
			*PnSEL0[ msp_pin->m_port ] |= msp_pin->m_pin;
		}
		else
		{
			*PnSEL0[ msp_pin->m_port ] &= ~msp_pin->m_pin;
		}

		if( msp_pin->m_mode & 0x02 )
		{
			*PnSEL1[ msp_pin->m_port ] |= msp_pin->m_pin;
		}
		else
		{
			*PnSEL1[ msp_pin->m_port ] &= ~msp_pin->m_pin;
		}

		if( msp_pin->m_mode & 0x04 )
		{
			*PnREN[ msp_pin->m_port ] |= msp_pin->m_pin;
		}
		else
		{
			*PnREN[ msp_pin->m_port ] &= ~msp_pin->m_pin;
		}

		if( msp_pin->m_mode & 0x08 )
		{
			*PnOUT[ msp_pin->m_port ] |= msp_pin->m_pin;
		}
		else
		{
			*PnOUT[ msp_pin->m_port ] &= ~msp_pin->m_pin;
		}

		if( msp_pin->m_mode & 0x10 )
		{
			*PnDIR[ msp_pin->m_port ] |= msp_pin->m_pin;
		}
		else
		{
			*PnDIR[ msp_pin->m_port ] &= ~msp_pin->m_pin;
		}

		return( ERROR_NO_ERROR );
	}

	return( ERROR_INVALID_PARAMETER );

}	/* update_pin_mode() */
