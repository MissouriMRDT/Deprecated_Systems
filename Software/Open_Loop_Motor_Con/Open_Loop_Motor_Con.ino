void setup()
{
  Serial.begin(9600);
  TCCR2A = 0b10000001;
  TCCR2B = 0b00000001;
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
