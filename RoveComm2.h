#ifndef ROVECOMM2
#define ROVECOMM2

//#include <stdio.h>
//#include <stdint.h>
//#include <string.h>

#include <Energia.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
EthernetUDP UdpReceiver;

void roveComm_Begin(uint8_t ip_octet_1, uint8_t ip_octet_2, uint8_t ip_octet_3, uint8_t ip_octet_4);
void roveComm_SendTo(uint8_t ip_octet_1, uint8_t ip_octet_2, uint8_t ip_octet_3, uint8_t ip_octet_4, uint16_t data_id, size_t data_byte_count, const void* data)

#endif