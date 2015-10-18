/*

This file has some client and server functions for our devices

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define ROVECOMM_PORT 3500
#define VERSION_NO 0x01
#define SEQ 0x0F0F

//device MAC Adress
byte mac[] = {0x00, 0x1a, 0xb6, 0x02, 0xe7, 0x50};

EthernetUDP udpServer;
char serverBuffer[UDP_TX_PACKET_MAX_SIZE];

uint8_t ver = VERSION_NO;

void sendPacket(IPAddress ip, int port, byte* msg, uint16_t size){
  Serial.print("Sending Msg...");
  EthernetUDP udpSender;
  while (!udpSender.begin(random(30000,35000)));
  udpSender.beginPacket(ip,port);
    udpSender.write(msg, size);
  udpSender.endPacket();
  udpSender.stop();
  Serial.println("Msg Sent");
}

void sendMsgTo(uint16_t data_Id, uint8_t* data, uint16_t size, IPAddress* dest)
{
  uint8_t buffer[UDP_TX_PACKET_MAX_SIZE];
  buffer[0] = VERSION_NO;
  buffer[1] = (size + 4) >> 8;
  buffer[2] = (size + 4) & 0x00FF;
  buffer[3] = SEQ >> 8;
  buffer[4] = SEQ & 0x00FF;
  buffer[5] = data_Id >> 8;
  buffer[6] = data_Id & 0x00FF;
  for (int i = 0; i<size; i++) {
    buffer[i+7] = data[i];
  }
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
  //sendPacket(IPAddress(192,168,1,102), ROVECOMM_PORT, (char*)&ver);
  getAllMsg();
  delay(5000);
}
