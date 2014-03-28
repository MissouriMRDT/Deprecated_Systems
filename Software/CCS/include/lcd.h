/*
 * lcd.h
 *
 *  Keenan Johnson
 */

#ifndef LCD_H_
#define LCD_H_

void init_LCD()
{
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3 );

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 |
								GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);

}

#endif /* LCD_H_ */
