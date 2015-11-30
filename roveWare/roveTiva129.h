// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare
#ifndef ROVETIVA129_H_
#define ROVETIVA129_H_

//mrdt::rovWare Horizon Protocol Definitions
//#include "roveProtocol.h"

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
enum RoveHw1294ShortHand {

    HW_ERROR_FREE = 1
    , HW_ERROR = -1
    , HW_TEST_DEVICE_PIN = 0
    , HW_TEST_DEVICE_ID = 0
    , HW_TRI_STATE_PIN = 1
};//end enum

//DevDec16
void rovePrintf_ByByteBuffer(uint8_t* printf_buffer, int32_t bytes_to_printf);
int32_t roveGetPinNum_ByDeviceId(int32_t data_id);

//Tiva Get/Set Wrappers
void roveDigital_Write(int32_t tiva_pin, int32_t high_or_low);
void rovePwm_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds);
int32_t roveUart_Write(int32_t tiva_pin, uint8_t* write_buffer, int32_t bytes_to_write);
int32_t roveUart_Read(int32_t tiva_pin, uint8_t* read_buffer, int32_t bytes_to_read);

//TODO ?? get the system clock for the delay
void roveDelay_MilliSec(uint32_t milliseconds);
void roveDelay_MicroSec(uint32_t microseconds);

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

//roveWare 2015
int32_t roveGetByteCnt_ByStructId(int32_t struct_id);

#endif //ROVETIVA129_H_
