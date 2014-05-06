/*
 * tcp_test.h
 *
 *  Created on: Apr 24, 2014
 *      Author: Zeus
 */

#ifndef TCP_TEST_H_
#define TCP_TEST_H_

#include "../include/tcp.h"

extern Void eth_test(UArg arg0, UArg arg1)
{
	// Initial TCP connection
	init_w5100();
	tcp_connect();

	while(1)
	{
		////////////////////
		// Reconnect logic
		////////////////////

		// If socket is disconnnected
	    if ( socket_connected() == false)
	    {
	    	System_printf("Socket disconnected\n");
	    	System_flush();

	    	// Reconnect
	    	init_w5100();
	    	tcp_connect();
	    }
	    /*
	    else
	    {
			//////////////////////
			// Recv Data
			//////////////////////
			uint32_t size;

			size = SPI_Read( S0_RX_RSR );
			System_printf("data size: %i\n", size);
			System_flush();
	    }
*/	}
}

#endif /* TCP_TEST_H_ */
