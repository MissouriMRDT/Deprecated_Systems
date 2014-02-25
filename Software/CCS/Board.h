#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "EK_LM4F120XL.h"

#define Board_initDMA               EK_LM4F120XL_initDMA
#define Board_initGeneral           EK_LM4F120XL_initGeneral
#define Board_initGPIO              EK_LM4F120XL_initGPIO
#define Board_initI2C				EK_LM4F120XL_initI2C
#define Board_initSDSPI             EK_LM4F120XL_initSDSPI
#define Board_initSPI               EK_LM4F120XL_initSPI
#define Board_initUART              EK_LM4F120XL_initUART
#define Board_initUSB               EK_LM4F120XL_initUSB
#define Board_initWatchdog          EK_LM4F120XL_initWatchdog
#define Board_initWiFi              EK_LM4F120XL_initWiFi

#define Board_LED_ON                EK_LM4F120XL_LED_ON
#define Board_LED_OFF               EK_LM4F120XL_LED_OFF
#define Board_LED0                  EK_LM4F120XL_LED_BLUE
#define Board_LED1                  EK_LM4F120XL_LED_GREEN
#define Board_LED2                  EK_LM4F120XL_LED_RED
#define Board_BUTTON0               EK_LM4F120XL_SW1
#define Board_BUTTON1               EK_LM4F120XL_SW2

#define Board_I2C0
#define Board_I2C1
#define Board_I2C_TMP               EK_LM4F120XL_I2C3
#define Board_I2C_NFC               EK_LM4F120XL_I2C3
#define Board_I2C_TPL0401           EK_LM4F120XL_I2C3

#define Board_SDSPI0                EK_LM4F120XL_SDSPI0

#define Board_SPI0                  EK_LM4F120XL_SPI0
#define Board_SPI1                  EK_LM4F120XL_SPI3
#define Board_SPI_CC3000            EK_LM4F120XL_SPI2
#define Board_SPI_AT45DB
#define Board_SPI_CS0

#define Board_USBDEVICE             EK_LM4F120XL_USBDEVICE

#define Board_UART0                 EK_LM4F120XL_UART0
#define Board_UART1                 EK_LM4F120XL_UART1
#define Board_UART2                 EK_LM4F120XL_UART2
#define Board_UART3                 EK_LM4F120XL_UART3
#define Board_UART4                 EK_LM4F120XL_UART4
#define Board_UART5                 EK_LM4F120XL_UART5
#define Board_UART7                 EK_LM4F120XL_UART7

#define Board_WATCHDOG0             EK_LM4F120XL_WATCHDOG0

#define Board_WIFI                  EK_LM4F120XL_WIFI

#define Board_gpioCallbacks0        EK_LM4F120XL_gpioPortFCallbacks
#define Board_gpioCallbacks1        EK_LM4F120XL_gpioPortFCallbacks

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
