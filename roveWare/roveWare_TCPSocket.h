// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style sockets on URC 2015 Horizon Protocol
//
// mrdt::rovWare

#ifndef ROVEWARE_TCPSOCKET_H_
#define ROVEWARE_TCPSOCKET_H_

//mrdt::rovWare Horizon Protocol Definitions
#include "roveWare_StructId_Protocol.h"

//C lib
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//CCS TI NDK BSD support
#include <sys/socket.h>
#include <arpa/inet.h>
#include <socketndk.h>

//hardcode the timeout in seconds
#define TCP_SOCKET_TIMEOUT_SEC 3

//hardcode the IP of the base station
#define RED_IP_ADDRESS "192.168.1.2"

//hardcode the TCP port
#define TCPPORT 11000

//hardcode command payload size
#define COMMAND_BYTE_CNT 4

//MRDT shorthand
#define ZERO_BYTES 0
#define SINGLE_BYTE 1

#define CONNECTED 1
#define DISCONNECTED -1

//fdOpenSession->TaskSelf -> therefore -> need to persist socket args by &
typedef struct rove_tcp_socket {

    //socket config
    int socket_fd;
    struct sockaddr_in server_addr;
    struct timeval tcp_timeout;

    //TCP overhead
    int post_recv_byte_cnt;
    int connected_flag;
    int error_code;

    //HORIZON command protocol
    char message_id;
    char struct_id;
    char command_value[COMMAND_BYTE_CNT];

}__attribute__((packed)) rove_tcp_socket, *rove_tcp_socket_ptr;

//rove ndk_socket wrappers
int roveTCP_Connect(rove_tcp_socket* rove_tcp_socket);

int roveTCP_HorizonProtocol_Recv(rove_tcp_socket* rove_tcp_socket);

int roveTCP_Recv(rove_tcp_socket* rove_tcp_socket, char* recv_buffer, int recv_buffer_byte_cnt);

void roveCatch_NdkErrors(int16_t ndk_tcp_error);

void rovePrintf_TCPCmdMsg(rove_tcp_socket* rove_tcp_socket);

#endif //ROVEWARE_TCPSOCKET_H_
