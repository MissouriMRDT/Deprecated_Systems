#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <EasyTransfer.h>
#include "Arduino.h"
#include "Setup.h"

//create ET object
EasyTransfer ET;

//gps sensor
SoftwareSerial gpsSerial(3, 2); // (Rx, Tx)
Adafruit_GPS GPS(&gpsSerial);
#define GPSECHO false //set to true if you want raw GPS data printed to serial monitor

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
  Serial.begin(115200);
  
  // Start GPS parse object
  GPS_setup(GPS, gps_data);
  
  // Begin transfer library
  ET.begin(details(gps_data), &Serial);
  
  delay(1000); 
}

uint32_t timer = millis();

void loop()
{
  if(GPS.newNMEAreceived())
  {
    if(!GPS.parse(GPS.lastNMEA()))
      return; //if fails to parse, go back to top of loop
  }
  
  //if millis or timer overflows, reset
  if(timer > millis())
    timer = millis();
  
  if(millis() - timer > data_delay)
  {
    timer = millis();
    
    gps_data.fix = GPS.fix;
    
    if(GPS.fix)
    {
      gps_data.latitude_whole = GPS.latitude;
      gps_data.latitude_frac = (GPS.latitude-gps_data.latitude_whole)*1000;
      gps_data.lat = GPS.lat;
      gps_data.longitude_whole = GPS.longitude;
      gps_data.longitude_frac = (GPS.longitude-gps_data.longitude_whole)*1000;
      gps_data.lon = GPS.lon;
      gps_data.altitude_whole = GPS.altitude;
      gps_data.altitude_frac = (GPS.altitude-gps_data.altitude_whole)*1000; 
      gps_data.satellites = GPS.satellites;
    }
  }
    ET.sendData();
}
