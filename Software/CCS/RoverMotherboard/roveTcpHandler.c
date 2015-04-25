// roveTcpHandler.c
//
// first created:
//
// 01_22_2015_Owen_Chiaventone omc8db@mst.edu
//
// last edited:
//
// 04_07_2015_Judah Schad_jrs6w7@mst.edu
//
// this implements a single function BIOS thread that acts as the RoverMotherboard.cfg roveTcpHandlerTask handle
//
// recieves base station commands and send device telemetry using tcp ip bsd sockets

#include "roveIncludes/roveWareHeaders/roveTcpHandler.h"

// BIOS_start in main inits this as the roveTcpHandlerTask Thread

// this is a RoverMotherboard.cfg object::roveTcpHandlerTask::		priority 2, vital_flag = t, 2048 persistent private stack

Void roveTcpHandler(UArg arg0, UArg arg1){

	//init socket file environment

	extern const uint8_t FOREVER;

	fdOpenSession((void*)TaskSelf());

	struct NetworkConnection RED_socket;
	RED_socket.isConnected = false;

	static char messageType = NULL;

	//Sending Task Parameters
    Task_Handle        taskHandle;
    Task_Params        taskParams;
    Error_Block        eb;

	//the task loops for ever and only exits from BIOS_start, on error state

    System_printf("roveTCPHandler 		init! \n");
    System_printf("\n");
    System_printf("\n");
    System_flush();

    while(FOREVER){

						System_printf("Attempting to connect\n");
						System_flush();

    	attemptToConnect(&RED_socket);

    	//Create sending thread
    	if(RED_socket.isConnected)
    	{
    		//Spawn sending thread

            Error_init(&eb);

            System_printf("Spawning roveTcpSender\n");
            Task_Params_init(&taskParams);
            taskParams.arg0 = (UArg)(RED_socket.socketFileDescriptor);
            taskParams.stackSize = 1280;
            taskParams.priority = SEND_TASK_PRIORITY;
            taskHandle = Task_create((Task_FuncPtr)roveTcpSender, &taskParams, &eb);
            //Check to see if memory could not be allocated for the task
            if (taskHandle == NULL) {
                System_printf("Error: Failed to create new roveTcpSender Task\n");
            }

    	}

    					System_printf("Finished attempt. Result: ");

    	// loop to recieve cmds and send telem from and to the base station: if socket breaks, loop breaks and we attempt to reconnect

    	while(RED_socket.isConnected == true){

							//System_printf("Connected\n");
							//System_flush();

    		// get Message Type, check for connection errors

    		if(roveRecv(&RED_socket, &messageType, 1) != -1){

    			switch(messageType){

					case CONSOLE_COMMAND:
					break;

					case SYNCHRONIZE_STATUS:
					break;

					case COMMAND_METADATA:
					break;

					case TELEM_METADATA:
					break;

					case ERROR_METADATA:
					break;

					// defined 5
					case ROVER_COMMAND:

						//System_printf("Got rover command. Passing control.\n");
						//System_flush;

						parseRoverCommandMessage(&RED_socket);

					break;

					case ROVER_TELEM:
					break;

					case ROVER_ERROR:
					break;

					// defined {
					case JSON_START_BYTE:

						System_printf("Got JSON start byte. Error, unable to Parse\n");

					break;

					default:

						System_printf("Command identifier not recognized: %c\n", messageType);

					break;

    			}//endswitch(messageType)

    		}else{

    			System_printf("Connection has been closed\n");
    			System_flush();

    		}//endif(roveRecv(&RED_socket, &messageType, 1) != -1)

    	}//endwhile(RED_socket.isConnected == true)

    	System_printf("Connection Lost\n\n");
    	System_flush();

    	// if execution reaches this point, then the connection has broken and we will attempt a new socket

    	close(RED_socket.socketFileDescriptor);

    }//endwhile (FOREVER)


    //postcondition: execution will not reach this state unless a serious error occurs

    //close the socket file environment

    fdCloseSession((void*)TaskSelf());

    System_printf("Tcp Handler Task Error: Forced Exit\n");
    System_flush();

    //exit Task

    Task_exit();

}//endfnctnTask roveTcpHandler Thread


Void roveTcpSender(UArg arg0, UArg arg1)
{
	struct NetworkConnection RED_socket;
	RED_socket.socketFileDescriptor = arg0;
	RED_socket.isConnected = true;
	to_base_station_msg_struct toBaseTelem;
	//Setup

	//Loop: Wait on mailbox, send keepalive otherwise
	while(RED_socket.isConnected)
	{
		//Check if there's data in the outgoing mailbox. This will block for a number of system ticks.
		if(Mailbox_pend(toBaseStationMailbox, &toBaseTelem, SEND_KEEPALIVE_DELAY_TICKS))
		{

			System_printf("Passed the Pend in TCP!! Success!!!\n");
			System_flush();

			//Let the base station know what we're sending
			roveSend(&RED_socket, toBaseTelem.bs_message_type, 1);

			//Send the id
			roveSend(&RED_socket, toBaseTelem.struct_id, 1);

			//Send the value
			roveSend(&RED_socket, toBaseTelem.value, getStructSize(toBaseTelem.struct_id));

		} else //Nothing to go out
		{
			System_printf("No data to send\n");
			System_flush();
		}

	}

	//Cleanup: Connection has broken

	fdCloseSession((void*)TaskSelf());
	Task_exit();
}


// Network Abstraction Layer

static int roveRecv(struct NetworkConnection* connection, char* buffer, int bytes){

	static int bytesRecvd;

	if(connection->isConnected){

		bytesRecvd = recv(connection->socketFileDescriptor, buffer, bytes, MSG_WAITALL);

		if(bytesRecvd <= 0){

			connection->isConnected = false;

			// connection broke
			return -1;
		}else{

			// recv'd correctly
			return bytesRecvd;

		}}else{

		// not connected
		return -1;
	}//endif

}//endfnctn roveRecv

static int roveSend(struct NetworkConnection* connection, char* buffer, int bytes)
{
	static int bytesSent;

	if(connection->isConnected){

		bytesSent = send(connection->socketFileDescriptor, buffer, bytes, MSG_WAITALL);

		if(bytesSent <= 0){

			connection->isConnected = false;

			// connection broke
			return -1;
		}else{

			// recv'd correctly
			return bytesSent;

		}}else{

		// not connected
		return -1;
	}//endif
}

/*
static int roveSend(struct NetworkConnection* connection, char* buffer, int bytes)
{
	return 0;
}
*/

static bool attemptToConnect(struct NetworkConnection* connection){

    struct sockaddr_in server_addr;
	struct timeval timeout;

	connection->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   	//flag for bad socket

	if(connection->socketFileDescriptor == -1){

		System_printf("Failed Socket() create serverfd (src = socket()) (%d)\n",fdError() );
		System_flush();

	}//endif:	(serverfd == -1)

	//init bsd socket config struct

	memset(&server_addr, 0, sizeof(server_addr) );

	//config the socket

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(TCPPORT);
	inet_pton(AF_INET, RED_IP, &server_addr.sin_addr);

	timeout.tv_sec = NETWORK_TIMEOUT;
	timeout.tv_usec = 0;

	//setsockopt(connection->socketFileDescriptor, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout) );
	//setsockopt(connection->socketFileDescriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout) );

	//connect to Red

	//connect the socket

	if(connect(connection->socketFileDescriptor, (PSA)&server_addr, sizeof(server_addr)) < 0){

		connection->isConnected = false;
		return false;

	}else{

		connection->isConnected = true;
		return true;

	}//endif

	//Share the socket
	//fdShare()

}//endfnctn attemptToConnect(struct NetworkConnection* connection)

static bool parseRoverCommandMessage(struct NetworkConnection* connection){

	int size;
	static base_station_msg_struct messagebuffer;

					//System_printf("Entering parseRoverCommandMessage\n");
					//System_flush();

	// get type of message

	if(!roveRecv(connection, &(messagebuffer.id), 1)){

		return false;

	}//endif

	//TODO: Not really sure about the best way to do this. We should probably
	//      have a lookup function that takes message type and outputs

					//System_printf("Getting struct size\n");
					//System_flush();

	// get size of message

	size = getStructSize((char)messagebuffer.id) - 1;

	//TODO 169-D remove the address operator for second paramenter to return char* instead of char**

	// get message contents
	if(!roveRecv(connection, &(messagebuffer.value), size)){

		return false;

	}//endif

					//System_printf("Recieved data. Posting to mailbox\n");
					//System_flush();

	// post message to maibox. The mailbox is defined as a global by the config script

	Mailbox_post(fromBaseStationMailbox, &messagebuffer, BIOS_WAIT_FOREVER);

	return true;

}//endfnctn parseRoverCommandMessage(struct NetworkConnection* connection)
