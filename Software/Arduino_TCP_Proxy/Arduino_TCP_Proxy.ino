#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,22);

// Enter the IP address of the server you're connecting to:
IPAddress server(192,168,1,2);
int port = 11000;

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 23 is default for telnet;
// if you're using Processing's ChatServer, use  port 10002):
EthernetClient client;

void setup() {
  // start the Ethernet connection:
  Ethernet.begin(mac, ip);
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  //Attempt connection
  while(!client.connect(server, port));
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    client.stop();
    // and reconnect
    while(!client.connect(server, port));
  }
}

