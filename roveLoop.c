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

//TODO ti.tirtos.TIRTOS : The GPIO module is deprecated. set ti.tirtos.TIRTOS.useGPIO to true in the .cfg instead (via graphical tool or text editor).
//TODO rtosWires::roveLoop.cpp



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



// ======== USING roveComm ========
//roveComm::int beginUdp(local_ip_addr, port);
//roveComm::int readUdp(remote_ip_addr, "char_message");
//roveComm::int writeUdp(remote_ip_addr, "char_message");
// ========  =======  ========


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



//////////////::BEGIN//////Forever Thread Tiva Rtos Scheduled Task//////////////
void roveLoop(UArg arg0, UArg arg1)
{
    //Private Thread Stack  (Tiva Rtos Task MemSpace) roveThread_Setup()

    //extern roveUart_Handle UART_2;
    //extern roveGpio_Handle PE_1;
    //roveUART_Handle FAKE_UART;
    //roveGPIO_Handle FAKE_GPIO;

    //roveMonitor?
    //roveTest testTimers;
    //roveclock roveTest_SoftTimer_mS;
    //roveclock roveTest_SoftTimer_uS;

    //roveControl roveTest_Ax12 = roveControl::BeginAx(serial_pin, dyna_id, baud_rate);
    //roveControl roveTest_Mx28 = roveControl::BeginMx(serial_pin, dyna_id, baud_rate);
    //roveControl roveTestCplusControllers(1);

    //roveTest testComms;
    //roveComm roveTest_Udp = roveComm::beginUdp(my_ip_addr, port);
    //roveComm roveTest_TcpServer =  roveComm::beginTcp(my_ip_addr, port);
    //roveComm roveTestCplusComms(1);

    while(1)
    {
        //SysClockGet
        printf("roveThreadLoop is awake: ");
    }// end for

}//end task
