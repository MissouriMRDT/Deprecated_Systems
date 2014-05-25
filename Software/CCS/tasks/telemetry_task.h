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
	struct power_board_telem power_telem;

	bool bms_is_valid = false;
	bool gps_is_valid = false;
	bool drill_telem_valid = false;
	bool power_telem_valid = false;

	extern bool drill_telem_active;
	extern bool gps_telem_active;
	extern bool power_telem_active;
	extern bool uart7_sem;

	char json[50];

	while(1)
	{
		if ( gps_telem_active )
		{
			mux_5(328);
			ms_delay( 1 );
			gps_is_valid = recv_struct( uart5, &gps_data, gps );

			if( gps_is_valid )
			{
				generate_json_strings(json, "0000", "GPS Data Valid");
				write_json(uart7, json);

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
			else
			{
				generate_json_strings(json, "0000", "GPS Data Not Valid");
				write_json(uart7, json);
			}
		}

		///////////////////
		// Read BMS data
		///////////////////
		mux_5(15);
		ms_delay( 1 );
		bms_is_valid = recv_struct( uart5, &bms_struct, bms );

		if ( bms_is_valid )
		{
			generate_json_strings(json, "0000", "BMS Data Valid");
			write_json(uart7, json);
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
		}
		else
		{
			generate_json_strings(json, "0000", "BMS Data Not Valid");
			write_json(uart7, json);
		}

		//////////////////////////////
		// Read Power board data
		//////////////////////////////
		if ( power_telem_active )
		{
			mux_5(13);
			ms_delay( 5 );
			power_telem_valid = recv_struct( uart5, &power_telem, power_board );

			if ( power_telem_valid )
			{
				generate_json_strings(json, "0000", "BMS Data Valid");
				write_json(uart7, json);
				ms_delay( delay );

				// Ambient Temperature
				generate_json_int(json, "5001", power_telem.ambientTemperature);
				write_json(uart7, json);
				ms_delay( delay );

				// Bus A Voltage
				generate_json_int(json, "5002", power_telem.busAVoltage);
				write_json(uart7, json);
				ms_delay( delay );

				// Bus B Voltage
				generate_json_int(json, "5003", power_telem.busBVoltage);
				write_json(uart7, json);
				ms_delay( delay );

				// Bus C Voltage
				generate_json_int(json, "5004", power_telem.busCVoltage);
				write_json(uart7, json);
				ms_delay( delay );

				//Input Voltage
				generate_json_int(json, "5005", power_telem.inputVoltage);
				write_json(uart7, json);
				ms_delay( delay );

				//Input Current
				generate_json_int(json, "5006", power_telem.inputCurrent);
				write_json(uart7, json);
				ms_delay( delay );
			}
			else
			{
				generate_json_strings(json, "0000", "Power Data Not Valid");
				write_json(uart7, json);
			}
		}

		/////////////////////
		// Drill Telemetry
		/////////////////////
		if ( drill_telem_active )
		{
			// Switch mux
			mux_2(10);
			ms_delay( 5 );

			drill_telem_valid = recv_struct( uart2, &drill_telem, drill );

			if ( drill_telem_valid )
			{
				generate_json_strings(json, "0000", "Drill Data Valid");
				write_json(uart7, json);

				// Hydrogen Reading
				generate_json_int(json, "6015", drill_telem.hydrogenReading);
				write_json(uart7, json);
				ms_delay( delay );

				// Methane Reading
				generate_json_int(json, "6016", drill_telem.methaneReading);
				write_json(uart7, json);
				ms_delay( delay );

				// Ammonia Reading
				generate_json_int(json, "6017", drill_telem.ammoniaReading);
				write_json(uart7, json);
				ms_delay( delay );

				generate_json_float(json, "6018", drill_telem.temp);
				write_json(uart7, json);
				ms_delay( delay );

				// Actual Speed
				generate_json_int(json, "6019", drill_telem.actualSpeed);
				write_json(uart7, json);
				ms_delay( delay );

				// Goal Current
				generate_json_int(json, "6020", drill_telem.goalCurrent);
				write_json(uart7, json);
				ms_delay( delay );

				// Actual Current
				generate_json_int(json, "6021", drill_telem.actualCurrent);
				write_json(uart7, json);
				ms_delay( delay );
			}

			else
			{
				generate_json_strings(json, "0000", "Drill Data Not Valid");
				write_json(uart7, json);
			}
		}
	}
}

#endif /* TELEMETRY_TASK_H_ */
