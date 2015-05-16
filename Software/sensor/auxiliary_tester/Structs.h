#ifndef STRUCTS_H_
#define STRUCTS_H_

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
  
  void ToString();
};

void GPS_Data::ToString(){
  Serial.print("struct_id = ");
  Serial.println(struct_id);
  Serial.print("fix = ");
  Serial.println(fix);
  Serial.print("fixquality = ");
  Serial.println(fixquality);
  Serial.print("satellites = ");
  Serial.println(satellites);
  Serial.print("latitude_fixed = ");
  Serial.println(latitude_fixed);
  Serial.print("longitude_fixed = ");
  Serial.println(longitude_fixed);
  Serial.print("altitude = ");
  Serial.println(altitude);
  Serial.print("speed = ");
  Serial.println(speed); // in knots
  Serial.print("angle = ");
  Serial.println(angle);
  Serial.println("------------------------------");
  delay(500);
}

#endif
