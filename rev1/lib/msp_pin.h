#if !defined( MSP_PIN_H )
#define MSP_PIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

#include <stdint.h>

#include "error_states.h"
#include "macros.h"

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

enum _e_pin_mode
{

	/*-----------------------------------
	Bit 0: SEL0
	Bit 1: SEL1
	Bit 2: REN
	Bit 3: OUT
	Bit 4: DIR
	Bit 5: N/A
	Bit 6: N/A
	Bit 7: N/A
	-----------------------------------*/

	PIN_MODE_INPUT_PRIMARY          = 0x01,
	PIN_MODE_INPUT_SECONDARY        = 0x02,
	PIN_MODE_INPUT_TERNINARY        = 0x03,
	PIN_MODE_INPUT_PULL_DOWN        = 0x04,
	PIN_MODE_INPUT_PULL_UP          = 0x0C,
	PIN_MODE_INPUT_GPIO             = 0x20,
	PIN_MODE_OUTPUT_PRIMARY         = 0x91,
	PIN_MODE_OUTPUT_SECONDARY       = 0x92,
	PIN_MODE_OUTPUT_TERINARY        = 0x93,
	PIN_MODE_OUTPUT_GPIO            = 0xF0,
	PIN_MODE_DONT_CARE              = PIN_MODE_INPUT_GPIO,
};
typedef uint8_t e_pin_mode;

enum _e_ports
{
	MSP_PORT_1,
	MSP_PORT_2,
	MSP_PORT_3,
	MSP_PORT_4,
	MSP_PORT_5,
	MSP_PORT_6,
	MSP_PORT_7,
	MSP_PORT_8,
	MSP_PORT_9,
	MSP_PORT_10,
	MSP_NUM_PORTS,
	MSP_PORT_NC,
	MSP_PORT_DISCONNECT = MSP_PORT_NC,
};
typedef uint8_t e_ports;

enum _e_pins
{
	PIN_0               = bitmsk( 0 ),
	PIN_1               = bitmsk( 1 ),
	PIN_2               = bitmsk( 2 ),
	PIN_3               = bitmsk( 3 ),
	PIN_4               = bitmsk( 4 ),
	PIN_5               = bitmsk( 5 ),
	PIN_6               = bitmsk( 6 ),
	PIN_7               = bitmsk( 7 ),
	PIN_8               = 0,
};
typedef uint8_t e_pins;

/***************************************************************************
*                                   CLASSES                                *
***************************************************************************/

/*******************************************************************
*
*	CLASS:
*		 c_msp_pin
*
*	DESCRIPTION:
*		Contains information needed to control a single pin on the
*			msp432
*
*******************************************************************/

typedef struct _c_msp_pin
{
	const e_pins        m_pin;      /* pin desired                   */
	const e_ports       m_port;     /* port desired                  */
	e_pin_mode          m_mode;     /* input or output               */
} c_msp_pin;

/***************************************************************************
*                                  VARIABLES                               *
***************************************************************************/

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/

extern inline uint8_t msp_432_get_pin_input_state
	(
		const c_msp_pin
				* const msp_pin     /* pin to update                */
	);

e_error_states msp_432_set_output_pin_high
	(
		const c_msp_pin
		        * const msp_pin     /* pin to update                */
	);

e_error_states msp_432_set_output_pin_low
	(
		const c_msp_pin
		        * const msp_pin     /* pin to update                */
	);

e_error_states msp_432_update_pin_mode
	(
		const c_msp_pin
		        * const msp_pin     /* pin to update                */
	);

#ifdef __cplusplus
}
#endif

#endif
