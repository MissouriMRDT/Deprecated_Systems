#include "Energia.h"
#include "SHT10.h"

int SHT10_Data_Pin = 26;    // PE_3
int SHT10_Clock_Pin = 25;   // PE_2
SHT10 sht(SHT10_Data_Pin, SHT10_Clock_Pin);

void setup()
{
  Serial.begin(9600);
 }
void loop()
{
  float temperature = sht.readTemperature();
  float humidity = sht.readHumidity();
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
}
