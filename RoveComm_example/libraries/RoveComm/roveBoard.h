// roveBoard.h for Tiva/Energia
// Author: Gbenga Osibodu

#ifndef ROVEBOARD_ENERGIA
#define ROVEBOARD_ENERGIA

#include <Energia.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>



typedef IPAddress roveIP;

bool roveIP::operator != (const roveIP & rhs) {return !(*this == rhs);}

void roveNetworkingStart(roveIP myIP);
void roveSocketListen(uint16_t port);
bool RoveCommSendPacket(roveIP destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize);
bool RoveCommGetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize);
roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
#endif
