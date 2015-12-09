// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// recieves base station commands using ip bsd style UDP sockets
//
// mrdt::rovWare

//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol
#ifndef ROVECOMM_H_
#define ROVECOMM_H_

//C lib
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//CCS TI NDK BSD support
#include <sys/socket.h>
#include <arpa/inet.h>
#include <socketndk.h>



//TODO Not sure I like to hardcode the port or max message size with version, header, sequence?
typedef enum RoveCommRelease {
    COMMS_VERSION_ONE = 0x01
    , COMMS_PORT_11000 = 11000
    , COMMS_HEADER_BYTE_COUNT = 7
    , COMMS_SEQ = 0x0F0F
    , COMMS_MAX_BUFF_BYTE_CNT = 40
} RoveCommRelease;



//defines base station/rovecomm packet and instruction set
typedef struct rovecomm_protocol {

        //TODO 2016 protocol
        int32_t data_id;
        int32_t data_byte_cnt;

        uint8_t data_buffer[COMMS_MAX_BUFF_BYTE_CNT];

        int32_t recv_byte_cnt;
        int32_t data_error;

}__attribute__((packed)) rovecomm_protocol, *rovcomm_protocol_ptr;



//TODO should we just typedef roveIP_HANDLE instead of local / remote
//local device
typedef struct rovecomm_local_ip {

    unsigned char  sin_family;
    unsigned short sin_port;
    struct         in_addr sin_addr;
    char           sin_zero[8];

}__attribute__((packed)) rovecomm_local_ip, *rovecomm_local_ip_ptr;



//is this a waste? just binding in_addr to socklen_t to hold remote devices/base stations subscriber
#define ROVECOMM_MAX_SUBSCRIBERS 1
typedef struct rovecomm_remote_ip {
    struct    in_addr sin_addr;
    socklen_t addr_len;
}__attribute__((packed)) rovecomm_remote_ip, *rovecomm_remote_ip_ptr;



//udp socket config
typedef struct rovecomm_socket {

    //allocate socket file descriptor
    int socket_fd;

    //allocate local rover ip address pointer
    rovecomm_local_ip* local_ip;

    //allocate max array of remote ip address subscribers
    rovecomm_remote_ip* rovecomm_ip_subscribers[ROVECOMM_MAX_SUBSCRIBERS];

    //handle network developement kit errors
    int32_t ndk_fd_error;

}__attribute__((packed)) rovecomm_socket, *rovecomm_socket_ptr;



//int32_t roveComm_Init(rovecomm_udp_socket* socket, struct in_addr *local_ip_addr,  unsigned short local_port);
int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket,  unsigned short local_port);

int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);

#endif // ROVECOMM_H_
