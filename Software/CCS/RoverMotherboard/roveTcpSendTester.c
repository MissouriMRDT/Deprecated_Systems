//
//
//
// roveSendTcpTester.c
//
//  Created on: Apr 25, 2015
//      Author: mrdtdev
//

//BIOS_start inits this as the roveTcpSendTester Thread

//This is a RoverMotherboard.cfg object::		roveTcpSendTester		::		priority 1, vital_flag = t, 2048 persistent private stack

#include "roveIncludes/roveWareHeaders/roveTcpSendTester.h"

Void roveTcpSendTester(UArg arg0, UArg arg1){

	const uint8_t FOREVER = 1;

	base_station_msg_struct toBaseMessage;

	int i;

	float value = 0;

	while(FOREVER){

		//200 total amps
		//25 amps per cell

		//33.6 volts
		//4.2 volts per cell

		// struct power_board_bms_telem
		// uint8_t struct_id;
		// float value;

		// bms_cell1_voltage_telem_id   151
		// bms_cell2_voltage_telem_id	152
		// bms_cell3_voltage_telem_id	153
		// bms_cell4_voltage_telem_id	154
		// bms_cell5_voltage_telem_id	155
		// bms_cell6_voltage_telem_id	156
		// bms_cell7_voltage_telem_id	157
		// bms_cell8_voltage_telem_id	158

		for(i = 151; i < 159; i++ ){

			ms_delay(500);

			((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = i;
			((struct power_board_bms_telem*)(&toBaseMessage))->value = 4.2;

			System_printf("Struct_id: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->struct_id);
			System_printf("Value: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->value);
			System_flush();

			Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);

			ms_delay(500);

		}//endfor

		for(i = 151; i < 159; i++ ){

			ms_delay(500);

			((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = i;
			((struct power_board_bms_telem*)(&toBaseMessage))->value = 2.7356;

			System_printf("Struct_id: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->struct_id);
			System_printf("Value: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->value);
			System_flush();

			Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);

			ms_delay(500);

		}//endfor

		// bms_pack_voltage_telem_id	159

		ms_delay(500);

		((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = 159;
		((struct power_board_bms_telem*)(&toBaseMessage))->value = 33.6;

		System_printf("Struct_id: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->struct_id);
		System_printf("Value: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->value);
		System_flush();

		Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);

		ms_delay(500);

		((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = 159;
		((struct power_board_bms_telem*)(&toBaseMessage))->value = 17.6356;

		System_printf("Struct_id: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->struct_id);
		System_printf("Value: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->value);
		System_flush();

		Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);

		// bms_total_amperage_telem_id	160

		ms_delay(500);

		((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = 160;
		((struct power_board_bms_telem*)(&toBaseMessage))->value = 200;

		System_printf("Struct_id: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->struct_id);
		System_printf("Value: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->value);
		System_flush();


		Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);

		ms_delay(500);

		((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = 160;
		((struct power_board_bms_telem*)(&toBaseMessage))->value = 101.5467;

		Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);


		// power_board_telem_motor1_current_id 				180
		// power_board_telem_motor2_current_id 				181
		// power_board_telem_motor3_current_id 				182
		// power_board_telem_motor4_current_id 				183
		// power_board_telem_motor5_current_id 				184
		// power_board_telem_motor6_current_id 				185

		for(i = 180; i < 186; i++ ){

			ms_delay(500);

			((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = i;
			((struct power_board_bms_telem*)(&toBaseMessage))->value = 24.2;

			Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);

			ms_delay(500);

			System_printf("Struct_id: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->struct_id);
			System_printf("Value: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->value);
			System_flush();


		}//endfor

		for(i = 180; i < 186; i++ ){

			ms_delay(500);

			((struct power_board_bms_telem*)(&toBaseMessage))->struct_id = i;
			((struct power_board_bms_telem*)(&toBaseMessage))->value = 5.2356;

			Mailbox_post(toBaseStationMailbox, &toBaseMessage, BIOS_WAIT_FOREVER);

			ms_delay(500);

			System_printf("Struct_id: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->struct_id);
			System_printf("Value: %d\n", ((struct power_board_bms_telem*)(&toBaseMessage))->value);
			System_flush();

		}//endfor

		// power_board_telem_aux_current_id					186
		// power_board_telem_5V_bus_current_id				187
		// power_board_telem_12v_critical_bus_current_id	188
		// power_board_telem_12v_highpower_bus_current_id	189
		// power_board_telem_robotarm_bus_current_id		190
		// power_board_telem_main_battery_voltage_id		191

	}//endwhile

}//endfnctn  roveTcpSendTester



