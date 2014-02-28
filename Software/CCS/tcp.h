/*
 * tcp.h
 *
 * Keenan Johnson
 */

#ifndef TCP_H_
#define TCP_H_

#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include <driverlib/ssi.h>
#include <driverlib/pin_map.h>

#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F

#define MR    0x0000   // Mode Register
#define GAR   0x0001   // Gateway Address: 0x0001 to 0x0004
#define SUBR  0x0005   // Subnet mask Address: 0x0005 to 0x0008
#define SAR   0x0009   // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR  0x000F   // Source IP Address: 0x000F to 0x0012
#define RMSR  0x001A   // RX Memory Size Register
#define TMSR  0x001B   // TX Memory Size Register
#define IR    0x0015   // Interrupt
#define IMR   0x0016   // Interrupt Mask

#define S0_MR      0x0400      // Socket 0: Mode Register Address
#define S0_CR      0x0401      // Socket 0: Command Register Address
#define S0_IR      0x0402      // Socket 0: Interrupt Register Address
#define S0_SR      0x0403      // Socket 0: Status Register Address
#define S0_PORT    0x0404      // Socket 0: Source Port: 0x0404 to 0x0405
#define SO_TX_FSR  0x0420      // Socket 0: Tx Free Size Register: 0x0420 to 0x0421
#define S0_TX_RD   0x0422      // Socket 0: Tx Read Pointer Register: 0x0422 to 0x0423
#define S0_TX_WR   0x0424      // Socket 0: Tx Write Pointer Register: 0x0424 to 0x0425
#define S0_RX_RSR  0x0426      // Socket 0: Rx Received Size Pointer Register: 0x0425 to 0x0427
#define S0_RX_RD   0x0428      // Socket 0: Rx Read Pointer: 0x0428 to 0x0429

#define TXBUFADDR  0x4000      // W5100 Send Buffer Base Address
#define RXBUFADDR  0x6000      // W5100 Read Buffer Base Address

// S0_MR values
#define MR_CLOSE      0x00    // Unused socket
#define MR_TCP        0x01    // TCP
#define MR_UDP        0x02    // UDP
#define MR_IPRAW      0x03    // IP LAYER RAW SOCK
#define MR_MACRAW     0x04    // MAC LAYER RAW SOCK
#define MR_PPPOE      0x05    // PPPoE
#define MR_ND         0x20    // No Delayed Ack(TCP) flag
#define MR_MULTI      0x80    // support multicating

// S0_CR values
#define CR_OPEN          0x01     // Initialize or open socket
#define CR_LISTEN        0x02     // Wait connection request in tcp mode(Server mode)
#define CR_CONNECT       0x04     // Send connection request in tcp mode(Client mode)
#define CR_DISCON        0x08     // Send closing reqeuset in tcp mode
#define CR_CLOSE         0x10     // Close socket
#define CR_SEND          0x20     // Update Tx memory pointer and send data
#define CR_SEND_MAC      0x21     // Send data with MAC address, so without ARP process
#define CR_SEND_KEEP     0x22     // Send keep alive message
#define CR_RECV          0x40     // Update Rx memory buffer pointer and receive data

// S0_SR values
#define SOCK_CLOSED      0x00     // Closed
#define SOCK_INIT        0x13     // Init state
#define SOCK_LISTEN      0x14     // Listen state
#define SOCK_SYNSENT     0x15     // Connection state
#define SOCK_SYNRECV     0x16     // Connection state
#define SOCK_ESTABLISHED 0x17     // Success to connect
#define SOCK_FIN_WAIT    0x18     // Closing state
#define SOCK_CLOSING     0x1A     // Closing state
#define SOCK_TIME_WAIT   0x1B     // Closing state
#define SOCK_CLOSE_WAIT  0x1C     // Closing state
#define SOCK_LAST_ACK    0x1D     // Closing state
#define SOCK_UDP         0x22     // UDP socket
#define SOCK_IPRAW       0x32     // IP raw mode socket
#define SOCK_MACRAW      0x42     // MAC raw mode socket
#define SOCK_PPPOE       0x5F     // PPPOE socket

#define TX_BUF_MASK      0x07FF   // Tx 2K Buffer Mask:
#define RX_BUF_MASK      0x07FF   // Rx 2K Buffer Mask:

void SPI_Send(uint16_t addr, uint32_t data)
{
  uint32_t dataAux;
  SSIDataPut(SSI0_BASE, WIZNET_WRITE_OPCODE);
  SSIDataPut(SSI0_BASE,  addr >> 8 );
  SSIDataPut(SSI0_BASE,  addr & 0x0FF);
  SSIDataPut(SSI0_BASE, data);
  while(SSIBusy(SSI0_BASE));
  while( SSIDataGetNonBlocking(SSI0_BASE, &dataAux) > 0);
}


uint32_t SPI_Read(uint32_t addr)
{
  uint32_t dataAux;
  SSIDataPut(SSI0_BASE, WIZNET_READ_OPCODE);
  SSIDataPut(SSI0_BASE,  addr >> 8 );
  SSIDataPut(SSI0_BASE,  addr & 0x0FF);
  SSIDataPut(SSI0_BASE, 0x00);
  while(SSIBusy(SSI0_BASE));
  while( SSIDataGetNonBlocking(SSI0_BASE, &dataAux) > 0);
  return dataAux;
}

void init_spi()
{

	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

	/* Need to unlock PF0 */
	GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	GPIOPinConfigure(GPIO_PA4_SSI0RX);
	GPIOPinConfigure(GPIO_PA5_SSI0TX);

	GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 |
									GPIO_PIN_4 | GPIO_PIN_5);

	SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1300000, 8);
	SSIEnable(SSI0_BASE);

	 //
	//Ethernet adapter config
	//

	unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
	unsigned char ip_addr[] = {192,168,1,25};
	unsigned char sub_mask[] = {255,255,255,0};
	unsigned char gtw_addr[] = {192,168,1,100};

	 System_printf("Resetting TCP\n");
	 System_flush();

	//
	// Basic IP configuration
	//
	SPI_Send(MR,0x80);    //Reset

	System_printf("SPI Sent\n");
		System_flush();

	SysCtlDelay( SysCtlClockGet() / 1000 );

	System_printf("Reset Finished\n");
	System_flush();


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


	//
	// Configure Socket 0 as TCP Server
	//
	SPI_Send(S0_MR, MR_TCP);                  //TCP Mode activation
	SPI_Send(S0_PORT, 0x11);                  //Using port 4500 = 0x1194
	SPI_Send(S0_PORT+1, 0x94);
	SPI_Send(IMR,1);                          //Enable Socket 0 Interrupts only
	SPI_Send(S0_CR, CR_CLOSE);
	SPI_Send(S0_CR, CR_OPEN);
	while(SPI_Read(S0_CR));                   //Wait for socket init
	SPI_Send(S0_CR, CR_LISTEN);
	while(SPI_Read(S0_CR));

}

#endif /* TCP_H_ */
