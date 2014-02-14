#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/ssi.h"
#include "inc/hw_ssi.h"

#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F

#define MR   0x0000   // Mode Register
#define GAR  0x0001   // Gateway Address: 0x0001 to 0x0004
#define SUBR 0x0005   // Subnet mask Address: 0x0005 to 0x0008
#define SAR  0x0009   // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR 0x000F   // Source IP Address: 0x000F to 0x0012
#define RMSR 0x001A   // RX Memory Size Register
#define TMSR 0x001B   // TX Memory Size Register

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the USB debug virtual serial port on the evaluation board)
//! will be configured in 115,200 baud, 8-n-1 mode.  All characters received on
//! the UART are transmitted back to the UART.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Send 32 bit command through SPI.
//
//*****************************************************************************
void SPI_Send(uint16_t addr, uint8_t data)
{

SSIDataPut(SSI1_BASE, WIZNET_WRITE_OPCODE);
SSIDataPut(SSI1_BASE, (addr>>8));
SSIDataPut(SSI1_BASE, (addr&0x00FF));
SSIDataPut(SSI1_BASE, data);
while(SSIBusy(SSI1_BASE))
    {
    }
}

void SPI_Read(uint16_t addr, uint32_t *data)
{
SSIDataPut(SSI1_BASE, WIZNET_READ_OPCODE);
SSIDataPut(SSI1_BASE, (addr>>8));
SSIDataPut(SSI1_BASE, (addr & 0x00ff));
SSIDataPut(SSI1_BASE, 0x55);
SSIDataGet(SSI1_BASE, data); //The big change between screens was commenting this statement
}


//*****************************************************************************
//
// This example demonstrates how to send a string of data to the UART.
//
//*****************************************************************************
main(void)
{
			unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
    unsigned char ip_addr[] = {192,168,2,10};
    unsigned char sub_mask[] = {255,255,255,0};
    unsigned char gtw_addr[] = {192,168,2,1};    
	
		   //Testing the read value by writing it on the LCD Screen
    uint32_t *n;
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handl ers, but at the expense of
    // extra stack usage.
    //
    ROM_FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0);
    
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER,
                     100000, 8);
    SSIEnable(SSI1_BASE);
    
    //
    //Ethernet adapter config
    
    SPI_Send(MR,0x80);    //Reset
    SysCtlDelay(500);

    //Gateway Address config
    SPI_Send(GAR+0,gtw_addr[0]);
    SPI_Send(GAR+1,gtw_addr[1]);
    SPI_Send(GAR+2,gtw_addr[2]);
    SPI_Send(GAR+3,gtw_addr[3]);
    
    //MAC Address config
    SPI_Send(SAR+0,mac_addr[0]);
    SPI_Send(SAR+1,mac_addr[1]);
    SPI_Send(SAR+2,mac_addr[2]);
    SPI_Send(SAR+3,mac_addr[3]);
    SPI_Send(SAR+4,mac_addr[4]);
    SPI_Send(SAR+5,mac_addr[5]);
    
    //Sub Mask config
    SPI_Send(SUBR+0,sub_mask[0]);
    SPI_Send(SUBR+1,sub_mask[1]);
    SPI_Send(SUBR+2,sub_mask[2]);
    SPI_Send(SUBR+3,sub_mask[3]);
    
    
    //Ip config
    SPI_Send(SIPR+0,ip_addr[0]);
    SPI_Send(SIPR+1,ip_addr[1]);
    SPI_Send(SIPR+2,ip_addr[2]);
    SPI_Send(SIPR+3,ip_addr[3]);
    
    // Setting the Wiznet W5100 RX and TX Memory Size, we use 2KB for Rx/Tx 4 channels
    SPI_Send(RMSR,0x55);
    SPI_Send(TMSR,0x55);

    
    while(1) //this is the loop in question
    {
    //SPI_Read(SIPR+0,n);
    }

    while(1)
    {
    }
}
