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
//#include <inet/inetaddr.h> wtf implicit

//TODO Not sure I like to hardcode the max buffer, max subscrbr? (leave open for future dev : device synch?)
typedef enum ROVECOMM_RELEASE {

    COMMS_VERSION_ONE = 0x01

    //TODO
    , COMMS_MAX_IP_SUBSCRIBERS_CNT = 1

    , COMMS_HEADER_BYTE_COUNT = 7
    , COMMS_SEQ = 0x0F0F

    , COMMS_MAX_BUFFER_BYTE_CNT = 40
    , COMMS_PORT_11000 = 11000

} ROVECOMM_RELEASE;


//why did I ip address wrapper ?? over complicating this just to bind socklen_t (and reads as board stdint_t)

// 32 bit long IP address, net order
typedef struct rove_comm_ip {

    uint8_t     ip_family;
    uint16_t    port;
    uint32_t    address;
    uint8_t     null_term[8];

    uint32_t   address_byte_cnt;

}__attribute__((packed)) rove_comm_ip;



//udp socket config
typedef struct rovecomm_socket {

    //allocate socket file descriptor
    int socket_fd;

    //allocate local rover ip address pointer
    rove_comm_ip local_ip;

    //allocate max array of remote ip address subscribers
    rove_comm_ip ip_subscribers[COMMS_MAX_IP_SUBSCRIBERS_CNT];

    //handle network developement kit errors
    int32_t ndk_fd_error;

}__attribute__((packed)) rovecomm_socket;



//defines base station/rovecomm packet and instruction set
typedef struct rovecomm_protocol {

        //TODO 2016 protocol
        int32_t data_id;
        int32_t data_byte_cnt;

        uint8_t data_buffer[COMMS_MAX_BUFFER_BYTE_CNT];

        int32_t recv_byte_cnt;
        int32_t data_error;

}__attribute__((packed)) rovecomm_protocol;



int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);

int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);

#endif // ROVECOMM_H_
