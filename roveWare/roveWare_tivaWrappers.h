// roveWareWrappers.h MST MRDT 2015
//
// Judah Schad jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare

#ifndef ROVEWARE_TIVAWRAPPERS_H_
#define ROVEWARE_TIVAWRAPPERS_H_

//mrdt::rovWare Horizon Protocol Definitions
#include "roveWare_StructId_Protocol.h"

//C lib
#include <stdio.h>

//TI hardware access routines
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>

//mrdt shorthand
#define ERROR -1

//Tiva Get/Set Wrappers
void rovePWM_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds);

int roveUART_Write(int tiva_pin, char* write_buffer, int bytes_to_write);

int roveUART_Read(int tiva_pin, char* read_buffer, int bytes_to_read);

void rovePrintf_ByteBuffer(char* printf_buffer, int bytes_to_printf);

int roveGetDeviceId_PinNum(char struct_id);

int roveGetStructId_ByteCnt(char struct_id);

// Physicl Pin Outs:

// GPIO pins
// PH0_GPIO_PIN 0
// PH1_GPIO_PIN 1
// PM6_GPIO_PIN 2
// PM7_GPIO_PIN 3
// PL0_GPIO_PIN 4
// PL1_GPIO_PIN 5
// PK2_GPIO_PIN 6
// PK3_GPIO_PIN 7
// PE0_GPIO_PIN 8
// PE1_GPIO_PIN 9

// UART pins
// U2RX PA6_UART_2
// U2TX PA7_UART_2
// U3RX PA4_UART_3
// U3TX PA5_UART_3
// U4RX PK0_UART_4
// U4TX PK1_UART_4
// U5RX PC6_UART_5
// U5TX PC7_UART_5
// U6RX PP0_UART_6
// U6TX PP1_UART_6
// U7RX PC4_UART_7
// U7TX PC5_UART_7

#endif //ROVEWARE_TIVAWRAPPERS_H_
