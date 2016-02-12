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

//TODO factor TI hardware config in EK_TM4C1294XL
#include "RoveTiva/EK_TM4C1294XL.h"

#include <stdio.h>
#include <stdint.h>

//Todo
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>

typedef enum
{
    ROVE_BOARD_ERROR_SUCCESS = 0
    ,ROVE_BOARD_ERROR_UNKNOWN = -1
    //,roveBoard_ERROR_KNOWN = -2
} roveBoard_ERROR;



typedef PWM_Handle rovePWM_Handle;
rovePWM_Handle roveBoard_PWM_open(unsigned int pwm_index, unsigned int period_in_microseconds);
void roveBoard_PWM_write(rovePWM_Handle tiva_pin, uint32_t duty_in_microseconds);



typedef UART_Handle roveUART_Handle;
roveUART_Handle roveBoard_UART_open(unsigned int uart_index , unsigned int baud_rate);
roveBoard_ERROR roveBoard_UART_write(roveUART_Handle uart, void* write_buffer, size_t bytes_to_write);
roveBoard_ERROR roveBoard_UART_read(roveUART_Handle uart, void* read_buffer, size_t bytes_to_read);



//typedef Watchdog_Handle roveWatchdog_Handle;
//roveWatchdog_Handle roveBoard_WATCHDOG_open(unsigned int watchdog_index)


#endif //ROVEBOARD_TIVA1294_H_

