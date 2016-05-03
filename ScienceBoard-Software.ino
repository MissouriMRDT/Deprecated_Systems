#include <EasyTransfer.h>

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Servo.h>

#include "RoveBoard.h"
#include "RoveEthernet.h"
#include "RoveComm.h"
#include "RoveDynamixel.h"

//////////////////////////////////
// ===== CONFIG VARIABLES ===== //
//////////////////////////////////

static const int TOTAL_SENSORS  = 7;

//////////////////////////////////
//          Board Pins          //
//////////////////////////////////

static const int FUNNEL_SERVO   = PL_5;

//////////////////////////////////
//       RoveComm DataID        //
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
// M3 does not exist
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
static const int M4_ON           = 9;

//////////////////////////////////
//    Device States Variables   //
//////////////////////////////////

bool t1_on = false;
bool t2_on = false;
bool t3_on = false;
bool t4_on = false;
bool m1_on = false;
bool m2_on = false;
// M3 does not exist
bool m4_on = false;

int drill_mode = 0;

//////////////////////////////////
//    EasyTransfer Protocol     //
//////////////////////////////////

EasyTransfer ETin, ETout; // TODO : Change names after confirmed working

struct RECEIVE_DATA_STRUCTURE { // Must match drill side
  float sensor_data[TOTAL_SENSORS];  // TODO : How important is latency?
                                     // Do these reset to 0 after each send? Hold value? What if something unassigned?
  int sensor_id[TOTAL_SENSORS];      // Should size be made to optimize send time (8) or readability (10)
};

struct SEND_DATA_STRUCTURE { // Must match drill side
  bool sensor_state[TOTAL_SENSORS];  
  int drill_state;
};

RECEIVE_DATA_STRUCTURE data_in;
SEND_DATA_STRUCTURE    cmd_out;

//////////////////////////////////

Dynamixel Carousel;
Servo Funnel;

void setup(){
  roveComm_Begin(192, 168, 1, 135); // predetermined science board IP
  DynamixelInit(&Carousel, AX, 1, 7, 1000000);
  DynamixelSetMode(Carousel, Joint);
  Funnel.attach(FUNNEL_SERVO);
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
       // M3 will not be equipped. Line filled by oscillating crystal.
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
         
       case FUNNEL_OPEN:
         Funnel.write(180);
         break;
       case FUNNEL_CLOSE:
         Funnel.write(50);
         break;
     }
   }
   
   if(dataID == DRILL_CMD) {
     switch(receivedMsg[0]){
       case DRILL_FWD:
         drill_mode = DRILL_FWD;
         break;
       case DRILL_STOP:
         drill_mode = DRILL_STOP;
         break;
       case DRILL_REV:
         drill_mode = DRILL_REV;
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
   // Device controls block //
   ///////////////////////////
   
   // TODO : Figure out how drill board receives
   cmd_out.sensor_state[T1_ON - 3] = t1_on;
   cmd_out.sensor_state[T2_ON - 3] = t2_on;
   cmd_out.sensor_state[T3_ON - 3] = t3_on;
   cmd_out.sensor_state[T4_ON - 3] = t4_on;
   cmd_out.sensor_state[M1_ON - 3] = m1_on;
   cmd_out.sensor_state[M2_ON - 3] = m2_on;
   // M3 slot occupied by the oscillating crystal. No M3 moisture sensor
   cmd_out.sensor_state[M4_ON - 3] = m4_on;
   
   cmd_out.drill_state = drill_mode;
   
   // This block is first to use the sensor_state array in EasyTransfer for which 
   // reads are enabled instead of ANOTHER giant set of if statements or a switch case
   for(int i = 0; i < 5; i++) { // clear buffer
     ETin.receiveData();
   }
   for(int j = 0; j < TOTAL_SENSORS; j++) { 
     if(cmd_out.sensor_state[j]) // if sensor is enabled
       roveComm_SendMsg(data_in.sensor_id[j], sizeof(data_in.sensor_data[j]), &data_in.sensor_data[j]);
   }
   
   ETout.sendData();
}
