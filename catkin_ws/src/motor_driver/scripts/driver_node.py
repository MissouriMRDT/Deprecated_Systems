#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
import trexjr

# Author: Owen Chiaventone
# This ROS Node converts twist messages into motor movements
# Subscribes to turtle1/cmd_vel
# Publishes nothing
# axis 1 aka left stick vertical controls linear speed
# axis 0 aka left stick horizonal controls angular speed

motors = trexjr.TrexJr()

def scale(value, in_min, in_max, out_min, out_max):
    """ Equivalent of Arduino's Map() function. Map means something different in python"""
    ans = int(((value - in_min) * ((out_max - out_min) / (in_max - in_min))) + out_min)
    if ans < out_min:
        ans = out_min
    elif ans > out_max:
        ans = out_max
    return ans

def callback(data):

    leftspeed = data.linear.x - data.angular.z
    rightspeed = data.linear.x + data.angular.z
    leftspeed = scale(leftspeed, -4, 4, -127, 127)
    rightspeed = scale(rightspeed, -4, 4, -127, 127)
    if leftspeed < 15 and leftspeed > -15:
        leftspeed = 0
    if rightspeed < 15 and rightspeed > -15:
        rightspeed = 0
    motors.move(leftspeed, rightspeed)

# Intializes everything
def start():
    # subscribed to twist inputs on topic "turtle1/cmd_vel"
    rospy.Subscriber("turtle1/cmd_vel", Twist, callback)
    # starts the node
    rospy.init_node('Motor_Controller')
    rospy.spin()

if __name__ == '__main__':
    start()

