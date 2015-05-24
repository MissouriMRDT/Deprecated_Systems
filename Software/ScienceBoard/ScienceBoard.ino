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
#define CCD_ELEMENTS      3694 //Number of Samples needed
#define LASER_WARMUP_TIME 3000 //3 second warmup
#define LASER_ON_TIME     1000 //1 second runtime
#define PH_STRUC_ID       210 //***FILLER NEEDS CONFIRM***

//-----------------------------------
// Software Serial Declares 
//-----------------------------------

SoftwareSerial PHSerial(PH_SENS_RX, PH_SENS_TX); // RX, TX
SoftwareSerial CCDSerial(CCD_RX, CCD_TX); // RX, TX

//-----------------------------------
// Mobo Variables  
//-----------------------------------

science_telem_request Req_data_from_Mobo;

//-----------------------------------
// PH Variables  
//-----------------------------------
PH_telem PH_data_to_Mobo;

char ph_rec_data[20]; //Data Buffer for data coming off of the pH Sensor
float ph = 0;             //Floating point number being sent to the MOBO
byte received_from_sensor = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_CTR, OUTPUT);  
  Serial.begin(115200);
  
  //Take the PH sensor out of continuous mode
  PHSerial.print("c,0\r"); 
  delay(50); 
  PHSerial.print("c,0\r"); 
  delay(50);
  
  //Open software serial on PH sensor
  PHSerial.begin(9600);
  //Open software serial on CCD at 115200 baud
  CCDSerial.begin(115200);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0 && Req_data_from_Mobo.requestType != 0)
  {
      switch(Req_data_from_Mobo.requestType)
      {
        case PH_TYPE:
  //        Read PH data (Software Serial);
         PHSerial.print("R\r"); //Request data from sensor
         delay(50); //Delay? Don't know if needed
         if(PHSerial.available()>0) //Read if data is there
         {
           received_from_sensor=PHSerial.readBytesUntil(13,ph_rec_data,20); //Read until carriage return
           
           ph_rec_data[received_from_sensor]=0; //Add null to end of array
           
           ph = atof(ph_rec_data); //Convert to floating
         
           PH_data_to_Mobo.struct_id = PH_STRUC_ID; //Fill in the struct with id
           PH_data_to_Mobo.PH = ph; //Fill in the struct with data
           
         }
         
  //        Send PH data;
          break;
        case MOIST_TYPE:
  //        Read Moisture Data (analog input);
  //        Send moisture data;
          break;
        case CCD_TYPE:
          digitalWrite(LASER_CTR, HIGH);
          delay(LASER_WARMUP_TIME);
        //  send CCD read request;
          delay(LASER_ON_TIME);
          digitalWrite(LASER_CTR, LOW);
          for(int i = 0; i < CCD_ELEMENTS; i++)
          {
            //request element from due
            //write into struct
            //if(struct full)
               //send struct 
          }
          break;
        default:
          //Error
          break;
      }
          
          
  }
  
}
