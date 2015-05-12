#ifndef SETUP_H_
#define SETUP_H_

#include "Structs.h"

void GPS_setup(Adafruit_GPS &GPS, GPS_Data &gps_data)
{
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  //setting default values for GPS data
  gps_data.struct_id = 140;
  gps_data.fix = 0;
  gps_data.fixquality = 0;
  gps_data.satellites = 0;
  gps_data.latitude_fixed = 0;
  gps_data.longitude_fixed = 0;
  gps_data.altitude = 0;
  gps_data.speed = 0;
  gps_data.angle = 0;

//  //settings for GPS timer
//  OCR0A = 0xAF;
//  TIMSK0 |= _BV(OCIE0A);
}

#endif
