#include "Arduino.h"
//-------------------------
//Comes in from motherboard
//-------------------------

struct science_telem_request
{
  byte struct_id;
  byte requestType;
};

//request types
const int PH_type = 1;
const int moisture_type = 2;
const int CCD_type = 3;

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
