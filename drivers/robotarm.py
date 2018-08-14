# Robotic arm driver for Lil' Shitter
# Author: Owen Chiaventone
# License: get yer grubby hands off it. How did you even get this code?

from __future__ import division
import time

# Import the PCA9685 module.
import Adafruit_PCA9685

class Arm:
    servo_min = 150  # Min pulse length out of 4096. Corresponds to 1.00 ms
    servo_max = 600  # Max pulse length out of 4096. Corresponds to 2.00 ms
    
    neutral = [70, 20, 0, 30, 0, 20]
    pushup = [50, 150, 0, 30, 0, 20]
    def __init__(self):
        self.controller = Adafruit_PCA9685.PCA9685()
        self.controller.set_pwm_freq(60) # Servos work best at 50 or 60 hz
                                         # I set it to 60 because 
                                         # THIS IS AMERICA, DAMNIT!
    def movejoint(self, joint, angle):
        """ angle should be between 0 and 180, inclusive
            Joint should be between 0 and 5, inclusive"""
        self.controller.set_pwm(joint, 0, scale(angle, 0, 180, Arm.servo_min, Arm.servo_max))
        
    def moveall(self, angle_list):
        """ angle_list should be a list of 6 angles between 0 and 180
            angle_list[0] = base
            angle_list[1] = first shoulder joint 
            ...
            angle_list[5] = gripper """
        for joint, angle in enumerate(angle_list):
            self.movejoint(joint, angle)
    def reset(self):
        self.moveall([90, 90, 90, 90, 90, 90])
    def limp(self):
	self.controller = Adafruit_PCA9685.PCA9685()
    def sweepall(self):
        for joint in range(0, 6):
            for angle in range(0, 180):
                self.movejoint(joint, angle)
                time.sleep(0.01)
            self.movejoint(joint, 90)
            

def scale(value, in_min, in_max, out_min, out_max):
    """ Equivalent of Arduino's Map() function. Map means something different in python"""
    return int(((value - in_min) * ((out_max - out_min) / (in_max - in_min))) + out_min)
