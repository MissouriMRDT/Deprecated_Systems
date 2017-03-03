#include "RoveBoard.h"
#include "RoveComm.h"
#include <stdint.h>


//enums
typedef enum CommandResult
{
  Success,
  Fail
} CommandResult;


//var/pins
const uint32_t WATCHDOG_TIMEOUT_US = 2000000; //the amount of microseconds that should pass without getting a transmission from base station before the arm ceases moving for safety
const uint8_t IP_ADDRESS [4] = {192, 168, 1, 135};

//functions


void initialize();
void spectrometer();
void partial_spec(const uint16_t data);


void turnOnLaser();//Turns On the Spectrometer Laser
void turnOffLaser();//Turns Off the Spectrometer Laser
void openFlap();//Opens the Sample Cache Flap
void closeFlap();//Closes the Sample Cache Flap
void rotateCarousel(const uint16_t pos);//Rotates carosel to position 0-4 from current position given a position (0-4)
void spectroMotorOff();
float instantSoilTemp();//Returns one Soil Temperature reading
float instantAirTemp();//Returns one Air Termperature reading
float instantUV();//Return one UV intensisty reading
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);//Maps the float value for UV intensity
//float instantPressure();//Returns one pressure reading but has problems so is not implemented
int readPhotoDiode1();//Returns one int reading from Photo Diode 1
int readPhotoDiode2();//Returns one int reading from Photo Diode 2
void spectroMotorForward();//Turns the spectrometer motor on, in the forward direction
void spectroMotorReverse();//Turns the spectrometer motor on, but in the reverse direction
float instantAirHumidity();//Placeholder
float instantSoilHumidity();//Placeholder
float instantMethane();//Placeholder



