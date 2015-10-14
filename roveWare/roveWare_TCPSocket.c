// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style sockets on URC 2015 Horizon Protocol
//
// mrdt::rovWare

#include "roveWare_TCPSocket.h"

int roveTCP_Connect(rove_tcp_socket* rove_tcp_socket) {

    rove_tcp_socket->socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //flag for bad socket

    if ( (rove_tcp_socket->socket_fd) < 1) {

        printf("Failed socket() with socket_fd: %d \n\n" , rove_tcp_socket->socket_fd);

        roveCatch_NdkErrors( fdError() );

        return DISCONNECTED;

    }//endif

    //init bsd socket config struct

    memset(&rove_tcp_socket->server_addr, 0, sizeof(struct sockaddr_in));

    //config the socket
    rove_tcp_socket->server_addr.sin_family = AF_INET;
    rove_tcp_socket->server_addr.sin_port = htons(TCPPORT);
    inet_pton(AF_INET, RED_IP_ADDRESS, &(rove_tcp_socket->server_addr.sin_addr));

    //set a timeout on the socket
    rove_tcp_socket->tcp_timeout.tv_sec = TCP_SOCKET_TIMEOUT_SEC;
    rove_tcp_socket->tcp_timeout.tv_usec = 0;
    setsockopt(rove_tcp_socket->socket_fd, SOL_SOCKET, SO_RCVTIMEO, &(rove_tcp_socket->tcp_timeout), sizeof(struct timeval) );

    //connect the socket
    if (connect(rove_tcp_socket->socket_fd, (PSA) &(rove_tcp_socket->server_addr), sizeof(struct sockaddr_in)) < 0) {

        printf("Failed connect() with socket_fd: %d \n\n" , rove_tcp_socket->socket_fd);

        roveCatch_NdkErrors( fdError() );

        return DISCONNECTED;

    } else {

        return CONNECTED;

    }//endif

}//endfnctn

int roveTCP_Recv(rove_tcp_socket* rove_tcp_socket, char* recv_buffer, int recv_byte_cnt) {

    if (rove_tcp_socket->connected_flag == CONNECTED) {

        //TODO
        recv_byte_cnt = recv(rove_tcp_socket->socket_fd, recv_buffer, recv_byte_cnt, MSG_WAITALL);

        if (recv_byte_cnt < ZERO_BYTES) {

            rove_tcp_socket->error_code = fdError();
            roveCatch_NdkErrors(rove_tcp_socket->error_code);

            printf("RETURN roveHorizon_Recv : Failed roveTCP_Recv(message_id) with socket_fd: %d \n\n" , rove_tcp_socket->message_id);

            return DISCONNECTED;

        }//endif

        return recv_byte_cnt;

    }//endif

    return DISCONNECTED;

}//endfnctn roveTCP_Connect


void roveCatch_NdkErrors(int16_t ndk_tcp_error) {

    switch(ndk_tcp_error) {

        case ENOMEM:
            printf("NDK cannot allocate memory ENOMEM %d\n\n", ndk_tcp_error);
            break;

        case ETIMEDOUT:
            printf("NDK operation timed out ETIMEDOUT %d\n\n", ndk_tcp_error);
            break;

        case ECONNREFUSED:
            printf("NDK connection refused ECONNREFUSED %d\n\n", ndk_tcp_error);
            break;

        case EHOSTDOWN:
            printf("NDK connection refused EHOSTDOWN %d\n\n", ndk_tcp_error);
            break;

        default:
            printf("NDK unknown error %d\n\n", ndk_tcp_error);
            break;

    } //endswitch

    return;

}//endfnctn roveCatch_NdkErrors


void rovePrintf_TCP_CmdMsg(rove_tcp_socket* rove_tcp_socket) {

    switch(rove_tcp_socket->struct_id){

    case motor_drive_right_id:

        printf("Rover Drive Right : struct_id %d : speed %d\n",rove_tcp_socket->struct_id, rove_tcp_socket->command_value);

        break;

    case motor_drive_left_id:

        printf("Rover Drive Left : struct_id %d : speed %d\n",rove_tcp_socket->struct_id, rove_tcp_socket->command_value);

        break;

    default:

        printf("Unknown Command Error");

        break;

    }//endswitch

    printf("Bytes Recieved: post_recv_byte_cnt %d :\n", rove_tcp_socket->post_recv_byte_cnt);

    printf("Socket State: connected_flag %d : error_code %d\n",rove_tcp_socket->connected_flag, rove_tcp_socket->error_code);

        return;

}//endfnctn rovePrintf_RoveStructs

