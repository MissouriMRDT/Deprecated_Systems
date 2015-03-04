/*
 * roveHardwareAbstraction.c
 *
 *  Created on: Mar 3, 2015
 *      Author: Owen
 */


#include "../roveWareHeaders/roveHardwareAbstraction.h"

void pinMode(int pin, int mode)
{
	//No idea how to start this one
}

void digitalWrite(int pin, int val)
{
	//Alarmingly enough, a switch case is really the only way to deal with this
	//Everything is base on a bunch of TI defined constants that can't be indexed into
	//Or iterated through

	if(val == LOW)
	{
		switch(pin)
		{
		case U3_MUX_S0 :
			GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, (0));
			break;
		case U3_MUX_S1 :
			GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1, (0));
			break;
		case U4_MUX_S0 :
			GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, (0));
			break;
		case U4_MUX_S1 :
			GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_7, (0));
			break;
		case U5_MUX_S0 :
			GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, (0));
			break;
		case U5_MUX_S1 :
			GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, (0));
			break;
		case U6_MUX_S0 :
			GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_2, (0));
			break;
		case U6_MUX_S1 :
			GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_3, (0));
			break;
		case U7_MUX_S0 :
			GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, (0));
			break;
		case U7_MUX_S1 :
			GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, (0));
			break;
		}//endswitch
	} else if (val == HIGH)
	{
		switch(pin)
		{
		case U3_MUX_S0 :
			GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, (~0));
			break;
		case U3_MUX_S1 :
			GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1, (~0));
			break;
		case U4_MUX_S0 :
			GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, (~0));
			break;
		case U4_MUX_S1 :
			GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_7, (~0));
			break;
		case U5_MUX_S0 :
			GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, (~0));
			break;
		case U5_MUX_S1 :
			GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, (~0));
			break;
		case U6_MUX_S0 :
			GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_2, (~0));
			break;
		case U6_MUX_S1 :
			GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_3, (~0));
			break;
		case U7_MUX_S0 :
			GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, (~0));
			break;
		case U7_MUX_S1 :
			GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, (~0));
			break;
		}//endswitch
	}
	return;

}

int deviceWrite(int rs485jack, char* buffer, int buf_len)
{
	//Debug
	System_printf("deviceWrite called\n");
	System_flush();
	/*
	switch(rs485jack)
	{
	case 1:
		GPIO_write(U1_MUX_S1, LOW)
		digitalWrite(U1_MUX_S0, LOW)
		UartWrite
		//Write buffer to UART
		break;
	//etc.
	}
	*/

}

int deviceRead(int rs485jack, char* buffer, int buf_len, int timeout)
{
	/*
	switch(rs485jack)
	{
	case 1:
		digitalWrite(U1_MUX_S1, LOW)
		digitalWrite(U1_MUX_S0, LOW)
		//Read UART into buffer
		break;
	//etc.
	}
	*/
}

void initUarts()
{

}

void initMuxGPIO()
{
	//Probably just a bunch of pinModes.
}
