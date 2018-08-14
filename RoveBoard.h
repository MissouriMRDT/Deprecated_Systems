//Missouri University of Science and Technology: Mars Rover Design Team
#pragma once
#ifndef ROVEBOARD_H_
#define ROVEBOARD_H_

//C lib
#include <stdint.h>

//Tivaware board hardware access
#include <stdbool.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
#include "RoveBoard/RoveTM4C1294/EK_TM4C1294XL.h"



//=== RoveBoard_Error ==============
//
typedef enum
{
    ROVEBOARD_ERROR_SUCCESS = 0
    ,ROVEBOARD_ERROR_UNKNOWN = -1

} roveBoard_ERROR;



//=== RoveCCSTiva_Bios_Rtos_Drivers ========
//
void roveBoard_init();

/*
//== RoveBoard_General_PurposeInput_Output_Pin_Access ===============
//
typedef struct roveGPIO_Config      *roveGPIO_Handle;
//
roveGPIO_Handle roveBoard_GPIO_open(unsigned int gpio_index);
void roveBoard_GPIO_digitalWrite(roveGPIO_Handle gpio, uint8_t write_value);
roveBoard_ERROR roveBoard_GPIO_digitalRead(roveGPIO_Handle gpio, uint8_t* read_value);
*/



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

#endif

