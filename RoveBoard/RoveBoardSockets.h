// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Gbenga Osibodu
//
// Last Edit: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare

#ifndef ROVEBOARDSOCKETS_H_
#define ROVEBOARDSOCKETS_H_

#include <stdint.h>
#include <stddef.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <socketndk.h>

#define INADDR_NONE 0

typedef unsigned int roveIP;

int roveCommSocket;
struct sockaddr_in roveCommAddr;

void roveNetworkingStart(roveIP myIP);
void roveUdpSocketListen(uint16_t port);
bool RoveCommSendUdpPacket(roveIP destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize);
bool RoveCommGetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize);
roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);

#endif // ROVEBOARDSOCKETS_H_
