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

typedef PWM_Handle rovePWM_Handle;
typedef UART_Handle roveUART_Handle;

enum RoveHwDev16ShortHand {
    HW_ERROR_FREE = 1
    , HW_ERROR = -1
    , HW_TEST_DEVICE_PIN = 0
    , HW_TEST_DEVICE_ID = 0
    , HW_TRI_STATE_PIN = 1
};//end enum
//End Todo

//Todo Hardware Handle Shorthand
typedef struct roveGPIO_Struct {
    uint32_t port;
    uint8_t pin;
} roveGPIO_Struct, *roveGPIO_Handle;
void roveBoard_DigitalWrite(roveGPIO_Handle gpio_pin, uint8_t digital_value);
roveGPIO_Handle roveBoard_GpioInit(roveGPIO_Handle gpio , uint32_t gpio_port , uint8_t gpio_pin);
//End Todo

typedef enum roveBoardERROR {
    roveBoardERROR_UARTError = -1
    , roveBoardERROR_success = 1
} roveBoardERROR;//end enum

//Works
rovePWM_Handle roveBoard_PwmInit(unsigned int pwm_index, unsigned int period_in_microseconds);
roveUART_Handle roveBoard_UartInit(unsigned int uart_index , unsigned int baud_rate);

void roveBoard_PwmWrite(rovePWM_Handle tiva_pin, uint32_t duty_in_microseconds);
roveBoardERROR roveBoard_UartWrite(roveUART_Handle uart, void* write_buffer, size_t bytes_to_write);
roveBoardERROR roveBoard_UartRead(roveUART_Handle uart, void* read_buffer, size_t bytes_to_read);

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

