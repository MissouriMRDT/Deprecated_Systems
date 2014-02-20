/*
 * Keenan Johnson
 *
 * Library for controller
 * Motherboard Muxes
 */

#ifndef MUXES_H_
#define MUXES_H_

void init_mux_pins()
{
	// Mux 1
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 );

	// Mux 2
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 );

	// Mux 3
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 );

	// Mux 4
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 );
}

//GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_5), (~0));

#endif /* MUXES_H_ */
