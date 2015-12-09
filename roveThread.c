// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// C interface for a TexInst TIVA RTOS TASK Thread with private stack / signal
// Using Texas Instruments Code Composer Studio RTOS stack instatiates the roveDevice_Thread.c
// This is found in the tivaRtscJS.cfg[TI-RTOS] Javascript Gui/Script tab at the bottom of Projece Explorer Folders
// recieves base station messages using ip bsd style sockets and issues logic commands to hardware
//
// mrdt::rovWare
#include "roveThread.h"

//RoveWare Naming Convention : loosely adapted from crnrPMcore Scripting Convention

//roveSquadName _ <Do Action> <On Noun> (optional ATTRIBUTE)
//ie. roveComm_ParseUdpMSG
//ie. roveDynmxl_SetWheelModeCFG

//Judah dev16 shorthand
//extern roveUart_Handle UART_2;
//extern roveGpio_Handle PE_1;
roveUART_Handle FAKE_UART;
roveGPIO_Handle FAKE_GPIO;


///////////////::BEGIN//////RoveThread Device Tiva Task//////////////
void roveThread_TivaTask(UArg arg0, UArg arg1) {

    printf("Init roveThread Arm Dyna Tester\n\n\n");

///////////////::BEGIN 2016//////RoveComm IP NETWORKING///////////////////

    //open a tiva ndk socket session in this task stack
    fdOpenSession( TaskSelf() );

    //Gbenga Thread Advice TODO:
    //1) I'd like to be able to pass in the local Ip on init from the thread
    //rovecomm_local ip local_device_ip;
    //local_device_ip.sin_addr.s_addr = htonl(LOCAL_DEVICE_IP_ADDRESS);
    //2) I'd like to be able to handle remote subscribers
    //RoveCommDec16.rovecomm_ip_subscribers[remote_ip_addrs++];

    //Judah Dev16 Shorthand
    #define LOCAL_DEVICE_IP_ADDRESS "192.168.1.2"
    #define LOCAL_DEVICE_PORT 11000

    //ip networking socket instance cfg and state struct
    rovecomm_socket RoveCommDec16;

    //Reed Thread Advice TODO:
    //I would like to cleanly hanlde errors that bubble up to the thread level
    //1) Protocol Integration Base Station define Data_Id, Data_Byte_Cnt definitions as int32_t to keep public interface consistent in Energia int
    //2) I can't decide on roveComm vs roveControl error bubble implementations...I would like these to match
    //I'm using data_byte_cnt >= 0 as no error and -1 as error roveComm_GetUdpMSG
    //thread_error = roveComm_UdpInit(&RoveCommDec16, &local_device_ip, LOCAL_DEVICE_PORT);

    //3)roveThread_CatchERRNO is just an empty stub in roveThread.h
    int32_t thread_error = THREAD_ERROR_FREE;
    thread_error = roveComm_InitUdpCFG(&RoveCommDec16, LOCAL_DEVICE_PORT);
    roveThread_CatchERRNO(thread_error);

///////////////::BEGIN //////RoveControl DYNAMIXEL SERIAL//////////////

    //Judah Dev16 shorthand
    #define LEFT_WRIST_ID 0x00
    #define RIGHT_WRIST_ID 0x00
    #define DYNA_WRITE_ONLY = 0

    //dynamixel ax12 smart servo instance cfg and state struct
    rove_dyna_serial LeftWrist;
    thread_error = roveDynmxl_InitCFG(&LeftWrist, LEFT_WRIST_ID, FAKE_UART, FAKE_GPIO);
    roveThread_CatchERRNO(thread_error);

    //dynamixel ax12 smart servo instance cfg and state struct
    rove_dyna_serial RightWrist;
    thread_error = roveDynmxl_InitCFG(&RightWrist, RIGHT_WRIST_ID, FAKE_UART, FAKE_GPIO);
    roveThread_CatchERRNO(thread_error);

    //ip networking protocol version metrics and details config
    rovecomm_protocol RoveProtocolDec16;

    //Judah Dev16 Shorthand
    uint32_t pause_test_microseconds;

///////////////::BEGIN //////MOTOR TEST ROUTINE////////////

    while (FOREVER) {

        //lisetn for udp from base station
        RoveProtocolDec16.data_byte_cnt = roveComm_GetUdpMSG(&RoveCommDec16, &RoveProtocolDec16);
        roveThread_CatchERRNO(RoveProtocolDec16.data_byte_cnt);

        //test dynamixel in wheel mode
        thread_error = roveDynmxl_TestWheelMode(&RightWrist, pause_test_microseconds);
        roveThread_CatchERRNO(thread_error);

        thread_error = roveDynmxl_TestWheelMode(&LeftWrist, pause_test_microseconds);
        roveThread_CatchERRNO(thread_error);
        //end test wheel mode



        //test dynamixel in joint mode
        thread_error = roveDynmxl_TestJointMode(&RightWrist, pause_test_microseconds);
        roveThread_CatchERRNO(thread_error);

        thread_error = roveDynmxl_TestJointMode(&LeftWrist, pause_test_microseconds);
        roveThread_CatchERRNO(thread_error);
        //end test joint mode

//::END MOTOR TEST ROUTINE

//////////////::REPEAT//////MOTOR TEST FOREVER/////////////

    }//endwhile FOREVER

}//endfnctnTask
//::END THREAD



