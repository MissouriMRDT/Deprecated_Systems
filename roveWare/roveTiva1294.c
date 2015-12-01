// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
// roveWare 1294XL Access Routines
//
// mrdt::rovWare
#include "roveTiva1294.h"

roveGpio_Handle* roveGpio_Init(roveGpio_Handle* gpio, uint32_t gpio_port, uint8_t gpio_pin) {

    gpio->port = gpio_port;
    gpio->pin = gpio_pin;

    return &gpio;
};//end fnctn



PWM_Handle rovePwm_Init(UInt pwm_index, UInt period_in_microseconds) {

    PWM_Handle pwmHandle;
    PWM_Params pwmParams;
    PWM_Params_init(&pwmParams);
    //TODO Phase Align params
    pwmParams.period = period_in_microseconds;

    pwmHandle = PWM_open(pwm_index, &pwmParams);
    if (pwmHandle == NULL) {
        System_abort("Error opening the PWM\n");
    }//endif

    return pwmHandle;
}//endfnctn



UART_Handle roveUart_Init(UInt uart_index, UInt baud_rate) {

    UART_Handle uartHandle;
    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = baud_rate;

    uartHandle = (UART_Handle)UART_open(uart_index, &uartParams);
    if (uartHandle == NULL) {
        System_abort("Error opening the UART\n");
    }//endif

    return uartHandle;
}//endfnct



/*TODO
UInt roveAdc_Init(UInt adc_index, UInt adc_cfg) {

    //TODO
    UInt adcHandle = NULL;

    //UInt adcParams;
    if (adcHandle == NULL) {
        System_abort("Error opening the ADC\n");
    } //endif

    return adcHandle;
}//endfnct*/



//rove to Tiva Read/Write Hardware I/O Module Wrappers
int32_t roveUart_Write(roveUart_Handle uart, uint8_t* write_buffer, int32_t bytes_to_write) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    return UART_write(uart, (char*)&write_buffer, bytes_to_write);
}//endfnctn

int32_t roveUart_Read(roveUart_Handle uart, uint8_t* read_buffer, int32_t bytes_to_read) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    return UART_read(uart, (char*)&read_buffer, bytes_to_read);
}//endfnctn



void rovePwm_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds) {

    PWM_setDuty(tiva_pin, duty_in_microseconds);
    return;
}//endfnctn

void roveDigital_Write(roveGpio_Handle* gpio_pin, uint8_t high_or_low) {

    if(high_or_low){

        GPIOPinWrite(gpio_pin->port, gpio_pin->pin, gpio_pin->pin);
        return;
    }//end if

    GPIOPinWrite(gpio_pin->port, gpio_pin->pin, ~gpio_pin->pin);
    return;
}//endfnctn



//TODO REED?? 123G used SysCtlClockGet 1294 doesn't even have that?? needs global return value for roveSetClockMicroSec_Init??
void roveDelay_MilliSec(uint32_t milliseconds) {

    //SysCtlDelay(milliseconds * (SysCtlClockGet() / 100));
}//endfnctn

void roveDelay_MicroSec(uint32_t microseconds) {

    //SysCtlDelay(microseconds * (SysCtlClockGet() / 100000));
}//endfnctn
