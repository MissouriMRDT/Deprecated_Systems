#ifndef ROVECOMM_HEAD
#define ROVECOMM_HEAD

#define ROVECOMM_PORT 11000
#define VERSION_NO 0x01
#define HEADER_BYTES 7
#define SEQ 0x0F0F

#include <Energia.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

//function prototypes
void rovecommInit(IPAddress ip);
void sendPacket(IPAddress ip, int port, byte* msg, uint16_t size);
void parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, void* data);
void sendMsgTo(uint16_t dataID, uint16_t size, void* data, IPAddress dest);
void getUdpMsg(uint16_t* dataID, uint16_t* size, void* data);
void parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, void* data);
void rovecommControl(uint16_t* dataID, uint16_t* size, void* data, IPAddress remote_ip, int remote_port);
bool rovecommAddSubscriber(IPAddress address);
void sendMsg(uint16_t dataID, uint16_t size, void* data);

#endif
