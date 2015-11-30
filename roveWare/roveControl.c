// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
// mrdt::rovWare
#include "roveControl.h"

int32_t roveDynamixel_Init(rove_dyna_serial* dynamixel, uint8_t dyna_id, int32_t tiva_pin, uint8_t write_only_flag ){

    //constructor fnctn
    dynamixel->dynamixel_id = dyna_id;
    dynamixel->tiva_pin = tiva_pin;
    dynamixel->write_only_flag = write_only_flag;

    return dynamixel->error_flag = AX_ERROR_FREE;
};//end fnctn



//TODO REED:
int32_t roveDynamixel_HandleAxREPLY(rove_dyna_serial* dynamixel, uint8_t* data_buffer) {

    //TODO system_abort :: delay for sys abort console logging?
    printf("Undhandled error reply: %d dynamixel_id: %d tiva_pin: %d", dynamixel->read_reply, dynamixel->dynamixel_id, dynamixel->tiva_pin);

    //currently tis fnctn debug prints console error but fnctn still return success stub
    return dynamixel->read_reply = AX_ERROR_FREE;
}//end_if

int32_t roveDynamixel_ParseReplyInt32MSG(uint8_t* data_buffer) {

    switch( data_buffer[0] ){

        case DEV16_TEST_INSTRUCTION:
            return (uint16_t)(data_buffer[1]);

        case DEV16_TEST_ERROR:
            return (uint8_t)(data_buffer[1]);

        default:
            return DEV16_NO_INSTRUCTION;
    }//end switch
}//end fnctn
//::End Quick Dev utilities:
//end TODO REED





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

///////////////////////////////////////////////////////Begin WHEEL Mode CFG/CMD
//wheel mode can be used for wheel-type operation robots since motors of the robot will spin infinitely at angle zero
//Wheel Mode : set to both Angle Limits to zero. The motor spins endlessly
int32_t roveDynamixel_SetWheelModeCFG(rove_dyna_serial* dynamixel) {

    //wheel Mode both are 0
    uint8_t cw_angle_limit_low_byte = 0;
    uint8_t cw_angle_limit_high_byte = 0;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]=

        //immediate no delay timing
        {WRITE_AX_CMD

         //TODO reg 8?? switch mode by setting cw/ccw angle infinte when both are zero
        , WHEEL_MODE_AX_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel->error_flag = roveDynamixel_WritePacketMSG(dynamixel, write_msg_data, sizeof(write_msg_data), dynamixel->write_only_flag );

    //Immediate return zero was read suceess (or listen_for_reply_flag was off)
    return roveDynamixel_HandleAxREPLY(dynamixel, write_msg_data);
}//end fnctn

int32_t roveDynamixel_SpinWheelCMD(rove_dyna_serial* dynamixel, int16_t wheel_speed) {

    //handle negative speed scale to absolute value
    wheel_speed =+ INTERFACE_PROTOCOL_SPEEDS;

    //scale direction by shift operations
    if(wheel_speed > INTERFACE_PROTOCOL_SPEEDS) {

        //clockwise direction is the 10th bit
        wheel_speed += (1 >> 10);
    }//end if
    uint8_t speed_low_byte = wheel_speed;
    uint8_t speed_high_byte = wheel_speed >> 8;

    uint8_t write_msg_data[]=

        //imediate command (no delay timing)
        {WRITE_AX_CMD

        //command servo to go go to goal speed
        , GO_SPEED_AX_REG
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel->error_flag = roveDynamixel_WritePacketMSG(dynamixel, write_msg_data, sizeof(write_msg_data), dynamixel->write_only_flag );
    return roveDynamixel_HandleAxREPLY(dynamixel, write_msg_data);
}//end fnctn

int32_t roveDynamixel_ReadWheelREQ(rove_dyna_serial* dynamixel) {

    //TODO GBENGA:
    //return_roveDynamixel_ReadRegistersREQ(dynamixel_id->dynamixel_id, AX12_SPEED_REGISTER, TWO_BYTES);
    return AX_ERROR;
}//end fnctn
//::End WHEEL Mode


/////////////////////////////////////////////////////Begin JOINT Mode CFG/CMD

//joint mode can be used for multi-joint robot since the joint mode can be controlled to go at specific speed to specific angles
//Joint Mode : set to Angle Limit anything other than zero??
int32_t roveDynamixel_SetJointModeCFG(rove_dyna_serial* dynamixel) {

    //TOD how to ctually set set speed zero? homing function function goal rotation to zero?
    roveDynamixel_SpinWheelCMD(dynamixel, 0);

    //SetEndless goal rotation...wheel mode is from TODO 0 to 4095 for the MX SERIES?
    //Multi Turn mode on the MX?
    uint8_t cw_angle_limit_low_byte = 255;
    uint8_t cw_angle_limit_high_byte = 3;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]=

         //immediate no delay timing
        {WRITE_AX_CMD

        //switch mode by setting ccw angle max limit
        , JOINT_MODE_AX_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel->error_flag = roveDynamixel_WritePacketMSG(dynamixel, write_msg_data, sizeof(write_msg_data), dynamixel->write_only_flag );

    //no errors -> ::roveDynamixel_WritePacketMSG set dynamixel_id->error_flag
    if(dynamixel->error_flag){

        return roveDynamixel_HandleAxREPLY(dynamixel, write_msg_data);
    }//end if
    return dynamixel->error_flag;
}//end fnctn

int32_t roveDynamixel_RotateJointCMD(rove_dyna_serial* dynamixel, uint16_t joint_position, uint16_t joint_speed) {

    //shift split two bytes
    uint8_t position_low_byte = joint_position;
    uint8_t position_high_byte = joint_position >> 8;
    uint8_t speed_low_byte = joint_speed;
    uint8_t speed_high_byte = joint_speed >> 8;

    uint8_t write_msg_data[]=

        //imediate command (no delay timing)
        {WRITE_AX_CMD

        //command servo to go to goal position
        , GO_ANGLE_AX_REG
        , position_low_byte
        , position_high_byte

        //command servo to go go to goal speed
        , GO_SPEED_AX_REG
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynamixel reply when asked to)
    dynamixel->error_flag = roveDynamixel_WritePacketMSG(dynamixel, write_msg_data, sizeof(write_msg_data), dynamixel->write_only_flag );

    //no errors -> ::roveDynamixel_WritePacketMSG set dynamixel_id->error_flag
    if(dynamixel->error_flag){

        return roveDynamixel_HandleAxREPLY(dynamixel, write_msg_data);
    }//end if
    return dynamixel->error_flag;
}//end fnctn

int32_t roveDynamixel_ReadJointREQ(rove_dyna_serial* dynamixel) {

    int16_t joint_angle = roveDynamixel_ReadRegistersREQ(dynamixel, READ_ANGLE_AX_REQ, 2);
    int16_t joint_speed = roveDynamixel_ReadRegistersREQ(dynamixel, READ_SPEED_AX_REQ, 2);

    //speed is the two high bytes, and angle is the two low bytes
    return joint_angle  + (joint_speed << 16);
}//end fnctn
//::End JOINT Mode







//TODO JOSH REED messaging refactor???:
/////////////////////////////////////////////////////Begin MSG Handling
//dynamixel sigle pin uart serial messaging protocol overhead
int32_t roveDynamixel_WritePacketMSG(rove_dyna_serial* dynamixel, uint8_t* write_msg_data, int32_t msg_data_byte_count, uint8_t read_reply_flag){

    //dynamixel check_sum begin to add all the bytes including the id
    uint8_t header_byte = 0;
    int32_t current_byte_count = 0;

    int32_t tiva_pin = roveGetPinNum_ByDeviceId(dynamixel->dynamixel_id);
    uint8_t check_sum = dynamixel->dynamixel_id;

    //check_sum with each byte in the data_buffer
    while(current_byte_count < msg_data_byte_count){
        check_sum += write_msg_data[current_byte_count];
    }//endwhile
    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
    check_sum = (~check_sum) & 0xFF;

    //set tristate buffer to uart_tx write status
    roveDigital_Write(HW_TRI_STATE_PIN, 1);

    //start dyna msg, id the dyna, tell dyna the msg data size (+ check_sum)
    header_byte = PACKET_AX_START_BYTE;
    roveUart_Write(tiva_pin, &header_byte, 1);

    header_byte = PACKET_AX_START_BYTE;
    roveUart_Write(tiva_pin, &header_byte, 1);

    header_byte = dynamixel->dynamixel_id;
    roveUart_Write(tiva_pin, &header_byte, 1);

    header_byte = msg_data_byte_count + 1;
    roveUart_Write(tiva_pin, &header_byte, 1);

    //send each byte in the data_buffer
    while(current_byte_count < msg_data_byte_count){
        roveUart_Write(tiva_pin, &write_msg_data[current_byte_count], 1);
    }//endwhile

    //send check sum
    roveUart_Write(tiva_pin, &check_sum, 1);
    //wait for uart_write
    roveDelay_MicroSec(TX_DELAY_AX_MICRO_SEC);
    //set tristate buffer to uart_rx read status
    roveDigital_Write(HW_TRI_STATE_PIN, 0);

    if(read_reply_flag) {
        //delay poll listen for dyna reply (uart read on polling timeout delay with error_status) :: we return 0 on success
        return roveDynamixel_ReadPacketMSG(dynamixel->dynamixel_id);
    }//end if

    //no reply needed (implies read_reply_flag = 0) :: we return 0 on success
    return read_reply_flag;
}//end fnctn

int32_t roveDynamixel_ReadPacketMSG(uint8_t dynamixel_id) {

    //Todo:
    //UART_Params.readTimeout
    uint8_t data_rx_byte_cnt = 0;
    int32_t current_byte_count = 0;
    uint8_t data_buffer[AX_MSG_MAX_BYTES];

    int32_t tiva_pin = roveGetPinNum_ByDeviceId(dynamixel_id);
    uint8_t check_sum = dynamixel_id;

    //This is used to decide how much pre-data to discard before quitting
    uint8_t rx_attempts = 0;
    while(rx_attempts < AX_MAX_READ_ATTMPT_CNT){

        roveUart_Read(tiva_pin, data_buffer, 1);
        if(PACKET_AX_START_BYTE == data_buffer[data_rx_byte_cnt]) {

            //qual and discard header bytes
            data_rx_byte_cnt++;
            roveUart_Read(tiva_pin, data_buffer, 1);
            if(PACKET_AX_START_BYTE == data_buffer[data_rx_byte_cnt]) {

                data_rx_byte_cnt++;
                roveUart_Read(tiva_pin, data_buffer, 1);
                if(dynamixel_id == data_buffer[data_rx_byte_cnt]) {

                    //get the data payload
                    data_rx_byte_cnt= 0;
                    data_rx_byte_cnt = data_buffer[data_rx_byte_cnt];
                    while(current_byte_count < data_rx_byte_cnt){

                        roveUart_Read(tiva_pin, &data_buffer[current_byte_count] , 1);
                        current_byte_count++;
                    }//endwhile

                    //dynamixel check_sum begin to add all the bytes (to the id)
                    current_byte_count = 0;
                    while(current_byte_count < data_rx_byte_cnt){
                        check_sum += data_buffer[current_byte_count];
                    }//endwhile

                    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
                    check_sum = (~check_sum) & 0xFF;
                    if(check_sum == data_buffer[data_rx_byte_cnt] ){

                       //return a single int32 reply payload
                       return roveDynamixel_ParseReplyInt32MSG(data_buffer);
                    }//endif
                }//endif
            }//endif
        }//endif

        rx_attempts++;
    }//endwhile

    return AX_NO_PACKET;
}//end fnctn






//TODO GBENGA: refactor to aggregate functions How to couple with multiple lookup calls by Model lookup table??
//https://gist.github.com/joshreed13/639117cbaefd505f0093
//TODO GBENGA: How to couple by AX12_SPEED_REGISTER AX12_ANGLE_POSITION_REGISTER by Model loojup table???
int32_t roveDynamixel_ReadRegistersREQ(rove_dyna_serial* dynamixel, uint8_t dyna_registers_addr, uint8_t dyna_registers_byte_cnt) {

    uint8_t write_msg_data[]=

        {READ_AX_REQ

        , dyna_registers_addr
        , dyna_registers_byte_cnt};

    return roveDynamixel_WritePacketMSG(dynamixel, write_msg_data, sizeof(write_msg_data), AX_READ_REPLY);
}//end fnctn

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
}//END::GBENGA TODO*/













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
}//end fnctn */
