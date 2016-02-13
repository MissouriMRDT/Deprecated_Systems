// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Authorjrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare
#ifndef ROVEBOARD_H_
#define ROVEBOARD_H_
#pragma once
#include <stdio.h>
#include <stdint.h>

//=== TODO: factor_TI_hardware_config_in_EK_TM4C1294XL ==============
//
//Tivaware board hardware access
#include <ti/drivers/Watchdog.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
//
//RoveWare board hardware config
#include "RoveTivaM4C/EK_TM4C1294XL.h"



//=== RoveBoard_Error ==============
//
typedef enum
{
    ROVEBOARD_ERROR_SUCCESS = 0
    ,ROVEBOARD_ERROR_UNKNOWN = -1

    //Todo: roveBoard_ERROR_KNOWN = -2 etc
} roveBoard_ERROR;



//== RoveBoard_Pulse_Width_Modulation_Pin_Access ===============
//
typedef PWM_Handle rovePWM_Handle;
//
rovePWM_Handle roveBoard_PWM_open(unsigned int pwm_index, unsigned int period_in_microseconds);
void roveBoard_PWM_write(rovePWM_Handle tiva_pin, uint32_t duty_in_microseconds);



//=== RoveBoard_Serial_Pin_Access ==============
//
typedef UART_Handle roveUART_Handle;
//
roveUART_Handle roveBoard_UART_open(unsigned int uart_index , unsigned int baud_rate);
roveBoard_ERROR roveBoard_UART_write(roveUART_Handle uart, void* write_buffer, size_t bytes_to_write);
roveBoard_ERROR roveBoard_UART_read(roveUART_Handle uart, void* read_buffer, size_t bytes_to_read);



//=== RoveBoard_Watchdog ==============
//
// Interface between RoveWare Estop and TexasIntrmnts RtosTask watchdog interrupt vector
//
typedef Watchdog_Callback roveBoard_WATCHDOG_Callback;
//
typedef Watchdog_Handle roveWatchdog_Handle;
//
roveWatchdog_Handle roveBoard_WATCHDOG_open(unsigned int watchdog_index, roveBoard_WATCHDOG_Callback attach_isr_countdown);



/*TODO Reed, Gbenga, Connor, Owen GPIO Advice??
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

typedef struct ROVE_GPIO_Config   *roveGPIO_Handle
typedef struct roveGPIO_Handle {
    uint32_t port;
    uint8_t pin;
} roveGPIO_Handle;
roveGPIO_Handle roveBoard_GPIO_Open(roveGPIO_Handle gpio, uint32_t gpio_port, uint8_t gpio_pin) {

    gpio->port = gpio_port;
    gpio->pin = gpio_pin;
//TODO
    return gpio;
};//end fnctn
void roveBoard_GPIO_digitalWrite(roveGPIO_Handle gpio_pin, uint8_t digital_value) {

    uint8_t pin_value = 0;

    if(digital_value > 0) {

        pin_value = ~0;
    }//end if

    GPIOPinWrite(gpio_pin->port, gpio_pin->pin, pin_value);
}//endfnctn

//Judah Todo: implement schedule starter pistol on roveBoard_LOOP_BeginLoops();
//Judah Todo: implement schedule starter pistol on roveBoard_LOOP_BeginMoreLoop();
//begin real time scheduler
//printf("BIOS Scheduler Begin\n\n");
//BIOS_start();
//return (0);
//Judah Todo: interface int main(void) from setup(void) for No Schedluer vs RtosScheduler Single Loop isomorphism copy/paste
//Double Bonus,  RoveCntrl_XBEE_Begin(serial_pin),  RoveCntrl_XBEE_Write(
//=== RoveBoard_PostProccess ==============
//
//TODO Clock and Timer Instances
//void roveBoard_DelayMilliSec(uint32_t milliseconds);
//void roveBoard_DelayMicroSec(uint32_t microseconds);
*/



#endif //ROVEBOARD_TIVA1294_H_

