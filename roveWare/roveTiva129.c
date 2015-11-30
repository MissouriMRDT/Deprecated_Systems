// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
// roveWare 1294XL Access Routines
//
// mrdt::rovWare
#include "roveTiva129.h"

//rove to Tiva Read/Write Hardware I/O Module Wrappers

int32_t roveUart_Write(int32_t tiva_pin, uint8_t* write_buffer, int32_t bytes_to_write) {

    extern UART_Handle uart_2;
    extern UART_Handle uart_3;
    extern UART_Handle uart_4;
    extern UART_Handle uart_5;
    extern UART_Handle uart_6;
    extern UART_Handle uart_7;

    switch (tiva_pin) {

        case HW_TEST_DEVICE_PIN:

            bytes_to_write = UART_write(uart_2, (char*)&write_buffer, bytes_to_write);
            break;
/*TODO
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
*/
        default:
            printf("roveUARTWrite passed invalid device: %d\n", tiva_pin);
            return HW_ERROR;
    }//end switch
    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    return bytes_to_write;
}//endfnctn roveUARTWrite

int32_t roveUart_Read(int32_t tiva_pin, uint8_t* read_buffer, int32_t bytes_to_read) {

    extern UART_Handle uart_2;
    extern UART_Handle uart_3;
    extern UART_Handle uart_4;
    extern UART_Handle uart_5;
    extern UART_Handle uart_6;
    extern UART_Handle uart_7;

    switch (tiva_pin) {

        case HW_TEST_DEVICE_PIN:
            //uart 2 is just the only muxless 485 Jack wired to a uart onboard Horizon's MOB pcb
            bytes_to_read = UART_read(uart_2, (char*)&read_buffer, bytes_to_read);
            break;

        default:
            printf("roveUARTRead was passed invalid UART: %d\n", tiva_pin);
            return HW_ERROR;
    }//endswitch
    //now holds the number of bytes actually read
    return bytes_to_read;
}//endfnctn roveUARTRead

void rovePwm_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds) {

    PWM_setDuty(tiva_pin, duty_in_microseconds);
    return;
}//endfnctn pwmWrite

void roveDigital_Write(int32_t tiva_pin, int32_t high_or_low) {

    if(high_or_low == 0){

        switch(tiva_pin) {

/*TODO            case TRI_STATE_PIN:
*/
            default:
                printf("roveDigital_Write passed invalid pin %d\n", tiva_pin);
                return;
        }//endswitch
    } else {

        switch(tiva_pin){

            case HW_TRI_STATE_PIN:
                //TODO
                //123G = PB3
                GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, GPIO_PIN_0);
                break;

            default:
                printf("roveDigital_Write passed invalid pin %d\n", tiva_pin);
        }//endswitch
    }//endif
    return;
}//endfnctn roveDigital_Write

//TODO sysctl.h
//*****************************************************************************
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
//*****************************************************************************

void roveDelay_MilliSec(uint32_t milliseconds) {

    //SysCtlDelay(milliseconds * (SysCtlClockGet() / 100));
}//endfnctn roveDelay_MilliSec

void roveDelay_MicroSec(uint32_t microseconds) {

    //SysCtlDelay(microseconds * (SysCtlClockGet() / 100000));
}//endfnctn roveDelay_MilliSec

//roveWare 2016
//TODO this function is maintenence hardcoded hardware cfg paradigm tho-> put in cfg file?
int32_t roveGetPinNum_ByDeviceId(int32_t data_id){

    switch (data_id) {

    case HW_TEST_DEVICE_ID:

        return HW_TEST_DEVICE_PIN;

    default:
        printf("roveGetDevicePin passed invalid device %d\n", data_id);
        return HW_ERROR;
    }//endswitch
}//endfnctn roveGetDevicePin


void rovePrintf_ByteBuffer(uint8_t* printf_buffer, int32_t bytes_to_printf) {

    int printf_cnt = 0;
    printf("Buffer holds: ");

    while (printf_cnt < bytes_to_printf) {
        printf(" %d", printf_buffer[printf_cnt]);
        printf_cnt++;
    }//end while

    printf("\n\n");
    return;
}//endfnctn rovePrintfBuffer


//roveWare 2015
int32_t roveGetByteCnt_ByStructId(int32_t struct_id) {

    switch (struct_id) {

        case HW_TEST_DEVICE_ID:

            printf("Testing");
            return NULL;

        default:
            printf("roveGetByteCnt_ByStructId passed invalid struct %d\n", struct_id);
            return HW_ERROR;
    }//endswitch
}//endfnctn roveGetStructSize

/*
uint8_t roveDynamixel_GetUartMessage(int deviceJack, char* buffer) {

    uint8_t rx_len = 0;
    uint8_t startByte = 0x06;
    uint8_t secondByte = 0x85;

    int bytesRead = 0;
    char receiveBuffer[40];

    // This is used to decide how much pre-data to discard before quitting
    uint8_t garbageCount = 10;
    bool startReceived = false;

    //testing
    //int debug_rx_cnt = 0;

    if (rx_len == 0) {

        while (!startReceived) {
            bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500);
            if (bytesRead == 1) {
               // if (receiveBuffer[0] == startByte) {
               //     startReceived = true;
                } else {
                    garbageCount--;
                    if (garbageCount <= 0)
                        return false;
                } //endif
            } //endif
              //debug_rx_cnt++;
        } //endwhile

//      System_printf("Looped through the rx debug_rx_cnt: %d\n", debug_rx_cnt);
//      System_flush();

        if ((bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500)) == 1) {
            if (receiveBuffer[0] != secondByte) {
                return false;
            } else {
                bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500);
                if (bytesRead == 1) {
                    rx_len = receiveBuffer[0];
                    if (rx_len == 0) {
                        return false;
                    } //endif
                } else {
                    return false;
                }
            } //endif

        } //endif
        else {
            return false;
        }

//      System_printf("bytesRead: %d\n", bytesRead);
//      System_flush();

    } //end if (rx_len == 0)

    if (rx_len > 0) {
        bytesRead = deviceRead(deviceJack, receiveBuffer, rx_len + 1, 2000);
        //rx_len + 1 for the checksum byte at the end
        if (bytesRead != (rx_len + 1))
            return false;

        uint8_t calcCS = calcCheckSum(receiveBuffer, rx_len);

        if (calcCS != receiveBuffer[rx_len]) {
            // Checksum error
            return false;
        } //end if

        memcpy(buffer, receiveBuffer, rx_len);
        return true;
    } //end if

    return false;
} //end recvSerialStructMessage

uint8_t roveGetCheckSum_ByStructPtr(const void* my_struct, uint8_t struct_byte_cnt) {

    uint8_t checkSum = size;
    uint8_t i;

    for (i = 0; i < size; i++)
        checkSum ^= *((char*) my_struct + i);

    return checkSum;

} //end fnctn*/
