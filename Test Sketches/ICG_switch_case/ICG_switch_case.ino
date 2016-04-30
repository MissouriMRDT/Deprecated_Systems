const int CCD_CLEANUP_START = 22 + (3648 + 14 + 32)*4;
const uint8_t PIN_0 = 0b00000000;
const uint8_t PIN_0_LOW_MASK = 0b00000000;
const uint8_t PIN_0_HIGH_MASK = 0b00000001;

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
    switch(i)
    {
    case 2:
      //digitalWrite(INTEGRATE_DATA_CCD_PIN, LOW);
      ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_0, PIN_0_LOW_MASK);
      break;
    case 11:
      //digitalWrite(INTEGRATE_DATA_CCD_PIN, HIGH);
      ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_0, PIN_0_HIGH_MASK);
      break;
    case CCD_CLEANUP_START:
      //digitalWrite(INTEGRATE_DATA_CCD_PIN, LOW);
      ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_0, PIN_0_LOW_MASK);
      break;
    case CCD_CLEANUP_START + 9:
      //digitalWrite(INTEGRATE_DATA_CCD_PIN, HIGH);
      ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_0, PIN_0_HIGH_MASK);
      break;
    default:
      break;
    }
  }
  msdelay = micros() - msdelay;
  Serial.println(msdelay); 
}
