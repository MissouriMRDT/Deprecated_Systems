// roveEnergia.hpp
//
// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// Energia C++ Public Interface Thin Wrappers
//
// mrdt::roveWare

#ifndef ROVECPLUSWIRES_H_
#define ROVECPLUSWIRES_H_

#ifdef __cplusplus
extern "C" {
#endif

//I contend we heavily enforce an explicitly ban on the use of "New" operator or "Task_create" function in roveWare throughout 2016
//That way all Rtos, C_plus, and pure C instantiation stays Compile Time and shares a common init pattern


/*
//ENERGIA::ROVECOMM::CLASS

//public interface for an distrubuted embedded ip network for robotic control
class RoveComm {



//TODO implement C_plus public
////////////////////////////////////C_plus
 //public:
    //RoveComm();
    //~RoveComm();

    //bool begin(char* local_ip_address, int local_port);

    //bool writeIpMsg(rove_comm_ip write_to_ip, char* msg_buffer, int msg_gyte_cnt );
    //rove_comm_ip readIpMsg(rove_comm_ip read_from_ip, char* msg_buffer);



////////////////////////////////////C
 private:

////////////////////////////////////thread api
    //c state binding instances
    rovecomm_socket rove_socket;
    rovecomm_protocol rove_data;

    //config C struct constructor
    int32_t roveComm_InitUdpCFG(rovecomm_socket* rove_socket, uint8_t* local_ip_address, int32_t local_port);

    //use case functions
    int32_t roveComm_GetUdpMSG(rovecomm_socket* rove_socket, rovecomm_protocol* rove_data);

///////////////////////////////////////////////////////static functions
    int32_t roveComm_ParseUdpMSG(rovecomm_protocol* rove_data);

    //developement hooks for empty stub debug:
    int32_t roveComm_CatchRoveCommERRNO(int32_t rove_errno);
    int32_t roveComm_CatchBoardNdkERRNO(int32_t ndk_errno);

};//end class






//ENERGIA::ROVECNTRL::ROVEDYNAMX_AX::CLASS

//public interface for smart servo logic to control the "Dynamixel Ax-Series Smart Servos"
class RoveDynmxAx {



//TODO implement C_plus public
////////////////////////////////////C_plus
 public:
    //RoveDynmxAx();
    //~RoveDynmxAx();

    //begin(uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

    //WHEEL mode
    //bool setWheelMode(bool read_reply_flag);
    //int spinWheel(int speed, bool read_reply_flag);
    //int readWheel();

    //JOINT mode
    //bool setJointMode(bool read_reply_flag);
    //int rotateJoint(int speed, int angle, bool read_reply_flag);
    //int readJoint();



////////////////////////////////////C
 private:

////////////////////////////////////thread api
    //c state binding instance
    rove_dyna_serial dynmxl;

    //config C struct constructor
    int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

    //use case functions
    //WHEEL mode
    int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
    int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
    int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

    //use case functions
    //JOINT mode
    int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
    int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
    int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);


///////////////////////////////////////////////////////static functions
    //General Atomic Telemetry Request
    int32_t roveDynmxAx_ReadRegisterREQ( rove_dyna_serial* dynmxl_id, uint8_t dyna_reg_addr, uint8_t dyna_reg_byte_cnt);

    //Handle Dyna Serial Comms
    int32_t roveDynmxAx_WritePacketMSG(rove_dyna_serial* dynmxl, uint8_t* write_msg_data, int32_t msg_data_byte_count);
    int32_t roveDynmxAx_ReadPacketMSG(rove_dyna_serial* dynmxl);
    int32_t roveDynmxAx_ParseREPLY(rove_dyna_serial* dynmxl, uint8_t* data_buffer);

    //developement hook for empty stub debug:
    int32_t roveDynmxAx_CatchERRNO(rove_dyna_serial* dynmxl_id);

};//end class





*/
#endif // ROVECPLUSWIRES_H_
