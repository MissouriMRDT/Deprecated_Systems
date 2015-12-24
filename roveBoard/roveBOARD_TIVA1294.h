// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare
#ifndef ROVEBOARD_TIVA1294_H_
#define ROVEBOARD_TIVA1294_H_



//C lib
#include <stdio.h>
#include <stdbool.h>

//TODO factor TI hardware config in EK_TM4C1294XL
#include "EK_TM4C1294XL.h"

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
//TODO #include <ti/drivers/Watchdog.h>

//CCS TI config
#include <xdc/runtime/System.h>



//TODO Hardware Handle Shorthand
typedef struct roveGPIO_Handle {
    uint32_t port;
    uint8_t pin;
} roveGPIO_Handle, *roveGPIO_HandlePtr;



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



typedef UART_Handle roveUART_Handle;
typedef PWM_Handle rovePWM_Handle;

roveGPIO_Handle* roveBoard_InitGpioCFG(roveGPIO_Handle* gpio , uint32_t gpio_port , uint8_t gpio_pin);
PWM_Handle roveBoard_InitPwmCFG(UInt pwm_index, UInt period_in_microseconds);
UART_Handle roveBoard_InitUartCFG(UInt uart_index , UInt baud_rate);

//Tiva Get/Set Wrappers
void roveBoard_DigitalWrite(roveGPIO_Handle* gpio_pin, uint8_t digital_value);
void roveBoard_PwmWrite(rovePWM_Handle pwm, int16_t duty_in_microseconds);

int32_t roveBoard_UartWrite( roveUART_Handle uart, uint8_t* write_buffer, int32_t bytes_to_write);
int32_t roveBoard_UartRead(roveUART_Handle uart, uint8_t* read_buffer, int32_t bytes_to_read);

#endif //ROVEBOARD_TIVA1294_H_
