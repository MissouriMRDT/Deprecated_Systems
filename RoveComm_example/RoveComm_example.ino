/*

This file has some client and server functions for our devices

*/

//These three includes are required for RoveComm
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

//Include Rovecomm itself
#include <rovecomm.h>


//Including stuff for this example, could be anywhere above
#include <string.h>

struct Rover {
  char name[16];
  int competitionYear;
  bool isActive;
  
  Rover(){strcpy(name,"N/A"); competitionYear=0; isActive=false;}
  Rover(char* n, int y, bool b):competitionYear(y),isActive(b){
    memset(&name, 0, 16);
    strcpy(name,n);
  }
  
  void printout(){
    Serial.print("Hi, I'm ");
    Serial.print(name);
    Serial.print(" and I was made for the ");
    Serial.print(competitionYear);
    Serial.println(" Mars Rover competition\n");
  }
};

void setup() {
  //define device MAC Address and IP for networking
  byte deviceMAC[] = {0x00, 0x1A, 0xB6, 0x02, 0xF0, 0xDF};
  IPAddress deviceIP(192,168,1,51);
  
  //Start serial for debugging
  Serial.begin(9600);
  
  //Setup and Start communications 
  rovecommInit(deviceMAC, deviceIP);
}

void loop() {
  Rover toSend("Horizon", 2015, true);
  short unsigned int size = sizeof(toSend);
  short unsigned int dataID = 1569;
  byte receivedMsg[100];
  
  //send a message to the test server
  sendMsg(dataID, &toSend, size);
  //get a reply from the test server
  getUdpMsg(&dataID, &size, receivedMsg);
  
  //Print our reply
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
  
  switch (dataID) {
    case 1569: //0x0621
      Serial.println("This is a Rover");
      ((Rover*)receivedMsg) -> printout();
      break;
    case 0x0300: // 768 in Decimal
      Serial.println("This is just a text message");
      Serial.println((char*)receivedMsg);
      break;
  }
  delay(1000);
}
