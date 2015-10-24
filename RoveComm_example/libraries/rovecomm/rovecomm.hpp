void rovecommInit(byte mac[]){
  if (!Ethernet.begin(mac)) {
    for (;;) {
      Serial.println("Connection Failed");
      delay(1000);
    }
  }
  udpReceiver.begin(ROVECOMM_PORT);
}

void sendPacket(IPAddress ip, int port, byte* msg, uint16_t size){
  Serial.print("Sending Msg...");
  EthernetUDP udpSender;
  while (!udpSender.begin(random(30000,35000)));
  udpSender.beginPacket(ip,port);
    udpSender.write(msg, size);
  udpSender.endPacket();
  udpSender.stop();
  Serial.println("Msg Sent");
}

void sendMsgTo(uint16_t dataId, uint8_t* data, uint16_t size, IPAddress dest)
{
  uint8_t buffer[UDP_TX_PACKET_MAX_SIZE];
  buffer[0] = VERSION_NO;
  buffer[1] = SEQ >> 8;
  buffer[2] = SEQ & 0x00FF;
  buffer[3] = dataId >> 8;
  buffer[4] = dataId & 0x00FF;
  buffer[5] = (size) >> 8;
  buffer[6] = (size) & 0x00FF;
  for (int i = 0; i<size; i++) {
    buffer[i + HEADER_BYTES] = data[i];
  }
  sendPacket(dest, ROVECOMM_PORT, buffer, size + HEADER_BYTES);
}

void getUdpMsg(uint16_t* dataID, uint16_t* size, uint8_t* data) {
  *dataID = 0;
  *size = 0;
  
  Serial.println("Checking messages");
  int packetSize = udpReceiver.parsePacket();
  Serial.print("Packet Size: ");
  Serial.println(packetSize);
  if (packetSize > 0){
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
    Serial.println();
    
  } 
}

void parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, uint8_t* data) {
  uint8_t proto_version = packet[0];
  if (proto_version == 1) {
    uint8_t dataIDUpper = packet[3];
    *dataID = dataIDUpper;
    *dataID = (*dataID << 8) | packet[4];
    uint8_t sizeUpper = packet[5];
    *size = sizeUpper;
    *size = (*size << 8) | packet[6];
    for( int i = 0; i<(*size); i++) {
      data[i] = packet[i+HEADER_BYTES];
    }
  }
}
