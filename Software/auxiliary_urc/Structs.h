#ifndef STRUCTS_H_
#define STRUCTS_H_

struct GPS_Data
{
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

#endif
