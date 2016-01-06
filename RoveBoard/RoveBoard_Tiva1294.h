// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare
#ifndef ROVEBOARD_TIVA1294_H_
#define ROVEBOARD_TIVA1294_H_

//
#ifdef __cplusplus
extern "C" {
#endif

//TODO factor TI hardware config in EK_TM4C1294XL
#include "EK_TM4C1294XL.h"

//RoveWare
//#include "roveWare/roveComm.h"
//#include "roveWare/roveControl.h"
//#include "roveWare/roveSense.h"
//#include "roveWare/roveScience.h"
//#include "roveWare/roveMonitor.h"

//TODO
enum RoveHwDev16ShortHand {
    HW_ERROR_FREE = 1
    , HW_ERROR = -1
    , HW_TEST_DEVICE_PIN = 0
    , HW_TEST_DEVICE_ID = 0
    , HW_TRI_STATE_PIN = 1
};//end enum


//C lib
#include <stdio.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
//TODO #include <ti/drivers/Watchdog.h>

//CCS TI config
#include <xdc/runtime/System.h>



typedef PWM_Handle rovePWM_Handle;
typedef UART_Handle roveUART_Handle;

//TODO Hardware Handle Shorthand
typedef struct roveGPIO_Handle {
    uint32_t port;
    uint8_t pin;
} roveGPIO_Handle, *roveGPIO_HandlePtr;

roveGPIO_Handle* roveBoard_InitGpio(roveGPIO_Handle* gpio , uint32_t gpio_port , uint8_t gpio_pin);
PWM_Handle roveBoard_InitPwm(UInt pwm_index, UInt period_in_microseconds);
UART_Handle roveBoard_InitUart(UInt uart_index , UInt baud_rate);

//Tiva Get/Set Wrappers
void roveBoard_DigitalWrite(roveGPIO_Handle* gpio_pin, uint8_t digital_value);
void roveBoard_PwmWrite(rovePWM_Handle pwm, int16_t duty_in_microseconds);

int32_t roveBoard_UartWrite( roveUART_Handle uart, uint8_t* write_buffer, int32_t bytes_to_write);
int32_t roveBoard_UartRead(roveUART_Handle uart, uint8_t* read_buffer, int32_t bytes_to_read);

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

