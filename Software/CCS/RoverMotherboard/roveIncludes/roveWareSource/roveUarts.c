// roveUarts.c MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveUarts.h"

UART_Handle init_uart(UInt uart_index, UInt baud_rate) {

    UART_Handle uart_handle;
    UART_Params uartParams;

    //init UART
    UART_Params_init(&uartParams);

    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = baud_rate;

    uart_handle = UART_open(uart_index, &uartParams);

    if (uart_handle == NULL) {

        System_abort("Error opening the UART");

    } //endif

    return uart_handle;

} //endfnct init_uart(UInt uart_index, UInt baud_rate)
