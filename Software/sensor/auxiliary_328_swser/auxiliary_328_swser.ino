#include <Adafruit_GPS.h> // Allows interaction with Adafruit GPS Module
#include <SoftwareSerial.h> // Allows UART on non-hardware serial digital pins
#include <EasyTransfer.h> // Simplifies transmission of structs
#include "Setup.h"

// create EasyTransfer object
EasyTransfer ET;

// create SoftwareSerial streams
SoftwareSerial moboSerial(2, 3); // (Rx from mobo, Tx to mobo)
SoftwareSerial gpsSerial(9, 10); // (Rx from GPS, Tx to GPS)

// create Adafruit_GPS object
Adafruit_GPS GPS(&gpsSerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false

// Set TOSTRING to 'false' to turn off printing of parsed GPS data in GPS_Data struct to Serial console
// Set to 'true' to print parsed data to Serial console
#define TOSTRING false

// Collect data from GPS every [data_delay] milliseconds
#define data_delay 500

// create GPS_Data struct to hold gps data
GPS_Data gps_data;

void setup()  
{
    
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars also spit it out
  Serial.begin(115200);
  
  // Start motherboard communication UART and EasyTransfer
  moboSerial.begin(115200);
  ET.begin(details(gps_data), &moboSerial);
  delay(5000);
  
  // Start GPS parse object
  GPS_setup(GPS, gps_data);
  delay(1000);
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  char c = GPS.read();
  
  // if true and valid, print raw gps data to serial monitor
  if ((c) && (GPSECHO))
    Serial.write(c); 
         
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every [data_delay] milliseconds or so, print out the current stats
  if (millis() - timer > data_delay) { 
    timer = millis(); // reset the timer
    
    gps_data.fix = GPS.fix;
    if (GPS.fix){
      gps_data.fixquality = GPS.fixquality;
      gps_data.satellites = GPS.satellites;
      gps_data.latitude_fixed = GPS.latitude_fixed;
      gps_data.longitude_fixed = GPS.longitude_fixed;
      gps_data.altitude = GPS.altitude;
      gps_data.speed = GPS.speed;
      gps_data.angle = GPS.angle;
      
      // Adjust latitude_fixed and longitude_fixed to reflect which hemispheres GPS is in (eliminates need for lat and lon)
      if (GPS.lat == 'S') {
        gps_data.latitude_fixed = -1 * gps_data.latitude_fixed;
      }
      if (GPS.lon == 'W') {
        gps_data.longitude_fixed = -1 * gps_data.longitude_fixed;
      }
    
    // ??Include time to know when last successful transmission was??
//    Serial.print("\nTime: ");
//    Serial.print(GPS.hour, DEC); Serial.print(':');
//    Serial.print(GPS.minute, DEC); Serial.print(':');
//    Serial.print(GPS.seconds, DEC); Serial.print('.');
//    Serial.println(GPS.milliseconds);
//    Serial.print("Date: ");
//    Serial.print(GPS.day, DEC); Serial.print('/');
//    Serial.print(GPS.month, DEC); Serial.print("/20");
//    Serial.println(GPS.year, DEC);
     }
     
    // if true and valid, print parsed gps data to serial monitor 
    if (TOSTRING){
      if(gps_data.fix){
        gps_data.ToString();
      }else{
        Serial.println("NO FIX");
      }
    }
    
    // send data to motherboard via EasyTransfer
    ET.sendData();
  }
}
