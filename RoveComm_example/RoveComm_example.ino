/*
This is an example use of the RoveComm Library
*/

//These three libraries are required for RoveComm to function
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

//Include Rovecomm itself
#include "RoveEthernet.h"
#include <RoveComm.h>

//Including stuff for this example
#include <string.h>

//You can send any kind of data, even structs
//Be prepared to receive various kinds of data as well
struct Rover {
  char name[16];            //The name of our Rover
  int competitionYear;      //What year it signed up for competition
  bool isActive;            //True if the Rover still runs
  
  Rover(){                  //Default Constructor
    memset(name, 0, 16);
    strcpy(name,"N/A");
    competitionYear=0;
    isActive=false;
  }
  
  //Constructor for known Rover
  Rover(char* n, int y, bool b):competitionYear(y),isActive(b){
    memset(name, 0, 16);
    strcpy(name,n);
  }
  
  //Prints Rover to Serial
  void printout(){
    Serial.print("Hi, I'm ");
    Serial.print(name);
    Serial.print(" and I was made for the ");
    Serial.print(competitionYear);
    Serial.println(" Mars Rover competition\n");
  }
};


void setup() {
  
  //Start serial for debugging
  Serial.begin(9600);
  
  //Setup and Start communications
  //this function waits for a basestation to connect before it
  // returns. For testing you can use the Udp Client in the C
  // folder to simulate it.
  RoveCommBegin(192,168,1,52);
}

void loop() {
  //Set Variables for a packet to send
  Rover toSend("Horizon", 2015, true);
  unsigned int size = sizeof(toSend);
  short unsigned int dataID = 1569;
  
  //A place to store data that was received
  byte receivedMsg[100];
  
  //send a message to the test server
  //RoveCommSendMsg(dataID, size, &toSend);
  RoveCommSendMsg(0x0300, 4, "cat\0");
  //get a reply from the test server
  RoveCommGetMsg(&dataID, &size, receivedMsg);
  
  if (dataID) {
  //Print the bytes of the received Data
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
  }
  //Act on the received data based on the dataID
  switch (dataID) {
    //If a Rover was received
    case 1569: //0x0621
      Serial.println("This is a Rover");
      ((Rover*)receivedMsg) -> printout();
      break;
      
    //If a character array was received
    case 180: // 0xB4
      Serial.println("This is just a text message");
      Serial.println((char*)receivedMsg);
      break;
  }
  delay(5000);
}
