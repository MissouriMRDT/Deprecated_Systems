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

        rove_tcp_socket->connected_flag = DISCONNECTED;

        return DISCONNECTED_SOCKET;

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

        rove_tcp_socket->connected_flag = DISCONNECTED;

        return DISCONNECTED_SOCKET;

    } else {

        rove_tcp_socket->connected_flag = CONNECTED;

        return CONNECTED_SOCKET;

    }//endif

}//endfnctn

int roveTCP_Recv(rove_tcp_socket* rove_tcp_socket, char* recv_buffer, int recv_byte_cnt) {

    if (rove_tcp_socket->connected_flag == CONNECTED) {

        recv_byte_cnt = recv(rove_tcp_socket->socket_fd, recv_buffer, recv_byte_cnt, MSG_WAITALL);

        if (recv_byte_cnt < 0) {

            rove_tcp_socket->connected_flag = DISCONNECTED;
            return DISCONNECTED_SOCKET;

        }//endif

        return recv_byte_cnt;

    }//endif

    return DISCONNECTED_SOCKET;

}//endfnctn roveTCP_Connect

int roveHorizon_Recv(rove_tcp_socket* rove_tcp_socket, message_cfg* recv_cfg, char* recv_buffer) {

    if( (roveTCP_Recv(rove_tcp_socket, &(recv_cfg->message_id), SINGLE_BYTE)) < ZERO_BYTES) {

        rove_tcp_socket->error_code = fdError();
        roveCatch_NdkErrors(rove_tcp_socket->error_code);

        printf("RETURN roveHorizon_Recv : Failed roveTCP_Recv(message_id) with socket_fd: %d \n\n" , recv_cfg->message_id);
        rove_tcp_socket->connected_flag = DISCONNECTED;

        return DISCONNECTED_SOCKET;

    }//endif

    if( (roveTCP_Recv(rove_tcp_socket, &(recv_cfg->struct_id), SINGLE_BYTE) ) < ZERO_BYTES){

        rove_tcp_socket->error_code = fdError();
        roveCatch_NdkErrors(rove_tcp_socket->error_code);

        printf("RETURN roveHorizon_Recv : Failed roveTCP_Recv(struct_id) with socket_fd: %d \n\n" , rove_tcp_socket->socket_fd);

        rove_tcp_socket->connected_flag = DISCONNECTED;
        return DISCONNECTED_SOCKET;

    }//endif

    //get the byte count for the message (- SINGLE_BYTE work around for old command protocol)
    recv_cfg->to_recv_byte_cnt = roveGetStructId_ByteCnt(recv_cfg->struct_id) - SINGLE_BYTE;

    if( recv_cfg->to_recv_byte_cnt < 0 ) {

        printf("RETURN roveHorizon_Recv :  Failed roveGetStructId_ByteCnt returned only : %d for struct_id %d\n\\n", recv_cfg->to_recv_byte_cnt, recv_cfg->struct_id );

        return STRUCTID_BYTECNT_ERR;

    }else{

        //recv_buffer[0] workaround for old command protocol
        recv_buffer[0] = recv_cfg->struct_id;

        //get the message vaue payload using Horizon Protocol recv_buffer[1] workaround for old command protocol
        recv_cfg->post_recv_byte_cnt = roveTCP_Recv(rove_tcp_socket, &(recv_buffer[1]), recv_cfg->to_recv_byte_cnt);

        if( recv_cfg->post_recv_byte_cnt < ZERO_BYTES ) {

            rove_tcp_socket->error_code = fdError();
            roveCatch_NdkErrors(rove_tcp_socket->error_code);

            printf("RETURN roveHorizon_Recv : Failed recv_buffer for roveRecv() count was: %d\n", recv_cfg->post_recv_byte_cnt);

            rove_tcp_socket->connected_flag = DISCONNECTED;
            return DISCONNECTED_SOCKET;

        }//endif

        //TODO
        printf("FINISH roveHorizon_Recv\n");
        rovePrintf_RoveStructs(recv_buffer, recv_cfg->struct_id );

        return recv_cfg->to_recv_byte_cnt;

    }//endelse

} //endfnctn

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

void rovePrintf_MessageCfg(message_cfg* message_cfg) {

    printf("message_id : %d struct_id : %d to_recv_byte_cnt : %d", message_cfg->message_id, message_cfg->struct_id, message_cfg->to_recv_byte_cnt );

    printf("post_recv_byte_cnt : %d\n\n", message_cfg->post_recv_byte_cnt);

}//end fnctn void rovePrintf_MessageCfg

void rovePrintf_RoveTCPSocket(rove_tcp_socket* rove_tcp_socket ) {

    /*TODO how to access human readable printf IP address and PORT
    char temp_ntop_buffer[ sizeof(struct in_addr) ];

    inet_ntop(AF_INET, (void*)&(rove_tcp_socket->server_addr.sin_addr), temp_ntop_buffer, sizeof(struct in_addr) );

    printf("socket_fd : %d\n\n", rove_tcp_socket->socket_fd );

    printf("sin_addr : ");

    rovePrintf_ByteBuffer(temp_ntop_buffer, sizeof(struct in_addr) );

    printf("sin_port : %d\n\n tcp_timeout : %d\n\n", rove_tcp_socket->server_addr.sin_port, rove_tcp_socket->tcp_timeout );
*/
    printf("connected_flag : %d error_code : %d roveRecv Count : %d\n\n", rove_tcp_socket->connected_flag, rove_tcp_socket->error_code, rove_tcp_socket->dbg_recv_cnt);

}//end fnctn void rovePrintf_RoveTCPSocket
