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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//=== TODO: factor_TI_hardware_config_in_EK_TM4C1294XL ==============
//
//Tivaware board hardware access
#include <ti/drivers/Watchdog.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
//
//RoveWare board hardware config
#include "RoveBoard/RoveM4C1294/EK_TM4C1294XL.h"


//=== RoveLoop_CCSBios_RtosSchedule ========
//
// rtos hooks are scheduled by implicit config priority/ interrupt_vector
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>



//=== RoveBoard_Error ==============
//
typedef enum
{
    ROVEBOARD_ERROR_SUCCESS = 0
    ,ROVEBOARD_ERROR_UNKNOWN = -1

    //Todo: roveBoard_ERROR_KNOWN = -2 etc
} roveBoard_ERROR;



//=== RoveCCSTiva_Bios_Rtos_Drivers ========
//
void roveBoard_EK_TM4C1294XL_Open();

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



//=== RoveBoard_Watchdog ==============
//
// Interface between RoveWare Estop and TexasIntrmnts RtosTask watchdog interrupt vector
//
typedef Watchdog_Callback roveBoard_WATCHDOG_Callback;
//
typedef Watchdog_Handle roveWatchdog_Handle;
//
roveWatchdog_Handle roveBoard_WATCHDOG_open(unsigned int watchdog_index, roveBoard_WATCHDOG_Callback attach_interrupt, bool board_reset_flag);



// == Texas Inst Loop Forever at Rtos Priority Schedule ========
//
// Interface between RoveWare LoopForever and TexasIntrmnts RtosTask schedule
typedef ti_sysbios_knl_Task_FuncPtr roveLoopPtr;
//
//roveTiRtos Interface Constructor
void roveBoard_LOOP_open(roveLoopPtr loop_Ptr, UInt loop_Pri);



//Judah Todo: interface int main(void) from setup(void) for No Schedluer vs RtosScheduler Single Loop isomorphism copy/paste
//=== RoveBoard_PostProccess ==============
//
//TODO Clock and Timer Instances
//void roveBoard_DelayMicroseconds(uint32_t milliseconds);
//void roveBoard_Delay(uint32_t microseconds);


#ifdef __cplusplus
}
#endif

#endif //ROVEBOARD_TIVA1294_H_

