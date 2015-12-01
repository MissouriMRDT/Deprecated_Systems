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

//TODO REED?? MRDT shorthand
enum RoveCommShortHand {

    COMMS_ZERO_BYTES = 0x00
    , COMMS_SINGLE_BYTE = 0x01
    , COMMS_ERROR = -1
    , COMMS_ERROR_FREE = 1
    , COMMS_NDK_DEFAULTS_FLAG = 0
};//end enum

//hardcode the local device ip address
enum RoveCommRelease {

    COMMS_VERSION_ONE = 0x01
    , COMMS_PORT_11000 = 11000
    , COMMS_HEADER_BYTE_COUNT = 7
    , COMMS_SEQ = 0x0F0F
    , COMMS_MAX_BUFF_BYTE_CNT = 40
};//end enum

//TODO errno codes
enum RoveCommErrNo {

    COMMS_PARSE_UDP_ERRNO = 0x01
    , COMMS_PRINTF_NDK_ERRNO = 0x02
};//end enum

//fdOpenSession->TaskSelf -> therefore -> need to persist socket args by &
typedef struct rove_udp_socket {

    //socket config
    int socket_fd;
    struct sockaddr_in local_addr;
    struct sockaddr_in remote_addr;
    socklen_t          remote_addr_length;
    int32_t fd_error;
}__attribute__((packed)) rove_udp_socket, *rove_udp_socket_ptr;

typedef struct rovecomm_protocol {

        //TODO 2016 protocol
        int32_t data_id;
        int32_t data_byte_cnt;
        uint8_t  data_buffer[COMMS_MAX_BUFF_BYTE_CNT];
}__attribute__((packed)) rove_protocol, *rove_protocol_ptr;

int32_t roveComm_Init(rove_udp_socket* rove_socket);

int32_t roveGet_UdpMsg(

        rove_protocol* rove_data
        , rove_udp_socket* rove_socket
);//end fnctn

int32_t roveParse_UdpMsg(

        rove_protocol* rove_data
        , rove_udp_socket* rove_socket
);//end fnctn

int32_t roveCatch_NdkErrno(int32_t ndk_error);

#endif // ROVEWARE_ROVECOMM_H_
