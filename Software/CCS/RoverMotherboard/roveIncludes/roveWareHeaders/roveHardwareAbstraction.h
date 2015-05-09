// roveHardwareAbstraction.h MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad jrs6w7@mst.edu

#ifndef ROVEHARDWAREABSTRACTION_H_
#define ROVEHARDWAREABSTRACTION_H_

// globally scoped Texas Instruments (TI) headers

#include "../RoverMotherboardMain.h"

// MRDesign Team::roveWare::		roveCom and RoveNet services headers

#include "../mrdtRoveWare.h"

//HARDWARE ABSTRACTION FUNCTIONS

//pass a device struct id (#define from mrdtRoveWare.h) as an int, and returns the rs485 jack as an int

int getDeviceJack(int device);

// pinMode sets a pin to be input or output.
// inputs:
// 	pin - name of the pin. Can be found in rovePinMap.h or the eagle file
// 	mode - INPUT or OUTPUT
// outputs:
// 	none
// pre: GPIO modules loaded into RTOS
// post: Pin can now be used for specified mode
//
// usage example: digitalWrite(U3_MUX_S0, OUTPUT);

void pinMode(int pin, int mode);

// digitalWrite sets a bit to be on or off
// inputs:
// 	pin - name of the pin. Can be found in rovePinMap.h or the eagle file
// 	val - HIGH or LOW
// outputs:
// 	none
// pre: pin has been set to mode OUTPUT by pinMode
// post: Pin is set to on or off
//
// usage example: digitalWrite(U3_MUX_S0, HIGH);

void digitalWrite(int pin, int val);

PWM_Handle rovePWMInit(PWM_Handle pwm_index, uint16_t period_in_microseconds);

void pwmWrite(PWM_Handle pin, int val);

void DriveMotor(PWM_Handle motor, int speed);

// deviceWrite sends data passed to it to the specified RS485 jack.
// It will deal with properly muxing to the device and writing to the uart
//    internally
// inputs:
// 	rs485jack - number of the jack to write to (0-18)
// 	buffer - where to get the data from
// 	bytes_to_write - number of bytes to write
// outputs:
// 	returns number of bytes written.
// 		-1 for invalid device.
// 		UART_ERROR for, well, a uart error
// pre: GPIO pins and UARTS have been initialized
// post: mux is set to correct settings for specified rs485 jack, data
// 	sent to device over UART
//
// usage example:
// 	buffer[15] = "My Buffer";
// 	deviceWrite(14, buffer, 15); //Write "My Buffer" to device on jack 14

int deviceWrite(int rs485jack, char* buffer, int bytes_to_write);

int UART_read_nonblocking (UART_Handle uart, char* buffer, int bytes_to_read, int timeout);

// deviceRead Retrieves a specified number of bytes from
// It will deal with properly muxing to the device and writing to the uart
//    internally
// inputs:
// 	rs485jack - number of the jack to write to (0-18) on ONBOARD_ROVECOMM
// 	buf_len - size of the buffer
// 	timeout: number of milliseconds to wait before moving abandoning the read
// 		and returning an error. Also accepts BIOS_WAIT_FOREVER
// outputs:
// 	returns number of bytes read.
// 		-1 for invalid device.
// 		UART_ERROR for, well, a uart error
// 	buffer: Overwritten with the data recieved from uart, and null terminated
// pre: muxes have been set up & UARTS are initialized
// post:mux is set to correct settings for specified rs485 jack, data
// 	recieved from device UART
//
// usage example:
// 	buffer[15];
// 	deviceRead(13, buffer, 1, BIOS_WAIT_FOREVER);
// 	switch(buffer[1])
// 	{
// 		case MY_STRUCT_ID: //This should be defined
// 			deviceRead(13, buffer, sizeof(struct my_struct), BIOS_WAIT_FOREVER);
// 			break;
// 	}
int deviceRead(int rs485jack, char* buffer, int bytes_to_read, int timeout);

// Generates a command to drive a motor controller and places it in the buffer
// This buffer can then be written to a motor controller with deviceWrite
//
// inputs:
// 	speed: 0 - 10000
// outputs:
//  number of bytes in command is returned
// 	buffer is filled with command data
//
// pre: buffer is big enough to handle the command. ~10 bytes should be good
// post: Buffer is filled with command, number of bytes in buffer returned
//
// usage example - set motor connected to MOTOR_JACK to half speed:
//    int size;
//    char buffer[50];
//    size = generateMotorCommand(5000, buffer);
//    DeviceWrite(MOTOR_JACK, buffer, size);

int generateMotorCommand(int speed, char* buffer);

//HARDWARE INITIALIZATION FUNCTIONS

// makes all uarts usable

void initUarts();

// sets all gpio mux pins usable

void initMuxGPIO();

#endif // ROVEHARDWAREABSTRACTION_H_
