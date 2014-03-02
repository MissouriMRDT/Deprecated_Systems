#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include "Arduino.h"
#include "Setup.h"

SoftwareSerial gpsSerial(3, 2); // (Rx, Tx)
Adafruit_GPS GPS(&gpsSerial);

//set to true if you want raw GPS data printed to serial monitor
#define GPSECHO true 

All_Data all_data;  //struct to contain all sensor data

//timer collecting raw GPS once every millisecond
SIGNAL(TIMER0_COMPA_vect) {
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
  Serial.begin(9600);
  Serial.println("Mars Rover Sensor Test");
  
  GPS_Setup(GPS, all_data);
  
  
  delay(1000);
  
}

uint32_t timer = millis();
void loop()
{
  if(GPS.newNMEAreceived())
  {
    if(!GPS.parse(GPS.lastNMEA()))
      return;
  }
  
  //if millis or timer overflows, reset
  if(timer > millis())
    timer = millis();
  
  //update struct data every 1.5 seconds
  
  /*
  if(millis() - timer > 2000)
  {
    timer = millis();
    
    all_data.gps_data.fix = GPS.fix;
    all_data.gps_data.fixquality = GPS.fixquality;
    all_data.gps_data.hour = GPS.hour;
    all_data.gps_data.minute = GPS.minute;
    all_data.gps_data.seconds = GPS.seconds;
    
    Serial.print("\nTime: ");
    Serial.print(all_data.gps_data.hour, DEC); Serial.print(':');
    Serial.print(all_data.gps_data.minute, DEC); Serial.print(':');
    Serial.println(all_data.gps_data.seconds, DEC);
    Serial.print("Date: ");
    Serial.print("Fix: "); Serial.print((int)all_data.gps_data.fix);
    Serial.print(" quality: "); Serial.println((int)all_data.gps_data.fixquality);
    
    if(GPS.fix)
    {
      all_data.gps_data.latitude = GPS.latitude;
      all_data.gps_data.longitude = GPS.longitude;
      all_data.gps_data.altitude = GPS.altitude;
      all_data.gps_data.speed = GPS.speed;
      all_data.gps_data.lat = GPS.lat;
      all_data.gps_data.lon = GPS.lon;
      all_data.gps_data.satellites = GPS.satellites;
      
      Serial.print("Location: ");
      Serial.print(all_data.gps_data.latitude, 4); Serial.print(all_data.gps_data.lat);
      Serial.print(", "); 
      Serial.print(all_data.gps_data.longitude, 4); Serial.println(all_data.gps_data.lon);
      
      Serial.print("Speed (knots): "); Serial.println(all_data.gps_data.speed);
      Serial.print("Altitude: "); Serial.println(all_data.gps_data.altitude);
      Serial.print("Satellites: "); Serial.println((int)all_data.gps_data.satellites);
      
      
      
    }
    
  }
    
    */
  
  
  
  
  
  
}
