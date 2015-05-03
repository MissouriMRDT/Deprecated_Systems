//
// roveHardwareTester.c
//
//  Created on: Mar 3, 2015
//      Author: owen
//
// Task that will test all of the hardware functionality
// Should be disabled most of the time. Only run it when you want to
// do hardware testing.

#include "roveIncludes/roveWareHeaders/roveHardwareTester.h"

#define PWM_TEST_LOOPS 2
#define UART_TEST_LOOPS 3

#define PWM_MIN_MICROS 1000
#define PWM_MAX_MICROS 2000
#define PWM_NEUTRAL_MICROS 1500
#define PWM_STEP_MICROS 100
#define PWM_STEP_DELAY_TIME_MILLIS 10

Void roveHardwareTester(UArg arg0, UArg arg1) {

	int i, j;

	extern const uint8_t FOREVER;

	extern UART_Handle uart0;
	extern UART_Handle uart1;
	extern UART_Handle uart2;
	extern UART_Handle uart3;
	extern UART_Handle uart4;
	extern UART_Handle uart5;
	extern UART_Handle uart6;
	extern UART_Handle uart7;

	extern PWM_Handle motor_0;
	extern PWM_Handle motor_1;
	extern PWM_Handle motor_2;
	extern PWM_Handle motor_3;
	extern PWM_Handle motor_4;
	extern PWM_Handle motor_5;

	System_printf("Starting hardware diagnostic\n");
	System_flush();

	while (FOREVER) {

// ------------------------------ GPIO --------------------- //

		System_printf("Testing GPIO abstraction on All pins\n");
		System_flush();
		for (i = 0; i < 2; i++) {
			System_printf("Testing High\n");
			System_flush();
			for (j = 0; j < 10; j++) //Test all 10 mux pins
				digitalWrite(j, HIGH);
			ms_delay(60);

			System_printf("Testing Low\n");
			System_flush();
			for (j = 0; j < 10; j++)
				digitalWrite(j, LOW);
			ms_delay(60);
		}

// ------------------------------ UART --------------------- //

		System_printf("Testing UART devices\n");
		System_flush();
		UART_write(uart0, "This is uart 0", 15);
		System_printf("Uart 0 tested\n");
		System_flush();
		UART_write(uart1, "This is uart 1", 15);
		System_printf("Uart 1 tested\n");
		System_flush();
		UART_write(uart2, "This is uart 2", 15);
		System_printf("Uart 2 tested\n");
		System_flush();
		UART_write(uart3, "This is uart 3", 15);
		System_printf("Uart 3 tested\n");
		System_flush();
		UART_write(uart4, "This is uart 4", 15);
		System_printf("Uart 4 tested\n");
		System_flush();
		UART_write(uart5, "This is uart 5", 15);
		System_printf("Uart 5 tested\n");
		System_flush();
		UART_write(uart6, "This is uart 6", 15);
		System_printf("Uart 6 tested\n");
		System_flush();
		UART_write(uart7, "This is uart 7", 15);
		System_printf("Uart 7 tested\n");
		System_flush();

// ------------------------------ PWM --------------------- //

		System_printf("Setting motors to neutral\n");
		System_flush();

		pwmWrite(motor_0, PWM_NEUTRAL_MICROS);
		pwmWrite(motor_1, PWM_NEUTRAL_MICROS);
		pwmWrite(motor_2, PWM_NEUTRAL_MICROS);
		pwmWrite(motor_3, PWM_NEUTRAL_MICROS);
		pwmWrite(motor_4, PWM_NEUTRAL_MICROS);
		pwmWrite(motor_5, PWM_NEUTRAL_MICROS);

		ms_delay(6000);

		System_printf("Spinning up\n");
		System_flush();

		// go forward

		for (i = PWM_NEUTRAL_MICROS; i < PWM_MAX_MICROS; i += PWM_STEP_MICROS) {

			pwmWrite(motor_0, i);
			pwmWrite(motor_1, i);
			pwmWrite(motor_2, i);
			pwmWrite(motor_3, i);
			pwmWrite(motor_4, i);
			pwmWrite(motor_5, i);

			ms_delay(100);

		} //end for

		System_printf("Spinning Down\n");
		System_flush();

		for (i = PWM_MAX_MICROS; i > PWM_MIN_MICROS; i -= PWM_STEP_MICROS) {

			pwmWrite(motor_0, i);
			pwmWrite(motor_1, i);
			pwmWrite(motor_2, i);
			pwmWrite(motor_3, i);
			pwmWrite(motor_4, i);
			pwmWrite(motor_5, i);

			ms_delay(500);

		} //end for

		System_flush();

		for (i = PWM_MIN_MICROS; i < PWM_NEUTRAL_MICROS; i += PWM_STEP_MICROS) {

			pwmWrite(motor_0, i);
			pwmWrite(motor_1, i);
			pwmWrite(motor_2, i);
			pwmWrite(motor_3, i);
			pwmWrite(motor_4, i);
			pwmWrite(motor_5, i);

			ms_delay(500);

		} //end for

		System_printf("Finished testing all pins\n");
		System_flush();
	}
	Task_exit();

} //end fnctn Task roveHardwareTester
