/*
 * tcp_task.h
 *
 */

#ifndef UART_LOOPBACK_TASK_H_
#define UART_LOOPBACK_TASK_H_

#include "../include/struct_xfer.h"
#include "../include/json.h"

extern Void bms_data(UArg arg0, UArg arg1)
{
	System_printf("Starting battery check program");
	System_flush();
	UART_Handle uart = init_uart( 5, 115200 );

	mux_5(14);

	struct bms_data_struct test_struct;

	bool is_valid = false;

	while(1)
	{
		is_valid = recv_struct( uart, &test_struct, bms );

		if ( is_valid )
		{
			System_printf("Volt 0: %i\n", test_struct.volt0);
			System_printf("Volt 1: %i\n", test_struct.volt1);
			System_printf("Volt 2: %i\n", test_struct.volt2);
			System_printf("Volt 3: %i\n", test_struct.volt3);
			System_printf("Volt 4: %i\n", test_struct.volt4);
			System_printf("Volt 5: %i\n", test_struct.volt5);
			System_printf("Volt 6: %i\n", test_struct.volt6);

			System_printf("Temp 0: %i\n", test_struct.temp0);
			System_printf("Temp 1: %i\n", test_struct.temp1);
			System_printf("Temp 2: %i\n", test_struct.temp2);
			System_printf("Temp 3: %i\n", test_struct.temp3);
			System_printf("Temp 4: %i\n", test_struct.temp4);
			System_printf("Temp 5: %i\n", test_struct.temp5);
			System_printf("Temp 6: %i\n", test_struct.temp6);
			System_flush();

		}
	}
}

#endif /* TCP_TASK_H_ */
