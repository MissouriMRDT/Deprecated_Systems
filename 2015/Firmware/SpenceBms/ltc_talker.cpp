#include "arduino/SPI.h"
#include "ltc_talker.h"
#include "bms_defines.h"

byte ltcResponse[18];
float cellVoltage[NUM_CELLS];
uint8_t	pecVAL;
uint8_t pecIN;

//uint8_t CONFIG_REGISTER[] = { CFGR0, CFGR1, CFGR2, CFGR3, CFGR4, CFGR5 };

void ltcInit()
{
	PORTB &= ~(SS_PIN);	
	SPI.transfer(WRCFG);													//Tell them we want to write to config registers
//	SPI.transfer(WRCFG_PEC);
	PORTB &= ~(SS_PIN);
}

void getLtsResponse()
{
	PORTB &= ~(SS_PIN);	
	
	SPI.begin();
	SPI.transfer(STCVAD);
//	SPI.transfer(STCVAD_PEC);
	delay(30); /* wait at least 12ms according to datasheet */
	SPI.transfer(LTC_ADDRESS);
	SPI.transfer(RDCV);
//	SPI.transfer(RDCV_PEC);
	
	for(int i = 0; i < 18; ++i )
	{
		ltcResponse[i] = SPI.transfer(RDCV);
//		ltc6803PEC(ltcResponse[i]);
	}

	PORTB |= (SS_PIN);
	//digitalWrite(SS_PIN, HIGH);

	decodeVoltage();
}

void decodeVoltage()
{
	byte tempByte;
	int tempInt;
	
	tempByte = ltcResponse[1] << 4;
	tempInt = (int)tempByte;
	cellVoltage[0] = ltcResponse[0] + (tempInt << 4);
	
	tempByte = ltcResponse[1] >> 4;
	tempInt = (int)ltcResponse[2];
	tempInt = tempInt << 4;
	cellVoltage[1] = tempInt + tempByte;
	
	tempByte = ltcResponse[4] << 4;
	tempInt = (int)tempByte;
	cellVoltage[2] = ltcResponse[3] + (tempInt << 4);
	
	tempByte = ltcResponse[4] >> 4;
	tempInt = (int)ltcResponse[5];
	tempInt = tempInt << 4;
	cellVoltage[3] = tempInt + tempByte;
	
	tempByte = ltcResponse[7] << 4;
	tempInt = (int)tempByte;
	cellVoltage[4] = ltcResponse[6] + (tempInt << 4);
	
	tempByte = ltcResponse[7] >> 4;
	tempInt = (int)ltcResponse[8];
	tempInt = tempInt << 4;
	cellVoltage[5] = tempInt + tempByte;
	
	tempByte = ltcResponse[10] << 4;
	tempInt = (int)tempByte;
	cellVoltage[6] = ltcResponse[9] + (tempInt << 4);

	tempByte = ltcResponse[10] >> 4;
	tempInt = (int)ltcResponse[11];
	tempInt = tempInt << 4;
	cellVoltage[7] = tempInt + tempByte;
}

void ltc6803PEC(uint8_t val)
{
	uint8_t curBit = 0;												//8-bit value with the current bit in its LSB
	for(uint8_t i = 0; i < 8; i++)									//Loop through every bit in the byte
	{
		curBit   = (val >> (7-i)) & 0x01;							//Isolate the the (i-1)th bit of val
		pecIN    = curBit ^ ((pecVAL >> 7) & 0x01);					//Initialize pecIN to (0b0000000X where X is curBit) XOR MSB of PEC
		pecIN   |= ((pecVAL & 0x01) ^ (pecIN & 0x01)) << 1;			//Magic 		(IN1 = PEC[0] XOR IN0)
		pecIN   |= (((pecVAL >> 1) & 0x01) ^ (pecIN & 0x01)) << 2; 	//More magic 	(IN2 = PEC[1] XOR IN0)
		pecVAL	 = ((pecVAL << 1) & ~0x07) | pecIN;					//Set the current PEC value
	}
}
