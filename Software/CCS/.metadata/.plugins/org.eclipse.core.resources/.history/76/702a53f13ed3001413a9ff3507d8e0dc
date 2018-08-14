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

int deviceWrite(int rs485jack, char* buffer, int bytes_to_write)
{
	int bytes_wrote;

	//Give us access to the uart handles
	//These should defined at the global scope
	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;

	//Debug
	//System_printf("deviceWrite called\n");
	//System_flush();
	switch(rs485jack)
	{
	//We have to include case 0 to get TI's compiler to build a jump table
	//If we leave this out, mux performance goes from O(1) to O(n) (That's bad)
	case 0:
	case 1:
		//Configure the mux pins
		//See the mux datasheet for more info
		digitalWrite(U3_MUX_S0, HIGH);
		digitalWrite(U3_MUX_S1, HIGH);

		//Write the buffer to the device
		bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
		break;
	case 2:
		digitalWrite(U3_MUX_S0, LOW);
		digitalWrite(U3_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
		break;
	case 3:
		digitalWrite(U3_MUX_S0, HIGH);
		digitalWrite(U3_MUX_S1, LOW);
		bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
		break;
	case 4:
		digitalWrite(U6_MUX_S0, LOW);
		digitalWrite(U6_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
		break;
	case 5:
		digitalWrite(U6_MUX_S0, HIGH);
		digitalWrite(U6_MUX_S1, LOW);
		bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
		break;
	case 6:
		digitalWrite(U7_MUX_S0, HIGH);
		digitalWrite(U7_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
		break;
	case 7:
		digitalWrite(U7_MUX_S0, LOW);
		digitalWrite(U7_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
		break;
	case 8:
		digitalWrite(U7_MUX_S0, HIGH);
		digitalWrite(U7_MUX_S1, LOW);
		bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
		break;
	case 9:
		digitalWrite(U5_MUX_S0, LOW);
		digitalWrite(U5_MUX_S1, LOW);
		bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
		break;
	case 10:
		digitalWrite(U5_MUX_S0, LOW);
		digitalWrite(U5_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
		break;
	case 11:
		digitalWrite(U5_MUX_S0, HIGH);
		digitalWrite(U5_MUX_S1, LOW);
		bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
		break;
	case 12:
		digitalWrite(U5_MUX_S0, LOW);
		digitalWrite(U5_MUX_S1, LOW);
		bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
		break;
	case 13:
		digitalWrite(U5_MUX_S0, HIGH);
		digitalWrite(U5_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
		break;
	case 14:
		digitalWrite(U4_MUX_S0, LOW);
		digitalWrite(U4_MUX_S1, LOW);
		bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
		break;
	case 15:
		digitalWrite(U4_MUX_S0, LOW);
		digitalWrite(U4_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
		break;
	case 16:
		digitalWrite(U4_MUX_S0, HIGH);
		digitalWrite(U4_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
		break;
	case 17:
		digitalWrite(U4_MUX_S0, HIGH);
		digitalWrite(U4_MUX_S1, LOW);
		bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
		break;
	case POWER_BOARD:
		digitalWrite(U6_MUX_S0, HIGH);
		digitalWrite(U6_MUX_S1, HIGH);
		bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
		break;
	case ONBOARD_ROVECOMM:
		bytes_wrote = UART_write(uart2, buffer, bytes_to_write);
		break;
	default:
		//Tried to write to invalid device
		System_printf("DeviceWrite passed invalid device %d\n", rs485jack);
		System_flush();
		return -1;
		break;
	//etc.
	}

	//Make sure the message is fully written before leaving the function
	ms_delay(1);
	return bytes_wrote;
}

int deviceRead(int rs485jack, char* buffer, int bytes_to_read, int timeout)
{
	int bytes_read;

	//Give us access to the uart handles
	//These should defined at the global scope
	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;


	//We have to include case 0 to get TI's compiler to build a jump table
	//If we leave this out, mux performance goes from O(1) to O(n) (That's bad)
	switch(rs485jack)
	{
	case 0:
	case 1:
		//Configure the mux pins
		//See the mux datasheet for more info
		digitalWrite(U3_MUX_S0, HIGH);
		digitalWrite(U3_MUX_S1, HIGH);

		//Write the buffer to the device
		bytes_read = Uart_read(uart3, buffer, bytes_to_read);
		break;
	case 2:
		digitalWrite(U3_MUX_S0, LOW);
		digitalWrite(U3_MUX_S1, HIGH);
		bytes_read = Uart_read(uart3, buffer, bytes_to_read);
		break;
	case 3:
		digitalWrite(U3_MUX_S0, HIGH);
		digitalWrite(U3_MUX_S1, LOW);
		bytes_read = Uart_read(uart3, buffer, bytes_to_read);
		break;
	case 4:
		digitalWrite(U6_MUX_S0, LOW);
		digitalWrite(U6_MUX_S1, HIGH);
		bytes_read = Uart_read(uart6, buffer, bytes_to_read);
		break;
	case 5:
		digitalWrite(U6_MUX_S0, HIGH);
		digitalWrite(U6_MUX_S1, LOW);
		bytes_read = Uart_read(uart6, buffer, bytes_to_read);
		break;
	case 6:
		digitalWrite(U7_MUX_S0, HIGH);
		digitalWrite(U7_MUX_S1, HIGH);
		bytes_read = Uart_read(uart7, buffer, bytes_to_read);
		break;
	case 7:
		digitalWrite(U7_MUX_S0, LOW);
		digitalWrite(U7_MUX_S1, HIGH);
		bytes_read = Uart_read(uart7, buffer, bytes_to_read);
		break;
	case 8:
		digitalWrite(U7_MUX_S0, HIGH);
		digitalWrite(U7_MUX_S1, LOW);
		bytes_read = Uart_read(uart7, buffer, bytes_to_read);
		break;
	case 9:
		digitalWrite(U5_MUX_S0, LOW);
		digitalWrite(U5_MUX_S1, LOW);
		bytes_read = Uart_read(uart5, buffer, bytes_to_read);
		break;
	case 10:
		digitalWrite(U5_MUX_S0, LOW);
		digitalWrite(U5_MUX_S1, HIGH);
		bytes_read = Uart_read(uart5, buffer, bytes_to_read);
		break;
	case 11:
		digitalWrite(U5_MUX_S0, HIGH);
		digitalWrite(U5_MUX_S1, LOW);
		bytes_read = Uart_read(uart5, buffer, bytes_to_read);
		break;
	case 12:
		digitalWrite(U5_MUX_S0, LOW);
		digitalWrite(U5_MUX_S1, LOW);
		bytes_read = Uart_read(uart5, buffer, bytes_to_read);
		break;
	case 13:
		digitalWrite(U5_MUX_S0, HIGH);
		digitalWrite(U5_MUX_S1, HIGH);
		bytes_read = Uart_read(uart5, buffer, bytes_to_read);
		break;
	case 14:
		digitalWrite(U4_MUX_S0, LOW);
		digitalWrite(U4_MUX_S1, LOW);
		bytes_read = Uart_read(uart4, buffer, bytes_to_read);
		break;
	case 15:
		digitalWrite(U4_MUX_S0, LOW);
		digitalWrite(U4_MUX_S1, HIGH);
		bytes_read = Uart_read(uart4, buffer, bytes_to_read);
		break;
	case 16:
		digitalWrite(U4_MUX_S0, HIGH);
		digitalWrite(U4_MUX_S1, HIGH);
		bytes_read = Uart_read(uart4, buffer, bytes_to_read);
		break;
	case 17:
		digitalWrite(U4_MUX_S0, HIGH);
		digitalWrite(U4_MUX_S1, LOW);
		bytes_read = Uart_read(uart4, buffer, bytes_to_read);
		break;
	case POWER_BOARD:
		digitalWrite(U6_MUX_S0, HIGH);
		digitalWrite(U6_MUX_S1, HIGH);
		bytes_read = Uart_read(uart6, buffer, bytes_to_read);
		break;
	case ONBOARD_ROVECOMM:
		bytes_read = Uart_read(uart2, buffer, bytes_to_read);
		break;
	default:
		//Tried to write to invalid device
		System_printf("DeviceWrite passed invalid device %d\n", rs485jack);
		System_flush();
		return -1;
		break;
	//etc.
	}
	return bytes_read;
}

void initUarts()
{

}

int generateMotorCommand(int speed, char* buffer){

	// variable to do temp work on the count of needed buffer size

	int workerCount = 0;

	// variable to do temp work on the integer for ASCII conversion

	int workerInt = speed;

	System_printf("Inside generateMotorCommand speed holds %d \n", workerInt);
	System_flush();

	// variable to work on the character for ASCII version

	char workerChar;

	while(workerInt != 0){

		// shift right one decimal digit

		workerInt = workerInt/10;

		// count that digit

		workerCount = workerCount + 1;

	}// endwhile:	(workerInt != 0)

	System_printf("Inside generateMotorCommand workerCount holds %d \n", workerCount);
	System_flush();

	// reload the speed value

	workerInt = speed;

	// initialize the buffer for G command

	buffer[0] = '!';
	buffer[1] = 'G';
	buffer[2] = ' ';
	buffer[3] = '1';
	buffer[4] = ' ';

	// store return value (this is the count of the ASCII chars in the buffer)

	workerCount = workerCount + 5;

	// terminate the string with control character
	// motor controller interperts '_' as the \r

	buffer[workerCount] = '_';

	//just for good measure (systemPrintf debugging, etc)

	buffer[workerCount + 1] = '\0';

	// loop until we run out of digits

	while(workerCount > 5){

		workerCount = workerCount - 1;

		//extracts right digit of integer speed and stores as binary

		workerChar = (workerInt%10);

		//add ASCII offset and place at the back of the buffer

		buffer[workerCount] = workerChar + '0'; //decrement workercount?

		//truncates the last digit of integer speed (shift one digit)

		workerInt = workerInt/10;

		//move one character towards the front of the buffer


	}//endwhile:	(workerCount > 0)

	// the message '!G 1 <ASCIISPEED>_' is placed by side effect in the passed buffer

	// return the size of the message

	return workerCount + 5;

}//end fnctn generateMotorCommand

void initMuxGPIO()
{
	//Probably just a bunch of pinModes.
}
