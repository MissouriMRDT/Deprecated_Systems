/*
 * networkRove.c
 *
 *  Created on: Jan 12, 2015
 *      Author: me
 */

Void networkFncRove(UArg arg0, UArg arg1)
{

	//handle to our networkFncRove to allow file descriptors in this thread
    fdOpenSession(TaskSelf());

	//red_socket
	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_socket < 0) {
	        System_printf("Socket listen failed\n");
	        Task_exit();
	        return;
	}//endif

	//rover_local_address
	struct sockaddr_in sLocalAddr;
    memset((char *)&sLocalAddr, 0, sizeof(sLocalAddr));
    sLocalAddr.sin_family = AF_INET;
    sLocalAddr.sin_len = sizeof(sLocalAddr);
    //need to hardcode RED_IP_ADDR
    sLocalAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sLocalAddr.sin_port = htons(ROVE_LISTEN_PORT);

    int bind_status;
    bind_status = bind(listen_socket, (struct sockaddr *)&sLocalAddr, sizeof(sLocalAddr));
    if (bind_status < 0) {
    	System_printf("Socket bind failed\n");
        fdClose(clientfd);
        Task_exit();
        return;
    }//endif

    if (listen(listen_socket, MAXCONN) != 0){
        System_printf("Socket listen failed\n");
        fdClose(listen_socket);
        Task_exit();
        return;
    }//endif

    //we must declare option storage space
    int optval;
    int optlen = sizeof(optval);
	if (setsockopt(listen_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
      System_printf("Socket setsockopt failed\n");
      fdClose(listen_socket);
      Task_exit();
      return;
    }//endif

	//initialize buffer and set contents to zero
	char tcp_recv_buffer[RECV_BUFFER_SIZE] = "";
	int num_bytes_recvd = 0;
	bool recvFlag = TRUE;
	bool connectedFlag = FALSE;
	SOCKET clientfd;

	/* Loop Forever */
	while (TRUE) {

		//try to connect
		clientfd = accept(listen_socket, (struct sockaddr*)&client_addr, &addrlen);
		while (clientfd == INVALID_SOCKET){
			//retry to connect
			clientfd = accept(listen_socket, (struct sockaddr*)&client_addr, &addrlen);
		}//endwhile

		//we are connected
		connectedFlag = TRUE;

		/* Loop while we receive data */
		while (recvFlag) {
			num_bytes_recvd  = recv(listen_socket, (char *)tcp_recv_buffer, MAX_PACKET_SIZE, 0);
			if (num_bytes_recvd > 0) {
		            /* Echo the data back */
		            send(clientfd, (char *)tcp_recv_buffer, num_bytes_recvd, 0 );
		        }
		        else {
		        	System_printf("Socket recv failed\n");
		        	//todo
		            fdClose(clientfd);
		            recvFlag = FALSE;
		            Task_exit();
		            return;
		     }//endif

		}//endwhile

	}//endwhile
    System_printf("End networkFncRove stop clientfd = 0x%x\n", clientfd);

    fdCloseSession(TaskSelf());

return;

}//endfnctn








