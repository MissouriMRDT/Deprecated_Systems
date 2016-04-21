#include "RoveWare.h"
#include "RoveSci.h"

const int PIN_T1 = 1;
const int PIN_T2 = 2;
const int PIN_M1 = 3;
const int PIN_M2 = 4;
const int PIN_M3 = 5;

const byte GROVE_ENABLE = 9;
const byte GROVE_DISABLE = 10;
const byte SHT10_H_ENABLE = 11;
const byte SHT10_H_DISABLE = 12; 
const byte FC28_ENABLE = 13;
const byte FC28_DISABLE = 14;

const byte DS18B20_ENABLE = 1;
const byte DS18B20_DISABLE = 2;
const byte SHT10_T_ENABLE = 3; 
const byte SHT10_T_DISABLE = 4;

void setup(){
  roveComm_Begin(192, 168, 1, 135); // predetermined science board IP
  bool grove_on = false;
  bool sht10_h_on = false;
  bool fc28_on = false;
  bool ds18b20_on = false;
  bool sht10_t_on = false;
}

void loop(){
   float dataRead;
   int dataID = 0;
   size_t size = 0;
   byte receivedMsg[1];
   
   // check 
   roveComm_GetMsg(&dataID, &size, receivedMsg);
   
   // nest within a loop to continually run between enable and disable
   if(dataID == 1808)
   {
      switch(receivedMsg[0]){
        case GROVE_ENABLE:
          grove_on = true;
          break; 
        case GROVE_DISABLE:
          grove_on = false;
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
          ds18b20_on = true;
          break;
        case SHT10_T_ENABLE:
          sht10_t_on = true;
          break;
        case SHT10_T_DISABLE:
          sht10_t_on = false;
          break;
      }
   }
   
   if(grove_on) {   
     dataRead = roveSci_Grove_ReadHumid(PIN_M1);
     roveComm_SendMsg(0x728, sizeof(dataRead), dataRead);
   } 
   if(sht10_h_on) {
     dataRead = roveSci_SHT10_ReadHumid(PIN_M2);
     roveComm_SendMsg(0x729, sizeof(dataRead), dataRead);
   }
   if(fc28_on) {
     dataRead = roveSci_FC28_ReadHumid(PIN_M3);
     roveComm_SendMsg(0x72A, sizeof(dataRead), dataRead);
   }
   if(ds18b20_on) {
     dataRead = roveSci_DS18B20_ReadTemp(PIN_T1);
     roveComm_SendMsg(0x720, sizeof(dataRead), dataRead);
   }
   if(sht10_t_on) {
     dataRead = roveSci_SHT10_ReadTemp(PIN_T2);
     roveComm_SendMsg(0x721, sizeof(dataRead), dataRead);
   }
}

