const int MASTER_PIN = 7;
const int SHIFT_PIN = 37;
const int ICG_PIN = 38;

uint8_t MASTER_BIT;
uint8_t MASTER_PORT;
uint32_t MASTER_PORTBASE;

uint8_t SHIFT_BIT;
uint8_t SHIFT_PORT;
uint32_t SHIFT_PORTBASE;

uint8_t ICG_BIT;
uint8_t ICG_PORT;
uint32_t ICG_PORTBASE;

void setup()
{
  
  
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  MASTER_BIT = digitalPinToBitMask(MASTER_PIN);
  //uint8_t MASTER_PIN_MASK = val ? bit : 0; 
  MASTER_PORT = digitalPinToPort(MASTER_PIN);
  MASTER_PORTBASE = (uint32_t) portBASERegister(SHIFT_PIN);
  
  SHIFT_BIT = digitalPinToBitMask(SHIFT_PIN);
  //uint8_t MASTER_PIN_MASK = val ? bit : 0; 
  SHIFT_PORT = digitalPinToPort(SHIFT_PIN);
  SHIFT_PORTBASE = (uint32_t) portBASERegister(SHIFT_PIN);
  
  ICG_BIT = digitalPinToBitMask(ICG_PIN);
  //uint8_t MASTER_PIN_MASK = val ? bit : 0; 
  ICG_PORT = digitalPinToPort(ICG_PIN);
  ICG_PORTBASE = (uint32_t) portBASERegister(ICG_PIN);
  
}

void loop()
{
  Serial.print("Master Pin: ");
  Serial.println(MASTER_PIN);
  Serial.print("Master Bit: ");
  Serial.println(MASTER_BIT);
  Serial.print("Master Portbase: ");
  Serial.println(MASTER_PORTBASE);
  
  Serial.print("Shift Pin: ");
  Serial.println(SHIFT_PIN);
  Serial.print("Shift Bit: ");
  Serial.println(SHIFT_BIT);
  Serial.print("Shift Portbase: ");
  Serial.println(SHIFT_PORTBASE);
  
  Serial.print("ICG Pin: ");
  Serial.println(ICG_PIN);
  Serial.print("ICG Bit: ");
  Serial.println(ICG_BIT);
  Serial.print("ICG Portbase: ");
  Serial.println(ICG_PORTBASE);
  /* 
  Serial.print("GPIO_PORTA_BASE: ");
  Serial.println(GPIO_PORTA_BASE);
  Serial.print("GPIO_PORTB_BASE: ");
  Serial.println(GPIO_PORTB_BASE);
  Serial.print("GPIO_PORTC_BASE: ");
  Serial.println(GPIO_PORTC_BASE);
  Serial.print("GPIO_PORTD_BASE: ");
  Serial.println(GPIO_PORTD_BASE);
  Serial.print("GPIO_PORTE_BASE: ");
  Serial.println(GPIO_PORTE_BASE);
  Serial.print("GPIO_PORTF_BASE: ");
  Serial.println(GPIO_PORTF_BASE); */
}


/* void digitalWrite(uint8_t pin, uint8_t val)
{
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t mask = val ? bit : 0;
    uint8_t port = digitalPinToPort(pin);
    uint32_t portBase = (uint32_t) portBASERegister(port);
    
    if (port == NOT_A_PORT) return;

    ROM_GPIOPinWrite(portBase, bit, mask);
} */
// GPIOPinWrite(uint32_t ui32Port, uint8_t ui8Pins, uint8_t ui8Val)
// HWREG(ui32Port + (GPIO_O_DATA + (ui8Pins << 2))) = ui8Val;

// MASTER PIN:
// HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + (16 << 2))) = 1; 

// ICG PIN:
// HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + (8 << 2))) = 1;

// SH PIN: 
// HWREG(GPIO_PORTC_BASE + (GPIO_O_DATA + (16 << 2))) = 1;
