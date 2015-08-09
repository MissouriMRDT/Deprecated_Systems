#ifndef GPS_SETUP_H_
#define GPS_SETUP_H_

#include "auxiliary_erc.h"

struct GPS_Data
{
  uint8_t struct_id;
  uint8_t fix;
  uint16_t latitude_whole;
  uint16_t latitude_frac;
  uint16_t longitude_whole;
  uint16_t longitude_frac;
  uint16_t altitude_whole;
  uint16_t altitude_frac;
  uint8_t lat;
  uint8_t lon;
  uint8_t satellites;
};

GPS_Data gps_data;

EasyTransfer gps_ET;

SoftwareSerial gps_ser(GPS_RX, GPS_TX);
Adafruit_GPS GPS(&gps_ser);

void gps_setup(Adafruit_GPS &GPS, GPS_Data &gps_data)
{
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  
  // setting default values for GPS data
  gps_data.struct_id = GPS_STRUCT_ID;
  gps_data.fix = GPS.fix = 0;
  gps_data.latitude_whole = 0;
  gps_data.latitude_frac = 0;
  gps_data.longitude_whole = 0;
  gps_data.longitude_frac = 0;
  gps_data.altitude_whole = 0;
  gps_data.altitude_frac = 0;
  gps_data.lat = 'X';
  gps_data.lon = 'X';
  gps_data.satellites = 0;
  
  // settings for GPS timer
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  
  // init EasyTransfer
  gps_ET.begin(details(gps_data), &Serial);
  
  return;
}

void gps_update(Adafruit_GPS &GPS, GPS_Data &gps_data){
  if(GPS.newNMEAreceived())
  {
    if(!GPS.parse(GPS.lastNMEA()))
      return; //if fails to parse, go back to top of loop
  }
  
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
  
  return;
}

void gps_send(){
  send_data(gps_ET);
  
  return;
}

#endif
