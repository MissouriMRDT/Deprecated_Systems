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
	// Mux # - S0, S1

	// Mux 1 - A5, A6
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 );

	// Mux 3 - B2, B3
	// Mux 4 - B4, B5
	// Mux 5 - B6, B7
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3 |
										   GPIO_PIN_4 | GPIO_PIN_5 |
										   GPIO_PIN_6 | GPIO_PIN_7);

	// Mux 7 - A5, A6
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 );

	// Mux 2 - E2, E3
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3 );

}

// Function to change mux1 to various
// RS-485 transceivers below
//
// 1, 8, 9
//
void mux_1( int rs_485_transceiver)
{
	switch(rs_485_transceiver){
	    case 1  :
	        GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_5 | GPIO_PIN_6), (0));
	        break;
	    case 8  :
	        GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_5), (~0));
	        GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_6), (0));
	        break;
	    case 9 :
	    	GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_5), (0));
		    GPIOPinWrite(GPIO_PORTA_BASE, (GPIO_PIN_6), (~0));
	    	break;
	    default :
	    	// Not a valid input
	    	System_printf("Not a vaid MUX_1 Location");
	    	System_flush();
	    	break;
	}
}

// Function to change mux2 to various
// RS-485 transceivers below
//
// 2, 7, 10
//
void mux_2( int rs_485_transceiver)
{
	switch(rs_485_transceiver){
	    case 2  :
	        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2 | GPIO_PIN_3), (0));
	        break;
	    case 7  :
	        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2), (~0));
	        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_3), (0));
	        break;
	    case 10 :
	        GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_2), (0));
		    GPIOPinWrite(GPIO_PORTE_BASE, (GPIO_PIN_3), (~0));
	        break;
	    default :
		    // Not a valid input
		    System_printf("Not a vaid MUX_1 Location");
		    System_flush();
		    break;
	}
}

#endif /* MUXES_H_ */
