#include <EasyTransfer.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "RoveBoard.h"
#include "RoveEthernet.h"
#include "RoveComm.h"
#include "RoveDynamixel.h"

//////////////////////////////////
// ===== CONFIG VARIABLES ===== //
//////////////////////////////////

static const int TEMP_SCALE     = 10;

//////////////////////////////////
//      RoveComm DataID         //
//////////////////////////////////

static const int SCI_CMD        = 1808;
static const int DRILL_CMD      = 866;
static const int CAROUSEL_CMD   = 1809;

//////////////////////////////////
// RoveComm received messages   //
//////////////////////////////////

static const byte T1_ENABLE     = 1;
static const byte T1_DISABLE    = 2;
static const byte T2_ENABLE     = 3; 
static const byte T2_DISABLE    = 4;
static const byte T3_ENABLE     = 5;
static const byte T3_DISABLE    = 6;
static const byte T4_ENABLE     = 7;
static const byte T4_DISABLE    = 8;

static const byte M1_ENABLE     = 9;
static const byte M1_DISABLE    = 10; 
static const byte M2_ENABLE     = 11;
static const byte M2_DISABLE    = 12;
static const byte M3_ENABLE     = 13;
static const byte M3_DISABLE    = 14;
static const byte M4_ENABLE     = 15;
static const byte M4_DISABLE    = 16;

static const byte CCD_REQ       = 17;
static const byte LASER_ENABLE  = 18;
static const byte LASER_DISABLE = 19;
static const byte FUNNEL_OPEN   = 20;
static const byte FUNNEL_CLOSE  = 21;

static const byte DRILL_STOP    = 0;
static const byte DRILL_FWD     = 1;
static const byte DRILL_REV     = 2;


//////////////////////////////////
//     DrillBoard Commands      //
//////////////////////////////////

static const int T1_ON           = 3;
static const int T2_ON           = 4;
static const int T3_ON           = 5;
static const int T4_ON           = 6;

static const int M1_ON           = 7;
static const int M2_ON           = 8;
static const int M3_ON           = 9;
static const int M4_ON           = 10;

//////////////////////////////////
//    Device States Variables   //
//////////////////////////////////

bool m1_on = false;
bool m2_on = false;
bool m3_on = false;
bool m4_on = false;
bool t1_on = false;
bool t2_on = false;
bool t3_on = false;
bool t4_on = false;

int drill_state = 0;

//////////////////////////////////
//    EasyTransfer Protocol     //
//////////////////////////////////

EasyTransfer ETin, ETout; // TODO : Change names after confirmed working

struct RECEIVE_DATA_STRUCTURE { // Must match drill side
  float sensor_data;
  int sensor_id;
};

struct SEND_DATA_STRUCTURE { // Must match drill side
  int device_state;
};

RECEIVE_DATA_STRUCTURE data_in;
SEND_DATA_STRUCTURE    cmd_out;

//////////////////////////////////

Dynamixel Carousel;

void setup(){
  roveComm_Begin(192, 168, 1, 135); // predetermined science board IP
  DynamixelInit(&Carousel, AX, 1, 7, 1000000);
  DynamixelSetMode(Carousel, Joint);
  Serial6.begin(9600);
  ETin.begin(details(data_in), &Serial);
  ETout.begin(details(cmd_out), &Serial);
}

void loop(){
   float dataRead;
   uint16_t dataID = 0;
   size_t size = 0;
   byte receivedMsg[1];
   
   // Get command from base station
   roveComm_GetMsg(&dataID, &size, receivedMsg);
   
   if(dataID == SCI_CMD)
   {
     //////////////////////////  
     // enable devices block //
     //////////////////////////
     
     switch(receivedMsg[0]){
       case M1_ENABLE:
         m1_on = true;
         break; 
       case M1_DISABLE:
         m1_on = false;
         break;
       case M2_ENABLE:
         m2_on = true;
         break;
       case M2_DISABLE:
         m2_on = false;
         break;
       case M3_ENABLE:
         m3_on = true;
         break;
       case M3_DISABLE:
         m3_on = false;
         break;
       case M4_ENABLE:
         m4_on = true;
         break;
       case M4_DISABLE:
         m4_on = false;
         break;
         
       case T1_ENABLE:
         t1_on = true;
         break;
       case T1_DISABLE:
         t1_on = false;
         break;
       case T2_ENABLE:
         t2_on = true;
         break;
       case T2_DISABLE:
         t2_on = false;
         break;
       case T3_ENABLE:
         t3_on = true;
         break;
       case T3_DISABLE:
         t3_on = false;
         break;
       case T4_ENABLE:
         t4_on = true;
         break;
       case T4_DISABLE:
         t4_on = false;
         break;
     }
   }
   
   if(dataID == DRILL_CMD) {
     switch(receivedMsg[0]){
       case DRILL_FWD:
         drill_state = DRILL_FWD;
         break;
       case DRILL_STOP:
         drill_state = DRILL_STOP;
         break;
       case DRILL_REV:
         drill_state = DRILL_REV;
         break;
     }
   }
     
   if(dataID == CAROUSEL_CMD)
   {
     uint16_t position = *(uint8_t*)(receivedMsg);
     if (position == 5)
       position = 4;
     DynamixelRotateJoint(Carousel, position * 102);
   }
   
   ///////////////////////////
   // Sensor controls block //
   ///////////////////////////
   
   // Temperature sensor scaled up in drill board
   if(t1_on) {   
     /*Serial6.write(T1_ON);
     dataRead = Serial6.read() / TEMP_SCALE; 
     roveComm_SendMsg(0x720, sizeof(dataRead), &dataRead);
     */
     cmd_out.device_state = T1_ON;
     ETout.sendData();
   } 
   if(t2_on) {   
     /*Serial6.write(T2_ON);
     dataRead = Serial6.read() / TEMP_SCALE;
     roveComm_SendMsg(0x721, sizeof(dataRead), &dataRead);*/
     cmd_out.device_state = T2_ON;
     ETout.sendData();
   } 
   if(t3_on) {   
     /* Serial6.write(T3_ON);
     dataRead = Serial6.read() / TEMP_SCALE;
     roveComm_SendMsg(0x722, sizeof(dataRead), &dataRead);
     */
     cmd_out.device_state = T3_ON;
     ETout.sendData();
   } 
   if(t4_on) {   
     /* Serial6.write(T4_ON);
     dataRead = Serial6.read() / TEMP_SCALE;
     roveComm_SendMsg(0x723, sizeof(dataRead), &dataRead);
     */ 
     cmd_out.device_state = T4_ON;
     ETout.sendData();
   } 
   
   if(m1_on) {   
     /* Serial6.write(M1_ON);
     dataRead = Serial6.read();
     roveComm_SendMsg(0x728, sizeof(dataRead), &dataRead);
     */
     cmd_out.device_state = M1_ON;
     ETout.sendData();
   } 
   if(m2_on) {   
     /*Serial6.write(M2_ON);
     dataRead = Serial6.read();
     roveComm_SendMsg(0x729, sizeof(dataRead), &dataRead);
     */
     cmd_out.device_state = M2_ON;
     ETout.sendData();
   } 
   
   // M3 slot occupied by the oscillating crystal. No M3 moisture sensor
   
   if(m4_on) {   
     /*Serial6.write(M4_ON);
     dataRead = Serial6.read();
     roveComm_SendMsg(0x72B, sizeof(dataRead), &dataRead);
     */
     cmd_out.device_state = M4_ON;
     ETout.sendData();
   } 
   
   //////////////////////////
   // Drill controls block //
   //////////////////////////
   
   Serial6.write(drill_state);
}
