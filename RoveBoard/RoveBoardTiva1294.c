// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
// roveWare 1294XL Access Routines
//
// mrdt::rovWare
#include "RoveBoardTiva1294.h"

//TODO factor TI hardware config in EK_TM4C1294XL
#include "EK_TM4C1294XL.h"

//C lib
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//Rtos Kernel Module Instance Api
//#include <ti/sysbios/knl/Task.h>
//#include <ti/sysbios/knl/Swi.h>
//#include <ti/sysbios/knl/Clock.h>
//#include <ti/sysbios/knl/Semaphore.h>
//TODO #include <ti/drivers/Watchdog.h>

//CCS TI config
#include <xdc/runtime/System.h>

//TODO Clock and Timer Instances

rovePWM_Handle roveBoard_PWM_open(unsigned int pwm_index, unsigned int period_in_microseconds){

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

roveUART_Handle roveBoard_UART_open(unsigned int uart_index, unsigned int baud_rate){

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
roveBoard_ERROR roveBoard_UART_write(roveUART_Handle uart, void* write_buffer, size_t bytes_to_write) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    int bytes_written = UART_write(uart, write_buffer, bytes_to_write);

    if(bytes_written < 0){
        return roveBoard_ERROR_UART_error;
    }//end if

    return roveBoard_ERROR_success;
}//endfnctn

roveBoard_ERROR roveBoard_UART_read(roveUART_Handle uart, void* read_buffer, size_t bytes_to_read) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);

    int bytes_read = UART_read(uart, read_buffer, bytes_to_read);

    if(bytes_read < 0){
      return roveBoard_ERROR_UART_error;
    }//end if

    return roveBoard_ERROR_success;
}//endfnctn



void roveBoard_PWM_write(rovePWM_Handle tiva_pin, uint32_t duty_in_microseconds) {

    PWM_setDuty(tiva_pin, duty_in_microseconds);
}//endfnctn


/*
void roveBoard_GPIO_digitalWrite(roveGPIO_Handle gpio_pin, uint8_t digital_value) {

    uint8_t pin_value = 0;

    if(digital_value > 0) {

        pin_value = ~0;
    }//end if

    GPIOPinWrite(gpio_pin->port, gpio_pin->pin, pin_value);
}//endfnctn

//extern int32_t GPIOPinRead(uint32_t ui32Port, uint8_t ui8Pins);
//extern void GPIOPinWrite(uint32_t ui32Port, uint8_t ui8Pins, uint8_t ui8Val);
*/






















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








////////////////////////////////////////////////////
 */


