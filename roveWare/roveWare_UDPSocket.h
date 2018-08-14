// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_UDPSocket.c
//
// jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style UDP sockets
//
// mrdt::rovWare
//
//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol

#ifndef ROVEWARE_UDPSOCKET_H_
#define ROVEWARE_UDPSOCKET_H_

//mrdt::rovWare Horizon Protocol Definitions
#include "roveWare_Protocol.h"

//C lib
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//CCS TI NDK BSD support
#include <sys/socket.h>
#include <arpa/inet.h>
#include <socketndk.h>

//hardcode the local device ip address
#define LOCAL_IP_ADDRESS "192.168.1.2"

//#define ROVECOMM_PORT 11000
//#define VERSION_NO 0x01
#define VERSION_ONE 1
#define LISTEN_PORT 11000
#define HEADER_BYTE_COUNT 7
#define SEQ 0x0F0F

//hardcode socket capability payload size
#define MAX_SUBSCRIBER_CNT 5
#define MAX_DATA_BYTE_CNT 40

//MRDT shorthand
#define ZERO_BYTES 0
#define SINGLE_BYTE 1

#define SUCCESS 1
#define ERROR_FREE 1
#define ERROR -1

#define DEFAULT_FLAG 0

//fdOpenSession->TaskSelf -> therefore -> need to persist socket args by &
typedef struct rove_udp_socket {

    //socket config
    int socket_fd;
    struct sockaddr_in local_addr;
    struct sockaddr_in remote_addr;
    socklen_t          remote_addr_length;

    //2016 command protocol
    uint16_t data_id;
    uint16_t data_byte_cnt;
    uint8_t  data_buffer[MAX_DATA_BYTE_CNT];

}__attribute__((packed)) rove_udp_socket, *rove_udp_socket_ptr;

//function prototypes
uint16_t getUdpMsg(uint16_t* data_id, uint16_t* data_byte_cnt, rove_udp_socket* rove_socket);

void parseUdpMsg(uint8_t* recv_buffer, uint16_t* data_id, uint16_t* data_byte_cnt, rove_udp_socket* rove_socket);

void rovecommInit(uint32_t port, rove_udp_socket* rove_socket);

void roveCatch_NdkErrors(int16_t ndk_error);

void rovePrintf_IPMessage(rove_udp_socket* rove_socket);

//UDP multicast overhead

//remote subscribers[MAX_SUBSCRIBER_CNT];

//subscribe to remote ip addresses
//typedef struct remote {
//
//    struct sockaddr_in remote_addr;
//    socklen_t          remote_addr_length;
//
//} __attribute__((packed)) remote, *remote_ptr;

//bool rovecommAddSubscriber(IPAddress address);

//void rovecommControl(uint16_t* dataID, uint16_t* size, void* data, IPAddress remote_ip, int remote_port);

#endif // ROVEWARE_UDPSOCKET_H_
