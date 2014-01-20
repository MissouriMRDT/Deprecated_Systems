#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"

//#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX             */
 
/* Thread IDs */
//osThreadId thread1_id;
 
/* Forward reference */
//void job1 (void const *argument);
 
/* Thread definitions */
//osThreadDef(job1, osPriorityAboveNormal, 1, 0);


/*----------------------------------------------------------------------------
     Thread 1: 'job1'
 *---------------------------------------------------------------------------*/
/*
void job1 (void const *argument) {    
  while (1) {                         
    UARTprintf("Hello, world!\n");          
    osDelay(500);                      
  }
}

*/

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

// MAIN
int main(void)
{
	
    volatile unsigned long ulLoop;

    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    ROM_FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
                       
    //
    // Initialize the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
    ROM_GPIOPinConfigure(GPIO_PB1_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioInit(1);

		UARTprintf("Hello, world!\n");

    //osKernelInitialize ();

		//thread1_id = osThreadCreate(osThread(job1),NULL);  /* create thread1 */
		
		//osKernelStart ();

}
