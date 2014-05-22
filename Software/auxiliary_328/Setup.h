#ifndef SETUP_H_
#define SETUP_H_

#include "Structs.h"

void GPS_setup(Adafruit_GPS &GPS, GPS_Data &gps_data)
{
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  
  //setting default values for GPS data
  gps_data.fix = GPS.fix;
  gps_data.latitude = 0.0;
  gps_data.longitude = 0.0;
  gps_data.altitude = 0.0;
  gps_data.speed = 0.0;
  gps_data.lat = 'X';
  gps_data.lon = 'X';
  gps_data.hour = 0.0;
  gps_data.minute = 0.0;
  gps_data.seconds = 0.0;
  gps_data.satellites = 0.0;
  
  //settings for GPS timer
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

#endif
