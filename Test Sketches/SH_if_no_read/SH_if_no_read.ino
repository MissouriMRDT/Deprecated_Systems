bool shift_toggle; 
const uint8_t PIN_2 = 0b00000100;
const uint8_t PIN_2_LOW_MASK = 0b00000000;
const uint8_t PIN_2_HIGH_MASK = 0b00000100;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  int msdelay = micros();
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 1000; i++)
  {
    int current_element = ((i - 3) / 4);
    if(((i - 3) % 4) == 0)
    {
      //digitalWrite(SHIFT_DATA_CCD_PIN, shift_toggle);
      if(shift_toggle == HIGH){
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_2, PIN_2_HIGH_MASK);
      }
      else if(shift_toggle == LOW){
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_2, PIN_2_LOW_MASK);
      }
      shift_toggle = !shift_toggle;
    }
  }
  msdelay = micros() - msdelay;
  Serial.println(msdelay); 
}
