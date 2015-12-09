// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
// speed used in BOTH wheel AND joint mode AX12:(WHEEL GoalSpeed :0~2047/0X7FF unit:0.1%):(JOINT GoalSpeed: 0~1023/0X3FF unit: 0.111rpm)
//
// angle ONLY used in joint mode AX12:(JOINT GoalPosition:0~1023/0x3FF) at 0.29 degree
//
// mrdt::rovWare
#include "roveControl.h"

//Private

//BEGIN JUDAH TODO factor MRDT shorthand
#define INTERFACE_PROTOCOL_SPEEDS 1024
typedef enum RoveWristDev16ShortHand {
    DEV16_NO_INSTRUCTION =      0x00
    , DEV16_TEST_INSTRUCTION =  0x01
    , DEV16_TEST_ERROR =        0x02
} RoveWristDev16ShortHand;
typedef enum RoveDynaAxSerialMsgCfg {
    AX_PACKET =                 1
    , AX_NO_PACKET =            0
    , AX_MSG_MAX_BYTES =        20
    , AX_READ_REPLY =           1
    , AX_MAX_READ_ATTMPT_CNT =  10
    , AX_ERROR_FREE =           1
    , AX_ERROR =                -1
} RoveDynaAxSerialMsgCfg;
typedef enum RoveDynaAxRegMsgHeaderCfg {
    PACKET_AX_START_BYTE  =   255
    , TX_DELAY_AX_MICRO_SEC = 100
    , WRITE_AX_CMD =            1
    , READ_AX_REQ =             2
    , READ_ONE_BYTE_AX_REQ =    1
    , READ_TWO_BYTES_AX_REQ =   2
} RoveDynaAxRegMsgHeaderCfg;
typedef enum RoveDynaAxRegCfg {
    JOINT_MODE_AX_CFG =         8
    , WHEEL_MODE_AX_CFG =       8
    , TORQUE_MODE_AX_CFG =      24
    , TORQUE_LIMIT_AX_CFG =     34
} RoveDynaAxRegCfg;
typedef enum RoveDynaAxRegCmd {

    GO_ANGLE_AX_REG =           30
    , GO_SPEED_AX_REG =         32
} RoveDynaAxRegCmd;
typedef enum RoveDynaAxRegTelemReq {
    READ_ANGLE_AX_REQ =         36
    , READ_SPEED_AX_REQ =       38
    , READ_LOAD_AX_REQ =        40
    , READ_VOLTAGE_AX_REQ =     42
    , READ_TEMPERATURE_AX_REQ = 43
    , READ_CURRENT_AX_REQ =     68
} RoveDynaAxRegTelemReq;
//END factor TODO


///////////////::BEGIN//////RoveDyna Private Functions//////////////

//General Atomic Telemetry Request
int32_t roveDynmxl_ReadRegisterREQ( rove_dyna_serial* dynmxl_id, uint8_t dyna_reg_addr, uint8_t dyna_reg_byte_cnt);

//developement hook for empty stub debug:
int32_t roveDynmxl_CatchERRNO(rove_dyna_serial* dynmxl_id);

//Handle Dyna Serial Comms
int32_t roveDynmxl_WritePacketMSG(rove_dyna_serial* dynmxl, uint8_t* write_msg_data, int32_t msg_data_byte_count);
int32_t roveDynmxl_ReadPacketMSG(rove_dyna_serial* dynmxl);
int32_t roveDynmxl_ParseREPLY(rove_dyna_serial* dynmxl, uint8_t* data_buffer);



///////////////::BEGIN//////RoveDyna Implementation//////////////

//construct a motor
int32_t roveDynmxl_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle uart_port, roveGPIO_Handle tri_state_pin){

    dynmxl->dynmxl_id = dyna_id;
    dynmxl->tri_state_buffer = tri_state_pin;
    dynmxl->uart = uart_port;

    dynmxl->read_reply_flag = AX_NO_PACKET;
    dynmxl->reply_id = AX_NO_PACKET;
    dynmxl->reply = AX_NO_PACKET;

    return dynmxl->err_no = AX_ERROR_FREE;
};//end fnctn



//Wheel Mode: set to both Angle Limits to zero. The motor spins endlessly
int32_t roveDynmxl_SetWheelModeCFG(rove_dyna_serial* dynmxl){

    //wheel Mode both are 0
    uint8_t cw_angle_limit_low_byte = 0;
    uint8_t cw_angle_limit_high_byte = 0;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]={

        //immediate no delay timing
        WRITE_AX_CMD

        , WHEEL_MODE_AX_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->err_no =

        roveDynmxl_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

    //Immediate return zero was read suceess
    return roveDynmxl_CatchERRNO(dynmxl);
}//end fnctn



//10bit Wheel -> 0-1023 CCW, 1024 - 2047 CW
int32_t roveDynmxl_SpinWheelCMD(rove_dyna_serial* dynmxl , int16_t wheel_speed){

    //handle negative speed scale to absolute value
    wheel_speed =+ INTERFACE_PROTOCOL_SPEEDS;

    //scale direction by shift operations
    if(wheel_speed > INTERFACE_PROTOCOL_SPEEDS) {

        //clockwise direction is the 10th bit
        wheel_speed += (1 >> 10);
    }//end if

    uint8_t speed_low_byte = wheel_speed;
    uint8_t speed_high_byte = wheel_speed >> 8;

    uint8_t write_msg_data[]={

        //imediate command (no delay timing)
        WRITE_AX_CMD

        //command servo to go go to goal speed
        , GO_SPEED_AX_REG
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->err_no =

        roveDynmxl_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

    return roveDynmxl_CatchERRNO(dynmxl);
}//end fnctn



int32_t roveDynmxl_ReadWheelREQ(rove_dyna_serial* dynmxl){
    //TODO GBENGA:
    //return_roveDynmxl_ReadregistersREQ(dynmxl_id->dynmxl_id, AX12_SPEED_REGISTER, TWO_BYTES);
    return AX_ERROR;
}//end fnctn



//Joint Mode : set to Angle Limits anything other than zero
int32_t roveDynmxl_SetJointModeCFG(rove_dyna_serial* dynmxl){

    //TOD how to ctually set set speed zero? homing function function goal rotation to zero?
    roveDynmxl_SpinWheelCMD(dynmxl, 0);

    //SetEndless goal rotation...wheel mode is from TODO 0 to 4095 for the MX SERIES?
    //Multi Turn mode on the MX?
    uint8_t cw_angle_limit_low_byte = 255;
    uint8_t cw_angle_limit_high_byte = 3;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]={

         //immediate no delay timing
        WRITE_AX_CMD

        //switch mode by setting ccw angle max limit
        , JOINT_MODE_AX_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->err_no =

        roveDynmxl_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

    //no errors -> ::roveDynmxl_WritePacketMSG set dynmxl_id->error_flag
    if(dynmxl->err_no){

        return roveDynmxl_CatchERRNO(dynmxl);
    }//end if

    return dynmxl->err_no;
}//end fnctn



int32_t roveDynmxl_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_angle , uint16_t joint_speed){

    //shift split two bytes
    uint8_t angle_low_byte = joint_angle;
    uint8_t angle_high_byte = joint_angle >> 8;
    uint8_t speed_low_byte = joint_speed;
    uint8_t speed_high_byte = joint_speed >> 8;

    uint8_t write_msg_data[]={

        //imediate command (no delay timing)
        WRITE_AX_CMD

        //command servo to go to goal position
        , GO_ANGLE_AX_REG
        , angle_low_byte
        , angle_high_byte

        //command servo to go go to goal speed
        , GO_SPEED_AX_REG
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->reply =

        roveDynmxl_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

//no errors -> ::roveDynmxl_WritePacketMSG set dynmxl_id->error_flag
    if(dynmxl->err_no){
        return roveDynmxl_CatchERRNO(dynmxl);
    }//end if

    return dynmxl->err_no;
}//end fnctn

int32_t roveDynmxl_ReadJointREQ(rove_dyna_serial* dynmxl){

    int16_t joint_angle =

        roveDynmxl_ReadRegisterREQ(

            dynmxl
            , READ_ANGLE_AX_REQ
            , READ_TWO_BYTES_AX_REQ);

    int16_t joint_speed =

        roveDynmxl_ReadRegisterREQ(

            dynmxl
            , READ_SPEED_AX_REQ
            , READ_TWO_BYTES_AX_REQ);

    //speed is the two high bytes, and angle is the two low bytes
    return joint_angle  + (joint_speed << 16);
}//end fnctn



/////////////////////////////////////////////////////Begin MSG Handling
//dynmxl sigle pin uart serial messaging protocol overhead
int32_t roveDynmxl_WritePacketMSG(rove_dyna_serial* dynmxl, uint8_t* write_msg_data, int32_t msg_data_byte_count) {

    //dynmxl check_sum begin to add all the bytes including the id
    uint8_t header_byte = 0;
    int32_t current_byte_count = 0;

    uint8_t check_sum = dynmxl->dynmxl_id;

    //check_sum with each byte in the data_buffer
    while(current_byte_count < msg_data_byte_count){
        check_sum += write_msg_data[current_byte_count];
    }//endwhile
    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
    check_sum = (~check_sum) & 0xFF;

    //set tristate buffer to uart_tx write status
    roveBoard_DigitalWrite(&dynmxl->tri_state_buffer, 1);

    //start dyna msg, id the dyna, tell dyna the msg data size (+ check_sum)
    header_byte = PACKET_AX_START_BYTE;
    roveBoard_UartWrite(dynmxl->uart, &header_byte, 1);

    header_byte = PACKET_AX_START_BYTE;
    roveBoard_UartWrite(dynmxl->uart, &header_byte, 1);

    header_byte = dynmxl->dynmxl_id;
    roveBoard_UartWrite(dynmxl->uart, &header_byte, 1);

    header_byte = msg_data_byte_count + 1;
    roveBoard_UartWrite(dynmxl->uart, &header_byte, 1);

    //send each byte in the data_buffer
    while(current_byte_count < msg_data_byte_count){
        roveBoard_UartWrite(dynmxl->uart, &write_msg_data[current_byte_count], 1);
    }//endwhile

    //send check sum
    roveBoard_UartWrite(dynmxl->uart, &check_sum, 1);
    //wait for uart_write
    roveBoard_DelayMicroSec(TX_DELAY_AX_MICRO_SEC);
    //set tristate buffer to uart_rx read status
    roveBoard_DigitalWrite(&dynmxl->tri_state_buffer, 0);

    if(dynmxl->read_reply_flag) {
        //delay poll listen for dyna reply (uart read on polling timeout delay with error_status) :: we return 0 on success
        return roveDynmxl_ReadPacketMSG(dynmxl);
    }//end if

    //no reply needed (implies read_reply_flag = 0) :: we return 0 as success
    return dynmxl->read_reply_flag;
}//end fnctn



int32_t roveDynmxl_ReadPacketMSG(rove_dyna_serial* dynmxl) {

    //Todo:
    //UART_Params.readTimeout
    uint8_t data_rx_byte_cnt = 0;
    int32_t current_byte_count = 0;
    uint8_t data_buffer[AX_MSG_MAX_BYTES];

    uint8_t check_sum = dynmxl->dynmxl_id;

    //This is used to decide how much pre-data to discard before quitting
    uint8_t rx_attempts = 0;
    while(rx_attempts < AX_MAX_READ_ATTMPT_CNT){

        roveBoard_UartRead(dynmxl->uart, data_buffer, 1);
        if(PACKET_AX_START_BYTE == data_buffer[data_rx_byte_cnt]) {

            //qual and discard header bytes
            data_rx_byte_cnt++;
            roveBoard_UartRead(dynmxl->uart, data_buffer, 1);
            if(PACKET_AX_START_BYTE == data_buffer[data_rx_byte_cnt]) {

                data_rx_byte_cnt++;
                roveBoard_UartRead(dynmxl->uart, data_buffer, 1);
                if(dynmxl->dynmxl_id == data_buffer[data_rx_byte_cnt]) {

                    //get the data payload
                    data_rx_byte_cnt= 0;
                    data_rx_byte_cnt = data_buffer[data_rx_byte_cnt];
                    while(current_byte_count < data_rx_byte_cnt){

                        roveBoard_UartRead(dynmxl->uart, &data_buffer[current_byte_count] , 1);
                        current_byte_count++;
                    }//endwhile

                    //dynmxl check_sum begin to add all the bytes (to the id)
                    current_byte_count = 0;
                    while(current_byte_count < data_rx_byte_cnt){
                        check_sum += data_buffer[current_byte_count];
                    }//endwhile

                    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
                    check_sum = (~check_sum) & 0xFF;
                    if(check_sum == data_buffer[data_rx_byte_cnt] ){

                       //return a single int32 reply payload
                       return dynmxl->err_no = roveDynmxl_ParseREPLY(dynmxl, data_buffer);
                    }//endif
                }//endif
            }//endif
        }//endif

        rx_attempts++;
    }//endwhile

    return AX_NO_PACKET;
}//end fnctn



//TODO JUDAH REFACTOR
roveDynmxl_ParseREPLY(rove_dyna_serial* dynmxl, uint8_t* data_buffer){

    dynmxl->reply_id = data_buffer[0];

    uint16_t reply = data_buffer[1];

        switch(dynmxl->reply_id){

            case DEV16_TEST_INSTRUCTION:
              dynmxl->reply = (uint32_t)reply;
              break;

            case DEV16_TEST_ERROR:
               dynmxl->err_no = (uint8_t)reply;
               break;
        default:
            dynmxl->reply = DEV16_NO_INSTRUCTION;
            break;
    }//end switch

        return dynmxl->err_no;

}//end fnctn

//TODO Reed, Connor, Owen Advice??
int32_t roveDynmxl_CatchERRNO(rove_dyna_serial* dynmxl){
    //TODO currently fnctn still pas through
    return dynmxl->reply;
}//end_if


//TODO refactor to aggregate functions How to couple with multiple lookup calls by Model lookup table??

//How to bind Registers by by Model Number (ie MX has extra regs... (enum cfg? lookup table?)

//https://gist.github.com/joshreed13/639117cbaefd505f0093
int32_t roveDynmxl_ReadRegistersREQ(rove_dyna_serial* dynmxl , uint8_t dyna_reg_addr, uint8_t dyna_reg_byte_cnt) {

    dynmxl->read_reply_flag = AX_READ_REPLY;

    uint8_t write_msg_data[]={

        READ_AX_REQ

        , dyna_reg_addr
        , dyna_reg_byte_cnt };

    return roveDynmxl_WritePacketMSG(dynmxl, write_msg_data, sizeof(write_msg_data));
}//end fnctn



int32_t roveDynmxl_TestWheelMode(rove_dyna_serial* dynmxl, uint32_t pause_microseconds){

    if( roveDynmxl_SetWheelModeCFG(dynmxl)) {
        printf("Dev16 Error roveDynmxl_SetWheelModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    if(roveDynmxl_SetWheelModeCFG(dynmxl)) {
        printf("Dev16 Error roveDynmxl_SetWheelModeCFG ldynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    int16_t speed = 0;
    //ramp up from zero to max forward
    for (speed = 0; speed < 1000; speed += 50) {

        //TODO arg2 could be negative??
        if(roveDynmxl_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        if(roveDynmxl_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        roveBoard_DelayMilliSec(pause_microseconds);
    } //end for

    //ramp back from max forward through zero to max reverse
    for (speed = 1000; speed > -1000; speed -= 50) {

        if(roveDynmxl_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        if(roveDynmxl_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        roveBoard_DelayMilliSec(pause_microseconds);
    } //end for

    //ramp back from max reverse landing on zero
    for (speed = -1000; speed < 0; speed += 50) {

        if(roveDynmxl_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        }//endif

        if(roveDynmxl_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        roveBoard_DelayMilliSec(pause_microseconds);
    } //end for

    roveBoard_DelayMilliSec(4*pause_microseconds);
    return AX_ERROR_FREE;
};//end fnctn



int32_t roveDynmxl_TestJointMode(rove_dyna_serial* dynmxl, uint32_t pause_microseconds){

    if( roveDynmxl_SetJointModeCFG(dynmxl)) {
        printf("Dev16 Error roveDynmxl_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    if(roveDynmxl_SetJointModeCFG(dynmxl)) {
        printf("Dev16 Error roveDynmxl_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    //very slowly now
    int16_t speed = 10;
    int16_t angle = 0;

    for (angle = 0; angle < 1000; angle += 50) {

        //TODO arg2 could be negative??
        if(roveDynmxl_RotateJointCMD(dynmxl, angle, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        if(roveDynmxl_RotateJointCMD(dynmxl, angle, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        roveBoard_DelayMilliSec(pause_microseconds);
    } //end for

    for (angle = 1000; angle > 0; angle -= 50) {

        if(roveDynmxl_RotateJointCMD(dynmxl, angle, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        }//endif

        if(roveDynmxl_RotateJointCMD(dynmxl, angle, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        }//endif

        roveBoard_DelayMilliSec(pause_microseconds);
    } //end for

    for (angle = 0; angle < 500; angle += 50) {

        if(roveDynmxl_RotateJointCMD(dynmxl, angle, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        }//endif

        if(roveDynmxl_RotateJointCMD(dynmxl, angle, speed)){
            printf("Dev16 Error roveDynmxl_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        }//endif

        roveBoard_DelayMilliSec(pause_microseconds);
    } //end for

    roveBoard_DelayMilliSec(4*pause_microseconds);
    return AX_ERROR_FREE;
};//end fnctn




/*///////////////////////////////////////////////////////////////////////////////////////
 void beginBaud(long baud)
{
    beginCom(baud);
}

void end()
{
    endCom();
}

int reset(unsigned char ID)
{
    char data[]={AX_RESET};
    return sendPacket(ID,data,sizeof(data));
}

int ping(unsigned char ID)
{
    char data[]={AX_PING};
    return sendPacket(ID,data,sizeof(data));
}

int setID(unsigned char ID, unsigned char newID)
{
    char data[]={AX_WRITE_DATA, AX_ID, newID};
    return sendPacket(ID,data,sizeof(data));
}

int setBD(unsigned char ID, long baud)
{
    unsigned char Baud_Rate = (2000000/baud) - 1;
    char data[]={AX_WRITE_DATA, AX_BAUD_RATE, Baud_Rate};
    return sendPacket(ID,data,sizeof(data));
}

nt moveRW(unsigned char ID, int Position)
{
    char Position_H,Position_L;
    Position_H = Position >> 8;
    Position_L = Position;
    char data[]={AX_REG_WRITE, AX_GOAL_POSITION_L, Position_L, Position_H};
    return sendPacket(ID,data,sizeof(data));
}

int moveSpeedRW(unsigned char ID, int Position, int Speed)
{
    char Position_H,Position_L,Speed_H,Speed_L;
    Position_H = Position >> 8;
    Position_L = Position;
    Speed_H = Speed >> 8;
    Speed_L = Speed;
    char data[]={AX_REG_WRITE, AX_GOAL_POSITION_L, Position_L, Position_H, Speed_L, Speed_H};
    return sendPacket(ID,data,sizeof(data));
}

void action()
{
    char data[]={AX_ACTION};
    return sendPacket(BROADCAST_ID,data,sizeof(data));
}

int torqueStatus( unsigned char ID, DynmxlStatus Status)
{
    char data[]={AX_WRITE_DATA, AX_TORQUE_ENABLE, (char)Status};
    return sendPacket(ID,data,sizeof(data));
}

int ledStatus(unsigned char ID, DynmxlStatus Status)
{
    char data[]={AX_WRITE_DATA, AX_LED, (char)Status};
    return sendPacket(ID,data,sizeof(data));
}

int readTemperature(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_PRESENT_TEMPERATURE, AX_BYTE_READ_ONE};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(1);
}

int readVoltage(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_PRESENT_VOLTAGE, AX_BYTE_READ_ONE};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(1);
}

int setTempLimit(unsigned char ID, unsigned char Temperature)
{
    char data[]={AX_WRITE_DATA, AX_LIMIT_TEMPERATURE, Temperature};
    return sendPacket(ID,data,sizeof(data));
}

int setVoltageLimit(unsigned char ID, unsigned char DVoltage, unsigned char UVoltage)
{
    char data[]={AX_WRITE_DATA, AX_DOWN_LIMIT_VOLTAGE, DVoltage, UVoltage};
    return sendPacket(ID,data,sizeof(data));
}

int setAngleLimit(unsigned char ID, int CWLimit, int CCWLimit)
{
    char CW_H,CW_L,CCW_H,CCW_L;
    CW_H = CWLimit >> 8;
    CW_L = CWLimit;
    CCW_H = CCWLimit >> 8;
    CCW_L = CCWLimit;
    //TODO: Not sure if the first byte should be AX_CCW_CW_LENGTH or AX_VL_LENGTH
    char data[]={AX_WRITE_DATA, AX_CW_ANGLE_LIMIT_L, CW_L, CW_H, AX_CCW_ANGLE_LIMIT_L, CCW_L, CCW_H};
    return sendPacket(ID,data,sizeof(data));
}

int setMaxTorque(unsigned char ID, int MaxTorque)
{
    char MaxTorque_H,MaxTorque_L;
    MaxTorque_H = MaxTorque >> 8;
    MaxTorque_L = MaxTorque;
    char data[]={AX_WRITE_DATA, AX_MAX_TORQUE_L, MaxTorque_L, MaxTorque_H};
    return sendPacket(ID,data,sizeof(data));
}

int setSRL(unsigned char ID, DynmxlStatusReturnLevel SRL)
{
    char data[]={AX_WRITE_DATA, AX_RETURN_LEVEL, (char)SRL};
    return sendPacket(ID,data,sizeof(data));
}

int setRDT(unsigned char ID, unsigned char RDT)
{
    char data[]={AX_WRITE_DATA, AX_RETURN_DELAY_TIME, (RDT/2)};
    return sendPacket(ID,data,sizeof(data));
}

int setLEDAlarm(unsigned char ID, unsigned char LEDAlarm)
{
    char data[]={AX_WRITE_DATA, AX_ALARM_LED, LEDAlarm};
    return sendPacket(ID,data,sizeof(data));
}

int setShutdownAlarm(unsigned char ID, unsigned char SALARM)
{
    //TODO: Not sure of packet structure with AX_ALARM_LED and AX_WRITE_DATA
    char data[]={AX_WRITE_DATA, AX_ALARM_SHUTDOWN, SALARM};
    return sendPacket(ID,data,sizeof(data));
}

int setCMargin(unsigned char ID, unsigned char CWCMargin, unsigned char CCWCMargin)
{
    char data[]={AX_WRITE_DATA, AX_CW_COMPLIANCE_MARGIN, CWCMargin, AX_CCW_COMPLIANCE_MARGIN, CCWCMargin};
    return sendPacket(ID,data,sizeof(data));
}

int setCSlope(unsigned char ID, unsigned char CWCSlope, unsigned char CCWCSlope)
{
    char data[]={AX_WRITE_DATA, AX_CW_COMPLIANCE_SLOPE, CWCSlope, CCWCSlope};// AX_CCW_COMPLIANCE_SLOPE
    return sendPacket(ID,data,sizeof(data));
}

int setPunch(unsigned char ID, int Punch)
{
    char Punch_H,Punch_L;
    Punch_H = Punch >> 8;
    Punch_L = Punch;
    char data[]={AX_WRITE_DATA, AX_PUNCH_L, Punch_L, Punch_H};
    return sendPacket(ID,data,sizeof(data));
}

int moving(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_MOVING, AX_BYTE_READ_ONE};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(1);
}

int lockregister(unsigned char ID)
{
    char data[]={AX_WRITE_DATA, AX_LOCK, LOCK};
    return sendPacket(ID,data,sizeof(data));
}

int RWStatus(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_REGISTERED_INSTRUCTION, AX_BYTE_READ_ONE};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(1);
}

int readLoad(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_PRESENT_LOAD_L, AX_BYTE_READ_TWO};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(2);
}//END::GBENGA TODO*/




///////////////::BEGIN//////Horizon Assets ////////////////////////



/* Judah TODO
//standard rcservo : 1000uS full reverse : 1500uS stop : 2000uS full forward
void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed);
void roveDriveMotor_ByPWM(rovePWM_Handle motor, int16_t speed){

    int16_t microseconds;

    //scale down to the final range to be between 1000 and 2000
    microseconds = speed / 2;

    //offset so that 1500 is neutral
    microseconds += 1500;

    //protect the upper bound on motor pulse width
    if (microseconds > 2000) {

        microseconds = 2000;
    }//endif

    //protect the lower bound on motor pulse width
    if (microseconds < 1000) {

        microseconds = 1000;
    }//endif

    rovePWM_Write(motor, microseconds);
    return;
} //endfnctn



//command_byte : forward /reverse
typedef struct linear_actuator_struct {

    uint8_t command_byte;
    uint8_t speed;

}__attribute__((packed)) linear_actuator_struct, *linear_actuator_struct_ptr;

//positive is forward, negative is reverse, only 8 bit low_byte is speed
void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed);
void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed){

    linear_actuator_struct linear_actuator;

    if( speed > 0 ){

        linear_actuator.command_byte = LIN_ACT_FORWARD;
    }else{

        linear_actuator.command_byte = LIN_ACT_REVERSE;
    }//end if


    //bit of an ugly hack to have called this whole int16_t speed
    linear_actuator.speed = (uint8_t)speed;

    roveUART_Write(tiva_pin, (char*)&linear_actuator, sizeof(linear_actuator) );
    return;
}//endfnctn
End Judah TODO*/
