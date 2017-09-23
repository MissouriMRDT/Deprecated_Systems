void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int reading = analogRead(PK_1);
  float voltage = (reading * 5.0) / 4095.0;
  
  Serial.print(voltage); Serial.println(" volts");
  
  Serial.print(reading); Serial.println(" analog reading");
  
  delay(2000);
}
