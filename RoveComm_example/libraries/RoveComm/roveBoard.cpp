// roveBoard.h for Tiva/Energia
// Author: Gbenga Osibodu

#include "roveBoard.h"

EthernetUDP udpReceiver;

void roveNetworkingStart(roveIP myIP) {
  Ethernet.begin(0, myIP);
}

roveIP roveSetIP(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) {
  roveIP temp = IPAddress(first_octet, second_octet, third_octet, fourth_octet);
  return temp;
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

bool RoveCommGetUdpMsg(roveIP* senderIP, void* buffer, size_t bufferSize) {
    
  int packetSize = udpReceiver.parsePacket(); 
  
  if (packetSize > 0){ //if there is a packet
    udpReceiver.read((char*)buffer, bufferSize);
    *senderIP = udpReceiver.remoteIP();
    return true;
  } else {
    return false;
  }
}

