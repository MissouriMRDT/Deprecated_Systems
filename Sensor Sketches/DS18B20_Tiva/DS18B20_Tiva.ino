#include <StellarisDS18B20.h>

  int DS18B20_Pin = 26;  // DS18B20 Signal pin on PE3
  DS18B20 ds(DS18B20_Pin); // on pin PE3

void setup(){
  Serial.begin(9600);  
}

void loop()
{ 
  delay(10);
  float temperature = ds.GetData();
  Serial.println(temperature);
}


