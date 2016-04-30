#define whatever 0x01

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
  for(int i = 0; i < 1000; i++)
    digitalWrite(whatever, HIGH);
  msdelay = micros() - msdelay;
  Serial.println(msdelay);
  return;
}
