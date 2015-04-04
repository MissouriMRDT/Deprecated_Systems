// roveTcpHandler.c
//
// first created:
//
// 01_22_2015_Owen_Chiaventone
//
// last edited:
//
//02_24_2015_Judah Schad_jrs6w7@mst.edu

//this implements a single function BIOS thread that acts as the RoverMotherboard.cfg roveTcpHandlerTask handle
//
//recieves base station commands and send device telemetry using tcp ip bsd sockets

#include "roveIncludes/roveWareHeaders/roveTcpHandler.h"

//BIOS_start inits this as the roveTcpHandlerTask Thread

//this is a RoverMotherboard.cfg object::		roveTcpHandlerTask		::		priority 1, vital_flag = t, 2048 persistent private stack

Void roveTcpHandler(UArg arg0, UArg arg1){

	//init socket file environment

	extern const uint8_t FOREVER;

	fdOpenSession((void*)TaskSelf());
	struct NetworkConnection RED_socket;
	RED_socket.isConnected = false;
	static char messageType = NULL;


	//the task loops for ever

	//only exits from BIOS_start, on error state

    System_printf("roveTCPHandler 		init! \n");
    System_printf("\n");
    System_printf("\n");
    System_flush();

    while(FOREVER){
    	System_printf("Attempting to connect\n");
    	System_flush();
    	attemptToConnect(&RED_socket);
    	System_printf("Finished attempt. Result: ");
    	//loop to recieve cmds and send telem from and to the base station: if socket breaks, loop breaks and we attempt to reconnect

    	while(RED_socket.isConnected == true)
    	{
    		System_printf("Connected\n");
    		System_flush();
    		//Get Message Type, check for connection errors
    		if(roveRecv(&RED_socket, &messageType, 1) != -1)
    		{
    			switch(messageType)
    			{
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
    			case ROVER_COMMAND:
    				System_printf("Got rover command. Passing control.\n");
    				parseRoverCommandMessage(&RED_socket);
    				break;
    			case ROVER_TELEM:
    			    break;
    			case ROVER_ERROR:
    			    break;
    			case JSON_START_BYTE:
    				System_printf("Got JSON start byte. Parsing...\n");
    				break;
    			default:
    				System_printf("Command identifier not recognized: %c\n", messageType);
    				break;
    			}
    		} else
    		{
    			System_printf("Connection has been closed\n");
    			System_flush();
    		}
    	}//endwhile(RED_socket.isConnected == true)
    	System_printf("Connection Lost\n\n");
    	System_flush();
    	//If execution reaches this point, then the connection has broken and we will attempt a new socket

    	close(RED_socket.socketFileDescriptor);

    }//endwhile:	(1)


    //postcondition: execution will not reach this state unless a serious error occurs

    //close the socket file environment

    fdCloseSession((void*)TaskSelf());

    System_printf("Tcp Handler Task Error: Forced Exit\n");
    System_flush();

    //exit Task

    Task_exit();

}//endfnctn:: 	roveTcpHandler() Task Thread


// ------- Network Abstraction Layer -----------//

static int roveRecv(struct NetworkConnection* connection, char* buffer, int bytes)
{
	static int bytesRecvd;
	if(connection->isConnected)
	{
		bytesRecvd = recv(connection->socketFileDescriptor, buffer, bytes, MSG_WAITALL);
		if(bytesRecvd <= 0)
		{
			connection->isConnected = false;
			//Connection broke
			return -1;
		} else
		{
			//Recv'd correctly
			return bytesRecvd;
		}
	} else
	{
		//Not connected
		return -1;
	}
}
/*
static int roveSend(struct NetworkConnection* connection, char* buffer, int bytes)
{
	return 0;
}
*/
static bool attemptToConnect(struct NetworkConnection* connection)
{
    struct 	         sockaddr_in server_addr;
	struct 			 timeval timeout;

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

	if(connect(connection->socketFileDescriptor, (PSA)&server_addr, sizeof(server_addr)) < 0)
	{
		connection->isConnected = false;
		return false;
	}	else
	{
		connection->isConnected = true;
		return true;
	}

	//Share the socket
	//fdShare()
}


static bool parseRoverCommandMessage(struct NetworkConnection* connection)
{
	static base_station_msg_struct messagebuffer;
	int size;

	System_printf("Entering parseRoverCommandMessage\n");
	System_flush();

	//Get type of message
	if(!roveRecv(connection, &(messagebuffer.id), 1))
		return false;

	//Get size of message
	//TODO: Not really sure about the best way to do this. We should probably
	//      have a lookup function that takes message type and outputs
	System_printf("Getting struct size\n");
	System_flush();
	size = getStructSize((char)messagebuffer.id) - 1;

	//Get message contents
	//TODO 169-D remove the address operator for second paramenter to return char* instead of char**
	if(!roveRecv(connection, &(messagebuffer.value), size))
		return false;

	System_printf("Recieved data. Posting to mailbox\n");
	System_flush();
	//Post message to maibox. The mailbox is defined as a global by the config script
	Mailbox_post(fromBaseStationMailbox, &messagebuffer, BIOS_WAIT_FOREVER);
	return true;
}
