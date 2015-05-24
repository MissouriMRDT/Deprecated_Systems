//----------------------
// Pin assignments
//----------------------

const int LASER_CTR = 6;

const int PH_SENS_RX = 2;
const int PH_SENS_TX = 3;

const int CCD_RX = 4;
const int CCD_TX = 5;

const int MOIS_SENSOR = 0; //Analog

//--------------------
//
//---------------------
const int LASER_WARMUP_TIME = 3000;

void setup() {
  // put your setup code here, to run once:
  pinMode(LASER_CTR, OUTPUT);  
  Serial.begin(115200);
  
  //Open software serial on PH sensor
  
  //Open software serial on CCD at 115200 baud
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //if(recieve science_telem_request)
  //{
      switch(science_telem_request.requestType)
      {
        case PH_type:
          Read PH data (Software Serial);
          Send PH data;
          break
        case moisture_type:
          Read Moisture Data (analog input);
          Send moisture data;
          break;
        case CCD_type:
          digitalWrite(LASER_CTR);
          delay(LASER_WARMUP_TIME);
          send CCD read request;
          delay(LASER_ON_TIME);
          digitalWrite(LASER_CTR, LOW);
          for(int i = 0; i < CCD_ELEMENTS; i++)
          {
            request element from due
            write into struct
            if(struct full)
               send struct 
          }
          break;
        default:
          Error
      }
          
          
    
  
}
