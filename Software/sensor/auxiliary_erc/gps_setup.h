#ifndef GPS_SETUP_H_
#define GPS_SETUP_H_

#include "auxiliary_erc.h"

struct GPS_Data
{
  uint8_t struct_id;
  bool fix;
  uint8_t fixquality;
  uint8_t satellites;
  int32_t latitude_fixed;
  int32_t longitude_fixed;
  float altitude;
  float speed;
  float angle;
};

GPS_Data gps_data;

SoftwareSerial gps_ser(GPS_RX, GPS_TX);
Adafruit_GPS GPS(&gps_ser);

void gps_setup(Adafruit_GPS &GPS, GPS_Data &gps_data)
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
  gps_data.struct_id = GPS_STRUCT_ID;
  gps_data.fix = 0;
  gps_data.fixquality = 0;
  gps_data.satellites = 0;
  gps_data.latitude_fixed = 0;
  gps_data.longitude_fixed = 0;
  gps_data.altitude = 0;
  gps_data.speed = 0;
  gps_data.angle = 0;
  
  return;
}
//void gps_setup(Adafruit_GPS &GPS, GPS_Data &gps_data)
//{
//  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
//  GPS.begin(9600);
//  
//  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
//  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
//  // uncomment this line to turn on only the "minimum recommended" data
//  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
//  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
//  // the parser doesn't care about other sentences at this time
//  
//  // Set the update rate
//  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
//  // For the parsing code to work nicely and have time to sort thru the data, and
//  // print it out we don't suggest using anything higher than 1 Hz
//
//  // Request updates on antenna status, comment out to keep quiet
//  GPS.sendCommand(PGCMD_ANTENNA);
//
//  //setting default values for GPS data
//  gps_data.struct_id = 140;
//  gps_data.fix = 0;
//  gps_data.fixquality = 0;
//  gps_data.satellites = 0;
//  gps_data.latitude_fixed = 0;
//  gps_data.longitude_fixed = 0;
//  gps_data.altitude = 0;
//  gps_data.speed = 0;
//  gps_data.angle = 0;
//  
//  // init EasyTransfer
//  gps_ET.begin(details(gps_data), &mobo_ser);
//  
//  return;
//}
//void gps_setup(Adafruit_GPS &GPS, GPS_Data &gps_data)
//{
//  GPS.begin(9600);
//  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
//  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
//  GPS.sendCommand(PGCMD_ANTENNA);
//  
//  // setting default values for GPS data
//  gps_data.struct_id = GPS_STRUCT_ID;
//  gps_data.fix = GPS.fix = 0;
//  gps_data.latitude_whole = 0;
//  gps_data.latitude_frac = 0;
//  gps_data.longitude_whole = 0;
//  gps_data.longitude_frac = 0;
//  gps_data.altitude_whole = 0;
//  gps_data.altitude_frac = 0;
//  gps_data.lat = 'X';
//  gps_data.lon = 'X';
//  gps_data.satellites = 0;
//  
//  // settings for GPS timer
//  OCR0A = 0xAF;
//  TIMSK0 |= _BV(OCIE0A);
//  
//  // init EasyTransfer
//  gps_ET.begin(details(gps_data), &Serial);
//  
//  return;
//}

void gps_update(Adafruit_GPS &GPS, GPS_Data &gps_data){
  if(GPS.newNMEAreceived())
  {
    if(!GPS.parse(GPS.lastNMEA()))
      return; //if fails to parse, go back to top of loop
  }
  
  gps_data.fix = GPS.fix;
  if(GPS.fix){
    gps_data.fixquality = GPS.fixquality;
    gps_data.satellites = GPS.satellites;
    gps_data.latitude_fixed = GPS.latitude_fixed;
    gps_data.longitude_fixed = GPS.longitude_fixed;
    gps_data.altitude = GPS.altitude;
    gps_data.speed = GPS.speed;
    gps_data.angle = GPS.angle;
    
    // Adjust latitude_fixed and longitude_fixed to reflect which hemispheres GPS is in (eliminates need for lat and lon)
    if (GPS.lat == 'S') {
      gps_data.latitude_fixed = -1 * gps_data.latitude_fixed;
    }
    if (GPS.lon == 'W') {
      gps_data.longitude_fixed = -1 * gps_data.longitude_fixed;
    }
  }
  
  return;
}

#endif
