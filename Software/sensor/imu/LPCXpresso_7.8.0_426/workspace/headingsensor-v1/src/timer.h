/*
 * timer.h
 *
 *  Created on: Jul 8, 2015
 *      Author: milesm
 */

#ifndef TIMER_H_
#define TIMER_H_

/*////////////////////////////////////////////////////////////////////////////////////////////
 // In header file
 typedef struct {
 void (*delayUs)(uint32_t);
 void (*delayMs)(uint32_t);
 bool (*enabled)(void);
 void (*startMs)(uint32_t);
 void (*stop)(void);
 bool (*expired)(void);
 } timer_t;
 extern const timer_t g_timer32b0m0;
 extern const timer_t g_timer32b0m1;

 // In c/cpp file
 static void Timer32b0m0DelayUs (uint32_t us) { ... }
 static void Timer32b0m0DelayMs (uint32_t ms) { Timer32b0m0DelayUs(ms * 1000); }
 static bool Timer32b0m0Enabled (void) { ... }
 static void Timer32b0m0StartMs (uint32_t ms) { ... }
 static void Timer32b0m0Stop (void) { ... }
 static bool Timer32b0m0Expired (void) { ... }
 const timer_t g_timer32b0m0 = { Timer32b0m0DelayUs,
 Timer32b0m0DelayMs,
 Timer32b0m0Enabled,
 Timer32b0m0StartMs,
 Timer32b0m0Stop,
 Timer32b0m0Expired };

 */ ///////////////////////////////////////////////////////////////////////////////////////////
/*////////////////////////////////////////////////////////////////////////////////////////////
 volatile uint32_t msTicks; // counts 1ms timeTicks

 void SysTick_Handler(void) {
 msTicks++; // increment counter necessary in Delay()
 }

 __inline static void _delay_ms(uint32_t del) {
 uint32_t curTicks;
 curTicks = msTicks;

 while ((msTicks - curTicks) < del) {
 __WFI();
 }
 }

 void setSYSTICK(void) {		// Setup Systick!
 if (SysTick_Config(SystemCoreClock / 100)) { // Setup SysTick Timer for 1 msec interrupts
 while (1)
 ; // Capture error
 }
 if ( !(SysTick->CTRL & (1<SYSTICKCLKDIV = 0x08;
 }
 }

 int main(void) {
 SystemInit();
 setSYSTICK();

 LPC_PMU->PCON |= (1 << 11);
 SCB->SCR &= ~(1 << 2);

 while (1) {
 _delay_ms(100);
 //Do Something
 }
 return 0;
 }
 *//////////////////////////////////////////////////////////////////////////////////////////////////

void _delay_ms(uint16_t ms) {
	uint16_t delay;
	volatile uint32_t i;
	for (delay = ms; delay > 0; delay--) { //1ms loop with -Os optimisation
		for (i = 3500; i > 0; i--) {}
	}
}

#endif // TIMER_H_ //
