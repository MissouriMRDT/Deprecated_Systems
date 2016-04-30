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

const byte DS18B20_ENABLE = 1;
const byte DS18B20_DISABLE = 2;
const byte SHT10_T_ENABLE = 3; 
const byte SHT10_T_DISABLE = 4;

const byte XD28_ENABLE = 9;
const byte XD28_DISABLE = 10;
const byte SHT10_H_ENABLE = 11;
const byte SHT10_H_DISABLE = 12; 
const byte FC28_ENABLE = 13;
const byte FC28_DISABLE = 14;

const byte DRILL_ENABLE = 15;
const byte DRILL_DISABLE = 16;

const int SCI_CMD = 1808;
const int DRILL_CMD = 866;
const int CAROUSEL_CMD = 1809;

//////////////////////////////////

bool xd28_on = false;
bool sht10_h_on = false;
bool fc28_on = false;
bool ds18b20_on = false;
bool sht10_t_on = false;
bool drill_on = false;

Dynamixel Carousel;

void setup(){
  roveComm_Begin(192, 168, 1, 135); // predetermined science board IP
  DynamixelInit(&Carousel, AX, 1, 7, 1000000);
  DynamixelSetMode(Carousel, Joint);
  Serial6.begin(9600);
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
       case XD28_ENABLE:
         xd28_on = true;
         break; 
       case XD28_DISABLE:
         xd28_on = false;
         break;
       case SHT10_H_ENABLE:
         sht10_h_on = true;
         break;
       case SHT10_H_DISABLE:
         sht10_h_on = false;
         break;
       case FC28_ENABLE:
         fc28_on = true;
         break;
       case FC28_DISABLE:
         fc28_on = false;
         break;
       case DS18B20_ENABLE:
         ds18b20_on = true;
         break;
       case DS18B20_DISABLE:
         ds18b20_on = false;
         break;
       case SHT10_T_ENABLE:
         sht10_t_on = true;
         break;
       case SHT10_T_DISABLE:
         sht10_t_on = false;
         break;
     }
   }
   
   if(dataID == DRILL_CMD)
   {
     if(receivedMsg[0])
       drill_on = true;
     if(!receivedMsg[0]);
       drill_on = false;
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
   if(xd28_on) {   
     Serial6.write(XD28_ENABLE);
     dataRead = Serial6.read();
     roveComm_SendMsg(0x728, sizeof(dataRead), &dataRead);
   } 
   if(sht10_h_on) {
     Serial6.write(SHT10_H_ENABLE);     
     dataRead = Serial6.read();
     roveComm_SendMsg(0x729, sizeof(dataRead), &dataRead);
   }
   if(fc28_on) {
     Serial6.write(FC28_ENABLE);
     dataRead = Serial6.read();
     roveComm_SendMsg(0x72A, sizeof(dataRead), &dataRead);
   }
   if(ds18b20_on) {
     Serial6.write(DS18B20_ENABLE);
     dataRead = Serial6.parseFloat();
     roveComm_SendMsg(0x720, sizeof(dataRead), &dataRead);
   }
   if(sht10_t_on) {
     Serial6.write(SHT10_T_ENABLE);
     dataRead = Serial6.parseFloat();
     roveComm_SendMsg(0x721, sizeof(dataRead), &dataRead);
   }
   
   //////////////////////////
   // Drill controls block //
   //////////////////////////
   if(drill_on) {
     Serial6.write(DRILL_ENABLE);
   }
   else if(!drill_on) {
     Serial6.write(DRILL_DISABLE);
   } 
}

