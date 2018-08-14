#include <SoftwareSerial.h>
#include <EasyTransfer.h>
#include <Wire.h>
#include <Adafruit_GPS.h>
#include "auxiliary_erc.h"

#include "gps_setup.h"
#include "imu_setup.h"
#include "sonar_setup.h"
#include "volt_setup.h"

//timer collecting raw GPS data once every millisecond
SIGNAL(TIMER0_COMPA_vect){
  char c = GPS.read();
  #ifdef UDR0
    if (GPSECHO)
      if (c) UDR0 = c;  
      // writing direct to UDR0 is much much faster than Serial.print 
      // but only one character can be written at a time. 
  #endif
}

SoftwareSerial mobo_ser(MOBO_RX, MOBO_TX);
EasyTransfer ET;

Sensor_Data sensor_data;

void setup()
{
  Serial.begin(115200);
  
  // Start mobo serial
  mobo_ser.begin(115200);
  ET.begin(details(sensor_data), &mobo_ser);
  
  // Setup sensors
  setup_data(GPS, gps_data, imu_data, son0_data, son1_data, son2_data, volt_data);
    
  delay(500); 
}

void loop(){
  update_data(GPS, gps_data, me, imu_data, son0_data, son1_data, son2_data, volt_data);
  combine_data(sensor_data, gps_data, imu_data, son0_data, son1_data, son2_data, volt_data);
  send_data(ET);
  if(PRINT_TO_SERIAL)
    print_data(sensor_data);
  
  delay(100);
}

void setup_data(Adafruit_GPS &GPS, GPS_Data &gps_data, IMU_Data &imu_data, Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data, Volt_Data &volt_data){
  if(ENABLE_GPS)
    gps_setup(GPS, gps_data);
  if(ENABLE_IMU)
    imu_setup(imu_data, me);
  if(ENABLE_SONAR)
    sonar_setup(son0_data, son1_data, son2_data);
  if(ENABLE_VOLT)
    volt_setup(volt_data);
}

void update_data(Adafruit_GPS &GPS, GPS_Data &gps_data, lsm9ds1 &me, IMU_Data &imu_data, Sonar_Data &son0_data, Sonar_Data &son1_data, Sonar_Data &son2_data, Volt_Data &volt_data){
  if(ENABLE_GPS)
    gps_update(GPS, gps_data);
  if(ENABLE_IMU)
    imu_update(imu_data, me);
  if(ENABLE_SONAR)
    sonar_update(son0_data, son1_data, son2_data);
  if(ENABLE_VOLT)
    volt_update(volt_data);
}

void combine_data(Sensor_Data &data, GPS_Data &gps, IMU_Data &imu, Sonar_Data son0, Sonar_Data son1, Sonar_Data son2, Volt_Data volt){
  data.struct_id = SENSOR_STRUCT_ID;
  data.gps_fix = gps.fix;
  data.gps_fixquality = gps.fixquality;
  data.gps_satellites = gps.satellites;
  data.gps_latitude_fixed = gps.latitude_fixed;
  data.gps_longitude_fixed = gps.longitude_fixed;
  data.gps_altitude = gps.altitude;
  data.gps_speed = gps.speed;
  data.gps_angle = gps.angle;
  data.imu_heading = imu.heading;
  data.son0_dist = son0.dist;
  data.son1_dist = son1.dist;
  data.son2_dist = son2.dist;
  data.rawvoltage = volt.rawvoltage;
}

void send_data(EasyTransfer &et){
  et.sendData();
  delay(send_delay);
  return;
}

void print_data(Sensor_Data &data){
  if(ENABLE_GPS){
    Serial.print("GPS num sats: "); 
    Serial.println(data.gps_satellites);
  }
  if(ENABLE_IMU){
    Serial.print("     IMU yaw: "); 
    Serial.println(data.imu_heading);
  }
  if(ENABLE_SONAR){
    Serial.print(" Sonar0 dist: "); Serial.println(data.son0_dist);
    Serial.print(" Sonar1 dist: "); Serial.println(data.son1_dist);
    Serial.print(" Sonar2 dist: "); Serial.println(data.son2_dist);
  }
  if(ENABLE_VOLT){
    Serial.print("     Voltage: "); 
    Serial.println(data.rawvoltage);
  }
}









