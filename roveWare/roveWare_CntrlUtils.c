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

void roveDriveMotor_ByPWM(PWM_Handle motor, int16_t speed){

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

} //endfnct roveDriveMotor_ByPWM




/*

#define sendData(args)  (Serial1.write(args))    // Write Over Serial
#define availableData() (Serial1.available())    // Check Serial Data Available
#define readData()      (Serial1.read())         // Read Serial Data
#define peekData()      (Serial1.peek())         // Peek Serial Data
#define beginCom(args)  (Serial1.begin(args))    // Begin Serial Comunication
#define endCom()        (Serial1.end())          // End Serial Comunication

// Macro for Timing

#define delayus(args) (delayMicroseconds(args))  // Delay Microseconds

// Macro for Comunication Flow Control

#define setDPin(DirPin,Mode)   (pinMode(DirPin,Mode))       // Select the Switch to TX/RX Mode Pin
#define switchCom(DirPin,Mode) (digitalWrite(DirPin,Mode))  // Switch to TX/RX Mode

*/
// Private Methods //////////////////////////////////////////////////////////////
/*
void roveDynamixel_SendByte(int tiva_pin, char* data_byte){

    roveUART_Write(tiva_pin, data_byte, SINGLE_BYTE);

}//end fnctn roveDynamixel_SendByte

int roveDynamixel_SendPacket(uint8_t dynamixel_id, char* data_buffer, int data_byte_count){

    //work variable
    int current_byte_count = 0;

    //Dynamixel check_sum : add all the bytes including the id
    char check_sum = dynamixel_id;

    //sum each byte in the data_buffer
    while(current_byte_count < data_byte_count){

        check_sum += data_buffer[current_byte_count];

    }//endwhile

    //last step in the check_sum is to complement the sum, and mask with 255 (max byte
    check_sum = (~check_sum) & 0xFF;

    //TODO I don't like this hard coded
    roveDigitalWrite(TRI_STATE_PIN, TX_HIGH);

    roveDynamixel_SendByte(DYNAMIXEL_START_BYTE);
    roveDynamixel_SendByte(DYNAMIXEL_START_BYTE);
    roveDynamixel_SendByte(dynamixel_id);

    //TODO wait why +1 ??
    roveDynamixel_SendByte(data_byte_count+1);

    //send each byte in the data_buffer
    while(current_byte_count < data_byte_count){

        roveDynamixel_SendByte(data_buffer[current_byte_count];

    }//endwhile

    roveDynamixel_SendByte(check_sum);

    //wait for uart_write
    roveDelay_MicroSec(DYNA_TX_DELAY_MICRO_SEC);

    roveDigitalWrite(TRI_STATE_PIN, RX_LOW);

    return ( roveCatch_DynamixelErrors() );

}//end fnctn roveDynamixel_SendPacket


/*
static int receivePacket(unsigned char numBytes)
{
    int result = -1;
    int Time_Counter = 0;
    while((availableData() < numBytes+5) & (Time_Counter < TIME_OUT)){
        Time_Counter++;
        delayus(1000);
    }

    while (availableData() > 0){
        unsigned char Incoming_Byte = readData();
        if ( (Incoming_Byte == 255) & (peekData() == 255) ){
            readData();                            // Start Bytes
            readData();                            // Ax-12 ID
            readData();                            // Length
            if( (unsigned char Error_Byte = readData()) != 0 )   // Error
                return (Error_Byte*(-1));
            if(numBytes==1)
                result = readData();
            else if(numBytes==2)
            {
                char tempByteL=readData();
                char tempByteH=readData();
                result = tempByteH << 8 + tempByteL;
            }
        }
    }
    return result;
}

static int read_error(void)
{
    int Time_Counter = 0;
    while((availableData() < 5) & (Time_Counter < TIME_OUT)){  // Wait for Data
        Time_Counter++;
        delayus(1000);
    }

    while (availableData() > 0){
        unsigned char Incoming_Byte = readData();
        if ( (Incoming_Byte == 255) & (peekData() == 255) ){
            readData();                                    // Start Bytes
            readData();                                    // Ax-12 ID
            readData();                                    // Length
            unsigned char Error_Byte = readData();                       // Error
            return (Error_Byte);
        }
    }
    return (-1);                                             // No Ax Response
}

// Public Methods //////////////////////////////////////////////////////////////

void beginDirectionPin(long baud, unsigned char directionPin)
{
    Direction_Pin = directionPin;
    setDPin(Direction_Pin,OUTPUT);
}

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

int move(unsigned char ID, int Position)
{
    char Position_H,Position_L;
    Position_H = Position >> 8;
    Position_L = Position;

    char data[]={AX_WRITE_DATA, AX_GOAL_POSITION_L, Position_L, Position_H};
    return sendPacket(ID,data,sizeof(data));
}

int moveSpeed(unsigned char ID, int Position, int Speed)
{
    char Position_H,Position_L,Speed_H,Speed_L;
    Position_H = Position >> 8;
    Position_L = Position;
    Speed_H = Speed >> 8;
    Speed_L = Speed;

    char data[]={AX_WRITE_DATA, AX_GOAL_POSITION_L, Position_L, Position_H, Speed_L, Speed_H};
    return sendPacket(ID,data,sizeof(data));
}

int setEndless(unsigned char ID, DynamixelStatus Status)
{
    if ( Status == AX_ON ) { //Wheel Mode
        char AX_CCW_AL_LT = 0;     // Changing the CCW Angle Limits for Full Rotation.
        char data[]={AX_WRITE_DATA, AX_CCW_ANGLE_LIMIT_L, AX_CCW_AL_LT, AX_CCW_AL_LT};
        return sendPacket(ID,data,sizeof(data));
    }
    else //Joint Mode
    {
        turn(ID,0,0);
        char data[]={AX_WRITE_DATA, AX_CCW_ANGLE_LIMIT_L, AX_CCW_AL_L, AX_CCW_AL_H};
        return sendPacket(ID,data,sizeof(data));
    }
}

int turn(unsigned char ID, DynamixelDirection Direction, int Speed)
{
    if(Direction == AX_CLOCKWISE) Speed += (1 >> 10);
    char Speed_H = Speed >> 8;
    char Speed_L = Speed;
    char data[]={AX_WRITE_DATA, AX_GOAL_SPEED_L, Speed_L, Speed_H};
    return sendPacket(ID,data,sizeof(data));
}

int moveRW(unsigned char ID, int Position)
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

int readPosition(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_PRESENT_POSITION_L, AX_BYTE_READ_TWO};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(2);
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

int readSpeed(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_PRESENT_SPEED_L, AX_BYTE_READ_TWO};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(2);
}

int readLoad(unsigned char ID)
{
    char data[]={AX_READ_DATA, AX_PRESENT_LOAD_L, AX_BYTE_READ_TWO};
    sendPacket(ID,data,sizeof(data));

    return receivePacket(2);
}

// EEPROM AREA  ///////////////////////////////////////////////////////////
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

typedef enum {
    AX_OFF = 0,
    AX_ON = 1
} DynamixelStatus;

typedef enum {
    AX_COUNTERCLOCKWISE = 0,
    AX_CLOCKWISE = 1
} DynamixelDirection;

typedef enum {
    AX_RETURN_NONE = 0,
    AX_RETURN_READ = 1,
    AX_RETURN_ALL = 2
} DynamixelStatusReturnLevel;

#include <inttypes.h>

unsigned char Direction_Pin;

static int sendPacket(unsigned char ID, char* data, int dataByteCount);
static int receivePacket(unsigned char numBytes);
static int read_error(void);

void beginDirectionPin(long baud, unsigned char directionPin);
void beginBaud(long baud);
void end(void);

int reset(unsigned char ID);
int ping(unsigned char ID);

int setID(unsigned char ID, unsigned char newID);
int setBD(unsigned char ID, long baud);

int move(unsigned char ID, int Position);
int moveSpeed(unsigned char ID, int Position, int Speed);
int setEndless(unsigned char ID,DynamixelStatus Status);
int turn(unsigned char ID, DynamixelDirection Direction, int Speed);
int moveRW(unsigned char ID, int Position);
int moveSpeedRW(unsigned char ID, int Position, int Speed);

void action(void);

int setTempLimit(unsigned char ID, unsigned char Temperature);
int setAngleLimit(unsigned char ID, int CWLimit, int CCWLimit);
int setVoltageLimit(unsigned char ID, unsigned char DVoltage, unsigned char UVoltage);
int setMaxTorque(unsigned char ID, int MaxTorque);
int setSRL(unsigned char ID, DynamixelStatusReturnLevel SRL);
int setRDT(unsigned char ID, unsigned char RDT);
int setLEDAlarm(unsigned char ID, unsigned char LEDAlarm);
int setShutdownAlarm(unsigned char ID, unsigned char SALARM);
int setCMargin(unsigned char ID, unsigned char CWCMargin, unsigned char CCWCMargin);
int setCSlope(unsigned char ID, unsigned char CWCSlope, unsigned char CCWCSlope);
int setPunch(unsigned char ID, int Punch);

int moving(unsigned char ID);
int lockRegister(unsigned char ID);
int RWStatus(unsigned char ID);

int readTemperature(unsigned char ID);
int readVoltage(unsigned char ID);
int readPosition(unsigned char ID);
int readSpeed(unsigned char ID);
int readLoad(unsigned char ID);

int torqueStatus(unsigned char ID, DynamixelStatus Status);
int ledStatus(unsigned char ID, DynamixelStatus Status);
*/



//ME








/*
//TODO
void roveDynamixel_Rotate(uint8_t dynamixel_id, int tiva_pin, int16_t first_command_value, int16_t second_command_value) {

    rove_dynamixel_struct dynamixel;

    dynamixel.protocol_start_byte1 = DYMAMIXEL_MSG_START_BYTE;
    dynamixel.protocol_start_byte2 = DYMAMIXEL_MSG_START_BYTE;

    dynamixel.dynamixel_id = dynamixel_id;

    //TODO
    dynamixel.message_byte_count = 5;
    dynamixel.read_write_flag = DYNAMIXEL_WRITE_DATA;

    //TODO
    dynamixel.dynamixel_register_address = DYNAMIXEL_ROTATE_AT_SPEED_COMMAND;

    //dynamixel.register1_low_byte = (uint8_t)first_command_value;
    //dynamixel.register1_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.register2_low_byte = (uint8_t)second_command_value;
    dynamixel.register2_high_byte = (uint8_t)(second_command_value >> 8);

    //dynamixel.check_sum  = ( ~(dynamixel_id + SIX_BYTES + DYNAMIXEL_WRITE_DATA + dynamixel.dynamixel_register_address + dynamixel.register1_low_byte + dynamixel.register1_high_byte + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

    dynamixel.check_sum  = ( ~(dynamixel_id + dynamixel.message_byte_count + dynamixel.read_write_flag + dynamixel.dynamixel_register_address + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

    roveUART_Write(tiva_pin, (char*)&dynamixel, sizeof(dynamixel) );

    return;

}//end fnctn buildDynamixelStructMessage

//TODO
void roveDynamixel_SetWheelMode(uint8_t dynamixel_id, int tiva_pin, int16_t first_command_value, int16_t second_command_value) {

    rove_dynamixel_struct dynamixel;

    dynamixel.protocol_start_byte1 = DYMAMIXEL_MSG_START_BYTE;
    dynamixel.protocol_start_byte2 = DYMAMIXEL_MSG_START_BYTE;

    dynamixel.dynamixel_id = dynamixel_id;

    //TODO
    dynamixel.message_byte_count = 5;
    dynamixel.read_write_flag = DYNAMIXEL_WRITE_DATA;

    //TODO
    dynamixel.dynamixel_register_address = SET_WHEEL_MODE_CMD_REG_ADDR;

    //dynamixel.register1_low_byte = (uint8_t)first_command_value;
    //dynamixel.register1_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.register2_low_byte = (uint8_t)first_command_value;
    dynamixel.register2_high_byte = (uint8_t)(first_command_value >> 8);

    dynamixel.check_sum  = ( ~(dynamixel_id + dynamixel.message_byte_count + dynamixel.read_write_flag + dynamixel.dynamixel_register_address + dynamixel.register2_low_byte + dynamixel.register2_high_byte) ) & 0xFF;

    roveUART_Write(tiva_pin, (char*)&dynamixel, sizeof(dynamixel) );

    return;

}//end fnctn buildDynamixelStructMessage


int16_t roveDynamixel_ConvertSpeed(int16_t dynamixel_rotate_at_speed){

    if(dynamixel_rotate_at_speed < DYNAMIXEL_SPEED_MIN) {

        dynamixel_rotate_at_speed = DYNAMIXEL_SPEED_MIN;

    }//end if

    if(dynamixel_rotate_at_speed > DYNAMIXEL_SPEED_MAX) {

        dynamixel_rotate_at_speed = DYNAMIXEL_SPEED_MAX;

    }//end if

    //dynamixel internal protocol
    if(dynamixel_rotate_at_speed < 0) {

        //0 to 1024 is counterclockwise speed
        dynamixel_rotate_at_speed = -dynamixel_rotate_at_speed;

    }else{

        //TODO 1024 to 2048 is clockwise speed
        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed + 1024;

    }//endif

    return dynamixel_rotate_at_speed;

}//end fnctn

int16_t roveDynamixel_ReverseSpeed(int16_t dynamixel_rotate_at_speed){

    if(dynamixel_rotate_at_speed < 1024) {

        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed -1024;

    }else{

        dynamixel_rotate_at_speed = dynamixel_rotate_at_speed + 1024;

    }//end if

    return dynamixel_rotate_at_speed;

}//end fnctn

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

}//endfnctn roveDrivePolulu_LinActCmd

*/

