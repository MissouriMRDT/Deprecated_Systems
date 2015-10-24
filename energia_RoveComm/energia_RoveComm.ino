/*

This file has some client and server functions for our devices

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <rovecomm.h>


//device MAC Adress
byte mac[] = {0x00, 0x1a, 0xb6, 0x02, 0xe7, 0x50};

void setup() {
  Serial.begin(9600);
  if (!Ethernet.begin(mac)) {
    for (;;) {
      Serial.println("Connection Failed");
      delay(1000);
    }
  }
  udpReceiver.begin(ROVECOMM_PORT);
}

void loop() {
  uint8_t toSend[]= { 0xaa, 0xbb, 0xcc };
  uint16_t size = sizeof(toSend);
  uint16_t dataID = 0x0AF3;
  uint8_t receivedMsg[UDP_TX_PACKET_MAX_SIZE];
  
  sendMsgTo(dataID, toSend, size, IPAddress(192,168,1,102));
  getUdpMsg(&dataID, &size, receivedMsg);
  
  Serial.print("dataID: ");
  Serial.println(dataID, HEX);
  Serial.print("size: ");
  Serial.println(size, DEC);
  Serial.print("Data Received: ");
  for( int i = 0; i<size; i++) {
    Serial.print(receivedMsg[i], HEX);
  }
  Serial.println();
  Serial.println();
  delay(5000);
}
