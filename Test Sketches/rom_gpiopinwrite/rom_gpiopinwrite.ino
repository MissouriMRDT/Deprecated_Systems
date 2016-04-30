
#define bitA 0
#define portA 0
#define portBaseA 0
#define GPIO_DATA 0x00000000
int name = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  name = portBaseA + (GPIO_DATA + bitA << 2);
}

void loop()
{
  int msdelay = micros();
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 1000; i++)
    ROM_GPIOPinWrite(portBaseA, bitA, 1);
  msdelay = micros() - msdelay;
  Serial.println(msdelay);
}
