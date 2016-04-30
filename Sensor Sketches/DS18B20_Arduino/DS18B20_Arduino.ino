#include <OneWire.h>

int DS18S20_Pin = 10; // DS18S20 Signal pin on digital 2
                     // Will be different for Tiva board

// Temperature chip i/o
OneWire ds(DS18S20_Pin); // on digital pin 2

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  float temperature = getTemp();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  delay(100); // just here to slow down the output so it is easier to read
  
}

float getTemp(){
  // return the temperature from one DS18S20 in DEG Celsius
  
  byte data[12];
  byte addr[8];
  
  ds.reset();
 // ds.select(addr);
  ds.write(0xCC); // Broadcasting to all devices. Should find singular address
  ds.write(0x44,1); // start conversion, with parasite power on at the end
  
  byte present = ds.reset();
//  ds.select(addr);
  ds.write(0xCC); // Broadcasting to all devices. Should find singular address
  ds.write(0xBE); // Read Scratchpad
  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
   data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];
  
  float tempRead = ((MSB << 8) | LSB); // using two's complement 
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
