// roveComReadester.c

#include "roveIncludes/roveWareHeaders/roveComReadTester.h"

/*
 #define MAX_COMMAND_SIZE = 30
 #define TEST_MESSAGE_SIZE 5

typedef struct test_msg_struct{

    char id;
    int message_count;
    int device_jack;
    char message[TEST_MESSAGE_SIZE];
}__attribute__((packed)) test_msg_struct, *test_msg;
*/

void roveComReadTester(UArg arg0, UArg arg1)
{
    extern const uint8_t FOREVER;

    extern UART_Handle uart0;
    extern UART_Handle uart1;
    extern UART_Handle uart2;
    extern UART_Handle uart3;
    extern UART_Handle uart4;
    extern UART_Handle uart5;
    extern UART_Handle uart6;
    extern UART_Handle uart7;

    test_msg_struct test_message_struct;
    char read_buffer[MAX_COMMAND_SIZE];

    uint8_t rx_length = 0;
    uint8_t start_byte = 0x06;
    uint8_t second_byte = 0x85;
    uint8_t garbage_count = 10;
    uint8_t check_sum = NULL;
    bool start_received = false;

    int bytes_read = 0;
    int device_jack = 0;
    int message_count = 0;
    int i;

    while(FOREVER)
    {
        test_message_struct.id = test_message_id;

        System_printf("roveComReadTester id: %d\n", test_message_struct.id);
        System_flush();

        device_jack = getDeviceJack(test_message_struct.id);

        System_printf("\nroveComReadTester device_jack: %d\n", device_jack);
        System_flush();

        if(!TEST_NON_BLOCKING_FLAG)
        {
            System_printf("\nroveComReadTester testing Blocking Uart_Read: \n");
            System_flush();
            if (rx_length == 0)
            {
                while (!start_received)
                {
                    bytes_read = UART_read(uart2, read_buffer, TEST_READ_ONE_BYTE);
                    if (bytes_read == 1)
                    {
                        if (read_buffer[0] == start_byte)
                        {
                            start_received = true;
                        }else{
                            garbage_count--;
                        }//endif
                    }//endif
                }//endwhile
                if ( (bytes_read = UART_read(uart2, read_buffer, TEST_READ_ONE_BYTE)) == 1)
                {
                    if (read_buffer[0] != second_byte)
                    {
                        System_printf("\nroveComReadTester ERROR Byte 2: \n");
                        System_flush();
                    }else{
                        bytes_read = UART_read(uart2, read_buffer, TEST_READ_ONE_BYTE);
                    }//end if
                    rx_length = read_buffer[0];
                }//endif
            }//endif (rx_length == 0)
            if (rx_length > 0)
            {
            //rx_len + 1 for the checksum byte at the end
            bytes_read = UART_read(uart2, read_buffer, rx_length + 1);
            }//endif

        }else{

            System_printf("\nroveComReadTester testing NON Blocking Uart_Read: \n");
            System_flush();
            while ( !recvSerialStructMessage(device_jack, read_buffer) );

        }//end if

        check_sum = calcCheckSum(read_buffer, rx_length);
        System_printf("\n\nroveComWriteTester CHAR* message_count: %d, check_sum: %d\n\n", message_count, check_sum);
        System_flush();

        System_printf("\n\nroveComWriteTester CHAR* contents: \n");
        System_flush();

        i = 0;
        while (i < (bytes_read))
        {
            System_printf("%d, ", read_buffer[i]);
            i++;
        } //end while

        // copy the struct into the buffer starting at byte 3
        memcpy((void*)&test_message_struct, read_buffer + 3, rx_length);

        check_sum = calcCheckSum((void*)&test_message_struct, (getStructSize(test_message_struct.id)));

        System_printf("\n\nroveComWriteTester STRUCT check_sum: %d, message_count: %d\n\n", check_sum, message_count);
        System_flush();

        System_printf("\n\nroveComWriteTester STRUCT id: %d, message_count: %d, device_jack: %d\n\n"
                , test_message_struct.id, test_message_struct.message_count,test_message_struct.device_jack );
        System_flush();

        i = 0;
        while (i < (TEST_MESSAGE_SIZE))
        {
            System_printf("%d, ", test_message_struct.message[i]);
            i++;
         } //end while
        message_count++;

        ms_delay(TEST_MS_DELAY);

    }//end while FOREVER

}//end fnctn roveComWriteTester
