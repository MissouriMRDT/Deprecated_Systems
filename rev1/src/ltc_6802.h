#if !defined( LTC_6802_H )
#define LTC_6802_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************
*                                   INLCUDES                               *
***************************************************************************/

#include <stdint.h>

#include <error_states.h>
#include <msp_pin.h>

#include "cells.h"

/***************************************************************************
*                             LITERAL CONSTANTS                            *
***************************************************************************/

/***************************************************************************
*                                   MACROS                                 *
***************************************************************************/

/***************************************************************************
*                                    TYPES                                 *
***************************************************************************/

enum _e_ltc_mode
{
	LTC_STANDBY,
	LTC_MEASURE,
	LTC_MONITOR
};
typedef uint8_t e_ltc_mode;

/***************************************************************************
*                              MEMORY CONSTANTS                            *
***************************************************************************/

/***************************************************************************
*                                   CLASSES                                *
***************************************************************************/

typedef struct _c_ltc_6802
{
	c_msp_pin           m_clk_pin;  /* msp432 clock pin             */
	c_msp_pin           m_enable_pin;
	                                /* msp432 enable pin            */
	c_msp_pin           m_gpio_1;   /* msp432 gpio 1 pin            */
	c_msp_pin           m_gpio_2;   /* msp432 gpio 2 pin            */
	e_ltc_mode          m_ltc_mode; /* desired ltc mode             */
	c_msp_pin           m_miso_pin; /* msp432 MISO pin              */
	c_msp_pin           m_mosi_pin; /* msp432 MOSI pin              */
	c_msp_pin           m_watchdog; /* msp432 watchdog timer pin    */
} c_ltc_6802;

/***************************************************************************
*                                  VARIABLES                               *
***************************************************************************/

extern c_ltc_6802       ltc_6802;   /* main LTC to read data from   */

/***************************************************************************
*                                 PROCEDURES                               *
***************************************************************************/

void eusci_b1_isr
	(
		void
	);

e_error_states ltc_init_normal_op
	(
		void
	);

e_error_states ltc_powerup
	(
		void
	);

e_error_states ltc_request_voltage_read
	(
		c_bms_cell    * bms_cells,  /* bms cells to read data into  */
		const uint8_t   num_cells   /* num cells to read data for   */
	);

#ifdef __cplusplus
}
#endif

#endif
