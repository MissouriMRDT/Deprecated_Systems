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

//TODO
#define TEST_DEVICE_ID 251

#endif // ROVEWARE_PROTOCOL_H_
