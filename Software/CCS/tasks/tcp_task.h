/*
 * tcp_task.h
 *
 *  Created on: Apr 7, 2014
 *      Author: Zeus
 */

#ifndef TCP_TASK_H_
#define TCP_TASK_H_

#include <string.h>
#include <stdbool.h>

#define mux_delay 500

enum peripheral_devices{motor_controller1, motor_controller2, robotic_arm};

uint8_t start_byte1=0x06;
uint8_t start_byte2=0x85;

struct motor_struct
{
	uint8_t x;
};

void send_struct(UART_Handle uart, void* my_struct, enum peripheral_devices device)
{
    uint8_t size;

    switch(device)
    {
        case motor_controller1:
        case motor_controller2:
            size = sizeof(*((struct motor_struct*)my_struct));
            break;
        case robotic_arm:
            size = sizeof(*((struct motor_struct*)my_struct));
            break;
    }

    uint8_t* address = (uint8_t*) my_struct;
    uint8_t* rx_buffer = (uint8_t*) malloc(size);  //think we can remove this, only used when receiving structs
    uint8_t CS = size;

    UART_write(uart, &start_byte1, 1);

    UART_write(uart, &start_byte2, 1);

    UART_write(uart, &size, 1);

    int i;
    for(i = 0; i<size; i++)
    {
        CS^=*(address+i);
        UART_write(uart, &(*(address+i)), 1);
    }
    UART_write(uart, &CS, 1);
};

extern Void tcp_connection(UArg arg0, UArg arg1)
{

	// Init UARTs
	//UART_Handle uart0 = init_uart( 0 );
	UART_Handle uart1 = init_uart( 1 );
	UART_Handle uart2 = init_uart( 2 );
	UART_Handle uart3 = init_uart( 3 );
	UART_Handle uart7 = init_uart( 7 );

	// Read buffer
	char tcp_input;

	struct motor_struct _struct;

	while(1)
	{
		// Read one byte from TCP
			UART_read(uart7, &tcp_input, 1);
			//UART_write(uart0, &tcp_input, 1);

			if( tcp_input == 'L' )
			{
				UART_read(uart7, &tcp_input, 1);

				_struct.x = tcp_input;
				//////////////////////////
				// Left Command
				//////////////////////////
				mux_1( 8 );
				mux_2( 7 );
				mux_3( 6 );

				send_struct(uart1, &_struct, motor_controller2);
				send_struct(uart2, &_struct, motor_controller2);
				send_struct(uart3, &_struct, motor_controller2);
			}
			if( tcp_input == 'R' )
			{
				UART_read(uart7, &tcp_input, 1);

				_struct.x = tcp_input;
				//////////////////////////
				// Left Command
				//////////////////////////
				mux_1( 1 );
				mux_2( 2 );
				mux_3( 3 );

				send_struct(uart1, &_struct, motor_controller2);
				send_struct(uart2, &_struct, motor_controller2);
				send_struct(uart3, &_struct, motor_controller2);
			}
		}
	}


#endif /* TCP_TASK_H_ */
