// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// C interface for a TexInst TIVA RTOS TASK Thread with private stack / signal
// Using Texas Instruments Code Composer Studio RTOS stack instatiates the roveDevice_Thread.c
// This is found in the tivaRtscJS.cfg[TI-RTOS] Javascript Gui/Script tab at the bottom of Projece Explorer Folders
// recieves base station messages using ip bsd style sockets and issues logic commands to hardware
//
// mrdt::rovWare
//Cplus

#include "roveThread.h"

// TODO Judah Factor Out Dev Shorthand
//extern roveUart_Handle UART_2;
//extern roveGpio_Handle PE_1;
//roveUART_Handle FAKE_UART;
//roveGPIO_Handle FAKE_GPIO;




// ======== roveDev16 ========
typedef enum ROVETHREAD_DEV16
{
   LEFT_WRIST_ID = 0x00
   , RIGHT_WRIST_ID = 0x00
   , WRITE_ONLY = 0
   , FAKE_UART = 0
   , FAKE_GPIO = 0
   , FOREVER = 1
} ROVETHREAD_DEV16;
// ========  =======  ========


// ======== USING roveControl ========
//roveControl::int DynmxlBeginAx(serial_pin, dyna_id, baud_rate);
//roveControl::int DynmxlBeginMx(serial_pin, dyna_id, baud_rate);

//WHEEL Mode
//roveControl::int setWheelMode();
//roveControl::int spinWheel(int wheel_speed);
//roveControl::int readWheel();

//WHEEL Mode
//roveControl::int setJointMode();
//roveControl::int rotateJoint(int joint_position, int wheel_speed);
//roveControl::int readJoint();
// ========  =======  ========
// ======== PLANNED roveControl Future Developement:
// ========  =======  ========


// ======== USING roveComm ========
//roveComm::int beginUdp(local_ip_addr, port);
//roveComm::int readUdp(remote_ip_addr, "char_message");
//roveComm::int writeUdp(remote_ip_addr, "char_message");
// ========  =======  ========


// ======== PLANNED roveComm Future Developement:
//roveComm::beginTcp(local_ip_addr, port);
//roveComm::readTcp(remote_ip_addr, "char_message");
//roveComm::writeTcp(remote_ip_addr, "char_message");
//
//roveComm::beginHttp();
//roveComm::getHttp(remote_url, "json_message");
//roveComm::postHttp(remote_url, "json_message");
//
//roveComm::beginMqqt(broker);
//roveComm::publishMqqt("message");
//roveComm::subscribeMqqt("message");
// ========  =======  ========

///////////////::BEGIN//////RoveThread Device Tiva Task//////////////
void roveThread(UArg arg0, UArg arg1)
{

    //roveRtosMonitor?
    //roveTest testTimers;
    //roveclock roveTest_SoftTimer_mS;
    //roveclock roveTest_SoftTimer_uS;

    //roveTest testControllers;
    //roveControl roveTest_Ax12 = roveControl::BeginAx(serial_pin, dyna_id, baud_rate);
    //roveControl roveTest_Mx28 = roveControl::BeginMx(serial_pin, dyna_id, baud_rate);
    roveControl roveTestCplusController(1);

    //roveTest testComms;
    //roveComm roveTest_Udp = roveComm::beginUdp(my_ip_addr, port);
    //roveComm roveTest_TcpServer =  roveComm::beginTcp(my_ip_addr, port);
    roveComm roveTestCplusComm(1);

    int roveTestClock = cl2.getId();

    for(;;)
    {
        //SysClockGet
        printf("roveThread_TivaTask is awake: ");
    }// end for

}//end task




// ======== clockPrd ========
// Wrapper function for
// PRD objects calling
// Clock::tick()
// ========  =======  ========
void clockPeriodic(UArg arg)
{
    Clock *clock = (Clock *)arg;

    clock->tick();
    return;
} //end task



// ======== clockTask ========
// Wrapper function for
// TSK objects
// calling Clock::tick()
void clockTask(UArg arg)
{
    Clock *clock = (Clock *)arg;
    int count = 0;

    if (clock->getId() == 3) {
        for(;;) {             // task id = 3
            Semaphore_pend(sem0, BIOS_WAIT_FOREVER);
            clock->tick();
            if(count == 50) {
                Task_sleep(25);
                count = 0;
            }
            count++;
            printf("wtf");
            //printf("clock->getId : %d : Count: %d ", clock->getId(), count);
            Semaphore_post(sem1);
        }//end for
    }//end if
    else {
        for(;;) {             // task id = 4
            Semaphore_pend(sem1, BIOS_WAIT_FOREVER);
            if(count == 50) {
                Task_sleep(25);
                count = 0;
            }
            clock->tick();
            count++;
            printf("wtf");
            //printf("clock->getId : %d : Count: %d ", clock->getId(), count);
            Semaphore_post(sem0);
        }//end for
    }//end if

};//end task















/*
roveUART_Handle FAKE_UART;
roveGPIO_Handle FAKE_GPIO;

////////////////////TEST ROUTINE METRICS CFG:

   //negative speeds allowed in wheel mode : rovecntrol allows -1024 to 1024
   //angle has no affect in wheel mode by definition
   , MAX_TEST_AX_WHEEL_SPEED = 256
   , MIN_TEST_AX_WHEEL_SPEED = -256
   , INCRMT_AX_TEST_WHEEL_SPEED = 8

   //negative speeds not allowed in joint mode 0 to 1024
   //: rovecntrol allows goto angles 0 to 300  (Ax 12 is dead between 300 and 360)
   , MIN_TEST_AX_JOINT_SPEED = 0
   , MAX_TEST_AX_JOINT_SPEED = 256
   , INCRMT_TEST_AX_JOINT_SPEED = 8

   , MIN_TEST_AX_JOINT_ANGLE = 45
   , MAX_TEST_AX_JOINT_ANGLE = 270
   , INCRMT_TEST_AX_JOINT_ANGLE = 5

   , PAUSE_TEST_AX_uS = 500
} ROVETHREAD_DEV;

//TODO Reed Error Sys Abort Logging Advice?
//namespace roveDeviceThread {
static void roveThread_CatchERRNO(int32_t thread_error);

typedef enum rove_thread_error {

    THREAD_ERROR_FREE = 0
    , THREAD_UNKNOWN_ERROR = 1
} rove_thread_error;
//};//end namespace


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

            //3) Debug Flag for messages destined for ANY IPv4 unspecified address #define INADDR_ANY 0x00000000  ??
            //const uint8_t device_address[ sizeof(device_address) ] = "\0"; ??
            //const uint8_t device_address[] = "192.168.1.2";
            //const int32_t rovecomm_port = 11000;

            //TODO : messages destined for ANY IPv4 unspecified address #define INADDR_ANY 0x00000000
            //const uint8_t device_address[ sizeof(device_address) ] = "\0"; ??

    //char and int ~ arduino public interface
    uint8_t device_address[] = "192.168.1.2";
    int32_t rovecomm_port = 11000;

    //ip networking socket instance cfg and state struct
    rovecomm_socket RoveCommDec16;

    //ip networking protocol version metrics and details config
    //rovecomm_protocol RoveProtocolDec16;

            //Reed Thread Advice TODO:
            //I would like to cleanly handle errors that bubble up to the thread level without a million printf switch statements
            //1) Protocol Integration Base Station define Data_Id, Data_Byte_Cnt definitions as int32_t to keep public interface consistent in Energia int
            //2) I can't decide on roveComm vs roveControl error bubble implementations...I would like these to match
            //3)roveThread_CatchERRNO is just an empty stub in roveThread.h


    roveThread_CatchERRNO(

            roveComm_InitUdpCFG(

                    &RoveCommDec16

                    , device_address
                    , rovecomm_port) );


///////////////::BEGIN //////RoveControl DYNAMIXEL SERIAL//////////////

    //dynamixel ax12 smart servo instance cfg and state struct
    rove_dyna_serial LeftWrist;
    roveThread_CatchERRNO(

            roveDynmxAx_InitCFG(

                    &LeftWrist

                    , LEFT_AX_WRIST_ID
                    , FAKE_UART
                    , FAKE_GPIO) );

    //dynamixel ax12 smart servo instance cfg and state struct
    rove_dyna_serial RightWrist;
    roveThread_CatchERRNO(

            roveDynmxAx_InitCFG(

                    &RightWrist

                    , RIGHT_AX_WRIST_ID
                    , FAKE_UART
                    , FAKE_GPIO) );

///////////////::BEGIN //////MOTOR TEST ROUTINE////////////

    rovecntrl_test_metrics test_wrist_routine;

    // 1 millisec
    test_wrist_routine.pause_microseconds = PAUSE_TEST_AX_uS;

    while (FOREVER) {

//TODO Reed advice?? Debug macro to toggle roveComm_GetUdpMSG
        //lisetn for udp from base station
//        roveThread_CatchERRNO(RoveProtocolDec16.data_byte_cnt =

//                roveComm_GetUdpMSG(

//                        &RoveCommDec16
//                        , &RoveProtocolDec16) );

        test_wrist_routine.min_speed = MIN_TEST_AX_WHEEL_SPEED;
        test_wrist_routine.max_speed = MAX_TEST_AX_WHEEL_SPEED;
        test_wrist_routine.speed_increment = INCRMT_AX_TEST_WHEEL_SPEED;

        //test dynamixel wrist routine for wheel mode
        roveThread_CatchERRNO(

                roveDynmxAx_TestWheelMode(

                        &RightWrist

                        , &test_wrist_routine) );

        roveThread_CatchERRNO(

                roveDynmxAx_TestWheelMode(

                        &LeftWrist

                        , &test_wrist_routine) );
        //end test wheel mode

        test_wrist_routine.min_speed = MIN_TEST_AX_JOINT_SPEED;
        test_wrist_routine.max_speed = MAX_TEST_AX_JOINT_SPEED;
        test_wrist_routine.speed_increment = INCRMT_TEST_AX_JOINT_SPEED;

        //Todo name LOL maybe we should tuck this down inside rotate as static
        test_wrist_routine.min_angle = MAX_TEST_AX_JOINT_ANGLE;
        test_wrist_routine.max_angle = MAX_TEST_AX_JOINT_ANGLE;
        test_wrist_routine.angle_increment = INCRMT_TEST_AX_JOINT_ANGLE;

        //test dynamixel wrist routine for joint mode
        roveThread_CatchERRNO(

                roveDynmxAx_TestJointMode(

                         &RightWrist

                         , &test_wrist_routine) );

        roveThread_CatchERRNO(

                roveDynmxAx_TestJointMode(

                         &LeftWrist

                         , &test_wrist_routine) );
        //end test joint mode

//::END MOTOR TEST ROUTINE

//////////////::REPEAT//////MOTOR TEST FOREVER/////////////

    }//endwhile FOREVER

}//endfnctnTask
//::END THREAD



//Reed Advice?
static void roveThread_CatchERRNO(int32_t thread_error){
    switch(thread_error) {
        case -1:
            printf("Unknown Thread Error");
        default:
        printf("Error Free");
    }//endswitch
};//end fnctn

*/
//Cplus
