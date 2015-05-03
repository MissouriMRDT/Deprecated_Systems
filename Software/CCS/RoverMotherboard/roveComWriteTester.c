// roveComWriteTester.c

#include "roveIncludes/roveWareHeaders/roveComWriteTester.h"

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

void roveComWriteTester(UArg arg0, UArg arg1)
{
    extern const uint8_t FOREVER;

    test_msg_struct test_message_struct;
	char write_buffer[MAX_COMMAND_SIZE];

	char write_test_msg[] = "ABCD";
	int write_test_msg_size = sizeof(write_test_msg);

	int device_jack = 0;
	int message_size = 0;

	int message_count = 0;
	uint8_t check_sum = NULL;
	int i;

	while(FOREVER)
	{
	    test_message_struct.id = test_message_id;

        //while(test_command_msg.id <= STRUCT_ID_MAX)
        //{

            test_message_struct.message_count = (char)message_count;

            device_jack = getDeviceJack(test_message_struct.id);

            System_printf("\n\nroveArmTester device_jack: %d\n", device_jack);
            System_flush();

            test_message_struct.device_jack = (char)device_jack;

            memcpy(&(test_message_struct.message[0]), write_test_msg, sizeof(write_test_msg));

            message_size = buildSerialStructMessage( (void*)&test_message_struct, write_buffer);

            System_printf("roveArmTester message_size: %d\n", message_size);
            System_flush();

            deviceWrite(device_jack, write_buffer, message_size);

            System_printf("roveComWriteTester just sent this message: \n\n");
            System_flush();

            i = 0;
            while (i < (message_size))
            {
                System_printf("%d, ", write_buffer[i]);
                i++;

            } //end while

            check_sum = calcCheckSum((void*)&test_message_struct, (getStructSize(test_message_struct.id)));

            // 3 for two start bytes and size byte plus size of struct to get final position

            System_printf("\n\nroveComWriteTester check_sum: %d, message_count: %d\n\n", check_sum, message_count);
            System_flush();

            //test_command_msg.id = test_command_msg.id + STRUCT_INCREMENT;

            message_count++;

			ms_delay(TEST_MS_DELAY);

		//}//end while STRUCT_ID_MAX

	}//end while FOREVER

}//end fnctn roveComWriteTester
