// roveWareWrappers.c MST MRDT 2015
//
// Judah Schad jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// roveWare 1294XL Access Routines
//
// mrdt::rovWare

#include "roveWare_tivaWrappers.h"

//rove to Tiva Read/Write Hardware I/O Module Wrappers
void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed){

    int16_t microseconds;

    //scale down to the final range to be between 1000 and 2000
    microseconds = speed / 2;

    //offset so that 1500 is neutral
    microseconds += 1500;

    //protect the upper bound on motor pulse width
    if (microseconds > 2000) {

        microseconds = 2000;

    }//endif

    //protect the lower bound on motor pulse width
    if (microseconds < 1000) {

        microseconds = 1000;

    }//endif

    rovePWM_Write(motor, microseconds);

    return;

} //endfnct roveDriveMotor_ByPWM

void rovePWM_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds) {

    PWM_setDuty(tiva_pin, duty_in_microseconds);

}//endfnctn pwmWrite

int16_t roveUART_Read(int16_t tiva_pin, char* read_buffer, int16_t bytes_to_read) {

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

    return bytes_to_read;

}//endfnctn roveUARTRead


int16_t roveUART_Write(int16_t tiva_pin, char* write_buffer, int16_t bytes_to_write) {

    extern UART_Handle uart2;
    extern UART_Handle uart3;
    extern UART_Handle uart4;
    extern UART_Handle uart5;
    extern UART_Handle uart6;
    extern UART_Handle uart7;

    switch (tiva_pin) {

        case TEST_DEVICE_PIN:

            bytes_to_write = UART_write(uart2, write_buffer, bytes_to_write);

        break;

        default:

            printf("roveUARTWrite passed invalid device: %d\n", tiva_pin);

        return ERROR;

    }//end switch

    //roveUARTWrite timing issue?
    //ms_delay(1);

    return bytes_to_write;

}//endfnctn roveUARTWrite


void rovePrintf_ByteBuffer(char* printf_buffer, int16_t bytes_to_printf) {

    uint16_t printf_cnt = 0;

    printf("Buffer holds: ");

    while (printf_cnt < bytes_to_printf) {

        printf(" %d", printf_buffer[printf_cnt]);

        printf_cnt++;

    } //end while

    printf("\n\n");

    return;

}//endfnctn rovePrintfBuffer


int16_t roveGetDeviceId_PinNum(int16_t struct_id) {

    switch (struct_id) {

    case test_device_id:

        return TEST_DEVICE_PIN;

    default:

        printf("roveGetDevicePin passed invalid device %d\n", struct_id);

        return ERROR;

    }//endswitch


}//endfnctn roveGetDevicePin


int16_t roveGetStructId_ByteCnt(char struct_id) {

    switch (struct_id) {

        case test_device_id:

           return sizeof(struct test_device_struct);

        case motor_drive_left_id:

            return sizeof(struct motor_control_struct);

        case motor_drive_right_id:

            return sizeof(struct motor_control_struct);

        case test_command_id:

             return sizeof(struct test_control_struct);

        default:

            printf("roveGetStructSize passed invalid struct %d\n", struct_id);

            return ERROR;

    }//endswitch

} //endfnctn roveGetStructSize
