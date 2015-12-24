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
#include "roveLoop.h"

#ifdef __cplusplus
extern "C" {
#endif



// ======== USING roveComm ========

//Cplus Public in roveWiresCplus.h
//roveComm::beginUdp(local_ip_addr, port);
//roveComm::readUdp(remote_ip_addr, "char_message");

//C Public as Cplus Private in roveComm.h
//int32_t roveComm_InitUdpCFG(&_udp_socket, (uint8_t*)my_ip_addr, (int32_t)port);
//int32_t roveComm_GetUdpMSG(&_udp_socket, &_udp_data);
// ========  =======  ========



// ======== USING roveControl ========

//Cplus Public in roveWiresCplus.h
//roveControl::BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin);
//roveControl:testWheelMode(int min_speed, int max_speed, int speed_increment, int pause_microseconds);
//roveControl:testJointMode(int min_angle, int max_angle, int angle_increment, int speed, int pause_microseconds);

//C Public as Cplus Private in roveControl.h
//int32_t roveDynmxAx_InitCFG(&_rove_dynamxl, (uint8_t)dyna_id, serial_pin, tri_state_pin);
//int32_t roveDynmxAx_TestWheelMode(rove_dyna_serial* dynmxl, rovecntrl_test_metrics* test);
//int32_t roveDynmxAx_TestJointMode(rove_dyna_serial* dynmxl, rovecntrl_test_metrics* test);
// ========  =======  ========



//Just Shorthand just for now
// ======== roveDev16 ========
typedef enum ROVETHREAD_DEV16
{
   FOREVER = 1
   , WRIST_ID = 1
} ROVETHREAD_DEV16;



//////////////::BEGIN//////Forever Thread Tiva Rtos Scheduled Task//////////////
void roveLoop(UArg arg0, UArg arg1)
{
    //Private Thread Stack  (Tiva Rtos Task MemSpace) roveThread_Setup()

    //extern roveUart_Handle UART_2;
    //extern roveGpio_Handle PE_1;
    //roveUART_Handle FAKE_UART;
    //roveGPIO_Handle FAKE_GPIO;

    RoveComm testCplusComms;
    int test_error =  testCplusComms.beginUdp("192.168.1.2", 11000);
    printf("beginUdp test_error: %d", test_error);

    //negative sign cntrl values allowed
    int min_speed = -1000;
    int max_speed = 1000;
    int speed_increment = 50;
    int pause_microseconds = 1000;

    RoveControl testCplusControllers(WRIST_ID);
    test_error = testCplusControllers.testWheelMode(min_speed, max_speed, speed_increment, pause_microseconds);
    printf("beginUdp test_error: %d", test_error);

    int speed = 100;
    int min_angle = 0;
    int max_angle = 360;
    int angle_increment = 5;

    test_error = testCplusControllers.testJointMode(min_angle, max_angle, angle_increment, speed, pause_microseconds);
    printf("beginUdp test_error: %d", test_error);

    while(FOREVER)
    {
        test_error = testCplusComms.readUdp();
        printf("readUdp test_error: %d", test_error);

    }// end while

}//end task

#ifdef __cplusplus
}
#endif
