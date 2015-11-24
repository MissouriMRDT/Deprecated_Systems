// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_CntrlUtils.c
//
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
// mrdt::rovWare
#include "roveWare_DynamixelAX12.h"

////////////////////////////////////////////////////////////////////TODO Finish Mode Specs

    //dynamixel servos have different configurable "modes" of operation depending on series
    //the range and unit of CW/CCW Angle Limits dictate how positon and speed are interperted by operation mode
    //position and speed command range and unit scale will vary or have no effect with different operation mode

//Satterfield/Bischoff:  TODO-> Proofread/Edit/Maintain Model Differences: Specs

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


///////////////////////////////////////////////////////Begin WHEEL Mode CFG/CMD
//wheel mode can be used for wheel-type operation robots since motors of the robot will spin infinitely at angle zero
//Wheel Mode : set to both Angle Limits to zero. The motor spins endlessly
void roveDynamixel_SetWheelModeCFG(rove_dyna_serial_port* dynamixel_id) {

    //wheel Mode both are 0
    uint8_t cw_angle_limit_low_byte = 0;
    uint8_t cw_angle_limit_high_byte = 0;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]=

        //immediate no delay timing
        {WRITE_AX12_CMD

         //switch mode by setting cw/ccw angle infinte when both are zero
        , SET_MODE_AX12_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel_id->error_flag = roveDynamixel_WritePacketMSG(dynamixel_id->dynamixel_id, write_msg_data, sizeof(write_msg_data), dynamixel_id->listen_for_reply_flag );

    //Either was read suceess (or listen_for_reply_flag was off)
    if(dynamixel_id->error_flag){

        roveDynamixel_HandleErrorREPLY(dynamixel_id, write_msg_data);
    }//end if
    return;
}//end fnctn

void roveDynamixel_SpinWheelCMD(rove_dyna_serial_port* dynamixel_id, int16_t wheel_speed) {

    //handle negative speed scale to absolute value
    wheel_speed =+ AX12_WHEEL_SPEED_ORIGIN_OFFSET;

    //scale direction by shift operations
    if(wheel_speed > AX12_WHEEL_SPEED_ORIGIN_OFFSET) {

        //clockwise direction is the 10th bit
        wheel_speed += (1 >> 10);
    }//end if
    uint8_t speed_low_byte = wheel_speed;
    uint8_t speed_high_byte = wheel_speed >> 8;

    uint8_t write_msg_data[]=

        //immediate no delay timing
        {WRITE_AX12_CMD

        //goal speed
        , AX12_SPEED_REGISTER
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel_id->error_flag = roveDynamixel_WritePacketMSG(dynamixel_id->dynamixel_id, write_msg_data, sizeof(write_msg_data), dynamixel_id->listen_for_reply_flag );

    //no errors -> ::roveDynamixel_WritePacketMSG set dynamixel_id->error_flag
    if(dynamixel_id->error_flag){
        roveDynamixel_HandleErrorREPLY(dynamixel_id, write_msg_data);
    }//end if
    return;
}//end fnctn

uint32_t roveDynamixel_ReadWheelREQ(rove_dyna_serial_port* dynamixel_id) {

    //TODO GBENGA:
    uint32_t return_uint32_always = roveDynamixel_ReadRegistersREQ(dynamixel_id->dynamixel_id, AX12_SPEED_REGISTER, TWO_BYTES);
    return return_uint32_always;
}//end fnctn
//::End WHEEL Mode


/////////////////////////////////////////////////////Begin JOINT Mode CFG/CMD

//joint mode can be used for multi-joint robot since the joint mode can be controlled to go at specific speed to specific angles
//Joint Mode : set to Angle Limit anything other than zero??
void roveDynamixel_SetJointModeCFG(rove_dyna_serial_port* dynamixel_id) {

    //TOD how to ctually set set speed zero? homing function function goal rotation to zero?
    roveDynamixel_SpinWheelCMD(dynamixel_id, ZERO_SPEED);

    //SetEndless goal rotation...wheel mode is from TODO 0 to 4095 for the MX SERIES?
    //Multi Turn mode on the MX?
    uint8_t cw_angle_limit_low_byte = 255;
    uint8_t cw_angle_limit_high_byte = 3;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]=

         //immediate no delay timing
        {WRITE_AX12_CMD

        //switch mode by setting ccw angle max limit
        , SET_MODE_AX12_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel_id->error_flag = roveDynamixel_WritePacketMSG(dynamixel_id->dynamixel_id, write_msg_data, sizeof(write_msg_data), dynamixel_id->listen_for_reply_flag );

    //no errors -> ::roveDynamixel_WritePacketMSG set dynamixel_id->error_flag
    if(dynamixel_id->error_flag){

        roveDynamixel_HandleErrorREPLY(dynamixel_id, write_msg_data);
    }//end if
    return;
}//end fnctn

void roveDynamixel_RotateJointCMD(rove_dyna_serial_port* dynamixel_id, uint16_t joint_position, uint16_t joint_speed) {

    //shift split two bytes
    uint8_t position_low_byte = joint_position;
    uint8_t position_high_byte = joint_position >> 8;
    uint8_t speed_low_byte = joint_speed;
    uint8_t speed_high_byte = joint_speed >> 8;

    uint8_t write_msg_data[]=

        //imediate no delay timing
        {WRITE_AX12_CMD

        //goal position
        , AX12_ANGLE_POSITION_REGISTER
        , position_low_byte
        , position_high_byte

        //goal speed
        , AX12_SPEED_REGISTER
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel_id->error_flag = roveDynamixel_WritePacketMSG(dynamixel_id->dynamixel_id, write_msg_data, sizeof(write_msg_data), dynamixel_id->listen_for_reply_flag );

    //no errors -> ::roveDynamixel_WritePacketMSG set dynamixel_id->error_flag
    if(dynamixel_id->error_flag){

        roveDynamixel_HandleErrorREPLY(dynamixel_id, write_msg_data);
    }//end if
    return;
}//end fnctn

uint32_t roveDynamixel_ReadJointREQ(rove_dyna_serial_port* dynamixel_id) {

//TODO GBENGA: How to couple by AX12_SPEED_REGISTER AX12_ANGLE_POSITION_REGISTER by Model loojup table???
    int16_t joint_speed = roveDynamixel_ReadRegistersREQ(dynamixel_id->dynamixel_id, AX12_SPEED_REGISTER, TWO_BYTES);
    int16_t joint_angle = roveDynamixel_ReadRegistersREQ(dynamixel_id->dynamixel_id, AX12_ANGLE_POSITION_REGISTER, TWO_BYTES);

    //speed is the two high bytes, and angle is the two low bytes
    uint32_t return_uint32_always = joint_angle  + (joint_speed << 16);
    return return_uint32_always;
}//end fnctn
//::End JOINT Mode

//Quick Dev utilities:
int16_t roveDynamixel_ReadRegistersREQ(uint8_t dynamixel_id, uint8_t dyna_registers_addr, uint8_t dyna_registers_byte_cnt) {

    uint8_t write_msg_data[]=

        {READ_AX12_REQ

        , dyna_registers_addr
        , dyna_registers_byte_cnt};

    int16_t return_int16_t_always = (int16_t)roveDynamixel_WritePacketMSG(dynamixel_id, write_msg_data, sizeof(write_msg_data), LISTEN_FOR_REPLY);

    return return_int16_t_always;
}//end fnctn
//::End JOINT Mode


//TODO JOSH REED refactor HERE:
/////////////////////////////////////////////////////Begin MSG Handling

void roveDynamixel_WriteByteMSG(uint8_t dynamixel_id, uint8_t tx_data_byte) {

    //which pin is this device //TODO I dunno I like this in a struct instance maybe tho
    int tiva_pin = roveGetPinNum_ByDeviceId(dynamixel_id);

    //Todo roveUart_Read should args as uint8_t??
    //(char*)&  casts low level roveWare stdint _t types to high level char, int, etc ecosystem
    roveUart_Write(tiva_pin, (char*)&tx_data_byte, SINGLE_BYTE);
}//end fnctn

//dynamixel sigle pin uart serial messaging protocol overhead
uint32_t roveDynamixel_WritePacketMSG(uint8_t dynamixel_id, uint8_t* data_buffer, uint16_t data_byte_count, uint8_t listen_for_reply_flag){

    //dynamixel check_sum begin to add all the bytes including the id
    uint16_t current_byte_count = 0;
    uint8_t check_sum = dynamixel_id;

    //check_sum with each byte in the data_buffer
    while(current_byte_count < data_byte_count){
        check_sum += data_buffer[current_byte_count];
    }//endwhile

    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
    check_sum = (~check_sum) & 0xFF;

    //TODO I don't like this hard coded here like this tho...dont love args either tho
    roveDigital_Write(TRI_STATE_PIN, TX_HIGH);

    //start dyna msg, id the dyna, tell dyna the msg data size (+ check_sum)
    roveDynamixel_WriteByteMSG(dynamixel_id, DYNAMIXEL_PACKET_START_BYTE);
    roveDynamixel_WriteByteMSG(dynamixel_id, DYNAMIXEL_PACKET_START_BYTE);
    roveDynamixel_WriteByteMSG(dynamixel_id, dynamixel_id);
    roveDynamixel_WriteByteMSG(dynamixel_id, data_byte_count+1);

    //send each byte in the data_buffer
    while(current_byte_count < data_byte_count){
        roveDynamixel_WriteByteMSG(dynamixel_id, data_buffer[current_byte_count]);
    }//endwhile

    //send check sum
    roveDynamixel_WriteByteMSG(dynamixel_id, check_sum);

    //wait for uart_write
    roveDelay_MicroSec(DYNAMIXEL_TX_DELAY_MICRO_SEC);
    roveDigital_Write(TRI_STATE_PIN, RX_LOW);

    if(listen_for_reply_flag) {

        //delay poll listen for dyna error repsonse
        return roveDynamixel_ReadPacketMSG(dynamixel_id);
    }//end if

    //no reply needed listen_for_reply_flag = 0
    return listen_for_reply_flag;
}//end fnctn

uint8_t roveDynamixel_ReadByteMSG(uint8_t dynamixel_id) {

    uint8_t rx_data_byte;
    int tiva_pin = roveGetPinNum_ByDeviceId(dynamixel_id);

    //Todo roveUart_Read should args as uint8_t??
    roveUart_Read(tiva_pin, (char*)&rx_data_byte, SINGLE_BYTE);
    return rx_data_byte;
}//end fnctn

uint32_t roveDynamixel_ReadPacketMSG(uint8_t dynamixel_id) {

    //Todo:
    //2015 MOB Device Read???? //UART_Params.readTimeout
    //plug into Uart_READ
    uint8_t data_rx_byte_cnt = 0;
    uint8_t data_buffer[MAX_BYTES_AX12_REPLY];
    int16_t current_byte_count = 0;

    uint8_t check_sum = dynamixel_id;

    //This is used to decide how much pre-data to discard before quitting
    uint8_t rx_attempts = 0;
    while(rx_attempts < MAX_READ_ATTEMPT_AX12_CNT){

        if(DYNAMIXEL_PACKET_START_BYTE == roveDynamixel_ReadByteMSG(dynamixel_id)) {

            if(DYNAMIXEL_PACKET_START_BYTE == roveDynamixel_ReadByteMSG(dynamixel_id)) {

                if(dynamixel_id == roveDynamixel_ReadByteMSG(dynamixel_id)) {

                    data_rx_byte_cnt = roveDynamixel_ReadByteMSG(dynamixel_id);

                    while(current_byte_count < data_rx_byte_cnt){

                        data_buffer[current_byte_count] = roveDynamixel_ReadByteMSG(dynamixel_id);
                        current_byte_count++;
                    }//endwhile

                    //dynamixel check_sum begin to add all the bytes including the id
                    current_byte_count = 0;
                    while(current_byte_count < data_rx_byte_cnt){
                        check_sum += data_buffer[current_byte_count];
                    }//endwhile

                    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
                    check_sum = (~check_sum) & 0xFF;
                    if(check_sum == data_buffer[data_rx_byte_cnt] ){

                       return roveDynamixel_ParseReplyUint32MSG(data_buffer);
                    }//endif
                }//endif
            }//endif
        }//endif

        rx_attempts++;
    }//endwhile

    return NO_PACKET;
}//end fnctn

//TODO REED:
void roveDynamixel_HandleErrorREPLY(rove_dyna_serial_port* dynamixel_id, uint8_t* data_buffer) {

    printf("Undhandled error reply: %d dynamixel_id: %d tiva_pin: %d", dynamixel_id->reply, dynamixel_id->dynamixel_id, dynamixel_id->tiva_pin);
    return;
}//end_if


//TODO REED
uint32_t roveDynamixel_ParseReplyUint32MSG(uint8_t* data_buffer) {

    uint32_t return_uint32_always = 0;
    switch( data_buffer[0] ){

        case TEST_INSTRUCTION:
            return return_uint32_always + (uint16_t)(data_buffer[1]);

        case TEST_ERROR:
            return return_uint32_always + (uint8_t)(data_buffer[1]);

        default :
            return NO_INSTRUCTION;
    }//end switch
}//end fnctn
//::End Quick Dev utilities:
//end TODO REED


//TODO GBENGA: refactor to aggregate functions with multiple lookup calls HERE:

//https://gist.github.com/joshreed13/639117cbaefd505f0093


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

int torqueStatus( unsigned char ID, DynamixelStatus Status)
{
    char data[]={AX_WRITE_DATA, AX_TORQUE_ENABLE, (char)Status};
    return sendPacket(ID,data,sizeof(data));
}

int ledStatus(unsigned char ID, DynamixelStatus Status)
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

int setSRL(unsigned char ID, DynamixelStatusReturnLevel SRL)
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

int lockRegister(unsigned char ID)
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
}


 */







/*JUDAH DEV////////////////////////Begin Dynamixel Runtime CFG and Telem REQUEST ROUTINES
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
}//end fnctn */
