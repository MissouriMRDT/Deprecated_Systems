// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// mrdt::rovWare

#pragma once
#ifndef ROVECOMM_HPP
#define ROVECOMM_HPP
/*
#ifdef __cplusplus
extern "C" {
#endif

#include "RoveComm.h"

//C lib
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//CCS TI NDK BSD support
#include <sys/socket.h>
#include <arpa/inet.h>
#include <socketndk.h>
//#include <inet/inetaddr.h>

/*
// ========  roveComm  ========
// Cplus object wrappers
class RoveCommClass
{
    public:
        RoveCommClass();
        ~RoveCommClass();

        void begin();
        void read(uint16_t* dataID, size_t* size, char* data);
        void write(uint16_t dataID, size_t size, const char* const data);
};// end class

//extern void RoveCommBegin();
//extern void RoveCommGetMsg(uint16_t* dataID, size_t* size, void* data);
//extern void RoveCommSendMsg(uint16_t dataID, size_t size, const void* const data);


// ========  roveComm  ========
RoveCommClass::RoveCommClass()
{
}// end constructor

RoveCommClass::~RoveCommClass()
{
}// end destructor

void RoveCommClass::begin()
{
    RoveCommBegin();
}// end method

void RoveCommClass::read(uint16_t* dataID, size_t* size, char* data)
{
    RoveCommGetMsg(dataID, size, data);
}// end method

void RoveCommClass::write(uint16_t dataID, size_t size, const char* const data)
{
    RoveCommSendMsg(dataID, size, data);
}// end method

*/
#ifdef __cplusplus
}
#endif

#endif // ROVECOMM_H_

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
