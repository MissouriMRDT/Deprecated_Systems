/*
 * networkRove.c
 *
 *  Created on: Jan 12, 2015
 *      Author: me
 */

Void networkFncRove(UArg arg0, UArg arg1)
{

	//red_socket
	SOCKET clientfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientfd < 0) {
	        System_printf("tcpHandler: socket failed\n");
	        Task_exit();
	        return;
	}//endif

	//rover_addr
	struct sockaddr_in sLocalAddr;

    memset((char *)&sLocalAddr, 0, sizeof(sLocalAddr));
    sLocalAddr.sin_family = AF_INET;
    sLocalAddr.sin_len = sizeof(sLocalAddr);
    sLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sLocalAddr.sin_port = htons(ROVE_LISTEN_PORT);

    status = bind(lSocket, (struct sockaddr *)&sLocalAddr, sizeof(sLocalAddr));
    if (status < 0) {
        System_printf("tcpHandler: bind failed\n");
        fdClose(lSocket);
        Task_exit();
        return;
    }


	//initialize buffer and set contents to zero
	char tcp_recv_buffer[RECV_BUFFER_SIZE] = "";





    int num_bytes_recvd  = recv(red_socket, (char *)tcp_recv_buffer, MAX_PACKET_SIZE, 0);




    fdOpenSession(TaskSelf());

    System_printf("tcpWorker: start clientfd = 0x%x\n", clientfd);

    /* Make sure Error_Block is initialized */
    Error_init(&eb);

    /* Get a buffer to receive incoming packets. Use the default heap. */
    buffer = Memory_alloc(NULL, TCPPACKETSIZE, 0, &eb);
    if (buffer == NULL) {
        System_printf("tcpWorker: failed to alloc memory\n");
        Task_exit();
    }

    /* Loop while we receive data */
    while (flag) {
        nbytes = recv(clientfd, (char *)buffer, TCPPACKETSIZE, 0);
        if (nbytes > 0) {
            /* Echo the data back */
            send(clientfd, (char *)buffer, nbytes, 0 );
        }
        else {
            fdClose(clientfd);
            flag = false;
        }
    }
    System_printf("tcpWorker stop clientfd = 0x%x\n", clientfd);

    /* Free the buffer back to the heap */
    Memory_free(NULL, buffer, TCPPACKETSIZE);

    fdCloseSession(TaskSelf());
    /*
     *  Since deleteTerminatedTasks is set in the cfg file,
     *  the Task will be deleted when the idle task runs.
     */
    Task_exit();
}



#endif /* NETWORKROVE_H_ */





