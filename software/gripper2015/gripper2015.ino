#include <DynamixelSerial.h>
#include <EasyTransfer.h>

EasyTransfer ETreceive;

struct RECEIVE_DATA_STRUCTURE{
  uint8_t OPEN;
  uint8_t CLOSE;
};

RECEIVE_DATA_STRUCTURE receiveData;

void setup(){
    Serial.begin(115200);
    Dynamixel.begin(115200);
    while(!Dynamixel.ping(ID));
    Dynamixel.reset(ID);
    Dynamixel.torqueStatus(1, ON);
    Dynamixel.setMaxTorque(1, 255);
    resetStruct();
    ETreceive.begin(details(receiveData), &Serial); 
}

void loop(){
  if(ETreceive.receiveData()){ 
    if(receiveData.OPEN)
      Dynamixel.turn(1, RIGTH, 255);
    if(receiveData.CLOSE)
      Dynamixel.turn(1, LEFT, 255);
    else if((receiveData.OPEN && receiveData.CLOSE) == 0)
      Dynamixel.turn(1, LEFT, 0);
    resetStruct();
  }
}

void resetStruct(){
  receiveData.OPEN = 0;
  receiveData.CLOSE = 0;
}
