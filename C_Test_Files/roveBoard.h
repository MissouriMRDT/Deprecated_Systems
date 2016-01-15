// roveBoard.h for Linux
// Author: Gbenga Osibodu

#ifndef ROVEBOARD_LINUX
#define ROVEBOARD_LINUX

#include <stdint.h>
#include <netinet/in.h>
#include <stdbool.h>

typedef in_addr_t roveIP;

int roveCommSocket;
struct sockaddr_in roveCommAddr;

void roveNetworkingStart(roveIP myIP);
void roveSocketListen(uint16_t port);
bool RoveCommSendPacket(in_addr_t destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize);
bool RoveCommGetUdpMsg(roveIP IP, void* buffer);

#endif
