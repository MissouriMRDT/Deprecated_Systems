#ifndef ROVECOMM
#define ROVECOMM

#define ROVECOMM_PORT 3500
#define VERSION_NO 0x01
#define HEADER_BYTES 7
#define SEQ 0x0F0F

EthernetUDP udpReceiver;
uint8_t receiverBuffer[UDP_TX_PACKET_MAX_SIZE];

void rovecommInit(byte mac[]);
void sendPacket(IPAddress ip, int port, byte* msg, uint16_t size);
void parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, uint16_t* data);
void sendMsgTo(uint16_t dataId, uint8_t* data, uint16_t size, IPAddress dest);
void getUdpMsg(uint16_t* dataID, uint16_t* size, uint8_t* data);
void parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, uint8_t* data);

#include <rovecomm.hpp>

#endif
