// This function starts networking and sets up our listening port
void rovecommInit(byte mac[], IPAddress ip) {
  uint16_t dataID = 0, size = 0;
  uint8_t tempData[UDP_TX_PACKET_MAX_SIZE];
  
  Ethernet.begin(mac, ip);
  udpReceiver.begin(ROVECOMM_PORT);
  Serial.println("Waiting for Base Station");
  while (rovecommSubscribers[0] == INADDR_NONE)
    getUdpMsg(&dataID, &size, tempData);
}

void sendPacket(IPAddress ip, int port, byte* msg, uint16_t size) {
  Serial.print("Sending Msg...");
  EthernetUDP udpSender; //Create a new temporary port for sending messages. If we need verification, it's important that it doesn't interfere with the regular listening port
  while (!udpSender.begin(random(30000,35000))); //keep trying to open a port on a socket until it gets one
  udpSender.beginPacket(ip,port);
    udpSender.write(msg, size);
  udpSender.endPacket();
  udpSender.stop(); //close socket
  Serial.println("Msg Sent");
}

void sendMsgTo(uint16_t dataID, uint16_t size, void* data, IPAddress dest) {
  uint8_t buffer[UDP_TX_PACKET_MAX_SIZE];

  //setup the packet header
  buffer[0] = VERSION_NO;
  buffer[1] = SEQ >> 8;
  buffer[2] = SEQ & 0x00FF;
  buffer[3] = dataID >> 8;
  buffer[4] = dataID & 0x00FF;
  buffer[5] = (size) >> 8;
  buffer[6] = (size) & 0x00FF;
  //copy the message into the packet
  for (int i = 0; i<size; i++) {
    buffer[i + HEADER_BYTES] = ((uint8_t*)data)[i];
  }
  sendPacket(dest, ROVECOMM_PORT, buffer, size + HEADER_BYTES);
}

void getUdpMsg(uint16_t* dataID, uint16_t* size, void* data) {
  uint8_t receiverBuffer[UDP_TX_PACKET_MAX_SIZE];
  
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
    parseUdpMsg(receiverBuffer, dataID, size, data);
    if (*dataID < 0x65) {
      Serial.print("RoveComm function received with dataID: ");
      Serial.println(*dataID, HEX);
      if (rovecommSubscribers[0] == INADDR_NONE) { //if this is running during rovecommInit();
        rovecommControl(dataID, size, data, remote_ip, remote_port);
      } else {
        rovecommControl(dataID, size, data, remote_ip, remote_port);
        getUdpMsg(dataID, size, data);
      }
    }
    Serial.println();
  }
}

void parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, void* data) {
  uint8_t proto_version = packet[0]; //get Protocol Version
  //Switch based on protocol version
  if (proto_version == 1) {
    uint8_t dataIDUpper = packet[3];
    *dataID = dataIDUpper;
    *dataID = (*dataID << 8) | packet[4];
    uint8_t sizeUpper = packet[5];
    *size = sizeUpper;
    *size = (*size << 8) | packet[6];
    for( int i = 0; i<(*size); i++) {
      ((uint8_t*)data)[i] = packet[i+HEADER_BYTES];
    }
  }
}

void rovecommControl(uint16_t* dataID, uint16_t* size, void* data, IPAddress remote_ip, int remote_port) {
  switch (*dataID) {
    case 1: //Add subscriber
      rovecommAddSubscriber(remote_ip);
  }
}

bool rovecommAddSubscriber(IPAddress address) {
  int i = 0;
  Serial.println("Adding Subsrciber");
  while(i < 5 && !(rovecommSubscribers[i] == INADDR_NONE || rovecommSubscribers[i] == address))
    i++;
  if (i == 5) //If we have exceeded the subscribers array
    return false;
  rovecommSubscribers[i] = address;
  return true;
}

void sendMsg(uint16_t dataID, uint16_t size, void* data) {
  Serial.println("Sending to Basestations");
  int i=0;
  while(i<5 && !(rovecommSubscribers[i] == INADDR_NONE)) {
    sendMsgTo(dataID, size, data, rovecommSubscribers[i]); 
    i++;
  }
}
