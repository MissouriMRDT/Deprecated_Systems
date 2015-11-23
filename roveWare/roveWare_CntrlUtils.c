// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_CntrlUtils.c
//
// jrs6w7@mst.edu
//
// Control Utilities for URC 2016
//
// mrdt::rovWare
#include "roveWare_CntrlUtils.h"

////////////////////////////////////////////////////////////////////TODO Finish Mode Specs

    //dynamixel servos have different configurable "modes" of operation depending on series
    //the range and unit of CW/CCW Angle Limits dictate how positon and speed are interperted by operation mode
    //position and speed command range and unit scale will vary or have no effect with different operation mode

//http://support.robotis.com/en/techsupport_eng.htm#product/dynamixel/ax_series/dxl_ax_actuator.htm

    //TODO AX12 SOME specs:
        //AX12 has two modes
            //10bit Wheel -> 0-1023 CCW, 1024 - 2047 CW
            //no amperage control

    //TODO MX12 SOME specs
        //MX12 has three modes
            //12bit Wheel -> 0-2047 CCW, 2048 - 4095 CW
            //Goal_punch_reg and acceleration_reg control provides amperage control

///////////////////////////////////////////////////////Begin WHEEL Mode CFG/CMD
//wheel mode can be used for wheel-type operation robots since motors of the robot will spin infinitely at angle zero
//Wheel Mode : set to both Angle Limits to zero. The motor spins endlessly
void roveDynamixel_SetWheelModeCFG(uint8_t dynamixel_id) {

    //wheel Mode both are 0
    uint8_t cw_angle_limit_low_byte = 0;
    uint8_t cw_angle_limit_high_byte = 0;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t msg_data[]=
        //no exec on delay timing
        {WRITE_AX12_CMD
         //switch mode by setting cw/ccw angle infinte when both are zero
        , SET_MODE_AX12_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return;
}//end fnctn

//TODO remove 'spin_wheel_direction' arg1??   ->...arg2 could be negative??
void roveDynamixel_SpinWheelCMD(uint8_t dynamixel_id, uint8_t spin_wheel_direction, uint16_t wheel_speed) {

    //scale speed by shift operations
    if(spin_wheel_direction == CLOCKWISE) {
        wheel_speed += (1 >> 10);
    }//end if
    uint8_t speed_low_byte = wheel_speed;
    uint8_t speed_high_byte = wheel_speed >> 8;

    uint8_t msg_data[]=
        //no exec on delay timing
        {WRITE_AX12_CMD
        //goal speed
        , WRITE_TARGET_SPEED_AX12_CMD
        , speed_low_byte
        , speed_high_byte};

    roveDynamixel_WritePacketMSG(dynamixel_id , msg_data, sizeof(msg_data));
    return;
}//end fnctn
//::End WHEEL Mode

/////////////////////////////////////////////////////Begin JOINT Mode CFG/CMD
//joint mode can be used for multi-joint robot since the joint mode can be controlled to go at specific speed to specific angles
//Joint Mode : set to Angle Limit anything other than zero??
void roveDynamixel_SetJointModeCFG(uint8_t dynamixel_id) {

    //set speed zero? homing function function goal rotation to zero?
    roveDynamixel_SpinWheelCMD(dynamixel_id, COUNTERCLOCKWISE, ZERO_SPEED);

    //SetEndless goal rotation...wheel mode is from TODO 0 to 4095 for the MX SERIES?
    //Multi Turn mode on the MX?
    uint8_t cw_angle_limit_low_byte = 255;
    uint8_t cw_angle_limit_high_byte = 3;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t msg_data[]=

        {WRITE_AX12_CMD
        //switch mode by setting ccw angle max limit
        , SET_MODE_AX12_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    if( !roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data)) ){

         roveDynamixel_HandleErrorMSG(dynamixel_id, msg_data);
    }//end if
    return;
}//end fnctn

void roveDynamixel_RotateJointCMD(uint8_t dynamixel_id, uint16_t joint_position, uint16_t joint_speed) {

    //shift split two bytes
    uint8_t position_low_byte = joint_position;
    uint8_t position_high_byte = joint_position >> 8;
    uint8_t speed_low_byte = joint_speed;
    uint8_t speed_high_byte = joint_speed >> 8;

    uint8_t msg_data[]=
        //no exec on delay timing
        {WRITE_AX12_CMD
        //goal position
        , WRITE_TARGET_POSITN_AX12_CMD
        , position_low_byte
        , position_high_byte
        //goal speed
        , WRITE_TARGET_SPEED_AX12_CMD
        , speed_low_byte
        , speed_high_byte};

    if( !roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data)) ){

        roveDynamixel_HandleErrorMSG(dynamixel_id, msg_data);
    }//end if
    return;
}//end fnctn
//::End JOINT Mode
//::End CMD Routines

/////////////////////////////////////////////////////Begin MSG Handling
//TODO NEXT : this still stubs out empty success always
void roveDynamixel_HandleErrorMSG(uint8_t dynamixel_id, uint8_t* data_buffer) {

      switch( data_buffer[0] ){

          case TEST_ERROR:
              printf("dynamixel_id: %d TEST_ERROR: %d\n", dynamixel_id, data_buffer[0]);

          default :
              printf("dynamixel_id: %d unknown error: %d\n", dynamixel_id, data_buffer[0]);
      }//end switch
      return;
}//end fnctn

void roveDynamixel_WriteByteMSG(uint8_t dynamixel_id, uint8_t tx_data_byte) {

    //which pin is this device //TODO I dunno I like this in a struct instance maybe tho
    int tiva_pin = roveGetPinNum_ByDeviceId(dynamixel_id);

    //(char*)&  casts low level roveWare stdint _t types to high level char, int, etc ecosystem
    roveUart_Write(tiva_pin, (char*)&tx_data_byte, SINGLE_BYTE);
}//end fnctn

//dynamixel sigle pin uart serial messaging protocol overhead
uint32_t roveDynamixel_WritePacketMSG(uint8_t dynamixel_id, uint8_t* data_buffer, uint16_t data_byte_count){

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

    //delay poll listen for dyna error repsonse
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

uint8_t roveDynamixel_ReadByteMSG(uint8_t dynamixel_id) {

    uint8_t rx_data_byte;
    int tiva_pin = roveGetPinNum_ByDeviceId(dynamixel_id);

    roveUart_Read(tiva_pin, (char*)&rx_data_byte, SINGLE_BYTE);
    return rx_data_byte;
}//end fnctn

uint32_t roveDynamixel_ReadPacketMSG(uint8_t dynamixel_id) {

    //Todo:
    //2015 MOB Device Read???? //UART_Params.readTimeout
    //plug into Uart_READ
    uint8_t data_rx_byte_cnt = 0;

    uint8_t data_buffer[MAX_BYTES_AX12_REPLY];

    // This is used to decide how much pre-data to discard before quitting
    uint8_t rx_attempts = 0;

    while(rx_attempts < MAX_READ_AX12_ATTEMPT_COUNT){

        if(DYNAMIXEL_PACKET_START_BYTE == roveDynamixel_ReadByteMSG(dynamixel_id)) {

            if(DYNAMIXEL_PACKET_START_BYTE == roveDynamixel_ReadByteMSG(dynamixel_id)) {

                if(dynamixel_id == roveDynamixel_ReadByteMSG(dynamixel_id)) {

                    data_rx_byte_cnt = roveDynamixel_ReadByteMSG(dynamixel_id);

                    int current_byte_count = 0;
                    while(current_byte_count < data_rx_byte_cnt){

                        data_buffer[current_byte_count] = roveDynamixel_ReadByteMSG(dynamixel_id);
                        current_byte_count++;
                    }//endwhile

                    //dynamixel check_sum begin to add all the bytes including the id
                    current_byte_count = 0;
                    uint8_t check_sum = dynamixel_id;

                    while(current_byte_count < data_rx_byte_cnt){
                        check_sum += data_buffer[current_byte_count];
                    }//endwhile

                    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
                    check_sum = (~check_sum) & 0xFF;

                    if(check_sum == data_buffer[data_rx_byte_cnt] ){

                       return roveDynamixel_ParseReplyMSG(data_buffer);
                    }//endif
                }//endif
            }//endif
        }//endif

        rx_attempts++;
    }//endwhile

    return NO_PACKET;
}//end fnctn

uint32_t roveDynamixel_ParseReplyMSG(uint8_t* data_buffer) {

    uint32_t return_uint32_always = 0;
    switch( data_buffer[0] ){

        case TEST_INSTRUCTION:
            return return_uint32_always + (uint16_t)data_buffer[1];

        case TEST_ERROR:
            return return_uint32_always + (uint8_t)data_buffer[1];

        default :
            return NO_INSTRUCTION;
    }//end switch
}//end fnctn
//::End MSG Handling

//////////////////////////////////////////Begin telem REQUEST Handling

uint32_t roveDynamixel_ReadSpeedREQ(uint8_t dynamixel_id) {

    uint8_t msg_data[]=
        {READ_TELEM_AX12_REQ
        , READ_PRESENT_SPEED_AX12_REQ
        , READ_TWO_BYTES_AX12_REQ};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

uint32_t roveDynamixel_ReadAngleREQ(uint8_t dynamixel_id) {

    uint8_t msg_data[]=
        {READ_TELEM_AX12_REQ
        , READ_PRESENT_POSITION_AX12_REQ
        , READ_TWO_BYTES_AX12_REQ};

    roveDynamixel_WritePacketMSG(dynamixel_id, msg_data, sizeof(msg_data));
    return roveDynamixel_ReadPacketMSG(dynamixel_id);
}//end fnctn

//TODO HERE

/*////////////////////////Begin Dynamixel Runtime CFG and Telem REQUEST ROUTINES
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

/////////////////////////////////////////////////////Begin 2015 Horizon Motors CFG/CMD
//roveWare 2015 Horizon Drive Motors Robotech slb1300 series
void roveDriveMotor_ByPwmCMD(PWM_Handle motor, int16_t speed) {

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

    rovePwm_Write(motor, microseconds);
    return;
} //endfnct roveDriveMotor_ByPWM

/*roveWare 2015 Horizon Robot Arm Shoulder Prismatic Joint TODO series
void rovePolulu_DriveLinAct(int tiva_pin, int16_t speed){

    linear_actuator_struct linear_actuator;

    if( speed > 0 ){

    }else{
        linear_actuator.command_byte = LIN_ACT_REVERSE;
    }//end if


    //bit of an ugly hack to have called this whole int16_t speed
    linear_actuator.speed = (uint8_t)speed;

    roveUART_Write(tiva_pin, (char*)&linear_actuator, sizeof(linear_actuator) );
    return;
}//endfnctn roveDrivePolulu_LinActCmd*/
