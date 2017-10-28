#include "RoveComm2.h"

/////////////////////////////
// 48 Byte: RoveComm Packet Header:
//
// 		Statically populated by RoveManifest.h
//
// 			8 Byte:  RoveComm Version Number
// 			8 Byte:  Rover Id
//
// 		Statically populated by board programmers themselves
//
// 			8 Byte:  Board Id
// 			8 Byte:  Software Flash Count
//
// 		Dynamically populated by RoveComm itself
//
// 			16 Byte: Session Count

static const uint32_t ROVECOMM_PACKET_HEADER_BYTE_COUNT = 8 + 8 + 8 + 8 + 16;

/////////////////////////////
// 64 Byte: RoveComm Data Header:
//
// 		16 Byte: Data Id
// 		32 Byte: Data Sequence Count
// 		16 Byte: Data Byte Count
static const uint32_t ROVECOMM_DATA_HEADER_BYTE_COUNT = 16 + 32 + 16;

// 		Variable (0 ~ 912) Byte:  Data 

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
static const uint32_t ROVECOMM_UNREGISTERED_BOARD_ID  								= 65532;
static const uint32_t ROVECOMM_UNREGISTERED_SOFTWARE_ID  							= 65531;

//////////////////////////////////////////////////////////////////////////

static const uint32_t ROVECOMM_VERSION 						= 2;
static const uint32_t ROVECOMM_PORT 						= 11000;
static const uint32_t ROVECOMM_MAX_SUBSCRIBERS_COUNT 		= 15;
static const uint32_t ROVECOMM_MAX_DATA_ID_COUNT		 	= 15;
static const uint32_t UDP_TRANSMIT_PACKET_MAX_BYTE_COUNT 	= 1024;
uint8_t RoveCommBuffer[UDP_TRANSMIT_PACKET_MAX_BYTE_COUNT];

static struct {
	
   IPAddress ip_address;
   uint16_t data_ids[ROVECOMM_MAX_DATA_ID_COUNT];
   
} RoveCommSubscriber;

static RoveCommSubscriber RoveCommSubscribers[ROVECOMM_MAX_SUBSCRIBERS_COUNT];
uint8_t RoveCommPacketHeader[6];
uint16_t session_count;
uint32_t data_sequence_ids[ROVECOMM_MAX_DATA_ID_COUNT];
uint32_t data_sequence_counts[ROVECOMM_MAX_DATA_ID_COUNT];

IPAddress IP_ADDRESS_NONE = IPAddress(0, 0, 0, 0);

void roveComm_Begin(uint8_t ip_octet_1, uint8_t ip_octet_2, uint8_t ip_octet_3, uint8_t ip_octet_4, uint8_t board_id, uint8_t software_flash_id)
{
	IPAddress ip_address = IPAddress(first_octet, second_octet, third_octet, fourth_octet);
	Ethernet.begin(0, ip_address);
	Ethernet.enableLinkLed();
	Ethernet.enableActivityLed();
	
	UdpReceiver.begin(ROVECOMM_PORT);
	
	RoveCommPacketHeader[0] = ROVECOMM_VERSION;
	RoveCommPacketHeader[1] = ROVER_ID;
	RoveCommPacketHeader[2] = board_id;
	RoveCommPacketHeader[3] = software_flash_id;
	
	//Pending Drue's RovePermaMem for incrementing sessions from EEProm
	session_count = 0;
	RoveCommPacketHeader[4] = session_count >> 8;
	RoveCommPacketHeader[5] = session_count & 0x00FF;
	
	// Initialize subscriber array with null ip addresses and null subscribed data id's	
	int i = 0;
	for (i=0; i < ROVECOMM_MAX_SUBSCRIBER_COUNT; i++) 
	{
		RoveCommSubscribers[i].ip_address = IP_ADDRESS_NONE;
		
		int j = 0;
		for (j=0; j < ROVECOMM_MAX_DATA_ID_COUNT; j++) 
		{
			RoveCommSubscribers[i].data_ids[j] = 0;
		}
	}
	
	int k = 0;
	for (k=0; k < ROVECOMM_MAX_DATA_ID_COUNT; k++) 
	{
		data_sequence_ids[k] = 0;
		data_sequence_counts[k] = 0;
	}
}



void roveComm_SendTo(uint8_t ip_octet_1, uint8_t ip_octet_2, uint8_t ip_octet_3, uint8_t ip_octet_4, uint16_t data_id, size_t data_byte_count, const void* data)
{
	uint32_t data_sequence_count = 0;
	int i = 0;
	for (i=0; i < ROVECOMM_MAX_DATA_ID_COUNT; i++) 
	{
		if (data_sequence_ids[i] == data_id)
		{
			data_sequence_counts[i]++;
			data_sequence_count = data_sequence_counts[i];
			
		} else {
			
			int j = 0;
			for (j=0; j < ROVECOMM_MAX_DATA_ID_COUNT; j++) 
			{
				if (data_sequence_ids[j] == 0)
				{
					data_sequence_ids[j] = data_id;
					data_sequence_counts[j] = 1;
					data_sequence_count = data_sequence_counts[j];					
			}
		}
	}
	
	size_t packet_byte_count = ROVECOMM_PACKET_HEADER_BYTE_COUNT + ROVECOMM_DATA_HEADER_BYTE_COUNT + data_byte_count;
	uint8_t packet_buffer[packet_byte_count];
	
	uint8_t RoveCommDataHeader[8];
	RoveCommDataHeader[0] = data_id >> 8;
	RoveCommDataHeader[1] = data_id & 0x00FF;	
	RoveCommDataHeader[2] = (data_sequence_count & 0xFF000000) >> 24;
	RoveCommDataHeader[3] = (data_sequence_count & 0x00FF0000) >> 16;
	RoveCommDataHeader[4] = (data_sequence_count & 0x0000FF00) >> 8;
	RoveCommDataHeader[5] = data_sequence_count & 0x00000000FF;
	RoveCommDataHeader[6] = data_byte_count >> 8;
	RoveCommDataHeader[7] = data_byte_count & 0x00FF;

	memcpy(&(packet_buffer[0]), RoveCommPacketHeader, ROVECOMM_PACKET_HEADER_BYTE_COUNT);
	memcpy(&(packet_buffer[ROVECOMM_PACKET_HEADER_BYTE_COUNT]), RoveCommDataHeader, ROVECOMM_DATA_HEADER_BYTE_COUNT);
	memcpy(&(packet_buffer[ROVECOMM_PACKET_HEADER_BYTE_COUNT + ROVECOMM_DATA_HEADER_BYTE_COUNT]), data, data_byte_count);
	
	IPAddress ip_address = IPAddress(first_octet, second_octet, third_octet, fourth_octet);
	if(ip_address == IP_ADDRESS_NONE)
	{
		int i = 0;	
		for (i=0; i < ROVECOMM_MAX_SUBSCRIBER_COUNT; i++) 
		{
			if (RoveCommSubscribers[i].ip_address != IP_ADDRESS_NONE)
			{
				int j = 0;
				for (j=0; j < ROVECOMM_MAX_DATA_ID_COUNT; j++) 
				{
					if (RoveCommSubscribers[i].data_ids[j] == data_id)
					{	
						UdpReceiver.beginPacket(RoveCommSubscribers[i].ip_address, ROVECOMM_PORT);
						UdpReceiver.write(packet_buffer, packet_byte_count);
						UdpReceiver.endPacket();
						break;
					}
				}
			}
		}
		
	} else {
		
		UdpReceiver.beginPacket(ip_address, ROVECOMM_PORT);
		UdpReceiver.write(packet_buffer, packet_byte_count);
		UdpReceiver.endPacket();	
	}
}
