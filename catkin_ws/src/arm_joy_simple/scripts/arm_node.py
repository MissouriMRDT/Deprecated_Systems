#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Joy
import robotarm_driver

# Author: Owen Chiaventone

arm = robotarm_driver.Arm()
joints = arm.neutral[:] # [:] means make a copy instead of a reference

def scale(value, in_min, in_max, out_min, out_max):
    """ Equivalent of Arduino's Map() function. Map means something different in python"""
    ans = int(((value - in_min) * ((out_max - out_min) / (in_max - in_min))) + out_min)
    if ans < out_min:
        ans = out_min
    elif ans > out_max:
        ans = out_max
    return ans

def callback(data):
    global joints
    if(data.buttons[1] == 1):
        arm.limp()
    if(data.buttons[3] == 1):
        joints = arm.neutral[:]
        arm.moveall(joints)
    if(data.axes[7] == 1):
        joints[1] += 10
        arm.moveall(joints)
    elif(data.axes[7] == -1):
        joints[1] -= 10
        arm.moveall(joints)
    if(data.axes[6] == 1):
        joints[0] += 10
        arm.moveall(joints)
    elif(data.axes[6] == -1):
        joints[0] -= 10
        arm.moveall(joints)
    arm.movejoint(5, scale(data.axes[5], 1, -1, 20, 120))

# Intializes everything
def start():
    # subscribed to twist inputs on topic "turtle1/cmd_vel"
    rospy.Subscriber("joy", Joy, callback)
    # starts the node
    rospy.init_node('arm_controller')
    rospy.spin()

if __name__ == '__main__':
    start()

