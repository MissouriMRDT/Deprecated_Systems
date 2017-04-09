//const int TMP36Pin = PB_5;    // pin
const float analogRes = 4095; // A/D resolution


void setup()
{
  Serial.begin(9600);
  Serial.println("Starting temperature readings...");
  //pinMode (PB_5, INPUT);
}

void loop()
{
  // Get the output from the sensor and multiply it by
  // 3.3V / resolution to get the voltage.  Note that
  // I am using 3.24V since that is what I read on my DMM.

  float voltage = (analogRead(PB_5) / analogRes);
  
  // TMP36 datasheet provides the conversion formula
  //float degC = (voltage - 0.5) * 100.0;
  float degC = (voltage * 165) - 40;
  
  // and if fahrenheit is desired
  float degF = (degC * 1.8) + 32.0;

  // Now the serial output...
  Serial.println("___________________________________________");
  Serial.print("Analog Read:     "); Serial.println(analogRead(PB_5));
  Serial.print("Voltage:         "); Serial.println(voltage,3);
  Serial.print("Temperature (C): "); Serial.println(degC,1);
  Serial.print("Temperature (F): "); Serial.println(degF,1);

  delay(2000); 
}

