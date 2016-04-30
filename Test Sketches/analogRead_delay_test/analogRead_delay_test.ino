void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  int reading = 0;
  int msdelay = micros();
  // put your main code here, to run repeatedly:
    reading = analogRead(27);
  msdelay = micros() - msdelay;
  Serial.println(msdelay);
}
