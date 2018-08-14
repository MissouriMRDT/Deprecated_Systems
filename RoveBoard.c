//Missouri University of Science and Technology: Mars Rover Design Team
#include "../RoveBoard.h"

//C lib
#include <stdio.h>
#include <stdint.h>

//CCS TI config
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include <xdc/runtime/System.h>



//=== RoveCCSTiva_Bios_Rtos_Drivers ========
//
void roveBoard_init()
{
    // TI board driver routines
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();
    EK_TM4C1294XL_initWatchdog();
}//end fnctn



/*
//=== RoveCCSTiva_General_Purpose_IO_Pin_Access ========
//
typedef struct roveGPIO_Config
{
    uint32_t port;
    uint8_t pin;
} roveGPIO_Config;


roveGPIO_Handle roveBoard_GPIO_open(uint32_t gpio_port, uint8_t gpio_pin)
{
    roveGPIO_Handle gpioHandle;

    gpioHandle->port = gpio_port;
    gpioHandle->pin = gpio_pin;

    return gpioHandle;
};//end fnctn

void roveBoard_GPIO_digitalWrite(roveGPIO_Handle gpio, uint8_t write_value) 
{
    uint8_t pin_value = 0;

    if(digital_value > 0) 
    {
        pin_value = ~0;
    }//end if

    GPIOPinWrite(gpio->port, gpio->pin, pin_value);
}//endfnctn

void roveBoard_GPIO_digitalRead(roveGPIO_Handle gpio, uint8_t* read_value) 
{
    uint8_t pin_value = 0;

    if(digital_value > 0) 
    {
        pin_value = ~0;
    }//end if

    GPIOPinWrite(gpio->port, gpio->pin, pin_value);
}//endfnctn
*/



//=== RoveCCSTiva_Pulse_Width_Modulation_Pin_Access ========
//
rovePWM_Handle roveBoard_PWM_open(unsigned int pwm_index, unsigned int period_in_microseconds)
{
    //ethernet pin conflict: EK_TM4C1294XL.h
    if (pwm_index == 0)
    {
        System_abort("Error opening the PWM\n");
    }//endif

    PWM_Handle pwmHandle;
    PWM_Params pwmParams;
    PWM_Params_init(&pwmParams);
    pwmParams.period = period_in_microseconds;

    pwmHandle = PWM_open(pwm_index, &pwmParams);
    if (pwmHandle == NULL) {
        System_abort("Error opening the PWM\n");
    }//endif

    return pwmHandle;
}//endfnctn

void roveBoard_PWM_write(rovePWM_Handle pwm, uint32_t duty_in_microseconds) 
{
    PWM_setDuty(pwm, duty_in_microseconds);
}//endfnctn


//=== RoveCCSTiva_Serial_Pin_Access ========
//
roveUART_Handle roveBoard_UART_open(unsigned int uart_index, unsigned int baud_rate)
{
    UART_Handle uartHandle;
    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = baud_rate;

    uartHandle = (UART_Handle)UART_open(uart_index, &uartParams);
    if (uartHandle == NULL) 
    {
        System_abort("Error opening the UART\n");
    }//endif

    return uartHandle;
}//endfnct

//rove to Tiva Read/Write Hardware I/O Module Wrappers
roveBoard_ERROR roveBoard_UART_write(roveUART_Handle uart, void* write_buffer, size_t bytes_to_write) 
{
    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    int bytes_written = UART_write(uart, write_buffer, bytes_to_write);

    if(bytes_written < 0)
    {
        return ROVEBOARD_ERROR_UNKNOWN;
    }//end if

    return ROVEBOARD_ERROR_SUCCESS;
}//endfnctn

roveBoard_ERROR roveBoard_UART_read(roveUART_Handle uart, void* read_buffer, size_t bytes_to_read) 
{
    int bytes_read = UART_read(uart, read_buffer, bytes_to_read);

    if(bytes_read < 0)
    {
      return ROVEBOARD_ERROR_UNKNOWN;
    }//end if

    return ROVEBOARD_ERROR_SUCCESS;
}//endfnctn

