void setup()
{
  Serial.begin(9600);
  OCR2A = 128;
  DDRB = 0b00101000;// set PWM pin as output
  PORTB = 0x0;
}

void loop()
{
  if(Serial.available())
  {
    OCR2A = Serial.read();
  }
}
