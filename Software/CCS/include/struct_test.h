/*
 * struct_test.h
 *
 *  Created on: Mar 24, 2014
 *      Author: Zeus
 */

#ifndef STRUCT_TEST_H_
#define STRUCT_TEST_H_

#include <stdlib.h>
#include <stdio.h>

enum peripheral_devices{motor_controller1, motor_controller2, robotic_arm};

uint8_t start_byte1=0x06;
uint8_t start_byte2=0x85;


struct example_struct
{
	uint16_t x;
};

void send_struct(UART_Handle uart, void* my_struct, enum peripheral_devices device)
{
    uint8_t size;

    switch(device)
    {
        case motor_controller1:
        case motor_controller2:
            size = sizeof(*((struct example_struct*)my_struct));
            break;
        case robotic_arm:
            size = sizeof(*((struct example_struct*)my_struct));
            break;
    }

    uint8_t* address = (uint8_t*) my_struct;
    uint8_t* rx_buffer = (uint8_t*) malloc(size);  //think we can remove this, only used when receiving structs
    uint8_t CS = size;

    UART_write(uart, &start_byte1, 1);
    System_printf("Start1: %x\n", start_byte1);
    System_flush();

    UART_write(uart, &start_byte2, 1);
    System_printf("Start2: %x\n", start_byte2);
	System_flush();

    UART_write(uart, &size, 1);
    System_printf("Size: %x\n", size);
	System_flush();

    int i;
    for(i = 0; i<size; i++)
    {
        CS^=*(address+i);
        UART_write(uart, &(*(address+i)), 1);
        System_printf("DATA: %x\n", *(address+i));
		System_flush();
        //serial.write(*(address+i));
    }

    System_printf("CS: %x\n", CS);
    System_flush();
    UART_write(uart, &CS, 1);

    //serial.write(CS);

};

extern Void struct_xfer_test()
{
	UART_Handle uart = init_uart( 5 );

	struct example_struct test_struct;

	test_struct.x = 300;

	mux_5( 13 );

	while(1)
	{
		System_printf("Writing struct\n");
		System_flush();

		// Send struct
		send_struct(uart, &test_struct, motor_controller2);

		// Delay 1 seconds
		SysCtlDelay( SysCtlClockGet());
	}
}

#endif /* STRUCT_TEST_H_ */
