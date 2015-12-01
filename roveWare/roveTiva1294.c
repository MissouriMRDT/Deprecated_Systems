// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
// roveWare 1294XL Access Routines
//
// mrdt::rovWare
#include "roveTiva1294.h"

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

//TODO            case TRI_STATE_PIN:
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



void roveDelay_MilliSec(uint32_t milliseconds) {

    //SysCtlDelay(milliseconds * (SysCtlClockGet() / 100));
}//endfnctn



void roveDelay_MicroSec(uint32_t microseconds) {

    //SysCtlDelay(microseconds * (SysCtlClockGet() / 100000));
}//endfnctn
