#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <EasyTransfer.h>
#include "Arduino.h"
#include "Setup.h"

//create ET object
//EasyTransfer ET;

//gps sensor
SoftwareSerial gpsSerial(9, 10); // (Rx, Tx)
SoftwareSerial moboSerial(0, 1); // (Rx, Tx)  **Not able to get HWSerial working

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
  GPS.fix;
  GPS.fixquality;
  GPS.satellites;
  GPS.latitude_fixed;
  GPS.lat;
  GPS.longitude_fixed;
  GPS.lon;
  GPS.altitude;
  GPS.speed;
  GPS.angle;

  //if millis or timer overflows, reset
  if(timer > millis())
    timer = millis();

  if(millis() - timer > data_delay)
  {
    timer = millis();

    gps_data.fix = GPS.fix;

    if(GPS.fix)
    {
      gps_data.fixquality = GPS.fixquality;
      gps_data.satellites = GPS.satellites;
      gps_data.latitude_fixed = GPS.latitude_fixed;
      gps_data.longitude_fixed = GPS.longitude_fixed;
      gps_data.altitude = GPS.altitude;
      gps_data.speed = GPS.speed;
      gps_data.angle = GPS.angle;
    }
  }

  if(GPS.lat == 'W')
    gps_data.latpos = 0;
  else
    gps_data.latpos = 1;

  if(GPS.lon == 'W')
    gps_data.lonpos = 0;
  else
    gps_data.lonpos = 1;

  /*
  Serial.print("fix = ");
  Serial.println(gps_data.fix);
  Serial.print("fixquality = ");
  Serial.println(gps_data.fixquality);
  Serial.print("satellites = ");
  Serial.println(gps_data.satellites);
  Serial.print("latitude_fixed = ");
  Serial.println(gps_data.latitude_fixed);
  Serial.print("latpos = ");
  Serial.println(gps_data.latpos);
  Serial.print("longitude_fixed = ");
  Serial.println(gps_data.longitude_fixed);
  Serial.print("lonpos = ");
  Serial.println(gps_data.lonpos);
  Serial.print("altitude = ");
  Serial.printlnt(gps_data.altitude);
  Serial.print("speed = ");
  Serial.println(gps_data.speed);
  Serial.print("angle = ");
  Serial.println(gps_data.angle);
  Serial.println("------------------------------");

  delay(50); //*/

//    moboSerial.write(gps_data);
}
