/*
 * uarts.h
 *
 * Keenan Johnson
 */

#ifndef UARTS_H_
#define UARTS_H_

UART_Handle init_uart( UInt uart_index, UInt baud_rate )
{
	UART_Handle uart_handle;

	// For now uart params are declared here
	// TODO: move this into a parameter
	UART_Params uartParams;

	// Start UART7
	UART_Params_init(&uartParams);
	uartParams.readReturnMode = UART_RETURN_FULL;
	uartParams.readMode = UART_MODE_BLOCKING;
	uartParams.readEcho = UART_ECHO_OFF;
	uartParams.baudRate = baud_rate;
	uart_handle = UART_open(uart_index, &uartParams);

	if (uart_handle == NULL) {
		System_abort("Error opening the UART");
	}

	return uart_handle;
}

#endif /* UARTS_H_ */
