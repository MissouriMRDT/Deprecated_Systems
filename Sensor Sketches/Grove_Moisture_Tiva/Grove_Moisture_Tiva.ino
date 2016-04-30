int sensorPin = 26;    // PE_3
int sensorValue = 0;  // variable to store the value coming from the sensor
 
void setup() {
  // declare the ledPin as an OUTPUT:
   Serial.begin(9600);  
}
 
void loop() {
  // read the value from the sensor:
  sensorValue = -(analogRead(sensorPin) - 4095) * 100 / 2185;
  if(sensorValue >= 100)
    Serial.println(100);                   
  Serial.println(sensorValue);
  delay(100);  
}
