// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_tivaWrappers.h
//
// jrs6w7@mst.edu
//
// module for utlity wrapper access to Texas Instruments TivaWare
//
// mrdt::rovWare

#ifndef ROVEWARE_TIVAWRAPPERS_H_
#define ROVEWARE_TIVAWRAPPERS_H_

//mrdt::rovWare Horizon Protocol Definitions
#include "roveWare_Protocol.h"

//C lib
#include <stdio.h>

//TI hardware access routines
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>

//mrdt shorthand
#define ERROR -1
#define HIGH 1
#define LOW 0

//Tiva Get/Set Wrappers
void digitalWrite(int tiva_pin, int high_or_low);

void rovePWM_Write(PWM_Handle tiva_pin, int16_t duty_in_microseconds);

int roveUART_Write(int tiva_pin, char* write_buffer, int bytes_to_write);

int roveUART_Read(int tiva_pin, char* read_buffer, int bytes_to_read);

void rovePrintf_ByteBuffer(char* printf_buffer, int bytes_to_printf);

int roveGetDeviceId_PinNum(char data_id);

int roveGetStructId_ByteCnt(char data_id);

#endif //ROVEWARE_TIVAWRAPPERS_H_
