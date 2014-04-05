#ifndef STRUCTS_H_
#define STRUCTS_H_

struct GPS_Data
{
  boolean fix;
  float latitude, longitude, altitude, speed;
  char lat, lon;
  uint8_t hour, minute, seconds, fixquality, satellites;
};

struct Temp_Data
{
  float temperature;
  float humidity;
};

struct All_Data
{
  GPS_Data gps_data;
  Temp_Data temp_data;
    
    
    
};


#endif
