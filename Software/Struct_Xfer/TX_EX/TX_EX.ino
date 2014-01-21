#include "Struct_Xfer.h"
#include "Test_Structs.h"

//create connection object
Struct_Xfer CONNECTION; 

//give a name to the group of data
Foo mydata;

void setup(){
  // Star Serial Port
  Serial.begin(115200);
  
  //start the library, pass in the data details and the name of the serial port
  CONNECTION.begin(details(mydata), &Serial);
  
}

void loop(){

  mydata.x = random(5);
  mydata.y = random(5);
  
  CONNECTION.sendData();
  
  delay(1000);
}
