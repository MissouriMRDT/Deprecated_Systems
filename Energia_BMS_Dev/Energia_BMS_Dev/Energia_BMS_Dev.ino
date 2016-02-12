//////////////////MSP 432 / LTC 6803 / ACS 770

/////////////////Jetter Notes : LTC 6803 Voltage/Temp Monitoring IC
//SCKI (clock in)
//SDI (serial in)
//SDO (serial out)
//CSBI (chip select (ie data read))


////////////////Jetter Notes : MSP 432 MicrController
//Estop1 (432P.1.5) If it's at 0 turn pack Gate ON (5v turn off)
//Estop2 (432P.1.6)
//Wait...Do we 'and' or 'or' the Estops Active Drain (idles at 3.3 with pull up resistor)?
//SCKI  P6_3    WHAT?
//MISO  P6_5    9
//MOSI  P6_4    10
//CSBI  P6_2    WHAT?


#include <SPI.h>

//P1_5
#define ESTOP_ONE 7

/////////////////Judah Notes : MSP 432 MicrController lists the PinOuts as:
//Wait...these don't match Jetter at all and actually conflict with Jetter Pinouts?
//SCK   P1_5    7
//MISO  P1_7    14
//MOSI  P1_6    15
//CS    P5_7    18

//http://energia.nu/wordpress/wp-content/uploads/2015/03/MSP432-LaunchPad-%E2%80%94-Pins-Maps.jpg

void setup() 
{
  SPI.begin(); 
  pinMode(ESTOP_ONE, INPUT);
  SPI.transfer(TODO_DATA_BMS_OFF);
  
}//end setup

void loop() 
{
 
  if(digitalRead(ESTOP_ONE) )
  {
    SPI.transfer(TODO_DATA_BMS_OFF);
  }//end if
  
}//end loop

