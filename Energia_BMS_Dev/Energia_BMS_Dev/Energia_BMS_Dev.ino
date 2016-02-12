//MSP 432 / LTC 6803 / ACS 770

//Josh Jetter Notes
//LTC 6803 Voltage/Temp Monitoring
//CSBI (chip select (ie data read)), SDO (serial out), SDI (serial in), SCKI (clock in)

//User Interface
//Estop1 (432P.1.5) If it's at 0 turn pack Gate ON (5v turn off)
//Estop2 (432P.1.6)
//Do we 'and' these or 'or' them?
//Active Drain (idles at 3.3 with pull up resistor)
///////////////////////////////////

//SCK   P1_5    7
//MISO  P1_7    14
//MOSI  P1_6    15
//CS    P5_7    18

void setup()
{
  // put your setup code here, to run once:
  
}

void loop()
{
  // put your main code here, to run repeatedly:
  
}
