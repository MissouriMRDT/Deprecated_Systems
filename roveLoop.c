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


// ======== roveComm Future Developement:
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


/* ========  roveComm  ========
//
// Cplus object wrappers
class roveComm
{
    public:
    //private:
        //pure C public API roveComm.h
        rovecomm_socket _udp_socket;
        rovecomm_protocol _udp_data;

        int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);
        int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);

    //public:
        //Cplus extension API for Tiva Threads
        roveComm(int newId);
        ~roveComm();
        //roveComm::beginUdp(my_ip_addr, port);
        //roveComm::beginTcp(my_ip_addr, port);;
};// end class

//Tell the compiler to wire the C++ Tiva interface to pure C implementations in roveComm.h
extern "C"
{
int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);
int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);
}// end extern



// ========  roveControl  ========
//
// Cplus object wrappers
class roveControl
{
    public:
    //private:
        rove_dyna_serial rove_dynamxl;

        //config constructor
        int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

        //WHEEL Mode
        int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
        int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
        int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

         //JOINT Mode
        int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
        int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
        int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);
    //public:
        roveControl(int newId);
        ~roveControl();
        //https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Constructor
        //BeginAx(serial_pin, dyna_id, baud_rate);
        //BeginMx(serial_pin, dyna_id, baud_ra);
};// end class

//Tell the compiler to wire the C++ Tiva interface to pure C implementations in roveControl.h
extern "C"
{
//config constructor
int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

//WHEEL Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

//JOINT Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);
}// end extern
//
// ========  =======  ========*/

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
