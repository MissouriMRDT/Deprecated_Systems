#include "RoveComm.h"

// This function starts networking and sets up our listening port
void RoveCommClass::begin(IPAddress ip) {
  uint16_t dataID = 0, size = 0;
  uint8_t tempData[UDP_TX_PACKET_MAX_SIZE];
  
  Ethernet.begin(0, ip); //MAC Address is set by hardware
  udpReceiver.begin(ROVECOMM_PORT);
  Serial.println("Waiting for Base Station");
  while (subscriberList[0] == INADDR_NONE)
    getMsg(&dataID, &size, tempData);
  initialized = true;
}

bool RoveCommClass::sendPacket(IPAddress ip, int port, int source_port, byte* msg, uint16_t size) {
  Serial.print("Sending Msg...");
  EthernetUDP udpSender; //Create a new temporary port for sending messages. If we need verification, it's important that it doesn't interfere with the regular listening port
  if (udpSender.begin(source_port)) { 
    udpSender.beginPacket(ip,port);
      udpSender.write(msg, size);
    udpSender.endPacket();
    udpSender.stop(); //close socket
    Serial.println("Msg Sent");
    return true;
  }
  return false;
}

void RoveCommClass::sendMsgTo(uint16_t dataID, uint16_t size, void* data, IPAddress dest, int dest_port, uint8_t flags) {
  uint8_t buffer[UDP_TX_PACKET_MAX_SIZE];
  int source_port;
  //setup the packet header
  buffer[0] = VERSION_NO;
  buffer[1] = SEQ >> 8;
  buffer[2] = SEQ & 0x00FF;
  buffer[3] = flags;
  buffer[4] = dataID >> 8;
  buffer[5] = dataID & 0x00FF;
  buffer[6] = size >> 8;
  buffer[7] = size & 0x00FF;
  //copy the message into the packet
  for (int i = 0; i<size; i++) {
    buffer[i + HEADER_BYTES] = ((uint8_t*)data)[i];
  }
  
  do { //send message on an open port from this pool
  source_port = random(30000, 35000);
  } while(sendPacket(dest, dest_port, source_port, buffer, size + HEADER_BYTES));
}

void RoveCommClass::getMsg(uint16_t* dataID, uint16_t* size, void* data) {
  uint8_t receiverBuffer[UDP_TX_PACKET_MAX_SIZE];
  uint8_t flags;
  *dataID = 0;
  *size = 0;
  
  Serial.println("Checking messages");
  int packetSize = udpReceiver.parsePacket(); //check if there is a packet
  Serial.print("Packet Size: ");
  Serial.println(packetSize);
  if (packetSize > 0){ //if there is a packet
    IPAddress remote_ip = udpReceiver.remoteIP();
    int remote_port = udpReceiver.remotePort();
    Serial.print("Message from ");
    for(int i = 0; i<4; i++) {
      Serial.print(remote_ip[i]);
      if (i < 3)
        Serial.print(".");
    }
    Serial.print(":");
    Serial.println(remote_port);
    udpReceiver.read(receiverBuffer, UDP_TX_PACKET_MAX_SIZE);
    parseUdpMsg(receiverBuffer, dataID, size, data, &flags);
    if (rovecommControl(dataID, size, data, &flags, remote_ip, remote_port))
      if (initialized == true)
        getMsg(dataID, size, data);
    Serial.println();
  }
}

void RoveCommClass::parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, void* data, uint8_t* flags) {
  uint8_t proto_version = packet[0]; //get Protocol Version
  //Switch based on protocol version
  if (proto_version == 1) {
    *flags = packet[3];
    uint8_t dataIDUpper = packet[4];
    *dataID = dataIDUpper;
    *dataID = (*dataID << 8) | packet[5];
    uint8_t sizeUpper = packet[6];
    *size = sizeUpper;
    *size = (*size << 8) | packet[7];
    for( int i = 0; i<(*size); i++) {
      ((uint8_t*)data)[i] = packet[i+HEADER_BYTES];
    }
  }
}

bool RoveCommClass::rovecommControl(uint16_t* dataID, uint16_t* size, void* data, uint8_t* flags, IPAddress & remote_ip, int & remote_port) {
  if (*flags & 1 == 1) { //Acknowledge Flag: Send reply to remote port
    sendMsgTo(0x0000,0,0,remote_ip, remote_port, 0);
  }

  if (*flags & 2 == 2) {
  
  }

  if (*flags & 4 == 4) {
  
  }

  if (*flags & 8 == 8) {
  
  }

  if (*flags & 16 == 16) {
  
  }

  if (*flags & 32 == 32) {
  
  }

  if (*flags & 64 == 64) {
  
  }

  if (*flags & 128 == 128) {
  
  }

  if (*dataID < 0x65) {
    Serial.print("RoveComm function received with dataID: 0x");
    Serial.println(*dataID, HEX);
  } else return false;
  
  switch (*dataID) {
    case 1: //Add subscriber
      addSubscriber(remote_ip);
  }
  
  return true;
}

bool RoveCommClass::addSubscriber(IPAddress address) {
  int i = 0;
  Serial.println("Adding Subsrciber");
  while(i < 5 && !(subscriberList[i] == INADDR_NONE || subscriberList[i] == address))
    i++;
  if (i == 5) //If we have exceeded the subscribers array
    return false;
  subscriberList[i] = address;
  return true;
}

void RoveCommClass::sendMsg(uint16_t dataID, uint16_t size, void* data, uint8_t flags) {
  Serial.println("Sending to Basestations");
  int i=0;
  while(i<5 && !(subscriberList[i] == INADDR_NONE)) {
    sendMsgTo(dataID, size, data, subscriberList[i], ROVECOMM_PORT,flags); 
    i++;
  }
}

void RoveCommClass::sendMsg(uint16_t dataID, uint16_t size, void* data) {
  sendMsg(dataID, size, data, 0);
}

RoveCommClass RoveComm;
