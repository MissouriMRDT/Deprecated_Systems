// roveTcpHandler.c MST MRDT
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu
//
// this implements a single function BIOS thread
// that acts as the RoverMotherboard.cfg roveTcpHandlerTask handle
//
// recieves base station commands and send device telemetry using tcp ip bsd sockets
//
// BIOS_start in main inits this as the roveTcpHandlerTask Thread
//
// this is a RoverMotherboard.cfg object::roveTcpHandlerTask::
//
// priority 2, vital_flag = t, 2048 persistent private stack

#include "roveIncludes/roveWareHeaders/roveTcpHandler.h"

Void roveTcpHandler(UArg arg0, UArg arg1) {

    //init socket file environment

    extern const uint8_t FOREVER;

    fdOpenSession((void*) TaskSelf());

    struct NetworkConnection RED_socket;
    RED_socket.isConnected = false;

    static char messageType = NULL;

    //Sending Task Parameters
    Task_Handle taskHandle;
    Task_Params taskParams;
    Error_Block eb;

    //the task loops for ever and only exits from BIOS_start, on error state

    printf("roveTCPHandler 		init! \n");
    printf("\n");
    printf("\n");

    while (FOREVER) {

        printf("Attempting to connect\n");

        attemptToConnect(&RED_socket);

        //Create sending thread
        if (RED_socket.isConnected) {

            //Spawn sending thread

            printf("Spawning roveTcpSender\n");

			Error_init(&eb);
			Task_Params_init(&taskParams);
			taskParams.arg0 = (UArg) (RED_socket.socketFileDescriptor);
			taskParams.stackSize = 1280;
			taskParams.priority = -1;
			taskHandle = Task_create((Task_FuncPtr) roveTcpSender, &taskParams,
					&eb);
			//Check to see if memory could not be allocated for the task
			if (taskHandle == NULL) {
				System_abort(
						"Error: Failed to create new roveTcpSender Task\n");
			}
			Task_setPri(taskHandle, 3);

            //Check to see if memory could not be allocated for the task
            if (taskHandle == NULL) {
                printf(
                        "Error: Failed to create new roveTcpSender Task\n");

            }//end if taskHandle

        }//end if isConnected

        printf("Finished attempt. Result: ");

        // loop to recieve cmds and send telem from and to the base station: if socket breaks, loop breaks and we attempt to reconnect

        while (RED_socket.isConnected == true) {

            //printf("Connected, entering roveRecv\n");


            // get Message Type, check for connection errors

            if (roveRecv(&RED_socket, &messageType, 1) != -1) {

                switch (messageType) {

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

                    //printf("Got rover command. Passing control.\n");
                    //System_flush;

                    parseRoverCommandMessage(&RED_socket);

                    break;

                case ROVER_TELEM:
                    break;

                case ROVER_ERROR:
                    break;

                    // defined {
                case JSON_START_BYTE:

                    printf(
                            "Got JSON start byte. Error, unable to Parse\n");

                    break;

                default:

                    printf("Command identifier not recognized: %c\n",
                            messageType);

                    break;

                }						//endswitch(messageType)

            } else {

                printf("Connection has been closed\n");


            }			//endif roveRecv

        }						//endwhile isConnected

        printf("Connection Lost\n\n");

		// if execution reaches this point, then the connection has broken and we will attempt a new socket
		fdClose(RED_socket.socketFileDescriptor);

    }						//endwhile FOREVER

    //postcondition: execution will not reach this state unless a serious error occurs

    //close the socket file environment

    fdCloseSession((void*) TaskSelf());

    printf("Tcp Handler Task Error: Forced Exit\n");


    //exit Task

    Task_exit();

}						//endfnctnTask roveTcpHandler Thread

Void roveTcpSender(UArg arg0, UArg arg1) {

	struct NetworkConnection RED_socket;
	RED_socket.socketFileDescriptor = arg0;
	RED_socket.isConnected = true;
	char message_type[] = {ROVER_TELEM};

	fdOpenSession(TaskSelf());
	fdShare(RED_socket.socketFileDescriptor);
	base_station_msg_struct toBaseTelem;
	//Setup

	//Loop: Wait on mailbox, send keepalive otherwise
	while (RED_socket.isConnected) {
		//Check if there's data in the outgoing mailbox. This will block for a number of system ticks.
		if (Mailbox_pend(toBaseStationMailbox, &toBaseTelem,SEND_KEEPALIVE_DELAY_TICKS))
		{

			//Send the message type and ID
			roveSend(&RED_socket, message_type, 1);
			roveSend(&RED_socket, &(toBaseTelem.id), 1);

			//Send the message contents
			roveSend(&RED_socket, (char *) &(toBaseTelem.value[0]),
					getStructSize(toBaseTelem.id));
			printf("Sent data\n");

		} else //Nothing to go out
		{
			printf("No data to send\n");

		}//end if

	}//end while

	printf("SendTask has detected a closed connection. Cleaning up\n");
	//Cleanup: Connection has broken
	fdClose(RED_socket.socketFileDescriptor);
	fdCloseSession((void*) TaskSelf());
	Task_exit();
}// end fnct roveTcpSender

// Network Abstraction Layer

static int roveRecv(struct NetworkConnection* connection, char* buffer,
        int bytes) {

	static int bytesRecvd;
	if (connection->isConnected) {

        bytesRecvd = recv(connection->socketFileDescriptor, buffer, bytes,
        MSG_WAITALL);

        if (bytesRecvd <= 0) {

            connection->isConnected = false;

            // connection broke
            return -1;
        } else {

            // recv'd correctly
            return bytesRecvd;

        }
    } else {

        // not connected
        return -1;
    }			//endif

}			//endfnctn roveRecv

static int roveSend(struct NetworkConnection* connection, char* buffer,
        int bytes) {
    static int bytesSent;

    if (connection->isConnected) {

        bytesSent = send(connection->socketFileDescriptor, buffer, bytes,
        MSG_WAITALL);

        if (bytesSent <= 0) {

            connection->isConnected = false;

            // connection broke
            return -1;
        } else {

            // recv'd correctly
            return bytesSent;

        }
    } else {

        // not connected
        return -1;
    }			//endif
}// end fnctn roveSend

static bool attemptToConnect(struct NetworkConnection* connection) {

    struct sockaddr_in server_addr;
    struct timeval timeout;

    connection->socketFileDescriptor = socket(AF_INET, SOCK_STREAM,
    IPPROTO_TCP);

    //flag for bad socket

    if (connection->socketFileDescriptor == -1) {

        printf("Failed Socket() create serverfd (src = socket()) (%d)\n",
                fdError());


    }			//endif:	(serverfd == -1)

    //init bsd socket config struct

    memset(&server_addr, 0, sizeof(server_addr));

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

    if (connect(connection->socketFileDescriptor, (PSA) &server_addr,
            sizeof(server_addr)) < 0) {

		connection->isConnected = false;
		printf("Fderror: %d\n", fdError());

		return false;

    } else {

        connection->isConnected = true;
        return true;

    }	//endif

    //Share the socket
    //fdShare()

}	//endfnctn attemptToConnect(struct NetworkConnection* connection)

static bool parseRoverCommandMessage(struct NetworkConnection* connection) {

    int size;
    static base_station_msg_struct messagebuffer;

    //printf("Entering parseRoverCommandMessage\n");

    // get type of message

    if (!roveRecv(connection, &(messagebuffer.id), 1)) {

        return false;

    }	//endif

    //TODO: Not really sure about the best way to do this. We should probably
    //      have a lookup function that takes message type and outputs

    //printf("Getting struct size\n");
    //

    // get size of message

    size = getStructSize((char) messagebuffer.id) - 1;

    //TODO 169-D remove the address operator for second paramenter to return char* instead of char**

	if(size <= 0)
	{
		printf("Invalid struct ID recieved: %d, skipping", messagebuffer.id);

	}

	//TODO 169-D remove the address operator for second paramenter to return char* instead of char**

    // get message contents
    if (!roveRecv(connection, &(messagebuffer.value), size)) {

        return false;

    }					//endif

    //printf("Recieved data. Posting to mailbox\n");


    // post message to maibox. The mailbox is defined as a global by the config script

    Mailbox_post(fromBaseStationMailbox, &messagebuffer, BIOS_WAIT_FOREVER);

    return true;

}	//endfnctn parseRoverCommandMessage(struct NetworkConnection* connection)
