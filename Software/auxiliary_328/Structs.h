#ifndef STRUCTS_H_
#define STRUCTS_H_

struct GPS_Data
{
  uint8_t fix;
  float latitude, longitude, altitude, speed;
  uint8_t lat, lon;
  uint8_t hour, minute, seconds, fixquality, satellites;
};

#endif
