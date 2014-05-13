/*
 * tcp_task.h
 *
 */

#ifndef TELEMETRY_TASK_H_
#define TELEMETRY_TASK_H_

#include "../include/struct_xfer.h"
#include "../include/json.h"
#include "../include/timing.h"

#define delay 1

extern Void bms_data(UArg arg0, UArg arg1)
{
	extern UART_Handle uart7;

	System_printf("Starting battery check program");
	System_flush();
	UART_Handle uart = init_uart( 5, 115200 );

	mux_5(14);

	struct bms_data_struct test_struct;

	bool is_valid = false;

	char json[50];

	while(1)
	{
		is_valid = recv_struct( uart, &test_struct, bms );

		if ( is_valid )
		{
			/////////////////////
			// Battery voltages
			/////////////////////

			// Cell 0
			generate_json_int(json, "3001", test_struct.volt0);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 1
			generate_json_int(json, "3002", test_struct.volt1);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 2
			generate_json_int(json, "3003", test_struct.volt2);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 3
			generate_json_int(json, "3004", test_struct.volt3);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 4
			generate_json_int(json, "3005", test_struct.volt4);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 5
			generate_json_int(json, "3006", test_struct.volt5);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 6
			generate_json_int(json, "3007", test_struct.volt6);
			write_json(uart7, json);
			ms_delay( delay );

			/////////////////////
			// Battery Temps
			/////////////////////

			// Cell 0
			generate_json_int(json, "3008", test_struct.temp0);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 1
			generate_json_int(json, "3009", test_struct.temp1);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 2
			generate_json_int(json, "3010", test_struct.temp2);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 3
			generate_json_int(json, "3011", test_struct.temp3);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 4
			generate_json_int(json, "3012", test_struct.temp4);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 5
			generate_json_int(json, "3013", test_struct.temp5);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 6
			generate_json_int(json, "3014", test_struct.temp6);
			write_json(uart7, json);
			ms_delay( delay );

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

#endif /* TELEMETRY_TASK_H_ */
