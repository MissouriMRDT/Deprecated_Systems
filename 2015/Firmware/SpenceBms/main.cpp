#include "Arduino/Arduino.h"
#include "Arduino/SPI.h"
#include <avr/io.h>

#include "pin_defines.h"
#include "bms_defines.h"
#include "ltc_talker.h"

void setup();
void loop();

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }
	
#define ROVER_ESTOP_PORT PORTD
#define ROVER_ESTOP_PIN  PRTD4

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
}

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	
//	delay(1000);
	
	DDRE = ROVER_POWER_SWITCH_PIN;
	DDRB = SS_PIN;
	PORTE = ROVER_POWER_SWITCH_PIN;
	
	/*
	PORTB |= 0b00000110;
	PORTB |= SS_PIN;
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV16);
	
	delay(100);
	
	PORTB &= ~(SS_PIN);
	SPI.begin();
	SPI.transfer(WRCFG);
	SPI.transfer(CFGR0);
	SPI.transfer(WRCFG);
	SPI.transfer(WRCFG_PEC);
	SPI.end();
	PORTB |= (SS_PIN);
	
	*/
	
	DDRD &= ~ROVER_ESTOP_PIN;
	PORTD |= ROVER_ESTOP_PIN;
	ROVER_ESTOP_PORT |= ROVER_ESTOP_PIN;
	
//	Serial.println("Finished setup");
}

void loop() {
	byte portRead;
	
	portRead = PIND;
	portRead &= ROVER_ESTOP_PIN;
	if( portRead )	
	{
		PORTE &= ~(ROVER_POWER_SWITCH_PIN);
	}
	else
	{
		PORTE |= ROVER_POWER_SWITCH_PIN;
	}
	
	/*
	uint8_t i;
	extern float cellVoltage[NUM_CELLS];
	
	getLtsResponse();
	
	Serial.println("~~~~~~~~~~~~~~~");
	
	for(i = 0; i < NUM_CELLS; ++i)
	{
		Serial.println(cellVoltage[i]);
	}
	Serial.println("----------------");
	delay(1000);
	*/
}
