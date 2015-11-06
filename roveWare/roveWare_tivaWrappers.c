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

#include "roveWare_tivaWrappers.h"

//rove to Tiva Read/Write Hardware I/O Module Wrappers
void rovePWM_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds) {

    PWM_setDuty(tiva_pin, duty_in_microseconds);

}//endfnctn pwmWrite

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

            //see the Mob Eagle file for details)

        break;

        default:

            printf("roveUARTRead was passed invalid UART: %d\n", tiva_pin);

        return ERROR;

    }//endswitch

    //now holds the number of bytes actually read
    return bytes_to_read;

}//endfnctn roveUARTRead


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

        default:

            printf("roveUARTWrite passed invalid device: %d\n", tiva_pin);

        return ERROR;

    }//end switch

    //roveUARTWrite timing issue?
    //ms_delay(1);

    return bytes_to_write;

}//endfnctn roveUARTWrite

void digitalWrite(int tiva_pin, int high_or_low) {

    if(high_or_low == LOW){

        switch(tiva_pin) {

            case TRI_STATE_BUFFER:

                //TODO
                //GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (0));
                break;

            default:

                printf("digitalWrite passed invalid pin %d\n", tiva_pin);
                return;

        }//endswitch

    } else {

        switch(tiva_pin){

            case TRI_STATE_BUFFER:

                //~0 implies write without calling GPIO_PIN_3 lookup
                //GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, (~0));
                break;

            default:

                printf("digitalWrite passed invalid pin %d\n", tiva_pin);
                return;

        }//endswitch

    }//endif

    return;

}//endfnctn digitalWrite


int roveGetDeviceId_PinNum(char data_id) {

    switch (data_id) {

    case TEST_DEVICE_ID:

        return TEST_DEVICE_PIN;

    default:

        printf("roveGetDevicePin passed invalid device %d\n", data_id);

        return ERROR;

    }//endswitch


}//endfnctn roveGetDevicePin


int roveGetStructId_ByteCnt(char data_id) {

    switch (data_id) {

        case TEST_DEVICE_ID:

            printf("Testing");

            return NULL;

        default:

            printf("roveGetStructSize passed invalid struct %d\n", data_id);

            return ERROR;

    }//endswitch

} //endfnctn roveGetStructSize

void rovePrintf_ByteBuffer(char* printf_buffer, int bytes_to_printf) {

    int printf_cnt = 0;

    printf("Buffer holds: ");

    while (printf_cnt < bytes_to_printf) {

        printf(" %d", printf_buffer[printf_cnt]);

        printf_cnt++;

    } //end while

    printf("\n\n");

    return;

}//endfnctn rovePrintfBuffer
