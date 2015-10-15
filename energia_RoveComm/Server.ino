#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

EthernetUDP udpServer;
char serverBuffer[UDP_TX_PACKET_MAX_SIZE];

void setupServer() {
  udpServer.begin(ROVECOMM_PORT);
}

void loopServer() {
  int packetSize = udpServer.parsePacket();
  if (packetSize){
    IPAddress remote = udpServer.remoteIP();
    int remote_port = udpServer.remotePort();
    Serial.print("Message from ");
    for(int i = 0; i<4; i++) {
      Serial.print(remote[i]);
      if (i < 3)
        Serial.print(".");
    }
    Serial.print(":");
    Serial.println(remote_port);
    udpServer.read(serverBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println(serverBuffer);
    Serial.println();
  }
}
