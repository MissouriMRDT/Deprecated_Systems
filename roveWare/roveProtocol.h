// Missouri Science and Technology Mars Rover Design Team 2015_2016
// jrs6w7@mst.edu
//
// for URC 2016 data_id based protocol definitions
//
// mrdt::rovWare
#ifndef ROVEPROTOCOL_H_
#define ROVEPROTOCOL_H_

//These struct_id and payload definitions are how messages get version coupled to Base Station
//HORIZON command CONFIG protocol
enum HorizonDriveCommands { DRIVE_RIGHT_MOTORS = 100, DRIVE_LEFT_MOTORS = 101 };

//Left Over from Horizon protocol//positive is clockwise, negative is counterclockwise
enum HorizonArmCommands { WRIST_ROTATE = 201, WRIST_VERTICAL = 202 , ELBOW_ROTATE = 203, ELBOW_VERTICAL = 204, BASE_ROTATE = 205, E_STOP_ARM = 206, ACTUATOR_INCREMENT = 207, GRIPPER_OPEN = 208 };

//DEVDec2016
#define TEST_DEVICE_ID 251

#endif // ROVEPROTOCOL_H_
