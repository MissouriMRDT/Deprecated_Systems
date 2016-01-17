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
void roveUdpSocketListen(uint16_t port);
bool RoveCommSendUdpPacket(roveIP destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize);
bool RoveCommGetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize);
roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);

#endif
