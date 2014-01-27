

#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"

#define NUM_SSI_DATA 3

// Wiznet W5100 Op Code
#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F
// Wiznet W5100 Register Addresses
#define MR   0x0000   // Mode Register
#define GAR  0x0001   // Gateway Address: 0x0001 to 0x0004
#define SUBR 0x0005   // Subnet mask Address: 0x0005 to 0x0008
#define SAR  0x0009   // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR 0x000F   // Source IP Address: 0x000F to 0x0012
#define RMSR 0x001A   // RX Memory Size Register
#define TMSR 0x001B   // TX Memory Size Register

int
main(void)
{
	  unsigned long ulDataTx[NUM_SSI_DATA];
    unsigned long ulDataRx[NUM_SSI_DATA];
    unsigned long ulindex;
	  
    //
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|
                    SYSCTL_OSC_MAIN);

	  // Enable SPI0
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	  //Configure Pins
	  GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
	
	  SSIClockSourceSet(SSI0_BASE,SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 1000000, 8);

    SSIEnable(SSI0_BASE);
		
		
		//clear out junk
		while(SSIDataGetNonBlocking(SSI1_BASE, &ulDataRx[0]));
    //
    // Initialize the data to send.
    //
    ulDataTx[0] = 's';
    ulDataTx[1] = 'p';
    ulDataTx[2] = 'i';
	
    //
    // Loop Forever
    //
    while(1)
    {

    }
}
