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

//roveWare 2015
int32_t roveGetByteCnt_ByStructId(int32_t struct_id);

//DevDec16
int32_t roveGetPinNum_ByDeviceId(int32_t data_id);
void rovePrintf_ByByteBuffer(uint8_t* printf_buffer, int32_t bytes_to_printf);

//Tiva Get/Set Wrappers
void roveDigital_Write(int32_t tiva_pin, int32_t high_or_low);
void rovePwm_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds);

int32_t roveUart_Write(int32_t tiva_pin, uint8_t* write_buffer, int32_t bytes_to_write);
int32_t roveUart_Read(int32_t tiva_pin, uint8_t* read_buffer, int32_t bytes_to_read);

void roveDelay_MilliSec(uint32_t milliseconds);
void roveDelay_MicroSec(uint32_t microseconds);

#endif //ROVETIVA129_H_
