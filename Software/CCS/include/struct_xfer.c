/*
 * struct_xfer.c
 *
 *  Created on: May 6, 2014
 *      Author: Zeus
 */

#include "struct_xfer.h"

#include <xdc/runtime/System.h>
#include "../structs.h"

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

