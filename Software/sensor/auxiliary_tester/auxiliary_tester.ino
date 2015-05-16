#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <EasyTransfer.h>
#include "Setup.h"

//create ET object
EasyTransfer ET;

//gps sensor serial
SoftwareSerial moboSerial(2, 3); // (Rx=0, Tx=1) **Set to 0,1 for 32u4 **Not able to get HWSerial working

Adafruit_GPS GPS(&Serial);//gpsSerial);

#define GPSECHO false // set to true if you want raw GPS data printed to serial monitor
#define TOSTRING false // set true if you want parsed gps_data.ToString() printed to serial monitor 
#define FIXINDICATOR false // set true if you want fix indicator on pin FIXOUT (digitalRead fix from GPS module on pin FIXIN)  

#define data_delay 50  //milliseconds between data collection

GPS_Data gps_data;  //instantiate struct to contain all sensor data

//timer collecting raw GPS data once every millisecond
SIGNAL(TIMER0_COMPA_vect)
{
  char c = GPS.read();
  #ifdef UDR0
    if (GPSECHO)
      if (c) UDR0 = c;
    // writing direct to UDR0 is much much faster than Serial.print
    // but only one character can be written at a time.
  #endif
}

void setup()
{
  // Begin Serial monitor comm for debugging
  Serial.begin(9600);

  // Begin mobo comm
  moboSerial.begin(115200);
  
  GPS_setup(GPS, gps_data);

  // Begin transfer library
  ET.begin(details(gps_data), &moboSerial);

  delay(1000);
}

uint32_t timer = millis();

void loop()
{
  //if millis or timer overflows, reset
  if (timer > millis())
    timer = millis();

// Populate GPS_Data struct w/ fake data
//  gps_data.struct_id = 140;
  gps_data.fix = 1;
  gps_data.fixquality = 2;
  gps_data.satellites = 8;
  gps_data.latitude_fixed = 379517250;
  gps_data.longitude_fixed = -917777716;
  gps_data.altitude = 343.30;
  gps_data.speed = 0.03;
  gps_data.angle = 150.76;

  // print out parsed data to serial monitor
  #ifdef TOSTRING
  #if TOSTRING
    gps_data.ToString();
  #endif 
  #endif

  //    moboSerial.write(gps_data);
  ET.sendData();
}
