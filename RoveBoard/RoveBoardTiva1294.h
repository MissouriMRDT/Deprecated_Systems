// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare
#pragma once
#ifndef ROVEBOARDTIVA1294_H_
#define ROVEBOARDTIVA1294_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//Todo
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>

//Todo
//typedef PWM_Handle roveGPIO_Handle
typedef PWM_Handle rovePWM_Handle;
typedef UART_Handle roveUART_Handle;

enum RoveHwDev16ShortHand {
    HW_ERROR_FREE = 1
    , HW_ERROR = -1
    , HW_TEST_DEVICE_PIN = 0
    , HW_TEST_DEVICE_ID = 0
    , HW_TRI_STATE_PIN = 1
};//end enum

typedef enum roveBoard_ERROR
{
    roveBoard_ERROR_UART_error = -1
    , roveBoard_ERROR_success = 1
} roveBoard_ERROR;

//Works
rovePWM_Handle roveBoard_PWM_open(unsigned int pwm_index, unsigned int period_in_microseconds);
roveUART_Handle roveBoard_UART_open(unsigned int uart_index , unsigned int baud_rate);

void roveBoard_PWM_write(rovePWM_Handle tiva_pin, uint32_t duty_in_microseconds);
roveBoard_ERROR roveBoard_UART_write(roveUART_Handle uart, void* write_buffer, size_t bytes_to_write);
roveBoard_ERROR roveBoard_UART_read(roveUART_Handle uart, void* read_buffer, size_t bytes_to_read);

#ifdef __cplusplus
}
#endif

#endif //ROVEBOARD_TIVA1294_H_



















/* TODO roveWare Upgrades Version 1 Release
// ========  roveMonitor ========
//
// Cplus object wrappers
class roveSoftClock
{
    private:
         // data
         int id;
         double ticks;
         //int microseconds;
         int milliseconds;
         //int seconds;
         void tick_millisecond();

    public:
        // methods
         roveSoftClock(int newId);
        ~roveSoftClock();
        int getClockId();
        int getMilliSec();
};// end class

// wires to call Clock rtos object
void clock_mS(UArg arg);
*/

