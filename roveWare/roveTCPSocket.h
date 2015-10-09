// Missouri Science and Technology Mars Rover Design Team 2015
//
// Judah Schad jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style sockets on URC 2015 Horizon Protocol
//
// mrdt::rovWare

#ifndef ROVETCPSOCKET_H_
#define ROVETCPSOCKET_H_

#include "roveWare_tivaWrappers.h"

//C lib
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

//CCS TI config
#include <xdc/std.h>

#include <xdc/cfg/global.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

//CCS TI operating system
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

//CCS TI NDK BSD support
#include <sys/socket.h>

#include <arpa/inet.h>

//hardcode the timeout in seconds
#define TCP_SOCKET_TIMEOUT_SEC 3

//hardcode the IP of the base station
#define RED_IP_ADDRESS "192.168.1.2"

//hardcode the TCP port
#define TCPPORT 11000

//MRDT shorthand
#define FOREVER 1

#define ZERO_BYTES 0
#define SINGLE_BYTE 1

#define CONNECTED 1
#define DISCONNECTED 0

#define CONNECTED_SOCKET 1
#define DISCONNECTED_SOCKET -1

#define STRUCTID_BYTECNT_ERR 1

//fdOpenSession->TaskSelf
//
//therefore persist socket args by &
typedef struct rove_tcp_socket {

    //socket handle
    int socket_fd;

    //socket config
    struct sockaddr_in server_addr;
    struct timeval tcp_timeout;

    //socket state
    int16_t connected_flag;
    int16_t error_code;

    //TODO dbg
    int16_t dbg_recv_cnt;

} rove_tcp_socket;

//Working set
typedef struct message_cfg {

    //Horizon 2015 protocol
    char message_id;
    char struct_id;

    int16_t to_recv_byte_cnt;
    int16_t post_recv_byte_cnt;

} message_cfg;

//hardcode the working buffer limit
#define MAX_CMD_BYTE_CNT 40

//rove ndk_socket wrappers
int16_t roveTCP_Connect(rove_tcp_socket* rove_tcp_socket);

int16_t roveHorizon_Recv(rove_tcp_socket* rove_tcp_socket, message_cfg* recv_cfg, char* recv_buffer);

int16_t roveTCP_Recv(rove_tcp_socket* rove_tcp_socket, char* recv_buffer, int16_t recv_byte_cnt);

void roveCatch_NdkErrors(int16_t ndk_tcp_error);

void rovePrintf_MessageCfg(message_cfg* message_cfg);

void rovePrintf_RoveTCPSocket(rove_tcp_socket* rove_tcp_socket );

/*?
extern int    fdStatus( SOCKET s, int request, int *results );
#define FDSTATUS_TYPE           0   // get socket type
#define FDSTATUS_TYPE_SOCKET    1
#define FDSTATUS_TYPE_PIPE      2
#define FDSTATUS_RECV           1   // get socket rcv status
#define FDSTATUS_SEND           2   // get socket snd status
*/

#endif /* ROVETCPSOCKET_H_ */
