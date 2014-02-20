/*
 * Keenan Johnson
 */

#ifndef MUXES_H_
#define MUXES_H_

// Mux Pins
//
// Mux 1
// PA6
// PA7
//
// Mux 1
// PE2
// PE3

void init_mux_pins()
{
	// Mux 1
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 );
}

//GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_5), (~0));

#endif /* MUXES_H_ */
