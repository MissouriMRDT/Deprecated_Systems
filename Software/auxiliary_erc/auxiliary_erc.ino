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
  
  // Setup sensors
  gps_setup(GPS, gps_data);
  imu_setup(imu_data);
  sonar_setup(sonar_data0, sonar_data1, sonar_data2);
  volt_setup(volt_data);
    
  delay(1000); 
}

void loop()
{
  // do GPS stuff
  #ifdef ENABLE_GPS
  gps_update(GPS, gps_data);
  gps_send();
  #ifdef PRINT
  Serial.print("GPS num sats: "); Serial.println(gps_data.satellites);
  #endif
  #endif
  
  // do IMU stuff
  #ifdef ENABLE_IMU
  imu_update(imu_data);
  imu_send();
  #ifdef PRINT
  Serial.print("     IMU yaw: "); Serial.println(imu_data.heading);
  #endif
  #endif
  
  // do sonar stuff
  #ifdef ENABLE_SONAR
  sonar_update(sonar_data0, sonar_data1, sonar_data2);
//  sonar_send();
  #ifdef PRINT
  Serial.print(" Sonar0 dist: "); Serial.println(sonar_data0.dist);
//  Serial.print(" Sonar1 dist: "); Serial.println(sonar_data1.dist);
//  Serial.print(" Sonar2 dist: "); Serial.println(sonar_data2.dist);
  #endif
  #endif
  
  // do voltage sensor stuff
  #ifdef ENABLE_VOLT
  volt_update(volt_data);
  volt_send();
  #ifdef PRINT
  Serial.print("     Voltage: "); Serial.println(volt_data.voltage);
  #endif
  #endif
  
  delay(2000);
}











