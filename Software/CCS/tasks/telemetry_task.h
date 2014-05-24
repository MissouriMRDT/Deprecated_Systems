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
	extern UART_Handle uart2;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart7;

	struct bms_data_struct bms_struct;
	struct gps_data_struct gps_data;
	struct drill_Telemetry drill_telem;

	bool bms_is_valid = false;
	bool gps_is_valid = false;
	bool drill_telem_valid = false;

	extern bool drill_telem_active;

	char json[50];
	char loop_count[15];
	char loop_string[25];

	int gps_counter = 20;
	int telem_loop_counter = 0;

	while(1)
	{
		// System tick
		telem_loop_counter++;
		itoa(telem_loop_counter, loop_count);
		strcpy( loop_string, "Telemetry Loop: " );
		strcat( loop_string, loop_count);
		generate_json_strings(json, "0000", loop_string);
		write_json(uart7, json);

		if ( gps_counter >= 10 )
		{
			gps_counter = 0;
			mux_5(328);
			ms_delay( delay );
			gps_is_valid = recv_struct( uart5, &gps_data, gps );

			if( gps_is_valid )
			{
				// GPS fix
				generate_json_int(json, "1001", gps_data.fix);
				write_json(uart7, json);
				ms_delay( delay );

				if ( gps_data.fix == 1 )
				{
					// Latitude
					generate_gps_json(json, "1002", gps_data.latitude_whole, gps_data.latitude_frac, gps_data.lat_dir);
					write_json(uart7, json);
					ms_delay( delay );

					// Longitude
					generate_gps_json(json, "1003", gps_data.longitude_whole, gps_data.longitude_frac, gps_data.lon_dir);
					write_json(uart7, json);
					ms_delay( delay );

					// Altitude
					generate_altitude_json(json, "1004", gps_data.altitude_whole, gps_data.altitude_frac);
					write_json(uart7, json);
					ms_delay( delay );

					// # of satellites
					generate_json_int(json, "1005", gps_data.satellites);
					write_json(uart7, json);
					ms_delay( delay );
				}
			}
		}
		else
		{
			gps_counter++;
		}

		///////////////////
		// Read BMS data
		///////////////////
		mux_5(14);
		ms_delay( delay );
		bms_is_valid = recv_struct( uart5, &bms_struct, bms );

		if ( bms_is_valid )
		{
			// Battery voltages

			// Cell 0
			generate_json_int(json, "3001", bms_struct.volt0);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 1
			generate_json_int(json, "3002", bms_struct.volt1);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 2
			generate_json_int(json, "3003", bms_struct.volt2);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 3
			generate_json_int(json, "3004", bms_struct.volt3);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 4
			generate_json_int(json, "3005", bms_struct.volt4);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 5
			generate_json_int(json, "3006", bms_struct.volt5);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 6
			generate_json_int(json, "3007", bms_struct.volt6);
			write_json(uart7, json);
			ms_delay( delay );

			// Battery Temps

			// Cell 0
			generate_json_int(json, "3008", bms_struct.temp0);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 1
			generate_json_int(json, "3009", bms_struct.temp1);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 2
			generate_json_int(json, "3010", bms_struct.temp2);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 3
			generate_json_int(json, "3011", bms_struct.temp3);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 4
			generate_json_int(json, "3012", bms_struct.temp4);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 5
			generate_json_int(json, "3013", bms_struct.temp5);
			write_json(uart7, json);
			ms_delay( delay );

			// Cell 6
			generate_json_int(json, "3014", bms_struct.temp6);
			write_json(uart7, json);
			ms_delay( delay );

			// Main Current
			generate_json_int(json, "3015", bms_struct.main_bat_cur);
			write_json(uart7, json);
			ms_delay( delay );

			// Main Voltage
			generate_json_int(json, "3016", bms_struct.main_bat_volt);
			write_json(uart7, json);
			ms_delay( delay );
		}

		// Drill Telemetry
		if ( drill_telem_active )
		{
			// Switch mux
			mux_2(10);
			ms_delay( 1 );

			drill_telem_valid = recv_struct( uart2, &drill_telem, drill );

			if ( drill_telem_valid )
			{
				System_printf("Drill Telem Good\n");
				System_flush();
			}
		}
	}
}

#endif /* TELEMETRY_TASK_H_ */
