// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// Author: Judah Schad jrs6w7@mst.edu
//
// mrdt::rovWare
#include "../RoveBoard.h"

//C lib
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//CCS TI config
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include <xdc/runtime/System.h>



//=== RoveCCSTiva_Bios_Rtos_Drivers ========
//
void roveBoard_EK_TM4C1294XL_Open()
{
    // TI board driver routines
    EK_TM4C1294XL_initGeneral();
    EK_TM4C1294XL_initGPIO();
    EK_TM4C1294XL_initEMAC();
    EK_TM4C1294XL_initUART();
    EK_TM4C1294XL_initPWM();
    EK_TM4C1294XL_initWatchdog();
}//end fnctn


//=== RoveCCSTiva_Watchdog_Timer_Interrupt ========
//
roveWatchdog_Handle roveBoard_WATCHDOG_open(unsigned int watchdog_index, roveBoard_WATCHDOG_Callback attach_interrupt, bool board_reset_flag)
{
  Watchdog_Handle watchdogHandle;
  Watchdog_Params watchdogParams;

  // Create and enable a Watchdog with resets enabled
  Watchdog_Params_init(&watchdogParams);
  watchdogParams.callbackFxn = attach_interrupt;

  if(board_reset_flag)
  {
      watchdogParams.resetMode = Watchdog_RESET_ON;
  }else{

      watchdogParams.resetMode = Watchdog_RESET_OFF;
  }//end if

  watchdogHandle = Watchdog_open(watchdog_index, &watchdogParams);
  if (watchdogHandle == NULL) {
      System_abort("Error opening Watchdog!\n");
  }//end if

  Watchdog_clear(watchdogHandle);

  return watchdogHandle;
}//endfnctn


//=== RoveCCSTiva_Thread_Constructor ========
//
void roveBoard_LOOP_open(roveLoopPtr loop_Ptr, UInt loop_Pri)
{
    //construct
    Task_Params roveLoop_Params;
    Task_Params_init(&roveLoop_Params);

    //config
    roveLoop_Params.priority = loop_Pri;
    Task_create (loop_Ptr, &roveLoop_Params, NULL);
}//end fnctn

/*
//=== RoveCCSTiva_General_Purpose_IO_Pin_Access ========
//
typedef struct roveGPIO_Config
{
    uint32_t port;
    uint8_t pin;
} roveGPIO_Config;

typedef struct roveGPIO_Params
{
    uint32_t todo;
} roveGPIO_Params;

roveGPIO_Handle roveBoard_GPIO_open(uint32_t gpio_port, uint8_t gpio_pin)
{
    roveGPIO_Handle gpioHandle;

    gpioHandle->port = gpio_port;
    gpioHandle->pin = gpio_pin;

    return gpioHandle;
};//end fnctn

void roveBoard_GPIO_digitalWrite(roveGPIO_Handle gpio, uint8_t write_value) {

    uint8_t pin_value = 0;

    if(digital_value > 0) {

        pin_value = ~0;
    }//end if

    GPIOPinWrite(gpio->port, gpio->pin, pin_value);
}//endfnctn
void roveBoard_GPIO_digitalRead(roveGPIO_Handle gpio, uint8_t* read_value) {

    uint8_t pin_value = 0;

    if(digital_value > 0) {

        pin_value = ~0;
    }//end if

    GPIOPinWrite(gpio->port, gpio->pin, pin_value);
}//endfnctn
*/


//=== RoveCCSTiva_Pulse_Width_Modulation_Pin_Access ========
//
rovePWM_Handle roveBoard_PWM_open(unsigned int pwm_index, unsigned int period_in_microseconds){

    //Todo: DO NOT INIT PWM_0 -> ethernet support conflict: roveBoard/EK_TM4C1294XL.h
    //These are hardcode configured as OUTPUTS in the roveBoard/EK_TM4C1294XL.C file
    if (pwm_index == 0) {
        System_abort("Error opening the PWM\n");
    }//endif

    PWM_Handle pwmHandle;
    PWM_Params pwmParams;
    PWM_Params_init(&pwmParams);
    //TODO Phase Align params
    pwmParams.period = period_in_microseconds;

    pwmHandle = PWM_open(pwm_index, &pwmParams);
    if (pwmHandle == NULL) {
        System_abort("Error opening the PWM\n");
    }//endif

    return pwmHandle;
}//endfnctn

void roveBoard_PWM_write(rovePWM_Handle pwm, uint32_t duty_in_microseconds) {

    PWM_setDuty(pwm, duty_in_microseconds);
}//endfnctn


//=== RoveCCSTiva_Serial_Pin_Access ========
//
roveUART_Handle roveBoard_UART_open(unsigned int uart_index, unsigned int baud_rate){

    UART_Handle uartHandle;
    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = baud_rate;

    uartHandle = (UART_Handle)UART_open(uart_index, &uartParams);
    if (uartHandle == NULL) {
        System_abort("Error opening the UART\n");
    }//endif

    return uartHandle;
}//endfnct

//rove to Tiva Read/Write Hardware I/O Module Wrappers
roveBoard_ERROR roveBoard_UART_write(roveUART_Handle uart, void* write_buffer, size_t bytes_to_write) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);
    int bytes_written = UART_write(uart, write_buffer, bytes_to_write);

    if(bytes_written < 0){
        return ROVEBOARD_ERROR_UNKNOWN;
    }//end if

    return ROVEBOARD_ERROR_SUCCESS;
}//endfnctn

roveBoard_ERROR roveBoard_UART_read(roveUART_Handle uart, void* read_buffer, size_t bytes_to_read) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);

    int bytes_read = UART_read(uart, read_buffer, bytes_to_read);

    if(bytes_read < 0){
      return ROVEBOARD_ERROR_UNKNOWN;
    }//end if

    return ROVEBOARD_ERROR_SUCCESS;
}//endfnctn



/*
 * //typedef CCP_Handle roveCCP_Handle;
roveCCP_Handle ccpHandle;
roveCCP_Params ccpParams;
roveCCP_Handle roveCCP_open(ccp_index, &ccpParams);
roveCCP_Handle roveBoard_CCP_open(unsigned int ccp_index, unsigned int ccp_sample_period, unsigned int init_flag){

    roveCCP_Handle ccpHandle;
    roveCCP_Params ccpParams;
    roveCCP_Params_init(&ccpParams);

    //TODO: flags
    //uartParams.readReturnMode = roveCCP_RETURN_FULL;
    //uartParams.readMode = UART_MODE_BLOCKING;
    //uartParams.readEcho = UART_ECHO_OFF;

    ccpParams.samplePeriod = ccp_sample_period;

    ccpHandle = (roveCCP_Handle)roveCCP_open(ccp_index, &ccpParams);
    if (ccpHandle == NULL) {
        System_abort("Error opening the CCP\n");
    }//endif

    return uartHandle;
}//endfnct

//Todo int roveTIVAWARE_CCP_read(ccp, read_buffer, read_flag);
roveBoard_ERROR roveBoard_CCP_read(roveCCP_Handle ccp, void* read_buffer, unsigned int read_flag) {

    //roveUARTWrite timing issue?
    //roveDelay_MilliSec(1);

    int bytes_read = roveTIVAWARE_CCP_read(ccp, read_buffer, read_flag);

    if(bytes_read < 0){
      return ROVE_BOARD_ERROR_UNKNOWN;
    }//end if

    return ROVE_BOARD_ERROR_SUCCESS;
}//endfnctn



typedef struct ROVE_ADC_Config
{
    uint32_t roveBaseAddr;
} ROVE_ADC_Config;

typedef struct ROVE_ADC_Config   *roveADC_Handle;

// ADC_0 : S_SQR 1x6
// TODO roveADC_Handle* roveBoard_InitAdcCFG(UInt adc_index , UInt adc_cfg??);
roveADC_Handle roveBoard_ADC_open(unsigned int adc_index, unsigned int adc_flags);

roveADC_Handle roveBoard_ADC_open(unsigned int adc_index, unsigned int adc_flags)
{
    //TODO
    roveADC_Handle ADC_Handle = NULL;

    //        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    //        ROM_GPIOPinTypeADC((uint32_t) portBASERegister(port), digitalPinToBitMask(pin));

    // Enable the first sample sequencer to capture the value of channel SEQUENCER_INDEX when the processor trigger occurs.
    ADCSequenceConfigure(ADC0_BASE, adc_index, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, adc_index, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    //UInt adcParams;
    if (ADC_Handle == NULL) {
        System_abort("Error opening the ADC\n");
    } //endif

    return ADC_Handle;
}//endfnct

roveBoard_ERROR roveBoard_ADC_read(roveADC_Handle adc, void* read_buffer, unsigned int read_flag)
{
    uint32_t adc_read = 0;

    ADCSequenceEnable(ADC0_BASE, SEQUENCER_INDEX);

    // Trigger the sample sequence.
    ADCProcessorTrigger(ADC0_BASE, SEQUENCER_INDEX);

    // Wait until the sample sequence has completed.
    while(!ADCIntStatus(ADC0_BASE, SEQUENCER_INDEX, false));

   // ROM_ADCIntClear(ADC0_BASE, 3);
   // ROM_ADCProcessorTrigger(ADC0_BASE, 3);

    // Read the value from the ADC.
    ADCSequenceDataGet(ADC0_BASE, SEQUENCER_INDEX, &adc_read);

    //ROM_ADCIntClear(ADC0_BASE, 3);

    if(adc_read <= 0){
       return ROVE_BOARD_ERROR_UNKNOWN;
     }//end if

     return ROVE_BOARD_ERROR_SUCCESS;
 }//endfnctn


    uint16_t analogRead(uint8_t pin) {

        uint8_t port = digitalPinToPort(pin);

        uint16_t value[1];
        uint32_t channel = digitalPinToADCIn(pin);


        if (channel == NOT_ON_ADC) { //invalid ADC pin
            return 0;
        }

        ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
        if(channel != ADC_CTL_TS)
            ROM_GPIOPinTypeADC((uint32_t) portBASERegister(port), digitalPinToBitMask(pin));

        ROM_ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
        ROM_ADCSequenceStepConfigure(ADC0_BASE, 3, 0, channel | ADC_CTL_IE | ADC_CTL_END);
        ROM_ADCSequenceEnable(ADC0_BASE, 3);

        ROM_ADCIntClear(ADC0_BASE, 3);
        ROM_ADCProcessorTrigger(ADC0_BASE, 3);

        while(!ROM_ADCIntStatus(ADC0_BASE, 3, false)) {
        }//endwhile

        ROM_ADCIntClear(ADC0_BASE, 3);
        ROM_ADCSequenceDataGet(ADC0_BASE, 3, (unsigned long*) value);

        return mapResolution(value[0], 12, _readResolution);
    }
*/




//TODO Code Review
/*
typedef enum {
  AX,
  MX
} DynamixelType;

typedef enum {
  Wheel = 0,
  Joint = 1,
  MultiTurn = 2
} DynamixelMode;

typedef struct {
  uint8_t id;
  DynamixelType type;
  roveUART_Handle uart;
} Dynamixel;

typedef enum {
  DYNAMIXEL_ERROR_SUCCESS = 0,
  DYNAMIXEL_ERROR_VOLTAGE = 1,
  DYNAMIXEL_ERROR_ANGLE_LIMIT = 2,
  DYNAMIXEL_ERROR_OVERHEATING = 4,
  DYNAMIXEL_ERROR_RANGE = 8,
  DYNAMIXEL_ERROR_CHECKSUM = 16,
  DYNAMIXEL_ERROR_OVERLOAD = 32,
  DYNAMIXEL_ERROR_UNKNOWN = 64
} Dynamixel_Error;

void DynamixelInit(Dynamixel* dyna, DynamixelType type, uint8_t id, uint8_t uartIndex, int baud);

void DynamixelSendPacket(Dynamixel dyna, uint8_t length, uint8_t* instruction);
uint8_t DynamixelGetReturnPacket(Dynamixel dyna, uint8_t* buffer, size_t bufferSize);
uint8_t DynamixelGetError(Dynamixel dyna);

uint8_t DynamixelPing(Dynamixel dyna);
uint8_t DynamixelSetId(Dynamixel* dyna, uint8_t id);

uint8_t DynamixelMoveTo(Dynamixel dyna, uint16_t position);
uint8_t DynamixelTurnAt(Dynamixel dyna, uint16_t position, uint16_t speed);

uint8_t DynamixelSetStatusReturnLevel(Dynamixel dyna, uint8_t level);
uint8_t DynamixelSetMode(Dynamixel dyna, DynamixelMode mode);

uint8_t DynamixelGetMode(Dynamixel dyna, DynamixelMode* mode);
uint8_t DynamixelGetPresentPosition(Dynamixel dyna, uint16_t* pos);
uint8_t DynamixelGetPresentSpeed(Dynamixel dyna, uint16_t* speed);
uint8_t DynamixelGetLoad(Dynamixel dyna, uint16_t* load);
uint8_t DynamixelGetVoltage(Dynamixel dyna, uint8_t* voltage);
uint8_t DynamixelGetTemperature(Dynamixel dyna, uint8_t* temp);

// Instructions
#define DYNAMIXEL_PING                     1
#define DYNAMIXEL_READ_DATA                2
#define DYNAMIXEL_WRITE_DATA               3
#define DYNAMIXEL_REG_WRITE                4
#define DYNAMIXEL_ACTION                   5
#define DYNAMIXEL_RESET                    6

// Sets poll for response timeout
#define TXDELAY 2000

// DYNAMIXEL EEPROM AREA
#define DYNAMIXEL_MODEL_NUMBER_L           0
#define DYNAMIXEL_MODEL_NUMBER_H           1
#define DYNAMIXEL_VERSION                  2
#define DYNAMIXEL_ID                       3
#define DYNAMIXEL_BAUD_RATE                4
#define DYNAMIXEL_RETURN_DELAY_TIME        5
#define DYNAMIXEL_CW_ANGLE_LIMIT_L         6
#define DYNAMIXEL_CW_ANGLE_LIMIT_H         7
#define DYNAMIXEL_CCW_ANGLE_LIMIT_L        8
#define DYNAMIXEL_CCW_ANGLE_LIMIT_H        9
#define DYNAMIXEL_LIMIT_TEMPERATURE        11
#define DYNAMIXEL_DOWN_LIMIT_VOLTAGE       12
#define DYNAMIXEL_UP_LIMIT_VOLTAGE         13
#define DYNAMIXEL_MAX_TORQUE_L             14
#define DYNAMIXEL_MAX_TORQUE_H             15
#define DYNAMIXEL_RETURN_LEVEL             16
#define DYNAMIXEL_ALARM_LED                17
#define DYNAMIXEL_ALARM_SHUTDOWN           18
//Todo: ////////////////////////////////////////////19&23?
// MX SERIES EEPROM
#define MX_MULTI_TURN_OFFSET_L             20
#define MX_MULTI_TURN_OFFSET_H             21
#define MX_RESOLUTION_DIVIDER              22
//////////////////////////////////////////////////////////
// DYNAMIXEL RAM AREA
#define DYNAMIXEL_TORQUE_ENABLE            24
#define DYNAMIXEL_LED                      25

// AX SERIES RAM
#define AX_CW_COMPLIANCE_MARGIN            26
#define AX_CCW_COMPLIANCE_MARGIN           27
#define AX_CW_COMPLIANCE_SLOPE             28
#define AX_CCW_COMPLIANCE_SLOPE            29
//Todo: ////////////////////////////////////////////29?
// MX SERIES RAM
#define MX_D_GAIN                          26
#define MX_I_GAIN                          27
#define MX_P_GAIN                          28

#define DYNAMIXEL_GOAL_POSITION_L          30
#define DYNAMIXEL_GOAL_POSITION_H          31
#define DYNAMIXEL_MOVING_SPEED_L           32
#define DYNAMIXEL_MOVING_SPEED_H           33
#define DYNAMIXEL_TORQUE_LIMIT_L           34
#define DYNAMIXEL_TORQUE_LIMIT_H           35
#define DYNAMIXEL_PRESENT_POSITION_L       36
#define DYNAMIXEL_PRESENT_POSITION_H       37
#define DYNAMIXEL_PRESENT_SPEED_L          38
#define DYNAMIXEL_PRESENT_SPEED_H          39
#define DYNAMIXEL_PRESENT_LOAD_L           40
#define DYNAMIXEL_PRESENT_LOAD_H           41
#define DYNAMIXEL_PRESENT_VOLTAGE          42
#define DYNAMIXEL_PRESENT_TEMPERATURE      43
#define DYNAMIXEL_REGISTERED_INSTRUCTION   44
#define DYNAMIXEL_MOVING                   46
#define DYNAMIXEL_LOCK                     47
#define DYNAMIXEL_PUNCH_L                  48
#define DYNAMIXEL_PUNCH_H                  49
//Todo: ////////////////////////////////////////////WHAT IS THIS//MX ONLY Mode!!
#define MX_GOAL_ACCELERATION               73

#define MX_HIGH_BYTE_MASK                  0x0F
#define AX_HIGH_BYTE_MASK                  0x03


#ifdef __cplusplus
}
#endif

#endif // ROVECONTROL_H_



// roveWare Upgrades Version 2 Release



//Standard C lib
//#include <stdint.h>
//Rover Wrappers for hardware specific microcontroller pin protocol drivers
//#include "../RoveBoard/RoveBoardPins.h"


//TODO Judah Factor Out Dev Shorthand
//Public
// 12 bit for MX
// AX_12_SCALE_REG_MSB = 1023 clockwise direction is the 10th bit
// Which is likely why most savage electronics control schemes fail out erratically on the 12 bit mx series btw
typedef enum ROVECNTRL_DEV_16
{
    CNTRLS_CUR_TODO_BOOKMRK_RET_ERRNO = 777
    , DEV16_NO_INSTRUCTION =          0x00
    , DEV16_TEST_INSTRUCTION =      0x01
    , DEV16_TEST_ERROR =            0x02

    //Dyna cntrl Flags
    , AX_ERROR =                    -1
    , AX_NO_PACKET =                0
    , AX_ERROR_FREE =               1
    , AX_PACKET =                   1
    , AX_READ_REPLY =               1
    , READ_ONE_BYTE_AX_REQ =        1
    , READ_TWO_BYTES_AX_REQ =       2

     //Dyna cfg
    , AX_MAX_READ_ATTMPT_CNT =      10
    , AX_MSG_MAX_BYTES =            20
    , AX_12_MAX_WHEEL_SPEED =       2047
    , AX_12_MAX_JOINT_SPEED =       1023
} ROVECNTRL_DEV_16;

//instance defintion
typedef struct rove_dyna_serial
{
    //Dynmxl AX12
    uint8_t dynmxl_id;
    roveUART_Handle uart;
    roveGPIO_Handle tri_state_buffer;
    uint8_t read_reply_flag;
    uint8_t reply_id;
    int32_t reply;
    int32_t err_no;
}__attribute__((packed)) rove_dyna_serial, *rove_dyna_serial_ptr;


#ifdef __cplusplus
// ========  roveControl  ========
// Cplus object wrappers
class RoveControl
{
    private:
        rove_dyna_serial _rove_dynamxl;

    public:
        RoveControl(int newId);
        ~RoveControl();

        int BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin);
        //TODO https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Named_Constructor
        //BeginMx(serial_pin, dyna_id, baud_ra);
};// end class
#endif

int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle serial_port, roveGPIO_Handle tri_state_pin);

//WHEEL Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetWheelModeCFG( rove_dyna_serial* dynmxl);
int32_t roveAxDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl, int16_t wheel_speed);
int32_t roveAxDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl);

//JOINT Mode : set to "AngleLimit" to anything other than zero
int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl);
int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_position, uint16_t joint_speed);
int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl);
*/




/*Todo Test Suite
int testWheelMode(int min_speed, int max_speed, int speed_increment, int pause_microseconds);
int testJointMode(int min_angle, int max_angle, int angle_increment, int speed, int pause_microseconds);

int RoveControl::testWheelMode(int min_speed, int max_speed, int speed_increment, int pause_microseconds)
{
    //TODO
    test_metrics test;
    return roveDynmxAx_TestWheelMode(&_rove_dynamxl, &test);
}// end method
int RoveControl::testJointMode(int min_angle, int max_angle, int angle_increment, int speed, int pause_microseconds)
{
    //TODO
    test_metrics test;
    return roveDynmxAx_TestJointMode(&_rove_dynamxl, &test);
}// end method



int32_t roveDynmxAx_TestWheelMode(rove_dyna_serial* dynmxl, test_metrics* test);
int32_t roveDynmxAx_TestJointMode(rove_dyna_serial* dynmxl, test_metrics* test);

int32_t roveDynmxAx_TestWheelMode(rove_dyna_serial* dynmxl, test_metrics* test)
{
    if( roveDynmxAx_SetWheelModeCFG(dynmxl) )
    {
        printf("Dev16 Error roveDynmxAx_SetWheelModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    if( roveDynmxAx_SetWheelModeCFG(dynmxl) )
    {
        printf("Dev16 Error roveDynmxAx_SetWheelModeCFG ldynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    int16_t speed = 0;

    //ramp up from zero to max forward
    for (speed = 0; speed < test->max_speed; speed += test->speed_increment)
    {
        //TODO arg2 could be negative??
        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed)){
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        //roveBoard_DelayMilliSec(test->pause_microseconds);
    } //end for

    //ramp back from max forward through zero to max reverse
    for (speed = test->max_speed; speed > test->min_speed; speed -= test->speed_increment)
    {
        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        //roveBoard_DelayMilliSec(test->pause_microseconds);
    } //end for

    //ramp back from max reverse landing on zero
    for (speed = test->min_speed; speed < 0; speed += test->speed_increment)
    {
        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        }//endif

        if(roveDynmxAx_SpinWheelCMD(dynmxl, speed))
        {
            printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            return AX_ERROR;
        }//endif

        //roveBoard_DelayMilliSec(test->pause_microseconds);
    } //end for

    //roveBoard_DelayMilliSec(4*test->pause_microseconds);
    return AX_ERROR_FREE;
};//end fnctn*/


/*
int32_t roveDynmxAx_TestJointMode(rove_dyna_serial* dynmxl, test_metrics* test)
{
    if( roveDynmxAx_SetJointModeCFG(dynmxl))
    {
        printf("Dev16 Error roveDynmxAx_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    if(roveDynmxAx_SetJointModeCFG(dynmxl))
    {
        printf("Dev16 Error roveDynmxAx_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//endif

    //catch dynamixel joint api confusion
    if(test->min_speed > test->max_speed)
    {
        printf("test->min_speed > test->max_speed Dev16 Error roveDynmxAx_SetJointModeCFG dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
        return AX_ERROR;
    }//end if

    //joint mode only takes positive speeds
    if(test->min_speed < 0)
    {
        test->min_speed = 0;
    }//end if

    //joint mode only takes positive speeds
    if(test->max_speed > AX_12_MAX_JOINT_SPEED)
    {
       test->max_speed = AX_12_MAX_JOINT_SPEED;
    }//end if

    uint16_t speed = 0;

    for (speed = test->min_speed; speed < test->max_speed; speed += test->speed_increment)
    {
        uint16_t angle = 0;

        for (angle = test->min_angle; angle < test->max_angle; angle += test->angle_increment)
        {
            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
                return AX_ERROR;
            }//endif

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
                return AX_ERROR;
            }//endif

            //roveBoard_DelayMilliSec(test->pause_microseconds);
        } //end for

        for (angle = test->max_angle; angle > test->min_angle; angle -= test->angle_increment)
        {

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed))
            {
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            //roveBoard_DelayMilliSec(test->pause_microseconds);
        } //end for

        for (angle = test->min_angle; angle < test->max_angle; angle += test->angle_increment) {

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed)){
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            if(roveDynmxAx_RotateJointCMD(dynmxl, angle, speed)){
                printf("Dev16 Error roveDynmxAx_SpinWheelCMD dynmxl->dynmxl_id :%d\n!", dynmxl->dynmxl_id);
            }//endif

            //roveBoard_DelayMilliSec(test->pause_microseconds);
        } //end for

    } //end for

    //oveBoard_DelayMilliSec(4*test->pause_microseconds);
    return AX_ERROR_FREE;
};//end fnctn
*/

//TODO Code Review



/*
void roveCntrl_Dynamixel_Init(Dynamixel* dyna, DynamixelType type, uint8_t id, uint8_t uartIndex, int baud) {
  dyna -> type = type;
  dyna -> id = id;
  dyna -> uart = roveBoard_UART_open(uartIndex, baud);
}

void roveCntrl_Dynamixel_SendPacket(Dynamixel dyna, uint8_t length, uint8_t* instruction) {
  int i;
  uint8_t checksum;

  checksum = dyna.id + (length + 1);
  for(i=0; i < length; i++) {
    checksum += instruction[i];
  }
  checksum = ~checksum;

  uint8_t packet[length + 5];

  packet[0] = 0xFF;
  packet[1] = 0xFF;
  packet[2] = dyna.id;
  packet[3] = length + 1;
  memcpy(&(packet[4]), instruction, length);
  packet[length + 4] = checksum;

  roveBoard_UART_write(dyna.uart, packet, length + 5);
  //roveBoard_Delay_Microseconds(50);
  roveBoard_UART_read(dyna.uart, NULL, length + 5);
}

uint8_t roveCntrl_Dynamixel_GetReturnPacket(Dynamixel dyna, uint8_t* data, size_t dataSize) {
  // To be fixed
  uint8_t id, length, error;
  uint8_t temp1, temp2;


  if(roveBoard_UART_available(dyna.uart) == true){
  roveBoard_UART_read(dyna.uart, &temp2, 1);

  while(roveBoard_UART_available(dyna.uart) == true) {
    temp1 = temp2;
    roveBoard_UART_read(dyna.uart, &temp2, 1);
    if (temp1 == 255 && temp2 == 255) {
      roveBoard_UART_read(dyna.uart, &id, 1);
      roveBoard_UART_read(dyna.uart, &length, 1);
      roveBoard_UART_read(dyna.uart, &error, 1);
      if (dataSize + 2 != length) {
        roveBoard_UART_read(dyna.uart, NULL, length-2);
        return (error & DYNAMIXEL_ERROR_UNKNOWN);
      } else {
        roveBoard_UART_read(dyna.uart, data, length-2);
        roveBoard_UART_read(dyna.uart, NULL, 1);
        return error;
      }
    }
  }}
  return DYNAMIXEL_ERROR_UNKNOWN;
}

uint8_t roveCntrl_Dynamixel_GetError(Dynamixel dyna) {
  return DynamixelGetReturnPacket(dyna, NULL, 0);
}

uint8_t roveCntrl_Dynamixel_Ping(Dynamixel dyna) {
  uint8_t msgLength = 1;
  uint8_t command = DYNAMIXEL_PING;

  DynamixelSendPacket(dyna, msgLength, &command);
  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetError(dyna);
}

uint8_t roveCntrl_Dynamixel_SetId(Dynamixel* dyna, uint8_t id) {
  uint8_t msgLength = 3;
  uint8_t commands[msgLength];

  commands[0] = DYNAMIXEL_WRITE_DATA;
  commands[1] = DYNAMIXEL_ID;
  commands[2] = id;

  DynamixelSendPacket(*dyna, msgLength, commands);

  dyna -> id = id;

  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetError(*dyna);
}

uint8_t roveCntrl_Dynamixel_SpinWheel(Dynamixel dyna, uint16_t position) {
  uint8_t msgLength = 4;
  uint8_t commands[msgLength];

  commands[0] = DYNAMIXEL_WRITE_DATA;
  commands[1] = DYNAMIXEL_GOAL_POSITION_L;
  commands[2] = position & 0x00FF;
  commands[3] = position >> 8;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetError(dyna);
}

uint8_t roveCntrl_Dynamixel_RotateJoint(Dynamixel dyna, uint16_t position, uint16_t speed) {
  uint8_t msgLength = 6;
  uint8_t commands[msgLength];

  commands[0] = DYNAMIXEL_WRITE_DATA;
  commands[1] = DYNAMIXEL_GOAL_POSITION_L;
  commands[2] = position & 0x00FF;
  commands[3] = position >> 8;
  commands[4] = speed & 0x00FF;
  commands[5] = speed >> 8;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetError(dyna);
}

uint8_t roveCntrl_Dynamixel_SetStatusReturnLevel(Dynamixel dyna, uint8_t level) {
  uint8_t msgLength = 3;
  uint8_t commands[msgLength];

  commands[0] = DYNAMIXEL_WRITE_DATA;
  commands[1] = DYNAMIXEL_RETURN_LEVEL;
  commands[2] = level;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetError(dyna);
}


uint8_t roveCntrl_Dynamixel_SetMode(Dynamixel dyna, DynamixelMode mode) {
  uint8_t msgLength = 6;
  uint8_t commands[msgLength];
  uint8_t ccwHighByte;

  commands[0] = DYNAMIXEL_WRITE_DATA;
  commands[1] = DYNAMIXEL_CW_ANGLE_LIMIT_L;

  switch (mode) {
    case Wheel:
      commands[2] = 0x00;
      commands[3] = 0x00;
      commands[4] = 0x00;
      commands[5] = 0x00;
      break;
    case Joint:
      if (dyna.type == MX) {
        ccwHighByte = 0xFF & MX_HIGH_BYTE_MASK;
      }

      if (dyna.type == AX) {
        ccwHighByte = 0xFF & AX_HIGH_BYTE_MASK;
      }

      commands[2] = 0x00;
      commands[3] = 0x00;
      commands[4] = 0xFF;
      commands[5] = ccwHighByte;
      break;
    case MultiTurn:
      if (dyna.type == AX)
        return DYNAMIXEL_ERROR_UNKNOWN;

      if (dyna.type == MX) {
        ccwHighByte = 0xFF & MX_HIGH_BYTE_MASK;
      }

      commands[2] = 0xFF;
      commands[3] = ccwHighByte;
      commands[4] = 0xFF;
      commands[5] = ccwHighByte;
      break;
    default:
      return DYNAMIXEL_ERROR_UNKNOWN;
  }

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetError(dyna);
}

uint8_t roveCntrl_Dynamixel_GetMode(Dynamixel dyna, DynamixelMode* mode) {
  uint8_t msgLength = 3, dataSize = 4, error;
  uint8_t commands[msgLength], buffer[dataSize];
  uint16_t cwAngleLimit, ccwAngleLimit;

  commands[0] = DYNAMIXEL_READ_DATA;
  commands[1] = DYNAMIXEL_CW_ANGLE_LIMIT_L;
  commands[2] = dataSize;

  roveCntrl_Dynamixel_SendPacket(dyna, msgLength, commands);

  ////roveBoard_Delay_Microseconds(TXDELAY);
  error = roveCntrl_Dynamixel_GetReturnPacket(dyna, buffer, dataSize);

  cwAngleLimit = buffer[1];
  cwAngleLimit = (cwAngleLimit << 8) | buffer[0];
  ccwAngleLimit = buffer[3];
  ccwAngleLimit = (ccwAngleLimit << 8) | buffer[2];

  if (cwAngleLimit == 0 && ccwAngleLimit == 0) {
    *mode = Wheel;
  }

  switch (dyna.type) {
    case AX:
      if (cwAngleLimit == 0 && ccwAngleLimit == 0x03FF) {
        *mode = Joint;
      }
      break;
    case MX:
      if (cwAngleLimit == 0 && ccwAngleLimit == 0x0FFF) {
        *mode = Joint;
      }
      if (cwAngleLimit == 0x0FFF && ccwAngleLimit == 0x0FFF) {
        *mode = MultiTurn;
      }
  }
  return error;
}

uint8_t roveCntrl_Dynamixel_GetPresentPosition(Dynamixel dyna, uint16_t* pos) {
  uint8_t msgLength = 3, dataSize = 2, error;
  uint8_t commands[msgLength], buffer[dataSize];

  commands[0] = DYNAMIXEL_READ_DATA;
  commands[1] = DYNAMIXEL_PRESENT_POSITION_L;
  commands[2] = dataSize;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  error = roveCntrl_GetReturnPacket(dyna, buffer, dataSize);

  *pos = buffer[1];
  *pos = (*pos << 8) | buffer[0];

  return  error;
}

uint8_t roveCntrl_Dynamixel_GetPresentSpeed(Dynamixel dyna, uint16_t* speed) {
  uint8_t msgLength = 3, dataSize = 2, error;
  uint8_t commands[msgLength], buffer[dataSize];

  commands[0] = DYNAMIXEL_READ_DATA;
  commands[1] = DYNAMIXEL_PRESENT_SPEED_L;
  commands[2] = dataSize;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  error = DynamixelGetReturnPacket(dyna, buffer, dataSize);

  *speed = buffer[1];
  *speed = (*speed << 8) | buffer[0];

  return error;
}

uint8_t roveCntrl_Dynamixel_GetLoad(Dynamixel dyna, uint16_t* load) {
  uint8_t msgLength = 3, dataSize = 2, error;
  uint8_t commands[msgLength], buffer[dataSize];

  commands[0] = DYNAMIXEL_READ_DATA;
  commands[1] = DYNAMIXEL_PRESENT_LOAD_L;
  commands[2] = dataSize;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  error = DynamixelGetReturnPacket(dyna, buffer, dataSize);

  *load = buffer[1];
  *load = (*load << 8) | buffer[0];

  return error;
}

uint8_t DynamixelGetVoltage(Dynamixel dyna, uint8_t* voltage) {
  uint8_t msgLength = 3, dataSize = 1;
  uint8_t commands[msgLength];

  commands[0] = DYNAMIXEL_READ_DATA;
  commands[1] = DYNAMIXEL_PRESENT_VOLTAGE;
  commands[2] = dataSize;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetReturnPacket(dyna, voltage, dataSize);
}

uint8_t DynamixelGetTemperature(Dynamixel dyna, uint8_t* temp) {
  uint8_t msgLength = 3, dataSize = 1;
  uint8_t commands[msgLength], buffer[dataSize];

  commands[0] = DYNAMIXEL_READ_DATA;
  commands[1] = DYNAMIXEL_PRESENT_TEMPERATURE;
  commands[2] = dataSize;

  DynamixelSendPacket(dyna, msgLength, commands);

  //roveBoard_Delay_Microseconds(TXDELAY);
  return DynamixelGetReturnPacket(dyna, temp, dataSize);
}

#ifdef __cplusplus
}
#endif

// roveWare Upgrades Version 2 Release
// TODO Judah Factor Out Dev Shorthand
//Private
typedef enum ROVECNTRL_AX_12
{
//TODO RoveDev16 Cntrl vals for dyna ax motor series cfg (factor to ax/mx/rx series/model flag):
    AX_12_SCALE_REG_MSB =           10
    , AX_12_SCALE_SPEED_REG_BIAS =  1023
    , AX_12_SCALE_JOINT_REG_BIAS =  1023
    , AX_PACKET_START_BYTE  =       255
    , AX_DELAY_TX_uSEC =            100

//Runtime Dynamixel Ax_12 Regs
    //Message response behavior control regs
    , WRITE_AX_CMD =                1
    , READ_AX_REQ =                 2

    //Motor control modes regs
    , JOINT_MODE_AX_CFG =           8
    , WHEEL_MODE_AX_CFG =           8
    , TORQUE_MODE_AX_CFG =          24

    //Motor operating limits reg
    , TORQUE_LIMIT_AX_CFG =         34

    //Control command regs
    , GO_ANGLE_AX_REG =             30
    , GO_SPEED_AX_REG =             32

    //Telemetry request regs
    , READ_ANGLE_AX_REQ =           36
    , READ_SPEED_AX_REQ =           38
    , READ_LOAD_AX_REQ =            40
    , READ_VOLTAGE_AX_REQ =         42
    , READ_TEMPERATURE_AX_REQ =     43
    , READ_CURRENT_AX_REQ =         68
} ROVECNTRL_AX_12;

// ========  roveControl  ========
RoveControl::RoveControl(int newId)
{
    _rove_dynamxl.dynmxl_id = newId;
}// end constructor
RoveControl::~RoveControl()
{
}// end destructor
int RoveControl::BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin)
{
    //return roveDynmxAx_InitCFG(&_rove_dynamxl, (uint8_t)dyna_id, serial_pin, tri_state_pin);
    return -1;
}// end method

///////////////::BEGIN//////RoveDyna Private Functions//////////////

//General Atomic Telemetry Request
static int32_t roveDynmxAx_ReadRegsREQ(rove_dyna_serial* dynmxl_id, uint8_t dyna_reg_addr, uint8_t dyna_reg_byte_cnt);

//developement hook for empty stub debug:
static int32_t roveDynmxAx_CatchERRNO(rove_dyna_serial* dynmxl_id);

//Handle Dyna Serial Comms
static int32_t roveDynmxAx_WritePacketMSG(rove_dyna_serial* dynmxl, uint8_t* write_msg_data, int32_t msg_data_byte_count);
static int32_t roveDynmxAx_ReadPacketMSG(rove_dyna_serial* dynmxl);
static int32_t roveDynmxAx_ParseREPLY(rove_dyna_serial* dynmxl, uint8_t* data_buffer);

//TODO
static int16_t roveDynmxAx_ScaleReg_ByAngleDegrees(int16_t joint_angle_degrees, int16_t scale_joint_reg_bias);



///////////////::BEGIN//////RoveDyna Implementation//////////////

//construct a motor
int32_t roveDynmxAx_InitCFG(rove_dyna_serial* dynmxl, uint8_t dyna_id, roveUART_Handle uart_port, roveGPIO_Handle tri_state_pin)
{
    //TODO Data Validation? roveDynmxAx_ValidateCfg(dynmxl, dyna_id, tri_state_pin, uart_port);
    dynmxl->dynmxl_id = dyna_id;
    dynmxl->tri_state_buffer = tri_state_pin;
    dynmxl->uart = uart_port;

    dynmxl->read_reply_flag = AX_NO_PACKET;
    dynmxl->reply_id = AX_NO_PACKET;
    dynmxl->reply = AX_NO_PACKET;

    //TODO? roveDynmxAx_CatchERRNO(dynmxl);
    return dynmxl->err_no = AX_ERROR_FREE;
};//end fnctn



//Wheel Mode: set to both Angle Limits to zero. The motor spins endlessly
int32_t roveDynmxAx_SetWheelModeCFG(rove_dyna_serial* dynmxl)
{
    //wheel Mode both are 0
    uint8_t cw_angle_limit_low_byte = 0;
    uint8_t cw_angle_limit_high_byte = 0;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]={

        //immediate no delay command timing
        WRITE_AX_CMD
        , WHEEL_MODE_AX_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->err_no = roveDynmxAx_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

    //Immediate return zero was read suceess
    return roveDynmxAx_CatchERRNO(dynmxl);
}//end fnctn



int32_t roveDynmxAx_SpinWheelCMD(rove_dyna_serial* dynmxl , int16_t wheel_speed)
{
    //handle negative speed scale to absolute value
    //AX12 - 10bit Wheel -> 0-1023 CCW, 1024 - 2047 CW
    wheel_speed =+ AX_12_SCALE_SPEED_REG_BIAS;

    //scale direction by shift operations
    if(wheel_speed > AX_12_SCALE_SPEED_REG_BIAS)
    {
        // TODO to 12 bit for MX
        // AX_12_SCALE_REG_MSB = 1023 clockwise direction is the 10th bit
        wheel_speed += (1 >> AX_12_SCALE_REG_MSB);
    }//end if

    uint8_t speed_low_byte = wheel_speed;
    uint8_t speed_high_byte = wheel_speed >> 8;

    uint8_t write_msg_data[]={

        //imediate command (no delay timing)
        //command servo to go go to goal speed
        WRITE_AX_CMD
        , GO_SPEED_AX_REG
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->err_no =

        roveDynmxAx_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

    return roveDynmxAx_CatchERRNO(dynmxl);
}//end fnctn



int32_t roveDynmxAx_ReadWheelREQ(rove_dyna_serial* dynmxl)
{
    //TODO GBENGA: (see roveDynmxAx_ReadJointREQ implementation)
    //return roveDynmxAx_ReadRegsREQ(dynmxl , dyna_reg_addr, dyna_reg_byte_cnt)
    return CNTRLS_CUR_TODO_BOOKMRK_RET_ERRNO;
}//end fnctn



//Joint Mode : set to Angle Limits anything other than zero
int32_t roveDynmxAx_SetJointModeCFG(rove_dyna_serial* dynmxl)
{
    //TOD how to ctually set set speed zero? homing function function goal rotation to zero?
    roveDynmxAx_SpinWheelCMD(dynmxl, 0);

    //SetEndless goal rotation...wheel mode is from TODO 0 to 4095 for the MX SERIES?
    //Multi Turn mode on the MX?
    uint8_t cw_angle_limit_low_byte = 255;
    uint8_t cw_angle_limit_high_byte = 3;
    uint8_t ccw_angle_limit_low_byte = 0;
    uint8_t ccw_angle_limit_high_byte = 0;

    uint8_t write_msg_data[]={

        //immediate no delay timing
        //switch mode by setting ccw angle max limit
        WRITE_AX_CMD
        , JOINT_MODE_AX_CFG
        , cw_angle_limit_low_byte
        , cw_angle_limit_high_byte
        , ccw_angle_limit_low_byte
        , ccw_angle_limit_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->err_no = roveDynmxAx_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

    //no errors -> ::roveDynmxAx_WritePacketMSG set dynmxl_id->error_flag
    if(dynmxl->err_no)
    {
        return roveDynmxAx_CatchERRNO(dynmxl);
    }//end if

    return dynmxl->err_no;
}//end fnctn



//TODO __Judah__ hmmmmm I don't like this path
int16_t roveDynmxAx_ScaleReg_ByAngleDegrees(int16_t joint_angle_degrees, int16_t scale_joint_reg_bias)
{
    return CNTRLS_CUR_TODO_BOOKMRK_RET_ERRNO;
}//edn fnctn

int32_t roveDynmxAx_RotateJointCMD( rove_dyna_serial* dynmxl, uint16_t joint_angle , uint16_t joint_speed)
{
    joint_angle = roveDynmxAx_ScaleReg_ByAngleDegrees(joint_angle, AX_12_SCALE_JOINT_REG_BIAS);

    //shift split two bytes
    uint8_t angle_low_byte = joint_angle;
    uint8_t angle_high_byte = joint_angle >> 8;
    uint8_t speed_low_byte = joint_speed;
    uint8_t speed_high_byte = joint_speed >> 8;

    uint8_t write_msg_data[]={

        //imediate command (no delay timing)
        //command servo to go to goal position
        //command servo to go go to goal speed
        WRITE_AX_CMD
        , GO_ANGLE_AX_REG
        , angle_low_byte
        , angle_high_byte
        , GO_SPEED_AX_REG
        , speed_low_byte
        , speed_high_byte};

    //write a message (and wait for dynmxl reply when asked to)
    dynmxl->reply = roveDynmxAx_WritePacketMSG(

            dynmxl
            , write_msg_data
            , sizeof(write_msg_data));

    //no errors -> ::roveDynmxAx_WritePacketMSG set dynmxl_id->error_flag
    if(dynmxl->err_no)
    {
        return roveDynmxAx_CatchERRNO(dynmxl);
    }//end if

    return dynmxl->err_no;
}//end fnctn



int32_t roveDynmxAx_ReadJointREQ(rove_dyna_serial* dynmxl)
{
    int16_t joint_angle = roveDynmxAx_ReadRegsREQ(

            dynmxl
            , READ_ANGLE_AX_REQ
            , READ_TWO_BYTES_AX_REQ);

    int16_t joint_speed = roveDynmxAx_ReadRegsREQ(

            dynmxl
            , READ_SPEED_AX_REQ
            , READ_TWO_BYTES_AX_REQ);

    //speed is the two high bytes, and angle is the two low bytes
    return joint_angle  + (joint_speed << 16);
}//end fnctn



//TODO refactor to aggregate functions How to couple with multiple lookup calls by Model lookup table??
//How to bind Registers by by Model Number (ie MX has extra regs... (enum cfg? lookup table?)
//https://gist.github.com/joshreed13/639117cbaefd505f0093
static int32_t roveDynmxAx_ReadRegsREQ(rove_dyna_serial* dynmxl , uint8_t dyna_reg_addr, uint8_t dyna_reg_byte_cnt)
{
    dynmxl->read_reply_flag = AX_READ_REPLY;

    uint8_t write_msg_data[]={

        READ_AX_REQ
        , dyna_reg_addr
        , dyna_reg_byte_cnt };

    return roveDynmxAx_WritePacketMSG(dynmxl, write_msg_data, sizeof(write_msg_data));
}//end fnctn



/////////////////////////////////////////////////////Begin MSG Handling
//dynmxl sigle pin uart serial messaging protocol overhead
static int32_t roveDynmxAx_WritePacketMSG(rove_dyna_serial* dynmxl, uint8_t* write_msg_data, int32_t msg_data_byte_count)
{
    //dynmxl check_sum begin to add all the bytes including the id
    uint8_t header_byte = 0;
    int32_t current_byte_count = 0;

    uint8_t check_sum = dynmxl->dynmxl_id;

    //check_sum with each byte in the data_buffer
    while(current_byte_count < msg_data_byte_count)
    {
        check_sum += write_msg_data[current_byte_count];
    }//endwhile
    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
    check_sum = (~check_sum) & 0xFF;

    //set tristate buffer to uart_tx write status
    //roveBoard_DigitalWrite(&dynmxl->tri_state_buffer, 1);

    //start dyna msg, id the dyna, tell dyna the msg data size (+ check_sum)
    header_byte = AX_PACKET_START_BYTE;
    roveBoard_UART_write(dynmxl->uart, &header_byte, 1);

    header_byte = AX_PACKET_START_BYTE;
    roveBoard_UART_write(dynmxl->uart, &header_byte, 1);

    header_byte = dynmxl->dynmxl_id;
    roveBoard_UART_write(dynmxl->uart, &header_byte, 1);

    header_byte = msg_data_byte_count + 1;
    roveBoard_UART_write(dynmxl->uart, &header_byte, 1);

    //send each byte in the data_buffer
    while(current_byte_count < msg_data_byte_count)
    {
        roveBoard_UART_write(dynmxl->uart, &write_msg_data[current_byte_count], 1);
    }//endwhile

    //send check sum
    roveBoard_UART_write(dynmxl->uart, &check_sum, 1);
    //wait for uart_write
    //roveBoard_DelayMicroSec(AX_DELAY_TX_uSEC);
    //set tristate buffer to uart_rx read status
    //roveBoard_DigitalWrite(&dynmxl->tri_state_buffer, 0);

    if(dynmxl->read_reply_flag)
    {
        //delay poll listen for dyna reply (uart read on polling timeout delay with error_status) :: we return 0 on success
        return roveDynmxAx_ReadPacketMSG(dynmxl);
    }//end if

    //no reply needed (implies read_reply_flag = 0) :: we return 0 as success
    return dynmxl->read_reply_flag;
}//end fnctn



static int32_t roveDynmxAx_ReadPacketMSG(rove_dyna_serial* dynmxl)
{
    //Todo:
    //UART_Params.readTimeout
    uint8_t data_rx_byte_cnt = 0;
    int32_t current_byte_count = 0;
    uint8_t data_buffer[AX_MSG_MAX_BYTES];

    uint8_t check_sum = dynmxl->dynmxl_id;

    //This is used to decide how much pre-data to discard before quitting
    uint8_t rx_attempts = 0;
    while(rx_attempts < AX_MAX_READ_ATTMPT_CNT)
    {
        roveBoard_UART_read(dynmxl->uart, data_buffer, 1);
        if(AX_PACKET_START_BYTE == data_buffer[data_rx_byte_cnt])
        {
            //qual and discard header bytes
            data_rx_byte_cnt++;
            roveBoard_UART_read(dynmxl->uart, data_buffer, 1);
            if(AX_PACKET_START_BYTE == data_buffer[data_rx_byte_cnt])
            {
                data_rx_byte_cnt++;
                roveBoard_UART_read(dynmxl->uart, data_buffer, 1);
                if(dynmxl->dynmxl_id == data_buffer[data_rx_byte_cnt])
                {
                    //get the data payload
                    data_rx_byte_cnt= 0;
                    data_rx_byte_cnt = data_buffer[data_rx_byte_cnt];
                    while(current_byte_count < data_rx_byte_cnt)
                    {
                        roveBoard_UART_read(dynmxl->uart, &data_buffer[current_byte_count] , 1);
                        current_byte_count++;
                    }//endwhile

                    //dynmxl check_sum begin to add all the bytes (to the id)
                    current_byte_count = 0;
                    while(current_byte_count < data_rx_byte_cnt)
                    {
                        check_sum += data_buffer[current_byte_count];
                    }//endwhile

                    //last step in the check_sum is to complement the sum, and mask with 255 (max num 8 bits)
                    check_sum = (~check_sum) & 0xFF;
                    if(check_sum == data_buffer[data_rx_byte_cnt] )
                    {
                       //return a single int32 reply payload
                       return dynmxl->err_no = roveDynmxAx_ParseREPLY(dynmxl, data_buffer);
                    }//endif
                }//endif
            }//endif
        }//endif

        rx_attempts++;
    }//endwhile

    return AX_NO_PACKET;
}//end fnctn



//TODO JUDAH REFACTOR
static int32_t roveDynmxAx_ParseREPLY(rove_dyna_serial* dynmxl, uint8_t* data_buffer)
{
    dynmxl->reply_id = data_buffer[0];

    uint16_t reply = data_buffer[1];

        switch(dynmxl->reply_id)
        {
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
static int32_t roveDynmxAx_CatchERRNO(rove_dyna_serial* dynmxl){
    //TODO currently fnctn still pas through
    return CNTRLS_CUR_TODO_BOOKMRK_RET_ERRNO;
}//end_if



////////////////////////////////////////////////////////////////////////////////////////
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
}//END::GBENGA TODO







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

End Judah TODO*

// ======== USING roveComm ========
//Cplus Public in roveWiresCplus.h
//roveComm::beginUdp(local_ip_addr, port);
//roveComm::readUdp(remote_ip_addr, "char_message");

//C Public as Cplus Private in roveComm.h
//int32_t roveComm_InitUdpCFG(&_udp_socket, (uint8_t*)my_ip_addr, (int32_t)port);
//int32_t roveComm_GetUdpMSG(&_udp_socket, &_udp_data);
// ========  =======  ========

// ======== USING roveControl ========
//Cplus Public in roveWiresCplus.h
//roveControl::BeginAx(char dyna_id, int baud_rate, char serial_pin, char tri_state_pin);

//C Public as Cplus Private in roveControl.h
//int32_t roveDynmxAx_InitCFG(&_rove_dynamxl, (uint8_t)dyna_id, serial_pin, tri_state_pin);
// ========  =======  ========
 *
 *
 */

