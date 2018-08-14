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

    char messageBuffer[MAX_TELEM_SIZE];

    int deviceJack;
<<<<<<< HEAD

    deviceJack = GPS_ON_MOB;

    while (FOREVER) {

        while(!recvSerialStructMessage(deviceJack, messageBuffer));

        Mailbox_post(toBaseStationMailbox, messageBuffer, BIOS_WAIT_FOREVER);
=======
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

            while(!recvSerialStructMessage(deviceJack, &messageInBuffer));

            //uint8_t struct_id;
            //bool fix;
            //uint8_t fix_quality;
            //uint8_t satellites;
            //int32_t latitude_fixed;
            //int32_t longitude_fixed;
            //float altitude;
            //float speed;
            //float angle;
            ((struct gps_telem*)(&messageInBuffer))->struct_id = 140;
            ((struct gps_telem*)(&messageInBuffer))->fix = 1;
            ((struct gps_telem*)(&messageInBuffer))->fix_quality = 2;
            ((struct gps_telem*)(&messageInBuffer))->satellites = 3;
            ((struct gps_telem*)(&messageInBuffer))->latitude_fixed = 12345;
            ((struct gps_telem*)(&messageInBuffer))->longitude_fixed = 56789;
            ((struct gps_telem*)(&messageInBuffer))->altitude = 123.456;
            ((struct gps_telem*)(&messageInBuffer))->speed = 234.567;
            ((struct gps_telem*)(&messageInBuffer))->angle = 345.678;
/*
            printf("\nStruct_id: %d\n", messageInBuffer.id);


            //debugging only:
            //i = 0;
*/
            messageSize = getStructSize(messageInBuffer.id);
/*
            printf("\nTelemCntrl Just Sent %d: messageSize \n", messageSize);

            printf(" struct_id %d ",((struct gps_telem*)(&messageInBuffer))->struct_id);
            printf(" fix %d ",((struct gps_telem*)(&messageInBuffer))->fix);
            printf(" fix_quality %d ",((struct gps_telem*)(&messageInBuffer))->fix_quality);
            printf(" satellites %d ",((struct gps_telem*)(&messageInBuffer))->satellites);
            printf(" latitude %d ",((struct gps_telem*)(&messageInBuffer))->latitude_fixed);
            printf(" longitude %d ",((struct gps_telem*)(&messageInBuffer))->longitude_fixed);
            printf(" altitude %d ",((struct gps_telem*)(&messageInBuffer))->altitude);
            printf(" speed %d ",((struct gps_telem*)(&messageInBuffer))->speed);
            printf(" angle %d \n",((struct gps_telem*)(&messageInBuffer))->angle);
*/
            Mailbox_post(toBaseStationMailbox, &messageInBuffer,BIOS_WAIT_FOREVER);

        //} //endfor
>>>>>>> origin/tester/gpsTelem

    } //endwhile

    //postcondition: execution will not reach this state unless a serious error occurs

    printf("Rove Telem Cntrl Task Error: Forced Exit\n");

    //exit Task

    Task_exit();

} //endfnctn:       roveTelemContoller() Task Thread
