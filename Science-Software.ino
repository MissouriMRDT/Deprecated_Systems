// Sensor libraries
#include "Energia.h"
#include <SHT10.h>
#include <StellarisDS18B20.h>

void setup(){}
void loop(){}

float RoveSci_DS18B20_ReadTemp(int data_pin)
{
  int DS18B20_Pin = data_pin;
  DS18B20 ds(DS18B20_Pin); // split into DS18B20_Begin? removes param
  return float(ds.GetData());
}

int RoveSci_Grove_ReadHumid(int data_pin)
{
  int sensorValue = analogRead(data_pin) * 100 / 4095;
  return  sensorValue;
}

int RoveSci_FC28_ReadHumid(int data_pin)
{
  int percentage = -(analogRead(data_pin) - 4095) * 100 / 1850;
  if (percentage >= 100)
    Serial.println(100);
  else
    Serial.println(percentage); 
}

float RoveSci_SHT10_ReadTemp(int data_pin, int clock_pin)
{
  SHT10 sht(data_pin, clock_pin); // same deal as DS18B20
  return sht.readTemperature(); 
}

float RoveSci_SHT10_ReadHumid(int data_pin, int clock_pin)
{
  SHT10 sht(data_pin, clock_pin);
  return sht.readHumidity(); 
}
