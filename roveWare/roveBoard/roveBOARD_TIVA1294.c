// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
// roveWare 1294XL Access Routines
//
// mrdt::rovWare
#include "roveBOARD_TIVA1294.h"


//


    /*
    //  ======== bigtime.cpp ========
    //  In this program, C++ is used to create a real-time clock/calendar.
    //  The C++ class object, Clock, is driven by a variety
    //  of SYS/BIOS objects: two Clock objects, two Task objects, and an
    //  Idle object. Each SYS/BIOS object has its own instantiation
    //  of the Clock.  When the Clock, Task, and Idle functions
    //  execute, they call their clock's tick function, advancing
    //  the connected timer by one second.
    //
    //  Because the functions execute at different rates, the attached
    //  clocks also advance at different rates.  For example, one of the
    //  Clock objects, prdClock1, has a period of one second.  When prdClock1
    //  runs, it advances its timer by one second.  This results in an
    //  accurate clock.  On the other hand, idlClock runs with every pass
    //  through the idle loop.  Therefore, the number of seconds passed for
    //  its attached timer indicates the time spent in the idle loop.
    //  See the SYS/BIOS configuration file for more information on the
    //  SYS/BIOS objects.
    //
    //  To view the effects of this program, open RTA RAW Logs and halt target.
    //
    //  You can experiment with advancing Clock at different rates
    //  by changing the Clock::tick function.
    //
    //
    ///

    #include <xdc/std.h>

    #include <xdc/runtime/Log.h>
    #include <xdc/runtime/Diags.h>
    #include <xdc/runtime/System.h>
    #include <ti/sysbios/BIOS.h>
    #include <ti/sysbios/knl/Semaphore.h>
    #include <ti/sysbios/knl/Task.h>


    #include <xdc/cfg/global.h>

//

//TODO Reed, Connor, Owen Advice??
roveGPIO_Handle* roveBoard_InitGpioCFG(roveGPIO_Handle* gpio, uint32_t gpio_port, uint8_t gpio_pin) {

    gpio->port = gpio_port;
    gpio->pin = gpio_pin;
//TODO
    return gpio;
};//end fnctn

//TODO Reed, Judah, Drue, Drew, Gbenga, Ian, Clayton, David use case Config choices
roveADC_Handle roveAdc_Init(UInt adc_index, UInt adc_cfg) {

    //TODO
    UInt roveADC_Handle = NULL;

    //UInt adcParams;
    if (roveADC_Handle == NULL) {
        System_abort("Error opening the ADC\n");
    } //endif

    return roveADC_Handle;
}//endfnct*/



//TODO Connor, Drue, Jetter Hbridge use case Config choices
PWM_Handle roveBoard_InitPwmCFG(UInt pwm_index, UInt period_in_microseconds) {

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



UART_Handle roveBoard_InitUartCFG(UInt uart_index, UInt baud_rate) {

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



//TODO Reed, Connor, Owen Advice?? 123G used SysCtlClockGet 1294 doesn't even have that?? needs global return value for roveSetClockMicroSec_Init
//We should explicitly init the clock juuuust to get the return global??? It's being Init in Rtsc already? that global hides an rtos handle??
//void roveBoard_DelayMilliSec(uint32_t milliseconds) {
    //SysCtlDelay(milliseconds// (SysCtlClockGet() / 100));
//}//endfnctn

//void roveBoard_DelayMicroSec(uint32_t microseconds) {

   //SysCtlDelay(microseconds// (SysCtlClockGet() / 100000));



//////////////////////////////////////roveClock


/*class Clock {
    private:
         // data
         int id;
         double ticks;
         int microsecond;
         int millisecond;
         int second;
         int minute;
         int hour;
         int day;
         int month;
         int year;
         int century;
         int millenium;
//             Diags_Mask clockLog;

    public:
        // methods
        Clock(int newId);  // Constructor
        ~Clock();                           // Destructor
        void tick();
        long getTicks();
        int getId();
        int getMicrosecond();
        int getMillisecond();
        int getSecond();
        int getMinute();
        int getHour();
        int getDay();
        int getMonth();
        int getYear();
        int getCentury();
        int getMillenium();
        void setMicrosecond();
        void setMillisecond();
        void setSecond();
        void setMinute();
        void setHour();
        void setDay();
        void setMonth();
        void setYear();
        void setCentury();
        void setMillenium();
};

String months[12] = { "January", "February", "March",
                      "April",   "May",      "June",
                      "July",    "August",   "September",
                      "October", "November", "December" };

//
// Extern "C" block to prevent name mangling
// of functions called within the Configuration
// Tool
 //
extern "C" {

// Wrapper functions to call Clock::tick()
void clockTask(UArg arg);
void clockPrd(UArg arg);
void clockIdle(void);

} // end extern "C"

// Global clock objects
//Clock cl0(0);  // idle loop clock
Clock roveIDLE_CLOCK(0);


//Clock cl1(1);  /
// periodic clock, period = 1 ms
Clock roveClock_mSec(1);

//Clock cl2(2);
// periodic clock, period = 1 sec
//Clock roveClock_Sec(2);


//Clock cl3(3);
//task clock
//Clock roveTaskClockTHREE(3);
// task clock

//Clock cl4(4);  // task clock///
//Clock roveTaskClockFOUR(4);
// task clock


//
//  ======== clockTask ========
//  Wrapper function for TSK objects calling
//  Clock::tick()
//
void clockTask(UArg arg)
{
    Clock//clock = (Clock//)arg;
    int count = 0;

    if (clock->getId() == 3) {
        for(;;) {             // task id = 3
            Semaphore_pend(sem0, BIOS_WAIT_FOREVER);
            clock->tick();
            if(count == 50) {
                Task_sleep(25);
                count = 0;
            }
            count++;
            Semaphore_post(sem1);
        }
    }
    else {
        for(;;) {             // task id = 4
            Semaphore_pend(sem1, BIOS_WAIT_FOREVER);
            if(count == 50) {
                Task_sleep(25);
                count = 0;
            }
            clock->tick();
            count++;
            Semaphore_post(sem0);
        }
    }
}//end task



//
// ======== clockPrd ========
// Wrapper function for PRD objects calling
// Clock::tick()
///
void clockPrd(UArg arg)
{
    Clock//clock = (Clock//)arg;

    clock->tick();
    return;
}


//
// ======== clockIdle ========
// Wrapper function for IDL objects calling
// Clock::tick()
///
void clockIdle(void)
{
  //  cl0.tick();
    return;
}


//
// Clock methods
///
Clock::Clock(int newId)
{
    id = newId;
    ticks = 0;
    microsecond = 0;
    millisecond = 0;
    second = 0;
    minute = 0;
    hour = 0;
    day = 19;
    month = 8;
    year = 10;
    century = 20;
    millenium = 0;
}

Clock::~Clock()
{
}

void Clock::tick()
{
    ticks++;

    if ((getId() == 1) || (getId() == 2)) {
       // Log_info4("id %d : %d:%d:%d", getId(), hour, minute, second);
        //Log_info5("id %d : %s %d, %d%d", getId(), (IArg)months[month-1], day, century, year);
    }

//
// Change selected function to alter clock rate
//
//  setMicrosecond();
//  setMillisecond();
    setSecond();
//  setMinute();
//  setDay();
    return;
}

void Clock::setMicrosecond()
{
    if (microsecond >= 999) {
        setMillisecond();
        microsecond = 0;
    }
    else {
        microsecond++;
    }

    return;
}

void Clock::setMillisecond()
{
    if (millisecond >= 999) {
        setSecond();
        millisecond = 0;
    }
    else {
        millisecond++;
    }

    return;
}

void Clock::setSecond()
{
    if (second == 59) {
        setMinute();
        second = 0;
    }
    else {
        second++;
    }

    return;
}

void Clock::setMinute()
{
    if (minute == 59) {
        setHour();
        minute = 0;
    }
    else {
        minute++;
    }

    return;
}

void Clock::setHour()
{
    if (hour == 23) {
        setDay();
        hour = 0;
    }
    else {
        hour++;
    }

    return;
}

void Clock::setDay()
{
    bool thirtydays = false;
    bool feb = false;
    bool leap = false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        // April, June, September, November.
        thirtydays = true;
    }

    if (month == 2) {  // test for February
        feb = true;
    }

    //
    // A year is a leap year if it is divisible by 4, but not by 100.
    //
    // If a year is divisible by 4 and by 100, it is a leap year only
    // if it is also divisible by 400.
    ///
    if ((year%4 == 0 && year%100 != 0) ||
            (year%4 == 0 && year%100 == 0 && year%400 == 0)) {
        leap = true;
    }

    if ((day == 28) && (feb) && (!leap)) {
        setMonth();
        day = 1;
    }
    else if ((day == 29) && (feb) && (leap)) {
        setMonth();
        day = 1;
    }
    else if ((day == 30) && (thirtydays == true)) {
        setMonth();
        day = 1;
    }
    else if ((day == 31) && (thirtydays == false)) {
        setMonth();
        day = 1;
    }
    else {
        day++;
    }

    return;
}

void Clock::setMonth()
{
    if (month >= 12) {
        setYear();
        month = 1;
    }
    else {
        month++;
    }

    return;
}

void Clock::setYear()
{
    year++;
    if ((year%100) == 0) {
        setCentury();
    }

    return;
}

void Clock::setCentury()
{
    century++;
    if ((century%10) == 0) {
        setMillenium();
    }

    return;
}

void Clock::setMillenium()
{
    millenium++;

    return;
}

long Clock::getTicks()
{
    return ticks;
}

int Clock::getId()
{
    return id;
}

int Clock::getMicrosecond()
{
    return microsecond;
}

int Clock::getMillisecond()
{
    return millisecond;
}

int Clock::getSecond()
{
    return second;
}

int Clock::getMinute()
{
    return minute;
}

int Clock::getHour()
{
    return hour;
}

int Clock::getDay()
{
    return day;
}

int Clock::getMonth()
{
    return month;
}

int Clock::getYear()
{
    return year;
}

int Clock::getCentury()
{
    return century;
}

int Clock::getMillenium()
{
    return millenium;
}


}//endfnctn*/
