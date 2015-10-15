/*

This project multitasks a client and a server for our chip

*/

#include <SPI.h>
#include <Ethernet.h>

//device MAC Adress
byte mac[] = {0xae, 0x00, 0x00, 0x00, 0x00, 0x00};

//device assigned IP address
byte ip[] = {192,168,0,1};

void setup() {
  Ethernet.begin(mac, ip);
}

void loop() {
  
}
