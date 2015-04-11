/*
 * RoverBMS.cpp
 *
 * Created: 7/22/2014 10:42:00 PM
 *  Author: Chris
 */ 


#include <avr/io.h>
#include "Arduino/Arduino.h"
#include "Arduino/SPI.h"

#define LTC_ADDRESS 0x80
#define SPI_PIN     10
#define SDI			11
#define SDO			12

#define STCVAD 0x10 // Start all A/D's - poll status'
#define RDCV 0x04 // Read cells

#define NUM_CELLS 8

byte ltcResponse[18];
float cellVoltage[NUM_CELLS];

void setup();
void loop();

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }
	
void setupLTC();
void readVoltage();
void decodeVoltage();

int main(void)
{
	// Start the platform
	init();
	initVariant();
	USBDevice.attach();

	// Call setup
	setup();
	
	while (1)
	{
		// Main loop function
		loop();
		
		// Check for USB serial events
		if (serialEventRun)
		{
			serialEventRun();
		}
	}
	return 0;
}

void setup()
{
	Serial.begin(115200);
	setupLTC();	
}

void setupLTC()
{
	  pinMode(SPI_PIN, OUTPUT);
	  pinMode(SDI, OUTPUT);
	  pinMode(SDO, INPUT);
	  pinMode(13, OUTPUT);

	  digitalWrite(SPI_PIN, HIGH);
	  SPI.setBitOrder(MSBFIRST);
	  SPI.setDataMode(SPI_MODE3);
	  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop()
{
	Serial.println("OK!");
	Serial.println(cellVoltage[0]);
	delay(100);
}

void readVoltage()
{
	//extern byte ltcResponse[18];

	digitalWrite(SPI_PIN, LOW);

	SPI.transfer(STCVAD);
	delay(20); /* wait at least 12ms according to datahseet */
	SPI.transfer(LTC_ADDRESS);
	SPI.transfer(RDCV);
	
	for(int i = 0; i < 18; ++i )
	{
		ltcResponse[i] = SPI.transfer(RDCV);
	}

	digitalWrite(SPI_PIN, HIGH);

	decodeVoltage();
}

void decodeVoltage()
{
	byte tempByte;
	int tempInt;

	for(int i = 0; i < NUM_CELLS; ++i )
	{
		switch(i % 2)
		{
			case 0:
			tempByte = ltcResponse[i] << 4;
			tempInt  = (int)ltcResponse[i+1];
			cellVoltage[i] = tempInt + tempByte;
			break;

			case 1:
			tempByte = ltcResponse[i] >> 4;
			tempInt  = (int)ltcResponse[i+1];
			tempInt  = tempInt << 4;
			cellVoltage[i] = tempInt + tempByte;
			break;
		}
	}
}
