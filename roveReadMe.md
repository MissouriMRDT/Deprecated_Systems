# CCS-Device-2016
Code Composer Studio UDP Server to PWM / UART Device Controller

///////////////////////////////////////////////////////////////////////

//NEW_MEMBER_READ_ME.txt
//Open roveDevice_Thread
//Scroll to:
//END 2016 DEVICE RECIEVE
//UDP IP LAN SOCKET MESSAGE HAS BEEN RECIEVED FROM RED BASE STATION
//YOU NOW HAVE A FULL CHARACTER BYTE BUFFER: 
//TODOs
//Coming Soon
////////////////////////////////////////////////////////////////////////

//NEW CODE MEMBER CHALLENGE:
// watch these video: (optional, not required) 
// https://www.youtube.com/watch?v=OkSGiko5EE0

//EXPERT CODE MEMBER CODE BONUS CHALLENGE 
// watch these video: (optional, not required)  https://www.youtube.com/watch?v=zTRts9KHTBA
// http://processors.wiki.ti.com/index.php/Introduction_to_the_TI-RTOS_Kernel_Workshop#Intro_to_TI-RTOS_Kernel_Workshop_Online_Video_Tutorials





/////////TODO 2015 Deployed Updates : Deprecated Horizon DEV HW Pin Outs Tiva 123G:
// GPIO: TRI_STATE_BUFFER                   PB3
// GPIO: MOTOR_CONTROLLER_ENABLE            PD2
// GPIO: MOTOR_CONTROLLER_INPUT_1           PD3
// GPIO: MOTOR_CONTROLLER_INPUT_2           PE2
//UART 0:   TX PA1, RX PA0
//UART 1:   TX PB1, RX PB0
//UART 2:   TX PD7, RX PD6  MOTHERBOARD_UART
//UART 3:   TX PC7, RX PC6  END_EFFECTOR_UART
//UART 4:   TX PC5, RX PC4  DYNAMIXEL_UART
//UART 5:   TX PE5, RX PE4
//UART 6:   TX PD5, RX PD4
//UART 7:   TX PE1, RX PE0  LINEAR_ACTUATOR_UART

/////////////////////////////////TODO 2016 Developing Cycle : Pin Outs Tiva 1294XL:

// GPIO pins
// PH0_GPIO_PIN 0
// PH1_GPIO_PIN 1
// PM6_GPIO_PIN 2
// PM7_GPIO_PIN 3
// PL0_GPIO_PIN 4
// PL1_GPIO_PIN 5
// PK2_GPIO_PIN 6
// PK3_GPIO_PIN 7
// PE0_GPIO_PIN 8
// PE1_GPIO_PIN 9

// UART pins
// U2RX PA6_UART_2
// U2TX PA7_UART_2
// U3RX PA4_UART_3
// U3TX PA5_UART_3
// U4RX PK0_UART_4
// U4TX PK1_UART_4
// U5RX PC6_UART_5
// U5TX PC7_UART_5
// U6RX PP0_UART_6
// U6TX PP1_UART_6
// U7RX PC4_UART_7
// U7TX PC5_UART_7

//PWM Pins
// GPIO_PF1_M0PWM1
// GPIO_PF2_M0PWM2
// GPIO_PF3_M0PWM3
// GPIO_PG0_M0PWM4
// GPIO_PG1_M0PWM5
// GPIO_PK4_M0PWM6

//TODO PORT Physical Pin Outs for Tiva 123G:
//#define WRIST_A_ID  0x01
//#define WRIST_B_ID  0x02
//#define ELBOW_A_ID  0x03
//#define ELBOW_B_ID  0x04
//#define BASE_ID     0x05
//#define LIN_ACT_ID  0x06
//#define GRIPPER_ID  0x08

//#define ARM_UART 1
//#define WRIST_UART      ARM_UART
//#define ELBOW_UART      ARM_UART
//#define BASE_UART       ARM_UART
//#define GRIPPER_UART END_EFFECTOR_UART
//#define END_EFFECTOR_UART    2
//#define LIN_ACT_UART    3


//END NEW MEMBER_READ_ME.txt
