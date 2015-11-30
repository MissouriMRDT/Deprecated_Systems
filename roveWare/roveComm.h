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

//TODO MRDT shorthand
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

//TODO rove_tcp_socket Socket??
//fdOpenSession->TaskSelf -> therefore -> need to persist socket args by &
typedef struct rove_udp_socket {

    //socket config
    int socket_fd;
    struct sockaddr_in local_addr;
    struct sockaddr_in remote_addr;
    socklen_t          remote_addr_length;
}__attribute__((packed)) rove_udp_socket, *rove_udp_socket_ptr;

typedef struct rovecomm_protocol {

        //TODO 2016 protocol
        int32_t data_id;
        int32_t data_byte_cnt;
        uint8_t  data_buffer[COMMS_MAX_BUFF_BYTE_CNT];
}__attribute__((packed)) rove_protocol, *rove_protocol_ptr;

int32_t roveComm_Init(rove_udp_socket* rove_socket);
int32_t roveGet_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket);
int32_t roveParse_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket);




//TODO Move to HArdwareTiva Utils combine PRINTF_ERRNO and ndk_error or extend errno.h??
int32_t rovePrintf_Errno(int32_t ndk_error);
//void rovePrintf_Protocol(rove_protocol* rove_protocol);




//TODO UDP multicast overhead
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



/////////////////////////////////////////BEGIN Custom Library Distributed IP Embedded Network Handler
//class RoveComm {
/////////////////////////////////////////BEGIN Advanced Member CCS API Hooks
//    private:
        //RoveComm();
        //~RoveComm();
        //RoveComm private functions
//::END CCS API Hooks
/////////////////////////////////////////BEGIN Beginner Member Arduino Library API
       //TODO public:
       // void begin();
       // void read();
       // void write();
       //rove_udp_socket rove_comm;
//};//end class



#endif // ROVEWARE_ROVECOMM_H_
