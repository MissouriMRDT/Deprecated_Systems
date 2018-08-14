#ifndef VnhHalfBridgeMotorDriver_h
#define VnhHalfBridgeMotorDriver_h

#include <Arduino.h>

class VnhHalfBridgeMotorDriver
{
  public:  
    // CONSTRUCTORS
    VnhHalfBridgeMotorDriver(); // Default pin selection.
    VnhHalfBridgeMotorDriver(unsigned char INA1, unsigned char INB1, unsigned char EN1DIAG1, unsigned char CS1); 
                          
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ. 
    void setM1Speed(int speed); // Set speed for M1.
    void setM1Brake(int brake); // Brake M1. 
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1. 
    unsigned char getM1Fault(); // Get fault reading from M1.

  private:
    unsigned char _INA1;
    unsigned char _INB1;
    static const unsigned char _PWM1 = 9;
    unsigned char _EN1DIAG1;
    unsigned char _CS1;
 
};

#endif
