//	Using the Texas Instruments (TI) Network Developement Kit (NDK) Application Programmer Interface
//
//	Strict adherence to the TI NDK API OS App layer abstraction
//
//	Getting Started NDK - (skip to page 63)		www/ti.com/lit/an/spraax4.pdf
//
//	Full NDK User Guide -						www.ti.com/lit/ug/spru523i.pdf
//
//	NDK FULL API Define -						www.ti.com/lit/ug/spru524i.pdf
//
//  RTOS TI Kernel v6.4 -						www.ti.com/lit/ug/spruex3o/spruex3o.pdf
//
//
//
//	Inline declaration stylistics and system flushing purely for developement purpose
//
//
//
//	Think of the Base Station(RED) as the Rover's Client. rove_so_tcp_handler is our internal rtos tcp ip Server
//
//
//
//	Robot Martian Logic Layer:		Created Jan.2015:		MRDT:	Owen, Connor, Judah, G_Zuess_2014
//
//
//	Last Edited:					Jan.2015				MRDT:	Judah

#include "listen_handshake_tcp_ip_proto.h"

//	macro values, the preproccessor does a find and replace in pure text before compile time

#define TCPPACKETSIZE 1024
#define LOCAL_PORT_TO_LISTEN 4500
#define MAX_NUM_CLIENTS_IN_QUEU_SIZE 3

// 	rove_so_tcp_handler fronts as rtos scheduled handler in forever loop state with prioirity and implicit blocking
//  on a preallocated Stack through the NDK API Network TASK at the RTOS init
//
// 			via TIRTOS.PRODUCTS.SYSBIOS.SCHEDULING.TASK_INSTANCE
//			and TIRTOS.PRODUCTS.NDK.NETWORK.SCHEDULING.SCHEDULING_OPTIONS
//
// 	See tcpEcho.cfg for details
//			or navigate the CCS cnfg Gui path panes (i.e. Available Products->NDK>NETWORK>SCHEDULING ..etc)
//			(via XDCTools and XConfig rtsc markup bundles installed for eclispse)

Void rove_so_tcp_handler(UArg arg0, UArg arg1){

	// File descriptor environment in this Task's private memory

		System_printf("\n");
		System_printf("opening file descriptor environment");
		System_printf("\n");

	// System_printf buffer will only print to the console when you call flush or exit (SysMin)

		System_flush();

	// 			We believe this is in the compile time TASK_INIT() private stack frame. Task_Create() woud use a runtime dynamic Heap.

	// 			TaskSelf() returns a handle to rove_tcp_handler, much like a .this call in managed languages

	// 		We only use two socket structs in roveSoNet: listen_handshake_socket, and accept_recv_socket.

	// 		listen_handshake_socket instantiates memory binds to ip and port, and then
	//              listen_handshake_socket passes accept() this file descriptor (fd) context to accept_recv_socket during the handshake
	// 				listen_handshake_socket blocks idle but will implicitly awake on client re-connects thru hidden calls to ndk NETCTRL and NTLTOOL lower layers scheduled by rtos
	//				listen_handshake_socket fd context is entirely persisitent for the life of the program

	//		accept_recv_socket recieves client data in a buffer and passes to rover/rtos logic modules
	//				accept_recv_socket blocks idle in accept state if no data present but periodically polls
	//              the client for successful/keep alive and clear context and attempt to reinhereit fd contex from listen_handshake_socket at connection loss
	//              on error/reconnect reload states
	// 		 		TODO
	//              Add time out to the clear context and attempt to reinhereit fd contex from listen_handshake_socket at connection loss
	//              Add Message Queue Task for persistent buffer hook
	//              Remove inline format, comments, add logging Api config, remove One Time accept/recv/send test


	// 		We only use two keep_alive instances of the fd environment

	// 		A single listen socket
	//		A single accept socket that inhereits from the listen socket


	// 		fdOpenSession allocates ndk memory space emulating a linux file system for 16 bsd socket struct file descriptors

    fdOpenSession(TaskSelf());

    // create our listen_handshake_socket

    SOCKET listen_handshake_socket;

    // lets see how this looks intitialized. It should be init as INVALID_SOCKET (-1) state for disqualify use

    	System_printf("\n");
    	System_printf("instantiating the listen_handshake_socket = %d",listen_handshake_socket);
    	System_printf("\n");

    // Will only print to the console when you call flush or exit (SysMin)

    System_flush();

    // AF_INET			-	defined bsd standard for ipv4 config (as opposed to ipv6)
    // SOCK_STREAM		-	defined bsd standard for connection type of socket for STREAM (as opposed to raw sockets, datagram, etc)
    // IPPROTO_TCP		- 	defined bsd standard for tcp and ip protocol (as opposed to udp, etc)

    //			If socket() succeeds, it returns a file descriptor (valued int) to represent the socket
    //			Otherwise, a value of INVALID_SOCKET is returned and the functions errno() or fdError() can be used to return the detail types of error

    listen_handshake_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    	if (listen_handshake_socket < 0) {
    	    System_printf("\n");
    		System_printf("socket() failed");
    		System_printf("\n");
    		Task_exit();
    	return;
    	}//endif

    	System_printf("\n");
    	System_printf("this handle for listen_handshake_socket after socket() holds = %d", listen_handshake_socket);
    	System_printf("\n");
    	System_flush();

    // 0 is already reserved for fdStatus.return therefore we are initializing to 111 purely arbitrarily

      int fd_socket_status = 111;

    // FDSTATUS_RECV	-	TODO no idea what this means for detail?

    // 			fdstatus returns 0 for valid socket and on -1 writes the error for INVALID_SOCKET into our memory location
    //			We pass the &fd_socket_status for reference

      	fdStatus(listen_handshake_socket, FDSTATUS_RECV, &fd_socket_status);

      	System_printf("\n");
      	System_printf("fdStatus() for listen_handshake_socket after socket() = %d", fd_socket_status);
      	System_printf("\n");
      	System_flush();

      	System_printf("\n");
      	System_printf("we have now allocated and instatiated a socket");
      	System_printf("\n");
      	System_flush();

    //reset our custom fd error flags memspace

       	fd_socket_status = 111;

    //	Define our Struct for Socket Address Information on the file description Environment in socket 1 of the 16 frame socket memspace
    //			We really only care about IP ADDRESS and PORT. Everything else is basic config for bsd socket on ip/tcp
    // 			memset is init setting this Socket Address Information structure to zero

    // AF_INET			-	defined standard for ipv4 config (as opposed to ipv6)
    // INADDR_ANY		-	defined bsd standard for 0.0.0.0 implies we listen to ANY IP at this port
    // htonl			-	'host to network long' This flips the byte order b/c the network transport layer needs them backwards (reverse the endianess)

    // hard coding the port the Client will be connecting to listen and accept from (Base Station RED Software Application)

    // LOCAL_PORT_TO_LISTEN =  4500;

    struct sockaddr_in socket_local_addr;

    memset((char *)&socket_local_addr, 0, sizeof(socket_local_addr));
    socket_local_addr.sin_family = AF_INET;
    socket_local_addr.sin_len = sizeof(socket_local_addr);
    socket_local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_local_addr.sin_port = htons(LOCAL_PORT_TO_LISTEN);

    	int bindStatus = 111;

    // If bind() succeeds, this function returns 0
    //			Otherwise, a value of -1 is returned and the functions errno() or fdError() can be used to return the detail types of error

    bindStatus = bind(listen_handshake_socket, (struct sockaddr *)&socket_local_addr, sizeof(socket_local_addr));
    	if (bindStatus < 0) {
    	    System_printf("\n");
            System_printf("bind() failed");
            System_printf("\n");
            fdClose(listen_handshake_socket);
            Task_exit();
        return;
        }//endif

    	System_printf("\n");
    	System_printf("bindStatus for listen_handshake_socket after bind() = %d", bindStatus);
    	System_printf("\n");
    	System_flush();

    // lets see what fdstatus has to see about our socket now

    	fdStatus(listen_handshake_socket, FDSTATUS_RECV, &fd_socket_status);

    	System_printf("\n");
    	System_printf("fdStatus() for listen_handshake_socket after bind() = %d", fd_socket_status);
    	System_printf("\n");
    	System_flush();

    //reset our custom fd error flags memspace

    	fd_socket_status = 111;

    	System_printf("\n");
    	System_printf("we have now bound our listen_handshake_socket to ip, port, and tcp config");
    	System_printf("\n");
    	System_flush();

    // If listen() succeeds, this function returns 0
    //			Otherwise, a value of -1 is returned and the functions errno() or fdError() can be used to return the detail types of error

    	int listenStatus = 111;


    // MAX_NUM_CLIENTS_IN_QUEU_SIZE -   this is set to 3 just b/c we want to be overcareful about the queue size right now
    //          Our App can ONLY actual handle ONE client. We just have a big queue right now for safe bounds in dev

    // MAX_NUM_CLIENTS_IN_QUEU_SIZE =  3;

    // listen() is a blocking function call in idle state scheduled by the rtos ndk to awake upon a connect() initiated by the client (base station)

    listenStatus = listen(listen_handshake_socket, MAX_NUM_CLIENTS_IN_QUEU_SIZE);
    	if (listenStatus < 0) {
    	    System_printf("\n");
            System_printf("listen() failed");
            System_printf("\n");
            fdClose(listen_handshake_socket);
            Task_exit();
        return;
        }//endif

        System_printf("\n");
        System_printf("listenStatus for listen_handshake_socket after = %d", listenStatus);
        System_printf("\n");
        System_flush();

    // lets see what fdstatus has to see about our socket now

        fdStatus(listen_handshake_socket, FDSTATUS_RECV, &fd_socket_status);

        System_printf("\n");
        System_printf("fdStatus() for listen_handshake_socket after listen() = %d", fd_socket_status);
        System_printf("\n");
        System_flush();

     //reset our custom fd error flags memspace

        fd_socket_status = 111;

        System_printf("\n");
        System_printf("we are now listening to tcp connect() attempts on port 4500");
        System_printf("\n");
        System_flush();

    // If setsockop() succeeds, this function returns 0
    //			Otherwise, a value of -1 is returned and the function errno() returns the type of error

        int optionStatus = 111;

    //setsocketopt() needs US to allocate a memory space for the option AND pass it in to the fnctn args

    int optval;
    int optlen = sizeof(optval);

    // setsockop() is a runtime ti ndk config call on how the listening socket should act over time in the rtos schedule

    // SOL_SOCKET		-		at the SOCKET level, as opposed to lower layers in teh OSI/TCP heirarchy
    // SO_KEEPALIVE		-		NDK will periodically send a keep alive packet under the hood
    //			By default this sends KEEP probes every 75 seconds AFTER two hours of idle
    //			TODO change this defaultin the NDK - IP - .cfg options to a MUCH shorter idle time. pg 173 of NDK API spru524i

    // If setsockopt succeeds, this function returns 0
    //			Otherwise, a value of -1 is returned and the function errno() returns the type of error

    optionStatus = setsockopt(listen_handshake_socket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen);
    	if (optionStatus < 0) {
    	    System_printf("\n");
            System_printf("setsockopt() failed");
            System_printf("\n");
            fdClose(listen_handshake_socket);
            Task_exit();
        return;
        }//endif

        System_printf("\n");
        System_printf("optionStatus for listen_handshake_socket after set sockopt() = %d", optionStatus);
        System_printf("\n");
        System_flush();

    // lets see what fdstatus has to see about our socket now

        fdStatus(listen_handshake_socket, FDSTATUS_RECV, &fd_socket_status);

        System_printf("\n");
        System_printf("fdStatus() for listen_handshake_socket after setsockopt() = %d", fd_socket_status);
        System_printf("\n");
        System_flush();

    //reset our custom fd error flags memspace

        fd_socket_status = 111;

        System_printf("\n");
        System_printf("we are now listening to tcp connect() attempts on our port 4500, for the life of this program");
        System_printf("\n");
        System_flush();

    //	Define our Struct for Socket Address Information on the file description Environment in socket 2 of the 16 frame
    //			accept_recv_socket can inherit all the context of listen_handshake_socket as a copy
    // 			This way listen_handshake_socket stays persistent and able to re-establish accept handshake attempts
    //		    accept_recv_socket instances are decoupled from the handshake, and will now serve the client requests and logic and data streaming on the established connection

    // We just a need a new socket addr structs frame instance detail. We will copy all the heirarchy detail from listen_handshake_socket with accept()

    SOCKET accept_recv_socket;
    struct sockaddr_in accept_recv_socket_addr;
    int accept_recv_socket_addr_len = sizeof(accept_recv_socket);

    // If accept() succeeds, it returns a file descriptor (valued int) to represent the socket
    //			On success, accept_recv_socket now holds the identical file description environment information of the listen_handshake_socket
    //			in the ndk 'connected' state with the client
    //				Otherwise, a -1 value, INVALID_SOCKET is returned and the functions errno() or fdError() can be used to return the detail types of error

    accept_recv_socket = accept(listen_handshake_socket, (struct sockaddr*)&accept_recv_socket_addr, &accept_recv_socket_addr_len);
    if (accept_recv_socket < 0) {
                System_printf("\n");
                System_printf("accept() failed");
                System_printf("\n");
                fdClose(accept_recv_socket);
                fdClose(listen_handshake_socket);
                Task_exit();
            return;
            }//endif

				System_printf("\n");
				System_printf("this handle for listen_handshake_socket after One Time Test accept() = %d", listen_handshake_socket);
				System_printf("\n");
				System_printf("\n");
				System_printf("this handle for accept_recv_socket after One Time Test accept() = %d", accept_recv_socket);
				System_printf("\n");
				System_flush();

		// lets see what fdstatus has to see about our socket now

				fdStatus(listen_handshake_socket, FDSTATUS_RECV, &fd_socket_status);

                System_printf("\n");
                System_printf("fdStatus() for listen_handshake_socket after One Time Test accept() = %d", fd_socket_status);
                System_printf("\n");
                System_flush();

		//reset our custom fd error flags memspace

				fd_socket_status = 111;

				fdStatus(accept_recv_socket, FDSTATUS_RECV, &fd_socket_status);

                System_printf("\n");
                System_printf("fdStatus() for accept_recv_socket after One Time Test accept() = %d", fd_socket_status);
                System_printf("\n");
                System_flush();

		//reset our custom fd error flags memspace

				fd_socket_status = 111;

		        System_printf("\n");
		        System_printf("attempting to allocate a buffer");
		        System_printf("\n");
		        System_flush();

		 // allocate a buffer. It can only be as big as the tcp packet size, as it will get overwritten on next packet
		 // regardless of size (without overhead).
		 // TODO move each packet into a persistent RTOS API MessageQueue TASK() object. TI_config

		 char buffer[TCPPACKETSIZE] ="buffer works";

                 System_printf("\n");
                 System_printf("%s", buffer);
                 System_printf("\n");
                 System_printf("\n");
                 System_printf("we are now connected and accepted and ready to recieve tcp data stream");
                 System_printf("\n");
                 System_flush();

         // TODO comment the details NDK API function call recv()

         int num_bytes_recieved = -1;

         // recieve the data

         num_bytes_recieved = recv(accept_recv_socket, (char *)buffer, TCPPACKETSIZE, 0);

                 System_printf("\n");
                 System_printf("after recv() num_bytes_recieved = %d", num_bytes_recieved);
                 System_printf("\n");
                 System_printf("\n");
                 System_printf("the contents of the buffer = %s", buffer);
                 System_printf("\n");
                 System_flush();

         // lets see what fdstatus has to see about our socket now

                 fdStatus(accept_recv_socket, FDSTATUS_RECV, &fd_socket_status);

                 System_printf("\n");
                 System_printf("fdStatus() for accept_recv_socket after One Time Test recv() = %d", fd_socket_status);
                 System_printf("\n");
                 System_flush();

         //reset our custom fd error flags memspace

                 fd_socket_status = 111;

         // TODO comment the details NDK API function call send()

         // Echo the data back

         send(accept_recv_socket, (char *)buffer, num_bytes_recieved, 0 );

                System_printf("\n");
                System_printf("after send() num_bytes_recieved = %d", num_bytes_recieved);
                System_printf("\n");
                System_printf("\n");
                System_printf("the contents of the buffer = %s", buffer);
                System_printf("\n");
                System_flush();


         // lets see what fdstatus has to see about our socket now

                 fdStatus(accept_recv_socket, FDSTATUS_RECV, &fd_socket_status);

                 System_printf("\n");
                 System_printf("fdStatus() for accept_recv_socket after One Time Test send() = %d", fd_socket_status);
                 System_printf("\n");
                 System_flush();

         //reset our custom fd error flags memspace

                 fd_socket_status = 111;

   // We are closing down the accept_recv_socket. We now know that we have a successful tcp connection. We will repoen a new accept_recv_socket copy
   // inside our logic loop that will re-inhereit from our persistent listen_handshake_socket
   // NOW we reasonably know that any trouble in debugging is IN the loop logic, NOT the connection itself

   fdClose(accept_recv_socket);

            System_printf("\n");
            System_printf("One Time Test complete. We are closing One Time Test accept_recv_socket");
            System_printf("\n");
            System_printf("\n");
            System_printf("please reconnect for permenant connection. We are listening");
            System_printf("\n");
            System_flush();

    // accept(), recv(), send() connection forever loop

    int while_accept_count = 1;
    int while_recv_send_count = 1;
    bool connected_flag = true;

    while(true){

        accept_recv_socket = accept(listen_handshake_socket, (struct sockaddr*)&accept_recv_socket_addr, &accept_recv_socket_addr_len);

        if (accept_recv_socket < 0) {

                connected_flag = false;

                    System_printf("\n");
                    System_printf("accept() failed. We are disconnected, but still listening");
                    System_printf("\n");
                    System_printf("\n");
                    System_printf("the client should attempt to reconnect unless the end of the session");
                    System_printf("\n");
                    System_flush();

        }else{

                connected_flag = true;

                    System_printf("\n");
                    System_printf("accept() success");
                    System_printf("\n");
                    System_printf("\n");
                    System_printf("we are now connected and ready to recieve tcp data stream");
                    System_printf("\n");
                    System_flush();

        }//endif

        // lets see what fdstatus has to see about our sockets now

                    fdStatus(listen_handshake_socket, FDSTATUS_RECV, &fd_socket_status);

                    System_printf("\n");
                    System_printf("after accept() for while_accept_count = %d, fdStatus() for listen_handshake_socket = %d", while_accept_count, fd_socket_status);
                    System_printf("\n");
                    System_flush();

                    fd_socket_status = 111;

                    fdStatus(accept_recv_socket, FDSTATUS_RECV, &fd_socket_status);

                    System_printf("\n");
                    System_printf("after accept() for while_accept_count = %d, fdStatus() for accept_recv_socket = %d", while_accept_count, fd_socket_status);
                    System_printf("\n");
                    System_flush();

                    fd_socket_status = 111;

        // recieve the data loop

        // TODO add timeout logic

            while(connected_flag == true){

                num_bytes_recieved = recv(accept_recv_socket, (char *)buffer, TCPPACKETSIZE, 0);

               if(num_bytes_recieved < 0){

        // TODO if we reach this point the connection has failed lets handle this better

                   connected_flag = false;

                   System_printf("\n");
                   System_printf("recv() failed. We are disconnected, but still listening");
                   System_printf("\n");
                   System_printf("\n");
                   System_printf("the client should attempt to reconnect unless the end of the session");
                   System_printf("\n");
                   System_flush();

               }else{

        // TODO if we reach this point we have valid data

                       System_printf("\n");
                       System_printf("recv() success. We are still connected");
                       System_printf("\n");
                       System_printf("\n");
                       System_printf("after recv() for while_recv_send_count = %d", while_recv_send_count);
                       System_printf("\n");
                       System_printf("\n");
                       System_printf("num_bytes_recieved = %d", num_bytes_recieved);
                       System_printf(" and the contents of the buffer = %s", buffer);
                       System_printf("\n");
                       System_flush();

                       fdStatus(accept_recv_socket, FDSTATUS_RECV, &fd_socket_status);

                       System_printf("\n");
                       System_printf("after recv() for while_recv_send_count = %d, fdStatus() for accept_recv_socket = %d", while_recv_send_count, fd_socket_status);
                       System_printf("\n");
                       System_flush();

         //reset our custom fd error flags memspace

                       fd_socket_status = 111;


         // Echo the data back

              send(accept_recv_socket, (char *)buffer, num_bytes_recieved, 0); System_printf("\n");


               }//endif}

                    while_recv_send_count = while_recv_send_count + 1;

               // lets see what fdstatus has to see about our socket now

                         fdStatus(accept_recv_socket, FDSTATUS_RECV, &fd_socket_status);

                         System_printf("\n");
                         System_printf("after send() for while_recv_send_count = %d, fdStatus() for accept_recv_socket = %d", while_recv_send_count, fd_socket_status);

                         System_printf("fdStatus() after send() for accept_recv_socket = %d after while_recv_send_count = %d", fd_socket_status, while_recv_send_count);
                         System_printf("\n");
                         System_flush();

                   //reset our custom fd error flags memspace

                         fd_socket_status = 111;

            }//end recv() send() while

            fdClose(accept_recv_socket);

            while_accept_count = while_accept_count + 1;

    }//end accept() while

    fdClose(listen_handshake_socket);

    Task_exit();


}//endfnct rove_tcp_handler

//TODO : next feature

// TODO : fix comments on blocking -> listen(), accept(), recieve()  NETRCTRL, NETTOOLS for these three functions...
// ie how does accept change states and socket context under the hood and do the pending?



