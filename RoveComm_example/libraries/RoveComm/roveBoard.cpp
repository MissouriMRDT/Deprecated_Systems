// roveBoard.h for Tiva/Energia
// Author: Gbenga Osibodu

#include "roveBoard.h"

EthernetUDP udpReceiver;

void roveNetworkingStart(roveIP myIP) {
  Ethernet.begin(0, myIP);
}

void roveSocketListen(uint16_t port) {
  udpReceiver.begin(port);
}

bool RoveCommSendPacket(roveIP destIP, uint16_t destPort, const uint8_t* const msg, size_t msgSize) {
  udpReceiver.beginPacket(destIP, destPort);
  udpReceiver.write(msg, msgSize);
  udpReceiver.endPacket();
  return true;
}

bool RoveCommGetUdpMsg(void* buffer) {
    
  int packetSize = udpReceiver.parsePacket(); 
  
  if (packetSize > 0){ //if there is a packet
    udpReceiver.read((char*)buffer, UDP_TX_PACKET_MAX_SIZE);
    
    return true;
  } else {
    return false;
  }
}

