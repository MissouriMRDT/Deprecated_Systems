// Missouri Science and Technology Mars Rover Design Team 2015_2016
//
// roveWare_Protocol.h
//
// jrs6w7@mst.edu
//
// for URC 2016 data_id based protocol definitions
//
// mrdt::rovWare

#ifndef ROVEWARE_PROTOCOL_H_
#define ROVEWARE_PROTOCOL_H_

//MRDT shorthand
#define FOREVER 1

//TODO

//PORT Physical Pin Outs for Tiva 123G:

#define TRI_STATE_BUFFER 0

// GPIO: TRI_STATE_BUFFER                  PB3
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

// To the Physical Pin Outs Tiva 1294XL:

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
/*
#define WRIST_A_ID  0x01
#define WRIST_B_ID  0x02
#define ELBOW_A_ID  0x03
#define ELBOW_B_ID  0x04
#define BASE_ID     0x05
//#define LIN_ACT_ID  0x06

#define GRIPPER_ID  0x08

//TODO

#define TEST_DEVICE_PIN 0

#define ARM_UART 1

#define WRIST_UART      ARM_UART
#define ELBOW_UART      ARM_UART
#define BASE_UART       ARM_UART

#define GRIPPER_UART END_EFFECTOR_UART

#define END_EFFECTOR_UART    2
#define LIN_ACT_UART    3

//These struct_id and payload definitions are how messages get version coupled to Base Station

//HORIZON command CONFIG protocol
#define DRIVE_RIGHT_MOTORS 100
#define DRIVE_LEFT_MOTORS 101

//Left Over from Horizon protocol//positive is clockwise, negative is counterclockwise
#define WRIST_ROTATE 201
#define WRIST_VERTICAL 202
#define ELBOW_ROTATE 203
#define ELBOW_VERTICAL 204
#define BASE_ROTATE 205
#define E_STOP_ARM 206
#define ACTUATOR_INCREMENT 207
#define GRIPPER_OPEN 208
*/
#define TEST_DEVICE_ID 251


#endif // ROVEWARE_PROTOCOL_H_
