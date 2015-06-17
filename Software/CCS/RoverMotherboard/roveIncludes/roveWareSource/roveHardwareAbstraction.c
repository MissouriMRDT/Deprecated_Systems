// roveHardwareAbstraction.c MST MRDT 2015
//
// Owen Chiaventone omc8db@mst.edu
//
// Connor Walsh cwd8d@mst.edu
//
// Judah Schad_jrs6w7@mst.edu

#include "../roveWareHeaders/roveHardwareAbstraction.h"
#include <ti/sysbios/knl/Task.h>

//TODO Configure Patch Panel Jacks to Physical Devices (In Hardware FIRST)

int getDeviceJack(int device) {

    switch (device) {
    case 0:
        //Tried to get jack for an null device
        printf("getDeviceJack passed null device %d\n", device);
        return -1;

 /*   case test_device_id:

        return TEST_JACK;

    case motor_left_id:

        return TEST_JACK;

    case bms_emergency_stop_command_id ... bms_total_amperage_telem_id:
        return TEST_JACK;

    case power_board_command_id ... power_board_telem_main_battery_voltage_id:
        return POWER_BOARD_ON_MOB;
*/
    case PTZ_Cam_id_0:
    		return PTZ_CAM_0;

    case PTZ_Cam_id_1:
    		return PTZ_CAM_1;

    case PTZ_Cam_id_2:
    		return PTZ_CAM_2;

    case PTZ_Cam_id_3:
    		return PTZ_CAM_3;

    case wrist_clock_wise ... drill_forward:
        return ARM_JACK;

    case gps_telem_reply:
        return GPS_ON_MOB;

    default:
        //Tried to get jack for an \ invalid device
        printf("getDeviceJack passed invalid device %d\n", device);
        return -1;

    } //endswitch (device)

} //endfnctn deviceJack

void pinMode(int pin, int mode) {

    //No idea how to start this one

} //endfnctn pinMode

void digitalWrite(int pin, int val) {

    //Alarmingly enough, a switch case is really the only way to deal with this
    //Everything is base on a bunch of TI defined constants that can't be indexed into
    //Or iterated through

    if (val == LOW) {

        switch (pin) {

        case U3_MUX_S0:
            GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, (0));
            break;
        case U3_MUX_S1:
            GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1, (0));
            break;
        case U4_MUX_S0:
            GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, (0));
            break;
        case U4_MUX_S1:
            GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_7, (0));
            break;
        case U5_MUX_S0:
            GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, (0));
            break;
        case U5_MUX_S1:
            GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, (0));
            break;
        case U6_MUX_S0:
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_2, (0));
            break;
        case U6_MUX_S1:
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_3, (0));
            break;
        case U7_MUX_S0:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, (0));
            break;
        case U7_MUX_S1:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, (0));
            break;
        default:
            //Tried to write to invalid device
            printf("DigitalWrite passed invalid pin %d\n", pin);
            return;
        }	//endswitch

    } else if (val == HIGH) {

        switch (pin) {

        case U3_MUX_S0:
            GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0, (~0));
            break;
        case U3_MUX_S1:
            GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1, (~0));
            break;
        case U4_MUX_S0:
            GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, (~0));
            break;
        case U4_MUX_S1:
            GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_7, (~0));
            break;
        case U5_MUX_S0:
            GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, (~0));
            break;
        case U5_MUX_S1:
            GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, (~0));
            break;
        case U6_MUX_S0:
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_2, (~0));
            break;
        case U6_MUX_S1:
            GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_3, (~0));
            break;
        case U7_MUX_S0:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, (~0));
            break;
        case U7_MUX_S1:
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, (~0));
            break;
        default:
            //Tried to write to invalid device
            printf("DigitalWrite passed invalid pin %d\n", pin);
            return;

        }	//endswitch

    }	//endif

    return;

}	//endfnctn digitalWrite

// output 1.5ms for 2 seconds to arm the servos

PWM_Handle rovePWMInit(PWM_Handle pwm_index, uint16_t period_in_microseconds) {

    PWM_Handle pwm_handle;

    PWM_Params pwmParams;
    uint16_t duty = 0;
    uint16_t dutyInc = 100;

    PWM_Params_init(&pwmParams);

    pwmParams.period = period_in_microseconds;
    pwm_handle = PWM_open(pwm_index, &pwmParams);

    if (pwm_handle == NULL) {

        System_abort("Error opening the PWM\n");

    }	//endif

    return pwm_handle;

}	//endfnctn rovePWMInit

void pwmWrite(PWM_Handle pin, int duty_microseconds) {

    PWM_setDuty(pin, duty_microseconds);

}	//endfnctn pwmWrite


void DriveMotor(PWM_Handle motor, int speed)
{
	//Scaling
	int microseconds;
	microseconds = speed / 2; //Scale down. We want the final range to be between 1000 and 2000
	microseconds += 1500;     //Offset. 1500 is neutral

    //Bound checking
    if (microseconds > 2000) //Upper bound on motor pulse width
        microseconds = 2000;
    if (microseconds < 1000) //Lower bound on motor pulse width
        microseconds = 1000;

	//Writing
	pwmWrite(motor, microseconds);
	return;

} //endfnct DriveMotor

int deviceWrite(int rs485jack, char* buffer, int bytes_to_write) {

    int bytes_wrote;

    // give us access to the uart handles defined at the global scope in main

    //extern UART_Handle uart0;
    //extern UART_Handle uart1;
    extern UART_Handle uart2;
    extern UART_Handle uart3;
    extern UART_Handle uart4;
    extern UART_Handle uart5;
    extern UART_Handle uart6;
    extern UART_Handle uart7;

    //System_printf("deviceWrite called\n");
    //System_flush();

    switch (rs485jack) {

    // we have to include case 0 to get TI's compiler to build a jump table
    // if we leave this out, mux performance goes from O(1) to O(n) (That's bad)
    case 0:
        break;
    case 1 ... 6:
     printf(
                "deviceWrite was called with a deprecated jack! Pin %d is now used for PWM!\n",
                rs485jack);
        break;
        /*
         case 1:
         // configure the mux pins, see the mux datasheet for more info
         digitalWrite(U3_MUX_S0, HIGH);
         digitalWrite(U3_MUX_S1, HIGH);
         // write the buffer to the device
         bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
         break;
         case 2:
         digitalWrite(U3_MUX_S0, LOW);
         digitalWrite(U3_MUX_S1, HIGH);
         bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
         break;
         case 3:
         digitalWrite(U3_MUX_S0, HIGH);
         digitalWrite(U3_MUX_S1, LOW);
         bytes_wrote = UART_write(uart3, buffer, bytes_to_write);
         break;
         case 4:
         digitalWrite(U6_MUX_S0, LOW);
         digitalWrite(U6_MUX_S1, HIGH);
         bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
         break;
         case 5:
         digitalWrite(U6_MUX_S0, HIGH);
         digitalWrite(U6_MUX_S1, LOW);
         bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
         break;
         case 6:
         digitalWrite(U7_MUX_S0, HIGH);
         digitalWrite(U7_MUX_S1, HIGH);
         bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
         break;
         */
    case 7:
        digitalWrite(U7_MUX_S0, LOW);
        digitalWrite(U7_MUX_S1, HIGH);
        bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
        break;
    case 8:
        digitalWrite(U7_MUX_S0, HIGH);
        digitalWrite(U7_MUX_S1, LOW);
        bytes_wrote = UART_write(uart7, buffer, bytes_to_write);
        break;
    case 9:
        digitalWrite(U5_MUX_S0, LOW);
        digitalWrite(U5_MUX_S1, LOW);
        bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
        break;
    case 10:
        digitalWrite(U5_MUX_S0, LOW);
        digitalWrite(U5_MUX_S1, HIGH);
        bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
        break;
    case 11:
        digitalWrite(U5_MUX_S0, HIGH);
        digitalWrite(U5_MUX_S1, LOW);
        bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
        break;
    case 12:
        digitalWrite(U5_MUX_S0, LOW);
        digitalWrite(U5_MUX_S1, LOW);
        bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
        break;
    case 13:
        digitalWrite(U5_MUX_S0, HIGH);
        digitalWrite(U5_MUX_S1, HIGH);
        bytes_wrote = UART_write(uart5, buffer, bytes_to_write);
        break;
    case 14:
        digitalWrite(U4_MUX_S0, LOW);
        digitalWrite(U4_MUX_S1, LOW);
        bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
        break;
    case 15:
        digitalWrite(U4_MUX_S0, LOW);
        digitalWrite(U4_MUX_S1, HIGH);
        bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
        break;
    case 16:
        digitalWrite(U4_MUX_S0, HIGH);
        digitalWrite(U4_MUX_S1, HIGH);
        bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
        break;
    case 17:
        digitalWrite(U4_MUX_S0, HIGH);
        digitalWrite(U4_MUX_S1, LOW);
        bytes_wrote = UART_write(uart4, buffer, bytes_to_write);
        break;
    case POWER_BOARD_ON_MOB:
        digitalWrite(U6_MUX_S0, HIGH);
        digitalWrite(U6_MUX_S1, HIGH);
        bytes_wrote = UART_write(uart6, buffer, bytes_to_write);
        break;
    case GPS_ON_MOB:
        bytes_wrote = UART_write(uart2, buffer, bytes_to_write);
        break;
    default:
        //Tried to write to invalid device
        printf("DeviceWrite passed invalid device %d\n", rs485jack);
        return -1;
        //etc.
    }    //end switch(rs485jack)

    // make sure the message is fully written before leaving the function

    ms_delay(1);

    return bytes_wrote;

}		//endfnctn deviceWrite

Void readIntTask(UArg arg0, UArg arg1) {
	System_printf("ReadIntTask going to sleep for %d ticks\n", (int)arg1);
  System_flush();
    Task_sleep((int) arg1);

    UART_readCancel((UART_Handle) arg0);

    System_printf("Canceled uart read\n");
    System_flush();
    while (1) // wait for task to be deleted by task that created it
    {
        Task_sleep(10000);
    } //end while
} //end TASK readIntTask

int UART_read_nonblocking(UART_Handle uart, char* buffer, int bytes_to_read,
        int timeout) {
    Task_Params readInterruptTaskParams;
    Task_Handle readInterruptTask;
    Error_Block eb;
    int bytes_read;

    Error_init(&eb);
    Task_Params_init(&readInterruptTaskParams);
    readInterruptTaskParams.stackSize = 512;
    readInterruptTaskParams.priority = -1;
    readInterruptTaskParams.arg0 = (UArg) uart;
    readInterruptTaskParams.arg1 = (UArg) timeout;

    readInterruptTask = Task_create((Task_FuncPtr) readIntTask,
            &readInterruptTaskParams, &eb);
    if (readInterruptTask == NULL) {
        System_printf("Failed to create Task in UART_read_nonblocking!\n");
        System_flush();
    }

    Task_setPri(readInterruptTask, RECV_UART_NONBLOCK_TASK_PRIORITY);
    bytes_read = UART_read(uart, buffer, bytes_to_read);
    Task_delete(&readInterruptTask);

    if (bytes_read >= 0) {
        return bytes_read;
    }

    return -1;
}
//TODO connor? ->  ^ Need to implement this function, should return negative one if error

int deviceRead(int rs485jack, char* buffer, int bytes_to_read, int timeout) {

    int bytes_read;

    // give us access to the uart handles defined at the global scope in main
    //extern UART_Handle uart0;
    //extern UART_Handle uart1;
    extern UART_Handle uart2;
    extern UART_Handle uart3;
    extern UART_Handle uart4;
    extern UART_Handle uart5;
    extern UART_Handle uart6;
    extern UART_Handle uart7;

    // we have to include case 0 to get TI's compiler to build a jump table
    // if we leave this out, mux performance goes from O(1) to O(n) (That's bad)
    switch (rs485jack) {
 /* Deprecated Non Blocking (Never found other telemetry
    case 0:
    case 1:
        //Configure the mux pins
        //See the mux datasheet for more info
        digitalWrite(U3_MUX_S0, HIGH);
        digitalWrite(U3_MUX_S1, HIGH);

        //Write the buffer to the device
        bytes_read = UART_read_nonblocking(uart3, buffer, bytes_to_read,
                timeout);
        break;
    case 2:
        digitalWrite(U3_MUX_S0, LOW);
        digitalWrite(U3_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart3, buffer, bytes_to_read,
                timeout);
        break;
    case 3:
        digitalWrite(U3_MUX_S0, HIGH);
        digitalWrite(U3_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart3, buffer, bytes_to_read,
                timeout);
        break;
    case 4:
        digitalWrite(U6_MUX_S0, LOW);
        digitalWrite(U6_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart6, buffer, bytes_to_read,
                timeout);
        break;
    case 5:
        digitalWrite(U6_MUX_S0, HIGH);
        digitalWrite(U6_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart6, buffer, bytes_to_read,
                timeout);
        break;
    case 6:
        digitalWrite(U7_MUX_S0, HIGH);
        digitalWrite(U7_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart7, buffer, bytes_to_read,
                timeout);
        break;
    case 7:
        digitalWrite(U7_MUX_S0, LOW);
        digitalWrite(U7_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart7, buffer, bytes_to_read,
                timeout);
        break;
    case 8:
        digitalWrite(U7_MUX_S0, HIGH);
        digitalWrite(U7_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart7, buffer, bytes_to_read,
                timeout);
        break;
    case 9:
        digitalWrite(U5_MUX_S0, LOW);
        digitalWrite(U5_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart5, buffer, bytes_to_read,
                timeout);
        break;
    case 10:
        digitalWrite(U5_MUX_S0, LOW);
        digitalWrite(U5_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart5, buffer, bytes_to_read,
                timeout);
        break;
    case 11:
        digitalWrite(U5_MUX_S0, HIGH);
        digitalWrite(U5_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart5, buffer, bytes_to_read,
                timeout);
        break;
    case 12:
        digitalWrite(U5_MUX_S0, LOW);
        digitalWrite(U5_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart5, buffer, bytes_to_read,
                timeout);
        break;
    case 13:
        digitalWrite(U5_MUX_S0, HIGH);
        digitalWrite(U5_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart5, buffer, bytes_to_read,
                timeout);
        break;
    case 14:
        digitalWrite(U4_MUX_S0, LOW);
        digitalWrite(U4_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart4, buffer, bytes_to_read,
                timeout);
        break;
    case 15:
        digitalWrite(U4_MUX_S0, LOW);
        digitalWrite(U4_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart4, buffer, bytes_to_read,
                timeout);
        break;
    case 16:
        digitalWrite(U4_MUX_S0, HIGH);
        digitalWrite(U4_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart4, buffer, bytes_to_read,
                timeout);
        break;
    case 17:
        digitalWrite(U4_MUX_S0, HIGH);
        digitalWrite(U4_MUX_S1, LOW);
        bytes_read = UART_read_nonblocking(uart4, buffer, bytes_to_read,
                timeout);
        break;
    case POWER_BOARD_ON_JACK:
        digitalWrite(U6_MUX_S0, HIGH);
        digitalWrite(U6_MUX_S1, HIGH);
        bytes_read = UART_read_nonblocking(uart6, buffer, bytes_to_read,
                timeout);
        break;
    case ONBOARD_ROVECOMM:
        bytes_read = UART_read_nonblocking(uart2, buffer, bytes_to_read,
                timeout);
        break;*/

//One Device Full Blocking Only
    case GPS_ON_MOB:
          bytes_read = UART_read(uart2, buffer, bytes_to_read);
        break;
    default:
        //Tried to write to invalid device
        printf("DeviceWrite passed invalid device! We only use GPS_ON_MOB %d\n", rs485jack);
        return -1;
        //etc.

    }			//endswitch(rs485jack)

    return bytes_read;

}			//endfnctn deviceRead

int generateMotorCommand(int speed, char* buffer) {

    // variable to do temp work on the count of needed buffer size
    int workerCount = 0;

    //protect from the max and min for the motorcontroller
    if (speed > 999) {
        speed = 999;
    }			//endif

    if (speed < -999) {
        speed = -999;
    }			//endif

    // variable to do temp work on the integer for ASCII conversion
    int workerInt = speed;

    // variable to work on the character for ASCII version
    char workerChar;

    while (workerInt != 0) {

        // shift right one decimal digit
        workerInt = workerInt / 10;

        // count that digit
        workerCount = workerCount + 1;

    }			// endwhile(workerInt != 0)

    // reload the speed value
    workerInt = speed;

    // initialize the buffer for G command
    buffer[0] = '!';
    buffer[1] = 'G';
    buffer[2] = ' ';
    buffer[3] = '1';
    buffer[4] = ' ';

    workerCount = workerCount + 5;
    // terminate the string with control character
    // motor controller interperts '_' as the \r
    buffer[workerCount] = '_';

    //just for good measure (systemPrintf debugging, etc)
    buffer[workerCount + 1] = '\0';

    // loop until we run out of digit
    while (workerCount > 5) {

        //move one character towards the front of the buffer
        workerCount = workerCount - 1;

        //extracts right digit of integer speed and stores as binary
        workerChar = (workerInt % 10);

        //add ASCII offset and place at the back of the buffer
        buffer[workerCount] = workerChar + '0';

        //truncates the last digit of integer speed (shift one digit)
        workerInt = workerInt / 10;

    }	//endwhile:	(workerCount > 0)

    // the message '!G 1 <ASCIISPEED>_' is placed by side effect in the passed buffer
    // return the size of the message
    return workerCount + 5;

}	//end fnctn generateMotorCommand

// TI does these inits in the API implicitly in EK_TM4C1294XL but we may want some added value here:

//void initUarts(){
//}//endfnctn initUarts

//void initMuxGPIO(){
//Probably just a bunch of pinModes.
//}//endfnctn initMuxGPIO
