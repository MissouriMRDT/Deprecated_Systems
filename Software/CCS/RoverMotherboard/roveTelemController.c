/*
 * roveTelemController.c
 *
 *  Created on: Feb 14, 2015
 *      Author: mrdtdev
 */

#include "roveTelemController.h"

Void roveTelemController(UArg arg0, UArg arg1)
{
/*
	// define extern UARTs
	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;


	// Package Telem Struct
	struct package_telem_struct package_telem_struct;

	// Test Device Struct
	struct test_device_data_struct test_device_data_struct

	bool test_telem_is_valid = false;

	while(1)
	{

		mux_1( 9 );
		ms_delay( 1 );
		test_telem_is_valid = recv_struct( uart1, &test_device_data_struct, test );

		if( test_telem_is_valid )
		{

		System_printf("test_telem_is_valid is valid mux_1( 9 ) \n");
		System_flush();

		package_telem_struct.id = test_telem_is_valid.id;
		package_telem_struct.value = test_telem_is_valid.value;
		Mailbox_post(toBaseStationMailbox, &package_telem_struct, BIOS_WAIT_FOREVER);

		//void generate_json_strings(char *string_buf, const char *id, const char *value)
		//generate_json_strings(char *string_buf, const char *id, const char *value);

	}//endwhile
*/

	System_printf("roveTelemController has priority right now \n");
	System_flush();

}//endfnct roveTelemContoller



