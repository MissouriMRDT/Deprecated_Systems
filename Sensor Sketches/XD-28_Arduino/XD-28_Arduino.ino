int sensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t sensorValue = (-static_cast<int32_t>(analogRead(sensorPin)) + 1023) * 100 / 706;
  if(sensorValue >= 100)
    Serial.println(100);
  else
    Serial.println(sensorValue);
}
