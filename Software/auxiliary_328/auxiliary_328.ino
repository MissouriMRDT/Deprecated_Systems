#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <EasyTransfer.h>
#include "Arduino.h"
#include "Setup.h"

//create ET object
EasyTransfer ET;

//gps sensor
SoftwareSerial gpsSerial(3, 2); // (Rx, Tx)
Adafruit_GPS GPS(&gpsSerial);
#define GPSECHO true //set to true if you want raw GPS data printed to serial monitor

#define data_delay 100  //milliseconds between data collection

GPS_Data gps_data;  //instantiate struct to contain all sensor data

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
  Serial.println("Mars Rover Sensor Test");
  
  GPS_setup(GPS, gps_data);
  
  ET.begin(details(gps_data), &Serial);
  
  delay(1000); 
}

uint32_t timer = millis();
void loop()
{
  if(GPS.newNMEAreceived())
  {
    if(!GPS.parse(GPS.lastNMEA()))
      return; //if fails to parse, go back to top of loop
  }
  
  //if millis or timer overflows, reset
  if(timer > millis())
    timer = millis();
  
  if(millis() - timer > data_delay)
  {
    timer = millis();
    
    gps_data.fix = GPS.fix;
    gps_data.fixquality = GPS.fixquality;
    gps_data.hour = GPS.hour;
    gps_data.minute = GPS.minute;
    gps_data.seconds = GPS.seconds;
    
    /* 
    Serial.print("\nTime: ");
    Serial.print(all_data.gps_data.hour, DEC); Serial.print(':');
    Serial.print(all_data.gps_data.minute, DEC); Serial.print(':');
    Serial.println(all_data.gps_data.seconds, DEC);
    Serial.print("Date: ");
    Serial.print("Fix: "); Serial.print((int)all_data.gps_data.fix);
    Serial.print(" quality: "); Serial.println((int)all_data.gps_data.fixquality);
    */
    
    if(GPS.fix)
    {
      gps_data.latitude = GPS.latitude;
      gps_data.longitude = GPS.longitude;
      gps_data.altitude = GPS.altitude;
      gps_data.speed = GPS.speed;
      gps_data.lat = GPS.lat;
      gps_data.lon = GPS.lon;
      gps_data.satellites = GPS.satellites;
      
      /*
      Serial.print("Location: ");
      Serial.print(all_data.gps_data.latitude, 4); Serial.print(all_data.gps_data.lat);
      Serial.print(", "); 
      Serial.print(all_data.gps_data.longitude, 4); Serial.println(all_data.gps_data.lon);
      
      Serial.print("Speed (knots): "); Serial.println(all_data.gps_data.speed);
      Serial.print("Altitude: "); Serial.println(all_data.gps_data.altitude);
      Serial.print("Satellites: "); Serial.println((int)all_data.gps_data.satellites);
      */
    }
  }
    ET.sendData();
}
