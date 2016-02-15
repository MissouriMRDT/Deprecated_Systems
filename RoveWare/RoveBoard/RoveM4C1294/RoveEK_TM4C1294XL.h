/*
 * roveEK_TM4C1294XL.h
 *
 *  Created on: Jan 15, 2016
 *      Author: mrdtdev
 //

#ifndef ROVEEK_TM4C1294XL_H_
#define ROVEEK_TM4C1294XL_H_

/*



#include <stdint.h>
#include <stdbool.h>

#include <inc/hw_memmap.h>
//#include <inc/hw_types.h>
#include <inc/hw_ints.h>
//#include <inc/hw_gpio.h>

#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>
#include <driverlib/timer.h>
#include <driverlib/interrupt.h>







//roveBoard/rove_drivers -> roveCCPTiva.h

typedef struct roveCCPTiva_HWAttrs
{
    unsigned int baseAddr;
    unsigned int intNum;
} roveCCPTiva_HWAttrs;

typedef struct roveCCPTiva_Object
{
    //Todo uint16_t ccp_data;
} roveCCPTiva_Object;



//roveBoard/rove_drivers -> roveCCPTiva.c

void roveCCPTiva_init(roveCCP_Handle handle);

void roveCCPTiva_open(roveCCP_Handle handle, roveCCP_Params *params);

void roveCCPTiva_init(roveCCP_Handle handle)
{
    //uint8_t                statusIndex;
    roveCCPTiva_Object        *object = handle->object;
    roveCCPTiva_HWAttrs const *hwAttrs = handle->hwAttrs;
    //Todo
}//end fnctn

//
//  ======== rovecCPTiva_open ========
//
roveCCP_Handle roveCCPTiva_open(roveCCP_Handle handle, roveCCP_Params *params)
{
    unsigned int               key;
    Types_FreqHz               freq;
    UARTTiva_Object           *object = handle->object;
    UARTTiva_HWAttrs const    *hwAttrs = handle->hwAttrs;
    union {
        Hwi_Params             hwiParams;
        Semaphore_Params       semParams;
    } paramsUnion;

    // If params are NULL use defaults.
    if (params == NULL) {
        params = (UART_Params *) &UART_defaultParams;
    }

    // Check that a callback is set
    Assert_isTrue((params->readMode != UART_MODE_CALLBACK) ||
                  (params->readCallback != NULL), NULL);
    Assert_isTrue((params->writeMode != UART_MODE_CALLBACK) ||
                  (params->writeCallback != NULL), NULL);

    object->readMode       = params->readMode;
    object->writeMode      = params->writeMode;
    object->readTimeout    = params->readTimeout;
    object->writeTimeout   = params->writeTimeout;
    object->readCallback   = params->readCallback;
    object->writeCallback  = params->writeCallback;
    object->readReturnMode = params->readReturnMode;
    object->readDataMode   = params->readDataMode;
    object->writeDataMode  = params->writeDataMode;
    object->readEcho       = params->readEcho;

    // Disable preemption while checking if the UART is open.
    key = Hwi_disable();

    // Check if the UART is open already with the base addr.
    if (object->opened == true) {
        Hwi_restore(key);

        Log_warning1("UART:(%p) already in use.", hwAttrs->baseAddr);
        return (NULL);
    }

    object->opened = true;
    Hwi_restore(key);

    // Set UART variables to defaults.
    object->writeBuf = NULL;
    object->readBuf = NULL;
    object->writeCount = 0;
    object->readCount = 0;
    object->writeSize = 0;
    object->readSize = 0;
    object->writeCR = false;

    // Create Hwi object for this UART peripheral.
    Hwi_Params_init(&(paramsUnion.hwiParams));
    paramsUnion.hwiParams.arg = (UArg)handle;

    Hwi_construct(&(object->hwi), hwAttrs->intNum, UARTTiva_hwiIntFxn,
                  &(paramsUnion.hwiParams), NULL);

    Semaphore_Params_init(&(paramsUnion.semParams));
    paramsUnion.semParams.mode = Semaphore_Mode_BINARY;

    // If write mode is blocking create a semaphore and set callback.
    if (object->writeMode == UART_MODE_BLOCKING) {
        Semaphore_construct(&(object->writeSem), 0, &(paramsUnion.semParams));
        object->writeCallback = &writeSemCallback;
    }

    // If read mode is blocking create a semaphore and set callback.
    if (object->readMode == UART_MODE_BLOCKING) {
        Semaphore_construct(&(object->readSem), 0, &(paramsUnion.semParams));
        object->readCallback = &readSemCallback;
    }

    // Enable UART and its interrupt.
    UARTIntClear(hwAttrs->baseAddr, (UART_INT_TX | UART_INT_RX | UART_INT_RT));
    UARTIntEnable(hwAttrs->baseAddr, (UART_INT_TX | UART_INT_RX | UART_INT_RT));
    UARTEnable(hwAttrs->baseAddr);

    // Set the FIFO level to 7/8 empty and 7/8 full.
    UARTFIFOLevelSet(hwAttrs->baseAddr, UART_FIFO_TX1_8, UART_FIFO_RX7_8);

    BIOS_getCpuFreq(&freq);
    UARTConfigSetExpClk(hwAttrs->baseAddr,
                        freq.lo,
                        params->baudRate,
                        dataLength[params->dataLength] |
                        stopBits[params->stopBits] |
                        parityType[params->parityType]);

    Log_print3(Diags_USER1, "UART:(%p) CPU freq: %d; UART baudrate to %d",
               hwAttrs->baseAddr, freq.lo, params->baudRate);

    Log_print1(Diags_USER1, "UART:(%p) opened", hwAttrs->baseAddr);

    // Return the handle
    return (handle);
}



int UARTTiva_read(UART_Handle handle, void *buffer, size_t size)
{
    unsigned int        key;
    UARTTiva_Object    *object = handle->object;

    /* Disable preemption while checking if the uart is in use.
    key = Hwi_disable();
    if (object->readSize) {
        Hwi_restore(key);

        Log_warning1("UART:(%p) Could not read data, uart in use.",
                     ((UARTTiva_HWAttrs const *)(handle->hwAttrs))->baseAddr);
        return (UART_ERROR);
    }

    /* Save the data to be read and restore interrupts.
    object->readBuf = buffer;
    object->readCount = 0;

    Hwi_restore(key);

    if (!(object->readSize = readData(object, (UARTTiva_HWAttrs *) handle->hwAttrs, size))) {
        /* Read is finished. //
        Log_print2(Diags_USER1, "UART:(%p) Read finished, %d bytes read",
                   ((UARTTiva_HWAttrs const *)(handle->hwAttrs))->baseAddr,
                   object->readCount);

        if (object->readMode == UART_MODE_CALLBACK) {
            /* Reset the read buffer so we can pass it back
            object->readBuf = (unsigned char *)object->readBuf - object->readCount;
            object->readCallback(handle, object->readBuf, object->readCount);

            /* Return 0 for UART_MODE_CALLBACK
            return (0);
        }
        return (object->readCount);
    }

    /* If readMode is blocking, block and get the status.
    if (object->readMode == UART_MODE_BLOCKING) {
        /* Pend on semaphore and wait for Hwi to finish.
        if (!Semaphore_pend(Semaphore_handle(&(object->readSem)),
                            object->readTimeout)) {
            /* Semaphore timed out, make the read empty and log the read.
            object->readSize = 0;

            Log_print2(Diags_USER1, "UART:(%p) Read timed out, %d bytes read",
                       ((UARTTiva_HWAttrs const *)(handle->hwAttrs))->baseAddr,
                       object->readCount);

        }
        return (object->readCount);
    }

    return (0);
}


int UARTTiva_readPolling(UART_Handle handle, void *buf, size_t size)
{
    int32_t                    count = 0;
    UARTTiva_Object           *object = handle->object;
    UARTTiva_HWAttrs const    *hwAttrs = handle->hwAttrs;
    unsigned char             *buffer = (unsigned char *)buf;

    /* Read characters. //
    while (size) {
        *buffer = UARTCharGet(hwAttrs->baseAddr);
        Log_print2(Diags_USER2, "UART:(%p) Read character 0x%x",
                   hwAttrs->baseAddr, *buffer);
        count++;
        size--;

        if (object->readDataMode == UART_DATA_TEXT && *buffer == '\r') {
            /* Echo character if enabled. //
            if (object->readEcho) {
                UARTCharPut(hwAttrs->baseAddr, '\r');
            }
            *buffer = '\n';
        }

        /* Echo character if enabled. //
        if (object->readEcho) {
            UARTCharPut(hwAttrs->baseAddr, *buffer);
        }

        /* If read return mode is newline, finish if a newline was received.
        if (object->readReturnMode == UART_RETURN_NEWLINE &&
            *buffer == '\n') {
            return (count);
        }

        buffer++;
    }

    Log_print2(Diags_USER1, "UART:(%p) Read polling finished, %d bytes read",
               hwAttrs->baseAddr, count);

    return (count);
}

/*
 *  ======== UARTTiva_readCancel ========
 //
void UARTTiva_readCancel(UART_Handle handle)
{
    unsigned int        key;
    UARTTiva_Object    *object = handle->object;

    /* Disable interrupts to avoid reading data while changing state. //
    key = Hwi_disable();

    /* Return if there is no read. //
    if (!object->readSize) {
        Hwi_restore(key);
        return;
    }

    /* Set size = 0 to prevent reading and restore interrupts. //
    object->readSize = 0;
    Hwi_restore(key);

    /* Reset the read buffer so we can pass it back //
    object->readBuf = (unsigned char *)object->readBuf - object->readCount;
    object->readCallback(handle, object->readBuf, object->readCount);

    Log_print2(Diags_USER1, "UART:(%p) Read canceled, %d bytes read",
               ((UARTTiva_HWAttrs const *)(handle->hwAttrs))->baseAddr,
               object->readCount);
}



const UART_Params roveCCP_Params_init = {
  /* Todo UART_MODE_BLOCKING, //  readMode
    UART_MODE_BLOCKING,   //  writeMode
    BIOS_WAIT_FOREVER,    //  readTimeout
    BIOS_WAIT_FOREVER,    //  writeTimeout
    NULL,                 //  readCallback
    NULL,                 //  writeCallback
    UART_RETURN_NEWLINE,  //  readReturnMode
    UART_DATA_TEXT,       //  readDataMode
    UART_DATA_TEXT,       //  writeDataMode
    UART_ECHO_ON,         //  readEcho
    UART_LEN_8,           //  dataLength
    UART_STOP_ONE,        //  stopBits
    UART_PAR_NONE,        //  parityType//
    NULL                  //  custom
};


//int16_t roveBoard_CaptureCompareRead(roveCaptureCompareRead_Handle) {
//listen for next Pwm Pulse
//start Pwm Pulse listen
TimerEnable(TIMER3_BASE, TIMER_A);
roveCCP_Handle roveBoard_CcpOpen(unsigned int ccp_index) {

  TimerClockSourceSet(TIMER3_BASE, TIMER_CLOCK_SYSTEM);

  //Split Timer Three as two 16 bit Timer Pin with Capture Register for 16 bit TIMER_A
  //(Frees up TIMER_B T3CCP1 for another gpio pin?)
  TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME);

  //Trigger the interrupt for BOTH rising and falling (dual half wave rise/fall edges)
  TimerControlEvent(TIMER3_BASE, TIMER_A, TIMER_EVENT_BOTH_EDGES);

  //Starting the timer at max value? what in relation to any prescaler?
  TimerLoadSet(TIMER3_BASE, TIMER_A, 0xffff);

  //Enable the timer to capture an event in a register for us
  TimerIntEnable(TIMER3_BASE, TIMER_CAPA_EVENT);

  //Enable the interrupt tied to the timer
  IntEnable(INT_TIMER3A);

  //Enable all interrupt schedules
  IntMasterEnable();






//roveBoard/rove_drivers -> roveCCP.h

typedef struct roveCCP_Config      *roveCCP_Handle;

typedef struct roveCCP_Params
{
    //Todo
} roveCCP_Params;

typedef struct roveCCP_Config
{
    void               *object;
    void         const *hwAttrs;
} roveCCP_Config;

extern void roveCCP_init(void);
extern void roveCCP_Params_init(roveCCP_Params *params);
extern roveCCP_Handle roveCCP_open(unsigned int index, roveCCP_Params *params);

//roveBoard/rove_drivers -> roveCCP.c

//TODODODODOD Default UART parameters structure
const UART_Params roveCCP_Params_init = {
  /* Todo UART_MODE_BLOCKING, //  readMode
    UART_MODE_BLOCKING,   //  writeMode
    BIOS_WAIT_FOREVER,    //  readTimeout
    BIOS_WAIT_FOREVER,    //  writeTimeout
    NULL,                 //  readCallback
    NULL,                 //  writeCallback
    UART_RETURN_NEWLINE,  //  readReturnMode
    UART_DATA_TEXT,       //  readDataMode
    UART_DATA_TEXT,       //  writeDataMode
    UART_ECHO_ON,         //  readEcho
    UART_LEN_8,           //  dataLength
    UART_STOP_ONE,        //  stopBits
    UART_PAR_NONE,        //  parityType//
    NULL                  //  custom
};

//
//  ======== roveCCP_init ========
//
void roveCCP_init(void)
{
    if (roveCCP_count == -1) {
        // Call each driver's init function
        for (roveCCP_count = 0; roveCCP_config[CCP_count]; roveCCP_count++) {
            roveCCPTiva_init( &(roveCCP_config[roveCCP_count]) );
        }//end for
    }//end if
}//end fnctn

//
//  ======== roveCCP_Params_init ========
//
void roveCCP_Params_init(roveCCP_Params *params)
{
   *params = roveCCP_defaultParams;
}

//
//  ======== roveCCP_Open ========
//
roveCCP_Handle roveCCP_Open(unsigned int index, roveCCP_Params *params)
{
    roveCCP_Handle         handle;

    // Get handle for this driver instance
    handle = (roveCCP_Handle)&(roveCCP_Config[index]);

    return roveCCPTiva_open(handle, params);
}








//roveBoard/roveEK_TM4C1294Xl.h

extern void roveEK_TM4C1294XL_initCCP(void);

typedef enum roveEK_TM4C1294XL_CCPName
{
    //roveWare16 Custom Cfg
    EK_TM4C1294XL_CCP0 = 0,
    //EK_TM4C1294XL_CCP1,
    //EK_TM4C1294XL_CCP2,
    //EK_TM4C1294XL_CCP3,
    //EK_TM4C1294XL_CCP4,
    //EK_TM4C1294XL_CCP5,
    //EK_TM4C1294XL_CCP6,
    //EK_TM4C1294XL_CCP7,
    EK_TM4C1294XL_CCPCOUNT
} roveEK_TM4C1294XL_CCPName;








//roveBoard/roveEK_TM4C1294Xl.c

    //includes roveBoard/driverlibs -> roveEK_TM4C1294Xl.h
    //includes roveBoard/driverlibs -> roveCCPTiva.h

// roveCCP objects
roveCCPTiva_Object roveCCPTivaObjects[EK_TM4C1294XL_CCPCOUNT];

// UART configuration structure
const roveCCPTiva_HWAttrs roveCcpTivaHWAttrs[EK_TM4C1294XL_CCPCOUNT] = {

    //roveWare16 Custom Cfg
    {TIMER3_BASE, INT_TIMER3A},
    //{TIMER3_BASE, INT_TIMERBA},
    //{TIMER4_BASE, },
    //{TIMER4_BASE, },
    //{TIMER5_BASE, },
    //{TIMER5_BASE, },
};

const roveCCP_Config roveCCP_config[] = {

    //roveWare16 Custom Cfg
    {&roveCcpTivaObjects[0], &roveCcpTivaHWAttrs[0]},
    //{&roveCcpTivaObjects[1], &roveCcpTivaHWAttrs[1]},
    //{&roveCcpTivaObjects[2], &roveCcpTivaHWAttrs[2]},
    //{&roveCcpTivaObjects[3], &roveCcpTivaHWAttrs[3]},
    //{&roveCcpTivaObjects[4], &roveCcpTivaHWAttrs[4]},
    //{&roveCcpTivaObjects[5], &roveCcpTivaHWAttrs[5]},
    {NULL, NULL, NULL}
};

void roveEK_TM4C1294XL_initCCP()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);

    //Port M Pin Two is first available Timer 3 CPP Pin
    //(T3CPP0 : PA6, PM2, PD4 : We are using PA6 as Uart2 already in Device Template serial)
    GPIOPinConfigure(GPIO_PM2_T3CCP0);
    GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_2);

    roveCCP_init();
}//end fnctn





















//Todo Hardware Handle Shorthand
typedef struct roveGPIO_Config      *roveGPIO_Handle;
typedef struct roveGPIO_Config
{
    uint32_t port;
    uint8_t pin;
} roveGPIO_Struct;
//void roveBoard_GPIO_digitalWrite(roveGPIO_Handle gpio_pin, uint8_t digital_value);
//roveGPIO_Handle roveBoard_GPIO_open(roveGPIO_Handle gpio , uint32_t gpio_port , uint8_t gpio_pin);
























///////////////////////////////////
 My thoughts on reading Pwm:

Basically the CAP means it holds the value in a register for us

We can Split the Timers into two Capture Pins

We should disable the interrupt and Post the HWI interrupt to a Software Interrupt at a lower priority to come back and process

We can THEN do all the math inside the Software Swi Handler and get the TimerValueGet(TIMER3_BASE, TIMER_A) out of the capture register

Then we re-enable that pin for pulse interrupt and listen for another pulse (we were not listening while Software Proccess was Posting)

We actually might be better off to start with capturing rising edge and at the interrupt configure for falling edge and posting two seperate Swi off one single Hwi, but for right now I just leave an empty Swi post




//main
BIOS_start();
}

//extern handle for rtos Cplus object callback HARDWARE Isr
extern "C" void hwi_CapturePwmPulse_Fxn(void)
{
    //keep from interrupting our own hndler
    TimerIntClear(TIMER3_BASE, TIMER_CAPA_EVENT);

    Swi_post(swi_PostPwmPeriod);
}

//extern handle for rtos Cplus object callback SOFTWARE Isr
extern "C" void swi_PostPwmPeriod_Fxn(void)
{
    //Flash the Led on success
    GPIO_toggle(Board_LED0);

//Would be things like Duty = (PreviousCapture - CurrentCapture)/Period;

    //listen for next Pwm Pulse
    TimerEnable(TIMER3_BASE, TIMER_A);
}





//.cfg file
// EK_TM4C1294XL.c file

//HWi added in the CCS Gui
//hwi_CapturePwmPulse_Fxn
//INT_TIMER3A
//vector table value 51

//SWi added in the CCS Gui
//swi_PostPwmPeriod_Fxn
//


#endif /* ROVEEK_TM4C1294XL_H_ //
