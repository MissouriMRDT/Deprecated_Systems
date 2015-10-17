/*

This file has some client and server functions for our devices

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define ROVECOMM_PORT 3500

//device MAC Adress
byte mac[] = {0x00, 0x1a, 0xb6, 0x02, 0xe7, 0x50};

EthernetUDP udpServer;
char serverBuffer[UDP_TX_PACKET_MAX_SIZE];

void sendMsg(IPAddress ip, int port, char* msg){
  Serial.print("Sending Msg: ");
  Serial.println(msg);
  EthernetUDP udpClient;
  while (!udpClient.begin(random(30000,35000)));
  udpClient.beginPacket(ip,port);
    udpClient.write(msg);
  udpClient.endPacket();
  udpClient.stop();
  Serial.println("Msg Sent");
}

void getAllMsg() {
  Serial.println("Checking messages");
  int packetSize = udpServer.parsePacket();
  while (packetSize){
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
    packetSize = udpServer.parsePacket();
  } 
}

void setup() {
  Serial.begin(9600);
  if (!Ethernet.begin(mac)) {
    for (;;) {
      Serial.println("Connection Failed");
      delay(1000);
    }
  }
  udpServer.begin(ROVECOMM_PORT);
}

void loop() {
  char saying[] = "Hello";
  sendMsg(IPAddress(192,168,1,102), ROVECOMM_PORT, saying);
  getAllMsg();
  delay(5000);
}
