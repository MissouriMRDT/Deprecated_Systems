// roveBoard.h for Tiva/Energia
// Author: Gbenga Osibodu

#ifndef ROVEBOARD_ENERGIA
#define ROVEBOARD_ENERGIA

#include <Energia.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


typedef IPAddress roveIP;

void roveNetworkingStart(roveIP myIP);
void roveSocketListen(uint16_t port);
bool RoveCommSendPacket(roveIP destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize);
bool RoveCommGetUdpMsg(void* buffer);
#endif
