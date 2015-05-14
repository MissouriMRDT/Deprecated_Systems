// roveTelemCnrtl.c MST MRDT
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu
//
// this implements a single function BIOS thread
// that acts as the RoverMotherboard.cfg roveTelemCnrtlTask handle
//
// recieves telemetry from Devices in roveCom protocol via uart
//
// sends telemetry to TCPHandler via roveCom protocol using TI.Mailbox.from objecm
//
// BIOS_start in main inits this as the roveTelemCntrlTask Thread
//
// this is a RoverMotherboard.cfg object::roveTelemCntrlTask::
//
// priority 3, vital_flag = t, 2048 persistent private stack

#include "roveIncludes/roveWareHeaders/roveTelemCntrl.h"

Void roveTelemCntrl(UArg arg0, UArg arg1) {

    const uint8_t FOREVER = 1;

    base_station_msg_struct messageInBuffer;

    char messageOutBuffer[MAX_TELEM_SIZE];

    int messageSize;
    int deviceJack;
    int i;

    while (FOREVER) {
/*
        for (i = 0; i < poll_telem_array_idx; i++) {

            int deviceJack = getDeviceJack(poll_telem_device[i]);

            //populate device id into the telem request
            deviceTelemReq.struct_id = telem_req_id;
            deviceTelemReq.telem_device_req_id = poll_telem_device[i];

            System_printf("Telem Entering build Serial\n");
            System_flush();

            messageSize = buildSerialStructMessage((void *) &deviceTelemReq,
                    messageOutBuffer);

            System_printf("Message Size: %d\n", messageSize);
            System_flush();

            deviceWrite(deviceJack, messageOutBuffer, messageSize);

            //looping through RecvSerial until it becomes valid, which tells us we have a full message to post to base
*/
            //debugging only:
            //i = 0;
            //slapping in nulls just for testing
            //while (i < (MAX_COMMAND_SIZE))
            //{
            //    messageInBuffer.value[i] = '\0';
            //    i++;
            //} //end while

            deviceJack = ONBOARD_ROVECOMM;

            //while(!recvSerialStructMessage(deviceJack, &messageInBuffer));

            ((struct gps_telem*)(&messageInBuffer))->struct_id = 140;
            ((struct gps_telem*)(&messageInBuffer))->fix = 1;
            ((struct gps_telem*)(&messageInBuffer))->fix_quality = 2;
            ((struct gps_telem*)(&messageInBuffer))->satellites = 3;
            ((struct gps_telem*)(&messageInBuffer))->latitude_fixed = 12345;
            ((struct gps_telem*)(&messageInBuffer))->longitude_fixed = 56789;
            ((struct gps_telem*)(&messageInBuffer))->altitude = 123.456;
            ((struct gps_telem*)(&messageInBuffer))->speed = 234.567;
            ((struct gps_telem*)(&messageInBuffer))->angle = 345.678;

            printf("\nStruct_id: %d\n", messageInBuffer.id);


            //debugging only:
            //i = 0;

            messageSize = getStructSize(messageInBuffer.id);

            printf("\nTelemCntrl Just Sent %d: messageSize \n", messageSize);
/*
            printf(" struct_id %d ",((struct gps_telem*)(&messageInBuffer))->struct_id);
            printf(" fix %d ",((struct  gps_telem*)(&messageInBuffer))->fix);
            printf(" fix_quality %d ",((struct  gps_telem*)(&messageInBuffer))->fix_quality);
            printf(" satellites %d ",((struct  gps_telem*)(&messageInBuffer))->satellites);
            printf(" latitude %d ",((struct  gps_telem*)(&messageInBuffer))->latitude_fixed);
            printf(" longitude %d ",((struct  gps_telem*)(&messageInBuffer))->longitude_fixed);
            printf(" altitude %f ",((struct  gps_telem*)(&messageInBuffer))->altitude);
            printf(" speed %f ",((struct  gps_telem*)(&messageInBuffer))->speed);
            printf(" angle %f \n",((struct  gps_telem*)(&messageInBuffer))->angle);
*/
            /*
                uint8_t struct_id;
                bool fix;
                uint8_t fix_quality;
                uint8_t satellites;
                int32_t latitude_fixed;
                int32_t longitude_fixed;
                float altitude;
                float speed;
                float angle;
            */

            Mailbox_post(toBaseStationMailbox, &messageInBuffer,BIOS_WAIT_FOREVER);



        //} //endfor

    } //endwhile:   (1)

    //postcondition: execution will not reach this state unless a serious error occurs

    System_printf("Rove Telem Cntrl Task Error: Forced Exit\n");
    System_flush();

    //exit Task

    Task_exit();

} //endfnctn:       roveTelemContoller() Task Thread

/*  Connors Testing Stuffs?... stashing it here

    extern UART_Handle uart2;

    struct device_telem_req deviceTelemReq;

    int poll_telem_array_idx = 2;
    char poll_telem_device[poll_telem_array_idx];

    poll_telem_device[0] = bms_id;
    poll_telem_device[1] = power_board_id;


    int bytes_to_read = 11;
    char buffer[40];
    int bytes_read;
    int device = ONBOARD_ROVECOMM;
    while (1) {
                memset(buffer, '\0', 20);
         bytes_read = deviceRead(device, buffer, bytes_to_read, 2000);
         System_printf("Bytes read: %d\n", bytes_read);
         if (bytes_read > 0)
         System_printf("%s\n", buffer);
         System_flush();

        if (recvSerialStructMessage(device, buffer)) {
            if (((struct rovecom_id_cast*) buffer)->struct_id == 22) {
                uint8_t value =
                        ((struct device_telem_req*) buffer)->telem_device_req_id;

                System_printf("Struct received with value: %x\n", value);
                System_flush();
            }
        }

        Task_sleep(100);
    }
*/
