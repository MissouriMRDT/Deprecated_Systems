// roveProtocol.c


#include "roveProtocol.h"


//TODO Reed Advice?

//DEVDec2016
#define TEST_DEVICE_ID 251
typedef enum HorizonDriveCommands {
    DRIVE_RIGHT_MOTORS = 100
    , DRIVE_LEFT_MOTORS = 101

} HorizonDriveCommands;
//Left Over from Horizon protocol//positive is clockwise, negative is counterclockwise
typedef enum HorizonArmCommands {

    WRIST_ROTATE = 201
    , WRIST_VERTICAL = 202
    , ELBOW_ROTATE = 203
    , ELBOW_VERTICAL = 204
    , BASE_ROTATE = 205
    , E_STOP_ARM = 206
    , ACTUATOR_INCREMENT = 207
    , GRIPPER_OPEN = 208

} HorizonArmCommands;
