#include "Arduino.h"
#define science_telem_request_id  130
#define PH_telem_id               131
#define moisture_telem_id         132
#define CCD_telem_packet_id       133

//request types
#define PH_TYPE    1
#define MOIST_TYPE 2
#define CCD_TYPE   3
#define LASER_ON   4
#define LASER_OFF  5


//-------------------------
//Comes in from motherboard
//-------------------------

struct science_telem_request
{
  byte struct_id;
  byte requestType;
};

//request types

//-----------------------
//Goes out to motherboard
//-----------------------

struct PH_telem
{
  byte struct_id;
  float PH;
};

struct moisture_telem
{
  byte struct_id;
  short moisture;
};

struct CCD_telem_packet
{
  byte struct_id;
  short packetIndex; 
  short data[12];
};
