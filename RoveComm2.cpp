#include "RoveComm2.h"
//#include <string.h>

/////////////////////////////
// 72 Byte: RoveComm Header:
//
// 8 Byte:  Rover Id
// 8 Byte:  Board Id
// 8 Byte:  Software Flash Count
// 16 Byte: Session Count
// 32 Byte: Data Sequence Count

EthernetUDP udpReceiver;

static const uint32_t ROVECOMM_VERSION 				= 2;
static const uint32_t ROVECOMM_HEADER_BYTE_COUNT 	= 8;
static const uint32_t ROVECOMM_PORT 				= 11000;
static const uint32_t UDP_TX_PACKET_MAX_SIZE 		= 1024;

uint8_t RoveCommBuffer[UDP_TX_PACKET_MAX_SIZE];

/////////////////////////////
// RoveComm Payload:
//
// 16 Byte: Data Id
// 16 Byte: Data Byte Count
// ? Byte:  Data

static const uint32_t ROVECOMM_SUBSCRIBE    		= 0;
static const uint32_t ROVECOMM_UNSUBSCRIBE      	= 1;

static const uint32_t ROVECOMM_MAX_SUBSCRIBERS 		= 15;
static const uint32_t ROVECOMM_MAX_DATA_IDS		 	= 15;

static struct {
	
   IPAddress IpAddress;
   uint16_t DataIds[ROVECOMM_MAX_DATA_IDS];
   
} RoveCommSubscriber;

static RoveCommSubscriber RoveCommSubscribers[ROVECOMM_MAX_SUBSCRIBERS];

static RoveCommSubscriber DataSequenceCount[ROVECOMM_MAX_DATA_IDS];

void roveComm_Begin(uint8_t IP_octet1, uint8_t IP_octet2, uint8_t IP_octet3, uint8_t IP_octet4) 
{
	IPAddress IP = IPAddress(first_octet, second_octet, third_octet, fourth_octet);
  
	Ethernet.begin(0, IP);
	Ethernet.enableLinkLed();
	Ethernet.enableActivityLed();

	udpReceiver.begin(ROVECOMM_PORT);
  
	int i = 0;
	for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++) 
	{
		RoveCommSubscribers[i] = ROVE_IP_ADDR_NONE;
	}
}


