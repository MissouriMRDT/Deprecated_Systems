#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

EthernetUDP udpClient;

void sendMsg(IPAddress ip, int port, char* msg){
  udpClient.begin(8889);
  udpClient.beginPacket(ip,port);
    udpClient.write(msg);
  udpClient.endPacket();
  udpClient.stop();
}

void setupClient() {
  
}

void loopClient() {
  char saying[] = "Hello";
  sendMsg(IPAddress(192,168,0,1), ROVECOMM_PORT, saying);
  delay(1000);
}
