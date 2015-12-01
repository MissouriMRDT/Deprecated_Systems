// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare
#ifndef ROVETIVA129_H_
#define ROVETIVA129_H_

//C lib
#include <stdio.h>
#include <stdbool.h>

//TI hardware access routines
#include "../roveBoard1294/EK_TM4C1294XL.h"

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
//TODO #include <ti/drivers/Watchdog.h>

//CCS TI config
#include <xdc/runtime/System.h>

//TODO REED??
typedef struct roveGpio_Handle {

    uint32_t port;
    uint8_t pin;
} roveGpio_Handle, *roveGpio_HandlePtr;

typedef UART_Handle roveUart_Handle;
typedef PWM_Handle rovePwm_Handle;

//TODO Watchdog_Handle watchdog;
//TODO: ADC_0 : S_SQR 1x6

//mrdt shorthand
enum RoveHwDev16ShortHand {
    HW_ERROR_FREE = 1
    , HW_ERROR = -1
    , HW_TEST_DEVICE_PIN = 0
    , HW_TEST_DEVICE_ID = 0
    , HW_TRI_STATE_PIN = 1
};//end enum

enum RoveGpioDev16ShortHand {
    PORT_E = GPIO_PORTE_BASE
    ,PORT_H = GPIO_PORTH_BASE
    ,PORT_K = GPIO_PORTK_BASE
    ,PORT_L = GPIO_PORTL_BASE
    ,PORT_M = GPIO_PORTM_BASE
    ,PIN_0 = GPIO_PIN_0
    ,PIN_1 = GPIO_PIN_1
    ,PIN_2 = GPIO_PIN_2
    ,PIN_3 = GPIO_PIN_3
    ,PIN_6 = GPIO_PIN_6
    ,PIN_7 = GPIO_PIN_7
};//end enum

roveGpio_Handle* roveGpio_Init(

        roveGpio_Handle* gpio
        , uint32_t gpio_port
        , uint8_t gpio_pin
);//end fnctn

PWM_Handle rovePwm_Init(

        UInt pwm_index
        , UInt period_in_microseconds
);//end fnctn

UART_Handle roveUart_Init(

        UInt uart_index
        , UInt baud_rate
);//end fnctn

//TODO UInt roveAdc_Init(

//      UInt adc_index
//      , UInt adc_cfg
//);//end fnctn

//DevDec16
int32_t roveGetPinNum_ByDeviceId(int32_t data_id);

void rovePrintf_ByByteBuffer(

        uint8_t* printf_buffer
        , int32_t bytes_to_printf
);//end fnctn

//Tiva Get/Set Wrappers
void roveDigital_Write(

        roveGpio_Handle* gpio_pin
        , uint8_t high_or_low
);//end fnctn

void rovePwm_Write(

        rovePwm_Handle pwm
        , int16_t duty_in_microseconds
);//end fnctn

int32_t roveUart_Write(

        roveUart_Handle uart
        , uint8_t* write_buffer
        , int32_t bytes_to_write
);//end fnctn

int32_t roveUart_Read(

        roveUart_Handle uart
        , uint8_t* read_buffer
        , int32_t bytes_to_read
);//end fnctn

void roveDelay_MilliSec(uint32_t milliseconds);

void roveDelay_MicroSec(uint32_t microseconds);

#endif //ROVETIVA129_H_
