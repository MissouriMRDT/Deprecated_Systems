// TODO roveEnergiaWrappers.cpp
//begin class RoveComm, RoveDnmxAx private fnctn interface

// wtf C++ support name mangling in CCS
/*#include "roveCplusWires.hpp"

//c++ thread public
RoveComm::begin();
*/

#include "roveCplusWires.h"

/*
RoveComm::writeIpMsg();
RoveComm::readIpMsg();


//c++ thread public
RoveDnmxAx::begin();

RoveDnmxAx::setWheelMode();

RoveDnmxAx::spinWheel();
RoveDnmxAx::readWheel()'

RoveDnmxAx::setJointMode();

RoveDnmxAx::rotateJoint();
RoveDnmxAx::readJoint()'


//ifdef c_plus
//compiler macro to wire c++ class up to the c thread public interface

///////////////////RoveComm
//using typedef struct rove_dyna_serial

//c thread api
#define roveComm_InitUdpCFG         RoveComm::roveComm_InitUdpCFG
#define roveComm_GetUdpMSG          RoveComm::roveComm_GetUdpMSG

//c static lib
#define roveComm_ParseUdpMSG        RoveComm::roveComm_ParseUdpMSG
#define roveComm_CatchRoveERRNO     RoveComm::roveComm_ParseUdpMSG
#define roveComm_CatchNdkERRNO      RoveComm::roveComm_ParseUdpMSG



//////////////////RoveCntrl::RoveDynmxAx
//using typedef struct rove_dyna_serial

//c thread api
#define roveDynmxAx_InitCFG         RoveDynmxAx::roveDynmxAx_InitCFG

#define roveDynmxAx_SetWheelModeCFG RoveDynmxAx::roveDynmxAx_SetWheelModeCFG
#define roveAxDynmxAx_SpinWheelCMD  RoveDynmxAx::roveAxDynmxAx_SpinWheelCMD
#define roveAxDynmxAx_ReadWheelREQ  RoveDynmxAx::roveAxDynmxAx_ReadWheelREQ

#define roveDynmxAx_SetJointModeCFG RoveDynmxAx::roveDynmxAx_SetJointModeCFG
#define roveDynmxAx_RotateJointCMD  RoveDynmxAx::roveDynmxAx_RotateJointCMD
#define roveDynmxAx_ReadJointREQ    RoveDynmxAx::roveDynmxAx_ReadJointREQ

//c static lib
#define roveDynmxAx_ReadRegisterREQ RoveDynmxAx::roveDynmxAx_ReadRegisterREQ

#define roveDynmxAx_WritePacketMSG  RoveDynmxAx::roveDynmxAx_WritePacketMSG
#define roveDynmxAx_ReadPacketMSG   RoveDynmxAx::roveDynmxAx_ReadPacketMSG
#define roveDynmxAx_ParseREPLY      RoveDynmxAx::roveDynmxAx_ParseREPLY

#define roveDynmxAx_CatchERRNO      RoveDynmxAx::roveDynmxAx_CatchERRNO



//end class
//endifdef c_plus
*/
