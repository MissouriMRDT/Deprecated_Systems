/*
 * tcp.c
 *
 *  Keenan Johnson
 */

#include "tcp.h"

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
	// Route clock to SPI peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

	// Configure pin purposes
	GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	GPIOPinConfigure(GPIO_PA4_SSI0RX);
	GPIOPinConfigure(GPIO_PA5_SSI0TX);

	GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 |
									GPIO_PIN_4 | GPIO_PIN_5);

	// Set up SPI clock
	SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1300000, 8);

	// Enable SPI 0
	SSIEnable(SSI0_BASE);
}

void set_up_tcp()
{
	//
	//Ethernet adapter config
	//

	unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
	unsigned char ip_addr[] = {192,168,1,25};
	unsigned char sub_mask[] = {255,255,255,0};
	unsigned char gtw_addr[] = {192,168,1,100};

	//
	// Basic IP configuration
	//
	SPI_Send(MR,0x80);    //Reset

	SysCtlDelay( SysCtlClockGet() / 1000 );

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
	// Configure Socket 0 as TCP Client
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

