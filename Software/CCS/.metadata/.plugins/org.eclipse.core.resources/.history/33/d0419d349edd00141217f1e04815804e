/*
 * roveStructTransfer.c
 *
 *  Created on: Mar 7, 2015
 *      Author: Connor Walsh
 */

#include "../mrdtRoveWare.h"

// New struct transfer to fill a buffer with a easy transfer frame

int buildSerialStructMessage(void* my_struct, char* buffer)
{
	uint8_t size;
	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t checkSum;
	int totalSize = -1;

	size = getStructSize(((struct rovecom_id_cast*)my_struct)->struct_id);
	if (size <= 0)
	{
		System_printf("Error in function: buildSerialStructMessage() - struct size is not valid");
		System_flush();
		return -1;
	}

//	checkSum = size;

	buffer[0] = start_byte1;
	buffer[1] = start_byte2;
	buffer[2] = size;

	// copy the struct into the buffer starting at byte 3
	memcpy(buffer + 3, my_struct, size);

	checkSum = calcCheckSum(my_struct, size);

	// 3 for two start bytes and size byte plus size of struct to get final position
	buffer[3 + size] = checkSum;

	totalSize = 3 + size + 1;

	return totalSize;
} // end Function

uint8_t calcCheckSum(const void* my_struct, uint8_t size)
{
	uint8_t checkSum = size;
	uint8_t i;

	for(i = 0; i < size; i++)
		checkSum ^= *((char*)my_struct + i);

	return checkSum;
}

//bool parseStructSerial(void* out_struct, enum peripheral_devices device, char* buffer)
//{
//	return true;
//}
/*
bool recv_struct(UART_Handle uart, void* my_struct, enum peripheral_devices device){

	uint8_t start_byte1 = 0x06;
	uint8_t start_byte2 = 0x85;
	uint8_t size;

	//calculate checksum

	uint8_t calc_CS;

	int i;

	//get size of struct

	switch(device){

		case bms:

			size = sizeof(*((struct bms_data_struct*)my_struct));

		break;

		case tcp_cmd:

			size = sizeof(*((struct base_station_msg_struct*)my_struct));

		break;

		case drill:

			size = sizeof(*((struct drill_Telemetry*)my_struct));

		break;

		case gps:

			size = sizeof(*((struct gps_data_struct*)my_struct));

		break;

		case power_board:

			size = sizeof(*((struct power_board_telem*)my_struct));

		break;

		case test:

					size = sizeof(*((struct test_device_data_struct*)my_struct));

		break;

	}//endswitch:		(device)

	char rx_buffer[150];
	char temp;

	//check for Start byte 1

	do{

		UART_read(uart, &temp, 1);

	}while(temp != start_byte1);

	// Check for Start byte 2

	UART_read(uart, &temp, 1);

	if(temp != start_byte2){

		//kick out of function

		return false;

	}//endif:		(temp != start_byte2)

	//check if size matches

	UART_read(uart, &temp, 1);

	if(temp != size){

		//size doesn't match

		return false;

	}//endif:		(temp != size)

	// Read in data bytes

	for(i = 0 ; i <= size ; i++){

		UART_read(uart, &temp, 1);
		rx_buffer[i] = temp;

	}//endfor:		(i = 0 ; i <= size ; i++)

	//calculate checksum

	calc_CS = size;

	for(i=0 ; i<size ; i++){

		calc_CS ^= rx_buffer[i];

	}//endfor:		(i=0 ; i<size ; i++)

	//flag for checksum match

	if(calc_CS != rx_buffer[size]){

		//checksum does not match

		return false;

	}//endif:		(calc_CS != rx_buffer[size]

	//copy buffer into struct

	memcpy (my_struct, rx_buffer, size);

	//fnctn success

	return true;

}//endnctn:		 recv_struct(UART_Handle uart, void* my_struct, enum peripheral_devices device)
*/
