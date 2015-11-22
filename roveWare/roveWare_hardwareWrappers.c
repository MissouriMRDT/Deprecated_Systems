// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_tivaWrappers.c
//
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// roveWare 1294XL Access Routines
//
// mrdt::rovWare

#include "roveWare_hardwareWrappers.h"

//rove to Tiva Read/Write Hardware I/O Module Wrappers

void rovePWM_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds) {

    PWM_setDuty(tiva_pin, duty_in_microseconds);

}//endfnctn pwmWrite

void roveDigital_Write(int tiva_pin, int high_or_low) {

    if(high_or_low == LOW){

        switch(tiva_pin) {

            case TRI_STATE_BUFFER:

            default:

                printf("digitalWrite passed invalid pin %d\n", tiva_pin);
                return;

        }//endswitch

    } else {

        switch(tiva_pin){

            case TRI_STATE_BUFFER:

                //TODO
                //123G = PB3
                GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, GPIO_PIN_0);
                break;

            default:

                printf("roveDigital_Write passed invalid pin %d\n", tiva_pin);
                return;

        }//endswitch

    }//endif

    return;

}//endfnctn roveDigital_Write

int roveUART_Write(int tiva_pin, char* write_buffer, int bytes_to_write) {

    extern UART_Handle uart_2;
    extern UART_Handle uart_3;
    extern UART_Handle uart_4;
    extern UART_Handle uart_5;
    extern UART_Handle uart_6;
    extern UART_Handle uart_7;

    switch (tiva_pin) {

        case TEST_DEVICE_PIN:

            bytes_to_write = UART_write(uart_2, write_buffer, bytes_to_write);
            break;

        case ARM_UART:
            //U3TX PA5_UART_3
            //123G = TX PC5 DYNAMIXEL_UART
            bytes_to_write = UART_write(uart_3, write_buffer, bytes_to_write);
            break;

        case END_EFFECTOR_UART:
            //U4TX PK1_UART_4
            //123G  = TX PC7 END_EFFECTOR_UART
            bytes_to_write = UART_write(uart_4, write_buffer, bytes_to_write);
            break;

        case LIN_ACT_UART:
            //U5TX PC7_UART_5
            //123G  = TX PE1 LINEAR_ACTUATOR_UART
            bytes_to_write = UART_write(uart_5, write_buffer, bytes_to_write);
            break;

        default:

            printf("roveUARTWrite passed invalid device: %d\n", tiva_pin);

        return ERROR;

    }//end switch

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);

    return bytes_to_write;

}//endfnctn roveUARTWrite

int roveUART_Read(int tiva_pin, char* read_buffer, int bytes_to_read) {

    extern UART_Handle uart_2;
    extern UART_Handle uart_3;
    extern UART_Handle uart_4;
    extern UART_Handle uart_5;
    extern UART_Handle uart_6;
    extern UART_Handle uart_7;

    switch (tiva_pin) {

        case TEST_DEVICE_PIN:

            //uart 2 is just the only muxless 485 Jack wired to a uart onboard Horizon's MOB pcb
            bytes_to_read = UART_read(uart_2, read_buffer, bytes_to_read);
            break;

        default:

            printf("roveUARTRead was passed invalid UART: %d\n", tiva_pin);

        return ERROR;

    }//endswitch

    //now holds the number of bytes actually read
    return bytes_to_read;

}//endfnctn roveUARTRead

//TODO sysctl.h

//*****************************************************************************
//
//! Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock, which is
//! also the clock rate of the peripheral modules (with the exception of
//! PWM, which has its own clock divider; other peripherals may have different
//! clocking, see the device data sheet for details).
//!
//! \note This cannot return accurate results if SysCtlClockSet() has not
//! been called to configure the clocking of the device, or if the device is
//! directly clocked from a crystal (or a clock source) that is not one of the
//! supported crystal frequencies.  In the latter case, this function should be
//! modified to directly return the correct system clock rate.
//!
//! \note This function can only be called on TM4C123 devices.  For TM4C129
//! devices, the return value from SysCtlClockFreqSet() indicates the system
//! clock frequency.
//!
//! \return The processor clock rate for TM4C123 devices only.
//
//*****************************************************************************

void roveDelay_MilliSec(uint32_t milliseconds) {

    //SysCtlDelay(milliseconds * (SysCtlClockGet() / 100));

} //endfnctn roveDelay_MilliSec

void roveDelay_MicroSec(uint32_t microseconds) {

    //SysCtlDelay(microseconds * (SysCtlClockGet() / 100000));

} //endfnctn roveDelay_MilliSec

//roveWare 2016


int16_t rovePinNum_ByDeviceId(uint8_t data_id) {

    switch (data_id) {

    case TEST_DEVICE_ID:

        return TEST_DEVICE_PIN;

    default:

        printf("roveGetDevicePin passed invalid device %d\n", data_id);

        return ERROR;

    }//endswitch


}//endfnctn roveGetDevicePin


void rovePrintf_ByteBuffer(uint8_t* printf_buffer, uint16_t bytes_to_printf) {

    int printf_cnt = 0;

    printf("Buffer holds: ");

    while (printf_cnt < bytes_to_printf) {

        printf(" %d", printf_buffer[printf_cnt]);

        printf_cnt++;

    } //end while

    printf("\n\n");

    return;

}//endfnctn rovePrintfBuffer


//roveWare 2015

int16_t roveGetByteCnt_ByStructId(uint8_t struct_id) {

    switch (struct_id) {

        case TEST_DEVICE_ID:

            printf("Testing");

            return NULL;

        default:

            printf("roveGetByteCnt_ByStructId passed invalid struct %d\n", struct_id);

            return ERROR;

    }//endswitch

} //endfnctn roveGetStructSize
