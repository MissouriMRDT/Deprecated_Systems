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

#define start_byte1 0x06
#define start_byte2 0x85

enum peripheral_devices{motor_controller1, motor_controller2, robotic_arm};


struct example_struct
{
    int x;
    int y;
    int z;
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
    uint8_t* rx_buffer = (uint8_t*) malloc(size);
    uint8_t CS = size;



    UART_write(uart, start_byte1, 1);
    UART_write(uart, start_byte2, 1);
    UART_write(uart, size, 1);

    int i;
    for(i = 0; i<size; i++)
    {
        CS^=*(address+i);
        UART_write(uart, *(address+i), 1);
        //serial.write(*(address+i));
    }
    UART_write(uart, CS, 1);
    //serial.write(CS);

};

extern Void struct_xfer_test()
{
	UART_Handle uart1 = init_uart( 1 );

	struct example_struct test_struct;

	test_struct.x = 15;
	test_struct.y = 20;
	test_struct.z = 30;

	while(1)
	{
		System_printf("Writing struct\n");
		System_flush();
		send_struct(uart1, &test_struct, motor_controller2);
		SysCtlDelay( SysCtlClockGet() * 3 );
	}

}

#endif /* STRUCT_TEST_H_ */
