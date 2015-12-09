// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// for URC 2016 data_id based protocol definitions
//
// mrdt::rovWare
#ifndef ROVEPROTOCOL_H_
#define ROVEPROTOCOL_H_

#endif // ROVEPROTOCOL_H_













































//wheel mode can be used for wheel-type operation robots since motors of the robot will spin infinitely at angle zero
//Wheel Mode : set to both Angle Limits to zero. The motor spins endlessly

/*TODO
uint8_t roveDynamixel_GetUartMessage(int deviceJack, char* buffer) {

    uint8_t rx_len = 0;
    uint8_t startByte = 0x06;
    uint8_t secondByte = 0x85;

    int bytesRead = 0;
    char receiveBuffer[40];

    // This is used to decide how much pre-data to discard before quitting
    uint8_t garbageCount = 10;
    bool startReceived = false;

    //testing
    //int debug_rx_cnt = 0;

    if (rx_len == 0) {

        while (!startReceived) {
            bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500);
            if (bytesRead == 1) {
               // if (receiveBuffer[0] == startByte) {
               //     startReceived = true;
                } else {
                    garbageCount--;
                    if (garbageCount <= 0)
                        return false;
                } //endif
            } //endif
              //debug_rx_cnt++;
        } //endwhile

//      System_printf("Looped through the rx debug_rx_cnt: %d\n", debug_rx_cnt);
//      System_flush();

        if ((bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500)) == 1) {
            if (receiveBuffer[0] != secondByte) {
                return false;
            } else {
                bytesRead = deviceRead(deviceJack, receiveBuffer, 1, 500);
                if (bytesRead == 1) {
                    rx_len = receiveBuffer[0];
                    if (rx_len == 0) {
                        return false;
                    } //endif
                } else {
                    return false;
                }
            } //endif

        } //endif
        else {
            return false;
        }

//      System_printf("bytesRead: %d\n", bytesRead);
//      System_flush();

    } //end if (rx_len == 0)

    if (rx_len > 0) {
        bytesRead = deviceRead(deviceJack, receiveBuffer, rx_len + 1, 2000);
        //rx_len + 1 for the checksum byte at the end
        if (bytesRead != (rx_len + 1))
            return false;

        uint8_t calcCS = calcCheckSum(receiveBuffer, rx_len);

        if (calcCS != receiveBuffer[rx_len]) {
            // Checksum error
            return false;
        } //end if

        memcpy(buffer, receiveBuffer, rx_len);
        return true;
    } //end if

    return false;
} //end recvSerialStructMessage

uint8_t roveGetCheckSum_ByStructPtr(const void* my_struct, uint8_t struct_byte_cnt) {

    uint8_t checkSum = size;
    uint8_t i;

    for (i = 0; i < size; i++)
        checkSum ^= *((char*) my_struct + i);

    return checkSum;

} //end fnctn*/
//TODO sysctl.h
//*****************************************************************************
//! Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock, which is
//! also the clock rate of the peripheral modules (with the exception of
//! PWM, which has its own clock divider; other peripherals may have different
//! clocking, see the device data sheet for details).
//!
//! \note This cannot return accurate results if SysCtlClockSet() has not
//! been called to configure the clocking of the device, or if the device is
//! directly clocked from a crystal (or a clock source) that is not one of the
//! supported crystal frequencies.  In the latter case, this function should be
//! modified to directly return the correct system clock rate.
//!
//! \note This function can only be called on TM4C123 devices.  For TM4C129
//! devices, the return value from SysCtlClockFreqSet() indicates the system
//! clock frequency.
//!
//! \return The processor clock rate for TM4C123 devices only.
//*****************************************************************************

//TODO Satterfield/Bischoff:  TODO-> Proofread/Edit/Maintain Model Differences: Specs

    //dynamixel servos have different configurable "modes" of operation depending on series
    //the range and unit of CW/CCW Angle Limits dictate how positon and speed are interperted by operation mode
    //position and speed command range and unit scale will vary or have no effect with different operation mode


    //TODO AX12 SOME specs:
        //AX12 has two modes
            //10bit Wheel -> 0-1023 CCW, 1024 - 2047 CW
            //no amperage control??

    //TODO MX12 SOME specs
        //MX12 has three modes
            //12bit Wheel -> 0-2047 CCW, 2048 - 4095 CW
            //Goal_punch_reg and acceleration_reg control provides amperage control??

//TODO Satterfield/Bischof Validate Modes: HERE:
    //http://support.robotis.com/en/techsupport_eng.htm#product/dynamixel/ax_series/dxl_ax_actuator.htm






//END TODO??
//#define AX12_ROTATE_AT_TORQUE             71
//#define AX12_ROTATE_AT_ACCELERATION       73
//#define AX12_WHEELSPEED_OFFSET 1024
//#define CLOCKWISE           1
//#define COUNTERCLOCKWISE    0
//#define ZERO_SPEED          0
//#define DONT_LISTEN_FOR_REPLY 0
//#define LISTEN_FOR_REPLY 1



//////////////////////////////////////////TODO->::EEPROM AREA
/*//////////////////////////////////////////////////////////
#define AX_MODEL_NUMBER_L           0
#define AX_MODEL_NUMBER_H           1
#define AX_VERSION                  2
#define AX_ID                       3
#define AX_BAUD_RATE                4
#define AX_RETURN_DELAY_TIME        5
#define AX_CW_ANGLE_LIMIT_L         6
#define AX_CW_ANGLE_LIMIT_H         7
#define AX_CCW_ANGLE_LIMIT_L        8
#define AX_CCW_ANGLE_LIMIT_H        9
#define AX_SYSTEM_DATA2             10
#define AX_LIMIT_TEMPERATURE        11
#define AX_DOWN_LIMIT_VOLTAGE       12
#define AX_UP_LIMIT_VOLTAGE         13
#define AX_MAX_TORQUE_L             14
#define AX_MAX_TORQUE_H             15
#define AX_RETURN_LEVEL             16
#define AX_ALARM_LED                17
#define AX_ALARM_SHUTDOWN           18
#define AX_OPERATING_MODE           19
#define AX_DOWN_CALIBRATION_L       20
#define AX_DOWN_CALIBRATION_H       21
#define AX_UP_CALIBRATION_L         22
#define AX_UP_CALIBRATION_H         23

// RAM AREA  //////////////////////////////////////////////////////////////
#define AX_TORQUE_ENABLE            24
#define AX_LED                      25
#define AX_CW_COMPLIANCE_MARGIN     26
#define AX_CCW_COMPLIANCE_MARGIN    27
#define AX_CW_COMPLIANCE_SLOPE      28
#define AX_CCW_COMPLIANCE_SLOPE     29
#define AX_GOAL_POSITION_L          30
#define AX_GOAL_POSITION_H          31
#define AX_GOAL_SPEED_L             32
#define AX_GOAL_SPEED_H             33
#define AX_TORQUE_LIMIT_L           34
#define AX_TORQUE_LIMIT_H           35
#define AX_PRESENT_POSITION_L       36
#define AX_PRESENT_POSITION_H       37
#define AX_PRESENT_SPEED_L          38
#define AX_PRESENT_SPEED_H          39
#define AX_PRESENT_LOAD_L           40
#define AX_PRESENT_LOAD_H           41
#define AX_PRESENT_VOLTAGE          42
#define AX_PRESENT_TEMPERATURE      43
#define AX_REGISTERED_INSTRUCTION   44
#define AX_PAUSE_TIME               45
#define AX_MOVING                   46
#define AX_LOCK                     47
#define AX_PUNCH_L                  48
#define AX_PUNCH_H                  49

// Instruction Set ///////////////////////////////////////////////////////////////
#define AX_PING                     1
#define AX_READ_DATA                2
#define AX_WRITE_DATA               3
#define AX_REG_WRITE                4
#define AX_ACTION                   5
#define AX_RESET                    6
#define AX_SYNC_WRITE               131

// Specials ///////////////////////////////////////////////////////////////
#define AX_BYTE_READ_ONE            1
#define AX_BYTE_READ_TWO            2
#define BROADCAST_ID                254
#define AX_START_BYTE               255

#define AX_CCW_AL_L                 255
#define AX_CCW_AL_H                 3
#define LOCK                        1

#define TIME_OUT                    10         // This parameter depends on the speed of transmission
#define TX_DELAY_TIME               400        // This parameter depends on the speed of transmission - but can be changed to a higher speed.

#define Tx_MODE                     1
#define Rx_MODE                     0
//END::TODO */

//TODO sysctl.h
//*****************************************************************************
//! Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock, which is
//! also the clock rate of the peripheral modules (with the exception of
//! PWM, which has its own clock divider; other peripherals may have different
//! clocking, see the device data sheet for details).
//!
//! \note This cannot return accurate results if SysCtlClockSet() has not
//! been called to configure the clocking of the device, or if the device is
//! directly clocked from a crystal (or a clock source) that is not one of the
//! supported crystal frequencies.  In the latter case, this function should be
//! modified to directly return the correct system clock rate.
//!
//! \note This function can only be called on TM4C123 devices.  For TM4C129
//! devices, the return value from SysCtlClockFreqSet() indicates the system
//! clock frequency.
//!
//! \return The processor clock rate for TM4C123 devices only.
//*****************************************************************************

//////////////////////////////////SATTERFIELD/BISCHOFF/MILES TODO-> Rove Dynamixel CONTROL MODES BY MODEL Table Specs

/*JUDAH TODO->::DEPRECATED 2016 Robot Arm Developement
#define ZERO_SPEED 0
#define ENDLESS_ROTATION 0
#define DYNAMIXEL_SPEED_MIN -1022
#define DYNAMIXEL_SPEED_MAX 1022
#define LIN_ACT_FORWARD 0xE1
#define LIN_ACT_REVERSE 0xE0
//command_byte : forward /reverse
typedef struct linear_actuator_struct {

    uint8_t command_byte;
    uint8_t speed;
}__attribute__((packed)) linear_actuator_struct, *linear_actuator_struct_ptr;
//positive is forward, negative is reverse, only 8 bit low_byte is speed
void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed);
*/


//TODO UDP multicast overhead
//remote subscribers[MAX_SUBSCRIBER_CNT];
//subscribe to remote ip addresses
//typedef struct remote {
//
//    struct sockaddr_in remote_addr;
//    socklen_t          remote_addr_length;
//
//} __attribute__((packed)) remote, *remote_ptr;
//bool rovecommAddSubscriber(IPAddress address);
//void rovecommControl(uint16_t* dataID, uint16_t* size, void* data, IPAddress remote_ip, int remote_port);

/////////////////////////////////////////BEGIN Custom Library Distributed IP Embedded Network Handler
//class RoveComm {
/////////////////////////////////////////BEGIN Advanced Member CCS API Hooks
//    private:
        //RoveComm();
        //~RoveComm();
        //RoveComm private functions
//::END CCS API Hooks
/////////////////////////////////////////BEGIN Beginner Member Arduino Library API
       //TODO public:
       // void begin();
       // void read();
       // void write();
       //rove_udp_socket rove_comm;
//};//end class
//void rovePrintf_Protocol(rove_protocol* rove_protocol);

//////////////////////////////////GBENGA TODO-> Rove Dynamixel Software Serial Feedback Aggregation Layer
//dynamixels have  many other registers
//roveDynamixel setDynaConfig aggregate function?
//roveDynamixel getDynaConfig aggregate function?
//More than One "roveDynamixel getTylemetryWeCareAbout request aggregate function?




//TODO
/*
    if (*dataID < 0x65) {
      Serial.print("RoveComm function received with dataID: ");
      Serial.println(*dataID, HEX);
      if (rovecommSubscribers[0] == INADDR_NONE) { //if this is running during rovecommInit();
        rovecommControl(dataID, size, data, remote_ip, remote_port);
      } else {
       rovecommControl(dataID, size, data, remote_ip, remote_port);
        getUdpMsg(dataID, size, data);
      }
    }
    Serial.println();
  }
}

void rovecommControl(uint16_t* data_id, uint16_t* data_byte_count, uint32_t remote_ip_address, int remote_port, rove_udp_socket* rove_udp_socket,) {

  switch (*data_id) {
    case ADD_SUBSCRIBER:
        rovecommAddSubscribers(rove_udp_socket->subscribers[0].remote_ip_addr);
        return;
    default:
        printf("Failed rovecommControl remote_ip_addr: %d \n\n" , rove_udp_socket->subscribers[0].remote_ip_addr);
       return;
  }//endswitch
}//endfnctn rovecommControl

int rovecommAddSubscribers(char* remote_ip_address, rove_udp_socket* rove_udp_socket) {

  int added_subscribers_count = 0;
  while(added_subscribers_count < MAX_SUBSCRIBER_CNT
          && !(rove_udp_socket->subscribers[added_subscribers_count] == INADDR_NONE
                  || rove_udp_socket->subscribers[added_subscribers_count] == remote_ip_address)) {
      added_subscribers_count++;
  }//endwhile

  //handle exceed the subscribers array
  if (added_subscribers_count == MAX_SUBSCRIBER_CNT) {
    printf("Subscriber failed");
    return false;
  }//endif
  rove_udp_socket->subscribers[added_subscribers_count] == remote_ip_address;
  printf("Subscriber added");
  return true;
}//end fnctn rovecommAddSubscriber


////////////////////////////////////////////////////////////////////////Judah Debugging ONLY:

void rovePrintf_Protocol(rove_udp_socket* rove_socket) {

    switch(rove_socket->data_id){

        case DRIVE_RIGHT_MOTORS:
            printf("Rover drive right : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case DRIVE_LEFT_MOTORS:
            printf("Rover drive left : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case WRIST_ROTATE:
            printf("Rover wrist rotate : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case WRIST_VERTICAL:
            printf("Rover wrist vertical : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case ELBOW_ROTATE:
            printf("Rover elbow rotate : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
            break;

        case ELBOW_VERTICAL:
           printf("Rover elbow vertical : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case BASE_ROTATE:
           printf("Rover base rotate : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case E_STOP_ARM:
           printf("Rover e stop arm : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case ACTUATOR_INCREMENT:
           printf("Rover actuator increment : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        case GRIPPER_OPEN:
           printf("Rover gripper open : data_id %d : speed %d\n",rove_socket->data_id, (*((int16_t*)rove_socket->data_buffer)) );
           break;

        default:
            printf("Unknown Command Error\n");
            break;
    }//endswitch
    return;
}//endfnctn rovePrintf_IPMessage

//RoveComm::RoveComm(){


//};//end construction

//RoveComm::~RoveComm(){

//};//end destruction

//RoveComm private functions
int16_t RoveComm::roveComm_Init(rove_udp_socket* rove_socket){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm::roveGet_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm:: roveParse_UdpMsg(rove_protocol* rove_data, rove_udp_socket* rove_socket){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm::begin(){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm:: read(){
    return rovePrintf_Errno( fdError() );
}//end fnctn

int16_t RoveComm:: write(){
    return rovePrintf_Errno( fdError() );
}//end fnctn*/



///////////////////////////////ADDENDUM///////// NOTES :TODO??
//access the global pwm handles
//extern PWM_Handle pwm_1;
//extern PWM_Handle pwm_2;
//extern PWM_Handle pwm_3;
//extern PWM_Handle pwm_4;
//extern PWM_Handle pwm_5;
//extern PWM_Handle pwm_6;*/














/*BEGIN JUDAH DEV////////////////////////Begin Dynamixel Runtime CFG and Telem REQUEST ROUTINES
void roveDynamixel_PingREQ(uint8_t dynamixel_id) {

    char msg_data[]={AX12_PING_REQUEST};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn roveDynamixel_PingREQ

int moving(unsigned char ID){

    char data[]={AX_READ_DATA, AX_MOVING, AX_BYTE_READ_ONE};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int readVoltage(unsigned char ID){

    char data[]={AX_READ_DATA, AX_PRESENT_VOLTAGE, AX_BYTE_READ_ONE};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int readLoad(unsigned char ID){

    char data[]={AX_READ_DATA, AX_PRESENT_LOAD_L, AX_BYTE_READ_TWO};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int readTemperature(unsigned char ID){

    char data[]={AX_READ_DATA, AX_PRESENT_TEMPERATURE, AX_BYTE_READ_ONE};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int RWStatus(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_REGISTERED_INSTRUCTION, AX_BYTE_READ_ONE};
    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

void roveDynamixel_TorqueStatusREQ(uint8_t dynamixel_id) {
    char msg_data[]=

        {AX_WRITE_DATA
        , AX_TORQUE_ENABLE
        WHAT?, (char)Status};
    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

void roveDynamixel_LedStatusREQ(uint8_t dynamixel_id) {
    char data[]={AX_WRITE_DATA, AX_LED, (char)Status};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

//Begin Runtime Set Dynamixel Config

//What does this one do??
void reset(uint8_t dynamixel_id) {

    uint8_t data[]={AX_RESET};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

void action() {

    char data[]={AX_ACTION};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

void roveDynamixel_SetIdCFG(uint8_t old_dynamixel_id, uint8_t new_dynamixel_id) {

    char msg_data[]=
        {AX_WRITE_DATA
        , old_dynamixel_id
        , new_dynamixel_id};

     roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

void roveDynamixel_SetBaudRateCFG(uint8_t old_dynamixel_id, uint8_t new_dynamixel_id) {

    unsigned char Baud_Rate = (2000000/baud) - 1;
    char data[]={AX_WRITE_DATA, AX_BAUD_RATE, Baud_Rate};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setTempLimit(unsigned char ID, unsigned char Temperature){

    char data[]={AX_WRITE_DATA, AX_LIMIT_TEMPERATURE, Temperature};
    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setVoltageLimit(unsigned char ID, unsigned char DVoltage, unsigned char UVoltage){

    char data[]={AX_WRITE_DATA, AX_DOWN_LIMIT_VOLTAGE, DVoltage, UVoltage};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setAngleLimit(unsigned char ID, int CWLimit, int CCWLimit) {

    char CW_H,CW_L,CCW_H,CCW_L;
    CW_H = CWLimit >> 8;
    CW_L = CWLimit;
    CCW_H = CCWLimit >> 8;
    CCW_L = CCWLimit;
    //TODO: Not sure if the first byte should be AX_CCW_CW_LENGTH or AX_VL_LENGTH

    char data[]={AX_WRITE_DATA, AX_CW_ANGLE_LIMIT_L, CW_L, CW_H, AX_CCW_ANGLE_LIMIT_L, CCW_L, CCW_H};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setMaxTorque(unsigned char ID, int MaxTorque) {
    char MaxTorque_H,MaxTorque_L;
    MaxTorque_H = MaxTorque >> 8;
    MaxTorque_L = MaxTorque;
    char data[]={AX_WRITE_DATA, AX_MAX_TORQUE_L, MaxTorque_L, MaxTorque_H};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setSRL(unsigned char ID, DynamixelStatusReturnLevel SRL) {

    char data[]={AX_WRITE_DATA, AX_RETURN_LEVEL, (char)SRL};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setRDT(unsigned char ID, unsigned char RDT) {

    char data[]={AX_WRITE_DATA, AX_RETURN_DELAY_TIME, (RDT/2)};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn


int setLEDAlarm(unsigned char ID, unsigned char LEDAlarm) {

    char data[]={AX_WRITE_DATA, AX_ALARM_LED, LEDAlarm};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setShutdownAlarm(unsigned char ID, unsigned char SALARM) {

    //TODO: Not sure of packet structure with AX_ALARM_LED and AX_WRITE_DATA
    char data[]={AX_WRITE_DATA, AX_ALARM_SHUTDOWN, SALARM};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setCMargin(unsigned char ID, unsigned char CWCMargin, unsigned char CCWCMargin) {

    char data[]={AX_WRITE_DATA, AX_CW_COMPLIANCE_MARGIN, CWCMargin, AX_CCW_COMPLIANCE_MARGIN, CCWCMargin};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setCSlope(unsigned char ID, unsigned char CWCSlope, unsigned char CCWCSlope) {

    char data[]={AX_WRITE_DATA, AX_CW_COMPLIANCE_SLOPE, CWCSlope, CCWCSlope};// AX_CCW_COMPLIANCE_SLOPE

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int setPunch(unsigned char ID, int Punch) {

    char Punch_H,Punch_L;
    Punch_H = Punch >> 8;
    Punch_L = Punch;
    char data[]={AX_WRITE_DATA, AX_PUNCH_L, Punch_L, Punch_H};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

int lockRegister(unsigned char ID) {

    char data[]={AX_WRITE_DATA, AX_LOCK, LOCK};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

void rovePrintf_ByteBuffer(uint8_t* printf_buffer, int32_t bytes_to_printf) {

    int printf_cnt = 0;
    printf("Buffer holds: ");

    while (printf_cnt < bytes_to_printf) {
        printf(" %d", printf_buffer[printf_cnt]);
        printf_cnt++;
    }//end while

    printf("\n\n");
    return;
}//endfnctn*/
