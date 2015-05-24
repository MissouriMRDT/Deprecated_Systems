#include "structs.h"
#include <SoftwareSerial.h>

//----------------------
// Pin assignments
//----------------------

#define MOIS_SENSOR       0 //Analog Pin A0 -- Real Pin 23
#define ROVE_COM_RX       0 //Digital Pin D0 -- Real Pin 2
#define ROVE_ROM_TX       1 //Digital Pin D1 -- Real Pin 3
#define PH_SENS_RX        2 //Digital Pin D2 -- Real Pin 4
#define PH_SENS_TX        3 //Digital Pin D3 -- Real Pin 5
#define CCD_RX            4 //Digital Pin D4 -- Real Pin 6
#define CCD_TX            5 //Digital Pin D5 -- Real Pin 11
#define LASER_CTR         6 //Digital Pin D6 -- Real Pin 12
#define CCD_ELEMENTS      3684 //Shit needs checking ***NO FUCKING CLUE***
#define LASER_WARMUP_TIME 3000 //3 second warmup
#define LASER_ON_TIME     1000 //3 seconds ***TENTATIVE***


SoftwareSerial PHSerial(PH_SENS_RX, PH_SENS_TX); // RX, TX

SoftwareSerial CCDSerial(CCD_RX, CCD_TX); // RX, TX


void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_CTR, OUTPUT);  
  Serial.begin(115200);
  
  //Open software serial on PH sensor
  PHSerial.begin(9600);
  //Open software serial on CCD at 115200 baud
  CCDSerial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //if(recieve science_telem_request)
  {
  //    switch(science_telem_request.requestType)
  //    {
  ///      case PH_type:
  //        Read PH data (Software Serial);
  //        Send PH data;
  //        break
  //      case moisture_type:
  //        Read Moisture Data (analog input);
  //        Send moisture data;
  //        break;
  //      case CCD_type:
  //        digitalWrite(LASER_CTR);
      //    delay(LASER_WARMUP_TIME);
        //  send CCD read request;
         // delay(LASER_ON_TIME);
          //digitalWrite(LASER_CTR, LOW);
          for(int i = 0; i < CCD_ELEMENTS; i++)
          {
            //request element from due
            //write into struct
            //if(struct full)
               //send struct 
          }
        //break;
        //default:
          //Error
      }
          
          
    
  
}
