// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_tivaWrappers.h
//
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare
#ifndef ROVEWARE_TIVAWRAPPERS_H_
#define ROVEWARE_TIVAWRAPPERS_H_

//mrdt::rovWare Horizon Protocol Definitions
#include "roveWare_Protocol.h"

//C lib
#include <stdio.h>

//TI hardware access routines
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>

//TODO wtf
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//mrdt shorthand
#define ERROR -1
#define HIGH 1
#define LOW 0

#define TEST_DEVICE_PIN 0
#define TRI_STATE_PIN   1

//Tiva Get/Set Wrappers
void roveDigital_Write(int tiva_pin, int high_or_low);
void rovePWM_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds);
int roveUART_Write(int tiva_pin, char* write_buffer, int bytes_to_write);
int roveUART_Read(int tiva_pin, char* read_buffer, int bytes_to_read);

//TODO ?? get the system clock for the delay
void roveDelay_MilliSec(uint32_t milliseconds);
void roveDelay_MicroSec(uint32_t microseconds);

//roveWare 2016
int16_t roveGetPinNum_ByDeviceId(uint8_t data_id);
void rovePrintf_ByByteBuffer(uint8_t* printf_buffer, int16_t bytes_to_printf);

//roveWare 2015
int16_t roveGetByteCnt_ByStructId(uint8_t struct_id);
//TODO sysctl.h
//*****************************************************************************
//! Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock, which is
//! also the clock rate of the peripheral modules (with the exception of
//! PWM, which has its own clock divider; other peripherals may have different
//! clocking, see the device data sheet for details).
//!
//! \note This cannot return accurate results if SysCtlClockSet() has not
//! been called to configure the clocking of the device, or if the device is
//! directly clocked from a crystal (or a clock source) that is not one of the
//! supported crystal frequencies.  In the latter case, this function should be
//! modified to directly return the correct system clock rate.
//!
//! \note This function can only be called on TM4C123 devices.  For TM4C129
//! devices, the return value from SysCtlClockFreqSet() indicates the system
//! clock frequency.
//!
//! \return The processor clock rate for TM4C123 devices only.
//*****************************************************************************
#endif //ROVEWARE_TIVAWRAPPERS_H_
