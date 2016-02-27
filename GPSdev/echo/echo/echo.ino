// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
// using MTK33x9 chipset
//    ------> http://www.adafruit.com/products/746

#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground'''';;';
// If using software serial (sketch example default):
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
// If using hardware serial (e.g. Arduino Mega):
//   Connect the GPS TX (transmit) pin to Arduino RX1, RX2 or RX3
//   Connect the GPS RX (receive) pin to matching TX1, TX2 or TX3

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);

// If using hardware serial (e.g. Arduino Mega), comment
// out the above lines and enable this line instead:
//Adafruit_GPS GPS(&Serial1);

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

GPS_Data gps_data;
#define data_delay 50

void GPS_setup(Adafruit_GPS &GPS, GPS_Data &gps_data)
{
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  
  //setting default values for GPS data
  gps_data.fix = GPS.fix = 0;
  gps_data.latitude_whole = 0;
  gps_data.latitude_frac = 0;
  gps_data.longitude_whole = 0;
  gps_data.longitude_frac = 0;
  gps_data.altitude_whole = 0;
  gps_data.altitude_frac = 0;
  gps_data.lat = 'X';
  gps_data.lon = 'X';
  gps_data.satellites = 0;
  
  //settings for GPS timer
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

SIGNAL(TIMER0_COMPA_vect)
{
  char c = GPS.read(); 
}

void setup()  
{    
  Serial.begin(9600);
  Serial.println("Adafruit GPS library basic test!");
  GPS_setup(GPS, gps_data);

  delay(1000);
  
}//end setup

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
    
    if(GPS.fix)
    {
      gps_data.latitude_whole = GPS.latitude;
      gps_data.latitude_frac = (GPS.latitude-gps_data.latitude_whole)*1000;
      gps_data.lat = GPS.lat;
      gps_data.longitude_whole = GPS.longitude;
      gps_data.longitude_frac = (GPS.longitude-gps_data.longitude_whole)*1000;
      gps_data.lon = GPS.lon;
      gps_data.altitude_whole = GPS.altitude;
      gps_data.altitude_frac = (GPS.altitude-gps_data.altitude_whole)*1000; 
      gps_data.satellites = GPS.satellites;
    }
   
  Serial.print("gps_data.fix: "); 
  Serial.println(gps_data.fix);
  Serial.print("gps_data.latitude_whole: ");
  Serial.println(gps_data.latitude_whole);
  Serial.print("gps_data.latitude_frac: ");
  Serial.println(gps_data.latitude_frac);
  Serial.print("gps_data.longitude_whole: ");
  Serial.println(gps_data.longitude_whole);
  Serial.print("gps_data.longitude_frac: ");
  Serial.println(gps_data.longitude_frac);
  Serial.print("gps_data.altitude_whole: ");
  Serial.println(gps_data.altitude_whole);
  Serial.print("gps_data.altitude_frac: ");
  Serial.println(gps_data.altitude_frac);
  Serial.print("gps_data.lat: ");
  Serial.println(gps_data.lat);
  Serial.print("gps_data.lon: ");
  Serial.println(gps_data.lon);
  Serial.print("gps_data.satellites: ");
  Serial.println(gps_data.satellites);
} //end loop





