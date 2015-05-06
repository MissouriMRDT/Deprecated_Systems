#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <EasyTransfer.h>
#include "Arduino.h"
#include "Setup.h"

//create ET object
//EasyTransfer ET;

//gps sensor
SoftwareSerial gpsSerial(9, 10); // (Rx, Tx)
SoftwareSerial moboSerial(8, 6);
Adafruit_GPS GPS(&gpsSerial);
#define GPSECHO false //set to true if you want raw GPS data printed to serial monitor

#define data_delay 50  //milliseconds between data collection

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

  // Start GPS parse object
  GPS_setup(GPS, gps_data);

  // Begin transfer library
  //ET.begin(details(gps_data), &Serial);

  delay(1000);
}

uint32_t timer = millis();

void loop()
{
//  Serial.println("fix = " + GPS.fix);
//  Serial.println("fixquality = " + GPS.fixquality);
//  Serial.println("satellites = " + GPS.satellites);
//  Serial.println("latitude = " + GPS.latitude);
//  Serial.println("latitude_fixed = " + GPS.latitude_fixed);
//  Serial.println("latitudeDegrees = " + GPS.latitudeDegrees);
//  Serial.println("lat = " + GPS.lat);
//  Serial.println("longitude = " + GPS.longitude);
//  Serial.println("longitude_fixed = " + GPS.longitude_fixed);
//  Serial.println("longitudeDegrees = " + GPS.longitudeDegrees);
//  Serial.println("lon = " + GPS.lon);
//  Serial.println("speed = " + GPS.speed);
//  Serial.println("angle = " + GPS.angle);
//  Serial.println("magvariation = " + GPS.magvariation);
//  Serial.println("mag = " + GPS.mag);
//  Serial.println("altitude = " + GPS.altitude);
//  Serial.println("geoidheight = " + GPS.geoidheight);
//  Serial.println("HDOP = " + GPS.HDOP);
//  Serial.println("------------------------------");
//
//  delay(50);

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

    if(GPS.fix)
    {
      gps_data.fix = GPS.fix;
      gps_data.fixquality = GPS.fixquality;
      gps_data.satellites = GPS.satellites;
      gps_data.latitude_fixed = GPS.latitude_fixed;
      gps_data.longitude_fixed = GPS.longitude_fixed;
      gps_data.altitude = GPS.altitude;
      gps_data.speed = GPS.speed;
      gps_data.angle = GPS.angle;
    }
  }
    //ET.senddata();
    moboSerial.println(gps_data);
}
