const int CCD_HEADER_END_INDEX     = 32;
const int CCD_PIXEL_END_INDEX      = 3648 + CCD_HEADER_END_INDEX;
const int CCD_FOOTER_END_INDEX     = 14 + CCD_PIXEL_END_INDEX;
const int CCD_CLEANUP_START        = 11 + (CCD_FOOTER_END_INDEX * 4) + 11;  
const int CCD_TOTAL_MASTER_TICKS   = CCD_CLEANUP_START + 17;              

const uint8_t PIN_2 = 0b00000100;
const uint8_t PIN_2_LOW_MASK = 0b00000000;
const uint8_t PIN_2_HIGH_MASK = 0b00000100;

volatile int master_clock_tick_count = 0;
volatile int shutter_tick_count = 0;
volatile bool shift_toggle = LOW;
volatile bool image_read_complete = false;

const uint8_t PIN_0 = 0b00000000;
const uint8_t PIN_0_LOW_MASK = 0b00000000;
const uint8_t PIN_0_HIGH_MASK = 0b00000001;

int ccd_packet_data_buffer[CCD_FOOTER_END_INDEX];


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
    i++;
  
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
    };
  
    int current_element = ((i - 3) / 4);
    if(((i - 3) % 4) == 0)
    {
      //digitalWrite(SHIFT_DATA_CCD_PIN, shift_toggle);
      if(shift_toggle == HIGH)
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_2, PIN_2_HIGH_MASK);
      else if(shift_toggle == LOW)
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, PIN_2, PIN_2_LOW_MASK);
      shift_toggle = !shift_toggle;
      ccd_packet_data_buffer[current_element] = analogRead(32);
    }
  
    if(i > CCD_TOTAL_MASTER_TICKS)
    {
      image_read_complete = true;
    }
  }
  msdelay = micros() - msdelay;
  Serial.println(msdelay); 
}

