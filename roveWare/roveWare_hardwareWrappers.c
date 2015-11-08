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

/*
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
    ms_delay(1);

    return bytes_to_write;

}//endfnctn roveUARTWrite
*/

int deviceWrite(int device_port, char* write_buffer,  int bytes_to_write)
{
    int bytes_wrote;

    // give us access to the uart handles defined at the global scope in main
    extern UART_Handle uart2;
    extern UART_Handle uart3;
    extern UART_Handle uart4;
    extern UART_Handle uart7;

    //System_printf("deviceWrite called\n");
    //System_flush();

    if(bytes_to_write < 0)
    {
        return -1;
    }//end if

    switch(device_port)
    {
        case DYNAMIXEL_UART:

            bytes_wrote = UART_write(uart3, write_buffer, bytes_to_write);

        break;
        case LINEAR_ACTUATOR_UART:

            bytes_wrote = UART_write(uart5, write_buffer, bytes_to_write);

        break;

        case END_EFFECTOR_UART:

             bytes_wrote = UART_write(uart4, write_buffer, bytes_to_write);

        break;

        default:

            return -1;
            //System_printf("DeviceWrite passed invalid device %d\n", device_port);
            //System_flush();

        //etc.
    }//end switch(jack)

    // make sure the message is fully written before leaving the function

    //ms_delay(1);

    return bytes_wrote;

}//endfnctn deviceWrite
void digitalWrite(int tiva_pin, int high_or_low) {

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

void ms_delay(int milliseconds) {

    SysCtlDelay(milliseconds * (SysCtlClockGet() / 100));

} //endfnctn ms_delay( int milliseconds )
