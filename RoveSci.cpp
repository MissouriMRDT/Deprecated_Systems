#include <SHT10.h>
#include <StellarisDS18B20.h>
#include "Arduino.h"

float roveSci_DS18B20_ReadTemp(int data_pin) {
  int DS18B20_Pin = data_pin;
  DS18B20 ds(DS18B20_Pin); // split into DS18B20_Begin? removes param
  return float(ds.GetData());
}

int16_t roveSci_Grove_ReadHumid(int data_pin) {
  int16_t sensorValue = analogRead(data_pin) * 100 / 4095;
  return  sensorValue;
}

int16_t roveSci_FC28_ReadHumid(int data_pin) {
  int16_t percentage = -(analogRead(data_pin) - 4095) * 100 / 1850;
  if (percentage >= 100)
	return 100;
  else
    return percentage
}

float roveSci_SHT10_ReadTemp(int data_pin, int clock_pin) {
  SHT10 sht(data_pin, clock_pin); // same deal as DS18B20
  return sht.readTemperature(); 
}

int16_t roveSci_SHT10_ReadHumid(int data_pin, int clock_pin) {
  SHT10 sht(data_pin, clock_pin);
  return static_cast<int16_t>(sht.readHumidity()); 
}