// roveWareWrappers.h MST MRDT 2015
//
// Judah Schad jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare

#ifndef ROVEWARETIVAWRAPPERS_H_
#define ROVEWARETIVAWRAPPERS_H_

//C lib
//#include <stdint.h>
//#include <string.h>
//#include <stdbool.h>
#include <stdio.h>

//CCS TI config
#include <xdc/std.h>

#include <xdc/cfg/global.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

//CCS TI operating system
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

//TI hardware access routines//TODO
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
/*
//TI BIOS hardware drivers//TODO
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "inc/hw_memmap.h"
*/
// mrdt::rovWare

//MRDT shorthand
#define ERROR -1

//These struct_id and payload definitions are how messages get version coupled to Base Station

//motor command struct_id and struct
#define motor_drive_right_id 100
#define motor_drive_left_id 101

struct motor_control_struct{

    char struct_id;
    int speed;

}__attribute__((packed));

//test command struct_id and struct
#define test_command_id 206

struct test_control_struct{

    char struct_id;
    int test_value;

}__attribute__((packed));

//test telemetry struct_id and struct
#define test_device_id 0

struct test_device_struct {

    char struct_id;
    int test_value;

}__attribute__((packed));

//hardware parameters

#define TEST_DEVICE_PIN 0

//Tiva Get/Set Wrappers

void rovePWM_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds);

int roveUART_Write(int tiva_pin, char* write_buffer, int bytes_to_write);

int roveUART_Read(int tiva_pin, char* read_buffer, int bytes_to_read);

void rovePrintf_ByteBuffer(char* printf_buffer, int bytes_to_printf);

int roveGetDeviceId_PinNum(char struct_id);

int roveGetStructId_ByteCnt(char struct_id);

void rovePrintf_RoveStructs(char* printf_buffer, char struct_id);


/* Physicl Pin Outs:

//GPIO pins
#define PH0_GPIO_PIN 0
#define PH1_GPIO_PIN 1
#define PM6_GPIO_PIN 2
#define PM7_GPIO_PIN 3
#define PL0_GPIO_PIN 4
#define PL1_GPIO_PIN 5
#define PK2_GPIO_PIN 6
#define PK3_GPIO_PIN 7
#define PE0_GPIO_PIN 8
#define PE1_GPIO_PIN 9

// UART pins
#define U2RX PA6_UART_2
#define U2TX PA7_UART_2
#define U3RX PA4_UART_3
#define U3TX PA5_UART_3
#define U4RX PK0_UART_4
#define U4TX PK1_UART_4
#define U5RX PC6_UART_5
#define U5TX PC7_UART_5
#define U6RX PP0_UART_6
#define U6TX PP1_UART_6
#define U7RX PC4_UART_7
#define U7TX PC5_UART_7

*/

#endif /* ROVEWAREWRAPPERS_H_ */
