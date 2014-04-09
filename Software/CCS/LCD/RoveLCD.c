/*
 * lcd44780_LP.c
 *		Basic HD44780 driver for Stellaris Launchpad
 *      Version 1.00
 *      Author: NYH
 *      Reference: Robot Head to Toe Vol. 11 - pg 35-36
 *      Note: One full port must be used for this LCD. In this driver PORTB is used.
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "RoveLCD.h"
#include <xdc/runtime/System.h>
#include <xdc/std.h>

void initLCD() {

	// Enable Peripheral Clocks
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	// Enable pin PD3 for GPIOOutput
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);

	// Enable pin PF0 for GPIOOutput
	//First open the lock and select the bits we want to modify in the GPIO commit register.
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

	//Now modify the configuration of the pins that we unlocked.
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);

	// Enable pin PF3 for GPIOOutput
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

	// Enable pin PF4 for GPIOOutput
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);

	// Enable pin PF1 for GPIOOutput
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

	// Enable pin PF2 for GPIOOutput
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

	// Please refer to the HD44780 datasheet for how these initializations work!
	SysCtlDelay((500e-3)*CLKSPEED/3);

	GPIOPinWrite(LCDPORTD, RS,  0x00 );

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7,  0x06 );
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3); GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((50e-3)*CLKSPEED/3);

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7,  0x06 );
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3);GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((50e-3)*CLKSPEED/3);

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7,  0x06 );
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3); GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((10e-3)*CLKSPEED/3);

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7,  0x04 );
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3); GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((10e-3)*CLKSPEED/3);

	LCDCommand(0x01);	// Clear the screen.
	LCDCommand(0x06);	// Cursor moves right.
	LCDCommand(0x0f);	// Cursor blinking, turn on LCD.


}

void LCDCommand(unsigned char command) {

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7, (command & 0xf0) >> 3);
	GPIOPinWrite(LCDPORTD, RS, 0x00);
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3); GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((100e-6)*CLKSPEED/3);

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7, (command & 0x0f) << 1 );
	GPIOPinWrite(LCDPORTD, RS, 0x00);
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3); GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((5e-3)*CLKSPEED/3);

}

void LCDWrite(unsigned char inputData) {

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7, (inputData & 0xf0) >> 3 );
	GPIOPinWrite(LCDPORTD, RS, 0x08);
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3); GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((100e-6)*CLKSPEED/3);

	GPIOPinWrite(LCDPORTF, D4 | D5 | D6 | D7, (inputData & 0x0f) << 1 );
	GPIOPinWrite(LCDPORTD, RS, 0x08);
	GPIOPinWrite(LCDPORTF, E, 0x01);SysCtlDelay((20e-6)*CLKSPEED/3); GPIOPinWrite(LCDPORTF, E, 0x00);

	SysCtlDelay((5e-3)*CLKSPEED/3);

}

void LCDWriteText(char* inputText)
{
	LCDCommand(0x01);
	unsigned char address = 0x80;
	LCDCommand(address);
	if(strlen(inputText)>16)
    {
		int i;
    	for(i=0;i<16;i++)
    	{
    		LCDWrite(*inputText++);
    	}
    	LCDCommand(0xC0);
    	while(*inputText)
    		LCDWrite(*inputText++);
    }
	else
	{
		while(*inputText)
		    LCDWrite(*inputText++);
	}
}

