// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
// roveWare 1294XL Access Routines
//
// mrdt::rovWare
#include "RoveBoard_Tiva1294.h"



//TODO Clock and Timer Instances



//TODO Connor, Drue, Jetter Hbridge use case Config choices
PWM_Handle roveBoard_InitPwm(UInt pwm_index, UInt period_in_microseconds) {

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

UART_Handle roveBoard_InitUart(UInt uart_index, UInt baud_rate) {

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



//rove to Tiva Read/Write Hardware I/O Module Wrappers
int32_t roveBoard_UartWrite(roveUART_Handle uart, uint8_t* write_buffer, int32_t bytes_to_write) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    return UART_write(uart, (char*)&write_buffer, bytes_to_write);
}//endfnctn

int32_t roveBoard_UartRead(roveUART_Handle uart, uint8_t* read_buffer, int32_t bytes_to_read) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    return UART_read(uart, (char*)&read_buffer, bytes_to_read);
}//endfnctn



void roveBoard_PwmWrite(PWM_Handle tiva_pin, int16_t duty_in_microseconds) {

    PWM_setDuty(tiva_pin, duty_in_microseconds);
    return;
}//endfnctn

void roveBoard_DigitalWrite(roveGPIO_Handle* gpio_pin, uint8_t digital_value) {

    if(digital_value){

        GPIOPinWrite(gpio_pin->port, gpio_pin->pin, gpio_pin->pin);
        return;
    }//end if

    GPIOPinWrite(gpio_pin->port, gpio_pin->pin, ~(gpio_pin->pin) );
    return;
}//endfnctn


/*TODO Reed, Connor, Owen Advice??

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

//TODO Watchdog_Handle watchdog;
//TODO: ADC_0 : S_SQR 1x6
//TODO roveADC_Handle* roveBoard_InitAdcCFG(UInt adc_index , UInt adc_cfg??);

//void roveBoard_DelayMilliSec(uint32_t milliseconds);
//void roveBoard_DelayMicroSec(uint32_t microseconds);

typedef struct roveGPIO_Handle {
    uint32_t port;
    uint8_t pin;
} roveGPIO_Handle, *roveGPIO_HandlePtr;

roveGPIO_Handle roveBoard_InitGpioCFG(roveGPIO_Handle gpio, uint32_t gpio_port, uint8_t gpio_pin) {

    gpio->port = gpio_port;
    gpio->pin = gpio_pin;
//TODO
    return gpio;
};//end fnctn

//TODO Reed, Judah, Drue, Drew, Gbenga, Ian, Clayton, David use case Config choices
roveCapCmpr_Handle roveCapCmpr_Init(UInt cap_cmpr_index, UInt cap_cmpr_cfg) {

    //TODO
    UInt roveCapCmpr_Handle = NULL;

    //UInt capCmprParams;
    if (roveCapCmpr_Handle == NULL) {
        System_abort("Error opening the CapCmpr\n");
    } //endif

    return roveCapCmpr_Handle;
}//endfnct

//TODO Reed, Judah, Drue, Drew, Gbenga, Ian, Clayton, David use case Config choices
roveADC_Handle roveAdc_Init(UInt adc_index, UInt adc_cfg) {

    //TODO
    UInt roveADC_Handle = NULL;

    //UInt adcParams;
    if (roveADC_Handle == NULL) {
        System_abort("Error opening the ADC\n");
    } //endif

    return roveADC_Handle;
}//endfnct

*/

