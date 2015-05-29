#include "structs.h"
#include <SoftwareSerial.h>
#include "EasyTransfer.h"

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

#define BLOCK_SIZE      12
#define CCD_BLOCKS      304 //Number of Samples needed
#define LASER_WARMUP_TIME 3000 //3 second warmup
#define LASER_PRE_ON_TIME     1000 //1 second runtime
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

PH_telem PH;
moisture_telem moisture;
CCD_telem_packet ccddata;

EasyTransfer Mobo_incoming;
EasyTransfer PH_comm;
EasyTransfer Moisture_comm;
EasyTransfer CCD_comm;

char ph_rec_data[20]; //Data Buffer for data coming off of the pH Sensor
float ph = 0;             //Floating point number being sent to the MOBO
byte received_from_sensor = 0;

bool recvStruct(science_telem_request* telem_req);

void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_CTR, OUTPUT);

  Req_data_from_Mobo.struct_id = science_telem_request_id;
  PH.struct_id = PH_telem_id;
  moisture.struct_id = moisture_telem_id;
  ccddata.struct_id = CCD_telem_packet_id;

  Serial.begin(115200);
  Mobo_incoming.begin(details(Req_data_from_Mobo), &Serial);
  PH_comm.begin(details(PH), &Serial);
  Moisture_comm.begin(details(moisture), &Serial);
  CCD_comm.begin(details(ccddata), &Serial);


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

  if (Mobo_incoming.receiveData())
  {
    switch (Req_data_from_Mobo.requestType) {
      case PH_TYPE:
        //        Read PH data (Software Serial);
        PHSerial.print("R\r"); //Request data from sensor
        delay(50); //Delay? Don't know if needed
        if (PHSerial.available() > 0) //Read if data is there
        {
          received_from_sensor = PHSerial.readBytesUntil(13, ph_rec_data, 20); //Read until carriage return

          ph_rec_data[received_from_sensor] = 0; //Add null to end of array

          PH.PH = atof(ph_rec_data); //Convert to floating

          PH_comm.sendData();
        }
        break;

      case MOIST_TYPE:
        moisture.moisture = analogRead(MOIS_SENSOR);
        //        Send moisture data;
        Moisture_comm.sendData();
        break;

      case CCD_TYPE:
        //Sample
        CCDSerial.print('S');

        //Output
        CCDSerial.print('O');
        CCDSerial.flush();
        for (int i = 0; i < CCD_BLOCKS; i++)
        {
          ccddata.packetIndex = i;
          for (int j = 0; j < 12; j++)
          {
            ccddata.data[j] = ((CCDSerial.read() << 8) & CCDSerial.read()) ;
          }

          //Check that we're still in sync with CCD
          CCD_comm.sendData();
        }
        break;
      case LASER_ON:
        digitalWrite(LASER_CTR, HIGH);
        break;
      case LASER_OFF:
        digitalWrite(LASER_CTR, LOW);
        break;
      default:
        //Error
        break;
    }
  }


}
