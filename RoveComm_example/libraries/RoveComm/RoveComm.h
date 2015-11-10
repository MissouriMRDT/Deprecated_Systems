#ifndef ROVECOMM_HEAD
#define ROVECOMM_HEAD

#define ROVECOMM_PORT 11000
#define VERSION_NO 0x01
#define HEADER_BYTES 7
#define SEQ 0x0F0F

#include <Energia.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


class RoveCommClass {
  
  //declare our receiving server and a subscriber buffer
  EthernetUDP udpReceiver;
  IPAddress rovecommSubscribers[5] = {INADDR_NONE};
  
  //function prototypes
  void sendPacket(IPAddress ip, int port, byte* msg, uint16_t size);
  void parseUdpMsg(uint8_t* packet, uint16_t* dataID, uint16_t* size, void* data);
  void sendMsgTo(uint16_t dataID, uint16_t size, void* data, IPAddress dest);
  void rovecommControl(uint16_t* dataID, uint16_t* size, void* data, IPAddress remote_ip, int remote_port);
  bool rovecommAddSubscriber(IPAddress address);

  
  public:
  void rovecommInit(IPAddress ip);
  void sendMsg(uint16_t dataID, uint16_t size, void* data);
  void getUdpMsg(uint16_t* dataID, uint16_t* size, void* data);
};

extern RoveCommClass RoveComm;
#endif
