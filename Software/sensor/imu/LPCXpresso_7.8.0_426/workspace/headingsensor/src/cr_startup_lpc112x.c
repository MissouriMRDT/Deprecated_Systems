//*****************************************************************************
// LPC112x Microcontroller Startup code for use with LPCXpresso IDE
//
// Version : 150120
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2013-15
// All rights reserved.
//
// Software that is described herein is for illustrative purposes only
// which provides customers with programming information regarding the
// LPC products.  This software is supplied "AS IS" without any warranties of
// any kind, and NXP Semiconductors and its licensor disclaim any and
// all warranties, express or implied, including all implied warranties of
// merchantability, fitness for a particular purpose and non-infringement of
// intellectual property rights.  NXP Semiconductors assumes no responsibility
// or liability for the use of the software, conveys no license or rights under any
// patent, copyright, mask work right, or any other intellectual property rights in
// or to any products. NXP Semiconductors reserves the right to make changes
// in the software without notification. NXP Semiconductors also makes no
// representation or warranty that such application will be suitable for the
// specified use without further testing or modification.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation is hereby granted, under NXP Semiconductors' and its
// licensor's relevant copyrights in the software, without fee, provided that it
// is used in conjunction with NXP Semiconductors microcontrollers.  This
// copyright, permission, and disclaimer notice must appear in all copies of
// this code.
//*****************************************************************************

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
// Declaration of external SystemInit function
extern void SystemInit(void);
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
// Note: The names used for the IRQ Handlers in the LPCXpresso LPC112x startup
// code did not originally match those used by the LPCOpen LPC112x package.
// Now default to using LPCOpen IRQ Handler names. But allow the use of the
// previous names if necessary for legacy code by undefining the below symbol
//*****************************************************************************
#define USE_LPCOPEN_IRQHANDLER_NAMES

#if defined (USE_LPCOPEN_IRQHANDLER_NAMES)
void WAKEUP_IRQHandler  (void) ALIAS(IntDefaultHandler);
void ADCB_IRQHandler (void) ALIAS(IntDefaultHandler);
void SSP1_IRQHandler (void) ALIAS(IntDefaultHandler);
void I2C_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER16_0_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER16_1_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER32_0_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER32_1_IRQHandler (void) ALIAS(IntDefaultHandler);
void SSP0_IRQHandler (void) ALIAS(IntDefaultHandler);
void UART_IRQHandler (void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler (void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler (void) ALIAS(IntDefaultHandler);
void ADCA_IRQHandler (void) ALIAS(IntDefaultHandler);
void WDT_IRQHandler (void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIOINT3_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIOINT2_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIOINT1_IRQHandler (void) ALIAS(IntDefaultHandler);
void PIOINT0_IRQHandler (void) ALIAS(IntDefaultHandler);
#else
void WAKEUP0_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP1_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP2_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP3_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP4_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP5_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP6_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP7_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP8_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP9_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP10_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP11_IRQHandler (void) ALIAS(IntDefaultHandler);
void WAKEUP12_IRQHandler (void) ALIAS(IntDefaultHandler);
void ADC_B_IRQHandler (void) ALIAS(IntDefaultHandler);
void SSP1_IRQHandler (void) ALIAS(IntDefaultHandler);
void I2C_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER_16_0_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER_16_1_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER_32_0_IRQHandler (void) ALIAS(IntDefaultHandler);
void TIMER_32_1_IRQHandler (void) ALIAS(IntDefaultHandler);
void SSP0_IRQHandler (void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler (void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler (void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler (void) ALIAS(IntDefaultHandler);
void ADC_A_IRQHandler (void) ALIAS(IntDefaultHandler);
void WDT_IRQHandler (void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler (void) ALIAS(IntDefaultHandler);
void FMC_IRQHandler (void) ALIAS(IntDefaultHandler);
void EINT3_IRQHandler (void) ALIAS(IntDefaultHandler);
void EINT2_IRQHandler (void) ALIAS(IntDefaultHandler);
void EINT1_IRQHandler (void) ALIAS(IntDefaultHandler);
void EINT0_IRQHandler (void) ALIAS(IntDefaultHandler);
#endif
//*****************************************************************************
//
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);
//*****************************************************************************
//
// External declaration for the pointer to the stack top from the Linker Script
//
//*****************************************************************************
extern void _vStackTop(void);

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM0
    &_vStackTop, // The initial stack pointer
    ResetISR,                               // The reset handler
    NMI_Handler,                            // The NMI handler
    HardFault_Handler,                      // The hard fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,                            // SVCall handler
    0,                                      // Reserved
    0,                                      // Reserved
    PendSV_Handler,                         // The PendSV handler
    SysTick_Handler,                        // The SysTick handler

    // Chip Level - LPC112x
#if defined (USE_LPCOPEN_IRQHANDLER_NAMES)
    WAKEUP_IRQHandler,         // PIO0_0  Wakeup
    WAKEUP_IRQHandler,         // PIO0_1  Wakeup
    WAKEUP_IRQHandler,         // PIO0_2  Wakeup
    WAKEUP_IRQHandler,         // PIO0_3  Wakeup
    WAKEUP_IRQHandler,         // PIO0_4  Wakeup
    WAKEUP_IRQHandler,         // PIO0_5  Wakeup
    WAKEUP_IRQHandler,         // PIO0_6  Wakeup
    WAKEUP_IRQHandler,         // PIO0_7  Wakeup
    WAKEUP_IRQHandler,         // PIO0_8  Wakeup
    WAKEUP_IRQHandler,         // PIO0_9  Wakeup
    WAKEUP_IRQHandler,         // PIO0_10 Wakeup
    WAKEUP_IRQHandler,         // PIO0_11 Wakeup
    WAKEUP_IRQHandler,         // PIO1_0  Wakeup
    ADCB_IRQHandler,           // ADC Sequence B Interrupt
    SSP1_IRQHandler,           // SPI/SSP1 Interrupt
    I2C_IRQHandler,            // I2C0
    TIMER16_0_IRQHandler,      // CT16B0 (16-bit Timer 0)
    TIMER16_1_IRQHandler,      // CT16B1 (16-bit Timer 1)
    TIMER32_0_IRQHandler,      // CT32B0 (32-bit Timer 0)
    TIMER32_1_IRQHandler,      // CT32B1 (32-bit Timer 1)
    SSP0_IRQHandler,           // SPI/SSP0 Interrupt
    UART_IRQHandler,           // UART0
    UART1_IRQHandler,          // UART1
    UART2_IRQHandler,          // UART2
    ADCA_IRQHandler,           // ADC Sequence A (A/D Converter)
    WDT_IRQHandler,            // WDT   (Watchdog Timer)
    BOD_IRQHandler,            // BOD   (Brownout Detect)
    0,                         // Reserved
    PIOINT3_IRQHandler,        // PIO INT3
    PIOINT2_IRQHandler,        // PIO INT2
    PIOINT1_IRQHandler,        // PIO INT1
    PIOINT0_IRQHandler,        // PIO INT0
#else
    WAKEUP0_IRQHandler,        // WAKEUP0
    WAKEUP1_IRQHandler,        // WAKEUP1
    WAKEUP2_IRQHandler,        // WAKEUP2
    WAKEUP3_IRQHandler,        // WAKEUP3
    WAKEUP4_IRQHandler,        // WAKEUP4
    WAKEUP5_IRQHandler,        // WAKEUP5
    WAKEUP6_IRQHandler,        // WAKEUP6
    WAKEUP7_IRQHandler,        // WAKEUP7
    WAKEUP8_IRQHandler,        // WAKEUP8
    WAKEUP9_IRQHandler,        // WAKEUP9
    WAKEUP10_IRQHandler,       // WAKEUP10
    WAKEUP11_IRQHandler,       // WAKEUP11
    WAKEUP12_IRQHandler,       // WAKEUP12
    ADC_B_IRQHandler,          // ADC_B
    SSP1_IRQHandler,           // SSP1
    I2C_IRQHandler,            // I2C
    TIMER_16_0_IRQHandler,     // TIMER_16_0
    TIMER_16_1_IRQHandler,     // TIMER_16_1
    TIMER_32_0_IRQHandler,     // TIMER_32_0
    TIMER_32_1_IRQHandler,     // TIMER_32_1
    SSP0_IRQHandler,           // SSP0
    UART0_IRQHandler,          // UART0
    UART1_IRQHandler,          // UART1
    UART2_IRQHandler,          // UART2
    ADC_A_IRQHandler,          // ADC_A
    WDT_IRQHandler,            // Watchdog timer
    BOD_IRQHandler,            // Brown Out Detect
    FMC_IRQHandler,            // FMC
    EINT3_IRQHandler,          // EINT3
    EINT2_IRQHandler,          // EINT2
    EINT1_IRQHandler,          // EINT1
    EINT0_IRQHandler,          // EINT0
#endif
}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;


//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void
ResetISR(void) {

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
    SystemInit();
#endif

#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main() ;
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SVC_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{ while(1) {}
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{ while(1) {}
}


