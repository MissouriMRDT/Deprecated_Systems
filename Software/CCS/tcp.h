/*
 * tcp.h
 *
 * Keenan Johnson
 */

#ifndef TCP_H_
#define TCP_H_

#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F

#define MR   0x0000   // Mode Register
#define GAR  0x0001   // Gateway Address: 0x0001 to 0x0004
#define SUBR 0x0005   // Subnet mask Address: 0x0005 to 0x0008
#define SAR  0x0009   // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR 0x000F   // Source IP Address: 0x000F to 0x0012
#define RMSR 0x001A   // RX Memory Size Register
#define TMSR 0x001B   // TX Memory Size Register

void SPI_Send(uint16_t addr, uint8_t data)
{

	SSIDataPut(SSI0_BASE, WIZNET_WRITE_OPCODE);
	SSIDataPut(SSI0_BASE, (addr>>8));
	SSIDataPut(SSI0_BASE, (addr&0x00FF));
	SSIDataPut(SSI0_BASE, data);
	while(SSIBusy(SSI0_BASE))
    {
    }
}

uint32_t SPI_Read(uint16_t addr)
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
    unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
    unsigned char ip_addr[] = {192,168,1,27};
    unsigned char sub_mask[] = {255,255,255,0};
    unsigned char gtw_addr[] = {192,168,1,1};

    SysCtlDelay(200);
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

}

#endif /* TCP_H_ */
