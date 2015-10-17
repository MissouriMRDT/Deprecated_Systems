/*

This project multitasks a client and a server for our chip

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define ROVECOMM_PORT 3500

//device MAC Adress
byte mac[] = {0x00, 0x1a, 0xb6, 0x02, 0xe7, 0x50};

//device assigned IP address
//IPAddress ip(192,168,0,2);

void setup() {
  Serial.begin(9600);
  if (!Ethernet.begin(mac)) {
    for (;;) {
      Serial.print("Connection Failed");
      delay(1000);
    }
  }
}

void loop() {
  
}
