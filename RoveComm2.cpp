#include "RoveComm2.h"

static const uint32_t ROVECOMM_PORT 				= 11000;
uint8_t RoveCommBuffer[UDP_TRANSMIT_PACKET_MAX_BYTE_COUNT];

/////////////////////////////
// RoveComm Payload:
//
// 16 Byte: Data Id
// 16 Byte: Data Byte Count
// ? Byte:  Data
/////////////////////////////
// 80 Byte: RoveComm Header:
//
// 		Statically populated by RoveManifest.h
//
// 			8 Byte:  RoveComm Version Number
// 			8 Byte:  Rover Id
// 			8 Byte:  Board Id
// 			8 Byte:  Software Flash Count
//
// 		Dynamically populated by RoveComm itself
//
// 			16 Byte: Session Count
// 			32 Byte: Data Sequence Count

static const uint32_t ROVECOMM_VERSION 						= 2;
static const uint32_t ROVECOMM_HEADER_BYTE_COUNT 			= 10;
static const uint32_t UDP_TRANSMIT_PACKET_MAX_BYTE_COUNT 	= 1024;

/////////////////////////////
// Reserved Data Id's
//
// 		Data Id 3~16383 (2^14) for unacked commands
// 		Data Id 16384~32767 (2^15) for acked commands
//		Data Id 32768~65535 (2^16) for system commands

static const uint32_t ROVECOMM_SUBSCRIBE    										= 0;
static const uint32_t ROVECOMM_UNSUBSCRIBE      									= 1;

static const uint32_t ROVECOMM_SUBSCRIBE_ALL_DATA	  								= 0;

static const uint32_t ROVECOMM_REQUESTED_SUBSCRIBER_IP_ADDRESS_LIMIT_EXCEEDED  		= 65535;
static const uint32_t ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_LIMIT_EXCEEDED  		= 65534;
static const uint32_t ROVECOMM_REQUESTED_SUBSCRIBER_DATA_ID_UNKNOWN  				= 65533;

//////////////////////////////////////////////////
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
	IPAddress IP_ADDRESS = IPAddress(first_octet, second_octet, third_octet, fourth_octet);
	Ethernet.begin(0, IP_ADDRESS);
	Ethernet.enableLinkLed();
	Ethernet.enableActivityLed();

	udpReceiver.begin(ROVECOMM_PORT);
	
	
  
	// Initialize subscriber array with null ip addresses and null data id's	
  	IPAddress IP_ADDRESS_NONE = IPAddress(0, 0, 0, 0);
	int i = 0;
	for (i=0; i < ROVECOMM_MAX_SUBSCRIBERS; i++) 
	{
		RoveCommSubscribers[i].IpAddress = IP_ADDRESS_NONE;
		
		int j = 0;
		for (j=0; j < ROVECOMM_MAX_DATA_IDS; j++) 
		{
			RoveCommSubscribers[i].DataIds[j] = 0;
		}
	}
}


