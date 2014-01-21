#include "Struct_Xfer.h"
#include "Test_Structs.h"

//create connection object
Struct_Xfer CONNECTION; 

//give a name to the group of data
Foo mydata;

void setup(){
  // Start Serial Port
  Serial.begin(115200);
  
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  CONNECTION.begin(details(mydata), &Serial);
  
}

void loop(){
  //check and see if a data packet has come in. 
  if(CONNECTION.receiveData()){
    char buffer[50];
    
    sprintf (buffer, "X = %d", mydata.x);
    Serial.println(buffer);
    sprintf (buffer, "Y = %d", mydata.y);
    Serial.println(buffer);
  }
  
  //you should make this delay shorter then your transmit delay or else messages could be lost
  delay(250);
}
