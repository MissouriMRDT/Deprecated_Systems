void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop()
{
  // put your main code here, to run repeatedly:
  int reading = analogRead(port_here);   //whichever port is being read from
  
  Serial.print("Analog Output: "); Serial.println(reading);
  
  float voltage = ((reading * 5.0) / 4095); //calculating voltage
  
  Serial.print("Voltage Output: "); Serial.println(voltage); //use to troubleshoot voltage
  
  //create a formula of percent moisture based on analog output and voltage output
  //float moisture = ...
  
  //Serial.print(moisture); Serial.println("%");
  
  delay(2000);
}


