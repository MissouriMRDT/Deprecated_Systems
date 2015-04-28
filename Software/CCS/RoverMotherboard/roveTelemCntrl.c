//	TODO: Port To Fresh Build (using TI example:			This version educational practice not for distro)
//
// roveTelemCnrtl.c
//
// first created:
//
// 01_22_2015_Owen_Chiaventone
//
// last edited:
//
//02_28_2015_Judah Schad_jrs6w7@mst.edu

//	this implements a single function BIOS thread that acts as the RoverMotherboard.cfg roveTelemCntrl handle
//
//	recieves a request for telem from the command thread,
//
//	requests telem from the device,
//
//	recieves telem from the device,
//
//	and posts telem to the roveTCPHandler thread

#include "roveIncludes/roveWareHeaders/roveTelemCntrl.h"

//BIOS_start inits this as the roveTelemCntrlTask Thread

//This is a RoverMotherboard.cfg object::		roveTelemCntrlTask		::		priority 1, vital_flag = t, 2048 persistent private stack

Void roveTelemCntrl(UArg arg0, UArg arg1){

	extern UART_Handle uart2;

	int bytes_to_read = 11;
	char buffer[20];
	int bytes_read;
	int device = ONBOARD_ROVECOMM;

	while(1)
	{
		memset(buffer, '\0', 20);
		bytes_read = deviceRead(device, buffer, bytes_to_read, 2000);

		System_printf("Bytes read: %d\n", bytes_read);

		if (bytes_read > 0)
			System_printf("%s\n", buffer);
		System_flush();

		Task_sleep(5000);
	}

/*
	const uint8_t FOREVER = 1;

	struct device_telem_req deviceTelemReq;

	int poll_telem_array_idx = 2;
	char poll_telem_device[poll_telem_array_idx];

//	poll_telem_device[0] = bms_id;
//	poll_telem_device[1] = power_board_id;

	base_station_msg_struct messageInBuffer;

	char messageOutBuffer[MAX_TELEM_SIZE];

	int messageSize;

	int i;

	while(FOREVER){

		for(i = 0; i < poll_telem_array_idx; i++ ){

		int deviceJack = getDeviceJack(poll_telem_device[i]);

		//populate device id into the telem request

		deviceTelemReq.struct_id = telem_req_id;
		deviceTelemReq.telem_device_req_id = poll_telem_device[i];

		System_printf("Telem Entering build Serial\n");
		System_flush();

		messageSize = buildSerialStructMessage((void *)&deviceTelemReq, messageOutBuffer);

			System_printf("Message Size: %d\n", messageSize);
			System_flush();

			deviceWrite(deviceJack, messageOutBuffer, messageSize);

			//looping through RecvSerial until it becomes valid, which tells us we have a full message to post to base

			while( !RecvSerialStructMessage(deviceJack, &messageInBuffer) );

			System_printf("Struct_id: %d\n", &(messageInBuffer.id) );
			System_flush();

			System_printf("Value: %d\n", &(messageInBuffer.value[0]) );
			System_flush();

			Mailbox_post(toBaseStationMailbox, &messageInBuffer, BIOS_WAIT_FOREVER);

		}//endfor

	}//endwhile:	(1)

	//postcondition: execution will not reach this state unless a serious error occurs

	System_printf("Rove Telem Cntrl Task Error: Forced Exit\n");
	System_flush();

	//exit Task

	Task_exit();
	*/

}//endfnctn:		roveTelemContoller() Task Thread
