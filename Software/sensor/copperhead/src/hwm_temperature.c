/*********************************************************************
*
*   MODULE NAME:
*       hwm_temperature.c
*
*   DESCRIPTION:
*       This file converts ADC values into temperature values to be
*       transmitted as temperature PGN over NMEA2K.
*
* Copyright 2015 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/

#include "hwm_temperature.h"

/*--------------------------------------------------------------------
                          LITERAL CONSTANTS
--------------------------------------------------------------------*/

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

static uint32 temperature_ext;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_get_temperature - Get Actual Temperature (Kelvins)
*
*   DESCRIPTION:
*       Gets the Temperature.
*       Returns Degrees Kelvin with range of 0 to 655.32 and a
*       resolution of 1x10E-2.
*
*********************************************************************/
uint16_t HWM_get_temperature
    (
    void
    )
{

uint8 i = 0;
uint8 j = 0;
float adc_value = 0;
float value = 0;

for( i = 0; i < ( sizeof( adc_value_buff ) / sizeof( adc_value_buff[0] ) ); i++ )
    {
    if( adc_value_buff[i] != 0 )
        {
            adc_value += adc_value_buff[i];
            j++;
        }
    }

adc_value = ( adc_value /  j );

value = R1 / ( ( 1023 / adc_value  ) - 1 );
value = 1 / ( ( 1 / (float) T0 ) + ( 1 / (float) B ) * logf( value / (float) R0 ) );

temperature_ext = ( (uint32) ( value * 1000 ) );

return ( (uint16_t) ( value * 100 ) );
}   /* HWM_get_temperature() */


/*********************************************************************
*
*   PROCEDURE NAME:
*       HWM_get_temperature_ext - Get Actual Temperature (Kelvins)
*
*   DESCRIPTION:
*       Gets the Temperature.
*       Returns Degrees Kelvin with range of 0 to 16,77.212 and a
*       resolution of 1x10E-3.
*
*********************************************************************/
uint32_t HWM_get_temperature_ext
    (
    void
    )
{
    return temperature_ext;
}   /* HWM_get_temperature_ext() */
