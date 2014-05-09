/*
 * struct_xfer.c
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 */

#include "struct_xfer.h"

#include <xdc/runtime/System.h>
#include "../include/structs.h"

void send_struct(UART_Handle uart, void* my_struct, enum peripheral_devices device)
{
    uint8_t size;
    uint8_t start_byte1 = 0x06;
    uint8_t start_byte2 = 0x85;

    switch(device)
    {
        case motor_controller:
            size = sizeof(*((struct motor_struct*)my_struct));
            break;
    }

    uint8_t* address = (uint8_t*) my_struct;
    uint8_t CS = size;

    UART_write(uart, (char*) &start_byte1, 1);

    UART_write(uart, (char*) &start_byte2, 1);

    UART_write(uart, (char*) &size, 1);

    int i;
    for(i = 0; i<size; i++)
    {
        CS^=*(address+i);
        UART_write(uart, (char*) &(*(address+i)), 1);

    }

    UART_write(uart, (char*) &CS, 1);
};

// Reads struct straight up from uart buffer
bool recv_struct( UART_Handle uart, void* my_struct, enum peripheral_devices device )
{
	// Variables
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t size;
	uint8_t calc_CS;	   //calculated Chacksum
	int i;

	// Get size of struct
	switch(device)
	{
		case bms:
			size = sizeof(*((struct bms_data_struct*)my_struct));
			break;
		case recv_test:
			size = sizeof(*((struct receive_test*)my_struct));
			break;
	}

	char rx_buffer[60];
	char temp;

	// Check for Start byte 1
	do {
		UART_read(uart, &temp, 1);
	} while ( temp != start_byte1 );

	// Check for Start byte 2
	UART_read(uart, &temp, 1);
	if ( temp != start_byte2 )
	{
		// Kick out of function
		return false;
	}

	// Check if size matches
	UART_read(uart, &temp, 1);
	if ( temp != size )
	{
		// Size doesn't match
		return false;
	}

	// Read in data bytes
	for ( i = 0 ; i <= size ; i++ )
	{
		UART_read(uart, &temp, 1);
		rx_buffer[i] = temp;
	}

	// calculate checksum
	calc_CS = size;

	for ( i=0 ; i<size ; i++ )
	{
		calc_CS ^= rx_buffer[i];
	}

	// Does checksum match?
	if ( calc_CS != rx_buffer[size] )
	{
		// Checksum does not match
		return false;
	}

	// Copy buffer into struct
	memcpy ( my_struct, rx_buffer, size );

	// Success
	return true;

}
