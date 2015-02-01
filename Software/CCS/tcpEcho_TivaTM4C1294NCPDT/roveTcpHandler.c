/*
 * roveTcpHandler.c
 *
 *  Created on: Jan 22, 2015
 *      Author: Owen Chiaventone, Judah Schad, Connor Walsh
 *
 *  Deals with maintaining a connection to the base station
 *  more detailed documentation is available on the motherboard wiki
 */

#include "roveTcpHandler.h"

Void roveTcpHandler(UArg arg0, UArg arg1)
{

	System_printf("Tcp Handler Task Created\n");
	System_flush();

	//---- This command creates
	//     a file descriptor environment
	//     This is required to have a place to put the sockets
	//     The socket descriptors are integers that reference objects
	//     In this file descriptor environment
	//
	//     By default, this environment has space to hold up to 16 file
	//     descriptors concurrently. Calls to socket() and accept() will
	//     allocate one of these spaces to a socket object.
	//     Close(int socket) can be used to free one of these spaces
	fdOpenSession(TaskSelf());

	//----Allocate variables

    //A reference to the file descriptor of the socket object
	//Note that references to file descriptors are NOT pointers
    int                clientfd;

    int                connect_success;
    int                connectedFlag = NOT_CONNECTED; //Used to indicate if the system is connected to RED
    int                bytesReceived = 0; //Used for detecting errors in receiving
    int                bytesSent; //Used for echoing data
    MsgObj             fromBaseMsg;

    //Parameters for the Sending Task
    Task_Handle        taskHandle;
    Task_Params        taskParams;
    Error_Block        eb;

    //char fromBaseMsg.message_body[TCPPACKETSIZE]; //Where we hold incoming data

    connectedFlag = NOT_CONNECTED;

    //System_printf("Network Setup Completed\n\n");
    //System_flush();
    //---- The main loop
    //---- precondition: listen_socket is configured and listening on port TCPPORT
    while(1)
    {
    	//Block until a connection is available
    	//When it is, pass it off to the socket clientfd
    	System_printf("Attempting to Connect() new connection\n");
    	System_flush();

    	//---- Attempt to connect to base station
    	connect_success =  attemptToConnect(&clientfd);

    	if(connect_success < 0)
    	{
    		connectedFlag = NOT_CONNECTED;
    		System_printf("Error: accept() failed\n");
    		System_flush();
    	} else
    	{
    		connectedFlag = CONNECTED;
    		System_printf("Connected to RED\n");
    		System_flush();

    		//Spawn a send task

            /* Init the Error_Block */
            Error_init(&eb);

            /* Initialize the defaults and set the parameters. */
            System_printf("Spawning Task");
            Task_Params_init(&taskParams);
            taskParams.arg0 = (UArg)clientfd;
            taskParams.stackSize = 1280;
            taskHandle = Task_create((Task_FuncPtr)roveTcpSender, &taskParams, &eb);
            if (taskHandle == NULL) {
                System_printf("Error: Failed to create new Task\n");
                close(clientfd);
            }

    	}

    	//At this point, we know we have a valid connection
    	while(connectedFlag == CONNECTED)
    	{
    		//Pend on a new event being available on the socket
    		System_printf("Connected. Waiting for data\n");
    		System_flush();
    		bytesReceived = recv(clientfd, fromBaseMsg.message_body, TCPPACKETSIZE, 0);

    		//Check if the connection broke
    		if(bytesReceived<0)
    		{
    			connectedFlag = NOT_CONNECTED;
    			System_printf("Connection lost. (src = recv)\n");
    			System_flush();
    		} else
    		{
    			//At this point, we know that the connection is valid and we have data waiting

    			//Add a null character
    			fromBaseMsg.message_body[bytesReceived] = '\0';

    			//Dump data to debugging console
    			System_printf("Received data: %s\n", fromBaseMsg.message_body);
    			System_flush();

    			//Put the data in a mailbox
    			Mailbox_post(fromBaseStationMailbox, &fromBaseMsg, BIOS_WAIT_FOREVER);

    			//Echo the data back


    	        bytesSent = send(clientfd, fromBaseMsg.message_body, bytesReceived, 0);
    	        if (bytesSent < 0 || bytesSent != bytesReceived) {
    	            System_printf("Connection lost. (src = send)\n");
    	            connectedFlag = NOT_CONNECTED;
    	        } // endif

    		} // endelse

    	} // end while(connectedFlag == CONNECTED)

    	//If execution reaches this point, then the connection has broken
    	close(clientfd);
    } //end while(1)
    //---- postcondition: Execution will not reach this state unless a serious error occurs

    //Close the file descriptor environment opened at the start of the task
    fdCloseSession(TaskSelf());

	System_printf("Tcp Handler Task Exit\n");
	System_flush();
	return;
}

Void roveTcpSender(UArg arg0, UArg arg1)
{

    int  clientfd = (int)arg0;
    int  bytesSent;
    int  KEEPALIVE_SIZE = 9;
    int  isConnected = CONNECTED;
    System_printf("roveTcpSender: start thread for = 0x%x\n", clientfd);
    while(isConnected == CONNECTED)
    {
    	//Mailbox pend will go here. For now it will just send a keepalive after 2
    	Task_sleep(2000);

        bytesSent = send(clientfd, "keepalive", KEEPALIVE_SIZE, 0);

        if (bytesSent < 0 || bytesSent != KEEPALIVE_SIZE) {
            System_printf("Error: send failed.\n");
            isConnected = NOT_CONNECTED;
        }


    }

    System_printf("roveTcpSender: stop thread for = 0x%x\n", clientfd);
    Task_exit();
}


int attemptToConnect(int *the_socket)
{
	int connect_success;
    struct sockaddr_in localAddr;
    struct sockaddr_in clientAddr;
    int                optval;
    //int                optlen = sizeof(optval);
    //socklen_t          addrlen = sizeof(clientAddr);
    struct timeval     timeout; //Timeout settings for client

	//System_printf("Creating socket instance\n");
	//System_flush();
	*the_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( (*the_socket) == INVALID_SOCKET )
	{
		System_printf("failed socket create (%d)\n",fdError());
		System_flush();
	}

	//System_printf("Defining Socket Options\n");
	//System_flush();
	//----Define Socket options
	memset(&localAddr, 0, sizeof(localAddr));
	//Use IPv4
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(TCPPORT);
	System_printf("Assigning Target IP Address\n");
	inet_pton(AF_INET, RED_IP, &localAddr.sin_addr);

	//System_printf("Socket Options Set\n");
	//System_flush();
	// Configure our Tx and Rx timeout to be 5 seconds
	timeout.tv_sec = 3600;
	timeout.tv_usec = 0;
	setsockopt( *the_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
	setsockopt( *the_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

	//---- Attempt to make the connection
	connect_success =  connect( *the_socket, (PSA) &localAddr, sizeof(localAddr) );

	return connect_success;
}
