// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::rovWare

//TODO on URC 2016 OCTOBER_DEVELOPEMENT Protocol
#pragma once
#ifndef ROVECOMM_H_
#define ROVECOMM_H_

#ifdef __cplusplus
extern "C" {
#endif



// TODO Judah Factor Out Dev Shorthand
//Comms Version
//#include "roveProtocol.h"
//Public
typedef enum HorizonDriveCommands {

    DRIVE_RIGHT_MOTORS = 100
    , DRIVE_LEFT_MOTORS = 101
} HorizonDriveCommands;

//Left Over from Horizon protocol//positive is clockwise, negative is counterclockwise
typedef enum HorizonArmCommands {

    WRIST_ROTATE = 201
    , WRIST_VERTICAL = 202
    , ELBOW_ROTATE = 203
    , ELBOW_VERTICAL = 204
    , BASE_ROTATE = 205
    , E_STOP_ARM = 206
    , ACTUATOR_INCREMENT = 207
    , GRIPPER_OPEN = 208
} HorizonArmCommands;


//C lib
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//CCS TI NDK BSD support
#include <sys/socket.h>
#include <arpa/inet.h>
#include <socketndk.h>
//#include <inet/inetaddr.h>



//TODO Not sure I like to hardcode the max buffer, max subscrbr? (leave open for future dev : device synch?)
typedef enum ROVECOMM_RELEASE
{
    COMMS_VERSION_ONE = 0x01
    , COMMS_MAX_IP_SUBSCRIBERS_CNT = 1
    , COMMS_HEADER_BYTE_COUNT = 7
    , COMMS_SEQ = 0x0F0F
    , COMMS_MAX_BUFFER_BYTE_CNT = 40
    , COMMS_PORT_11000 = 11000
} ROVECOMM_RELEASE;



//why did I ip address wrapper ?? over complicating this just to bind socklen_t (and reads as board stdint_t)
// 32 bit long IP address, net order
typedef struct rove_comm_ip
{
    uint8_t     ip_family;
    uint16_t    port;
    uint32_t    address;
    uint8_t     null_term[8];
    uint32_t   address_byte_cnt;
}__attribute__((packed)) rove_comm_ip;



//udp socket config
typedef struct rovecomm_socket
{
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
typedef struct rovecomm_protocol
{
        //TODO 2016 protocol
        int32_t data_id;
        int32_t data_byte_cnt;
        uint8_t data_buffer[COMMS_MAX_BUFFER_BYTE_CNT];
        int32_t recv_byte_cnt;
        int32_t data_error;
}__attribute__((packed)) rovecomm_protocol;



int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);
int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);


#ifdef __cplusplus
}
#endif

#endif // ROVECOMM_H_





/*Todo

// ========  roveComm  ========
RoveComm::RoveComm()
{
}// end constructor

RoveComm::~RoveComm()
{
}// end destructor

int RoveComm::beginUdp(char* my_ip_addr, int port)
{
    return roveComm_InitUdpCFG(&_udp_socket, (uint8_t*)my_ip_addr, (int32_t)port);
}// end method

int RoveComm::readUdp()
{
    return roveComm_GetUdpMSG(&_udp_socket, &_udp_data);
}// end method



//#ifdef __cplusplus
//extern "C" {
//#endif
// ========  roveComm  ========
// Cplus object wrappers
class RoveComm
{
    //public:
    private:
        //pure C public API roveComm.h
        rovecomm_socket _udp_socket;
        rovecomm_protocol _udp_data;

    public:
        //Cplus extension API for Tiva Threads
        RoveComm();
        ~RoveComm();

        int beginUdp(char* my_ip_addr, int port);
        int readUdp();
        //int writeUdp(char* message);
};// end class
// ========  roveComm  ========
RoveComm::RoveComm()
{
}// end constructor
RoveComm::~RoveComm()
{
}// end destructor
int RoveComm::beginUdp(char* my_ip_addr, int port)
{
    return roveComm_InitUdpCFG(&_udp_socket, (uint8_t*)my_ip_addr, (int32_t)port);
}// end method
int RoveComm::readUdp()
{
    return roveComm_GetUdpMSG(&_udp_socket, &_udp_data);
}// end method
//#ifdef __cplusplus
//}
//#endif
*/

// ======== roveComm Future Developement:
//roveComm::beginTcp(local_ip_addr, port);
//roveComm::readTcp(remote_ip_addr, "char_message");
//roveComm::writeTcp(remote_ip_addr, "char_message");
//
//roveComm::beginHttp();
//roveComm::getHttp(remote_url, "json_message");
//roveComm::postHttp(remote_url, "json_message");
//
//roveComm::beginMqqt(broker);
//roveComm::publishMqqt("message");
//roveComm::subscribeMqqt("message");
// ========  =======  ========
